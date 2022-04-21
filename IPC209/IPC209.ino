/**
 * Group Name : IPC209
 * Another    : Sukarna Jana
 * Title      : Anti Sleep & Alcohol Detection During Driving
 * 
 * Copyright © 2022 Sukarna jana
 */

int irSensor = 3;
int buzzer = 2;
int engine = 4;
int ALCOHOL_sensor = 5;
int ALCOHOL_detected;  
void setup()
{
  pinMode(irSensor, INPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(engine, OUTPUT);
  pinMode(ALCOHOL_sensor, INPUT);  
}
void loop()
{ 
  int value = digitalRead(irSensor);
  ALCOHOL_detected = digitalRead(ALCOHOL_sensor); 

  if(value == 0 || ALCOHOL_detected == 1)
  {
    digitalWrite(buzzer, 1);
    delay(100);
    digitalWrite(engine,1);
  }
  else 
  {
    digitalWrite(buzzer,0);
    delay(100);
    digitalWrite(engine,00 );
  }
  delay(50);
}
