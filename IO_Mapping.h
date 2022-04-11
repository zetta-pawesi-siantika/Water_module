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

/* sd card / Data logger */
#define CHIP_SELECT 10 // SS pin on Arduino Pro mini

/* Mechanic */
#define PIN_SEAPUMP 2
#define PIN_PUREWATER 3
#define PIN_SERVO 9

/* DS3231 */

 /* Time DS3231 */
 String dayOftheWeek;
 String dateNow; 
 String timeNow;

#endif
