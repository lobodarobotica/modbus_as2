#include <ModbusMaster232.h>

#define TX_ENABLE_PIN 4

long tempo_anterior = 0;

ModbusMaster232 node(1, TX_ENABLE_PIN);  //Slave ID 01

void setup() {
  Serial.begin(115200);
  node.begin();
}

void loop() {
  if (millis() - tempo_anterior > 5000) {
    tempo_anterior = millis();
    read_modbus();
  }
}

void read_modbus() {
  node.readInputRegisters(1, 1);
  Serial.println(node.getResponseBuffer(0));
}
