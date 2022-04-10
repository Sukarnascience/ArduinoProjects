#define startMove 5
#define leftTurn 4
#define errorLED 13

int j = 0;

void setup(){

  pinMode(startMove,OUTPUT);
  pinMode(leftTurn,OUTPUT);
  pinMode(errorLED,OUTPUT);

  Serial.begin(9600);
  Serial.println("© Sukarna Jana 2022");
  Serial.println("1. In D13 pin LED blinks then some error has happened...");
  Serial.println("2. Command 11 for error");
  Serial.println("3. Command 10 for stop");
  Serial.println("4. If Command 10 called 5 times then move the car to left");
  Serial.println("---------------------------------------------------------");
  
}

void loop(){
  if (Serial.available()) {
    int infoFromBoard = Serial.parseInt();
    Serial.print("Data is :");
    Serial.println(infoFromBoard);
    if(infoFromBoard==11){
      digitalWrite(startMove,1);
      Serial.println("Stoping");
      j++;
      delay(10);
    }
    else if(infoFromBoard==10){
      Serial.println("Something went wrong");
      error();
    }
    else{
      digitalWrite(startMove,0);
      Serial.println("Moving");
    }
    if(j>5){
      digitalWrite(startMove,0);
      Serial.print("Moving");
      digitalWrite(leftTurn,0);
      Serial.println("and moving to left");
      delay(100);
      j = 0;
    }
  }
  else{
    digitalWrite(startMove,1);
    error();
  }
  digitalWrite(leftTurn,1);
  delay(50);
}

void error(){
  for(int i = 0;i<5;i++){
    digitalWrite(errorLED,1);
    delay(100);
    digitalWrite(errorLED,0);
    delay(100);
  }
}
