/* Control Mechanical operation */

/*  1). Checking water in the box, if water height = ... , turn on relay 1 (PUMP A)
 *  2). Turn on servo to reel the hose
 *  3). if no water in the box, turn on relay 2, pumping from seawater. 
 *  4). Waiting sensor to finish it's job
 *  5). turn on relay 1 to empty the water box (PUMP A).
 *  6). Turn on servo to roll back hose
 */

// emptying water box
void turnOnrelay1(){
  digitalWrite(PIN_RELAY_1, LOW);
}

void turnOffrelay1(){
  digitalWrite(PIN_RELAY_1, HIGH);
}

// take water from seawater
void turnOnrelay2(){
  digitalWrite(PIN_RELAY_2, LOW);
}

// 
void turnOffrelay2(){
  digitalWrite(PIN_RELAY_2, HIGH);
}
