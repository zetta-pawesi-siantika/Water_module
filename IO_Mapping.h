/* This file contains pin connection from device to microcontroller */

#ifndef IO_MAPPING_H
#define IO_MAPPING_H

/* Sensors */
// Analog pin
#define PIN_TURBIDITY A0
#define PIN_PH A1 
#define PIN_SALINITY A2 // Salinity and TDS Sensor

// Digital Pin
#define PIN_DS18B20 4
#define VCC_TURBIDITY 7 
#define VCC_SENSORS 8


/* sd card / Data logger */
#define CHIP_SELECT 10 // SS pin on Arduino Nano

/* Mechanic */
#define PIN_SEAPUMP 5
#define PIN_PUREWATER 6
#define PIN_SERVO 9


 /* Time DS3231 */
 String dayOftheWeek;
 String dateNow; 
 String timeNow;

#endif
