

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

  #if defined DEBUG_ALL || defined DS18B20 
  Serial.print("Suhu Celsius: ");
  Serial.print(DS18B20.getTempCByIndex(0));
  #endif
}
