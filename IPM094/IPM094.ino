/*
 * : Pins Connections :
 * --------LCD--------
 * LCD RS pin to digital pin 12
 * LCD Enable pin to digital pin 11
 * LCD D4 pin to digital pin 5
 * LCD D5 pin to digital pin 4
 * LCD D6 pin to digital pin 3
 * LCD D7 pin to digital pin 2
 * LCD R/W pin to ground
 * LCD VSS pin to ground
 * LCD VCC pin to 5V
 * 10K resistor:
 * ends to +5V and ground
 * wiper to LCD VO pin (pin 3)
 * --------Temp. Sensor--------
 * LM35 Out pin to Analog pin A0 
 * LM35 VCC pin to pin 3.3v or 5v
 * LM35 GND pin to GND (ground)
 * --------PIR Sensor-------
 * PIR Out pin to digital pin 4
 * PIR VCC pin to pin 3.3v or 5v
 * PIR GND pin to GND (ground)
 * --------LED--------
 * A(p)ve+ pin to digital pin 3
 * C(n)ve- pin to GND (ground)
 * --------Buzzer--------
 * A(p)ve+ pin to digital pin 2
 * C(n)ve- pin to GND (ground)
 * --------Motor--------
 * Note: dont connect motor directly to IC board
 * A(p)ve+ pin to digital pin 5
 * C(n)ve- pin to GND (ground)
 */

#include <LiquidCrystal.h>

#define temp A0
#define buzz 2
#define light 3
#define movement 4
#define motor 5

const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

const int trigPin = 7;
const int echoPin = 6;

long duration;
int distance;

void setup() {
  Serial.begin(9600);
  lcd.begin(16, 2);

  pinMode(temp, INPUT); 
  pinMode(movement,INPUT);
  pinMode(buzz,OUTPUT);
  pinMode(light,OUTPUT);
  
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  lcd.setCursor(0, 0);
  lcd.print("    WEL-COME    ");
  delay(2000);
  lcd.clear();
}
int stateNow = 0;
void loop() {
  if(digitalRead(movement)){
    lcd.setCursor(0, 0);
    lcd.print("Motion Detected");
    stateNow = 1;
    delay(2000);
    lcd.clear();
  }
  if(stateNow){
    while(digitalRead(movement)){
      int dis = calculateDistance();
      if(dis>30){
        lcd.setCursor(0, 0);
        lcd.print("Come Closer,need");
        lcd.setCursor(0, 0);
        lcd.print("to see the temp");
        delay(2000);
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Body Temp. is:");
        lcd.setCursor(0, 1);
        lcd.print(tempOfBody());
        lcd.setCursor(15, 1);
        lcd.print("C");
        delay(2000);
        if(tempOfBody()>45){
          lcd.clear();
          lcd.setCursor(0,0);
          lcd.print("Your Temp. is");
          lcd.setCursor(0,1);
          lcd.print("HIGH");
          digitalWrite(buzz,1);
          digitalWrite(light,1);
          delay(3000);
          digitalWrite(buzz,0);
          digitalWrite(light,1);
        }
        else{
          lcd.clear();
          lcd.setCursor(0,0);
          lcd.print("Everythng is");
          lcd.setCursor(0,1);
          lcd.print("fine you can GO");
          digitalWrite(motor,1);
          delay(2000);
          digitalWrite(motor,0);
        }
      }
    }
  }
  stateNow=0;
}

int calculateDistance(){
  
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = duration*0.034/2;
    
  return distance;
}

int tempOfBody(){
  
  int sensorValue = analogRead(temp);
  float voltage = sensorValue * 5.0;
  voltage /= 1024.0;
  float temp_in_C = (voltage - 0.5) * 100 ;
  Serial.print("The Temp. is :");
  Serial.println(temp_in_C);
  
  return temp_in_C;
}
