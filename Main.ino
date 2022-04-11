#include <Wire.h> 

#include "IO_Mapping.h"
#include "Data_Capture.h"

#define DELAY_OPERATION 800
#define V_REF_5V 5.0
#define ADC_RESOLUTION 1024.0
#define DELAY_EMPTYING 9000
#define DELAY_SEAWATER_FULLFILL 9000
#define DELAY_PUREWATER_FILLING 9000

// preprocessor write here
#define DEBUG_ALL

void setup(){
  Serial.begin(9600);
  // setup to closed water
  setupMechanical() ;
}

void loop(){
  moveServo(0);
  delay(2000);
  moveServo(180);
  delay(2000);
  /* Emptying pure water  */
//  moveServo(180); 
//  delay(DELAY_EMPTYING);
//  moveServo(0);
//
//  
//  /* Sucking seawater */
//  purewaterPump_ON();
//  delay(DELAY_SEAWATER_FULLFILL);
//  purewaterPump_OFF();
//
//  /* Activating Sensor  */ 
//  readSensorPH();
//  readSensorSalinity();
//
//  /* Deactivating Sensor */
//  /* Emptying Seawater */
//  moveServo(180);
//  delay(DELAY_EMPTYING);
//  moveServo(0);
  
  /* Activating pure water pump*/
  purewaterPump_ON();
  delay(DELAY_PUREWATER_FILLING);
  purewaterPump_OFF();

  Serial.println("DONE");
 // while(1){}
  
}
