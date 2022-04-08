/*
  # This sample code is used to test the pH meter V1.1.
  # Editor : YouYou
  # Date   : 2014.06.23
  # Ver    : 1.1
  # Product: analog pH meter
  # SKU    : SEN0161
*/

#define OFFSET 42.56            //deviation compensate
#define PH_CONST -19.185        // check datasheet at seeding studio
int _analogReadPH;
float _voltageConvertionPH;

void readSensorPH(){
    _analogReadPH = analogRead(PIN_PH);
    _voltageConvertionPH = _analogReadPH * V_REF_5V/ ADC_RESOLUTION;
    gPhvalue = -19.185 * _voltageConvertionPH + OFFSET;

    #if defined DEBUG_ALL || DEBUG_PH
      Serial.print("PH Value: ");
      Serial.println(gPhvalue);
     #endif
}
