

#include "IO_Mapping.h"
#include "Data_Capture.h"

#define DELAY_OPERATION 800
#define V_REF_5V 5.0
#define ADC_RESOLUTION 1024.0

// preprocessor write here
#define DEBUG_

void setup(){
  Serial.begin(9600);

}

void loop(){
  readSensorPH();
  Serial.print("PH Value: ");
  Serial.println(gPhvalue);

  delay(800);
  
}
