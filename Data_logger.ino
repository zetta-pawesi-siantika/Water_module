/*Data logger properties
 * this function is to log sensors data and stores it in micro SD Card
*/

//Libraries
#include <SPI.h>
#include <SD.h>



// Global Conts 
String FILE_TITLE ="WATER_1.txt";

// Local Conts 
String TEMPLATE_TITLE ="PH(0-14),Tds(ppm),Conductivity(Microsiemens),Turbidity(NTU),Water Temperature(Celcius)";
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
    Serial.println("error opening datalog.txt");
  
  }
  // template for title
  dataFile.println(TEMPLATE_TITLE);
  Serial.println(TEMPLATE_TITLE);
}

void dataLogger()
{
  // make a string for assembling the data to log:
  String dataString = "";

  // added time stamp to field
  dataFile.print(dayOftheWeek);
  dataFile.print(" ");
  dataFile.print(dateNow);
  dataFile.print(" ");
  dataFile.println(timeNow);
  

  dataString = dataString + String(gPhvalue) + "," + String(gTds)+ "," + String(gConductivity)+ "," + String(gNtu)+ "," + String(gTemp);
  dataFile.println(dataString);
  #if defined DEBUG_ALL || defined DEBUG_DATALOG
  Serial.println(dataString);
  #endif
  dataFile.flush();
  
}
