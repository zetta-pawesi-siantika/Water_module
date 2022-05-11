/* TDS sensor properties. It measure Conductivity and TDS. Needing convertion when uses for measure salinity  
 *  src: https://www.depoinovasi.com/produk-510-sensor-konduktivitas--tds--kadar-garam.html
 */

void readSensorSalinity() {
  float _volt[10];
  float _voltageAverage;

  for ( int i = 0; i < 10; i++) {
    int _val = analogRead(PIN_SALINITY);
    _volt[i] = _val * (V_REF_5V / ADC_RESOLUTION);
  }
  _voltageAverage = (_volt[0] + _volt[1] + _volt[2] + _volt[3] + _volt[4] + _volt[5] + _volt[6] + _volt[7] + _volt[8] + _volt[9]) / 10 ;
  delay(100);
  gTds = (211.2254 * _voltageAverage) - 144.1466;
  gConductivity = (0.3442 * _voltageAverage) - 0.253; 

  // If gConductivity value is negative sets it to 0.  It prevents gSalinity's value become nan (not an number).
  if (gConductivity <= 0) {
    gConductivity = 0;
  }

  gSalinity = pow(gConductivity, 1.0878)  * 0.4665 ; // src:https://sciencing.com/convert-gallons-quarts-pints-cups-5259231.html

#if defined DEBUG_ALL || defined DEBUG_SALINITY
  Serial.print(F("TDS: "));
  Serial.print(gTds);
  Serial.println(F(" ppm"));
  Serial.print(F("Conductvity: "));
  Serial.print(gConductivity);
  Serial.println(F(" Mikrosiemens/cm"));
  Serial.print(F("Salinity: "));
  Serial.print(gSalinity);
  Serial.println(F(" ppt"));
#endif
}
