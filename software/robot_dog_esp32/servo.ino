#define SERVO_MIN 600
#define SERVO_MAX 2400
#define SERVO_FREQ 330

float testAngle = 0;
float testAngleInc = 0.5;
bool testAngleWay = true;

void initServo()
{
  Serial.print("Servo ");
  
  pwm.begin();
  pwm.setOscillatorFrequency(27000000);  // The int.osc. is closer to 27MHz
  pwm.setPWMFreq(SERVO_FREQ);  // This is the maximum PWM frequency of servo

  Serial.println();
}

void setServoToMiddle(int id)
{
  for (int i = 0; i < LEG_NUM; i++) {
    legs[i].angle.alpha = M_PI_2;
    legs[i].angle.beta  = M_PI_2;
    legs[i].angle.gamma = M_PI_2;
  }
}


void servoSet()
{
  for (int i = 0; i < LEG_NUM; i++) {
    setLegPWM(legs[i]);
  }
}

bool setAngleDeg(leg &_leg, int angleId, double deg)
{
  // TODO limits?
  double rad = degToRad(deg);
  switch (angleId) {
    case ALPHA:
      _leg.angle.alpha = rad;
      break;
    case BETA:
      _leg.angle.beta  = rad;
      break;
    case GAMMA:
      _leg.angle.gamma = rad;
      break;
  }

  return true;
}

double getAngleDeg(leg &_leg, int angleId)
{
  switch (angleId) {
    case ALPHA:
      return radToDeg(_leg.angle.alpha);
      break;
    case BETA:
      return radToDeg(_leg.angle.beta);
      break;
    case GAMMA:
      return radToDeg(_leg.angle.gamma);
      break;
  }

  return 0.0;
}
