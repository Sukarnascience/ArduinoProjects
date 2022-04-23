#include <LiquidCrystal_I2C.h>
#include <dht.h>

LiquidCrystal_I2C lcd(0x27,16,2);
dht DHT;

#define moisture A5
#define ph A4
#define dhtData 2

#define soilWet 500 
#define soilDry 750

int state1 = 0;
int state2 = 0;
int state3 = 0;

float calibration_value = 21.34;
int phval = 0; 
unsigned long int avgval; 
int buffer_arr[10],temp;

#define IN1 6
#define IN2 7

/*
 * ESP Signals
 * IN1  IN2  Commands
 *  0    0     -NA-
 *  0    1     Cattail plant
 *  1    0     tulsi
 *  1    1     cactus
 */

void setup(){

  Serial.begin(9600);
  
  lcd.begin();
  lcd.setCursor(4,0);
  lcd.print("WELCOME");
  lcd.setCursor(1,1);
  lcd.print("to grp. IPC245");

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
  int temp = DHT.temperature;
  int humi = DHT.humidity;

  delay(1000);

  lcd.clear();

  int moisture = readSensor();
  Serial.print("Analog Moisture Output: ");
  Serial.println(moisture);
  lcd.setCursor(0, 0);
  lcd.print("Moisture level");
  lcd.setCursor(0, 1);
  lcd.print(moisture);

  delay(1000);

  lcd.clear();

  for(int i=0;i<10;i++) 
 { 
 buffer_arr[i]=analogRead(ph);
 delay(30);
 }
 for(int i=0;i<9;i++)
 {
 for(int j=i+1;j<10;j++)
 {
 if(buffer_arr[i]>buffer_arr[j])
 {
 temp=buffer_arr[i];
 buffer_arr[i]=buffer_arr[j];
 buffer_arr[j]=temp;
 }
 }
 }
 avgval=0;
 for(int i=2;i<8;i++)
 avgval+=buffer_arr[i];
 float volt=(float)avgval*5.0/1024/6;
 float ph_act = -5.70 * volt + calibration_value;
 lcd.setCursor(0, 0);
 lcd.print("pH Val:");
 lcd.setCursor(8, 0);
 lcd.print(ph_act);
 
 delay(1000);

 lcd.clear();
 
  if (moisture < soilWet) {
    Serial.println("Status: Soil is too wet");
    // Cattail plant
    state2 = 1;
    
  } else if (moisture >= soilWet && moisture < soilDry) {
    Serial.println("Status: Soil moisture is perfect");
    state2 = 2;
    // tulsi
  } else {
    Serial.println("Status: Soil is too dry - time to water!");
    state2 = 3;
    // cactus
  }

  if(temp <= 25 && humi>= 50){
    // Cattail plant
    state1 = 1;
  }
  else if(temp <= 50 && humi<= 50){
    state1 = 2;
    // tulsi
  }
  else{
    state1 = 3;
    // cactus
  }

  if(ph_act>=5 && ph_act<6){
    // Cattail plant
    state3 = 1;
  }
  else if(ph_act>=6 && ph_act<7){
    // tulsi
    state3 = 2;
  }
  else if(ph_act>=7 && ph_act<=9){
    state3 = 3;
    // cactus
  }

  if(state1 == 1 && state2 == 1 && state3 == 1){
    // Cattail plant
    sendDataToESP(1,0);
  }
  else if(state1 == 2 && state2 == 2 && state3 == 2){
    // tulsi
    sendDataToESP(0,1);
  }
  else if(state1 == 3 && state2 == 3 && state3 == 3){
    // cactus
    sendDataToESP(1,1);
  }

  delay(1000);
  state1 = 0;
  state2 = 0;
  state3 = 0;
  lcd.clear();
}
 

int readSensor() {
  digitalWrite(moisture, HIGH);
  delay(10);           
  int val = analogRead(moisture); 
  digitalWrite(moisture, LOW);  
  return val;         
}



void sendDataToESP(int IN1d,int IN2d){
  if(IN1d==0 && IN2d==0){
    Serial.println("Every thing is fine");
    digitalWrite(IN1,0);
    digitalWrite(IN2,0);
  }
  else if(IN1d==1 && IN2d==0){
    Serial.println("Cattail can be grown in this place");
    digitalWrite(IN1,1);
    digitalWrite(IN2,0);
  }
  if(IN1d==0 && IN2d==1){
    Serial.println("tulsi can be grown in this place");
    digitalWrite(IN1,0);
    digitalWrite(IN2,1);
  }
  if(IN1d==1 && IN2d==1){
    Serial.println("cactus can be grown in this place");
    digitalWrite(IN1,1);
    digitalWrite(IN2,1);
  }
  else{
    Serial.println("Ooops!");
    digitalWrite(IN1,0);
    digitalWrite(IN2,0);
  }
}
