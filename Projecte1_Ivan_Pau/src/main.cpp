#include <Arduino.h>

int led = 23;

void setup() {
  Serial.begin(115200);
  pinMode(led, OUTPUT);  
  Serial.println("");
  Serial.println("Hola mundo");
}

void loop() {
  digitalWrite(led,HIGH);  //Encender Led
  Serial.println("ON");     //Mostrar ON por Serie
  delay(500);               //Espera 500 ms
  digitalWrite(led,LOW);   //Apagar Led
  Serial.println("OFF");    //Mostrar OFF por Serie
  delay(500);               // Espera 500 ms
  int valor = analogRead(GPIO_NUM_4);
  Serial.println(valor);
}