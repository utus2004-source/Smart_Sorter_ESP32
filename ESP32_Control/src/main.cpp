#include <Arduino.h>
#include "wifi_server.h"

void setup() {
    Serial.begin(115200);
    delay(500);
    Serial.println("Start Smart Bin ESP32");

    startWiFi();
}


void loop() {
    checkNewClient();

    String message;
    if (readMessage(message)) {
        Serial.print("RCV: ");
        Serial.println(message);

        sendMessage("ECHO: " + message);   
    }
}
