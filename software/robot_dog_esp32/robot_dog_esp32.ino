#include "def.h"
#include "config.h"

#include <Wire.h>
#include <math.h>
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
    {10,20,20},
    {0,1,2},  // pins
    {0,0,0},
    {PI,PI,PI},
    {0,0,0},
    {0,0,0},
    {0,0,0},
    {true}
  },
  {
    {0, 0, 0},
    {10,20,20},
    {4,5,6},
    {0,0,0},
    {PI,PI,PI},
    {0,0,0},
    {0,0,0},
    {0,0,0},
    {true}
  },
  {
    {0, 0, 0},
    {10,20,20},
    {8,9,10},
    {0,0,0},
    {PI,PI,PI},
    {0,0,0},
    {0,0,0},
    {0,0,0},
    {true}
  },
  {
    {0, 0, 0},
    {10,20,20},
    {12,13,14},
    {0,0,0},
    {PI,PI,PI},
    {0,0,0},
    {0,0,0},
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
