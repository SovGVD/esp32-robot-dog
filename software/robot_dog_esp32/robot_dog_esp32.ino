#include <math.h>
#include "def.h"
#include "config.h"

#include <Wire.h>
#include "menu.h"
#include "libs/IK/geometry.h"
#include "libs/IK/leg.h"
#include "libs/IK/IK.h"
#include "libs/IK/IK.cpp"
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_PWMServoDriver.h>
#include "libs/MPU9250/MPU9250.h"


Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

uint32_t currentTime;
uint32_t loopTime;

// buttons
unsigned int BUTTON_VALUES[4] = {  1900,  3000,  2300,  1500 };
bool BUTTON_STATE[4]          = { false, false, false, false };

// HAL
figure body = {
  {  0,  0,  0},
  {  0,  0,  0}
};


leg legs[LEG_NUM] = {
  {
    {0, 0, 0},
    {LEG_SIZE_L1, LEG_SIZE_L2, LEG_SIZE_L3},
    {0,1,2},  // pins
    {LEG_ANGLE_ALPHA_MIN, LEG_ANGLE_BETA_MIN, LEG_ANGLE_GAMMA_MIN},
    {LEG_ANGLE_ALPHA_MAX, LEG_ANGLE_BETA_MAX, LEG_ANGLE_GAMMA_MAX},
    {0,0,0},
    {LEG_ANGLE_ALPHA, LEG_ANGLE_BETA, LEG_ANGLE_GAMMA},
    {0,0,0},
    {true}
  },
  {
    {0, 0, 0},
    {LEG_SIZE_L1, LEG_SIZE_L2, LEG_SIZE_L3},
    {4,5,6},
    {LEG_ANGLE_ALPHA_MIN, LEG_ANGLE_BETA_MIN, LEG_ANGLE_GAMMA_MIN},
    {LEG_ANGLE_ALPHA_MAX, LEG_ANGLE_BETA_MAX, LEG_ANGLE_GAMMA_MAX},
    {0,0,0},
    {LEG_ANGLE_ALPHA, LEG_ANGLE_BETA, LEG_ANGLE_GAMMA},
    {0,0,0},
    {true}
  },
  {
    {0, 0, 0},
    {LEG_SIZE_L1, LEG_SIZE_L2, LEG_SIZE_L3},
    {8,9,10},
    {LEG_ANGLE_ALPHA_MIN, LEG_ANGLE_BETA_MIN, LEG_ANGLE_GAMMA_MIN},
    {LEG_ANGLE_ALPHA_MAX, LEG_ANGLE_BETA_MAX, LEG_ANGLE_GAMMA_MAX},
    {0,0,0},
    {LEG_ANGLE_ALPHA, LEG_ANGLE_BETA, LEG_ANGLE_GAMMA},
    {0,0,0},
    {true}
  },
  {
    {0, 0, 0},
    {LEG_SIZE_L1, LEG_SIZE_L2, LEG_SIZE_L3},
    {12,13,14},
    {LEG_ANGLE_ALPHA_MIN, LEG_ANGLE_BETA_MIN, LEG_ANGLE_GAMMA_MIN},
    {LEG_ANGLE_ALPHA_MAX, LEG_ANGLE_BETA_MAX, LEG_ANGLE_GAMMA_MAX},
    {0,0,0},
    {LEG_ANGLE_ALPHA, LEG_ANGLE_BETA, LEG_ANGLE_GAMMA},
    {0,0,0},
    {true}
  }
};

IK ikLegLF(legs[LEGLF], body);
IK ikLegRF(legs[LEGRF], body);
IK ikLegLB(legs[LEGLB], body);
IK ikLegRB(legs[LEGRB], body);



void setup()
{
  
  Serial.begin(SERIAL_BAUD);

  initDisplay();
  initMenu();
  initIMU();
  initHAL();
  delay(2000);
}

void loop()
{
  currentTime = micros();
  
  updateIMU();
  updateLegs();
  buttonsUpdate();
  displayMenu();
  displayMenuActivity();
  servoSet(); // TODO another thread
  buttonsReset();
  
  displayPing();
  loopTime = micros() - currentTime;  // i want to know full loop time, and yes it will be previous value in displayPing  
}
