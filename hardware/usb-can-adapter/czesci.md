# Lista części – adapter USB-CAN

Bierne (R, C, LED): 0805 — większe od 0603, łatwiejsze do ręcznego lutowania.

## Układy scalone i półprzewodniki

| Ozn. | Funkcja | Część | Obudowa | LCSC | Stan magazynu | Cena | Uwagi |
|---|---|---|---|---|---|---|---|
| U1 | MCU | STM32G431CBT6 | LQFP-48 |C529355 |1,152 |$ 4.82 za 1 szt | |
| U2 | Stabilizator 5 V → 3,3 V | AP2112K-3.3TRG1 (Diodes) | SOT-23-5 | C51118 | 12 735 szt. (14.10) | ~0,17 USD (min. 5 szt.) | 600 mA |
| U3 | ESD na USB (D+, D−) | USBLC6-2SC6 (ST) | SOT-23-6 | C7519 | ok. 30 000 szt. | ~0,07 USD | |
| U4 | Transceiver CAN 3,3 V | SN65HVD230DR (TI) | SOIC-8 | C12084 | ok. 14 000 szt.; TME: 0 | ~0,72 USD | |
| D4 | ESD na CAN | NUP2105L (DOWO) | SOT-23 |C284104 |53,370 | 0.58 USD za 10szt | pin 1 = CAN_H, 2 = CAN_L, 3 = GND |
| Q1 | Klucz zasilania U4 (P-MOSFET) | AO3401A | SOT-23 |C15127 |146,725 |0.48$ za 5 szt |pin 1 = g, pin 2 = S pin 3 = D  | 
| Q2 | Sterowanie bramką Q1 (N-MOSFET) | 2N7002 | SOT-23 |C916396 |1,302,600 | 0.56$ za 50szt| 1=G, 2  = S, 3 =D |
| Y1 | Kwarc 24 MHz | X322524MOB4SI (YXC) | 3225 (4 pady) | C70590 | ok. 90 000 szt. | ~0,05 USD | CL = 12 pF → C13/C14 15 pF |
| D1 | LED zasilania | czerwona | 0805 |C19171391 |72,800 |$ 0.78 za 100szt  | |
| D2 | LED (PA15) | niebieska | 0805 |C19273154 |53,700 |$ 0.86 za 100szt  | R2 dobrać po Vf z noty |
| D3 | LED (PB11) | zielona | 0805 |C919444|7,525 |$ 0.7 za 30 szt  | R3 dobrać po Vf z noty |

## Złącza i przycisk

| Ozn. | Funkcja | Część | Obudowa | LCSC | Stan magazynu | Cena | Uwagi |
|---|---|---|---|---|---|---|---|
| J1 | SWD | goldpin 1×5 | 2,54 mm, THT | — | mam (listwa łamana) | — | |
| J2 | USB-C (USB 2.0, 16 pinów) |Korean Hroparts Elec TYPE-C-31-M-12  | SMD |C165948 |302.635 |0.87$ za 5 szt  | wybrać część, do której jest footprint w KiCad |
| J3 | Złącze CAN (CAN_H, CAN_L, GND) | KF350-3.5-3P (Kefa)| 3,5 mm, THT |C474893 |1,595 |0.78$ za 5 szt | |
| J4 | Zworka terminacji | goldpin 1×2 (mam, listwa łamana) + zworka HCTL HC-JP254-1-65-CL-B-G0 | 2,54 mm, THT | C5380290 (zworka) |30,750 | | zworka zamknięta (capped), czarna |
| SW1 | Przycisk BOOT0 |TS-1187A-B-A-B | SMD |C318884 |923,740 |0.42$ za 20 szt |A-b, c- d połączone  |

## Rezystory (0805)

| Ozn. | Wartość | LCSC | Stan magazynu | Uwagi |
|---|---|---|---|---|
| R1, R9 | 1k |C95781 |3,053,900 | R1: LED czerwona, ok. 1,3 mA |
| R2 | 330 Ω | C17630 | sprawdzić | LED niebieska, ok. 1,5 mA; UNI-ROYAL 0805W8F3300T5E |
| R3 | 470 Ω | C17710 | sprawdzić | LED zielona, ok. 2,3 mA; UNI-ROYAL 0805W8F4700T5E |
| R4, R5 | 5.1k |C27834 |659,200 | CC1/CC2 |
| R6 | 120 Ω | C17437 | 594,600| terminacja; UNI-ROYAL 0805W8F1200T5E |
| R7, R10, R11 | 10k |C17414 |41,816,700 | |
| R8 | 100k |C149504 |1,479,400 | |

## Kondensatory (0805)

| Ozn. | Wartość | LCSC | Stan magazynu | Uwagi |
|---|---|---|---|---|
| C13, C14 | 15 pF | C49326668| 2,100 | C0G, 50 V; AIDE 0805C0G150J500NT |
| C3 | 10 nF | C53084522| 39,250| X7R, 50 V; TORCH CC0805X7R50V103MN |
| C4–C9, C15 | 100 nF | C49678 | 8,861,540| X7R, 50 V; YAGEO CC0805KRX7R9BB104 |
| C1, C2, C11, C12 | 1 µF | C53084451| 89,850| X7R, 50 V; TORCH CC0805X7R50V105KN |
| C10 | 4.7 µF | C1779 |  387,440| X5R, 25 V; Samsung CL21A475KAQNNNE |

BOOT0: option bytes nSWBOOT0 = 0, nBOOT0 = 1 (fabrycznie). Wejście do bootloadera USB: SW1 trzymany przy resecie → PB8 = 1.
