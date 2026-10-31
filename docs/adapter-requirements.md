# USB–CAN adapter — requirements

## 1. Purpose

The adapter connects a Linux computer to a CAN bus, so frames on the bus can be monitored and sent from the computer.

## 2. Functional requirements

| ID | Requirement |
|---|---|
| REQ-1 | The adapter shall support CAN 2.0B (11- and 29-bit IDs) up to 1 Mbit/s. |
| REQ-2 | The adapter shall connect over USB-C, USB 2.0 Full Speed (12 Mbit/s). |
| REQ-3 | On Linux, the adapter shall be visible as a SocketCAN interface (`can0`). |
| REQ-4 | A 120 Ω bus termination shall be enabled with jumper J4. |
| REQ-5 | The adapter shall have 3 LEDs: red = power, blue (PA15) and green (PB11) = CAN bus status and traffic. |

## 3. Electrical

- Power: 5 V from USB VBUS → LDO AP2112K-3.3 → 3.3 V for the MCU and the CAN transceiver.
- ESD protection: USBLC6-2SC6 on D+/D−, NUP2105L on CAN_H/CAN_L.
- Clock: 24 MHz crystal (HSE), because CAN needs a precise clock (the internal HSI oscillator has about 1% deviation).

## 4. Programming and debug

- SWD: header J1, 1×5, 2.54 mm (1 +3V3, 2 SWDIO, 3 SWCLK, 4 NRST, 5 GND).
- USB DFU bootloader: hold SW1 (BOOT0) while plugging in the USB cable.

## 5. Mechanical

- Board size 50 × 25 mm, 2 layers.
- Passive components in 0805 packages, hand soldered.

## 6. Out of scope (v2)

- Galvanic isolation of the CAN bus.
- CAN FD.
- Firmware update over CAN.

## 7. Verification

| Check | Method | Expected result |
|---|---|---|
| Power | Multimeter on +3V3 | 3.3 V |
| REQ-4 | Multimeter between CAN_H and CAN_L, board unpowered, J4 installed | 120 Ω |
| REQ-2 | `lsusb` with SW1 held at plug-in | device in DFU mode |
| REQ-1, REQ-3 | `candump can0` with the Nano node on the bus | frame 0x200 from the Nano |
| REQ-5 | Visual | red LED on with USB, blue/green react to CAN traffic |
