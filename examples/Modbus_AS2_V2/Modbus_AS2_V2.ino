#include <Arduino.h>
#include <esp32ModbusRTU.h>
#include <algorithm>  // for std::reverse

esp32ModbusRTU modbus(&Serial2, 4);  // use Serial1 and pin 16 as RTS

void setup() {
  Serial.begin(115200);  // Serial output
  Serial2.begin(9600);

  modbus.onData([](uint8_t serverAddress, esp32Modbus::FunctionCode fc, uint16_t address, uint8_t* data, size_t length) {
    Serial.printf("id 0x%02x fc 0x%02x len %u: 0x", serverAddress, fc, length);
    for (size_t i = 0; i < length; ++i) {
      Serial.printf("%02x", data[i]);
    }
    //std::reverse(data, data + 4);  // fix endianness
    int Int32 = 0;
    Int32 = (Int32 << 8) + data[0];
    Int32 = (Int32 << 8) + data[1];
    
    Serial.printf("\n");
    Serial.println(Int32);
  });
  modbus.onError([](esp32Modbus::Error error) {
    Serial.printf("error: 0x%02x\n\n", static_cast<uint8_t>(error));
  });
  modbus.begin();

}

void loop() {
  static uint32_t lastMillis = 0;
  if (millis() - lastMillis > 3000) {
    lastMillis = millis();
    Serial.print("sending Modbus request...\n");
    modbus.readInputRegisters(0x01, 1, 1);
  }
}
