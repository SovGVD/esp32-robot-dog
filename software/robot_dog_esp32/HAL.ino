void initHAL()
{
  display.println("Init HAL");
  initServo();
  initLegs();
  display.display();
}

void initLegs() {
  /*
  legs[LEGLF].foot = ikLegLF.solveByAngle();
  legs[LEGRF].foot = ikLegRF.solveByAngle();
  legs[LEGLB].foot = ikLegLB.solveByAngle();
  legs[LEGRB].foot = ikLegRB.solveByAngle();
  */
}

void updateHAL() {
  updateLegs();
}

void doHAL() {
  servoSet();
}

void updateLegs() {
  // TODO check `isSolved`
  #ifdef DEBUG_HAL_LEG
    Serial.println("LEGLF");
  #endif
  legs[LEGLF].angle = ikLegLF.solve().angle;
  
  #ifdef DEBUG_HAL_LEG
    Serial.println("LEGRF");
  #endif
  legs[LEGRF].angle = ikLegRF.solve().angle;
  
  #ifdef DEBUG_HAL_LEG
    Serial.println("LEGLB");
  #endif
  legs[LEGLB].angle = ikLegLB.solve().angle;

  #ifdef DEBUG_HAL_LEG
    Serial.println("LEGRB");
  #endif
  legs[LEGRB].angle = ikLegRB.solve().angle;
}

double mapf(double val, double in_min, double in_max, double out_min, double out_max) {
  return (val - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

uint16_t angleToPulse(double angleRad) {
  // TODO, angle expected to be between 0 and 180 deg (0 and PI)
  
  double pulse = mapf(angleRad, 0, M_PI, 600, 2400);
  // from Adafruit PWM lib
  double pulselength;
  pulselength = 1000000; // 1,000,000 us per second

  // Read prescale
  uint16_t prescale = pwm.readPrescale();

  // Calculate the pulse for PWM based on Equation 1 from the datasheet section
  // 7.3.5
  prescale += 1;
  pulselength *= prescale;
  pulselength /= pwm.getOscillatorFrequency();
  pulse /= pulselength;

  return pulse;
}

void setLegPWM(leg &_leg)
{
  
  // TODO limits and angle normalize
  pwm.setPWM(_leg.pin.alpha,  0, angleToPulse(_leg.angle.alpha + _leg.trim.alpha));
  pwm.setPWM(_leg.pin.beta,   0, angleToPulse(_leg.angle.beta  + _leg.trim.beta));
  pwm.setPWM(_leg.pin.gamma,  0, angleToPulse(_leg.angle.gamma + _leg.trim.gamma));
}
