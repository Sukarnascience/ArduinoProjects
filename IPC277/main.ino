/**
 * Group Name : IPC277
 * Another    : Sukarna Jana
 * Title      : Automatic Gate Opener
 * 
 * Copyright © 2022 Sukarna jana
 */

#include <Servo.h>

#define outLazer A0
#define inLazer A1
#define pir 4
#define buzzer 5
#define servo 6

int inLDRsence = 0;
int outLDRsence = 0;
int pirData = 0;
int stateOfdir = 0;

Servo gate;

void setup(){
  pinMode(outLazer,INPUT);
  pinMode(inLazer,INPUT);
  pinMode(pir,INPUT);
  pinMode(buzzer,OUTPUT);

  gate.attach(servo);

  gate.write(0);
}

void loop(){
   inLDRsence = analogRead(outLazer);
   outLDRsence = analogRead(inLazer);
   pirData = digitalRead(pir);

   if(pirData==1){
    if(inLDRsence<=1000){
      stateOfdir = 1;
      gateState(1);
    }
    if(outLDRsence<=1000 && stateOfdir == 1){
      buzz();
      gateState(0);
      stateOfdir = 0;
    }
    if(outLDRsence<=1000 && stateOfdir == 0){
      stateOfdir = 1;
      gateState(1);
    }
    if(inLDRsence<=1000 && stateOfdir == 1){
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
  }
  else if(d1==0){
    for(int i=90;i>=0;i--){
      gate.write(i);
      delay(20);
    }
  }
  else{
    gate.write(0);
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
