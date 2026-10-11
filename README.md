# stm32-can-system

I'm a second-year microelectronics student at Poznań University of Technology.
In this project I'm learning the CAN bus and designing my first SMD board.

The goal is a small CAN system with three parts:

1. A USB-CAN adapter: my own board with an STM32G431. A Linux laptop sees it as `can0`.
2. A J1939 node: a board with three power outputs, current measurement and its own buck converter.
3. A Python script on Linux that reads the node's status and switches its outputs through the adapter.

Right now I'm working on the adapter.

## What works

- NUCLEO-G431RB bring-up: LED, `printf` over UART, breakpoints in the debugger
  ([firmware/01-blinky](firmware/01-blinky))
- CAN in loopback mode at 250 kbit/s: the STM32 sends frame `0x123` with 8 data bytes
  and receives it back inside the chip ([firmware/02-can-loopback](firmware/02-can-loopback))

## In progress

- Two CAN nodes on a real bus: the Nucleo with an SN65HVD230 transceiver and an
  Arduino Nano with an MCP2515. I'll check the frames with a logic analyzer.
- The adapter schematic in KiCad ([hardware/usb-can-adapter](hardware/usb-can-adapter)).
  The STM32 with its power pins and decoupling capacitors is done. I use the open-source
  CANable 2.0 as a reference and want to order the PCB in early November.

## What I learned so far

- STM32CubeIDE 2.x no longer includes CubeMX. You set up the chip in CubeMX and import
  the project into the IDE.
- The CAN controller in the STM32G4 has only 3 slots in its transmit queue. Sending in
  a loop without a delay fills it right away.
- On this chip the CAN RX pin (PB8) is also BOOT0. A transceiver keeps RX high, so after
  a reset the chip may start its bootloader instead of my program. The adapter has to
  deal with that.
- KiCad 10 keeps a local history folder with its own git repository inside. I added it
  to `.gitignore`.

## Next steps

- [ ] Two nodes on a real bus, frames decoded in PulseView
- [ ] Adapter: finish the schematic and layout, order the PCB
- [ ] Adapter: solder it and get `can0` working on Linux
- [ ] J1939 node: buck converter design, 4-layer PCB, measurements
- [ ] Python script with `python-can` and `cantools`

## Building the firmware

Open a folder from `firmware/` in STM32CubeIDE (File → STM32 Project Create/Import),
build it and run it on a NUCLEO-G431RB. The serial output goes to the ST-LINK COM port
at 115200 8N1.

I write short notes after each session in [docs/lab-notebook.md](docs/lab-notebook.md)
(in Polish).
