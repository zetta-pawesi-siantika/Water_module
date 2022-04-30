/* Mechanical operation */


#include <Servo.h>
Servo myservo;

void setupMechanical() {
  pinMode(PIN_SEAPUMP, OUTPUT);
  pinMode(PIN_PUREWATER, OUTPUT);
  myservo.attach(PIN_SERVO);
  myservo.write(SETTLE_SERVO_DEG);
}


void moveServo(byte deg){
  myservo.write(deg);
}

void seawaterPump_ON() {
  digitalWrite(PIN_SEAPUMP, LOW);
}

void seawaterPump_OFF() {
  digitalWrite(PIN_SEAPUMP, HIGH);
}

void purewaterPump_ON(){
  digitalWrite(PIN_PUREWATER, LOW);
}

void purewaterPump_OFF(){
  digitalWrite(PIN_PUREWATER, HIGH);
}
