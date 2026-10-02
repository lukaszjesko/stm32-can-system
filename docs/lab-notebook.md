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


## 2026-10-01
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

## 2026-10-02
projekt 02-can-loopback 

w cube mx nowy projket
Connectivity → FDCAN1  - odpowiada za komunikację CAN, domyślnie wszystkie wyłączone żeby oszczędzać prąd, activate daje procesorowi znać że używamy do komunikacji can

internal loopback - gadanie do lustra - procesor nie ma wypuszczać sygnału na zewnątrz do kabli tylko zawracać do środka 
FDCAN1_TX i FDCAN1_RX na zielono tx wysyła dane, rx odbiera, 
(PA11 , PA12) - używane do komunikacji USB w STM32 


CUBEMX prędkość 250kbit/s 
fd can 170Mhz - prędkość zegara CAN w MHz - z niego ustawia się długość jednego bity 

prescaler 17 dzieli zegar 
170 MHZ / 17  = 10 Mhz 
jeden takt to kwant czasu tq i trwa 100 ns

przy 250 kbit/s bit trwa 4 us czyli 40 kwantów

clock divider - devide by 1 - caly surowy syngnał z procesora 170 Mhz 
nominal prescaler - 17  
dlaczego? -  zegar 170 MHz trzeba zmniejszyć do 250 000 bitów na sekundę. 170 MHz / 17 = 10 MHz. Z okrągłych 10 MHz łatwo wyliczyć resztę: na jeden bit przypada dokładnie 40 taktów. 

każdy węzeł na magistal CAN musi mieć ustawioną tę samą prędkość 
prędkość CAN ustawia się dzieląc zegar kontrolera, wszystkie węzły musza mieć tą samą predkość i podobny czas próbkowania 
Punkt próbkowania to moment w trakcie bitu, w którym kontroler sprawdza, czy linia jest w stanie 0 czy 1.

ramka CAN ---------------
- ID - mówi co jest w ramce - prędkość silnika, nie jest adresem urządzenia
im mniejsze ID tym wyższy priorytet na magistrali

can ma 11 bitowe ID , J1939 29-bitowe 

- DLC liczba bajtów dancych od 0 do 8 

- dane to 0 - 8 bajtów 

C:

- FDCAN_TxHeaderTypeDef 

to struktura, czyli jakby formularz z polami. Wypełniasz go, a HAL na tej podstawie buduje ramkę. 
do środka dostajemy się przez kropkę 

- uint8_t txData[8] to tablica: 8 bajtów jeden po drugim. txData[0] to pierwszy bajt.
- 0x przed liczbą oznacza zapis szesnastkowy (hex). W CAN ID i dane zapisuje się prawie zawsze w hex.

FDCAN_TxHeaderTypeDef txHeader; to formularz ramki do wysłania,
FDCAN_RxHeaderTypeDef rxHeader; to formularz do którego HAL wpisze dane ramki 

Tx = Transmit, rx receive 

HAL - hardware abstraction layer, biblioteka gotowych funkcji od ST, zamiast samemu pisać wartości rejestrów wywołuję funkcję, 

BSP - > HAL -> rejestry 
wpisywanie wartości do formularza np. - txHeader.Identifier = 0x123;

co oznacza: 
txHeader.Identifier = 0x123; - nadaje identyfikator o wartości 123 w szesnastkowym, określa priorytet w przypadku kolizji na kablu 
txHeader.IdType = FDCAN_STANDARD_ID; - ustawia długość id na standard - 11 

txHeader.TxFrameType = FDCAN_DATA_FRAME; - definiuje jako ramkę z danymi 
txHeader.DataLength = FDCAN_DLC_BYTES_8; - określa dlc data length code na 8 bajtó ( maksymalny rozmiar danych dla klasycznego standardu CAN)

ctr shift f wyrównuje 
