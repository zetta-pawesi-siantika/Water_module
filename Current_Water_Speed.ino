/*
  Arduino Water flow meter
  YF- S201 Hall Effect Water Flow Sensor
  Water Flow Sensor output processed to read in litres/hour
*/
volatile int flow_frequency; // Measures flow sensor pulses
unsigned int cm3_sec; // Calculated litres/hour
unsigned char flowsensor = 2; // Sensor Input
unsigned long currentTime;
unsigned long cloopTime;

void flow () // Interrupt function
{
  flow_frequency++;
}


void setupWater()
{
  pinMode(flowsensor, INPUT);
  digitalWrite(flowsensor, HIGH); // Optional Internal Pull-Up
  Serial.begin(9600);
  attachInterrupt(0, flow, RISING); // Setup Interrupt
  sei(); // Enable interrupts
  currentTime = millis();
  cloopTime = currentTime;
}


void readWaterspeed()
{
  currentTime = millis();
  // Every second, calculate and print litres/hour
  if (currentTime >= (cloopTime + 1000))
  {
    cloopTime = currentTime; // Updates cloopTime
    // Pulse frequency (Hz) = 7.5Q, Q is flow rate in L/min.
    cm3_sec = (flow_frequency * 60 / 7.5 * 0.27 ); // (Pulse frequency x 60 min) / 7.5Q = flowrate in L/hour
    flow_frequency = 0; // Reset Counter

    unsigned int  waterVelocity = cm3_sec / 3.14;
    unsigned int  waterVelocity_knot = waterVelocity * 0.02;

    Serial.print(waterVelocity, DEC); // Print litres/hour
    Serial.println(" cm/s");

    Serial.print(waterVelocity_knot, DEC); // Print litres/hour
    Serial.println(" Knot");
  }
}
