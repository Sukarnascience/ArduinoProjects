/**
 * Group Name : IPC080
 * Another    : Sukarna Jana
 * Title      : Anti Sleep 
 * 
 * Copyright © 2022 Sukarna jana
 */

int irSensor = 3;
int buzzer = 2;
int engine = 4;
void setup()
{
  pinMode(irSensor, INPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(engine, OUTPUT);
}
void loop()
{ 
  int value = digitalRead(irSensor);

  if(value == 0)
  {
    digitalWrite(buzzer, 1);
    delay(100);
    digitalWrite(engine,1);
  }
  else 
  {
    digitalWrite(buzzer,0);
    delay(100);
    digitalWrite(engine,0);
  }
  delay(50);
}
