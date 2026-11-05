// Arduino Nano + MCP2515 CAN module (8 MHz crystal)
// Library: autowp-mcp2515
// Wiring: SCK=D13, SO=D12, SI=D11, CS=D10, INT=D2

#include <SPI.h>
#include <mcp2515.h>

MCP2515 mcp2515(10);      // CS on pin D10

struct can_frame txFrame; // frame we send
struct can_frame rxFrame; // frame we receive

void setup() {
  Serial.begin(115200);

  pinMode(5, OUTPUT);



  mcp2515.reset();
  mcp2515.setBitrate(CAN_250KBPS, MCP_8MHZ);
  mcp2515.setNormalMode();  

  txFrame.can_id  = 0x200;      // standard 11-bit ID
  txFrame.can_dlc = 8;        // 8 data bytes
  txFrame.data[0] = 0x11;
  txFrame.data[1] = 0x22;
  txFrame.data[2] = 0x33;
  txFrame.data[3] = 0x44;
  txFrame.data[4] = 0x55;
  txFrame.data[5] = 0x66;
  txFrame.data[6] = 0x77;
  txFrame.data[7] = 0x88;

  Serial.println("nano-can start");
}

void loop() {
  MCP2515::ERROR status = mcp2515.readMessage(&rxFrame);
  if (status == MCP2515::ERROR_OK){
    Serial.print(rxFrame.can_id,HEX); Serial.print(" ");
    for (int i = 0; i < rxFrame.can_dlc; i++){
      Serial.print(rxFrame.data[i],HEX); Serial.print(" ");
    }
    Serial.println();
    if (rxFrame.can_id == 0x300){
      digitalWrite(5, rxFrame.data[0]);
    }
  }
}
