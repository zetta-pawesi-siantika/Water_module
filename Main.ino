#include <Wire.h>

#include "IO_Mapping.h"
#include "Data_Capture.h"

#define DELAY_OPERATION 800
#define V_REF_5V 5.0
#define ADC_RESOLUTION 1024.0
#define DELAY_EMPTYING_SEAWATER 17000 // second
#define DELAY_EMPTYING_PUREWATER 11000 // second
#define DELAY_SEAWATER_FULLFILL 3000// second
#define DELAY_PUREWATER_FILLING 9000// second
#define EMPTYING_SEAWATER_DEG 160 // degree
#define EMPTYING_PUREWATER_DEG 130 // degree
#define SETTLE_SERVO_DEG 30 // degree 

// preprocessor write here
#define DEBUG_ALL
#define ALL_SYSTEM

void setup() {
  Serial.begin(9600);
  // setup to closed water
  delay(1000);
  setupMechanical() ;
  setupRTCDS3231();
  
  purewaterPump_OFF();
  seawaterPump_OFF();
  
}

void loop() {
  #ifdef ALL_SYSTEM
  setupDatalogger();
  /* Emptying pure water  */
  moveServo(EMPTYING_PUREWATER_DEG);
  delay(DELAY_EMPTYING_PUREWATER);
  moveServo(SETTLE_SERVO_DEG);

  /* Sucking seawater */
  seawaterPump_ON();
  delay(DELAY_SEAWATER_FULLFILL);
  seawaterPump_OFF();

  #if defined SENSORS_READING || defined ALL_SYSTEM
  /* Activating Sensor  */
  printTimennow(); 
  readSensorturbidity();
  //readSensorPH();
  readSensorSalinity();
  readSensords18b20();
  dataLogger();
  delay(2000);
  #endif
  /* Deactivating Sensor */
  
  /* Emptying Seawater */
  moveServo(EMPTYING_SEAWATER_DEG);
 
  delay(DELAY_EMPTYING_SEAWATER);
  moveServo(SETTLE_SERVO_DEG);

  /* Activating pure water pump */
purewaterPump_ON();
delay(DELAY_PUREWATER_FILLING);
purewaterPump_OFF();
  /* Deactivating Sensor  */
  
  Serial.println("DONE");
#endif
  #ifdef EMPTYING_SEAWATER
  moveServo(EMPTYING_SEAWATER_DEG);
  #endif

  #ifdef TURN_ON_SEAPUMP
  seawaterPump_ON();
  #endif

delay(1000);
}
