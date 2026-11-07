// Arduino Nano + MCP2515 CAN module (8 MHz crystal)
// Library: autowp-mcp2515
// Wiring: SCK=D13, SO=D12, SI=D11, CS=D10, INT=D2

#include <SPI.h>      // SPI bus (MISO, MOSI, SCK, CS) to talk to the MCP2515
#include <mcp2515.h>  // MCP2515 CAN controller library

MCP2515 mcp2515(10);      // MCP2515 object, CS on pin D10

struct can_frame rxFrame; // frame we receive

void setup() {
  Serial.begin(115200);   // UART to Serial Monitor, 115200 bit/s

  pinMode(5, OUTPUT);     // D5 drives the LED
  mcp2515.reset();
  mcp2515.setBitrate(CAN_250KBPS, MCP_8MHZ); // CAN bus 250 kbit/s, 8 MHz crystal on the module
  mcp2515.setNormalMode();  // send and receive (other modes: listen-only, loopback)
  
  Serial.println("nano-can start");
}

void loop() {
  MCP2515::ERROR status = mcp2515.readMessage(&rxFrame); // take one frame from the MCP2515 RX buffer into rxFrame
  if (status == MCP2515::ERROR_OK){ // a frame was received (otherwise ERROR_NOMSG)
    Serial.print(rxFrame.can_id,HEX); Serial.print(" "); // print ID in hex
    for (int i = 0; i < rxFrame.can_dlc; i++){ // loop over data bytes (DLC = 1 for 0x300)
      Serial.print(rxFrame.data[i],HEX); Serial.print(" "); // print each byte in hex
    }
    Serial.println();
    if (rxFrame.can_id == 0x300){ // button frame from Nucleo
      digitalWrite(5, rxFrame.data[0]); // data[0] = 1 -> LED on, 0 -> LED off
    }
  }
}
