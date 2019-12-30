#define SERVO_MIN 600
#define SERVO_MAX 2400
#define SERVO_FREQ 330

#define LEG_NUM 4

float testAngle = 0;
float testAngleInc = 0.5;
bool testAngleWay = true;

leg legs[LEG_NUM] = {
  {90, 90, 90,    0,  1,  2,   0, 0, 0,   true},
  {90, 90, 90,    4,  5,  6,   0, 0, 0,   true},
  {90, 90, 90,    8,  9, 10,   0, 0, 0,   true},
  {90, 90, 90,   12, 13, 14,   0, 0, 0,   true}
};

void initServo()
{
  display.println("Init servo...");
  display.display();
  
  pwm.begin();
  pwm.setOscillatorFrequency(27000000);  // The int.osc. is closer to 27MHz
  pwm.setPWMFreq(SERVO_FREQ);  // This is the maximum PWM frequency of servo
}


void servoTest() {
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
  display.clearDisplay();
  display.setCursor(0,0);
  display.print("Angle: ");
  display.println(testAngle, 4);

  display.print("Pulse: ");
  display.println(angleToPulse(testAngle), 4);

  display.print("Freq:  ");
  display.println(SERVO_FREQ);

  for (int i = 0; i < LEG_NUM; i++) {
    legs[i].coxaAngle  = testAngle;
    legs[i].femurAngle = testAngle;
    legs[i].tibiaAngle = testAngle;
  }
  
}

void setServoToMiddle()
{
  for (int i = 0; i < LEG_NUM; i++) {
    legs[i].coxaAngle  = 90;
    legs[i].femurAngle = 90;
    legs[i].tibiaAngle = 90;
  }
  menuBack();
}

void setServoToMin()
{
  for (int i = 0; i < LEG_NUM; i++) {
    legs[i].coxaAngle  = 0;
    legs[i].femurAngle = 0;
    legs[i].tibiaAngle = 0;
  }
  menuBack();
}

void setServoToMax()
{
  for (int i = 0; i < LEG_NUM; i++) {
    legs[i].coxaAngle  = 180;
    legs[i].femurAngle = 180;
    legs[i].tibiaAngle = 180;
  }
  menuBack();
}

double mapf(double val, double in_min, double in_max, double out_min, double out_max) {
    return (val - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

uint16_t angleToPulse(float angle) {

  double pulse = mapf(angle, 0, 180, 600, 2400);
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

void servoSet()
{
  for (int i = 0; i < LEG_NUM; i++) {
    pwm.setPWM(legs[i].coxaPin,  0, angleToPulse(legs[i].coxaAngle  + legs[i].coxaAngleTrim));
    pwm.setPWM(legs[i].femurPin, 0, angleToPulse(legs[i].femurAngle + legs[i].femurAngleTrim));
    pwm.setPWM(legs[i].tibiaPin, 0, angleToPulse(legs[i].tibiaAngle + legs[i].tibiaAngleTrim));
  }
}
