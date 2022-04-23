#include <Servo.h>

Servo servo01;
Servo servo02;
Servo servo03;

void setup() {
  servo01.attach(3);
  servo02.attach(5);
  servo03.attach(6);

  servo01.write(0);
  servo02.write(30);
  servo02.write(30);
}

void loop(){
  moveUP();
  wave();
  moveDown();
  fisbum();
  delay(2000);
}

void moveUP(){
  for(int i = 30;i<=90;i++){
    servo02.write(i);
    servo03.write(i);
    delay(100);
  }
}
void moveDown(){
  for(int i = 90;i>=0;i--){
    servo02.write(i);
    servo03.write(i);
    delay(100);
  }
}
void wave(){
  for(int i = 90;i<=130;i++){
    servo03.write(i);
    delay(100);
  }
  for(int i = 130;i>=60;i--){
    servo03.write(i);
    delay(100);
  }
  for(int i = 90;i<=130;i++){
    servo03.write(i);
    delay(100);
  }
  for(int i = 130;i>=60;i--){
    servo03.write(i);
    delay(100);
  }
  for(int i = 0;i<=30;i++){
    servo01.write(i);
    delay(100);
  }
  for(int i = 30;i>=0;i--){
    servo01.write(i);
    delay(100);
  }
  for(int i = 0;i<=30;i++){
    servo01.write(i);
    delay(100);
  }
  for(int i = 30;i>=0;i--){
    servo01.write(i);
    delay(100);
  }
}
void fisbum(){
  for(int i = 30;i<=90;i++){
    servo02.write(i);
    servo03.write(i);
    delay(100);
  }
  for(int i = 90;i<=110;i++){
    servo02.write(i);
    delay(100);
  }
  for(int i = 110;i>=90;i--){
    servo02.write(i);
    delay(100);
  }
  moveDown();
}
