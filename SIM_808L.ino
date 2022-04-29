#include <SoftwareSerial.h>
#include <String.h>


SoftwareSerial SIM808(2, 3); // RX || TX

void setupCom()
{
  SIM808.begin(9600);               // the GPRS baud rate

}

void sendDatatoserver()
{

  if (SIM808.available())
    Serial.write(SIM808.read());

  delay(1000);
  SIM808.println("AT");
  delay(1000);

  SIM808.println("AT+CPIN?");
  delay(1000);

  SIM808.println("AT+CREG?");
  delay(1000);

  SIM808.println("AT+CGATT?");
  delay(1000);

  SIM808.println("AT+CIPSHUT");
  delay(1000);

  SIM808.println("AT+CIPSTATUS");
  delay(2000);

  SIM808.println("AT+CIPMUX=0");
  delay(2000);

  ShowSerialData();

  SIM808.println("AT+CSTT=m2mautotronic"); //start task and setting the APN,
  delay(3000);

  ShowSerialData();


  SIM808.println("AT+CIICR");//bring up wireless connection
  delay(3000);

  ShowSerialData();


  SIM808.println("AT+CIFSR");//get local IP adress
  delay(2000);

  ShowSerialData();
  SIM808.println("AT+CIPSPRT=0");
  delay(3000);

  ShowSerialData();

  SIM808.println("AT+CIPSTART=\"TCP\",\"api.thingspeak.com\",\"80\"");//start up the connection
  delay(6000);

  ShowSerialData();

  SIM808.println("AT+CIPSEND");//begin send data to remote server
  delay(4000);
  ShowSerialData();
  //
  //  // Sensors channel
  //  // str += "GET https://api.thingspeak.com/update?api_key=" + String(API_KEY) + "&field1=" + String(50) + "&field2=" + String(60) + "&field3=" + String(70) + "&field4=" + String(80) + "&field5=" + String(20);
  //Serial.print("GET https://api.thingspeak.com/update?api_key=JIJJ0YWO8O6QK5BQ");
  SIM808.print("GET https://api.thingspeak.com/update?api_key=JIJJ0YWO8O6QK5BQ");//begin send data to remote server
  delay(2000);
  Serial.println(+ "&field1=" + String(gPhvalue) + "&field2=" + String(gNtu) + "&field3=" + String(gTemp) + "&field4=" + String(gTds) + "&field5=" + String(gSalinity));
  SIM808.println(+ "&field1=" + String(gPhvalue) + "&field2=" + String(gNtu) + "&field3=" + String(gTemp) + "&field4=" + String(gTds) + "&field5=" + String(gSalinity));//begin send data to remote server

  delay(2000);
  ShowSerialData();
  //
  SIM808.println((char)26);//sending
  delay(5000);//waitting for reply, important! the time is base on the condition of internet
  SIM808.println();
  //
  SIM808.println("AT+CIPSHUT");//close the connection
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
