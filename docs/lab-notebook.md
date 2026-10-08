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
## 2026-10-03
putty pokazuje tekst przychodzący przez com 

nucleo wysyła znaki putty, wyświetla 
Speed:  115200. To prędkość w bitach na sekundę 

Breakpoint zatrzymuje procesor na wybranej linijce.
Wtedy przez swd (te same przewody co od wgrywania projeku) można podejrzeć pjakie wartości mają zmiennne w pamięci 

## 2026-10-04
BSP_LED_Toggle(LED_GREEN) - zmienia stan LED 
printf("hello %lu\r\n", licznik); - %lu podstawia licznik, r - carriage return kursor na początek ekranu, n line feed nowa linia 

cubemx generuje inicjalizację (zegary piny, UART) ja piszę logikę pętli głownej 
UART - kabel transmisyjny - 
tx transmit - procesor nadaje    Universal Asynchronous Receiver-Transmitter - asynchroniczny bo brak osobnego kabla z zegarem

rx receive 
ćwiczeni dioda zapala się 5 razy w ciągu sekudnyd 
HAL_DELAY() przyjmuje w ms 
1000ms / 5 = 200ms ale że BSP_LED_Toggle(LED_GREEN) gdy dioda świeci to gasi, a jak zgaszona to zapala 
200/2 = 100ms 

BSP_LED_Toggle(LED_GREEN);
HAL_Delay(100);

BSP_PB_GetState(BUTTON_USER)
Bada stan pinu przycisku i zwraca wynik jako liczbę całkowitą: 0 albo 1

02-can-loopback
cubemx skonfigurował FDCAN1 ale nie włączył, żeby włączyć - HAL_FDCAN_Start(&hfdcan1);

w while 
HAL_FDCAN_AddMessageToTxFifoQ(&hfdcan1, &txHeder, txData) - wkłada do koljeki nadawczej TxFifo i kontroler sam wysyła

 & (przed hfdcan1 i txHeader) oznacza adres zmiennej, czyli informację, gdzie leży w pamięci
 Funkcja nie dostaje kopii całego „formularza”, tylko wskazanie, gdzie go znaleźć.

  hfdcan1 to uchwyt (handle), struktura opisująca kontroler FDCAN1, którą CubeMX zadeklarował w linii 45

  Pętla while (1) obraca się miliony razy na sekundę. Kolejka nadawcza CAN (tzw. Tx FIFO) ma miejsce tylko na 3 ramki naraz
  Bez opóźnienia procesor zapycha kolejkę w ułamku milisekundy i natychmiast zaczyna sypać błędem TX error

## 2026-10-05
  w stm32 jest wbudowany konroler CAN, bity normalnie wychodzą punem tx do transceivera a stamtąd do innych urządzeń, na razie nie ma transceivera (układu który zamnienia a je na napięca na kablu CAN) i stamtąd do innych urządzeń 


while (1)

  {


	  status = HAL_FDCAN_AddMessageToTxFifoQ(&hfdcan1, &txHeader, txData);
	  if (status != HAL_OK){
		  printf("TX error\r\n");
	  }else{
		  printf("TX ok\r\n");        HAL_OK - ramka trafiła do kolejki nadawczej 
	  }
	  HAL_Delay(1000);

    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }

## 2026-10-06
txData - TxFIFO - kontroler FDCAN (osobny układ wewnątrze stm3, odbera sam ramki i odkłada do Rx FIFO0 procesor w tym czasie czeka HAL_Delay) - loopback - filtr  - rx FIFO0 - rxHeader + rxData

HAL_FDCAN_GetRxFifoFillLevel(&hfdcan1, FDCAN_RX_FIFO0) - podaje poziom zapełnienia od &hfdcan1 - stm32g432 ma tylko Fdcan1 ale większe mają jeszcze kilka, dlatego każd  funkcja dostaje handle 
FDCAN_RX_FIFo0 - mówi o którą kolejkę pytam 
są FIFO0 i FIFO1,

status = HAL_FDCAN_GetRxMessage(&hfdcan1, FDCAN_RX_FIFO0, &rxHeader, rxData);

getrxmessage - hfdcan1 - któy kontroler fcdan_rx_fifo0 która kolejka, rxheader - adres formularza do kótrego zapisze fo którego HAL zpaisze, rxData - adres tablicy 
status = HAL_FDCAN_GetRxMessage


printf("RX id=0x%lX data=%02X...%02X\r\n", rxHeader.Identifier, rxData[0], rxData[7]);
 rxHeader.Identifier: kropka oznacza „wejdź do pola struktury” To ID odebranej ramki, które HAL wpisał
   %lX wypisuje liczbę w hex, l = long, bo ID jest typu uint32_t
   %02X wypisuje bajt w hex, zawsze 2 cyfry (0 = dopełnij zerem). Bez tego 0x05 wyświetliłoby się jako 5.

    %02 mówi tylko „2 cyfry, dopełnij zerem”. Brakuje litery, która mówi, jak wypisać liczbę (X = hex)


     ID ustala też priorytet: gdy dwa urządzenia nadają naraz, wygrywa mniejsze ID. Ten mechanizm nazywa się arbitraż

Putty wyświetla identyfikator id ramki w systemie szesnastkowym oraz pierwszą i ostatnią wartość z ramki, sprawdza też czy przenoszenie ramki się udało - jeśli się udało zapala się led 

## 2026-10-07

txHeader.Identifier = 0x123;
can id - identyfikator ramki, co to za wiadomość i ustala priorytet, mniejsze ID ma dostęp do magistrali, standardowe ID 11 bitów, 

https://github.com/makerbase-mks/CANable-MKS/blob/main/Hardware/MKS%20CANable%20V2.0/MKS%20CANable%20V2.0_001%20schematic.pdf
analiza projektu
c4 połączone z vss zasialnie z zasialniem 3.3v i kondensatorem, w tym samym połączeniu CAN RX z rezystorem 
c7 podobnie zasilanie tak jak c8 do vdd, zasilanie podone na vdd vdda vret+ w połączeniu z 3 kondensatorami 100nF, 
kondensatory odsprzęglające, 

boot0 - stan niski, mikrokontroler uruchamia się w trybie norlamnym, zaczyna wykonywać kod z pamięci flash,
boot1 - stan system memory, uruchamia się program st bootlander, który pozwala wgrać nowy soft to procesora bez st lina np magistralę can 

r6 rezystor ściągający pull down trzyma boot 0 w stanie 0 


LQFP - Low-profile Quad Flat Package   7x7mm wymiar plastikowego korpusu bez nóżek 
P0.5mm to pitch, czyli rozstaw nóżek: 0,5 mm od środka do środka

## 2026-10-08
DS12589, rysunek 16
po jednym 100 nF przy każdym pinie VDD, + 1 wspólny kondenastor dla wszystkich, 

vbat zasila backup circurity w procesorze - zegar czasu rzeczywistego, kwartc rejestry zapasowe 

nrst - pin pg10 - stan 0 zatrzymyuje procesor i zerouje 