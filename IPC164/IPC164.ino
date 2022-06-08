/*
 * Components :
 * 
 * DHT11 
 * data --> 8
 * 
 * Buzxer
 * +ve --> 9
 * 
 * Warning Led
 * +ve --> 10
 * 
 * MQ06
 * D0 --> 11
 * 
 * LCD i2c
 * SDA --> SDA
 * SCL --> SCL
 * 
 * Relay
 * INPUT --> 12
 * 
 * SIM800C
 * TXD --> 3
 * RXD --> 2
 * 
 */

#include <Wire.h>
#include <dht.h>
#include <LiquidCrystal_I2C.h>
#include <SoftwareSerial.h>

#define mq06 11
#define buzz 9
#define wLed 10
#define rely 12
#define temp 13

LiquidCrystal_I2C lcd(0x27,16,2);
SoftwareSerial sim800l(3,2); 
dht DHT;

void setup(){
  lcd.begin();
  Serial.begin(9600);
  sim800l.begin(9600);
  
  lcd.setCursor(4,0);
  lcd.print("WELCOME");
  lcd.setCursor(1,1);
  lcd.print("to grp. IPC164");
  Serial.println("Staring...");

  pinMode(mq06,INPUT);
  pinMode(buzz,OUTPUT);
  pinMode(wLed,OUTPUT);
  pinMode(rely,OUTPUT);

  delay(2000);
  lcd.clear();
  lcd.setCursor(4,0);
  lcd.print("Getting ready...");
  Serial.println("Getting it Ready");
  func();
  delay(4000);
  Serial.println("Started");
  func();
  Serial.println();
  lcd.clear();
  
}

void loop(){
  boolean x = isSmoke();
  boolean y = isHeat();
  if(x && !y){
    lcd.setCursor(0,0);
    lcd.print(" Everything is: ");
    lcd.setCursor(0,1);
    lcd.print("     NORMAL     ");
    func();
  }
   else{
    lcd.setCursor(0,0);
    lcd.print(" Fire Detected ");
    func();
    sendMsg();
    beep();
   }

  delay(5000);
  lcd.clear();
}

boolean isSmoke(){
  Serial.println("MQ06 Sensor Value:");
  if(digitalRead(mq06)){
    Serial.println("Smoke Detected");
    Serial.println();
    return true;
  }
  else{
    Serial.println("No Smoke Detected");
    Serial.println();
    return false;
  }
}

boolean isHeat(){
  int see = DHT.read11(temp);
  Serial.println("DHT11 Sensor Value:");
  Serial.print("Temperature :");
  Serial.println(DHT.temperature);
  Serial.print("Humidity :");
  Serial.println(DHT.humidity);
  Serial.println();
  if(DHT.temperature > 50 && DHT.humidity < 50){
    return true;
  }
  else{
    return false;
  } 
}

void func(){
  digitalWrite(wLed,1);
  delay(255);
  digitalWrite(wLed,0);
  delay(255);
}

void beep(){
  digitalWrite(buzz,1);
  delay(500);
  digitalWrite(rely,1);
  delay(2000);
  digitalWrite(buzz,0);
  delay(500);
  digitalWrite(rely,0);
  delay(500);
}

void sendMsg(){
  func();
  Serial.println("Sending MSG");

  sim800l.print("AT+CMGF=1\r");          
  delay(100);
  sim800l.print("AT+CMGS=\"+91xxxxxxxxxx\"\r");  
  delay(500);
  sim800l.print("Fire has been Detected in HOUSE... ");    
  delay(500);
  sim800l.print((char)26);
  delay(500);
  sim800l.println();

  if (sim800l.available()){         
    Serial.write(sim800l.read()); 
  }
  
  Serial.println("MSG Sended ");
  func();
}
