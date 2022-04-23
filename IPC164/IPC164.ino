#include <SoftwareSerial.h>
#include <LiquidCrystal_I2C.h>
#include "Adafruit_FONA.h"
 
#define FONA_RX            2
#define FONA_TX            3
#define FONA_RST           4
 
#define FONA_RI_INTERRUPT  0

#define IR 7
#define buzz 6

float sensorValue;
float sensorVolts;

LiquidCrystal_I2C lcd(0x27,16,2);

char sendto[21] = "9113688393"; // Enter your Mobile Number here. Exclude country code.
char message[141] = "Hi Device Started"; 

String techtrends;
SoftwareSerial fonaSS = SoftwareSerial(FONA_TX, FONA_RX);
 
Adafruit_FONA fona = Adafruit_FONA(FONA_RST);
 
void setup() {  

  pinMode(IR,INPUT);
  pinMode(buzz,OUTPUT);

  lcd.begin();
  
  Serial.begin(9600);
  lcd.setCursor(0,0);
  lcd.print("Starting the GSM");
  Serial.println(F("FONA incoming call example"));
  Serial.println(F("Initializing....(May take 3 seconds)"));
  delay(5000);
  fonaSS.begin(4800); // if you're using software serial
  if (! fona.begin(fonaSS)) {           // can also try fona.begin(Serial1) 
    Serial.println(F("Couldn't find FONA"));
    while (1);
  }
  Serial.println(F("FONA is OK"));
 
 fona.print ("AT+CSMP=17,167,0,0\r");
   fona.sendSMS(sendto, message);
   delay(1000);
   lcd.clear();
   lcd.setCursor(0,0);
   lcd.print("MQ-6 to warm up");
   delay(20000);   // allow the MQ-6 to warm up
   lcd.clear();
}
 
void loop()
{
  for(int i = 0; i < 100; i++){ 
    sensorValue = sensorValue + analogRead(0); // read analog input pin 0 
 } 
 sensorValue = sensorValue / 100; // get average reading 
 sensorVolts = sensorValue/1024*5.0; //convert to voltage 
 if(sensorVolts > 1.4){
     Serial.println("LPG gas detected!");
     fona.sendSMS(sendto,"LPG gas leakage detected!");
     lcd.setCursor(0,1);
     lcd.print("LPG gas Detected");
 }

 if(digitalRead(IR)){
  Serial.println("Fire");
  lcd.setCursor(0,1);
  lcd.print("Fire Detected!");
  digitalWrite(buzz,1);
 }
 
 delay(255); 
 digitalWrite(buzz,0);
 lcd.clear();
}
