#define MOTOR_R_a 3
#define MOTOR_R_b 9
#define MOTOR_L_a 10
#define MOTOR_L_b 11
#define MOTOR_SPEED 150
#define MOTOR_SPEED_HIGH 230
#define MOTOR_SPEED_LOW 230

#define EchoPin 13
#define TrigPin 12

const int IR_Left = A1;
const int IR_Right = A0;

void setup() {
  // put your setup code here, to run once:

  TCCR1B = TCCR1B & 0b11111000 | 0x05;  //저속주행이 가능하도록 모터A PWM 주파수 변경
  TCCR2B = TCCR2B & 0b11111000 | 0x07;  //저속주행이 가능하도록 모터B PWM 주파수 변경

  pinMode(MOTOR_R_a, OUTPUT);
  pinMode(MOTOR_R_b, OUTPUT);
  pinMode(MOTOR_L_a, OUTPUT);
  pinMode(MOTOR_L_b, OUTPUT);

  pinMode(TrigPin, OUTPUT);
  pinMode(EchoPin, INPUT);

  pinMode(IR_Left, INPUT);
  pinMode(IR_Right, INPUT);

  Serial.begin(115200);
}

void loop() {
  // put your main code here, to run repeatedly:

  //========================MicroSound============================//

  digitalWrite(TrigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(TrigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(TrigPin, LOW);

  unsigned long duration = pulseIn(EchoPin, HIGH);
  float distance = duration / 58.f;

  //Serial.print(distance, 2);
  //Serial.println("cm");
  //========================MicroSound============================//

  //==============================MOTOR===========================//
  int value_Left = analogRead(IR_Left);
  int value_Right = analogRead(IR_Right);

  boolean Line_L = (value_Left <= 700);
  boolean Line_R = (value_Right <= 700);

  if (distance >= 20.0f)
  {
    if (Line_L && Line_R)
    {
      analogWrite(MOTOR_R_a, MOTOR_SPEED);
      analogWrite(MOTOR_L_a, MOTOR_SPEED);

      analogWrite(MOTOR_R_b,  0);
      analogWrite(MOTOR_L_b,  0);
    }
    else if (Line_L && !Line_R)
    {
      analogWrite(MOTOR_R_a, MOTOR_SPEED_HIGH);
      analogWrite(MOTOR_R_b, 0);

      analogWrite(MOTOR_L_a, 0);
      analogWrite(MOTOR_L_b, MOTOR_SPEED_LOW);
    }
    else if (!Line_L && Line_R)
    {
      analogWrite(MOTOR_R_a, 0);
      analogWrite(MOTOR_R_b, MOTOR_SPEED_LOW);

      analogWrite(MOTOR_L_a, MOTOR_SPEED_HIGH);
      analogWrite(MOTOR_L_b, 0);
    }
  }
  else
  {
    analogWrite(MOTOR_R_a, 0);
    analogWrite(MOTOR_R_b, 0);
    analogWrite(MOTOR_L_a, 0);
    analogWrite(MOTOR_L_b, 0);

    delay(2000);
  }
  //
    Serial.print("Left : ");
    Serial.print(value_Left);
    Serial.print("  Right : ");
    Serial.println(value_Right);

  //==============================MOTOR===========================//

  delay(10);
}
