/**
 * 
 */

// Load Needed library
#include<Wire.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>

// Define I/O Pins
#define buzzer 1
#define eyeSen 2
#define errorLed 3

// Error Handle
int stateIs = 0;

// Static IP Address and Networking part
IPAddress local_IP(192,168,40,85);
IPAddress gateway(192,168,40,1);
IPAddress subnet(255,255,0,0);
IPAddress primaryDNS(8,8,8,8);
IPAddress secondaryDNS(8, 8, 4, 4);
const char* ssid     = "Local Network";
const char* password = "sukarna jana";
// WiFiServer server(80);
// or
ESP8266WebServer server(80);

const int addrOfMPU = 0x68;
int16_t AcX,AcY,AcZ,Tmp,GyX,GyY,GyZ;

int minVal=265;
int maxVal=402;

double x;
double y;
double z;

int seeV1 = 0;
int seeV2 = 0;

// Data to send
String data1 = "<p>Person_Is_About_To_Sleep</p>";
String data0 = "<p>Person_Is_Fine</p>";

void setup(){
  
  Wire.begin();
  Wire.beginTransmission(addrOfMPU);
  Wire.write(0x6B);
  Wire.write(0);
  Wire.endTransmission(true);

  Serial.begin(115200);

  pinMode(errorLed,OUTPUT);
  digitalWrite(errorLed,stateIs);

  // Configures static IP address
  if (!WiFi.config(local_IP, gateway, subnet, primaryDNS, secondaryDNS)) {
    stateIs = 1;
    digitalWrite(errorLed,stateIs);
  }
  // Connect to Wi-Fi network with SSID and password
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    digitalWrite(errorLed,stateIs);
    if(stateIs==1){
      stateIs = 0;
    }
    else{
      stateIs = 1;
    }
  }

  server.begin();  
  
}
void loop(){

  if(isEyeBlink()){
    seeV1 = 1;
  }
  else{
    seeV2 = 0;
  }
  if(xyzData()){
    seeV2 = 1;
  }
  else{
    seeV2 = 0;
  }

  if(seeV1==1 && seeV2==1){
     server.on("/", warning);
  }
  else{
    server.on("/", chill);
  }
  server.handleClient();     
}

void warning() {
  server.send(200, "text/html", data1);
}
void chill() {
  server.send(200, "text/html", data0);
}

int xyzData(){

    Wire.beginTransmission(addrOfMPU);
    Wire.write(0x3B);
    Wire.endTransmission(false);
    Wire.requestFrom(addrOfMPU,14,true);
    AcX=Wire.read()<<8|Wire.read();
    AcY=Wire.read()<<8|Wire.read();
    AcZ=Wire.read()<<8|Wire.read();
    int xAng = map(AcX,minVal,maxVal,-90,90);
    int yAng = map(AcY,minVal,maxVal,-90,90);
    int zAng = map(AcZ,minVal,maxVal,-90,90);

    x= RAD_TO_DEG * (atan2(-yAng, -zAng)+PI);
    y= RAD_TO_DEG * (atan2(-xAng, -zAng)+PI);
    z= RAD_TO_DEG * (atan2(-yAng, -xAng)+PI);

    int data = 0;

    return data;
  
}

int isEyeBlink(){
  if(digitalRead(eyeSen)){
    return 1;
  }
  else{
    return 0;
  }
}
