/* Sensor DSb18b20 properties, It measures water temperature */

#include <OneWire.h>
#include <DallasTemperature.h>
OneWire pin_DS18B20(PIN_DS18B20);
DallasTemperature DS18B20(&pin_DS18B20);

void setupDS18B20(){
  DS18B20.begin();
}

void readSensords18b20(){
  DS18B20.requestTemperatures();
  gTemp = DS18B20.getTempCByIndex(0);

  #if defined DEBUG_ALL || defined DEBUG_DS18B20 
  Serial.print(F("Temperature in Celsius: "));
  Serial.println(DS18B20.getTempCByIndex(0));
  #endif
}
