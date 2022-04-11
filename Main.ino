#include <Wire.h>

#include "IO_Mapping.h"
#include "Data_Capture.h"

#define DELAY_OPERATION 800
#define V_REF_5V 5.0
#define ADC_RESOLUTION 1024.0
#define DELAY_EMPTYING 3000
#define DELAY_SEAWATER_FULLFILL 3000
#define DELAY_PUREWATER_FILLING 3000
#define EMPTYING_DEG 30 // degree

// preprocessor write here
#define DEBUG_DATALOG

void setup() {
  Serial.begin(9600);
  // setup to closed water
  setupMechanical() ;
  setupRTCDS3231();
  setupDatalogger();
  purewaterPump_OFF();
  seawaterPump_OFF();
}

void loop() {

  /* Emptying pure water  */
  moveServo(180);
  delay(DELAY_EMPTYING);
  moveServo(EMPTYING_DEG);

  /* Sucking seawater */
  seawaterPump_ON();
  delay(DELAY_SEAWATER_FULLFILL);
  seawaterPump_OFF();

  /* Activating Sensor  */
  readSensorturbidity();
  readSensorPH();
  readSensorSalinity();
  readSensords18b20();
  dataLogger();
  /* Deactivating Sensor */
  
  /* Emptying Seawater */
  moveServo(180);
  delay(DELAY_EMPTYING);
  moveServo(EMPTYING_DEG);

  /* Activating pure water pump */
purewaterPump_ON();
delay(DELAY_PUREWATER_FILLING);
purewaterPump_OFF();
  /* Deactivating Sensor  */
  
  Serial.println("DONE");
 delay(2000);

}
