
#include "IO_Mapping.h"
#include "Data_Capture.h"

#define DELAY_OPERATION 800
#define V_REF_5V 5.0
#define ADC_RESOLUTION 1023.0

// preprocessor write here
#define DEBUG_

const int waterDatasampling = 5;
float sumWaterheight;
const float WATER_THRESH_HOLD_FULL = 4.0; // cm
const float WATER_THRESH_HOLD_EMPTY = 0.1; // cm

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(PIN_RELAY_1, OUTPUT);
  pinMode(PIN_RELAY_2, OUTPUT);
  setupSensorPH();

}

void loop() {
  // put your main code here, to run repeatedly:
  /*  1). Checking water in the box, if water height = ... , turn on relay 1 (PUMP A)
     2). Turn on servo to reel the hose
     3). if no water in the box, turn on relay 2, pumping from seawater.
     4). Waiting sensor to finish it's job
     5). turn on relay 1 to empty the water box (PUMP A).
     6). Turn on servo to roll back hose
  */

  // water level read sensor
  
  readSensorwaterlevel();
    Serial.print(" Water height: ");
    Serial.println(gWaterheight);
  // logic of water


    if (gWaterheight >= WATER_THRESH_HOLD_EMPTY) {
    // turn on solenoid
    // check the water again in box
    turnOnrelay1();
    Serial.println("box is full!!");
    }
    else if(gWaterheight < WATER_THRESH_HOLD_EMPTY) {
      // turn off relay 1
      turnOffrelay1();
      Serial.println("box is empty");
    
    } else {
    // pass
    }

delay(500);
  
  // let servo goes to water

  // activating sensors
  // read DO
  // read turbidity
  //  readSensorPH();
  //  readSensorSalinity();
  //  readSensorwaterlevel();

  /*
    if(){
      // drain the water
      // turn off relay

    }
  */

  // servo roll in

  // delay(DELAY_OPERATION);

}
