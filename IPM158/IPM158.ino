#define ma1 8
#define mb1 9
#define ma2 10
#define mb2 11

long duration;
int distance;

const int trigPin = 7;
const int echoPin = 6;

void setup(){
  pinMode(ma1,OUTPUT);
  pinMode(mb1,OUTPUT);
  pinMode(ma2,OUTPUT);
  pinMode(mb2,OUTPUT);
}

void loop(){
  if(calculateDistance()<=30){
    moveBack();
    delay(500);
    turnBit();
  }
  else{
    moveFront();
  }
}

void moveFront(){
  digitalWrite(ma1,1);
  digitalWrite(mb1,0);
  digitalWrite(ma2,0);
  digitalWrite(mb2,1);
}

void moveBack(){
  digitalWrite(ma1,0);
  digitalWrite(mb1,1);
  digitalWrite(ma2,1);
  digitalWrite(mb2,0);
}

void turnBit(){
  digitalWrite(ma1,1);
  digitalWrite(mb1,0);
  digitalWrite(ma2,1);
  digitalWrite(mb2,0);
  //delay(200);
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
