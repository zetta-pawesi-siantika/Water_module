/*Data logger properties
   this function is to log sensors data and stores it in micro SD Card
*/



// WARNING: UNDER PROCCESS --> still doesn't work


//Libraries
#include <SPI.h>
#include <SD.h>


File dataFile;

void setupDatalogger()
{
  pinMode(SS, OUTPUT);

  if (!SD.begin(CHIP_SELECT)) {
    Serial.println(F("Card failed, or not present"));
  }
  Serial.println(F("card initialized."));

  dataFile = SD.open("w.txt", FILE_WRITE);
  if (!dataFile) {
    Serial.println(F("error opening SD_Card"));

  }
  // template for title
  dataFile.println(F("PH(0-14), Turbidity(NTU),Water Temperature(Celcius),Tds(ppm),Salinity(gram/liter)"));
  delay(2000);
}

void dataLogger()
{
  dataFile.println(dateNow + "," + timeNow + "," + String(gPhvalue) + "," + String(gTurbidity) + "," + String(gTemp) + "," + String(gTds) + "," + String(gSalinity));
  delay(1000);
#if defined DEBUG_ALL || defined DEBUG_DATALOG
  Serial.println(F("Data Logged"));
#endif
  dataFile.flush();


}
