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

#if defined DEBUG_ALL || defined DEBUG_SALINITY
  Serial.print("Voltage of Salinity Sensor: ");
  Serial.println(rata_rata_teg);
  Serial.print("TDS: ");
  Serial.println(gTds);
  Serial.print("Conductvity: ");
  Serial.println(gConductivity);

#endif
}
