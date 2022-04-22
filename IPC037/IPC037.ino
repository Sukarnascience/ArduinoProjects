#include <Servo.h>
#include <LiquidCrystal_I2C.h>

#define pee 2
#define noice 3
#define isBaby 4

int Swing = 5;

#define IN1 6
#define IN2 7

/*
 * ESP Signals
 * IN1  IN2  Commands
 *  0    0     -NA-
 *  0    1     baby Pee..ed
 *  1    0     baby is crying
 *  1    1     baby is missing
 */
 
LiquidCrystal_I2C lcd(0x27,16,2);

Servo swingServo;

void setup(){

  Serial.begin(9600);

  pinMode(IN1,OUTPUT);
  pinMode(IN2,OUTPUT);
  
  lcd.begin();
  lcd.setCursor(4,0);
  lcd.print("WELCOME");
  lcd.setCursor(1,1);
  lcd.print("to grp. IPC037");

  pinMode(pee,INPUT);
  pinMode(noice,INPUT);
  pinMode(isBaby,INPUT);

  swingServo.attach(Swing);
  swingServo.write(90);
  delay(2000);
  lcd.clear();
  
}

void loop(){

  if(!digitalRead(isBaby)){
    lcd.setCursor(0,0);
    lcd.print("Baby is not");
    lcd.setCursor(0,1);
    lcd.print("there");
    delay(2000);
    lcd.clear();
    sendDataToESP(1,1);
  }
  else{
    sendDataToESP(0,0);
    if(digitalRead(noice)){
      lcd.setCursor(0,0);
      lcd.print("Baby is Crying");
      delay(2000);
      lcd.clear();
      sendDataToESP(1,0);
    }
    else if(digitalRead(pee)){
      lcd.setCursor(0,0);
      lcd.print("Baby has peed");
      delay(2000);
      lcd.clear();
      sendDataToESP(0,1);
    }
    swing();
  }
  
}

void swing(){

 for(int i =90;i>=60;i--){
  swingServo.write(i);
  delay(50);
 }
 delay(50);
 for(int i =60;i<=120;i++){
  swingServo.write(i);
  delay(50);
 }
 delay(50);
 for(int i =120;i<=90;i--){
  swingServo.write(i);
  delay(50);
 }
 swingServo.write(90);
  
}


void sendDataToESP(int IN1d,int IN2d){
  if(IN1d==0 && IN2d==0){
    Serial.println("Every thing is fine");
    digitalWrite(IN1,0);
    digitalWrite(IN2,0);
  }
  else if(IN1d==1 && IN2d==0){
    Serial.println("baby is crying");
    digitalWrite(IN1,1);
    digitalWrite(IN2,0);
  }
  if(IN1d==0 && IN2d==1){
    Serial.println("baby Pee..ed in cot");
    digitalWrite(IN1,0);
    digitalWrite(IN2,1);
  }
  if(IN1d==1 && IN2d==1){
    Serial.println("Baby is missing");
    digitalWrite(IN1,1);
    digitalWrite(IN2,1);
  }
  else{
    Serial.println("Ooops!");
    digitalWrite(IN1,0);
    digitalWrite(IN2,0);
  }
}
