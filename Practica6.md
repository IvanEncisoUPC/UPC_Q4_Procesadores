---
title: "Informe Práctica 6"
author: "Iván Enciso y Pau Codina"
date: "10/03/22"
output: html_document
---


# Informe Practica 6 Ivan Enciso & Pau Codina


## 1-Introducción


El presente informe describe el funcionamiento de un conjunto de programas diseñados para poner en uso el bus spi y comprender su funcionamiento.

#

## 2-Objetivos


El objetivo principal de la práctica es comprender el funcionamiento del bus spi.

#

## 3-Desarrollo

### 3.1 Descripción salida puerto serie





### 3.2 Funcionamiento

Este código se encarga de mostrar unos archivos que son leidos desde una targeta SD. Para ello primero se establece la conexión con la targeta SD, una vez realizada la conexión se ejecuta un comando que se encarga de extraer la información que contiene la targeta SD y por último esta información es mostrada por pantalla.

### 3.3 Código:
#

    #include <SPI.h>
    #include <SD.h>

    File myFile;

    void setup()
    {
     Serial.begin(9600);
    Serial.print("Iniciando SD ...");
    if (!SD.begin(4)) {
        Serial.println("No se pudo inicializar");
        return;
    }
    Serial.println("inicializacion exitosa");
 
    myFile = SD.open("archivo.txt");//abrimos  el archivo 
    if (myFile) {
        Serial.println("archivo.txt:");
        while (myFile.available()) {
    	Serial.write(myFile.read());
        }
        myFile.close(); //cerramos el archivo
        } else {
        Serial.println("Error al abrir el archivo");
        }
    }

    void loop()
    {
  
    }




#

### Ejercicio 2:

### Descripción salida puerto serie





### Funcionamiento

Este programa realiza la función de un lector de targetas. Para ello disponemos de un periférico que es capaz de detectar targetas del tipo RFID. Primero el programa inicia la comunicación serie, el bus SPI y el periférico, que en este caso es el MFRC522. Después se envia una orden al periférico para que nos diga si se ha encontrado o no alguna targeta y en caso de que si se haya encontrado una pedimos que se envíe su UID serialmente. Por último se pone fin a la lectura de la targeta en cuestión.

### Código:

#
    #include <SPI.h>
    #include <MFRC522.h>

    #define RST_PIN	9    //Pin 9 para el reset del RC522
    #define SS_PIN	10   //Pin 10 para el SS (SDA) del RC522
    MFRC522 mfrc522(SS_PIN, RST_PIN); //Creamos el objeto para el RC522

    void setup() {
	Serial.begin(9600); //Iniciamos la comunicación  serial
	SPI.begin();        //Iniciamos el Bus SPI
	mfrc522.PCD_Init(); // Iniciamos  el MFRC522
	Serial.println("Lectura del UID");
    }

    void loop() {
	// Revisamos si hay nuevas tarjetas  presentes
	if ( mfrc522.PICC_IsNewCardPresent()) 
        {  
  		//Seleccionamos una tarjeta
            if ( mfrc522.PICC_ReadCardSerial()) 
            {
                  // Enviamos serialemente su UID
                  Serial.print("Card UID:");
                  for (byte i = 0; i < mfrc522.uid.size; i++) {
                          Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
                          Serial.print(mfrc522.uid.uidByte[i], HEX);   
                  } 
                  Serial.println();
                  // Terminamos la lectura de la tarjeta  actual
                  mfrc522.PICC_HaltA();         
            }      
	}	
}

#



