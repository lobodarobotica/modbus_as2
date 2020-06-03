/////////////////////////////////////
/*
  Autor: Thellyson
  Data: 04/03/2020
*/
/////////////////////////////////////

#define TX_ENABLE_PIN 4

////////////////////////////////////////////////////////////////////////////////
//DECLARACOES DE BIBLIOTECAS
////////////////////////////////////////////////////////////////////////////////
#include <ModbusMaster232.h>    //ModbusMaster RTU pins   D7(13),D8(15)   RX,TX

/////////////////////////////////////////////////////////////////////////////////
//MODBUS
/////////////////////////////////////////////////////////////////////////////////

//Declaracoes do modbus:
ModbusMaster232 node(1, TX_ENABLE_PIN);      //Buscando no slave id=1
#define BAUD_RATE_MODBUS 9600                //BaudRate


void setup() {
  Serial.begin(9600);

  //Setup inicial do modbus:
  //////////////////////////
  node.begin(BAUD_RATE_MODBUS);
}

void loop() {
  //////////////////////////////////////////////////////////////////
  //MODBUS
  /////////////////////////////////////////////////////////////////

  //  //Registro [1]
  //  node.readHoldingRegisters(1, 1);
  //  Serial.println("REG[1]");
  //  delay(120);
  //  Serial.println(node.getResponseBuffer(0));
  //  node.clearResponseBuffer();

  //Registro [1]
  node.readInputRegisters(1, 1);
  Serial.println("REG[1]");
  delay(120);
  Serial.println(node.getResponseBuffer(0));
  delay(120);
  node.clearResponseBuffer();
  Serial.flush();
//  Serial2.flush();
  delay(1000);
}
