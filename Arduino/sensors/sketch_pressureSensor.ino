const float g = 9.81; //   in m/s^2 
const int waterDensity = 997; //   in Kg/m^3 
double depth;

void updateDepthReadings(){
  // read the input on analog pin 0:
  int sensorValue = analogRead(A0);
  // Convert the analog reading (which goes from 0 - 1023) to a voltage (0 - 5V):
  double voltage = sensorValue * (5.0 / 1023.0);
  // convert voltage to pressure in Pascals
  double pressure = (voltage/5-0.1)*(4/3)*1000000;
  // convert pressure to depth in meters
  depth = pressure / (g * waterDensity);
}

double getDepth(){ return depth; }

/*
10 meters underwater
pressure = 97706
voltage = .86
analog reading = 175.96

122 meters
pressure = 1200032.51
voltage = 5
analog reading = 1023
*/
