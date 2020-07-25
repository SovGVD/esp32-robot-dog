#include <math.h>

#include "libs/IK/geometry.h"
#include "libs/IK/leg.h"
#include "libs/IK/IK.h"
#include "libs/planner/planner.h"
#include "libs/balance/balance.h"
#include "libs/gait/gait.h"

#include "def.h"
#include "config.h"
#include "config_wifi.h"
#include <EEPROM.h>
#include "WiFi.h"
#include "ESPAsyncWebServer.h"
#include "web/index.html.gz.h"
#include "cli.h"

#include <Wire.h>

#include "libs/IK/IK.cpp"
#include "libs/planner/planner.cpp"
#include "libs/balance/balance.cpp"
#include "libs/gait/gait.cpp"

#include <Adafruit_PWMServoDriver.h>
#include "libs/MPU9250/MPU9250.h"

// run commands on diferent cores (FAST for main, SLOW for services)
bool runCommandFASTCore = false;
bool runCommandSLOWCore = false;
cliFunction cliFunctionFAST;
cliFunction cliFunctionSLOW;
double cliFunctionFASTVar = 0.0;
double cliFunctionSLOWVar = 0.0;

TwoWire WireServices = TwoWire(1);
TaskHandle_t ServicesTask;

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

unsigned long currentTime;
unsigned long previousTime;
unsigned long loopTime;

bool disableHAL = false;

// Gait
uint16_t ticksPerGaitItem    = 0;
uint16_t ticksToNextGaitItem = 0;
uint8_t  currentGait         = 0;
uint8_t  nextGait            = 0;
double   gaitItemProgress    = 0;
double   gaitProgress[]      = {0, 0, 0, 0};

transition bodyTransition;
transitionParameters bodyTransitionParams = {{0,0,0}, {0,0,0}, 0};

//Move
moveVector vector = {
  {0, 0, 0},
  {0, 0, 0}
};

//Failsafe
bool FS_FAIL = false;
uint8_t FS_WS_count = 0;

// HAL
point balanceOffset = {0, 15, 0};

figure body = {
  {  0,  0,  0},
  {  0,  0,  0}
};

leg legs[LEG_NUM] = {
  // LEFT FRONT
  {
    {LEGLF, "LF"},
    { -LEG_BODY_X,  LEG_BODY_Y_F,   LEG_BODY_Z},
    {-LEG_POINT_X, LEG_POINT_Y_F, -LEG_POINT_Z},
    { LEG_SIZE_L1,   LEG_SIZE_L2,  LEG_SIZE_L3},
    {LEG_ANGLE_ALPHA_MIN, LEG_ANGLE_BETA_MIN, LEG_ANGLE_GAMMA_MIN},
    {LEG_ANGLE_ALPHA_MAX, LEG_ANGLE_BETA_MAX, LEG_ANGLE_GAMMA_MAX},
    {
      {  0,  1,   2},  // 3 servo pins
      {  0,  0,   0},  // trim
      {  4,  2, 1.5}   // gear ratio, first and last one is 16 groves on servo and 24 groves on leg
    },
    {   -LEG_POINT_X,  LEG_POINT_Y_F,    -LEG_POINT_Z},
    {LEG_ANGLE_ALPHA, LEG_ANGLE_BETA, LEG_ANGLE_GAMMA},
    {true, true, false, false, false, true},
    {true, 34, 2000}
  },
  // RIGHT FRONT
  {
    {LEGRF, "RF"},
    { LEG_BODY_X,  LEG_BODY_Y_F,   LEG_BODY_Z},
    {LEG_POINT_X, LEG_POINT_Y_F, -LEG_POINT_Z},
    {LEG_SIZE_L1,   LEG_SIZE_L2,  LEG_SIZE_L3},
    {LEG_ANGLE_ALPHA_MIN, LEG_ANGLE_BETA_MIN, LEG_ANGLE_GAMMA_MIN},
    {LEG_ANGLE_ALPHA_MAX, LEG_ANGLE_BETA_MAX, LEG_ANGLE_GAMMA_MAX},
    {
      {  4,  5,   6},
      {  0,  0,   0},
      {  4,  2, 1.5}
    },
    {    LEG_POINT_X,  LEG_POINT_Y_F,    -LEG_POINT_Z},
    {LEG_ANGLE_ALPHA, LEG_ANGLE_BETA, LEG_ANGLE_GAMMA},
    {false, true, false, true, true, false},
    {true, 35, 2000}
  },
  // LEFT HIND
  {
    {LEGLH, "LH"},
    { -LEG_BODY_X,  -LEG_BODY_Y_H,   LEG_BODY_Z},
    {-LEG_POINT_X, -LEG_POINT_Y_H, -LEG_POINT_Z},
    { LEG_SIZE_L1,    LEG_SIZE_L2,  LEG_SIZE_L3},
    {LEG_ANGLE_ALPHA_MIN, LEG_ANGLE_BETA_MIN, LEG_ANGLE_GAMMA_MIN},
    {LEG_ANGLE_ALPHA_MAX, LEG_ANGLE_BETA_MAX, LEG_ANGLE_GAMMA_MAX},
    {
      {  8,  9,  10},
      {  0,  0,   0},
      {  4,  2, 1.5}
    },
    {   -LEG_POINT_X, -LEG_POINT_Y_H,    -LEG_POINT_Z},
    {LEG_ANGLE_ALPHA, LEG_ANGLE_BETA, LEG_ANGLE_GAMMA},
    {true, true, false, true, false, true},
    {true, 39, 2000}
  },
  // RIGHT HIND
  {
    {LEGRH, "RH"},
    { LEG_BODY_X,  -LEG_BODY_Y_H,   LEG_BODY_Z},
    {LEG_POINT_X, -LEG_POINT_Y_H, -LEG_POINT_Z},
    {LEG_SIZE_L1,    LEG_SIZE_L2,  LEG_SIZE_L3},
    {LEG_ANGLE_ALPHA_MIN, LEG_ANGLE_BETA_MIN, LEG_ANGLE_GAMMA_MIN},
    {LEG_ANGLE_ALPHA_MAX, LEG_ANGLE_BETA_MAX, LEG_ANGLE_GAMMA_MAX},
    {
      { 12, 13,  14},
      {  0,  0,   0},
      {  4,  2, 1.5}
    },
    {    LEG_POINT_X, -LEG_POINT_Y_H,    -LEG_POINT_Z},
    {LEG_ANGLE_ALPHA, LEG_ANGLE_BETA, LEG_ANGLE_GAMMA},
    {false, true, false, false, true, false},
    {true, 36, 2000}
  }
};

IK ikLegLF(legs[LEGLF], body);
IK ikLegRF(legs[LEGRF], body);
IK ikLegLH(legs[LEGLH], body);
IK ikLegRH(legs[LEGRH], body);

/* We need predict future position of legs/body */
planner walkPlanner(
  vector,
  body,
  legs[LEGLF],
  legs[LEGRF],
  legs[LEGLH],
  legs[LEGRH]
);

/* and balance it someway */
balance bodyBalance(
  balanceOffset,
  body,
  legs[LEGLF],
  legs[LEGRF],
  legs[LEGLH],
  legs[LEGRH]
);

// WebServer
bool clientOnline = false;
int WiFiMode = AP_MODE;
IPAddress WiFiIP;
AsyncWebServer server(80);
AsyncWebSocket ws("/ws");

// CLI
Stream *cliSerial;


void setup()
{
  Serial.begin(SERIAL_BAUD);
  Wire.begin();

  delay(500);

  initSettings();
  initIMU();
  initHAL();
  initGait();
  initWiFi();
  initWebServer();

  
  xTaskCreatePinnedToCore(
    servicesLoop,   /* Task function. */
    "Services",     /* name of task. */
    10000,       /* Stack size of task */
    NULL,        /* parameter of the task */
    1,           /* priority of the task */
    &ServicesTask,      /* Task handle to keep track of created task */
    0);          /* pin task to core 0 */
}

/**
   Main loop for all major things
   Core 1
*/
void loop()
{
  currentTime = millis();
  if (currentTime - previousTime >= LOOP_TIME) {
    previousTime = currentTime;

    updateFailsafe();
    updateIMU();
    updateGait();
    updateHAL();
    doHAL();

    updateWiFi();
    runFASTCommand();
    

    FS_WS_count++;

    loopTime = millis() - currentTime;
  }
}

/**
   Loop for service things, like CLI
   Core 0
*/
void servicesSetup() {
  WireServices.begin(SLOW_SDA, SLOW_SCL);
  cliSerial = &Serial;
  initCLI();
}

void servicesLoop(void * pvParameters) {
  servicesSetup();

  for (;;) {
    runSLOWCommand();
    updateCLI();
    delay(100);
  }
}

void runFASTCommand()
{
  if (runCommandFASTCore) {
    runCommandFASTCore = false;
    cliFunctionFAST(cliFunctionFASTVar);
  }
}

void runSLOWCommand()
{
  if (runCommandSLOWCore) {
    runCommandSLOWCore = false;
    cliFunctionSLOW(cliFunctionSLOWVar);
  }
}

/**
   TODO
    - calculate center of mass and use it for balance
*/
