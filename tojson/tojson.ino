#include <ArduinoJson.h>

void setup(){
    Serial.begin(115200);

    String result           = "{'data':[{'rfid_tag':'0','fname':'tim','lname':'albersmann','class':'10'},{'rfid_tag':'1','fname':'benedikt','lname':'ehrenmann','class':'10'}]}";

    DynamicJsonDocument doc(1024);
    deserializeJson(doc, result);

    int length              = doc["data"].size();

    for (int i = 0; i < length; i++){
        String si           = String(i);
        
        String fname        = doc["data"][i]["fname"];
        String lname        = doc["data"][i]["lname"];
        String player_class = doc["data"][i]["class"];
        int rfid_tag        = doc["data"][i]["rfid_tag"];

        Serial.println("fname_" + si + ": " + fname);
        Serial.println("lname_" + si + ": " + lname);
        Serial.println("class_" + si + ": " + player_class);
        Serial.println("rfid_tag_" + si + ": " + String(rfid_tag));
        Serial.println();
    }
}

void loop(){
    //hi
}