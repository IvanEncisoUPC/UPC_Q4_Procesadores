---
title: "Informe Práctica 1"
author: "Iván Enciso y Pau Codina"
date: "01/03/22"
output: html_document
---


# Informe Practica 1 Ivan Enciso & Pau Codina


## 1-Introduccion
El presente informe describe el funcionamiento de un programa diseñado para controlar un LED, enviar señales por bus CAN y leer el voltaje de un pin en un microcontrolador. 
## 2-Objetivos
El objetivo principal de la práctica es demostrar la funcionalidad de los diferentes componentes del microcontrolador y su capacidad de interactuar con el mundo físico. Además, el programa puede ser utilizado como punto de partida
para el desarrollo de sistemas más complejos que requieran de las mismas funcionalidades. Otro de los objetivos principales es que el alumnado se familiarice con el material y el lenguaje requerido en el laboratorio.
## 3-Desarrollo


### 3.1 Text
Para el desarrollo del programa encargado de generar el “blink”, primero inicializamos el pin del led como OUTPUT. Seguido de esto inicializamos el terminal serie para después crear el “loop” infinito que será el encargado de ejecutar una y otra vez el programa. Dentro del loop escribimos las sentencias de código encargadas de encender, apagar, mostrar mensajes de encendido y apagado y el tiempo que queremos que tenga el clk.


### 3.1-Código


#include <Arduino.h>


int led = 23;


        void setup() {
        Serial.begin(115200);
        pinMode(led, OUTPUT);  
        Serial.println("");
        Serial.println("Hola mundo");
        }


       void loop() {


       //Parte principal


        digitalWrite(led,HIGH);  //Encender Led
        Serial.println("ON");     //Mostrar ON por Serie
        delay(500);               //Espera 500 ms
        digitalWrite(led,LOW);   //Apagar Led
        Serial.println("OFF");    //Mostrar OFF por Serie
        delay(500);               // Espera 500 ms


        //Parte voluntaria


        int valor = analogRead(GPIO_NUM_4);
        Serial.println(valor);
      }




### 3.2-Diagrama de flujo
    flowchart TD


    k(Inicio) --> A[Asignar puerto serie]
    A[Asignar puerto serie] --> B[Pin 13 en modo salida]
    B --> C[Depurar BusCan]
    C --> D[Escribir HOLA MUNDO por terminal]
    D --> E
   
   
   
    E[Encender LED] --> F[Mostrar ON por terminal]
    F --> |Esperar 500ms|G[Apagar LED]
    G --> H[Mostrar OFF por terminal]
    H --> |Esperar 500ms|I[Leer valor del GPIO_NUM_4]
    I --> J[Escribir por terminal el valor leido]
    J --> E


## 4.Conclusiones


## 5.Referencias
[Blink](https://github.com/schacon/blink)
[AnalogReader](https://randomnerdtutorials.com/esp32-adc-analog-read-arduino-ide/)
