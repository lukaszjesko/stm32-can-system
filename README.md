# STM32 CAN System

A project where I learn CAN bus, SMD PCB design and power electronics.
It has three parts:

1. **USB-CAN adapter**: my first SMD board, based on the STM32G431. On Linux
   it shows up as `can0` (SocketCAN).
2. **J1939 node**: a board with three low-side power outputs, current sensing
   and its own buck converter. J1939 is the CAN protocol used in trucks and
   buses.
3. **Linux tools**: a DBC file and a Python script that read the node status
   and switch its outputs.

## Status

Work in progress, started in September 2026.

- [x] NUCLEO-G431RB bring-up: LED, UART, debugger ([`01-blinky`](firmware/01-blinky))
- [x] CAN in internal loopback mode on the Nucleo, 250 kbit/s ([`02-can-loopback`](firmware/02-can-loopback))
- [ ] Two CAN nodes at 250 kbit/s: Nucleo + Arduino Nano with MCP2515
- [ ] Adapter: schematic and PCB ([`hardware/usb-can-adapter`](hardware/usb-can-adapter), schematic in progress)
- [ ] Adapter: assembly, bring-up, `can0` on Linux
- [ ] Node: buck converter calculations
- [ ] Node: schematic and 4-layer PCB
- [ ] Node firmware on the Nucleo: FreeRTOS, J1939, DBC file, Python script
- [ ] Node: assembly and measurements

## 1. USB-CAN adapter

| | |
|---|---|
| MCU | STM32G431CBT6 (LQFP48) |
| USB | USB-C, Full Speed, ESD protection |
| CAN | CAN 2.0B up to 1 Mbit/s, 3.3 V transceiver |
| Termination | 120 Ω, enabled with a jumper |
| Clock | crystal (CAN needs an accurate clock) |
| Programming | SWD header and USB bootloader (BOOT0 button) |
| LEDs | power, RX, TX |
| PCB | 2 layers, about 40 x 20 mm, hand soldered |

I use the open-source CANable 2.0 (same MCU) as a reference. The first
bring-up uses the existing CANable firmware, so if something does not work I
know the problem is in my hardware. After that I switch to my own firmware.

## 2. J1939 node

| | |
|---|---|
| Supply | 9-32 V (12 V and 24 V systems) |
| Input protection | fuse, reverse polarity protection, TVS diode |
| Buck converter | 3.3 V, my own design from the datasheet: inductor, capacitors, layout of the switching loop |
| Outputs | 3 low-side MOSFETs, up to 2 A each, freewheeling diode for inductive loads |
| Current sensing | shunt on each output, STM32G4 internal op-amps, ADC |
| Protection | overcurrent shutdown in firmware |
| CAN | J1939 at 250 kbit/s, 29-bit IDs, address claim, commands and status at 10 Hz |
| Firmware | FreeRTOS, watchdog, CAN bus error handling |
| PCB | 4 layers: signal / GND / power / signal |

I will measure the ripple and efficiency of the buck converter at different
load currents.

## 3. Linux side

- Ubuntu in VirtualBox, SocketCAN, can-utils (`candump`, `cansend`)
- DBC file describing my J1939 messages
- Python with `python-can` and `cantools`

## Development board

Firmware is developed on a NUCLEO-G431RB (STM32G431RBT6, on-board STLINK-V3E).

| Signal | Pin | Note |
|---|---|---|
| LD2, green LED | PA5 | |
| B1, user button | PC13 | |
| Virtual COM port | PA2 / PA3 (LPUART1) | 115200 8N1 through the ST-LINK |
| FDCAN1 RX / TX | PB8 / PB9 | PB8 is also BOOT0, option bytes must be set before a transceiver is connected |

## Build

1. In STM32CubeIDE 2.x: **File → STM32 Project Create/Import →
   STM32CubeMX/STM32CubeIDE Project**, pick a folder in `firmware/`.
2. Build (`Ctrl+B`) and run it on the NUCLEO-G431RB.
3. Open a serial terminal on the ST-LINK COM port, 115200 8N1.

Pins and clocks are set in each project's `.ioc` file (STM32CubeMX 6.x).

## Not in this version

Ideas for v2: galvanic isolation of the CAN bus, high-side outputs, CAN FD,
firmware update over CAN.

## Tools

STM32CubeMX, STM32CubeIDE, KiCad. Short notes after each work session are in
the [lab notebook](docs/lab-notebook.md) (in Polish).
