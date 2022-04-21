/**
 * Group Name : IPC067
 * Another    : Sukarna Jana
 * Title      : Temperature,Humidity,Smoke,Alcohol Detector Using Arduino UNO IOT
 * 
 * Copyright © 2022 Sukarna jana
 */

// We will use 2 pins for sending Signals
/*
 * IN1 IN2 - DATA
 *  0   0    No Data
 *  1   0    Smoke Sence
 *  0   1    Alcohol Sence
 *  1   1    Fire Sence
 */

// Supporting Libraries
#include <dht.h>

dht DHT;
#define dht11Pin 2
#define fan 3
#define MQ2 A0 // #define MQ2 (0)
#define MQ3 A1 

#define IN1 4
#define IN2 5

#define Sober 120  
#define Drunk 400

float sensorValue1;
float sensorValue2;

void setup(){
  
  Serial.begin(9600);

  pinMode(MQ2,INPUT); // We can remove this
  pinMode(fan,OUTPUT);

  pinMode(IN1,OUTPUT);
  pinMode(IN2,OUTPUT);

  digitalWrite(fan,0);
  digitalWrite(IN1,0);
  digitalWrite(IN2,0);

  Serial.println("Gas sensor is warming up!");
  Serial.println("MQ3 warming up!");
  delay(20000);
}

void loop(){
  
  sensorValue2 = analogRead(MQ2); 
  int chk = DHT.read11(dht11Pin);
  
  Serial.print("Sensor Value: ");
  Serial.print(sensorValue2);

  Serial.print("Temp: ");
  Serial.print(DHT.temperature);
  Serial.print(" | Humi:");
  Serial.println(DHT.humidity);

  if((DHT.temperature)>=35){
    digitalWrite(fan,1);
  }
  else{
    digitalWrite(fan,0);
  }

  if((DHT.temperature)>=50 && (DHT.humidity)<=30 && sensorValue1 > 200){
    Serial.println("Fire Detected");
    sendDataToESP(1,1);
  }
  
  if(sensorValue1 > 200)
  {
    Serial.print(" | Smoke detected!");
    sendDataToESP(1,0);
  }

  sensorValue2 = analogRead(MQ3);
  Serial.print("Sensor Value: ");
  Serial.println(sensorValue2);
  
  Serial.println("");

  if (sensorValue2 < Sober) {
    Serial.println("  |  Status: Stone Cold Sober");
  } else if (sensorValue2 >= Sober && sensorValue2 < Drunk) {
    Serial.println("  |  Status: Drinking but within legal limits");
  } else {
    Serial.println("  |  Status: DRUNK");
    sendDataToESP(0,1);
  }

  Serial.print("Sensor 1 Value: ");
  Serial.print(sensorValue1);

  Serial.print("Sensor 2 Value: ");
  Serial.print(sensorValue2);

  delay(3000);
}

void sendDataToESP(int IN1d,int IN2d){
  if(IN1d==0 && IN2d==0){
    Serial.println("Everything is normal");
    digitalWrite(IN1,0);
    digitalWrite(IN2,0);
  }
  else if(IN1d==1 && IN2d==0){
    Serial.println("Smoke Detected");
    digitalWrite(IN1,1);
    digitalWrite(IN2,0);
  }
  if(IN1d==0 && IN2d==1){
    Serial.println("Alcohol Detected");
    digitalWrite(IN1,0);
    digitalWrite(IN2,1);
  }
  if(IN1d==1 && IN2d==1){
    Serial.println("Fire Detected");
    digitalWrite(IN1,1);
    digitalWrite(IN2,1);
  }
  else{
    Serial.println("Oops Wrong Command");
    digitalWrite(IN1,0);
    digitalWrite(IN2,0);
  }
}
