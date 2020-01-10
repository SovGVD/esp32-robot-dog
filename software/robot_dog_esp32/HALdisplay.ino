double displayHALMovement = 1;  // mm
double displayHALRotation = M_PI/180;

// TODO too much copy-paste!!!

void displayHALMoveBodyXAngle() {
  displayHALMoveBody(XAXIS, true);
}

void displayHALMoveBodyYAngle() {
  displayHALMoveBody(YAXIS, true);
}

void displayHALMoveBodyZAngle() {
  displayHALMoveBody(ZAXIS, true);
}

void displayHALMoveBodyXPosition() {
  displayHALMoveBody(XAXIS, false);
}

void displayHALMoveBodyYPosition() {
  displayHALMoveBody(YAXIS, false);
}

void displayHALMoveBodyZPosition() {
  displayHALMoveBody(ZAXIS, false);
}


void displayHALButtonsBody(int axis) {
  // TODO  pitch/roll/yaw
  if (BUTTON_STATE[BUTTON_UP]) {
    switch (axis) {
      case XAXIS:
        body.position.x = body.position.x + displayHALMovement;
        break;
    case YAXIS:
        body.position.y = body.position.y + displayHALMovement;
        break;
    case ZAXIS:
        body.position.z = body.position.z + displayHALMovement;
        break;
    }
  } else if (BUTTON_STATE[BUTTON_DOWN]) {
    switch (axis) {
      case XAXIS:
        body.position.x = body.position.x - displayHALMovement;
        break;
      case YAXIS:
        body.position.y = body.position.y - displayHALMovement;
        break;
      case ZAXIS:
        body.position.z = body.position.z - displayHALMovement;
        break;
    }
  }
}

void displayHALMoveBody(int axis, bool displayAngles) {
  displayHALButtonsBody(axis);

  if (axis == XAXIS) displayHighlightBegin();
  display.print("X:");
  display.print(body.position.x, DISPLAY_DIGITS);
  displayHighlightEnd();
  display.print(" ");
  
  if (axis == YAXIS) displayHighlightBegin();
  display.print("Y:");
  display.print(body.position.y, DISPLAY_DIGITS);
  displayHighlightEnd();
  display.print(" ");
  
  if (axis == ZAXIS) displayHighlightBegin();
  display.print("Z:");
  display.println(body.position.z, DISPLAY_DIGITS);
  displayHighlightEnd();


  if (displayAngles) {
    displayHALAngles();
  } else {
    displayHALPositions();
  }
}

void displayHALPosition(leg &_leg) {
  if (_leg.sensor.onGround) displayHighlightBegin();
  display.print(_leg.id.title);
  display.print(" ");
  display.print(_leg.body.x + body.position.x, 0);
  display.print(",");
  display.print(_leg.body.y + body.position.y, 0);
  display.print(",");
  display.print(_leg.body.z + body.position.z, 0);

  display.print(" ");
  display.print(_leg.foot.x, 0);
  display.print(",");
  display.print(_leg.foot.y, 0);
  display.print(",");
  display.print(_leg.foot.z, 0);
  display.print(" ");
  displayHighlightEnd();
}

void displayHALAngle(leg &_leg) {
  if (_leg.sensor.onGround) displayHighlightBegin();
  display.print(_leg.id.title);
  display.print(" ");
  display.print(displayAngle(_leg.angle.alpha), 0);
  display.print(" ");
  display.print(displayAngle(_leg.angle.beta), 0);
  display.print(" ");
  display.println(displayAngle(_leg.angle.gamma), 0);
  displayHighlightEnd();
}

void displayHALPositions() {
  for (int i = 0; i < LEG_NUM; i++) {
    displayHALPosition(legs[i]);
  }
}

void displayHALAngles() {
  for (int i = 0; i < LEG_NUM; i++) {
    displayHALAngle(legs[i]);
  }
}

void displayDisableHAL() {
  disableHAL = true;
  displayHALStatus();
}

void displayEnableHAL() {
  disableHAL = false;
  displayHALStatus();
}

void displayHALStatus() {
  display.println("HAL status:");
  display.println(disableHAL?"disabled":"enabled"); // This is usuful to set servos to middle (90 deg or PI/2)
}


// tests
int HALTEST_delta = 10; // 10 mm

void displayHALTest1() {
  
}
