/* Sensor Turbidity properties, It measures turbidity in NTU unit 
 *  src: https://how2electronics.com/diy-turbidity-meter-using-turbidity-sensor-arduino/
 */

void readSensorturbidity()
{
  #define CALIBRATION_BOUNDARY 4.20
  float _turbidityVolt;

  _turbidityVolt = 0;
  for (int i = 0; i < 800; i++)
  {
    _turbidityVolt += ((float)analogRead(PIN_TURBIDITY) / ADC_RESOLUTION) * V_REF_5V;
  }
  _turbidityVolt = _turbidityVolt / 800;
  _turbidityVolt = round_to_dp(_turbidityVolt, 2);

  // Calibration
  if (_turbidityVolt > CALIBRATION_BOUNDARY) {
    _turbidityVolt = CALIBRATION_BOUNDARY;
  }

  if (_turbidityVolt < 2.5) {
    gTurbidity = 3000;
  } else {
    gTurbidity = -1120.4 * square(_turbidityVolt) + 5742.3 * _turbidityVolt - 4352.9;
  }

#if defined DEBUG_ALL || defined DEBUG_TURBIDITY
  Serial.print(F("Turbidity: "));
  Serial.print(gTurbidity);
  Serial.println(F(" NTU"));
#endif
}


float round_to_dp( float in_value, int decimal_place )
{
  float multiplier = powf( 10.0f, decimal_place );
  in_value = roundf( in_value * multiplier ) / multiplier;
  return in_value;
}
