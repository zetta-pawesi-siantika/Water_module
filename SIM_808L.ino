/* SIM808L properties
 *  Please notice APIKEY from Thinkspeak 
 *  APN setting : m2mautotronic (default). for more: https://wa.me/+62811526010 (autotronic)
*/
#include <SoftwareSerial.h>

SoftwareSerial SIM808(2, 3); // RX || TX

void setupCom()
{
  SIM808.begin(9600);              
}

void sendDatatoserver()
{

  if (SIM808.available())
    Serial.write(SIM808.read());

  delay(1000);
  SIM808.println(F("AT"));
  delay(1000);

  SIM808.println(F("AT+CPIN?"));
  delay(1000);

  SIM808.println(F("AT+CREG?"));
  delay(1000);

  SIM808.println(F("AT+CGATT?"));
  delay(1000);

  SIM808.println(F("AT+CIPSHUT"));
  delay(1000);

  SIM808.println(F("AT+CIPSTATUS"));
  delay(2000);

  SIM808.println(F("AT+CIPMUX=0"));
  delay(2000);

  ShowSerialData();

  SIM808.println(F("AT+CSTT=m2mautotronic")); //start task and setting the APN,
  delay(3000);

  ShowSerialData();


  SIM808.println(F("AT+CIICR"));//bring up wireless connection
  delay(3000);

  ShowSerialData();


  SIM808.println(F("AT+CIFSR"));//get local IP adress
  delay(2000);

  ShowSerialData();
  SIM808.println(F("AT+CIPSPRT=0"));
  delay(3000);

  ShowSerialData();

  SIM808.println(F("AT+CIPSTART=\"TCP\",\"api.thingspeak.com\",\"80\""));//start up the connection
  delay(6000);

  ShowSerialData();

  SIM808.println(F("AT+CIPSEND"));//begin send data to remote server
  delay(4000);
  ShowSerialData();
  SIM808.print(F("GET https://api.thingspeak.com/update?api_key=FSFSIMDXAO8H8NWG"));//begin send data to remote server. || key is auth= SHOULD CHANGE IT ACCORDING TO YOUR CHANNEL
  delay(2000);
  Serial.println(+ "&field1=" + String(gPhvalue) + "&field2=" + String(gTurbidity) + "&field3=" + String(gTemp) + "&field4=" + String(gTds) + "&field5=" + String(gSalinity));
  SIM808.println(+ "&field1=" + String(gPhvalue) + "&field2=" + String(gTurbidity) + "&field3=" + String(gTemp) + "&field4=" + String(gTds) + "&field5=" + String(gSalinity));//begin send data to remote server

  delay(2000);
  ShowSerialData();

  SIM808.println((char)26);//sending
  delay(5000);//waitting for reply, important! the time is base on the condition of internet
  SIM808.println();
 
  SIM808.println(F("AT+CIPSHUT"));//close the connection
  delay(100);
  ShowSerialData();
}


void ShowSerialData()
{
  #if defined DEBUG_SIM808L || defined DEBUG_ALL
  while (SIM808.available() != 0)
    Serial.write(SIM808.read());
  delay(5000);
  #endif
}
