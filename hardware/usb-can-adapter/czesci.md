# Lista części – adapter USB-CAN

## Do wybrania

| Funkcja | Część | Obudowa | Nr TME/LCSC | Stan magazynu | Cena | Nota katalogowa | Uwagi |
|---|---|---|---|---|---|---|---|
| Transceiver CAN 3,3 V | SN65HVD230DR (TI) | SOIC-8 | LCSC C12084 | ok. 14 000 szt. (LCSC); TME: 0 | ~0,72 USD | | pin 8 (Rs) ↔ PA0 = standby jak w canable2-fw — sprawdzić w nocie |
| Stabilizator 5 V → 3,3 V | AP2112K-3.3TRG1 (Diodes) | SOT-23-5 | LCSC C51118 | 12 735 szt. (LCSC, 14.10) | ~0,17 USD (min. 5 szt.) | | 600 mA; wyjście min. 1 µF; wejście — sprawdzić w nocie |
| ESD na USB | USBLC6-2SC6 (ST) | SOT-23-6 | LCSC C7519 | ok. 30 000 szt. (LCSC) | ~0,07 USD | | |
| Kwarc 24 MHz | X322524MOB4SI (YXC) | 3225 (4 pady) | LCSC C70590 | ok. 90 000 szt. (LCSC) | ~0,05 USD | | CL = 12 pF → policzyć 2 kondensatory |
| Rezystor terminacji | 120 Ω | 0805 | | | | | |
| Zworka terminacji | goldpin 1×2 + zworka | 2,54 mm | | | | | |
| Złącze CAN | listwa śrubowa 3-pin (CANH, CANL, GND) | raster 3,5 mm, THT | do znalezienia | | | | wybrana 15.10 (rozmiar płytki, łatwe testy z modułami) |
| ESD na CAN | PESD2CAN (Nexperia) | SOT-23 | do znalezienia | | | | |

BOOT0: option bytes nSWBOOT0 = 0, nBOOT0 = 1, ustawiane przez SWD przy uruchamianiu, BOR 2,8 V. PB8 zostaje tylko jako CAN_RX, bez przycisku BOOT0.

## Już na schemacie

| Funkcja | Część | Obudowa | Nr TME/LCSC | Uwagi |
|---|---|---|---|---|
| MCU | STM32G431CBT6 | LQFP-48 | | |
| Złącze USB | USB-C 16P | | | |
| Rezystory CC | 5.1k | 0805 | | |
| LEDy | czerwona, zielona, niebieska | 0805 | | R1–R3 1k: dla blue/green dobrać po Vf z noty |
| Złącze SWD | 1×5 | | | |
