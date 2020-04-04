#define SERVO_MIN 600
#define SERVO_MAX 2400
#define SERVO_FREQ 330

float testAngle = 0;
float testAngleInc = 0.5;
bool testAngleWay = true;

void initServo()
{
  display.print(" Servo ");
  display.display();
  
  pwm.begin();
  pwm.setOscillatorFrequency(27000000);  // The int.osc. is closer to 27MHz
  pwm.setPWMFreq(SERVO_FREQ);  // This is the maximum PWM frequency of servo
}


void servoTest(int id) {
  if (testAngleWay) {
    testAngle = testAngle + testAngleInc;
  } else {
    testAngle = testAngle - testAngleInc;
  }
  if (testAngle > 110) {
    testAngle = 110;
    testAngleWay = !testAngleWay;
  }
  if (testAngle < 70) {
    testAngle = 70;
    testAngleWay = !testAngleWay;
  }
  
  display.print("Angle: ");
  display.println(testAngle, 4);

  display.print("Pulse: ");
  display.println(angleToPulse(testAngle), 4);

  display.print("Freq:  ");
  display.println(SERVO_FREQ);

  for (int i = 0; i < LEG_NUM; i++) {
    legs[i].angle.alpha = testAngle;
    legs[i].angle.beta  = testAngle;
    legs[i].angle.gamma = testAngle;
  }
  
}

void setServoToMiddle(int id)
{
  for (int i = 0; i < LEG_NUM; i++) {
    legs[i].angle.alpha = M_PI/2;
    legs[i].angle.beta  = M_PI/2;
    legs[i].angle.gamma = M_PI/2;
  }
  menuBack();
}


void servoSet()
{
  for (int i = 0; i < LEG_NUM; i++) {
    setLegPWM(legs[i]);
  }
}
