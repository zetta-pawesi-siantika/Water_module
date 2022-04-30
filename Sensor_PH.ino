/*
  # This sample code is used to test the pH meter V1.1.
  # Editor : YouYou
  # Date   : 2014.06.23
  # Ver    : 1.1
  # Product: analog pH meter
  # SKU    : SEN0161
*/

#define OFFSET 1.4  //deviation compensate --> done by self callibration

  int _analogReadPH;
  float _voltageConvertionPH;

void readSensorPH() {

  _analogReadPH = analogRead(PIN_PH);
  _voltageConvertionPH = _analogReadPH * V_REF_5V / ADC_RESOLUTION;
  Serial.println(_voltageConvertionPH);
  gPhvalue = 3.5 * _voltageConvertionPH + OFFSET;

#if defined DEBUG_ALL || defined DEBUG_PH
  Serial.print(F("PH Value: "));
  Serial.println(gPhvalue);
#endif
}
