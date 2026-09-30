moje notatki

## 2026-09-30

trzy rzeczy: 
- adapter usb-can - wpinam w laptopa, może podłuchiwać magistralę i sam nią nadawać 
- węzeł j1939 - własny sterownik, zasialam 24V, dostaje rozkazy np włącz wyjście 1, mierzy prąd i przy zwarciu się wyłącza się wyjście, wezeł działa dalej i głasza błąd po can, co 0,1s melduje swój stan 
- komputer z linuksem(maszyna wirtualna)

HSI 16Mhz - wewnętrzny oscylator RC, generator zegara zbudowany z rezystora i kondensatora  
PLL - 170 MHz -  pll mnoży częstotliwość zegara 170 MHz to max 
HSI - 48 osobny zegar 48 Mhz dla USB 

do can między dwoma ukłądami HSE 24MHZ - kwarc X3 na nucleo 

Kod ma trzy warstwy, jedna pod drugą:

BSP_LED_Toggle(LED_GREEN)                   ← BSP: "która dioda na płytce"
 └ HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5)    ← HAL: "który pin"
    └ GPIOA->BSRR = ...                     ← rejestry: zapis do sprzętu

BSP → HAL → rejestry; toggle przez ODR i BSRR, bo BSRR zmienia tylko wskazane bity jednym zapisem


## 2026-09-31