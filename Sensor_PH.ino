/* DF Robot pH sensor
 *  src: https://www.dfrobot.com/product-1782.html
*/

void readSensorPH() {
  #define OFFSET 0.5  //deviation compensate --> done by self callibration
  int _analogReadPH;
  float _voltageConvertionPH;

  _analogReadPH = analogRead(PIN_PH);
  _voltageConvertionPH = _analogReadPH * V_REF_5V / ADC_RESOLUTION;
  gPhvalue = 3.5 * _voltageConvertionPH + OFFSET;

#if defined DEBUG_ALL || defined DEBUG_PH
  Serial.print(F("PH Value: "));
  Serial.println(gPhvalue);
#endif
}
