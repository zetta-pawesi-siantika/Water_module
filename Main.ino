#include <Wire.h>
#include "IO_Mapping.h"
#include "Data_Capture.h"
#include "Mechanical_Setting.h"

#define V_REF_5V 5.0
#define ADC_RESOLUTION 1024.0


// preprocessor write here --> it enabels or disables features
#define MECHANICAL
#define SENSORS_READING
#define DEACTIVATED_SENSORS
#define DATA_LOGGER
#define SEND_TO_SERVER

void setup() {
  Serial.begin(9600);
  delay(2000); // delay for preventing pin form auto in low level when Arduino booting up

  pinMode(VCC_SENSORS, OUTPUT);
  pinMode(VCC_TURBIDITY, OUTPUT);
  setupMechanical() ;
  setupDatalogger();
  setupRTCDS3231();
  purewaterPump_OFF();
  seawaterPump_OFF();
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
  delay(DELAY_PUREWATER_FILLING);
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
