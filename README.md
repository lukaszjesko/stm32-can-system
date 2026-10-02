# stm32-can-system

A CAN bus system I'm designing and building from scratch: a **USB–CAN adapter** and a **J1939 power node**, both based on the STM32G431, controlled from a Linux PC.

```mermaid
flowchart LR
    PC["Linux PC<br/>SocketCAN, Python"] <-->|USB| ADP["USB–CAN adapter<br/>STM32G431"]
    ADP <-->|"CAN bus, J1939, 250 kbit/s"| NODE["J1939 power node<br/>9–32 V, 3 outputs"]
    NODE --> LOAD["Loads<br/>lamp, motor"]
```

| Part | What it does | Scope |
|---|---|---|
| **USB–CAN adapter** | Shows up in Linux as `can0`, so standard tools can use the bus | First SMD board: 2-layer PCB, USB 2.0 Full Speed, CAN 2.0B up to 1 Mbit/s, switchable 120 Ω termination |
| **J1939 power node** | Takes commands over CAN, switches loads, reports its status 10 times per second | Own 9–32 V → 3.3 V buck converter (design, ripple and efficiency measurements), 3 low-side MOSFET outputs up to 2 A with current sensing and overcurrent shutdown, 4-layer PCB, FreeRTOS |
| **Linux tools** | Send commands and decode status messages | `can-utils`, DBC file, Python (`python-can`, `cantools`) |

## Progress

- [x] Toolchain: STM32CubeMX, STM32CubeIDE, NUCLEO-G431RB
- [ ] First firmware: LED blink and UART `printf` – [`firmware/01-blinky`](firmware/01-blinky) *(built, hardware test next)*
- [ ] CAN controller in internal loopback mode, 250 kbit/s – [`firmware/02-can-loopback`](firmware/02-can-loopback) *(in progress)*
- [ ] Two-node CAN bus: Nucleo ↔ Arduino Nano with MCP2515
- [ ] USB–CAN adapter: schematic → PCB → bring-up
- [ ] J1939 power node: converter calculations → PCB → measurements
- [ ] Control from Linux: DBC file and Python script

Every step and measurement goes into the [lab notebook](docs/lab-notebook.md) (in Polish).
