double displayHALMovement = 1;  // mm
double displayHALRotation = M_PI/180;

// TODO too much copy-paste!!!

void displayHALMoveBodyX() {
  displayHALMoveBody(XAXIS);
}

void displayHALMoveBodyY() {
  displayHALMoveBody(YAXIS);
}

void displayHALMoveBodyZ() {
  displayHALMoveBody(ZAXIS);
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

void displayHALMoveBody(int axis) {
  displayHALButtonsBody(axis);
  display.print("Move by ");
  switch (axis) {
    case XAXIS:
      display.print("X");
      break;
    case YAXIS:
      display.print("Y");
      break;
    case ZAXIS:
      display.print("Z");
      break;
    default:
      menuBack(); // something wrong, goes back to menu
      break;
  }
  display.println(" axis");
  
  if (axis == XAXIS) displayHighlightBegin();
  display.print("X: ");
  display.println(body.position.x, DISPLAY_DIGITS);
  displayHighlightEnd();
  
  if (axis == YAXIS) displayHighlightBegin();
  display.print("Y: ");
  display.println(body.position.y, DISPLAY_DIGITS);
  displayHighlightEnd();
  
  if (axis == ZAXIS) displayHighlightBegin();
  display.print("Z: ");
  display.println(body.position.z, DISPLAY_DIGITS);
  displayHighlightEnd();


  if (legs[LEGLF].sensor.onGround) displayHighlightBegin();
  display.print("LF ");
  display.print(displayAngle(legs[LEGLF].angle.alpha), 0);
  display.print(" ");
  display.print(displayAngle(legs[LEGLF].angle.beta), 0);
  display.print(" ");
  display.println(displayAngle(legs[LEGLF].angle.gamma), 0);
  displayHighlightEnd();

  if (legs[LEGRF].sensor.onGround) displayHighlightBegin();
  display.print("RF ");
  display.print(displayAngle(legs[LEGRF].angle.alpha), 0);
  display.print(" ");
  display.print(displayAngle(legs[LEGRF].angle.beta), 0);
  display.print(" ");
  display.println(displayAngle(legs[LEGRF].angle.gamma), 0);
  displayHighlightEnd();

  if (legs[LEGLB].sensor.onGround) displayHighlightBegin();
  display.print("LB ");
  display.print(displayAngle(legs[LEGLB].angle.alpha), 0);
  display.print(" ");
  display.print(displayAngle(legs[LEGLB].angle.beta), 0);
  display.print(" ");
  display.println(displayAngle(legs[LEGLB].angle.gamma), 0);

  if (legs[LEGRB].sensor.onGround) displayHighlightBegin();
  display.print("RB ");
  display.print(displayAngle(legs[LEGRB].angle.alpha), 0);
  display.print(" ");
  display.print(displayAngle(legs[LEGRB].angle.beta), 0);
  display.print(" ");
  display.println(displayAngle(legs[LEGRB].angle.gamma), 0);
  displayHighlightEnd();
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
