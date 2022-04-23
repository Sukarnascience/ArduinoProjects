#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>

#define IN1 0
#define IN2 2

const char* ssid = "SSID";
const char* password = "PASS";

void setup(){

  pinMode(IN1,INPUT);
  pinMode(IN2,INPUT);

  Serial.begin(9600);

  setupWifi();
}

void loop(){

  if (WiFi.status() != WL_CONNECTED)
  {
    setupWifi();
  }
  int readIN1 = digitalRead(IN1);
  int readIN2 = digitalRead(IN2);

  if(readIN1==0 && readIN2==0){
    // Everything is Normal
    Serial.println("Everything is Normal");
  }
  else if(readIN1==1 && readIN2==0){
    // Send MSG that Smoke has been detected
    Serial.println("Cattail");
    while (SendData(String("Cattail can be grown in this place")) != 0); 
  }
  else if(readIN1==0 && readIN2==1){
    // Send MSG that Alcohol has been detected
    Serial.println("Tulsi");
    while (SendData(String("tulsi can be grown in this place")) != 0); 
  }
  else if(readIN1==1 && readIN2==1){
    // Send MSG that Fire has been detected
    Serial.println("Cactus");
    while (SendData(String("cactus can be grown in this place")) != 0); 
  }
  else{
    // Send MSG that there is some issue in DEVICE
    Serial.println("Device is mal funsaning");
    while (SendData(String("ERROR_IN_DEVICE")) != 0); 
  }
  
}

void setupWifi(){
  WiFi.mode(WIFI_STA);
  status = WiFi.begin(ssid, password);    
 
  Serial.print("Attempting to connect to SSID: ");
  Serial.println(ssid);  
 
  while (WiFi.status() != WL_CONNECTED) {
   delay(1000);
   Serial.print(".");
  }
  Serial.println("Connected to wifi");
}

int SendData(String state)
{
   HTTPClient http;
   int ret = 0;
   Serial.print("[HTTP] begin...\n");
   http.begin("http://maker.ifttt.com/trigger/WhichPlant/with/key/--key--/?value1="+state); //HTTP

    Serial.print("[HTTP] GET...\n");
    int httpCode = http.GET();
    if(httpCode > 0) {
    Serial.printf("[HTTP] GET code: %d\n", httpCode);

      if(httpCode == HTTP_CODE_OK) {
        String payload = http.getString();
        Serial.println(payload);
      }
    } else {
        ret = -1;
        Serial.printf("[HTTP] GET failed, error: %s\n", http.errorToString(httpCode).c_str());
        delay(500); 
    }

    http.end();
    return ret;
}  
