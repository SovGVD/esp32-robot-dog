#include <math.h>
#include "def.h"
#include "config.h"
#include <EEPROM.h>

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
bool disableHAL = false;

// buttons
unsigned int BUTTON_VALUES[4] = {  1900,  3000,  2300,  1500 };
bool BUTTON_STATE[4]          = { false, false, false, false };

// HAL
figure body = {
  {  0,  0,  0},
  {  0,  0,  0}
};

leg legs[LEG_NUM] = {
  // LEFT FRONT
  {
    {LEGLF, "LF"},
    {-LEG_BODY_X, LEG_BODY_Y, LEG_BODY_Z},
    {LEG_SIZE_L1, LEG_SIZE_L2, LEG_SIZE_L3},
    {LEG_ANGLE_ALPHA_MIN, LEG_ANGLE_BETA_MIN, LEG_ANGLE_GAMMA_MIN},
    {LEG_ANGLE_ALPHA_MAX, LEG_ANGLE_BETA_MAX, LEG_ANGLE_GAMMA_MAX},
    {
      {   0,  1,   2},  // 3 servo pins
      {   0,  0,   0},  // trim
      { 1.5,  1, 1.5}   // gear ratio, first and last one is 16 groves on servo and 24 groves on leg
    },
    {-LEG_POINT_X, LEG_POINT_Y, -LEG_POINT_Z},
    {LEG_ANGLE_ALPHA, LEG_ANGLE_BETA, LEG_ANGLE_GAMMA},
    {true, true, false, true, true, false},
    {true, 34, 2000}
  },
  // RIGHT FRONT
  {
    {LEGRF, "RF"},
    {LEG_BODY_X, LEG_BODY_Y, LEG_BODY_Z},
    {LEG_SIZE_L1, LEG_SIZE_L2, LEG_SIZE_L3},
    {LEG_ANGLE_ALPHA_MIN, LEG_ANGLE_BETA_MIN, LEG_ANGLE_GAMMA_MIN},
    {LEG_ANGLE_ALPHA_MAX, LEG_ANGLE_BETA_MAX, LEG_ANGLE_GAMMA_MAX},
    {
      {   4,  5,    6},
      {   0,  0,    0},
      { 1.5,  1,  1.5}
    },
    {LEG_POINT_X, LEG_POINT_Y, -LEG_POINT_Z},
    {LEG_ANGLE_ALPHA, LEG_ANGLE_BETA, LEG_ANGLE_GAMMA},
    {false, true, false, false, false, true},
    {true, 35, 2000}
  },
  // LEFT HIND
  {
    {LEGLH, "LH"},
    {-LEG_BODY_X, -LEG_BODY_Y, LEG_BODY_Z},
    {LEG_SIZE_L1, LEG_SIZE_L2, LEG_SIZE_L3},
    {LEG_ANGLE_ALPHA_MIN, LEG_ANGLE_BETA_MIN, LEG_ANGLE_GAMMA_MIN},
    {LEG_ANGLE_ALPHA_MAX, LEG_ANGLE_BETA_MAX, LEG_ANGLE_GAMMA_MAX},
    {
      {   8,  9,   10},
      {   0,  0,    0},
      { 1.5,  1,  1.5}
    },
    {-LEG_POINT_X, -LEG_POINT_Y, -LEG_POINT_Z},
    {LEG_ANGLE_ALPHA, LEG_ANGLE_BETA, LEG_ANGLE_GAMMA},
    {true, true, false, false, true, true},
    {true, 39, 2000}
  },
  // RIGHT HIND
  {
    {LEGRH, "RH"},
    {LEG_BODY_X, -LEG_BODY_Y, LEG_BODY_Z},
    {LEG_SIZE_L1, LEG_SIZE_L2, LEG_SIZE_L3},
    {LEG_ANGLE_ALPHA_MIN, LEG_ANGLE_BETA_MIN, LEG_ANGLE_GAMMA_MIN},
    {LEG_ANGLE_ALPHA_MAX, LEG_ANGLE_BETA_MAX, LEG_ANGLE_GAMMA_MAX},
    {
      {  12,  13,  14},
      {   0,   0,   0},
      { 1.5,   1, 1.5}
    },
    {LEG_POINT_X, -LEG_POINT_Y, -LEG_POINT_Z},
    {LEG_ANGLE_ALPHA, LEG_ANGLE_BETA, LEG_ANGLE_GAMMA},
    {false, true, false, true, false, false},
    {true, 36, 2000}
  }
};

IK ikLegLF(legs[LEGLF], body);
IK ikLegRF(legs[LEGRF], body);
IK ikLegLH(legs[LEGLH], body);
IK ikLegRH(legs[LEGRH], body);



void setup()
{
  Serial.begin(SERIAL_BAUD);

  initDisplay();
  initSettings();
  initMenu();
  initIMU();
  initHAL();

}

void loop()
{
  currentTime = micros();

  updateIMU();
  updateHAL();
  doHAL();

  buttonsUpdate();
  displayMenu();
  displayMenuActivity();
  buttonsReset();

  displayPing();
  loopTime = micros() - currentTime;  // i want to know full loop time, and yes it will be previous value in displayPing

}

/**
 * TODO
 *  - move display to another i2c and thread/task, sending data to display cost too much time
 *  - define M_PI/2
 */
