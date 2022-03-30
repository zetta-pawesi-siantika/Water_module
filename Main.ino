
#include "IO_Mapping.h"
#include "Data_Capture.h"

#define DELAY_OPERATION 800
#define V_REF_5V 5.0
#define ADC_RESOLUTION 1023.0

// preprocessor write here
#define DEBUG_ALL

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  setupSensorPH();

}

void loop() {
  // put your main code here, to run repeatedly:
  readSensorPH();
  readSensorSalinity();

  //delay(DELAY_OPERATION);

}
