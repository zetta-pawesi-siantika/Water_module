#include <Wire.h>

#include "IO_Mapping.h"
#include "Data_Capture.h"

#define DELAY_OPERATION 800
#define V_REF_5V 5.0
#define ADC_RESOLUTION 1024.0
#define DELAY_EMPTYING_SEAWATER 17000 // second
#define DELAY_EMPTYING_PUREWATER 11000 // second
#define DELAY_SEAWATER_FULLFILL 4000// second
#define DELAY_PUREWATER_FILLING 5500// second
#define EMPTYING_SEAWATER_DEG 80 // degree
#define EMPTYING_PUREWATER_DEG 120 // degree
#define SETTLE_SERVO_DEG 0 // degree 

// preprocessor write here

//#define DATA_LOGGER // for serial
//#define DEBUG_DATALOG // for operation
#define MECHANICAL
#define SENSORS_READING 
#define DEBUG_PH
//#define TURN_ON_SEAPUMP
#define DEACTIVATED_SENSORS
#define SEND_TO_SERVER
#define DEBUG_SIM808L


//#define TURN_ON_SEAPUMP

void setup() {

  Serial.begin(9600);

  // setup to closed water
  delay(1000);
 // setupDatalogger();
  delay(2000);
  pinMode(VCC_SENSORS, OUTPUT);
  pinMode(VCC_TURBIDITY, OUTPUT);
  setupMechanical() ;
  setupRTCDS3231();
  purewaterPump_OFF();
  seawaterPump_OFF();

  // setup comunication
  setupCom();


}

void loop() {

#if defined MECHANICAL || defined ALL_SYSTEM


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
  delay(2000);
  printTimennow();
  readSensorturbidity();
  readSensorPH();
  readSensorSalinity();
  readSensords18b20();
#endif




#if defined DEACTIVATED_SENSORS || defined ALL_SYSTEM
  /* Deactivating Sensor  */
  deactivateSensor();
#endif

#if defined DATA_LOGGER || defined ALL_SYSTEM
  dataLogger();
#endif



  /* Deactivating Sensor */
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

/*Disable servo */
void disableServo() {
  digitalWrite(PIN_SERVO, LOW);
}

/*Disable servo */
void enableServo() {
  pinMode(PIN_SERVO, OUTPUT);
}
