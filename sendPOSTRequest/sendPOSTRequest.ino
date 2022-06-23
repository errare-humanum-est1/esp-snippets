#include <WiFi.h>
#include <HTTPClient.h>


//Network information goes here
const char* ssid = "Biathlon Netzwerk";
const char* password = "DDACK79393";

//as the server ip should not change its permanently set
const String serverIP = "http://192.168.1.33";

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

boolean sendPOSTRequest(String request) {
    
    //Check WiFi connection status
    if(WiFi.status() != WL_CONNECTED){
      return false; 
    }

    WiFiClient client;
    HTTPClient http;

    // Your Domain name with URL path or IP address with path
    http.begin(client, request);

    // Specify content-type header
    http.addHeader("Content-Type", "application/x-www-form-urlencoded");
    http.addHeader("Content-Type", "application/json");
    
    // Send HTTP POST request
    int httpResponseCode = http.POST("");
    
    // If you need an HTTP request with a content type: application/json, use the following:
    //http.addHeader("Content-Type", "application/json");
    //int httpResponseCode = http.POST("{\"api_key\":\"tPmAT5Ab3j7F9\",\"sensor\":\"BME280\",\"value1\":\"24.25\",\"value2\":\"49.54\",\"value3\":\"1005.14\"}");

    // If you need an HTTP request with a content type: text/plain
    //http.addHeader("Content-Type", "text/plain");
    //int httpResponseCode = http.POST("Hello, World!");
    
    if (httpResponseCode != 200) {
      Serial.print("Response code: ");
      Serial.println(httpResponseCode);
      return false;
    }
    
    Serial.println(http.getString());

    // Free resources
    http.end();

    return true;
}

void setup(){
  Serial.begin(115200);   
  wifiConnect();
}

void loop(){
    //Your Domain name/IP address, the api path and any arguments get set here
    String apiPath = "/api/game/login_log/link.php";
    String apiArgs = "?rifle_id=1&rfid_tag=2";

    String postRequest = serverIP + apiPath + apiArgs;

    if (!sendPOSTRequest(postRequest)){
        Serial.println("something bad happened");
    }else{
        Serial.println("success");
    }
    delay(50000000);
}