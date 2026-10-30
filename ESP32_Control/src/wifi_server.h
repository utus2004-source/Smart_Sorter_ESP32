#pragma once
#include <Arduino.h>

void startWiFi();                    
void checkNewClient();               
bool readMessage(String &message);   //RCV message if true lenght OK
void sendMessage(String message);    //SND message back (for test the same )
