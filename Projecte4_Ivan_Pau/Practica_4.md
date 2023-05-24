---
title: "Informe Práctica 4"
author: "Iván Enciso y Pau Codina"
date: "10/03/22"
output: html_document
---


# Informe Practica 4 Ivan Enciso & Pau Codina


## 1-Introducción


El presente informe describe el funcionamiento de un programa diseñado para realizar multitareas, es decir, la ejecución de varios procesos que tienen lugar al mismo tiempo. Para ello nos ayudaremos de Arduino y FreeRTOS.

#

## 2-Objetivos


El objetivo principal de la práctica es comprender el funcionamiento de un sistema operativo en tiempo real. Para ello se llevarán a cabo un par de ejercicios que nos van a ayudar a entender cómo se desarrolla una multitarea en ESP32.

#

## 3-Desarrollo

### 3.1 Descripción salida puerto serie


Por el puerto serie sale una secuencia de mensajes que se repiten cada cierto periodo de tiempo. En este caso estos mensajes son: “this is ESP32 Task” y “this is another Task”.


### 3.2 Funcionamiento


Para el desarrollo del primer programa primero necesitamos crear una tarea que llamaremos “anotherTask” la cual tendrá unos parámetros por defecto. Segundo creamos un loop infinito que saque por pantalla un texto que en este caso será: “this i ESP32 Task”. Después llamamos a la tarea que hemos creado previamente que será invocada cuando una tarea adicional sea creada.  Dicho esto, creamos un loop infinito que sacará por pantalla el texto: “this is another task”. Y para finalizar ejecutamos el siguiente código: “vTaskDelete” que se encargará de eliminar la tarea cuando esta finalice.

### 3.3 Código:
#

    void setup()
    {
        Serial.begin(112500);
        xTaskCreate(anotherTask,"another Task",10000,NULL,1,NULL);
    }
 
    void loop()
    {
        Serial.println("this is ESP32 Task");
        delay(1000);
    }
 
    void anotherTask(  )
    {
    
        for(;;)
        {
            Serial.println("this is another Task");
            delay(1000);
        }
    
        vTaskDelete( NULL );
    }



#

### Ejercicio 2:

### Código:

#
    #include <Arduino.h>

    long debouncing_time = 150;
    volatile unsigned long last_micros;
    SemaphoreHandle_t mutex_v;

    void Encender (void *pvParameters)
    {
        for (;;) {

            xSemaphoreTake(mutex_v, portMAX_DELAY);
            digitalWrite(32, HIGH);
            digitalWrite(33, LOW);
            Serial.println("ENCENDIO");
            vTaskDelay(500 / portTICK_PERIOD_MS);
            xSemaphoreGive(mutex_v);
            vTaskDelay(500 / portTICK_PERIOD_MS);

        }
    }

    void Apagar (void *pvParameters)
    {
        for(;;){

            xSemaphoreTake(mutex_v, portMAX_DELAY);
            digitalWrite(32, LOW);
            digitalWrite(33, HIGH);
            Serial.println("APAGAO");
            vTaskDelay(500 / portTICK_PERIOD_MS);
            xSemaphoreGive(mutex_v);
            vTaskDelay(500 / portTICK_PERIOD_MS);

        }
    }

    void setup() {

        Serial.begin(115200);
        pinMode(32, OUTPUT);
        pinMode(33, OUTPUT);
        mutex_v = xSemaphoreCreateMutex();

        if(mutex_v == NULL){
            Serial.println("No se ha podido crear el Mutex");
        }

        xTaskCreate(Encender, "Led on", 10000, NULL, 0, NULL);
        xTaskCreate(Apagar, "Led off", 10000, NULL, 0, NULL);

    }

    void loop() {}
#

### Descripción salida puerto serie


Por el puerto serie sale una secuencia de mensajes que se repiten cada cierto periodo de tiempo. En este caso estos mensajes son: “ENCENDIDO” y “APAGADO”.

### Funcionamiento:

El programa anterior realiza la función de encendido y apagado de un LED. Para esto, primero se ejecuta una acción que se encarga de encender el LED y que al hacerlo muestra por pantalla un mensaje que dice "ENCENDIDO". Luego se ejecuta otra acción que se encarga de apagar el LED y que una vez realiza la acción saca por pantalla el mensaje "APAGADO". En cada una de estas dos acciones se utiliza un bucle for, además de añadir un delay de 500ms a cada ejecución. Por último, en el setup al ejecutar el programa si ocurre algún problema se nos mostrará un mensaje que dice "No se ha podido crear el Mutex".

