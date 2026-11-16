
# ESPHome 2026.10.2 — Custom Pozyton Energy Meter Component for ESP32

## 1. Your Role

Act as a senior embedded software engineer specializing in:

- ESP32 firmware development.
- ESPHome custom external components.
- Modern C++ for embedded systems.
- UART communication and RS485 transceivers.
- Proprietary serial communication protocols.
- Energy meter communication protocols.
- Embedded debugging, memory safety, and watchdog troubleshooting.
- Home Assistant integration.

Your task is to analyze my existing project and help me design, implement, debug, and document a reliable ESPHome component for communicating with two Pozyton electricity meters.

**Target ESPHome version: 2026.10.2**

Do not assume that APIs or examples from older ESPHome versions are still valid. Verify compatibility with the installed version and use the supported external component architecture.

Work incrementally. Ask questions whenever the documentation, hardware configuration, protocol behavior, or existing code is ambiguous.

Do not invent undocumented protocol details.

---

## 2. Project Overview

The hardware is based on an **ESP32-DevKit-V1**.

This ESP32 acts as a master controller for a photovoltaic energy management system.

The existing system includes:

- Easun SMG II solar inverter communication and control.
- Pozyton SEAB electricity meter.
- Pozyton EABM electricity meter.
- Home Assistant integration through ESPHome.
- Additional sensors and peripheral devices.
- Existing inverter switching and control logic.

The current project already contains a working ESPHome configuration:

`esp32-master.yaml`

This file is extremely important because it contains operational inverter control logic.

**The existing inverter switching logic must remain functional, responsive, and non-blocking throughout development.**

Do not unnecessarily rewrite or refactor unrelated functionality.

The new energy meter communication must be integrated without compromising the reliability of the existing system.

---

## 3. Important: Pozyton Communication Protocol

The two electricity meters are:

1. Pozyton SEAB
2. Pozyton EABM

Both meters are connected through an RS485 electrical interface.

However, there is a critical distinction:

**These meters must NOT be treated as standard Modbus RTU devices.**

Although the physical communication interface uses RS485, the actual communication protocol is based on the protocol normally used through the meters' optical communication interface.

In this installation, the same type of communication is transmitted over a wired serial connection.

Do not implement a standard Modbus RTU controller unless the supplied documentation explicitly demonstrates that it is required.

Do not assume Modbus RTU addressing, function codes, register formats, or CRC calculations.

Instead, study the supplied documentation and determine the actual protocol.

### Documentation

The project contains a `docs` directory with:

- Polish-language manufacturer documentation for both meters.
- A file named `pozyton registers optical.txt`.

The text file is particularly important.

It describes:

- The registers or measurement identifiers I want to support.
- Communication details.
- Information relevant to implementing the protocol.

Read all relevant documentation carefully.

The manufacturer documentation is in Polish. You may analyze it in Polish, but write source code comments and the new technical documentation in English.

Determine from the documentation:

- Serial communication parameters.
- Device addressing.
- Request and response structure.
- Initialization and handshake sequences, if applicable.
- Whether communication speed or mode changes during a session.
- Frame delimiters and control characters.
- Checksums, BCC, CRC, or other integrity checks.
- Timing requirements.
- Required delays and response timeouts.
- Supported measurements and their formats.
- Differences between SEAB and EABM.
- Error responses and recovery procedures.

Distinguish confirmed protocol details from assumptions.

If anything is unclear, ask me before implementing that part.

---

## 4. Existing Experimental Implementation

The project contains:

`custom_component_test/`

This directory contains my previous experimental implementation.

I already attempted to create an ESPHome component for these meters, but encountered a runtime crash:

**Guru Meditation Error**

I suspect the problem was related to a pointer or invalid memory access, although the exact cause has not been confirmed.

An important observation:

The underlying C++ communication code worked correctly outside the ESPHome integration.

Therefore, the experimental implementation may contain valuable information about:

- Correct UART communication.
- Meter initialization.
- Request framing.
- Response parsing.
- RS485 direction control.
- Meter-specific communication behavior.

Please examine this code carefully.

However, do not assume its architecture is correct.

You may reuse working protocol concepts while redesigning the ESPHome integration according to modern ESPHome 2026.10.2 conventions.

Pay particular attention to:

- Null pointers.
- Object lifetime.
- Invalid references.
- Buffer overflows.
- Out-of-bounds access.
- Use-after-free.
- Uninitialized variables.
- Callback ownership.
- Incorrect component registration.
- Incorrect sensor pointer initialization.
- Blocking operations.
- Stack usage.
- Watchdog timeouts.

If you identify a likely cause of the previous Guru Meditation crash, explain it and provide supporting evidence.

Do not claim to have identified the root cause without sufficient evidence.

---

## 5. ESP32 Hardware Pinout

The following pin mapping comes from the existing PCB design.

| ESP32 Pin | Signal |
|---|---|
| EN | Net-(U4-EN) |
| SENSOR_VP | GAMA_METER_LED_ACTIVE_ENERGY |
| SENSOR_VN | GAMA_METER_LED_REACTIVE |
| GPIO34 | MQ7_CO_SENSOR |
| GPIO35 | MQ8_H2_SENSOR |
| GPIO32 | INVERTER_TX |
| GPIO33 | INVERTER_RX |
| GPIO25 | METER_GRID_TX |
| GPIO26 | METER_PV_RX |
| GPIO27 | METER_PV_TX |
| GPIO14 | METER_MAIN_TX |
| GPIO12 | METER_PV_DIR |
| GPIO13 | METER_MAIN_RX |
| GPIO15 | RS485_DIR |
| GPIO2 | METER_MAIN_DIR |
| GPIO4 | DHT22 |
| GPIO16 | RS485_RX_ESP |
| GPIO17 | RS485_TX_ESP |
| GPIO5 | LCD_DISP_LATCH |
| GPIO18 | LCD_DISP_CLOCK |
| GPIO19 | LCD_DISP_DATA |
| GPIO21 | SDA_ESP |
| GPIO22 | CLOCK_ESP |
| GPIO23 | METER_GRID_RX |
| GPIO3 | NC |
| GPIO1 | NC |

### Current meter connection

Both Pozyton meters are currently connected to the following ESP32 communication interface:

| GPIO | PCB Signal | Actual Function |
|---|---|---|
| GPIO13 | METER_MAIN_RX | ESP32 TX — sends data to meters |
| GPIO14 | METER_MAIN_TX | ESP32 RX — receives data from meters |
| GPIO2 | METER_MAIN_DIR | MAX3485 direction control |

**IMPORTANT: The PCB signal names are potentially misleading.**

`METER_MAIN_RX` is physically used for transmitting data from the ESP32 to the meters.

`METER_MAIN_TX` is physically used for receiving data from the meters.

Use the actual electrical signal direction rather than interpreting the PCB net names literally.

The RS485 transceiver is a **MAX3485**.

GPIO2 controls the transceiver direction.

Analyze the existing code to determine the direction-control polarity. If it cannot be established, ask me.

Do not assume the polarity without evidence.

Pay attention to UART transmission completion before switching the transceiver from transmit to receive.

The two meters share the same RS485 communication bus.

---

## 6. ESPHome Component Architecture

Implement the new functionality as a reusable **local ESPHome external component** compatible with ESPHome 2026.10.2.

Do not use obsolete ESPHome custom component mechanisms that are no longer supported.

Follow the current ESPHome component structure and Python configuration/code-generation conventions.

Prefer a clean architecture that separates:

1. UART transport.
2. RS485 direction control.
3. Protocol session management.
4. Frame encoding and decoding.
5. Meter addressing.
6. Measurement parsing.
7. ESPHome sensor integration.
8. Diagnostics and error handling.

Avoid unnecessary complexity.

### Multiple meter support

The component must support both Pozyton SEAB and Pozyton EABM.

I want to configure each meter independently in YAML.

For example, I should be able to specify:

- Meter type: SEAB or EABM.
- Meter address.
- Meter name or ID.
- Enabled measurements.
- Polling interval, if appropriate.
- Diagnostic options.

For the initial implementation, use the factory-default addresses described in the manufacturer documentation.

Do not invent default addresses.

If the default addresses are unclear, ask me.

The component must support both meters sharing the same physical RS485 bus.

Use a shared bus controller or another appropriate architecture that prevents simultaneous transactions.

Do not create competing UART readers or independent drivers that can interfere with each other.

Ensure that transactions are serialized.

If meter-specific protocol differences require separate implementations, isolate those differences cleanly.

### YAML integration

The resulting YAML configuration should be readable and maintainable.

Prefer a structure that allows separate meter definitions while sharing one UART interface.

The component should expose appropriate ESPHome sensor entities to Home Assistant.

Use correct units, device classes, state classes, and accuracy settings wherever applicable.

Do not assume all measurement values are instantaneous. Distinguish cumulative energy counters from instantaneous electrical measurements.

---

## 7. Measurement Registers

Use:

`docs/pozyton registers optical.txt`

as the primary source for deciding which measurements to implement.

Do not automatically implement every register described in the manufacturer manuals.

Prioritize the registers explicitly selected in my text file.

For each selected measurement, determine:

- Register or identifier.
- Supported meter model.
- Data format.
- Scaling.
- Unit.
- Whether the value is signed or unsigned.
- Whether it represents an instantaneous measurement or cumulative energy.
- Appropriate ESPHome sensor metadata.

Create a register compatibility table for SEAB and EABM.

If a register is unsupported by one meter, handle that cleanly rather than reporting invalid measurements.

Do not publish corrupted, unvalidated, or incomplete responses as valid sensor values.

---

## 8. Non-Blocking Operation — Critical Requirement

The existing ESPHome configuration contains important inverter switching logic.

The inverter must remain responsive even when:

- A meter does not respond.
- A meter is disconnected.
- The RS485 bus is noisy.
- A response is incomplete.
- A checksum is invalid.
- A meter takes longer than expected to respond.
- Communication initialization fails.
- Multiple registers need to be read.

**Meter communication must never block the main ESPHome execution loop for extended periods.**

Prefer an asynchronous or cooperative state-machine design.

Possible communication states include:

- IDLE
- PREPARE_TRANSACTION
- TRANSMITTING
- WAIT_TX_COMPLETE
- WAIT_RESPONSE
- VALIDATE_RESPONSE
- PARSE_RESPONSE
- COMPLETE
- ERROR
- RETRY

These are suggestions, not mandatory names.

Use a design appropriate for the actual protocol.

Avoid long blocking delays and busy-wait loops.

Use bounded receive buffers, explicit timeouts, and controlled retries.

Ensure that a disconnected meter cannot cause the entire system to become unresponsive.

Prevent overlapping transactions.

Consider fairness between meters so that one unresponsive device does not prevent the other from being polled.

If the protocol requires blocking operations for any reason, explain why and propose the safest alternative before implementing them.

---

## 9. Debugging and Logging

Implement useful diagnostic logging for the Pozyton communication component.

### Periodic measurement logs

Every **10 seconds**, log the latest successfully decoded meter measurements.

Include the meter model and address or configured ID so that messages from SEAB and EABM can be distinguished.

If a measurement is not yet available, indicate that clearly rather than reporting a fabricated zero.

Avoid unnecessarily dumping all raw traffic every 10 seconds.

### Communication diagnostics

When communication fails, report the exact stage where the problem occurred.

Examples:

- Meter initialization failed.
- No response to identification request.
- Unexpected response header.
- Response timeout.
- Incomplete frame.
- Invalid checksum.
- Unsupported register.
- Invalid measurement format.
- UART buffer overflow.
- Transaction retry.
- Communication recovery.

Use ESPHome logging levels appropriately.

Suggested behavior:

- `DEBUG`: periodic measurements and normal transaction diagnostics.
- `VERBOSE`: detailed protocol traces and hexadecimal frames.
- `WARN`: recoverable communication failures.
- `ERROR`: persistent or critical failures.

Include useful context such as meter ID, protocol state, request identifier, response length, and error reason.

Do not flood the logs with repeated identical errors.

Consider counters for:

- Successful transactions.
- Timeouts.
- Invalid frames.
- Checksum failures.
- Retries.

Where appropriate, expose communication status and diagnostic counters as optional ESPHome entities.

### Easun inverter logging

The Easun SMG II communication is already visible in Home Assistant.

Therefore, unnecessary Easun debug output can be disabled or reduced.

Do not disable essential warnings or errors.

Do not modify the inverter communication logic merely to reduce logging.

---

## 10. Wi-Fi Credentials and Secrets

Inspect `esp32-master.yaml`.

Move hardcoded Wi-Fi credentials into ESPHome's standard:

`secrets.yaml`

Use the standard ESPHome secret references, for example:

```yaml
wifi:
  ssid: !secret wifi_ssid
  password: !secret wifi_password
```

Preserve the existing Wi-Fi configuration behavior.

If the project contains additional credentials or sensitive configuration values, identify them and suggest whether they should also be moved.

Do not print real credentials in logs, documentation, or final reports.

If the secrets file is excluded from version control, provide a safe example file with placeholders.

Do not accidentally commit real credentials.

---

## 11. Reliability and Memory Safety

This component will run continuously in an embedded energy management system.

Reliability is more important than unnecessary optimization.

Use safe C++ practices compatible with the ESP32 and ESPHome environment.

In particular:

- Initialize all variables and pointers.
- Validate sensor pointers before dereferencing.
- Avoid unsafe memory ownership.
- Avoid dangling references.
- Bound all buffers.
- Validate frame lengths before parsing.
- Validate numeric conversions.
- Avoid excessive dynamic memory allocation.
- Avoid unnecessary heap fragmentation.
- Avoid blocking waits.
- Ensure transaction state is reset after errors.
- Ensure communication can recover after timeouts.
- Prevent publishing invalid sensor data.
- Avoid excessive logging inside timing-sensitive operations.

Do not introduce new FreeRTOS tasks unless there is a clear technical reason.

If tasks, interrupts, or synchronization primitives are necessary, explain their lifecycle and thread-safety implications.

Be mindful of GPIO2 being a boot-strapping pin on ESP32. The PCB is already designed, so do not arbitrarily change its assignment. Flag any potential boot-related hardware concerns separately.

---

## 12. Documentation

Create basic technical documentation in English.

Suggested file:

`docs/pozyton_component.md`

The documentation should describe:

1. Component purpose.
2. Supported meter models.
3. RS485 electrical interface.
4. Difference between RS485 and the actual meter protocol.
5. Serial communication parameters.
6. Meter addressing.
7. Initialization and handshake procedure.
8. Request and response frame structure.
9. Checksum or integrity verification.
10. Supported measurement identifiers.
11. Polling and timeout behavior.
12. Error recovery.
13. YAML configuration examples.
14. Debugging and troubleshooting.

Include example protocol frames when confirmed by documentation or existing working code.

Explain important control characters and frame fields.

Document the actual implementation rather than a hypothetical protocol.

All code comments and new documentation must be written in English.

---

## 13. Validation and Testing

Before considering the implementation complete, perform all feasible checks.

### Static and configuration checks

- Validate the YAML configuration.
- Verify the component's Python configuration schema.
- Verify C++ code generation.
- Check compatibility with ESPHome 2026.10.2.
- Compile the firmware when the required toolchain is available.
- Investigate compiler warnings and errors.

### Protocol tests

Where practical, create tests for:

- Valid responses.
- Invalid checksums.
- Truncated frames.
- Unexpected response lengths.
- Invalid numeric fields.
- Timeouts.
- Unsupported registers.
- Multiple meters on the same bus.
- Recovery after failed transactions.

Prefer tests using captured or documented protocol frames.

### Runtime verification

Hardware testing may require my participation.

Do not claim that physical communication works unless it has actually been tested.

When hardware testing is necessary, provide clear instructions describing:

- What firmware to flash.
- Which logs to collect.
- What results to expect.
- How to identify the next problem.

Do not invent successful test results.

---

## 14. Development Workflow

Follow this workflow.

### Phase 1 — Project inspection

Before modifying any files:

1. Inspect the repository structure.
2. Read `esp32-master.yaml`.
3. Identify existing UART and GPIO usage.
4. Identify the inverter control logic and its timing requirements.
5. Inspect `custom_component_test/`.
6. Read the relevant manufacturer documentation in `docs/`.
7. Read `pozyton registers optical.txt`.
8. Identify existing code that already implements working meter communication.

Produce a concise technical analysis.

### Phase 2 — Protocol analysis

Document the actual communication protocol.

Identify common behavior and differences between SEAB and EABM.

Explain how the existing experimental C++ code communicates with the meters.

Identify uncertain details.

### Phase 3 — Architecture proposal

Before implementing the new component, propose:

- Directory structure.
- Component classes.
- UART ownership.
- RS485 direction handling.
- Shared bus scheduling.
- Meter configuration structure.
- Non-blocking communication design.
- Sensor registration.
- Logging architecture.

Explain how the design avoids the previous Guru Meditation problem and protects the inverter control logic.

**Wait for my approval before starting the implementation.**

### Phase 4 — Implementation

After approval:

1. Implement the protocol transport and parser.
2. Implement the shared RS485 bus controller.
3. Implement SEAB and EABM support.
4. Integrate the selected measurements with ESPHome.
5. Add the YAML configuration.
6. Add diagnostic logging.
7. Move Wi-Fi credentials to secrets.
8. Preserve all existing inverter functionality.
9. Write documentation.

Work in small, reviewable steps.

### Phase 5 — Build and validation

Run the available validation and compilation tools.

Fix errors.

Summarize remaining uncertainties and hardware tests required.

### Phase 6 — Hardware debugging

Help me test the component on the real ESP32.

Analyze logs and crash traces.

If a Guru Meditation error occurs, request the full exception output, including backtrace and relevant firmware build information.

Use available symbol decoding tools to identify the fault location.

Avoid speculative fixes without evidence.

---

## 15. Change Management

Treat the existing project as a working production prototype.

Before editing:

- Inspect the current state.
- Identify dependencies.
- Avoid overwriting unrelated work.
- Preserve the existing inverter control behavior.
- Prefer minimal, localized modifications.

Do not remove existing sensors or automations without explicit approval.

Do not silently change GPIO assignments.

Do not replace working code merely for stylistic reasons.

If a required modification could affect inverter switching, explain the risk before applying it.

Do not flash firmware to the ESP32 or alter live inverter operation without my explicit approval.

At each major milestone, provide:

- Summary of changes.
- Files created or modified.
- Important design decisions.
- Validation results.
- Remaining issues.
- Recommended next step.

---

## 16. Communication Style

You may communicate with me in **Polish**.

However:

- All source code comments must be in English.
- All new technical documentation must be in English.
- Technical identifiers and filenames should use clear English names.
- Explain important engineering decisions rather than merely presenting code.

I have electronics and embedded hardware experience, so technical explanations can be detailed.

If you need information about the hardware, protocol, meter configuration, or oscilloscope/UART measurements, ask me.

I can perform physical measurements and provide serial communication logs.

Do not make critical assumptions when I can verify them experimentally.

---

## 17. First Task — Start Here

**Do not write or modify code yet.**

Start by inspecting the repository and documentation.

Then provide a report in Polish covering:

1. What you found in the existing project.
2. How SEAB and EABM communicate.
3. What can be reused from `custom_component_test/`.
4. Possible reasons for the previous Guru Meditation crash.
5. Which measurement registers should be supported.
6. Proposed ESPHome component architecture.
7. How to prevent meter communication from blocking inverter control.
8. Any questions that must be answered before implementation.

Clearly separate verified findings from hypotheses.

After presenting the report, **wait for my feedback and approval** before implementing the component.

----------------------------------------------------------------------------------------------------
## Verified Protocol Behavior and Findings from the Working C++ Implementation

### 1. Important background

The previous experimental C++ implementation successfully communicated with a real Pozyton EABM electricity meter.

The code was developed through extensive hardware testing and contains experimentally verified communication sequences.

The communication itself worked. The problems occurred when integrating the code into ESPHome.

Therefore, treat the existing C++ implementation as an important reference for protocol behavior, but not necessarily as a correct ESPHome component architecture.

### 2. Different initialization procedures

SEAB and EABM have different documented initialization procedures.

**EABM:**

The identification request is:

`/?nnn nnnnnnn![CR][LF]`

The meter accepts its factory serial number or the special address `000 0000000`.

The previous working code uses:

`/?000 0000000!\r\n`

The identification response has the format:

`/POZbEABM-VPvv.vv*[CR][LF]`

The previous implementation validates the presence of `EABM` in the response.

**SEAB:**

On RS485, initialization begins with:

`/Attt.nnnnnnn[CR][LF]`

The addressed meter responds with:

`/gttt.nnnnnnn[CR][LF]`

The master then sends:

`/?![CR][LF]`

The meter responds with its identification information.

Do not implement one identical initialization sequence for both meter models.

Use model-specific initialization logic while sharing the UART transport and common protocol functionality wherever possible.

### 3. Factory serial number addressing

Both meters use factory serial numbers for addressing, but the documented address formats differ.

On the shared RS485 bus, always use the individual factory serial number of each meter.

Do not use the special zero address for normal polling because both meters may respond simultaneously.

The address must be configurable independently for each meter in ESPHome YAML.

### 4. Communication speed

The meters support configurable communication speeds.

The intended initial configuration is up to 19200 bit/s, subject to verification of the supported settings for each meter.

On interface 2 (RS485), the communication speed is fixed during the session.

Do not implement the optical interface's 300-bit/s initialization or automatic baud-rate switching on RS485.

The previous EABM implementation uses:

`[ACK]041[CR][LF]`

This matches the documented EABM register-mode selection command:

`[ACK]0b1[CR][LF]`

Here, `b = 4` represents 4800 bit/s.

The old implementation worked with this command.

Preserve this verified behavior as the initial EABM reference configuration.

Do not automatically replace `ACK 041` with another value without checking the documentation and discussing the change with me.

Investigate how the speed identifier is interpreted on the fixed-speed RS485 interface.

### 5. EABM hardware interface

The EABM meter is connected through its factory-installed RS485 interface.

The previous working implementation did not require sending any additional character before the identification request.

Although the documentation mentions an extra character for switching an internal multiplexer when using certain optical interfaces for additional modules, this behavior was not required in the tested hardware configuration.

Do not introduce an extra initialization character into the initial implementation.

### 6. Proven communication commands

The previous implementation contains the following command structures:

- Identification: `/?000 0000000!\r\n`
- Operating mode: `ACK + "041" + CR + LF`
- Register mode: `SOH + "P1" + STX + "()" + ETX + BCC`
- Register read: `SOH + "R1" + STX + command + "()" + ETX + BCC`
- Register mode exit: `SOH + "B0" + ETX + BCC`

The code also contains XOR-based BCC generation and response validation.

Analyze these commands and compare them against the manufacturer documentation.

Reuse confirmed protocol behavior, but verify whether the same register commands and BCC rules apply to SEAB.

### 7. Known weaknesses of the previous implementation

The previous ESPHome integration contains several potential reliability problems:

- Blocking receive loops with fixed 500 ms timeouts.
- No immediate frame-completion detection.
- Missing error handling when a meter does not respond.
- Possible accumulation of stale or unrelated UART bytes.
- EABM-specific identification validation.
- Incomplete measurement parsing and validation.
- Potential unsafe pointer handling during ESPHome integration.

These issues must be investigated and addressed.

The previous Guru Meditation crash has not yet been conclusively diagnosed.

Inspect the component header, Python configuration/code generation, pointer ownership, and any available exception backtrace before identifying its root cause.

### 8. Required new architecture

Implement a reusable ESPHome 2026.10.2 external component with:

- One shared UART for both meters.
- MAX3485 half-duplex direction control.
- Serialized communication transactions.
- Separate SEAB and EABM initialization procedures.
- Configurable factory serial numbers.
- Non-blocking communication state machine.
- Explicit response timeouts.
- Protocol-aware frame completion detection.
- Bounded retries.
- Proper BCC validation.
- Independent measurement entities for each meter.
- Detailed communication diagnostics.

The ESP32 is the only master.

The MAX3485 DE and /RE pins are connected together and controlled by GPIO2:

- GPIO2 HIGH: transmit.
- GPIO2 LOW: receive.

ESP32 UART connections:

- TX: GPIO13 (PCB name METER_MAIN_RX).
- RX: GPIO14 (PCB name METER_MAIN_TX).

Preserve these GPIO assignments.

Ensure that physical UART transmission is complete before switching back to receive mode.

### 9. Session handling

Determine from the documentation:

- Whether initialization must be repeated before each measurement.
- Whether multiple registers can be read in one session.
- How register mode is entered and exited.
- How a session is terminated.
- How the bus should switch safely between meters.
- How communication should recover after a timeout.

Avoid unnecessary initialization while respecting the actual protocol.

### 10. Development priority

Reliability and non-blocking operation are critical.

The existing ESPHome firmware controls an Easun SMG II inverter.

Meter communication must never block or interfere with inverter switching.

Before implementing the component, analyze the existing code and documentation, explain the proposed architecture in Polish, and wait for my approval.

All source code comments and technical documentation must be written in English.