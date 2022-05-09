#include <Wire.h>
#include <DS3231.h>
#include "IO_Mapping.h"
#include "Data_Capture.h"
#include "Mechanical_Setting.h"
#include "LowPower.h"
#define V_REF_5V 5.0
#define ADC_RESOLUTION 1024.0

// Check firmware's documentation here: link 
// preprocessor for enable/disable operations 
#define ALL_SYSTEM

// preprocessor for enable/disable serial print each feature
//#define DEBUG_ALL

DS3231  rtc(SDA, SCL);
Time t;


/* Hour Operation */
const byte workTimeinterval = 12; // minutes
const byte relaxTimeinterval = 60; // night operation every 1 hour

// morning time
const byte morningTimestart = 4 ; // 4.00 am
const byte morningTimeend = 6 ; // 6.00 am

// mid Day
const byte middayTimestart = 11; // 11.00
const byte middayTimeend = 13 ; // 13.00

// Sunset
const byte sunsetTimestart = 17; // 17.00
const byte sunsetTimeend = 19; // 19.00

void setup() {
  Serial.begin(9600);
  purewaterPump_OFF(); // SHOULD BE HERE
  seawaterPump_OFF(); // SHOULD BE HERE
  delay(2000); // delay for preventing pin from auto in low level when Arduino booting up. DON'T CHANGE THE HIERARCHY OF THIS SETUP!!!
  pinMode(VCC_SENSORS, OUTPUT);
  pinMode(VCC_TURBIDITY, OUTPUT);
  setupMechanical() ;
  setupDatalogger();
  setupRTCDS3231();
  setupCom();
}

void loop() {
 t = rtc.getTime();
  byte timeHournow = t.hour;
  Serial.println(t.hour);

  if (timeHournow >= morningTimestart && timeHournow < morningTimeend) {

    operationDevice(workTimeinterval);
    Serial.println("Morning");
  }
  else if (timeHournow >= middayTimestart && timeHournow < middayTimeend) {
    operationDevice(workTimeinterval);
    Serial.println("Mid day");
  }
  else if (timeHournow >= sunsetTimestart && timeHournow < sunsetTimeend) {
    operationDevice(workTimeinterval);
    Serial.println("Sunset");
  }
  else {
    operationDevice(relaxTimeinterval);
    Serial.println("Relaxing");
  }
  delay(1000); // sleep before delay
  LowPower.powerDown(SLEEP_8S, ADC_OFF, BOD_OFF);
  delay(2000); // wakeup time

}

// operation
void operation(){
#if defined MECHANICAL || defined ALL_SYSTEM
  /* Emptying pure water  */
  moveServo(EMPTYING_PUREWATER_DEG);
  delay(DELAY_EMPTYING_PUREWATER);
  moveServo(SETTLE_SERVO_DEG);

  /* Sucking seawater */
  seawaterPump_ON();
  delay(DELAY_SEAWATER_FULLFILLING);
  seawaterPump_OFF();

#endif


#if defined SENSORS_READING || defined ALL_SYSTEM
  activateSensor();
  delay(3000); // give sensors time to initialize setup
  printTimennow();
  readSensorturbidity();
  readSensorPH();
  readSensorSalinity();
  readSensords18b20();
#endif


#if defined DEACTIVATED_SENSORS || defined ALL_SYSTEM
  deactivateSensor();
#endif

#if defined DATA_LOGGER || defined ALL_SYSTEM
  dataLogger();
#endif


  /* Emptying Seawater */
#if defined MECHANICAL || defined ALL_SYSTEM
  moveServo(EMPTYING_SEAWATER_DEG);
  delay(DELAY_EMPTYING_SEAWATER);
#endif

  // send data to server
#if defined SEND_TO_SERVER  || defined ALL_SYSTEM // sensitive issue, Issolate
  sendDatatoserver();
#endif

#if defined MECHANICAL || defined ALL_SYSTEM
  moveServo(SETTLE_SERVO_DEG);
  purewaterPump_ON();
  delay(DELAY_PUREWATER_FULLFILLING);
  purewaterPump_OFF();
  Serial.println("DONE");
#endif


  /* Testing mechanical operation
      it is not part from main code, only use when to doing specific operation on mechanical / debugging
  */

#ifdef SETTLE_SERVO
  moveServo(SETTLE_SERVO_DEG);
#endif

#ifdef EMPTYING_SEAWATER
  moveServo(EMPTYING_SEAWATER_DEG);
#endif

#ifdef TURN_ON_SEAPUMP
  seawaterPump_ON();
#endif

#ifdef TURN_ON_PUREWATER_PUMP
  purewaterPump_ON();
#endif

}


void operationDevice(byte timeInterval) {
  if (t.min % timeInterval == 0) {
    Serial.println("OPERATING");
    //operation starts here
    operation();
    
    byte endTimeoperation = t.min;
    while (endTimeoperation == t.min) {
      t = rtc.getTime();
      Serial.println(t.min);
      delay(2000);
      LowPower.powerDown(SLEEP_8S, ADC_OFF, BOD_OFF);
      delay(2000);
    }

  } else {
    Serial.println("SLEEPING");
  }
}
