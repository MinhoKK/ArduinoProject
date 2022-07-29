#include <Stepper.h>

Stepper stepper(400, 8, 10, 9, 11);

const int trigPin = 5;
const int echoPin = 6;

void setup(){ 
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  Serial.begin(115200);
  stepper.setSpeed(30);
}

void loop(){
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  unsigned long duration = pulseIn(echoPin, HIGH);
  unsigned long distance = duration/58.f;

  Serial.println(distance);
    
  if(distance<=5.0 && distance>0){
    int steps = 420;
    stepper.step(steps);
    delay(2000);

    
    stepper.step(-(steps*2));
    delay(1000);

    stepper.step(steps);
    delay(1000);
  }
}
