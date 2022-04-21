/**
 * Group Name : IPC064 
 * Another    : Sukarna Jana
 * Title      : Soil Moisture Detection
 * 
 * Copyright © 2022 Sukarna jana
 */

#include <dht.h>
#include <LiquidCrystal_I2C.h>

#define moisture A5
#define dhtData 2

#define soilWet 500 
#define soilDry 750

LiquidCrystal_I2C lcd(0x3f,16,2);
dht DHT;

void setup(){
  
  Serial.begin(9600);

  lcd.begin();
  lcd.setCursor(4,0);
  lcd.print("WELCOME");
  lcd.setCursor(1,1);
  lcd.print("to grp. IPC064");

  delay(2000);
  lcd.clear();
  
}

void loop(){

  int chk = DHT.read11(dhtData);
  lcd.setCursor(7, 0);
  lcd.print(DHT.temperature);
  lcd.setCursor(7, 1);
  lcd.print(DHT.humidity);
  lcd.setCursor(0, 0);
  lcd.print("Temp:-");
  lcd.setCursor(0, 1);
  lcd.print("Humi:-");
  Serial.print("Temp: ");
  Serial.print(DHT.temperature);
  Serial.print(" | Humi:");
  Serial.println(DHT.humidity);

  delay(1000);

  lcd.clear();

  int moisture = readSensor();
  Serial.print("Analog Moisture Output: ");
  Serial.println(moisture);

  if (moisture < soilWet) {
    Serial.println("Status: Soil is too wet");
    lcd.setCursor(0, 0);
    lcd.print("Status: Soil is");
    lcd.setCursor(8, 1);
    lcd.print("too wet");
    
  } else if (moisture >= soilWet && moisture < soilDry) {
    Serial.println("Status: Soil moisture is perfect");
    lcd.setCursor(0, 0);
    lcd.print("Status:moisture");
    lcd.setCursor(0, 1);
    lcd.print("is perfect");
  } else {
    Serial.println("Status: Soil is too dry - time to water!");
    lcd.setCursor(0, 0);
    lcd.print("Status: Soil is ");
    lcd.setCursor(8, 1);
    lcd.print("too dry");
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
