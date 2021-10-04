//define unique magnetometers
Adafruit_LSM303_Mag_Unified mag1 = Adafruit_LSM303_Mag_Unified(12345);
Adafruit_LSM303_Mag_Unified mag2 = Adafruit_LSM303_Mag_Unified(12346);

sensors_event_t event1;
sensors_event_t event2;

const double L = 5; // distance between magnetometers

void initMagnetometers(){
  mag1.enableAutoRange(true);
  mag2.enableAutoRange(true);
  if (!mag1.begin()) {
    /* There was a problem detecting the LSM303 ... check your connections */
    Serial.println("Ooops, first LSM303 magnetometer not detected ... Check your wiring!");
    while (1);
  }
  if (!mag2.begin()) {
    /* There was a problem detecting the LSM303 ... check your connections */
    Serial.println("Ooops, second LSM303 magnetometer not detected ... Check your wiring!");
    while (1);
  }
}

void updateMagneticReadings(){
  // get new values for both magnetometers 
  mag1.getEvent(&event1);
  mag2.getEvent(&event2);
}

double getA1(){ return event1.magnetic.x; }
double getB1(){ return event1.magnetic.y; }
double getC1(){ return event1.magnetic.z; }
double getA2(){ return event2.magnetic.x; }
double getB2(){ return event2.magnetic.y; }
double getC2(){ return event2.magnetic.z; }

double getHeadingDeviation(double a1, double b1){
  return atan2(b1, a1);
}

double getHorizontalOffset(double a1, double b1, double c1, double a2, double b2, double c2){
  return (L * cos(getHeadingDeviation(a1, b1)) * (c1 * sqrt(pow(a2, 2) + pow(b2, 2)) + c2) * sqrt(pow(a1, 2) + pow(b1, 2)))
  / (2 * (-c1 * sqrt(pow(a2, 2) + pow(b2, 2)) + c2 * sqrt(pow(a1, 2) + pow(b1, 2))));
}

double getVerticalOffset(double a1, double b1, double c1, double a2, double b2, double c2){
  return (L* b1 * sqrt(pow(a2, 2) + pow(b2, 2)))
  / (c1 * sqrt(pow(a2, 2) + pow(b2, 2)) - c2 * sqrt(pow(a1, 2) + pow(b1, 2)));  
}
