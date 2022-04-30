/* TDS sensor properties. It measure Conductivity and TDS. Needing convertion when uses for measure salinity  */
// src: https://www.depoinovasi.com/produk-510-sensor-konduktivitas--tds--kadar-garam.html

float teg[10];
float rata_rata_teg;

void readSensorSalinity() {
  for ( int i = 0; i < 10; i++) {
    int val = analogRead(PIN_SALINITY);
    teg[i] = val * (V_REF_5V / ADC_RESOLUTION);
  }
  rata_rata_teg = (teg[0] + teg[1] + teg[2] + teg[3] + teg[4] + teg[5] + teg[6] + teg[7] + teg[8] + teg[9]) / 10 ;
  delay(100);
  gTds = (211.2254 * rata_rata_teg) - 144.1466;
  gConductivity = (0.3442 * rata_rata_teg) - 0.253;

  // If gSalinity value is Nan 
  if (gConductivity <= 0){
    gConductivity=0;
  }
  
  gSalinity = pow(gConductivity,1.0878)  * 0.4665 ; // src:https://sciencing.com/convert-gallons-quarts-pints-cups-5259231.html

#if defined DEBUG_ALL || defined DEBUG_SALINITY
  Serial.print(F("TDS: "));
  Serial.print(gTds);
  Serial.println(F(" ppm"));
  Serial.print(F("Conductvity: "));
  Serial.print(gConductivity);
  Serial.println(F(" Mikrosiemens/cm"));
  Serial.print(F("Salinity: "));
  Serial.print(gSalinity); 
  Serial.println(F(" gram/liter")); 
#endif
}
