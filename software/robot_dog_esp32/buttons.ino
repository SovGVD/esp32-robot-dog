#define BUTTON_ADC_PIN 32

#define BUTTON_DEADBAND 200

#define BUTTON_BACK 0
#define BUTTON_OK   1
#define BUTTON_UP   2
#define BUTTON_DOWN 3
#define BUTTON_NONE 99999;

/*
 *  0(back)  2(up)
 *  1(ok)    3(down)
 */

// TODO only one press
unsigned int BUTTON_VALUES[4] = {  1900,  3000,  2300,  1500 };
bool BUTTON_STATE[4]          = { false, false, false, false };
unsigned int BUTTON_ADC_VALUE = 0;
unsigned int BUTTON_LAST_PRESSED = BUTTON_NONE;

void buttonsUpdate() {
  BUTTON_ADC_VALUE = analogRead(BUTTON_ADC_PIN);
  for (int i=0;i<4;i++) {
    if (i == BUTTON_LAST_PRESSED) {
      if (buttonState(i)) {
        buttonsReset();
        break;
      } else {
        BUTTON_LAST_PRESSED = BUTTON_NONE;
      }
    }
    if (buttonState(i)) {
      BUTTON_LAST_PRESSED = i;
    }
    BUTTON_STATE[i] = buttonState(i);
  }
  if (BUTTON_STATE[BUTTON_BACK]) {
    menuBack();
    buttonsReset();
  }
}

void buttonsReset() {
  for (int i=0;i<4;i++) {
    BUTTON_STATE[i] = false;
  }
}

bool buttonState(int i)
{
  return (BUTTON_ADC_VALUE > (BUTTON_VALUES[i] - BUTTON_DEADBAND)) && (BUTTON_ADC_VALUE < (BUTTON_VALUES[i] + BUTTON_DEADBAND));
}
