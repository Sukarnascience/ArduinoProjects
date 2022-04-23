#include <LiquidCrystal_I2C.h>
#include <Arduino.h>
#include <EEPROM.h>

#define CLK 3
#define DIO 4

#define charge 5

int i=0;
int impulsCount=0;
float total_amount=0;

boolean Cstate = false;

LiquidCrystal_I2C lcd(0x27,16,2);

void setup() {

 Serial.begin(9600);

 pinMode(charge,OUTPUT);
 digitalWrite(charge,0);

 lcd.begin();
 
 attachInterrupt(0,incomingImpuls, FALLING);
 EEPROM.get(0, total_amount);

}

void incomingImpuls()
{
  impulsCount=impulsCount+1;
  i=0;
}

void loop() {
  i=i+1;

  Serial.print("i=");
  Serial.print(i);
  Serial.print(" Impulses:");
  Serial.print(impulsCount);
  Serial.print(" Total:");
  Serial.println(total_amount);
 
  if (i>=30 and impulsCount==1){
    total_amount=total_amount+2;
    impulsCount=0;
    EEPROM.put(0, total_amount);
    Cstate = true;
  }
   if (i>=30 and impulsCount==2){
    total_amount=total_amount+1;
    impulsCount=0;
    EEPROM.put(0, total_amount);
    Cstate = true;
  }
   if (i>=30 and impulsCount==3){
    total_amount=total_amount+0.5;
    impulsCount=0;
    EEPROM.put(0, total_amount);
    Cstate = true;
  }
   if (i>=30 and impulsCount==4){
    total_amount=total_amount+0.2;
    impulsCount=0;
    EEPROM.put(0, total_amount);
    Cstate = true;
  }
   if (i>=30 and impulsCount==5){
    total_amount=total_amount+0.1;
    impulsCount=0;
    EEPROM.put(0, total_amount);
    Cstate = true;
  }

  if(Cstate){
    digitalWrite(charge,1);
    delay(300000); //5min
    Cstate = false; 
  }
  digitalWrite(charge,0);
}
