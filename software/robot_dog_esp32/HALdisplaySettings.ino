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

// -------------------------

// TODO
// I need to do something with that copy-paste hell

// LEFT FRONT
void displayHALTrimLFAlpha() {
  displayHALTrim(legs[LEGLF], ALPHA);
}

void displayHALTrimLFBeta() {
  displayHALTrim(legs[LEGLF], BETA);
}

void displayHALTrimLFGamma() {
  displayHALTrim(legs[LEGLF], GAMMA);
}

void displayHALTrimLFSave() {
  displayHALTrimSave(legs[LEGLF]);
}


// RIGHT FRONT
void displayHALTrimRFAlpha() {
  displayHALTrim(legs[LEGRF], ALPHA);
}

void displayHALTrimRFBeta() {
  displayHALTrim(legs[LEGRF], BETA);
}

void displayHALTrimRFGamma() {
  displayHALTrim(legs[LEGRF], GAMMA);
}

void displayHALTrimRFSave() {
  displayHALTrimSave(legs[LEGRF]);
}


// LEFT HIND
void displayHALTrimLHAlpha() {
  displayHALTrim(legs[LEGLH], ALPHA);
}

void displayHALTrimLHBeta() {
  displayHALTrim(legs[LEGLH], BETA);
}

void displayHALTrimLHGamma() {
  displayHALTrim(legs[LEGLH], GAMMA);
}

void displayHALTrimLHSave() {
  displayHALTrimSave(legs[LEGLH]);
}


// RIGHT HIND
void displayHALTrimRHAlpha() {
  displayHALTrim(legs[LEGRH], ALPHA);
}

void displayHALTrimRHBeta() {
  displayHALTrim(legs[LEGRH], BETA);
}

void displayHALTrimRHGamma() {
  displayHALTrim(legs[LEGRH], GAMMA);
}

void displayHALTrimRHSave() {
  displayHALTrimSave(legs[LEGRH]);
}
