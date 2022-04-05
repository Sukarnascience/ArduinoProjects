#define startMove 5
#define leftTurn 4
#define errorLED 13

int j = 0;

void setup(){
  Serial.begin(9600);

  pinMode(startMove,OUTPUT);
  pinMode(leftTurn,OUTPUT);
  pinMode(errorLED,OUTPUT);

}

void loop(){
  if (Serial.available() > 0) {
    int info = Serial.read();
    if(info==10){
      error();
    }
    if(info==11){
      digitalWrite(startMove,0);
      j++;
      delay(100);
    }
    else{
      digitalWrite(startMove,1);
    }
    if(j>5){
      digitalWrite(startMove,1);
      digitalWrite(leftTurn,1);
      j = 0;
    }
  }
  else{
    error();
  }
  digitalWrite(leftTurn,0);
  delay(100);
}

void error(){
  for(int i = 0;i<5;i++){
    digitalWrite(errorLED,1);
    delay(100);
    digitalWrite(errorLED,0);
    delay(100);
  }
}
