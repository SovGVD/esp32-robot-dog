void displayHALTrim(leg &_leg, int angleId) {
  if (BUTTON_STATE[BUTTON_UP] || BUTTON_STATE[BUTTON_DOWN]) {
    switch (angleId) {
      case ALPHA:
        displayHALTrim(_leg.hal.trim.alpha, BUTTON_STATE[BUTTON_DOWN]);
        break;
      case BETA:
        displayHALTrim(_leg.hal.trim.beta,  BUTTON_STATE[BUTTON_DOWN]);
        break;
      case GAMMA:
        displayHALTrim(_leg.hal.trim.gamma, BUTTON_STATE[BUTTON_DOWN]);
        break;
    }

  }
  display.println("- [UP]");
    switch (angleId) {
      case ALPHA:
        display.println(displayAngle(_leg.hal.trim.alpha));
        break;
      case BETA:
        display.println(displayAngle(_leg.hal.trim.beta));
        break;
      case GAMMA:
        display.println(displayAngle(_leg.hal.trim.gamma));
        break;
    }
  display.println("+ [DOWN]");  

}

void displayHALTrim(double &_value, bool inc) {
  if (inc && _value < LEG_TRIM_LIMIT) {
    _value = _value + LEG_TRIM_INC;
  } else if (!inc && _value > -LEG_TRIM_LIMIT) {
    _value = _value - LEG_TRIM_INC;
  }
}


void displayHALTrimSave(leg &_leg) {
  settingsSaveTrimLeg(_leg);
  menuBack();
}

void menuDisplayHALTrimSave(int id) {
  displayHALTrimSave(legs[id]);
}


// -------------------------

// LEFT FRONT
void displayHALTrimLF(int angle) {
  displayHALTrim(legs[LEGLF], angle);
}

// RIGHT FRONT
void displayHALTrimRF(int angle) {
  displayHALTrim(legs[LEGRF], angle);
}

// LEFT HIND
void displayHALTrimLH(int angle) {
  displayHALTrim(legs[LEGLH], angle);
}

// RIGHT HIND
void displayHALTrimRH(int angle) {
  displayHALTrim(legs[LEGRH], angle);
}
