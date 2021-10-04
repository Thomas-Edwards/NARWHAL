#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_LSM303_U.h>
#include <Adafruit_9DOF.h>
#include <Adafruit_L3GD20_U.h>
#include <math.h>

void setup() {
  Serial.begin(9600);
  initAhrs();
  initMagnetometers();
  //dive to searching level.
  //swim around until cable is detected
}

void loop() {

  updateDepthReadings();
  Serial.println("Depth in meters: ");
  Serial.print(getDepth());

  updateMagneticReadings();
  Serial.println("Heading Deviation: ");
  Serial.print(getHeadingDeviation(getA1(), getB1()));
  
  Serial.println("Horizontal Offset: ");
  Serial.print(getHorizontalOffset(getA1(), getB1(), getC1(), getA2(), getB2(), getC2()));
  
  Serial.println("Vertical Offset: ");
  Serial.print(getHorizontalOffset(getA1(), getB1(), getC1(), getA2(), getB2(), getC2()));

  updateAhrsReadings();
  Serial.println("Roll: ");
  Serial.print(getRoll());
  
  Serial.println("Pitch: ");
  Serial.print(getPitch());
  
  Serial.println("Heading: ");
  Serial.print(getHeading());

  Serial.println("X Acceleration: ");
  Serial.print(getXAcceleration());

  Serial.println("Y Acceleration: ");
  Serial.print(getYAcceleration());

  Serial.println("Z Acceleration: ");
  Serial.print(getZAcceleration());
  
  delay(100);
}
