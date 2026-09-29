# stm32-can-system

A CAN bus system in three parts, built step by step:

1. **USB-CAN adapter** – my first SMD board, STM32G431, seen by Linux as `can0` (SocketCAN)
2. **J1939 power node** – 9–32 V input, my own buck converter, three MOSFET outputs with current sensing
3. **Linux tools** – `candump`, a DBC file and a Python script that controls the node

## Status

| Part | State |
|---|---|
| Development setup on NUCLEO-G431RB | in progress |
| USB-CAN adapter | planned |
| J1939 power node | planned |
| Linux tools | planned |

## Repository layout

```
docs/       lab notebook, notes, calculations
firmware/   STM32 projects (STM32CubeMX + STM32CubeIDE)
hardware/   KiCad projects
tools/      Linux scripts and the DBC file
```