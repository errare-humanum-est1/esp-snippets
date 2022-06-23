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

String sendGETRequest(String getRequest) {
    
    //Check WiFi connection status
    if(WiFi.status() != WL_CONNECTED){
      return ""; 
    }

    HTTPClient http;

    // Your Domain name with URL path or IP address with path
    http.begin(getRequest.c_str());
    
    // Send HTTP GET request
    int httpResponseCode = http.GET();
    
    if (httpResponseCode != 200) {
      Serial.print("Response code: ");
      Serial.println(httpResponseCode);
      return "";
    }

    String payload = http.getString();

    // Free resources
    http.end();

    return payload;

}

void setup() {
  Serial.begin(115200);   
  wifiConnect();
}

void loop(){
  //Your Domain name/IP address, the api path and any arguments get set here
  String apiPath = "/api/game/login_log/get_rfid_tag.php";
  String apiArgs = "?rifle_id=1";

  String getRequest = serverIP + apiPath + apiArgs;

  String result = sendGETRequest(getRequest);
  
  if (result != ""){
    Serial.println(result);
  }

  delay(5000);
}