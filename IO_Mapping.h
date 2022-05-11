/* **************************************************************************** */
/* This sketch file is used to initialize IO pin on ARDUINO Nano Old bootloader */
/* board                                                                        */
/* **************************************************************************** */

#ifndef IO_MAPPING_H
#define IO_MAPPING_H

/* No needs to declare Pin */
/* many peripherals don't need  initialize Pin, which are:
  1. DS32331 -> I2C 
  2. Data Logger -> SPI (10-13)
*/

/* Sensors */
/* Analog pin */
/* block starts here */
#define PIN_TURBIDITY A0
#define PIN_PH A1 
#define PIN_SALINITY A2 // Salinity and TDS Sensor
/* analog pin block ends here */

/* Digital Pin */
/* block starts here */
#define PIN_DS18B20 4
#define VCC_TURBIDITY 7 
#define VCC_SENSORS 8
/* sd card / Data logger */
#define CHIP_SELECT 10 // SS pin on Arduino Nano (Micro SD Card property)
/* Mechanic */
#define PIN_SEAPUMP 5
#define PIN_PUREWATER 6
#define PIN_SERVO 9
/* Digital pin block ends here */
#endif
