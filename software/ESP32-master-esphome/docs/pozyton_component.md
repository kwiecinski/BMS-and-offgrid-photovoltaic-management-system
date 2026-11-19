# Pozyton SEAB and EABM ESPHome component

## Purpose and scope

This local ESPHome external component polls one SEAB meter and one EABM meter on a shared half-duplex RS485 bus. The component owns the UART reader, serializes meter sessions, and publishes only measurements whose response frame and numeric data have passed validation.

The MAX3485 direction pin is HIGH while transmitting and LOW while receiving. The current `esp32-master.yaml` uses TX GPIO13, RX GPIO14, and direction GPIO2, with SEAB address `523.0012230` and EABM address `825 0001275`.

RS485 describes the electrical interface. The meter messages use the manufacturer's text protocol with control bytes and XOR BCC, not Modbus RTU.

## Serial settings and addressing

Both meters use 7 data bits, even parity, and one stop bit. The included example configures 4800 baud on the UART and in the component timing settings. If the meters are configured for another RS485 speed, update both `uart.baud_rate` and `pozyton_energy_meters.baud_rate` to the same value. The supported setting range in this component is 300–19200 baud.

Address formats are model-specific:

- SEAB: `ttt.nnnnnnn`, initialized with `/Attt.nnnnnnn\r\n`.
- EABM: `nnn nnnnnnn`, initialized with `/?nnn nnnnnnn!\r\n`.

The configured address must be each meter's individual factory serial number. Do not poll either device at the shared zero address.

## Session startup and framing

SEAB responds to its addressed `/A` request with `/g` and the same address. The component then sends `/?!\r\n` and checks the identification line for the SEAB product marker. EABM receives its addressed `/?...!` identification request and the component checks for `EABM` in the response.

The component selects read-only register mode with `ACK 041 CR LF` for both models. The manuals' `B`/`b` is a placeholder for a speed identifier, not a literal letter; `4` denotes 4800 bit/s. On the fixed-speed RS485 interface, the speed identifier does not change the UART speed. After register mode selection, the component waits cooperatively for the meter's `SOH P0 STX (0000) ETX BCC` authorization request and replies with `SOH P1 STX () ETX BCC`. It then reads all requested registers in that session and sends `SOH B0 ETX BCC` to close it.

### First frames with the current configuration

All frames below use 4800 bit/s, 7E1 (one start bit, seven data bits LSB first, even parity, one stop bit), with no initial 300 bit/s phase and no baud switching. RS485 speed must match the value programmed in each meter.

| Meter | First TX (control characters shown in brackets) | Hexadecimal bytes | Expected first RX |
|---|---|---|---|
| SEAB | `/A523.0012230[CR][LF]` | `2F 41 35 32 33 2E 30 30 31 32 32 33 30 0D 0A` | `/g523.0012230[CR][LF]` |
| EABM | `/?825 0001275![CR][LF]` | `2F 3F 38 32 35 20 30 30 30 31 32 37 35 21 0D 0A` | `/POZbEABM-VPvv.vv*[CR][LF]` (b and vv.vv depend on the meter) |

The space in the EABM address is an actual `0x20` byte. Neither initial request has a BCC. SEAB's first frame is 15 characters (31.25 ms on wire), EABM's is 16 (33.33 ms). A bit lasts approximately 208.33 microseconds. After TX the component schedules DIR LOW after `ceil(characters * 10 * 1000 / baud) + 3 ms`: 35 ms for SEAB and 37 ms for EABM, plus component loop scheduling latency. This is a software estimate, not hardware TX-completion feedback.

After SEAB's address reply the next TX is `/?![CR][LF]`, then the meter returns its identification. After identification both models receive `[ACK]041[CR][LF]` (`06 30 34 31 0D 0A`). SEAB register-mode authorization allows at least 1300 ms for the documented 1000 ms delay; initial replies use the configured 500 ms timeout. A timeout retries the same frame once before moving on to the other meter.

Register requests use `SOH R1 STX <register>() ETX BCC`; a response uses `STX <data> ETX BCC`. The BCC is the XOR of bytes after SOH, or after STX when SOH is absent, through ETX inclusive. The implementation checks the frame terminator and BCC before parsing the payload.

## Supported measurements

Every sensor entry is optional. The polling scheduler skips a register when none of its associated sensors is configured. One response updates all configured entities for that register.

| Register request | SEAB response format | EABM response format | Sensors updated |
|---|---|---|---|
| `EPP0()` | `0.8.0.(value)` | `0.8.0.(value)` | Active energy import, kWh, total-increasing |
| `EPM0()` | `1.8.0.(value)` | `1.8.0.(value)` | Active energy export, kWh, total-increasing |
| `EQP0()` | `2.8.0.(value)` | `2.8.0.(value)` | Reactive energy positive, kvarh, total-increasing |
| `EQM0()` | `3.8.0.(value)` | `3.8.0.(value)` | Reactive energy negative, kvarh, total-increasing |
| `F()` | `97.6.0(value)` | `14.7.0(value*Hz)` | Frequency, Hz |
| `P()` | `107(L1;L2;L3;total)` | Per-phase and total OBIS records | Active power by phase and total, W |
| `Q()` | `109(L1;L2;L3;total)` | Per-phase and total OBIS records | Reactive power by phase and total, var |
| `U()` | `97.5.6(L1;L2;L3;phase flags)` | `32.7.0`, `52.7.0`, `72.7.0` | Voltage L1, L2, L3, V |
| `I()` | `97.4.4(L1;L2;L3)` | `31.7.0`, `51.7.0`, `71.7.0` | Current L1, L2, L3, A |
| `TF()` | Not enabled; not assumed supported | `103.3(value)` | EABM neutral tangent |

The four energy identifiers above follow the user-confirmed register notes. Trailing decimal precision is accepted as sent by the meter; units are assigned from the register definition rather than parsed from the response. EABM multi-record power responses are normalized from kW/kvar to W/var. SEAB grouped readings expressed with decimal kW/kvar are converted to W/var; integer-valued grouped readings are treated as W/var as described by the SEAB protocol.

There is no total voltage or total current entity because the documented measurement requests do not provide those totals. Phase and total active/reactive power entities are populated from the same `P()` or `Q()` request.

## Non-blocking scheduling, timeouts, and recovery

UART receive and protocol work runs in the ESPHome component loop. The TX-to-RX transition is scheduled from the configured baud rate and frame length; the loop does not busy-wait for transmission or response. The response timeout defaults to 500 ms. Register-mode startup uses a cooperative deadline long enough for the documented one-second SEAB delay.

Each request is retried at most once. A failed initialization ends that meter's current poll cycle; a failed measurement is logged and the remaining requested registers are attempted. The scheduler then services the other meter. Subsequent cycles retry offline meters. Receive frames are bounded to 512 bytes, and malformed, incomplete, unsupported, or invalid numeric data is not published.

Each meter can use a different poll interval. The default is 10 seconds. The shared bus prevents concurrent sessions. A complete session is ended explicitly, and meter-specific idle termination remains the protocol fallback after communication loss.

## YAML configuration

The project example defines every requested entity for both meters. Remove any unneeded sensor key to disable that entity; the component will also skip its register if no associated entity is configured. The direction GPIO, UART TX/RX pins, baud rate, meter addresses, response timeout, and per-meter polling intervals are configurable.

```yaml
uart:
  - id: pozyton_uart
    baud_rate: 4800
    data_bits: 7
    parity: EVEN
    stop_bits: 1
    tx_pin: GPIO25  # Placeholder
    rx_pin: GPIO26  # Placeholder

pozyton_energy_meters:
  id: pozyton_bus
  uart_id: pozyton_uart
  direction_pin: GPIO27  # Placeholder
  baud_rate: 4800
  response_timeout: 500ms
  meters:
    - meter_name: eabm
      model: EABM
      address: "456 1234567"  # Placeholder factory number
      sensors:
        active_power_total:
          name: "EABM Active Power Total"
        neutral_tangent:
          name: "EABM Neutral Tangent"
      diagnostics:
        connection:
          name: "EABM Communication Connected"
        last_success:
          name: "EABM Last Successful Reading"
        communication_errors:
          name: "EABM Communication Errors"
```

The `neutral_tangent` option is rejected for SEAB because it is not established as supported by the supplied SEAB documentation.

## Diagnostics and logs

Diagnostics are independently optional per meter:

- `connection`: binary sensor; becomes ON after a poll cycle successfully reads at least one configured register.
- `last_success`: text sensor with uptime seconds for the latest successful poll cycle.
- `communication_errors`: cumulative count of retries and failed protocol/measurement stages.

Protocol stages and failures are logged with model, configured meter name/address, stage or register, and reason. Periodic measurement logs are emitted every 10 seconds at INFO level; transaction details are DEBUG and raw frames are VERBOSE. Warnings identify timeouts, NAKs, bad BCC, malformed values, and receive buffer overflow.

`debug_first_response: true` under `pozyton_energy_meters` enables an additional INFO-level dump (enabled in the current YAML). `FIRST TX` shows the request and UART parameters; `FIRST RX` shows the first nonempty received response per meter after each reboot in HEX and readable ASCII. Capture happens before NUL filtering, frame validation, or BCC validation. An incomplete reply is dumped at timeout; overflow dumps are limited to 512 raw bytes. Empty timeouts explicitly show `timeout, no bytes received` and keep capture armed for the first actual reply. After a nonempty dump, further raw dumps for that meter require a restart. Set the option to `false` to disable this diagnostic. Bytes are attributed to the currently addressed meter; this does not distinguish meter replies from local echo or bus noise.

## Troubleshooting

1. Replace all placeholder UART and direction pins with the verified PCB pinout.
2. Replace the sample addresses with the individual serial numbers in the model-specific formats.
3. Match the YAML UART and component baud rates to the meter's fixed RS485 speed; retain 7E1.
4. Check that the MAX3485 direction line is HIGH only during TX and returns LOW before the response window.
5. Enable DEBUG logs for periodic values and VERBOSE logs for frame traces.
6. Check the reported protocol stage before investigating parser values. The component rejects invalid BCC and malformed numeric data rather than publishing it.

## Building on Windows

Use ESPHome 2026.10.2. With the shortened project path, run `esphome compile esp32-master.yaml` directly from the project directory; no PowerShell wrapper is needed.
The older fallback for Windows path length failures is
`./compile-windows.ps1` in PowerShell. This uses short physical directories
`C:\eh-idf`, `C:\eh-data`, and `C:\eh-build` for the toolchain, dependency cache,
and build output. The script restores the process environment afterwards.
Override its `-IdfPath`, `-DataPath`, and `-BuildPath` parameters if needed; use
short physical paths outside another Git repository. ESPHome resolves toolchain
drive mappings and junctions to their original paths, so those do not reliably
avoid Windows path limits. The first build downloads the required dependencies.

Run the schema regression checks with `python -m unittest discover -s tests -v`
using the Python environment that contains ESPHome 2026.10.2.

Verified on 2026-11-17: ESPHome 2026.10.2 compiled the complete configuration
using `compile-windows.ps1`, producing factory and OTA images. All three schema
regression tests passed. Nonfatal warnings remain for legacy Modbus
`command_throttle`/`register_count` options and password-based OTA; these do not
prevent compilation. The IDF component-mirror timeout also did not prevent the
build from completing with the downloaded dependencies.

Physical meter verification remains necessary before deployment. No firmware has
been flashed by this change.
