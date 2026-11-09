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

// Mesage buffer ,
String buffer = "";
//new message
bool new_message = false;

void startWiFi() {
    WiFi.mode(WIFI_AP); //
    WiFi.softAPConfig(ip, gateway, subnet);//
    WiFi.softAP(ssid, password, 6, false, 1);   // Configuration od WIFI 
    //(Network SSD,Password , chanel number,ssd hide network and max devices connected to it)

    //Print Wifi information
    Serial.print(" WiFi: ");
    Serial.println(ssid);
    Serial.print("IP ESP32: ");
    Serial.println(WiFi.softAPIP());

    server.begin();
    Serial.println("Serwer TCP waits on port number 5000");
}

void checkNewClient() {
    
    // Check if client diconnected and disconnect comunication 
    if (clientConnected && !client.connected()) {
        Serial.println("Client disconnected");
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
        Serial.print("Connected with: ");
        Serial.println(client.remoteIP());
        Serial.print("on port number : ");
        Serial.println(client.localPort());
        Serial.print("connection satus : ");
        Serial.println(client.connected());
    }
}

bool readMessage(String &message ) {


    if (!clientConnected) {
        return false;
    }

    char c = client.read();

    //check begginign of the message
    if (c == 'S' ) {
        buffer = "";
        new_message = true;

    }
    
    // checking the end of message
    if ( c == '\n' && new_message) {

        message = buffer;
        buffer = "";

        message.trim();

        if (message.length() > 0) {
            new_message = false;
            return true;

        }

        }
    else { 
        //Creates the recieved message 
        if (new_message){
        buffer += c;
        }
        //Messgae to long send false
        if (buffer.length() > 512) {

            Serial.println("Message too long!");
            new_message = false;
            buffer = "";
            }
        }

    return false;
}

void sendMessage(String message) {
    if (clientConnected) {
        client.print(message + "\n");
    }
}
