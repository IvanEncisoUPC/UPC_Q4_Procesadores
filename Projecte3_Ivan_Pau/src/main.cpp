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