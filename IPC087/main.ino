/**
 * Group Name : IPC087
 * Another    : Sukarna Jana
 * Title      : Arduino Color Sorter Project
 * 
 * Copyright © 2022 Sukarna jana
 */

// Supporting Libraries
#include <Servo.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Color Sensor
#define s0 2
#define s1 3
#define s2 4
#define s3 5
#define sOut 6

int redFrequency = 0;
int greenFrequency = 0;
int blueFrequency = 0;

// IR Sensor
#define ir 7

// Buzzer
#define buzz 11

// Servo
#define servo1 9
#define servo2 10
Servo collectServo;
Servo dropServo;

int freq = 0;
int color = 0;
LiquidCrystal_I2C lcd(0x3F,16,2);


void setup(){

  Serial.begin(9600);
  
  lcd.begin();
  lcd.setCursor(4,0);
  lcd.print("WELCOME");
  lcd.setCursor(1,1);
  lcd.print("to grp. IPC087");

  pinMode(s0, OUTPUT);
  pinMode(s1, OUTPUT);
  pinMode(s2, OUTPUT);
  pinMode(s3, OUTPUT);
  pinMode(buzz,OUTPUT);
  pinMode(sOut, INPUT);
  pinMode(ir, INPUT);

  collectServo.attach(servo1);
  dropServo.attach(servo2);

  // set color sensor at 20% frequency-scaling
  digitalWrite(s0,HIGH);
  digitalWrite(s1,LOW);

  delay(1000);
  lcd.clear();
  
}


void loop(){
  if(!digitalRead(ir)){

    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print(" R     G      B ");
    
    // Setting RED (R) filtered photodiodes to be read
    digitalWrite(s2,LOW);
    digitalWrite(s3,LOW);
    redFrequency = pulseIn(sOut, LOW);
    lcd.setCursor(0,1);
    lcd.print(redFrequency);
    delay(100);
  
    // Setting GREEN (G) filtered photodiodes to be read
    digitalWrite(s2,HIGH);
    digitalWrite(s3,HIGH);
    greenFrequency = pulseIn(sOut, LOW);
    lcd.setCursor(6,1);
    lcd.print(greenFrequency);
    delay(100);
 
    // Setting BLUE (B) filtered photodiodes to be read
    digitalWrite(s2,LOW);
    digitalWrite(s3,HIGH);
    blueFrequency = pulseIn(sOut, LOW);
    lcd.setCursor(13,1);
    lcd.print(blueFrequency);
    delay(100);

    Serial.print(":R=");
    Serial.print(redFrequency);
    Serial.print("|G=");
    Serial.print(greenFrequency);
    Serial.print("|B=");
    Serial.print(blueFrequency);
    Serial.println(":");

    sortColor(redFrequency,greenFrequency,blueFrequency);
    
  }
  else{
    lcd.setCursor(0,0);
    lcd.print("Oops! Cartilage");
    lcd.setCursor(0,1);
    lcd.print("  is empty :(  ");
    collectServo.write(115);
    dropServo.write(50);
    digitalWrite(buzz,1);
  }
  delay(500);
  digitalWrite(buzz,0);
}

void sortColor(int red, int green, int blue){

  collectServo.write(115);
  delay(500);
  
  for(int i = 115; i > 65; i--) {
    collectServo.write(i);
    delay(2);
  }
  delay(500);

  if(red<45 && red>32 && green<65 && green>55){
    dropServo.write(50); // Red
  }
  else if(green<55 && green>43 && blue<47 && blue>35){
    dropServo.write(75); // Orange
  }
  else if(red<53 && red>40 && green<53 && green>40){
    dropServo.write(100); // Green
  }
  else if(red<38 && red>24 && green<44 && green>30){
    dropServo.write(125); // Yellow
  }
  else if(red<56 && red>46 && green<65 && green>55){
    dropServo.write(150); // Brown
  }
  else if (green<58 && green>45 && blue<40 && blue>26){
    dropServo.write(175); // Blue
  }
  delay(300);
  
  for(int i = 65; i > 29; i--) {
    collectServo.write(i);
    delay(2);
  } 
  delay(200);
  
  for(int i = 29; i < 115; i++) {
    collectServo.write(i);
    delay(2);
  }
  
}
