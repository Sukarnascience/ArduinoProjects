// control by a bluetooth (vamsi)

#define leftMA 4    // pin D4 to IN1
#define leftMU 5    // pin D5 to IN2
#define rightMA 6   // pin D6 to IN3
#define rightMU 7   // pin D7 to IN4

/* Data sended by App
front = 'a';
back = 'b';
left = 'c';
right = 'd';
stop = 'e';
*/ 

void setup(){

  pinMode(leftMA,OUTPUT);
  pinMode(leftMU,OUTPUT);
  pinMode(rightMA,OUTPUT);
  pinMode(rightMU,OUTPUT);
    
  delay(2000);
}

void loop(){
  if(Serial.available()>0){
    char data = Serial.read();
    switch(data){
      case 'a':
        moveFront();
        break;
      case 'b':
        moveBack();
        break;
      case 'c':
        moveLeft();
        break;
      case 'd':
        moveRight();
        break;
      case 'e':
        stopMove();
        break;
      default:
        stopMove();
        break;
    }
  }
}


void moveFront(){
  digitalWrite(leftMA,1);
  digitalWrite(leftMU,0);
  digitalWrite(rightMA,1);
  digitalWrite(rightMU,0);
}

void moveBack(){
  digitalWrite(leftMA,0);
  digitalWrite(leftMU,1);
  digitalWrite(rightMA,0);
  digitalWrite(rightMU,1);
}

void moveLeft(){
  digitalWrite(leftMA,0);
  digitalWrite(leftMU,1);
  digitalWrite(rightMA,1);
  digitalWrite(rightMU,0);
}

void moveRight(){
  digitalWrite(leftMA,1);
  digitalWrite(leftMU,0);
  digitalWrite(rightMA,0);
  digitalWrite(rightMU,1);
}

void stopMove(){
  digitalWrite(leftMA,0);
  digitalWrite(leftMU,0);
  digitalWrite(rightMA,0);
  digitalWrite(rightMU,0);
}
