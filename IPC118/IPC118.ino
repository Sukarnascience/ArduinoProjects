#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define capPin A5
#define buz 9
#define pulsePin A4

#define led 10

#define OLED_WIDTH 128
#define OLED_HEIGHT 64
#define OLED_ADDR   0x3C

Adafruit_SSD1306 display(OLED_WIDTH, OLED_HEIGHT);

long sumExpect=0;
long ignor=0; 
long diff=0;        
long pTime=0;
long buzPeriod=0; 

void setup() 
{
  display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR);
  Serial.begin(9600);
  pinMode(pulsePin, OUTPUT); 
  digitalWrite(pulsePin, LOW);
  pinMode(capPin, INPUT);  
  pinMode(buz, OUTPUT);
  digitalWrite(buz, LOW);
  pinMode(led, OUTPUT);
}

void loop() 
{
  int minval=1023;
  int maxval=0;
  long unsigned int sum=0;
  for (int i=0; i<256; i++)
  {
    pinMode(capPin,OUTPUT);
    digitalWrite(capPin,LOW);
    delayMicroseconds(20);
    pinMode(capPin,INPUT);
    applyPulses();
    
    int val = analogRead(capPin); 
    minval = min(val,minval);
    maxval = max(val,maxval);
    sum+=val;
    
    long unsigned int cTime=millis();
    char buzState=0;
    if (cTime<pTime+10)
    {
      if (diff>0)
        buzState=1;
      else if(diff<0)
        buzState=2;
    }
    if (cTime>pTime+buzPeriod)
    {
      if (diff>0)
      buzState=1;
      else if (diff<0)
      buzState=2;
      pTime=cTime;   
    }
    if (buzPeriod>300)
    buzState=0;

    if (buzState==0)
    {
      digitalWrite(led, LOW);
      runOnOLED(2,0,0,"METAL NOT DETECTED");
      display.display();
      noTone(buz);
    }  
    else if (buzState==1)
    {
      tone(buz,2000);
      digitalWrite(led, HIGH);
      runOnOLED(2,0,0,"METAL DETECTED");
      display.display();
    }
    
    else if (buzState==2)
    {
      tone(buz,500);
      digitalWrite(led, HIGH);
      runOnOLED(2,0,0,"METAL DETECTED");
      display.display();
    }
  }

  sum-=minval; 
  sum-=maxval;
  
  if (sumExpect==0) 
  sumExpect=sum<<6; //set sumExpect to expected value
  long int avgsum=(sumExpect+32)>>6; 
  diff=sum-avgsum;
  if (abs(diff)<avgsum>>10)
  {
    sumExpect=sumExpect+sum-avgsum;
    ignor=0;
  } 
  else 
    ignor++;
  if (ignor>64)
  { 
    sumExpect=sum<<6;
    ignor=0;
  }
  if (diff==0) 
    buzPeriod=1000000;
  else 
  buzPeriod=avgsum/(2*abs(diff));    
  display.clearDisplay();
}

void applyPulses()
{
    for (int i=0;i<3;i++) 
    {
      digitalWrite(pulsePin,HIGH); //take 3.5 uS
      delayMicroseconds(3);
      digitalWrite(pulsePin,LOW);  //take 3.5 uS
      delayMicroseconds(3);
    }
}

void runOnOLED(int textSize, int x, int y, String data){
  display.setTextSize(textSize);
  display.setTextColor(WHITE);
  display.setCursor(x, y);
  display.println(data);
}
