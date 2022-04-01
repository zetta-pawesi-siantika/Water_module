static float _waterSensorread; // variable untuk menampung nilai baca dari sensor dalam bentuk integer
float _waterSensorvoltage; // untuk menampung nilai ketinggian air
const float _SENSOR_LENGTH = 4.0 ; // 4.0 cm, bisa dirubah, menyesuikan dengan panjang sensor yang kalian gunakan
const float _CALIBRATION_WATER_LEVEL = 0.48;


void readSensorwaterlevel() {
  _waterSensorread = analogRead(PIN_WATERLEVEL); // membaca tengan dari sensor dalam bentuk integer
  gWaterheight =  _waterSensorread * _SENSOR_LENGTH/ADC_RESOLUTION - 0.48 ;
  _waterSensorvoltage = _waterSensorread * V_REF_5V/ADC_RESOLUTION;

  #if defined DEBUG_ALL || defined DEBUG_WATER_LEVEL
  Serial.print("Sensor Voltage = ");
  Serial.print(_waterSensorvoltage);
  Serial.println(" V");
  Serial.print("Tinggi Air = ");
  Serial.print(gWaterheight);
  Serial.println(" cm ");
  Serial.println();
  #endif
}
