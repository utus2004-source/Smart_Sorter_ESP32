#include "wifi_server.h"
#include <WiFi.h>

//Wifi of ESP32 setting 
const char* ssid = "SmartBin_AP";
const char* password = "smartbin123";

IPAddress ip(192, 168, 4, 1);
IPAddress gateway(192, 168, 4, 1);
IPAddress subnet(255, 255, 255, 0);

// TCP serwer on port number  5000
WiFiServer server(5000);
WiFiClient client;
bool clientConnected = false;

// Mesage buffer 
String buffer = "";

void startWiFi() {
    WiFi.mode(WIFI_AP); //
    WiFi.softAPConfig(ip, gateway, subnet);//
    WiFi.softAP(ssid, password, 6, false, 1);   // Configuration od WIFI 
    //(Network SSD,Password , chanel number,ssd hide network and max devices connected to it)

    //Print Wifi information
    Serial.print("Siec WiFi: ");
    Serial.println(ssid);
    Serial.print("IP ESP32: ");
    Serial.println(WiFi.softAPIP());

    server.begin();
    Serial.println("Serwer TCP waits on port number 5000");
}

void checkNewClient() {
    
    // Check if client diconnected and disconnect comunication 
    if (clientConnected && !client.connected()) {
        Serial.println("Raspberry Pi sie rozlaczylo");
        client.stop();
        clientConnected = false;
    }

    // new client wants to connect
    WiFiClient newClient = server.available(); //check if cleint is connected 

    if (newClient) {

        client = newClient;
        clientConnected = true;
        buffer = "";
        
        //print client information after connection
        Serial.print("Polaczono z: ");
        Serial.println(client.remoteIP());
        Serial.println(client.localPort());
        Serial.println(client.connected());
    }
}

bool readMessage(String &message) {


    if (!clientConnected) {
        return false;
    }

    char c = client.read();

    if ( c == '\n') {




        
    }

    
}

void sendMessage(String message) {
    if (clientConnected) {
        client.print(message + "\n");
    }
}
