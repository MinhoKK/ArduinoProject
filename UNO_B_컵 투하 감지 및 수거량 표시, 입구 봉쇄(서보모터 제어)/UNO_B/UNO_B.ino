#include <Servo.h>
const int SERVO = 10;
const int trigPin = 11;
const int echoPin = 12;
const int Red = 6;
const int Green = 5;
const int Blue = 3;
const int button = 4;

Servo servo;

volatile float distance = 0;
volatile int cupcount = 0;



void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(button, INPUT);
  Serial.begin(115200);
  servo.attach(SERVO);
  servo.write(180);



}

void loop() {

  int checkButton = digitalRead(button);
  Serial.print("버튼체크");
  Serial.println(checkButton);
  if (checkButton == 0) {
    servo.write(180);
    delay(1);
    cupcount = 0;
  }


  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  unsigned long duration = pulseIn(echoPin, HIGH);
  distance = duration / 58.f;

  Serial.print("거리");
  Serial.println(distance, 2);
  Serial.print("컵카운트:");
  Serial.println(cupcount);

  switch (cupcount) {
    case 0:
      analogWrite(Red, 0);
      analogWrite(Green, 255);
      analogWrite(Blue, 0);
      break;
    case 1:
      analogWrite(Red, 100);
      analogWrite(Green, 255);
      analogWrite(Blue, 0);
      break;
    case 2:
      analogWrite(Red, 255);
      analogWrite(Green, 255);
      analogWrite(Blue, 0);
      break;
    case 3:
      analogWrite(Red, 255);
      analogWrite(Green, 70);
      analogWrite(Blue, 0);
      break;
    case 4:
      analogWrite(Red, 255);
      analogWrite(Green, 0);
      analogWrite(Blue, 0);
      break;
    default:
      analogWrite(Red, 255);
      analogWrite(Green, 0);
      analogWrite(Blue, 0);
      break;
  }

  if (distance <= 5) {
    delay(1500);
    servo.write(3);
    delay(12000);
    servo.write(180);
    delay(1);
    cupcount++;
  }
  
  if (cupcount >= 5) {
    servo.write(3);
    delay(1);
  }


  delay(50);

}
