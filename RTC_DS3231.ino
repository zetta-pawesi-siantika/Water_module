
void setupRTCDS3231(){
   rtc.begin();
}

void printTimennow(){
  dateNow = rtc.getDateStr();
  timeNow = rtc.getTimeStr();
  
  #if defined DEBUG_RTCDS3231 || defined DEBUG_ALL
  // Showing date
  Serial.print(dateNow);
  Serial.print(F(" -- "));

  // Showing time
  Serial.println(timeNow);
  #endif
}
