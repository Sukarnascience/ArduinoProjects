#include <ESP8266WiFi.h>

#define m1A D1
#define m1B D2
#define notifyLed D0
#define statesLed D4

const char* ssid     = "LocalNetwork";
const char* password = "sukarna jana";

WiFiServer server(80);
IPAddress local_IP(192, 168, 43, 30);
IPAddress gateway(192, 168, 43, 1);
IPAddress subnet(255, 255, 255, 0);
IPAddress primaryDNS(8, 8, 8, 8);  
IPAddress secondaryDNS(8, 8, 4, 4);

String stateIs = "close";

void setup(){
  pinMode(m1A,OUTPUT);
  pinMode(m1B,OUTPUT);
  pinMode(notifyLed,OUTPUT);
  pinMode(statesLed,OUTPUT);
  
  if (!WiFi.config(local_IP, gateway, subnet, primaryDNS, secondaryDNS)) {
    error();
  }
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    digitalWrite(notifyLed,1);
    delay(500);
    digitalWrite(notifyLed,1);
    delay(500);
  }

  server.begin();

  digitalWrite(statesLed,0);
  digitalWrite(m1A,0);
  digitalWrite(m1B,0);
}

void loop(){
  
  WiFiClient client = server.available();  

  if (!client) { 
    error();
  } 
  
  String request = client.readStringUntil('\r');
  client.flush();
             
  if (request.indexOf("/State=open") != -1) {
    stateIs = "open";
    openJi();
  } else if (request.indexOf("/State=close") != -1) {
    stateIs = "close";
    closeJi();
  }

  client.println("HTTP/1.1 200 OK");
  client.println("Content-type:text/html");
  client.println("Connection: close");
  client.println();
  client.println("<!DOCTYPE html><html>");
  client.println("<head><title>Curtain Controller</title><style>body{text-align: center;background-color: #702963;color:rgb(255, 255, 255);font-size: 35px;font-family: \"Courier New\", Courier, monospace;}button{border-radius: 20px;font-size: 45px;font-family: \"Courier New\", Courier, monospace;width: 80%;padding: 25px;}div{width: 100%;height: 100%;display: grid;column-gap: 50px;}#open{background-color: rgba(0, 255, 149, 0.801);}#close{background-color: rgba(255, 67, 67, 0.801);}</style>");    
  client.println("</head><body>");
  client.println("<h1>Curtain Controller</h1><p>Helps you to close/open the Curtain</p><div>");
                         
  if (stateIs=="close") {
    client.println("<a href=\"/State=open\"><button id=\"open\"><b>Open</b></button></a></div>");
  } 
  else if (stateIs=="open") {
    client.println("<a href=\"/State=close\"><button id=\"close\"><b>Close</b></button></a><br>");
  } 
              
  client.println("<p>&#169; Sukarna Jana 2022</p>");
  client.println("</body></html>");
  client.println();
  
}

void openJi(){
  digitalWrite(m1A,0);
  digitalWrite(m1B,1);
  digitalWrite(statesLed,1);
}
void closeJi(){  
  digitalWrite(m1A,1);
  digitalWrite(m1B,0);
  digitalWrite(statesLed,0);
}

void error(){
  digitalWrite(notifyLed,1);
  delay(100);
  digitalWrite(notifyLed,1);
  delay(100);
}
