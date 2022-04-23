#define light 2
#define clap 3

int data = 0;
int stateOfL = 0;

void setup(){
  pinMode(light,OUTPUT);
  pinMode(clap,INPUT);
}

void loop(){
  data = digitalRead(clap);
  if(data){
    stateOfL = 1;
  }
  if(stateOfL==1){
    while(1==1){
      digitalWrite(light,1);
      if(digitalRead(clap)){
        stateOfL = 0;
        break;
      }
    }
  }
  if(stateOfL==0){
    digitalWrite(light,0);
  }
}
