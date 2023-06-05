#include <Arduino>
#include <HardwareSerial.h>

HardwareSerial Serial2(2);//UART2

void setup(){
  //Conexions de serial
  Serial.begin(115200);
  Serial2.begin(SERIAL_8N1,16,17); //RX en 16 y TX en 17
  Serial.setRx(RX2);
  Serial.setTx(TX2);
  Serial.write(1);
j
}

void loop() {
  //Lectura de les dades de UART0 i enviem a UART2
  while(Serial.available()){
    Serial.write(Serial.read());
  }

  //Loh mijmoh de pa'alla pa'arriba pero al reveh
  while(Serial2.available()){
    Serial.write(Serial2.read()+1);
  }
}