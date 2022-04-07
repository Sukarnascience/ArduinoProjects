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
    if(inLDRsence<300){
      gateState(1);
    }
    if(outLDRsence<300){
      buzz();
      gateState(0);
    }
   }
}

void gateState(int d1){
  if(d1==1){
    gate.write(90);
  }
  else if(d1==0){
    gate.write(0);
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
