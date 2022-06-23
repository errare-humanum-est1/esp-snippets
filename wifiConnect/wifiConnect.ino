#include <WiFi.h>

const char* ssid = "Biathlon Netzwerk";
const char* password = "DDACK79393";

void wifiConnect(){
    WiFi.begin(ssid, password);
    Serial.println("Connecting");
    
    while(WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }

    Serial.println("");
    Serial.print("Connected to WiFi network with IP Address: ");
    Serial.println(WiFi.localIP());
}

void loop(){
    if(WiFi.status()== WL_CONNECTED){
        //do when connected
    }
    else {
        Serial.println("WiFi Disconnected");
}