void initHAL()
{
  Serial.print("HAL ");
  initServo();
  initLegs();
  Serial.println();
}

void initLegs() {

}

void updateHAL() {
  updateLegs();
}

void doHAL() {
  servoSet();
}

void readLegsSensors() {
  // TODO that will be i2c ADC, not analog read
  // TODO enable if sensors available
  // TODO don't set to legs, this should be part of gait
  for (int i = 0; i < LEG_NUM; i++) {
    //legs[i].sensor.onGround = analogRead(legs[i].sensor.pin) > legs[i].sensor.threshold;
  }
}

void updateLegs() {
  if (!isHALEnabled()) return;

  readLegsSensors();
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
    Serial.println("LEGLH");
  #endif
  legs[LEGLH].angle = ikLegLH.solve().angle;

  #ifdef DEBUG_HAL_LEG
    Serial.println("LEGRH");
  #endif
  legs[LEGRH].angle = ikLegRH.solve().angle;
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
  pwm.setPWM(_leg.hal.pin.alpha,  0,  angleToPulse(limitServoAngle(getHALAngle(_leg.angle.alpha, _leg.hal.mid.alpha, _leg.hal.trim.alpha, _leg.hal.ratio.alpha, _leg.inverse.alpha))));
  pwm.setPWM(_leg.hal.pin.beta,   0,  angleToPulse(limitServoAngle(getHALAngle(_leg.angle.beta,  _leg.hal.mid.beta,  _leg.hal.trim.beta,  _leg.hal.ratio.beta,  _leg.inverse.beta ))));
  pwm.setPWM(_leg.hal.pin.gamma,  0,  angleToPulse(limitServoAngle(getHALAngle(_leg.angle.gamma, _leg.hal.mid.gamma, _leg.hal.trim.gamma, _leg.hal.ratio.gamma, _leg.inverse.gamma))));
}

double limitServoAngle(double angle)
{
  // TODO this is not right solution, we should restart calc to solve the angle instead of just limit if something wrong
  //      also this is nothing about real mechanical limits, so need TODO
  
  // default servo can handle angles from 0 to 180 (PI) degrees only
  if (angle < 0) angle = 0;
  if (angle > PI) angle = PI;

  return angle;
}

double getHALAngle(double angle, double mid, double trimAngle, double gearRatio, bool inverse) {
  angle = (angle - mid) * gearRatio + M_PI_2;
  if (inverse) angle = M_PI - angle;
  angle = angle + trimAngle;
  return angle;
}

double getHALTrim (leg &_leg, int angleId)
{
  switch (angleId) {
    case ALPHA:
      return _leg.hal.trim.alpha;
      break;
    case BETA:
      return _leg.hal.trim.beta;
      break;
    case GAMMA:
      return _leg.hal.trim.gamma;
      break;
  }

  return 0;
}

bool setHALTrim (leg &_leg, int angleId, double deg)
{
  double rad = degToRad(deg);
  if (rad >= LEG_TRIM_LIMIT || rad <= -LEG_TRIM_LIMIT) {
    return false;
  }
  
  switch (angleId) {
    case ALPHA:
      _leg.hal.trim.alpha = rad;
      break;
    case BETA:
      _leg.hal.trim.beta  = rad;
      break;
    case GAMMA:
      _leg.hal.trim.gamma = rad;
      break;
  }

  settingsSaveTrimLeg(_leg);
  _leg.hal.trim = settingsLoadTrimLeg(_leg);

  return true;
}

bool isHALEnabled()
{
  // This not correct, we are not enbale/disable HAL, but just disable servo position calculations
  return HALEnabled;
}
