#define startMove 10
#define leftTurn 11
#define errorLED 13
#define beep 12
#define motion 9

int j = 0;

void setup(){

  pinMode(startMove,OUTPUT);
  pinMode(leftTurn,OUTPUT);
  pinMode(errorLED,OUTPUT);
  pinMode(motion,INPUT);
  pinMode(beep,OUTPUT);

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
    //int infoFromBoard = Serial.parseInt();
    char infoFromBoard = Serial.read();
    int detectMove = digitalRead(motion);
    if(detectMove){
      Serial.println("Motion Detect");
    }
    else{
      Serial.println("NO Motion Detect");
    }
    Serial.print("Data is :");
    Serial.println(infoFromBoard);
    //if(infoFromBoard==11){
    if(infoFromBoard=='S' || detectMove==0){
      digitalWrite(startMove,1);
      Serial.println("Stoping");
      j++;
      delay(10);
    }
    //else if(infoFromBoard==10){
    else if(infoFromBoard=='E'){
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
      digitalWrite(beep,1);
      delay(100);
      j = 0;
    }
  }
  else{
    digitalWrite(startMove,1);
    error();
  }
  digitalWrite(leftTurn,1);
  digitalWrite(beep,0);
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
