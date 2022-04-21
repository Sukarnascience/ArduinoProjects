/**
 * Group Name : IPM058 + IPC197
 * Another    : Sukarna Jana
 * Title      : Smart Plant Watering System 
 * 
 * Copyright © 2022 Sukarna jana
 */

#include <LiquidCrystal.h>

#define moisture A0
#define green 9
#define red 8
#define pump 10

#define soilWet 500 
#define soilDry 750

const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup(){
  
  Serial.begin(9600);

  pinMode(red,OUTPUT);
  pinMode(green,OUTPUT);
  pinMode(pump,OUTPUT);

  digitalWrite(red,0);
  digitalWrite(green,0);
  digitalWrite(pump,0);

  lcd.begin(16, 2);
  lcd.setCursor(4,0);
  lcd.print("WELCOME");
  lcd.setCursor(1,1);
  lcd.print("to grp. IPM058");

  delay(2000);
  lcd.clear();
  
}

void loop(){
  
  int moisture = readSensor();
  Serial.print("Analog Moisture Output: ");
  Serial.println(moisture);

  if (moisture < soilWet) {
    Serial.println("Status: Soil is too wet");
    lcd.setCursor(0, 0);
    lcd.print("Status: Soil is");
    lcd.setCursor(8, 1);
    lcd.print("too wet");
    digitalWrite(red,1);
    digitalWrite(green,0);
    digitalWrite(pump,1);
    
  } else if (moisture >= soilWet && moisture < soilDry) {
    Serial.println("Status: Soil moisture is perfect");
    lcd.setCursor(0, 0);
    lcd.print("Status:moisture");
    lcd.setCursor(0, 1);
    lcd.print("is perfect");
    digitalWrite(red,0);
    digitalWrite(green,1);
    digitalWrite(pump,1);
  } else {
    Serial.println("Status: Soil is too dry - time to water!");
    lcd.setCursor(0, 0);
    lcd.print("Status: Soil is ");
    lcd.setCursor(8, 1);
    lcd.print("too dry");
    digitalWrite(red,1);
    digitalWrite(green,1);
    digitalWrite(pump,0);
  }

  delay(1000);

  lcd.clear();
  
}

int readSensor() {
  digitalWrite(moisture, HIGH);
  delay(10);           
  int val = analogRead(moisture); 
  digitalWrite(moisture, LOW);  
  return val;         
}
