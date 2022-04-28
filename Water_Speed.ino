/* It handles current water speed using water flow sensor (YF-S201)*/

/*
  Arduino Water flow meter
  YF- S201 Hall Effect Water Flow Sensor
  Water Flow Sensor output processed to read in litres/hour
*/
//volatile int flow_frequency; // Measures flow sensor pulses
//unsigned int cm3_sec; // Calculated litres/hour
//unsigned char flowsensor = 2; // Sensor Input
//unsigned long currentTime;
//unsigned long cloopTime;
//void flow () // Interrupt function
//{
//  flow_frequency++;
//}
//
//void setup()
//{
//  pinMode(flowsensor, INPUT);
//  digitalWrite(flowsensor, HIGH); // Optional Internal Pull-Up
//  Serial.begin(9600);
//  attachInterrupt(0, flow, RISING); // Setup Interrupt
//  sei(); // Enable interrupts
//  currentTime = millis();
//  cloopTime = currentTime;
//}
