/* Mechanical: Water operation */
/*  0. reel out
    1. check water in the box,
    2. Emptying water by servo --> turn right 90 deg
    3. return servo to 0 deg (vertical)
    3. check water
        3.1 If already emptying
            -> Turn on pump 1 (sucking seawater)
            -> Check Water
              3.1.1 If water full --> turn of relay
              3.1.2 If no, continue on water pump 1 on
     4. Activating sensor
     5. deactivating sensor
     6. Emptying box (seawater --> turn lef 90 deg)
     7. return servo to 0 deg (vertical)
     8. reel in hose


*/
#include <Servo.h>
Servo myservo;
byte _Angle = 0; // degree

void setupMechanical() {
  pinMode(PIN_SEAPUMP, OUTPUT);
  pinMode(PIN_PUREWATER, OUTPUT);
  myservo.attach(PIN_SERVO);
  myservo.write(20);
}

/* *********** Servo Operation *********** */
void moveServo(byte deg){
  myservo.write(deg);
}
/* *********** Servo end here *********** */


/* *********** Pump operation *********** */
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
/* *********** pump operation end here *********** */
