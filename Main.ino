#include <Wire.h>

#include "IO_Mapping.h"
#include "Data_Capture.h"

#define DELAY_OPERATION 800
#define V_REF_5V 5.0
#define ADC_RESOLUTION 1024.0
#define DELAY_EMPTYING_SEAWATER 17000 // second
#define DELAY_EMPTYING_PUREWATER 11000 // second
#define DELAY_SEAWATER_FULLFILL 4000// second
#define DELAY_PUREWATER_FILLING 6000// second
#define EMPTYING_SEAWATER_DEG 80 // degree
#define EMPTYING_PUREWATER_DEG 120 // degree
#define SETTLE_SERVO_DEG 0 // degree 

// preprocessor write here

#define SENSORS_READING
#define DEBUG_DS18B20

//#define TURN_ON_SEAPUMP

void setup() {
#if defined SENSORS_READING || defined ALL_SYSTEM
  Serial.begin(9600);

  // setup to closed water
  delay(1000);

  pinMode(VCC_SENSORS, OUTPUT);
  pinMode(VCC_TURBIDITY, OUTPUT);
  setupMechanical() ;
  setupRTCDS3231();
  purewaterPump_OFF();
  seawaterPump_OFF();

  // setup comunication
  setupCom();

#endif
}

void loop() {

#if defined MECHANICAL || defined ALL_SYSTEM

  setupDatalogger();
  delay(1000);
  /* Emptying pure water  */
  moveServo(EMPTYING_PUREWATER_DEG);
  delay(DELAY_EMPTYING_PUREWATER);
  moveServo(SETTLE_SERVO_DEG);

  /* Sucking seawater */
  seawaterPump_ON();
  delay(DELAY_SEAWATER_FULLFILL);
  seawaterPump_OFF();

#endif


#if defined SENSORS_READING || defined ALL_SYSTEM
  /* Activating Sensor  */
  activateSensor();
  delay(1000);
  printTimennow();
  readSensorturbidity();
  readSensorPH();
  readSensorSalinity();
  readSensords18b20();
#endif







#if defined DEACTIVATED_SENSORS || defined ALL_SYSTEM
  /* Deactivating Sensor  */
  deactivateSensor();
  delay(2000);
#endif

#ifdef SEND_TO_SERVER // sensitive issue, Issolate
  sendDatatoserver();
#endif


#if defined DATA_LOGGER || defined ALL_SYSTEM
  dataLogger();
  delay(2000);
#endif

  /* Deactivating Sensor */
  /* Emptying Seawater */

#if defined MECHANICAL || defined ALL_SYSTEM
  moveServo(EMPTYING_SEAWATER_DEG);
  delay(DELAY_EMPTYING_SEAWATER);
  moveServo(SETTLE_SERVO_DEG);
  purewaterPump_ON();
  delay(DELAY_PUREWATER_FILLING);
  purewaterPump_OFF();
  Serial.println("DONE");
#endif


  // mechanical operation
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
  delay(1000);
}


/* Activating sensors */
void activateSensor() {
  digitalWrite(VCC_SENSORS, HIGH);
  digitalWrite(VCC_TURBIDITY, HIGH);
}

/* Deactivating sensors */
void deactivateSensor() {
  digitalWrite(VCC_SENSORS, LOW);
  digitalWrite(VCC_TURBIDITY, LOW);
}
