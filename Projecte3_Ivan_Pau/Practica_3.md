---
title: "Informe Práctica 3"
author: "Iván Enciso y Pau Codina"
date: "10/03/22"
output: html_document
---


# Informe Practica 3 Ivan Enciso & Pau Codina


## 1. Introducción


El presente informe describe el funcionamiento de dos periféricos (Wifi y Bluetooth), mediante un web server que nosotros mismos generaremos utilizando el microprocesador ESP32. A su vez, nos ayudaremos de una aplicación movil para establecer esta comunicación serie Bluetooth.

#

## 2. Objetivos


El objetivo principal de la práctica es comprender el funcionamiento de WIFI y Bluetooth. 

#

### 3. Desarrollo

### 3.2 Salida puerto serie

La salida por el puerto serie mostrará información sobre el proceso de conexión a la red Wi-Fi y el inicio del servidor HTTP. 

Un ejemplo de lo que puede salir por el puerto série podría ser este:

    Try Connecting to 
    Xiaomi_11T_Pro
    ........
    WiFi connected successfully
    Got IP: 192.168.1.10
    HTTP server started

Es importante tener en cuenta que la salida real por el puerto serie puede variar según la configuración de la red Wi-Fi, el estado de la conexión y otros factores. Además, pueden aparecer mensajes adicionales o información de depuración según el código y las bibliotecas utilizadas.

### 3.3 Funcionamiento

Nuestro programa consiste en la generación de una página web. Para ello es esencial disponer de conexión a Internet, por lo que nuestra primera parte de código es la que se encarga de establecer una conexión via WIFI a un punto de acceso como puede ser un teléfono movil.

El setup nos muestra si la conexión con este punto de acceso ha sido realizada correctamente. Para ello primero muestra un mensaje por pantalla que nos indica que se esta intentando establecer la conexión, una vez establecida se muestra por pantalla otro mensaje que indica que la conexión se ha establecido correctamente además de la dirección IP de nuestro ESP32. Por último se muestra un mensaje que nos hace saber que el servidor HTTP se ha inicializado y es aquí donde entra en funcionamiento el loop.

El loop tiene en su interior el código necesario para mostrar la información que nosottros queremos en la web que estamos creando. 

### 3.4 Código:
#
    #include <WiFi.h>
    #include <WebServer.h>

    // SSID & Password
    const char* ssid = "Xiaomi_11T_Pro"; 
    const char* password = "f5cbd8a82232";
    WebServer server(80);

    // HTML & CSS contents which display on web server
    String HTML = "<!DOCTYPE html>\
    <html>\
    <body>\
    <h1>My Ejemplo de HTML, &#128522;</h1>\
    </body>\
    </html>";

    // Handle root url (/)
    void handle_root() {
        server.send(200, "text/html", HTML);
    }

    // Object of WebServer(HTTP port, 80 is defult)
    void setup() {
        Serial.begin(115200);
        Serial.println("Try Connecting to ");
        Serial.println(ssid);

        // Connect to your wi-fi modem
        WiFi.begin(ssid, password);

        // Check wi-fi is connected to wi-fi network
        while (WiFi.status() != WL_CONNECTED) {
            delay(1000);
            Serial.print(".");
        }

        Serial.println("");
        Serial.println("WiFi connected successfully");
        Serial.print("Got IP: ");
        Serial.println(WiFi.localIP()); 
        server.on("/", handle_root);
        server.begin();
        Serial.println("HTTP server started");
        delay(100);

    }

    void loop() {
        server.handleClient();
    }


#

### 4. Ejercicio 2:

### 4.2 Salida puerto serie: 

 Por el puerto serie salen los datos que ingresan a través del puerto serial USB y los datos que llegan a través de Bluetooth.

Este es un ejemplo de lo que podría salir por el puerto serie:

    The device started, now you can pair it with bluetooth!
    Hello from Bluetooth device
    Received message: Change the password


Es importante tener en cuenta que la salida real por el puerto serie dependerá de las interacciones específicas con los dispositivos Bluetooth emparejados y los mensajes enviados y recibidos

### 4.3 Funcionamiento: 

Este código permite establecer una comunicación bidireccional entre el ESP32 y otro dispositivo a través de Bluetooth. Los datos enviados desde el puerto serial se transmiten a través de la conexión Bluetooth, y los datos recibidos se envían al puerto serial estándar. Esto permite la comunicación inalámbrica entre el ESP32 y otro dispositivo compatible con Bluetooth, como un teléfono o un ordenador.

### 4.4 Código:

#
    #include "BluetoothSerial.h"

    BluetoothSerial SerialBT;

    void setup() {
        Serial.begin(115200);
        SerialBT.begin("ESP32test"); //Bluetooth device name
        Serial.println("The device started, now you can pair it with bluetooth!")
    }

    void loop() {
        if (Serial.available()) {
            SerialBT.write(Serial.read());
        }
        if (SerialBT.available()) {
            Serial.write(SerialBT.read());
        }
        delay(20);
    }
#


### 5. Ejercicio adicional:

### 5.2 Código:
#

    #include <WiFi.h>

    const char* ssid     = "ESP32_Iwa";
    const char* password = "123456789";

    WiFiServer server(80);

    String header;
    String output26State = "off";
    String output27State = "off";

    const int output26 = 26;
    const int output27 = 27;

    void setup() {
     Serial.begin(115200);
     pinMode(output26, OUTPUT);
     pinMode(output27, OUTPUT);
     digitalWrite(output26, LOW);
     digitalWrite(output27, LOW);
     Serial.print("Setting AP (Access Point)…");
     WiFi.softAP(ssid, password);
     IPAddress IP = WiFi.softAPIP();
     Serial.print("AP IP address: ");
     Serial.println(IP);
     server.begin();
    }

     void loop(){
        WiFiClient client = server.available();   
        if (client) {                             
         Serial.println("New Client.");          
        String currentLine = "";                
        while (client.connected()) {            
         if (client.available()) {             
            char c = client.read();             
            header += c;
            if (c == '\n') {                    
                if (currentLine.length() == 0) {
                client.println("HTTP/1.1 200 OK");
                client.println("Content-type:text/html");
                client.println("Connection: close");
                client.println();
                    if (header.indexOf("GET /26/on") >= 0) {
                     Serial.println("GPIO 26 on");
                     output26State = "on";
                     digitalWrite(output26, HIGH);
                }   else if (header.indexOf("GET /26/off") >= 0) {
                     Serial.println("GPIO 26 off");
                     output26State = "off";
                     digitalWrite(output26, LOW);
                } else if (header.indexOf("GET /27/on") >= 0) {
                     Serial.println("GPIO 27 on");
                     output27State = "on";
                     digitalWrite(output27, HIGH);
                } else if (header.indexOf("GET /27/off") >= 0) {
                     Serial.println("GPIO 27 off");
                     output27State = "off";
                     digitalWrite(output27, LOW);
                }
                 client.println("<!DOCTYPE html><html>");
                 client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
                 client.println("<link rel=\"icon\" href=\"data:,\">");
                 client.println("<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}");
                 client.println(".button { background-color: #4CAF50; border: none; color: white; padding: 16px 40px;");
                 client.println("text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}");
                 client.println(".button2 {background-color: #555555;}</style></head>");
                 client.println("<body><h1>ESP32 Web Server</h1>");
                 client.println("<p>GPIO 26 - State " + output26State + "</p>");
                 if (output26State=="off") {
                    client.println("<p><a href=\"/26/on\"><button class=\"button\">ON</button></a></p>");
                 } else {
                    client.println("<p><a href=\"/26/off\"><button class=\"button button2\">OFF</button></a></p>");
                 } 
                     client.println("<p>GPIO 27 - State " + output27State + "</p>");
                    if (output27State=="off") {
                     client.println("<p><a href=\"/27/on\"><button class=\"button\">ON</button></a></p>");
                 } else {
                     client.println("<p><a href=\"/27/off\"><button class=\"button button2\">OFF</button></a></p>");
                 }
                  client.println("</body></html>");
                  client.println();
                  break;
            } else { 
             currentLine = "";
            }
         } else if (c != '\r') {
            currentLine += c;      
         }
        }
       }
         client.stop();
         Serial.println("Client disconnected.");
         Serial.println("");
      }
    }


