/* This tab store all the data from sensor capture*/
#ifndef DATA_CAPTURE_H
#define DATA_CAPTURE_H

/* PH sensor */
float gPhvalue;

/* TDS Sensor */
float gTds;
float gConductivity;
int gSalinity;

/* Turbidity Sensor */
float gTurbidity;

/* ds18b20 Sensor */
float gTemp;

/* RTC DS3231 */
 String dateNow; 
 String timeNow;
#endif
