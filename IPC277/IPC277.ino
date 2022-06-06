/**
 * Group Name : IPC277
 * Another    : Sukarna Jana
 * Title      : Automatic Gate Opener
 * 
 * Copyright © 2022 Sukarna jana
 */

#include <Servo.h>
#include <dht.h>

#define outLazer A0
#define inLazer A1
#define pir 4
#define buzzer 5
#define servo 6
#define temphumi 2

int inLDRsence = 0;
int outLDRsence = 0;
int pirData = 0;
int stateOfdir = 0;

Servo gate;
dht DHT;

void setup(){
  pinMode(outLazer,INPUT);
  pinMode(inLazer,INPUT);
  pinMode(pir,INPUT);
  pinMode(buzzer,OUTPUT);

  gate.attach(servo);

  Serial.begin(9600);

  gate.write(0);
}

void loop(){
   inLDRsence = analogRead(outLazer);
   outLDRsence = analogRead(inLazer);
   pirData = digitalRead(pir);
   int cTaH = DHT.read11(temphumi);

   Serial.println("----DATA----");
   Serial.print("Temp :");
   Serial.print(DHT.temperature);
   Serial.println("°C");
   Serial.print("Humi : ");
   Serial.print(DHT.humidity);
   Serial.println("%");
   Serial.println("------------");
  
   Serial.print("Sensor Data : ");
   Serial.print("inLDRsence : ");
   Serial.print(inLDRsence);
   Serial.print(" | outLDRsence : ");
   Serial.println(outLDRsence);

   if(pirData==1){
    if(DHT.temperature>=40){
      buzz();
    }
    if(inLDRsence>=480){
      stateOfdir = 1;
      gateState(1);
    }
    if(outLDRsence>=480 && stateOfdir == 1){
      buzz();
      gateState(0);
      stateOfdir = 0;
    }
    if(outLDRsence>=480 && stateOfdir == 0){
      stateOfdir = 1;
      gateState(1);
    }
    if(inLDRsence>=480 && stateOfdir == 1){
      stateOfdir = 0;
      buzz();
      gateState(0);
    }
   }
}

void gateState(int d1){
  if(d1==1){
    for(int i=0;i<=90;i++){
      gate.write(i);
      delay(20);
    }
    Serial.println("Gate Open");
  }
  else if(d1==0){
    for(int i=90;i>=0;i--){
      gate.write(i);
      delay(20);
    }
    Serial.println("Gate Close");
  }
  else{
    gate.write(0);
    Serial.println("Gate Close");
  }
}

void buzz(){
  digitalWrite(buzzer,1);
  delay(100);
  digitalWrite(buzzer,0);
  delay(100);
  digitalWrite(buzzer,1);
  delay(100);
  digitalWrite(buzzer,0);
  delay(100);
}
