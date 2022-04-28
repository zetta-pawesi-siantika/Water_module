/*Data logger properties
 * this function is to log sensors data and stores it in micro SD Card
*/

//Libraries
#include <SPI.h>
#include <SD.h>



// Global Conts 
String FILE_TITLE ="Wtr.txt"; // MAXIMUM 7 Characters !

// Local Conts 
String TEMPLATE_TITLE ="PH(0-14), Turbidity(NTU),Water Temperature(Celcius),Tds(ppm),Salinity(gram/liter)";
File dataFile;

void setupDatalogger()
{
  Serial.print("Initializing SD card...");
  // make sure that the default chip select pin is set to
  // output, even if you don't use it:
  pinMode(SS, OUTPUT);
  
  if (!SD.begin(CHIP_SELECT)) {
    Serial.println("Card failed, or not present");
   
  }
  Serial.println("card initialized.");
  

  dataFile = SD.open(FILE_TITLE, FILE_WRITE);
  if (! dataFile) {
    Serial.println("error opening "+ FILE_TITLE);
  
  }
  // template for title
  dataFile.println(TEMPLATE_TITLE);
   delay(2000);
}

void dataLogger()
{
  // make a string for assembling the data to log: 
  dataFile.println(dateNow + ","+ timeNow + "," + String(gPhvalue) + "," + String(gNtu)+ "," + String(gTemp)+ "," + String(gTds)+ "," + String(gSalinity));
  delay(2000);
  #if defined DEBUG_ALL || defined DEBUG_DATALOG
  Serial.println("Data Logged");
  #endif
  dataFile.flush();
 
  
}
