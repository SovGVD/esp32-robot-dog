#include <Wire.h>
#include "menu.h";
#include "leg.h";
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_PWMServoDriver.h>
#include "libs/MPU9250/MPU9250.h"

#include "def.h"
#include "config.h"

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

uint32_t currentTime;
uint32_t loopTime;

void setup()
{
  Serial.begin(SERIAL_BAUD);

  initDisplay();
  initMenu();
  initIMU();
  initServo();
  delay(2000);
}

void loop()
{
  currentTime = micros();
  
  updateIMU();
  buttonsUpdate();
  displayMenu();
  displayMenuActivity();
  servoSet();
  buttonsReset();
  
  displayPing();
  loopTime = micros() - currentTime;  // i want to know full loop time, and yes it will be previous value in displayPing  
}
