# stm32-can-system

USB–CAN adapter and J1939 power node on STM32G431, controlled from Linux over SocketCAN.

```
┌────────────┐  USB  ┌─────────────────┐  CAN 250 kbit/s  ┌──────────────────┐
│ Linux PC   │◄─────►│ USB–CAN adapter │◄────────────────►│ J1939 power node │──► 3 × load
│ SocketCAN  │       │ STM32G431       │      J1939       │ STM32G431        │    ≤ 2 A each
└────────────┘       └─────────────────┘                  └──────────────────┘
```

## Target specification

| | USB–CAN adapter | J1939 power node |
|---|---|---|
| MCU | STM32G431CBT6, Cortex-M4, 170 MHz | STM32G431 |
| Supply | USB 5 V → 3.3 V LDO, ESD protection | 9–32 V → 3.3 V buck converter (own design); fuse, reverse polarity, TVS |
| CAN | 2.0B, up to 1 Mbit/s, 120 Ω termination on a jumper | J1939, 250 kbit/s, 29-bit ID, address claim |
| I/O | USB 2.0 Full Speed on USB-C | 3 × low-side MOSFET, current sensing, overcurrent shutdown |
| Software | appears in Linux as `can0` | FreeRTOS, watchdog, status frame every 100 ms |
| PCB | 2 layers, ~40 × 20 mm | 4 layers |

## Status

| Step | Done when | State |
|---|---|---|
| [01-blinky](firmware/01-blinky) | LED blinks, `printf` over the ST-LINK virtual COM port, breakpoint hit | done (2026-10-04) |
| [02-can-loopback](firmware/02-can-loopback) | FDCAN1 in internal loopback: frame 0x123 sent and received at 250 kbit/s | in progress |
| 03-can-two-nodes | Nucleo ↔ Arduino Nano + MCP2515, frame decoded with a logic analyzer | planned |
| USB–CAN adapter | `can0` up in Linux, `candump` shows frames from the bus | planned |
| J1939 power node | buck ripple and efficiency measured, load switched from Linux | planned |

## Development board

NUCLEO-G431RB (STM32G431RBT6, on-board STLINK-V3E).

| Signal | Pin | Note |
|---|---|---|
| LD2, green LED | PA5 | |
| B1, user button | PC13 | |
| Virtual COM port | PA2 / PA3 (LPUART1) | 115200 8N1 through ST-LINK |
| FDCAN1 RX / TX | PB8 / PB9 | PB8 is also BOOT0: option bytes must be set before a transceiver is connected |

## Build

1. STM32CubeIDE 2.x → **File → STM32 Project Create/Import → STM32CubeMX/STM32CubeIDE Project** → pick a folder in `firmware/`.
2. Build (`Ctrl+B`) and run on the NUCLEO-G431RB.
3. Open a serial terminal on the ST-LINK COM port, 115200 8N1.

Peripheral configuration lives in each project's `.ioc` file (STM32CubeMX 6.x).

## Repository

```
firmware/   one STM32CubeMX + STM32CubeIDE project per step
hardware/   KiCad projects (adapter, node)
tools/      DBC file, Python scripts
docs/       lab notebook (in Polish), measurements
```

Lab notebook: [docs/lab-notebook.md](docs/lab-notebook.md)