/* Assign a unique ID to the sensors */
Adafruit_9DOF                 dof   = Adafruit_9DOF();
Adafruit_LSM303_Accel_Unified accel = Adafruit_LSM303_Accel_Unified(30301);
Adafruit_LSM303_Mag_Unified   mag   = Adafruit_LSM303_Mag_Unified(30302);

sensors_event_t accel_event;
sensors_event_t mag_event;
sensors_vec_t   orientation;


void initAhrs() 
{
  if(!accel.begin())
  {
    /* There was a problem detecting the LSM303 ... check your connections */
    Serial.println(F("Ooops, no LSM303 detected ... Check your wiring!"));
    while(1);
  }
  if(!mag.begin())
  {
    /* There was a problem detecting the LSM303 ... check your connections */
    Serial.println("Ooops, no LSM303 detected ... Check your wiring!");
    while(1);
  }
}


void updateAhrsReadings(){
  accel.getEvent(&accel_event);
  mag.getEvent(&mag_event);
  if (dof.fusionGetOrientation(&accel_event, &mag_event, &orientation))
  {}
}

double getRoll(){ return orientation.roll; }
double getPitch(){ return orientation.pitch; }
double getHeading(){ return orientation.heading; }
double getXAcceleration(){ return accel_event.acceleration.x; }
double getYAcceleration(){ return accel_event.acceleration.y; }
double getZAcceleration(){ return accel_event.acceleration.z; }
