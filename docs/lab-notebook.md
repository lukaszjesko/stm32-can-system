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


## 2026-10.01
- printf przez UART

breakpoint - punkt zatrzymania, zatrzymanie procesora a danej lini i oglądanie wartości zmiennych 

printf("hello")

printf("hello")                        ← kod
 └ _write()                            ← syscalls.c:80, dzieli tekst na znaki
    └ __io_putchar()                   ← BSP, stm32g4xx_nucleo.c:576, gotowe od CubeMX
       └ HAL_UART_Transmit()           ← HAL wysyła 1 bajt
          └ LPUART1 → pin PA2 (TX)     ← sprzęt STM32
             └ ST-LINK → USB → COMx    ← UM2505, rozdz. 7.6.5, str. 24
                └ PuTTY na laptopie

UART - łącze szeregowe, bity idą jeden po drugim, bez osobnego sygnału zegara 

stdio.h (standard input/output) zawiera deklarację printf: informację dla kompilatora, jak wygląda ta funkcja i co przyjmuje.

uint32_t - u unsigned int 32 bity czyli 4 bajty wybieramy 32 bity o cortex-m4 procesor 32 bitowy i taki rozmiar przetwarza najszybciej 

hello %lu\r\n - tekst formatujący 
%lu - long unsigned 
\r - carriage return - cofa kursor na początek lini 
\n przenosi kursor linię niżej 


ctr- b - build 

1. preprocesor wkleja pliki z  #include 
2. komilator zamienia .c na ARM .o kod maszynowy 
3. linker skleja w jeden plik 