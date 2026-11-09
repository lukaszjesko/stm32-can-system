# J1939 node — requirements

## 1. Purpose

The node is an output module on a CAN bus (J1939). A Linux laptop sends commands through
the USB-CAN adapter to switch the outputs on and off. The node sends back its status:
the state and the current of each output. Test loads: a 24 V bulb and a 24 V DC motor.

## 2. Functional requirements

| ID | Requirement |
|---|---|
| REQ-1 | The node shall use CAN 2.0B with 29-bit IDs (J1939) at 250 kbit/s. |
| REQ-2 | The node shall claim its J1939 source address after power-up (address claim). |
| REQ-3 | The node shall switch each of its 3 outputs on or off on a command frame from the bus. |
| REQ-4 | The node shall send a status frame every 100 ms (10 Hz) with the state and current of each output. |
| REQ-5 | The node shall have 3 low-side outputs (MOSFET between the load and ground), each up to 2 A. |
| REQ-6 | The node shall measure the current of each output (shunt resistor + STM32G4 internal op-amp + ADC). |
| REQ-7 | The node shall switch off an output when its current exceeds 2.5 A. |
| REQ-8 | The node shall recover from bus-off automatically, without a reset. |
| REQ-9 | All outputs shall be off after power-up and after a watchdog reset. |

## 3. Electrical

- Power input: 9–32 V DC (12 V and 24 V vehicle systems; 32 V is a safety margin).
- Input protection: fuse, reverse polarity protection, TVS diode.
- Buck converter 9–32 V → 3.3 V, my own design: inductor and capacitors calculated by hand,
  output ripple and efficiency measured. Output current: to be determined.
- MCU: STM32G4 (3 internal op-amps for current measurement). Exact part: to be determined.
- CAN transceiver 3.3 V, 120 Ω termination enabled with a jumper (same as the adapter).
- Outputs: 3 × low-side MOSFET, each with a flyback diode for inductive loads (motor).

## 4. Firmware

- FreeRTOS: separate tasks for CAN receive, current measurement and status.
- Independent watchdog: resets the MCU if the firmware hangs.
- Bus-off recovery (REQ-8).
- DBC file that describes the node's frames, used by the Python tools on Linux.

## 5. Programming and debug

- SWD: same header as the adapter (1×5, 2.54 mm: 1 +3V3, 2 SWDIO, 3 SWCLK, 4 NRST, 5 GND),
  so the same ST-LINK fits both boards.

## 6. Mechanical

- 4 layers: Signal / GND / PWR / Signal.
- Board size: to be determined.
- Screw terminals for power, CAN and the 3 outputs (thicker wires, up to 2 A per output).

## 7. Out of scope (v2)

- Galvanic isolation of the CAN bus.
- High-side outputs.
- CAN FD.
- Firmware update over CAN.

## 8. Verification

| Check | Method | Expected result |
|---|---|---|
| Power | Multimeter on 3.3 V rail, input 12 V and 24 V | 3.3 V |
| Buck converter | Oscilloscope on 3.3 V rail; input/output voltage and current | ripple and efficiency measured |
| REQ-1, REQ-2 | candump can0 after power-up | address claim frame with a 29-bit ID |
| REQ-3 | cansend command frame with the 24 V bulb on output 1 | bulb switches on and off |
| REQ-4 | candump -t d can0 | status frame every 100 ms |
| REQ-5, REQ-6 | Multimeter in series with the load vs. current in the status frame | values match |
| REQ-7 | Load above 2.5 A (power resistors) | output switches off |
| REQ-8 | Short CAN_H to CAN_L for a moment, then remove the short | node sends status again without a reset |
| REQ-9 | Power-up; force a watchdog reset in firmware | all outputs off |
