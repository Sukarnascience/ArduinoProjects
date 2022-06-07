const int trigPin = 2;
const int echoPin = 3;
const int buzz = 7;
const int vibrate = 4;

// defines variables
long duration;
int distance;

void setup() {
pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
pinMode(echoPin, INPUT); // Sets the echoPin as an Input
pinMode(vibrate,OUTPUT);
pinMode(buzz,OUTPUT);
Serial.begin(9600); // Starts the serial communication
}

void loop() {
// Clears the trigPin
digitalWrite(trigPin, LOW);
delayMicroseconds(2);

// Sets the trigPin on HIGH state for 10 micro seconds
digitalWrite(trigPin, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin, LOW);

// Reads the echoPin, returns the sound wave travel time in microseconds
duration = pulseIn(echoPin, HIGH);

// Calculating the distance
distance= duration*0.034/2;

// Prints the distance on the Serial Monitor
Serial.print("Distance: ");
Serial.println(distance);
if(distance<=30){
  Serial.print(distance);
  digitalWrite(buzz,1);
  digitalWrite(vibrate,1);
  tone(buzz,220,100);
}
else{
  digitalWrite(buzz,0);
  digitalWrite(vibrate,0);
}

}
