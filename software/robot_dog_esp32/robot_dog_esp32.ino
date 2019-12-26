#include <Wire.h>
#include "menu.h";
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_PWMServoDriver.h>
#include <MPU9250.h>

#include "def.h"
#include "config.h"

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);


void setup()
{
  Serial.begin(SERIAL_BAUD);

  initDisplay();
  initMenu();
  initIMU();
  delay(2000);
}

void loop()
{
  updateIMU();
  buttonsUpdate();
  displayMenu();
  displayMenuActivity();
  displayPing();
  buttonsReset();
  delay(100);
}
