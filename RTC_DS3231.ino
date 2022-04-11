#include <DS3231.h>
DS3231  rtc(SDA, SCL);

void setupRTCDS3231(){
   rtc.begin();
}

void printTimennow(){
  dayOftheWeek = rtc.getDOWStr();
  dateNow = rtc.getDateStr();
  timeNow = rtc.getTimeStr();
  
  #if defined DEBUG_RTCDS3231 || defined DEBUG_ALL
    // Send Day-of-Week
  Serial.print(dayOftheWeek);
  Serial.print(" ");
  
  // Send date
  Serial.print(dateNow);
  Serial.print(" -- ");

  // Send time
  Serial.println(timeNow);
  #endif
}
