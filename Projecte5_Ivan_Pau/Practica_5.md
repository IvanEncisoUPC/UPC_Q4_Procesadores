---
title: "Informe Práctica 5"
author: "Iván Enciso y Pau Codina"
date: "10/03/22"
output: html_document
---


# Informe Practica 5 Ivan Enciso & Pau Codina


## 1-Introducción


El presente informe describe el funcionamiento de los buses de comunicación entre periféricos. Para ello montaremos y programaremos una série de programas que nos permitiran utilizar diversos tipos de periféricos. Estos a su vez pueden ser internos o externos al procesador, aunque en nuestro caso seran externos.

#

## 2-Objetivos


El objetivo principal de la práctica es comprender el funcionamiento de los buses de comunicación entre periféricos. Entre los buses que vamos a ver se encuentran el I2C, SPI, I2S y USART entre otros.

#

## 3-Desarrollo

### 3.1 Descripción salida puerto serie

la salida del monitor serial mostrará información detallada sobre los dispositivos I2C encontrados en el bus I2C del ESP32, incluyendo sus direcciones.

#
### 3.2 Funcionamiento

Para la creación de este programa primero debemos escribir las lineas de código necesarias para hacer que nuestro microprocesador escanee en busca de periféricos.En caso de que se encuentre un periférico se mostrará por pantalla la dirección donde se encontró el dispositivo. Por otro lado si se produce un error el programa nos dirá por pantalla la dirección donde el error en cuestión se haya producido.Por último, si al realizar el escaneo no se encuentran dispositivos se mostrará por pantalla un mensaje diciendo que ningún dispositivo fue encontrado y pasados 5 segundos se volverá a repetir el escaneo de nuevo.

### 3.3 Código:
#

    #include <Arduino.h>

    #include <Wire.h>


    void setup()
    {
    Wire.begin();
    Serial.begin(115200);
    while (!Serial);         
    Serial.println("\nI2C Scanner");
    }
 
 
    void loop()
    {
    byte error, address;
    int nDevices;
 
    Serial.println("Scanning...");
 
    nDevices = 0;
    for(address = 1; address < 127; address++ )
    {
    Wire.beginTransmission(address);
    error = Wire.endTransmission();
 
    if (error == 0)
    {
      Serial.print("I2C device found at address 0x");
      if (address<16)
        Serial.print("0");
      Serial.print(address,HEX);
      Serial.println("  !");
 
      nDevices++;
    }
    else if (error==4)
    {
      Serial.print("Unknown error at address 0x");
      if (address<16)
        Serial.print("0");
        Serial.println(address,HEX);
    }    
    }
    if (nDevices == 0)
        Serial.println("No I2C devices found\n");
    else
        Serial.println("done\n");
    delay(5000);          
    }

#

### Ejercicio 2:

### Código:

#
   
#


