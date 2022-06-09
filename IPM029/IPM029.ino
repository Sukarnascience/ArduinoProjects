/*
 * Another    : Sukarna Jana
 * Title      : Smart Chair for Maintain Body Posture
 * Date       : 08 June 2022, 01:19
 * 
 * Copyright © 2022 Sukarna jana
 * 
 *      [ PinOut ] 
 * 
 * ---- IR Sensors ----
 * out1 --> D2
 * out2 --> D3
 * out3 --> D4
 * ---- FSR Sensors ----
 * BigerPad1 --> A0
 * smallPad1 --> A1
 * smallPad2 --> A2
 * ---- ESP8266-01 ----
 * TX --> D 
 * RX --> D
 * ---- LED 16x2 ----
 * RS --> 12
 * Enable --> 11
 * D4     --> 5
 * D5     --> 4
 * D6     --> 3
 * D7     --> 2
 * R/W    --> GND
 * VSS    --> GND
 * VCC    --> 5V
 * 10K resistor:
 * ends to +5V and ground
 * wiper to LCD VO pin (pin 3)
 */

#include <LiquidCrystal.h>
#include <SoftwareSerial.h>

#define ir1 6
#define ir2 7
#define ir3 8

#define sLed 9

#define fsr1 A0
#define fsr2 A1
#define fsr3 A2

const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

SoftwareSerial esp(3,2); 

int count = 0;

void setup(){

  Serial.begin(9600);
  lcd.begin(16, 2);
  
  pinMode(ir1,INPUT);
  pinMode(ir2,INPUT);
  pinMode(ir3,INPUT);

  pinMode(sLed,OUTPUT);

  func();
  esp.print("AT+CWSAP=\"iPhone\",\"Nyankhan\",1,4");
  delay(1000);
}

void loop(){
   if(isSitting()){
    // Note the initial Time of start
    count++;
    if(!isNCoBody()){
      // Send msg to sit properly
      fixBodyP();
    }
   }
   if(count>=60){
    count = 0;
    fixBodyP();
   }
   delay(1000);
}

boolean isSitting(){
  int xx = analogRead(fsr1);
  int yy = analogRead(fsr2);
  int zz = analogRead(fsr3);

  if((xx > 200) && (yy > 200) && (zz > 200)){
    Serial.println("Sitting Properly");
    Serial.println();
    return true;
  }
  else if((xx < 50) && (yy < 50) && (zz < 50)){
    Serial.println("Not Sitting Properly");
    Serial.println();
    fixBodyP(); 
    return false;
  }
  else{
    Serial.println("No one is Sitting");
    Serial.println();
    return false;
  }
}

boolean isNCoBody(){
  boolean x = digitalRead(ir1);
  boolean y = digitalRead(ir2);
  boolean z = digitalRead(ir3);

  Serial.println("---- Body Posture ----");
  Serial.print("IR1 :");
  Serial.println(x);
  Serial.print("IR2 :");
  Serial.println(y);
  Serial.print("IR3 :");
  Serial.println(z);
  Serial.println("----------------------");
  Serial.println();

  if(x==0 && y==0 && z==0){
    // sitting good
    return true;
  }
  else{
    func();
    return false;
  }
}                                                                                                             

void fixBodyP(){
  esp.print("AT+HTTPCLIENT=1,0,\"https://maker.ifttt.com/trigger/Getup/with/key/dlytuNd3LHhhaEcBsQfrxK\",\"maker.ifttt.com\",\"/get\",1");
  func();
  delay(1000);
}

void func(){
  digitalWrite(sLed,1);
  delay(255);
  digitalWrite(sLed,0);
  delay(255);
}
