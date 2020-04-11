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

#include <Wire.h>
#include "menu.h"

#include "libs/IK/IK.cpp"
#include "libs/planner/planner.cpp"
#include "libs/balance/balance.cpp"
#include "libs/gait/gait.cpp"

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_PWMServoDriver.h>
#include "libs/MPU9250/MPU9250.h"

TwoWire WireServices = TwoWire(1);
TaskHandle_t ServicesTask;

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &WireServices, OLED_RESET);

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

unsigned long currentTime;
unsigned long previousTime;
unsigned long loopTime;

bool disableHAL = false;

// buttons
unsigned int BUTTON_VALUES[4] = {  1900,  3000,  2300,  1500 };
bool BUTTON_STATE[4]          = { false, false, false, false };

// Gait
uint16_t ticksPerGaitItem    = 0;
uint16_t ticksToNextGaitItem = 0;
uint8_t  currentGait         = 0;
uint8_t  nextGait            = 0;
double   gaitProgress[]      = {0, 0, 0, 0};

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
    { -LEG_BODY_X, LEG_BODY_Y, LEG_BODY_Z},
    { -LEG_POINT_X, LEG_POINT_Y, -LEG_POINT_Z},
    {LEG_SIZE_L1, LEG_SIZE_L2, LEG_SIZE_L3},
    {LEG_ANGLE_ALPHA_MIN, LEG_ANGLE_BETA_MIN, LEG_ANGLE_GAMMA_MIN},
    {LEG_ANGLE_ALPHA_MAX, LEG_ANGLE_BETA_MAX, LEG_ANGLE_GAMMA_MAX},
    {
      {   0,  1,   2},  // 3 servo pins
      {   0,  0,   0},  // trim
      { 1.5,  1, 1.5}   // gear ratio, first and last one is 16 groves on servo and 24 groves on leg
    },
    { -LEG_POINT_X, LEG_POINT_Y, -LEG_POINT_Z},
    {LEG_ANGLE_ALPHA, LEG_ANGLE_BETA, LEG_ANGLE_GAMMA},
    {true, true, false, true, true, false},
    {true, 34, 2000}
  },
  // RIGHT FRONT
  {
    {LEGRF, "RF"},
    {LEG_BODY_X, LEG_BODY_Y, LEG_BODY_Z},
    {LEG_POINT_X, LEG_POINT_Y, -LEG_POINT_Z},
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
    { -LEG_BODY_X, -LEG_BODY_Y, LEG_BODY_Z},
    { -LEG_POINT_X, -LEG_POINT_Y, -LEG_POINT_Z},
    {LEG_SIZE_L1, LEG_SIZE_L2, LEG_SIZE_L3},
    {LEG_ANGLE_ALPHA_MIN, LEG_ANGLE_BETA_MIN, LEG_ANGLE_GAMMA_MIN},
    {LEG_ANGLE_ALPHA_MAX, LEG_ANGLE_BETA_MAX, LEG_ANGLE_GAMMA_MAX},
    {
      {   8,  9,   10},
      {   0,  0,    0},
      { 1.5,  1,  1.5}
    },
    { -LEG_POINT_X, -LEG_POINT_Y, -LEG_POINT_Z},
    {LEG_ANGLE_ALPHA, LEG_ANGLE_BETA, LEG_ANGLE_GAMMA},
    {true, true, false, false, true, false},
    {true, 39, 2000}
  },
  // RIGHT HIND
  {
    {LEGRH, "RH"},
    {LEG_BODY_X, -LEG_BODY_Y, LEG_BODY_Z},
    {LEG_POINT_X, -LEG_POINT_Y, -LEG_POINT_Z},
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
    {false, true, false, true, false, true},
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


void setup()
{
  Serial.begin(SERIAL_BAUD);
  Wire.begin();

  xTaskCreatePinnedToCore(
    servicesLoop,   /* Task function. */
    "Services",     /* name of task. */
    10000,       /* Stack size of task */
    NULL,        /* parameter of the task */
    1,           /* priority of the task */
    &ServicesTask,      /* Task handle to keep track of created task */
    0);          /* pin task to core 0 */
  delay(500);

  initSettings();
  initMenu();
  initIMU();
  initHAL();
  initGait();
  initWiFi();
  initWebServer();
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

    //updateWiFi();

    FS_WS_count++;

    loopTime = millis() - currentTime;
  }
}

/**
   Loop for service things, like display
   Core 0
*/
void servicesLoop(void * pvParameters) {
  WireServices.begin(SCREEN_SDA, SCREEN_SCL);
  initDisplay();

  for (;;) {
    buttonsUpdate();
    displayMenu();
    displayMenuActivity();
    buttonsReset();

    displayPing();
    delay(200);
  }
}

/**
   TODO
    - calculate center of mass and use it for balance
*/
