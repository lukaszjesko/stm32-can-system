# Lista części – adapter USB-CAN

Bierne (R, C, LED): 0805 — większe od 0603, łatwiejsze do ręcznego lutowania.

## Układy scalone i półprzewodniki

| Ozn. | Funkcja | Część | Obudowa | LCSC | Stan magazynu | Cena | Uwagi |
|---|---|---|---|---|---|---|---|
| U1 | MCU | STM32G431CBT6 | LQFP-48 | | | | |
| U2 | Stabilizator 5 V → 3,3 V | AP2112K-3.3TRG1 (Diodes) | SOT-23-5 | C51118 | 12 735 szt. (14.10) | ~0,17 USD (min. 5 szt.) | 600 mA |
| U3 | ESD na USB (D+, D−) | USBLC6-2SC6 (ST) | SOT-23-6 | C7519 | ok. 30 000 szt. | ~0,07 USD | |
| U4 | Transceiver CAN 3,3 V | SN65HVD230DR (TI) | SOIC-8 | C12084 | ok. 14 000 szt.; TME: 0 | ~0,72 USD | |
| D4 | ESD na CAN | NUP2105L (DOWO) | SOT-23 |C284104 |53,370 | 0.58 USD za 10szt | pin 1 = CAN_H, 2 = CAN_L, 3 = GND |
| Q1 | Klucz zasilania U4 (P-MOSFET) | AO3401A | SOT-23 |C15127 |146,725 |0.48$ za 5 szt |pin 1 = g, pin 2 = S pin 3 = D  | 
| Q2 | Sterowanie bramką Q1 (N-MOSFET) | 2N7002 | SOT-23 |C916396 |1,302,600 | 0.56$ za 50szt| 1=G, 2  = S, 3 =D |
| Y1 | Kwarc 24 MHz | X322524MOB4SI (YXC) | 3225 (4 pady) | C70590 | ok. 90 000 szt. | ~0,05 USD | CL = 12 pF → C13/C14 15 pF |
| D1 | LED zasilania | czerwona | 0805 | | | | |
| D2 | LED (PA15) | niebieska | 0805 | | | | R2 dobrać po Vf z noty |
| D3 | LED (PB11) | zielona | 0805 | | | | R3 dobrać po Vf z noty |

## Złącza i przycisk

| Ozn. | Funkcja | Część | Obudowa | LCSC | Stan magazynu | Cena | Uwagi |
|---|---|---|---|---|---|---|---|
| J1 | SWD | goldpin 1×5 | 2,54 mm, THT | | | | |
| J2 | USB-C (USB 2.0, 16 pinów) |Korean Hroparts Elec TYPE-C-31-M-12  | SMD |C165948 |302.635 |0.87$ za 5 szt  | wybrać część, do której jest footprint w KiCad |
| J3 | Złącze CAN (CAN_H, CAN_L, GND) | KF350-3.5-3P (Kefa)| 3,5 mm, THT |C474893 |1,595 |0.78$ za 5 szt | |
| J4 | Zworka terminacji | goldpin 1×2 + zworka | 2,54 mm, THT | | | | |
| SW1 | Przycisk BOOT0 |TS-1187A-B-A-B | SMD |C318884 |923,740 |0.42$ za 20 szt |A-b, c- d połączone  |

## Rezystory (0805)

| Ozn. | Wartość | LCSC | Stan magazynu | Uwagi |
|---|---|---|---|---|
| R1–R3, R9 | 1k | | | |
| R4, R5 | 5.1k | | | CC1/CC2 |
| R6 | 120 Ω | | | terminacja |
| R7, R10, R11 | 10k | | | |
| R8 | 100k | | | |

## Kondensatory (0805)

| Ozn. | Wartość | LCSC | Stan magazynu | Uwagi |
|---|---|---|---|---|
| C13, C14 | 15 pF | | | dielektryk C0G (NP0) |
| C3 | 10 nF | | | |
| C4–C9, C15 | 100 nF | | | |
| C1, C2, C11, C12 | 1 µF | | | |
| C10 | 4.7 µF | | | |

BOOT0: option bytes nSWBOOT0 = 0, nBOOT0 = 1 (fabrycznie). Wejście do bootloadera USB: SW1 trzymany przy resecie → PB8 = 1.
