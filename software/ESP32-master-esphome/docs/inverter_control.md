# Inverter control: stage 1

The active implementation is in `esp32-master.yaml`. The one-second `interval`
automation owns all automatic output-priority decisions. Sensor callbacks only
record receipt times. Power and current measurements remain available for
monitoring; they are not decision inputs in this stage.

## Decision inputs and freshness

The controller requires four published values:

| Input | Register | Maximum age |
| --- | --- | --- |
| Battery voltage | 215 | 30 seconds |
| PV voltage | 219 | 30 seconds |
| Operation mode | 201 | 30 seconds |
| Output priority | 301 | 30 seconds |

Each callback updates its own monotonic receipt timestamp, including when the
value is unchanged. A separate bit mask distinguishes a received value at uptime
zero from a value that has never been received. Voltages must be finite, battery
voltage positive, and PV voltage nonnegative. `Unknown` operation mode prevents
SOL entry. All time differences use unsigned subtraction to support uptime
counter wraparound. Individual register publications are not an atomic snapshot.

Missing, invalid or stale data resets SOL qualification and selects SUB as the
target. If no input has been received in the last 30 seconds, the controller
reports that communication is unavailable and does not enqueue writes. If some
communication remains, it can request SUB using the last known priority. It
cannot guarantee delivery when the inverter is disconnected. Already confirmed,
fresh SUB does not need to be written again.

## Priority decisions

| Condition | Result |
| --- | --- |
| Fresh operation mode `Fault` | Suspend automatic writes and reset SOL qualification |
| PV voltage below 180 V | Target SUB |
| Current priority SOL and a `Mains` sample newer than the latest priority change/request | Target SUB, regardless of PV voltage |
| Current priority SOL, other valid conditions | Remain in SOL |
| Other priorities | Target SUB unless SOL qualification completes |

SOL qualification requires all of the following:

- All four decision inputs are fresh and valid.
- Operation mode is `Mains`, `Off-Grid` or `Bypass`.
- PV voltage is strictly above 200 V.
- Battery voltage is at least 26.5 V.
- Astronomy permits entry, or no valid astronomical result is available.
- The above conditions remain true for at least 120 seconds.
- More than 15 minutes have elapsed since the last priority request or observed
  priority change, including the first priority read after boot.

Any failed qualification condition resets the 120-second timer. The controller
checks cached values each second, but receipt age limits continuity: it cannot
qualify using one old sample for two minutes. The inverter polling period remains
10 seconds, so a short event between polls may not be observed.

Between 180 and 200 V inclusive, SOL can remain active if it is not operating on
mains. SUB cannot qualify for SOL in that band. Battery voltage below 26.5 V
blocks entry; it is not an exit threshold in this stage.

The automatic targets are exclusively SOL (register value 1) and SUB (value 3).
UTI and SBU remain selectable through the existing entity, but the automatic
controller can overwrite a manual choice. There is no manual/automatic switch in
this stage. Unsupported automatic priorities are normalized to SUB before later
qualification for SOL.

## Astronomy and operation without internet

`Allow Solar Mode` uses the existing hysteresis: elevation strictly above 15
degrees enables SOL entry; elevation strictly below 8 degrees disables entry.
Between the thresholds the previous result is retained. At boot, the astronomical
permission starts disabled. Elevation is evaluated at most once per second.

When the configured time source has no valid time, or solar elevation cannot be
calculated, `Allow Solar Mode` returns true: only the local voltage and inverter
state conditions gate SOL entry. Restoring valid time restarts the astronomical
hysteresis from disabled. The gate affects entry only: sunset alone does not
force a running SOL inverter into SUB.

Losing internet after synchronization does not necessarily invalidate the local
clock; in that case astronomy continues normally. No network-connected state is
required for voltage control. Both API and Wi-Fi `reboot_timeout` are set to `0s`
to prevent connection-loss reboots. Other reboot causes are unaffected.

`Inverter Clock Valid` reports time validity; `Allow Solar Mode` reports the
effective entry permission, including the voltage-only fallback. A future I2C RTC
can provide valid time, but must also be connected to the time source used here
and by `sun`; adding RTC hardware alone does not change this configuration.

## Writes and confirmation

`optimistic: false` is explicit on the priority selector. A request records its
target, time and priority-publication sequence. Confirmation requires a subsequent
fresh publication of the requested priority; a write request alone is not logged
as a confirmed change. Operation mode and output priority are separate concepts.

Only one request is awaited at a time, for up to 30 seconds. Further requests are
spaced by at least 60 seconds. A SUB request that cancels a previously requested
SOL can bypass this spacing, including when cached readback still says SUB.
The first-stage logic can therefore retreat from SOL when a later poll reports
`Mains`; it does not add a fixed post-switch grace period. The operation-mode
receipt time must be strictly newer than the latest priority change/request.
This prevents a cached pre-switch `Mains` sample from immediately cancelling a
newly confirmed SOL priority. Equal receipt timestamps wait for another poll.

Both requests and observed priority changes update the 15-minute SOL cooldown.
An unconfirmed request emits a warning and resets qualification. The controller
never reports successful delivery without readback. `Inverter Control Status`
and `inverter_control` logs expose decisions and pending confirmation.

## Limitations and hardware checks

This is a structural first step, not a complete battery-protection algorithm.
High PV voltage and a charged battery do not prove sufficient available solar
power, particularly when the battery was charged from the grid. The offline
voltage-only fallback intentionally loses the dawn/dusk astronomical protection.
It retains the 120-second qualification and 15-minute SOL cooldown. A loss of
communication can leave the inverter in its last physical priority.

No new battery undervoltage exit threshold, discharge-current limit, energy
budget, power balance or relay-event counter is introduced. Existing inverter
hardware protections remain necessary. Before enabling operation on hardware:

1. Confirm output-priority readback for SUB and SOL; verify requested and confirmed
   log messages are distinct.
2. Confirm the four required readings arrive within 30 seconds during normal
   operation. Check whether this timeout suits the actual Modbus queue.
3. Verify SOL entry only after 120 seconds of qualifying voltages and completion
   of the 15-minute cooldown.
4. Check that a failed qualifying sample resets the stability timer.
5. Check SUB selection below 180 V and when SOL reports `Mains`.
6. Disconnect inverter communication: SOL must not be entered; status must expose
   the loss of communication. Reconnect and confirm fresh readings recover control.
7. Restart without internet access. With invalid time, verify voltage-only entry
   permission. Then restore time and check the 15/8-degree hysteresis.
8. Disable Home Assistant and separately Wi-Fi; verify these losses do not cause
   periodic reboots and local Modbus control continues.

Do not infer successful physical tests from configuration validation or compilation.
