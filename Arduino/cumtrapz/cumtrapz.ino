#include <SimpleKalmanFilter.h>

void setup() {
  
Serial.begin(9600);
//randomSeed(analogRead(0)); uncomment this for truly random
compareAccelerations(true); //true = random values. false = positive linear values
  /*
  velocities[0] = 0;
  integrate(accelerations, velocities, readings, 1);
  positions[0] = 0;
  integrate(velocities, positions, readings, 1);
  Serial.begin(9600);
  for(int i = 0; i < readings; i++){
    Serial.println(positions[i]);
    delay(1000);
  }
  */

}

void compareAccelerations(boolean rando){
  const int readings = 200;
  double rawAccelerations[readings];
  double estimatedAccelerations[readings];
  if(rando){
    generateRandomAccelerations(rawAccelerations, readings);
  }
  else{
    generateLinearAccelerations(rawAccelerations, readings);
  }
  estimateAccelerations(rawAccelerations, estimatedAccelerations, readings);

  for(int i = 0; i < readings; i++){
    Serial.print(rawAccelerations[i]);
    Serial.print(",");
    Serial.println(estimatedAccelerations[i]);  
    delay(100);
  }
}

void comparePositions(){
  const int readings = 50;
  double rawAccelerations[readings];
  double rawVelocities[readings];
  double rawPositions[readings];
  double estimatedAccelerations[readings];
  double estimatedVelocities[readings];
  double estimatedPositions[readings];
  
  generateRandomAccelerations(rawAccelerations, readings);
  rawVelocities[0] = 0;
  integrate(rawAccelerations, rawVelocities, readings, 1);
  rawPositions[0] = 0;
  integrate(rawVelocities, rawPositions, readings, 1);
  
  estimateAccelerations(rawAccelerations, estimatedAccelerations, readings);
  estimatedVelocities[0] = 0;
  integrate(estimatedAccelerations, estimatedVelocities, readings, 1);
  estimatedPositions[0] = 0;
  integrate(estimatedVelocities, estimatedPositions, readings, 1);
  
  for(int i = 0; i < readings; i++){
    Serial.print(rawPositions[i]);
    Serial.print(",");
    Serial.println(estimatedPositions[i]);  
    delay(100);
  }

}

void demonstrateIntegration(){
  int len = 8;
  double accelerations[] = {0, 1, 2, 3, 4, 5, 6, 7};
  /*
  double accelerations[len];
  accelerations[0] = 0;
  for(int i = 1; i < len; i++){
    accelerations[i] = accelerations[i-1] + 0.5;
  }
  */
  double velocities[len];
  velocities[0] = 0;
  double positions[len];
  positions[0] = 0;

  integrate(accelerations, velocities, len, 1);
  integrate(velocities, positions, len, 1);

  for(int i = 0; i < len; i++){
    Serial.print(accelerations[i]);
    Serial.print(",");
    Serial.println(velocities[i]);
    //Serial.print(",");
    //Serial.println(positions[i]);
    delay(100);
  }
}

void generateRandomAccelerations(double list[], int len){
  list[0] = 0;
  double sign = 1;
  for(int i = 1; i < len; i++){
    long randNum = random(11);
    if(randNum < 2){
      sign *= -1;
      list[i] = list[i-1];
    }
    else if(randNum < 7){
      list[i] = list[i-1] + sign * 3;
    }
    else{
      list[i] = list[i-1] + sign * 4;
    }
    //uncomment to add noise
    list[i] = list[i] + random(1, 12) * random(-1, 2);
  }
}

void generateLinearAccelerations(double list[], int len){
  list[0] = 0;
  double sign = 1;
  for(int i = 1; i < len; i++){
    list[i] = i * 2;
    //uncomment to add noise
    list[i] = list[i] + random(1, 12) * random(-1, 2);
  }
}

void estimateAccelerations(double initial[], double result[], int len){
  SimpleKalmanFilter AccelerationKalmanFilter(0.5, 0.5, 0.01);
  for(int i = 0; i < len; i++){
    result[i] = AccelerationKalmanFilter.updateEstimate(initial[i]);
  }
}

//RECURSIVE APPROACH?
void integrate(double initial[], double result[], int len, double timeLapse){
  
  for(int i = 1; i < len; i++){
    result[i] = result[i-1] + 0.5*timeLapse*(initial[i-1] + initial[i]);
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  
  
}
