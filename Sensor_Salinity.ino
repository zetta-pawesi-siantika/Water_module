/* Salinity sensor properties */

float teg[10];
float rata_rata_teg;

void readSensorSalinity() {
  for ( int i = 0; i < 10; i++) {
    int val = analogRead(PIN_SALINITY);
    teg[i] = val * (V_REF_5V / ADC_RESOLUTION);
  }
  rata_rata_teg = (teg[0] + teg[1] + teg[2] + teg[3] + teg[4] + teg[5] + teg[6] + teg[7] + teg[8] + teg[9]) / 10 ;
  //delay(1000);
  gTds = (211.2254 * rata_rata_teg) - 144.1466;
  gConductivity = (0.3442 * rata_rata_teg) - 0.253;
  gSalinity = pow(gConductivity,1.0878)  * 0.4665 ; // src:https://sciencing.com/convert-gallons-quarts-pints-cups-5259231.html
#if defined DEBUG_ALL || defined DEBUG_SALINITY
//  Serial.print("Voltage of Salinity Sensor: ");
//  Serial.println(rata_rata_teg);
  Serial.print("TDS: ");
  Serial.print(gTds);
  Serial.println(" ppm");
  Serial.print("Conductvity: ");
  Serial.print(gConductivity);
  Serial.println(" Mikrosiemens/cm");
  Serial.print("Salinity: ");
  Serial.print(gSalinity); 
  Serial.println(" gram/liter"); // not sure

#endif
}
