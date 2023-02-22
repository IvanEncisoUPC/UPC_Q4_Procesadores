/*
  Titulo: Practica 1
  Autores: Ivan Enciso & Pau Codina
*/



// Este es un posible inicio

//Libreras
#include <Serial.h> //Para escribir mensajes por el puerto serie

//Inicializacion del led 13
int led = 13;

//Inicializacion del puerto serie
Serial.begin(115200); //Esxpresado en baudios

void setup() {                
  pinMode(led, OUTPUT);     
}

// the loop routine runs over and over again forever:
void loop() {
  digitalWrite(led, HIGH);   // turn the LED on (HIGH is the voltage level)
  Serial.println("ON");
  delay(500);               // wait for a second
  digitalWrite(led, LOW);    // turn the LED off by making the voltage LOW
  Serial.println("OFF");
  delay(500);               // wait for a second
}

//hola
