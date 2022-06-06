/*
 * Pin Connections :
 * leds are connected from D3 to D12
 * buzzer at D2
 * RFID EM-18 TX pin to RX Pin of UNO
 * 
 * Cards Datas :
 * Card0: 0009041468 137,63036 ==> Card ID: 250089F63C66
 * Card1: 0009009282 137,30850 ==> Card ID: 250089788256
 * Card2: 0002459050 037,34218 ==> Card ID: 0B002585AA01
 * Card3: 0003040595 137,62163 ==> Card ID: 250089F2D38D
 * Card4: 0009019457 137,41025 ==> Card ID: 250089A0414D
 * Card5: 0009070991 138,27023 ==> Card ID: 25008A698F49
 * Card6: 0008999822 137,21390 ==> Card ID: 250089538E71
 * Card7: 0009002487 137,24055 ==> Card ID: 2500895DF706
 * Card8: 0009076887 138,32919 ==> Card ID: 25008A8097B8
 * Card9: 0009063484 138,19516 ==> Card ID: 25008A4C3CDF 
 */

#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x3f,16,2);

#define buzz 2

String card1 = "250089F63C66";
String card2 = "250089788256";
String card3 = "0B002585AA01";
String card4 = "250089F2D38D";
String card5 = "250089A0414D";
String card6 = "25008A698F49";
String card7 = "250089538E71";
String card8 = "2500895DF706";
String card9 = "25008A8097B8";
String card10 = "25008A4C3CDF";

int detect[10] = {3,4,5,6,7,8,9,10,11,12};

int count = 0;                                       
char input[12];                                     
boolean flag = 0;      
                                 
void setup()
{
   lcd.begin();
   
   lcd.setCursor(4,0);
   lcd.print("WELCOME");
   lcd.setCursor(1,1);
   lcd.print("to grp. IPC084");
   
   Serial.begin(9600);      
   for(int i=0; i<10; i++){
    pinMode(detect[i],OUTPUT);
    digitalWrite(detect[i],1);
    delay(100);                           
   }
   delay(500);
   for(int i=0; i<10; i++){
    digitalWrite(detect[i],0);
    delay(100); 
   }
   delay(500);
   pinMode(buzz,OUTPUT);
   beep();
   delay(1000);
   
   lcd.clear();
}
void loop()
{
  if(Serial.available())
  {
    count = 0;
    while(Serial.available() && count < 12)       
    {
       input[count] = Serial.read();
       count++;
       delay(5);
    }
    Serial.println(input);                           
      
    if((input[0] ^ input[2] ^ input[4] ^ input[6] ^ input[8] == input[10]) && 
       (input[1] ^ input[3] ^ input[5] ^ input[7] ^ input[9] == input[11])){
          Serial.println("No Error");
          if(card1==input){
            blinkPro(detect[0]);
            lcd.setCursor(0,0);
            lcd.print("Item ID:001");
            lcd.setCursor(0,1);
            lcd.print("Chips Added");
          }
          else if(card2==input){
            blinkPro(detect[1]);
            lcd.setCursor(0,0);
            lcd.print("Item ID:010");
            lcd.setCursor(0,1);
            lcd.print("ChokiChoki Added");
          }
          else if(card3==input){
            blinkPro(detect[2]);
            lcd.setCursor(0,0);
            lcd.print("Item ID:011");
            lcd.setCursor(0,1);
            lcd.print("Gone Mad Added");
          }
          else if(card4==input){
            blinkPro(detect[3]);
            lcd.setCursor(0,0);
            lcd.print("Item ID:100");
            lcd.setCursor(0,1);
            lcd.print("Mixture Added");
          }
          else if(card5==input){
            blinkPro(detect[4]);
            lcd.setCursor(0,0);
            lcd.print("Item ID:101");
            lcd.setCursor(0,1);
            lcd.print("A4 Papers Added");
          }
          else if(card6==input){
            blinkPro(detect[5]);
            lcd.setCursor(0,0);
            lcd.print("Item ID:110");
            lcd.setCursor(0,1);
            lcd.print("Bingo Added");
          }
          else if(card7==input){
            blinkPro(detect[6]);
            lcd.setCursor(0,0);
            lcd.print("  Item Out Of  ");
            lcd.setCursor(0,1);
            lcd.print("Stock");
            beep();
          }
          else if(card8==input){
            blinkPro(detect[7]);
            lcd.setCursor(0,0);
            lcd.print("  Item Out Of  ");
            lcd.setCursor(0,1);
            lcd.print("Stock");
            beep();
          }
          else if(card9==input){
            blinkPro(detect[8]);
            lcd.setCursor(0,0);
            lcd.print("  Invalid Item  ");
            beep();
          }
          else if(card10==input){
            blinkPro(detect[9]);
            lcd.setCursor(0,0);
            lcd.print("  Invalid Item  ");
            beep();
          }
          else{
            beep();
          }
    }
    else{
          Serial.println("Error");   
          beep();
    }   
   }
   delay(3000);
   lcd.clear();
}

void beep(){
  digitalWrite(buzz,1);
  delay(100);
  digitalWrite(buzz,0);
  delay(100);
  digitalWrite(buzz,1);
  delay(100);
  digitalWrite(buzz,0);
  delay(100);
}

void blinkPro(int pin){
  digitalWrite(pin,1);
  delay(100);
  digitalWrite(pin,0);
  delay(100);
  digitalWrite(pin,1);
  delay(100);
  digitalWrite(pin,0);
  delay(100);
}
