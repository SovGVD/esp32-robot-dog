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
