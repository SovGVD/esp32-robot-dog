double displayHALMovement = 1;  // mm
double displayHALRotation = M_PI/180;

void displayHALVector(int id) {
  if(FS_FAIL) displayHighlightBegin();
  display.print("X   :");
  display.println(vector.x, 4);

  display.print("Y   :");
  display.println(vector.y, 4);

  display.print("Z   :");
  display.println(vector.z, 4);

  display.print("AngZ:");
  display.println(vector.angZ, 4);
  displayHighlightEnd();
  
  display.print("FS  :");
  display.println(FS_WS_count);

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
  display.print(displayAngle(_leg.angle.alpha), 1);
  display.print(" ");
  display.print(displayAngle(_leg.angle.beta), 1);
  display.print(" ");
  display.println(displayAngle(_leg.angle.gamma), 1);
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

void displayToggleHAL(int toggle) {
  disableHAL = toggle == 1?true:false;
  displayHALStatus();
}

void displayHALStatus() {
  display.println("HAL status:");
  display.println(disableHAL?"disabled":"enabled"); // This is usuful to set servos to middle (90 deg or PI/2)
}


// tests
double HALTEST1_dx    = 0;
double HALTEST1_dy    = 0;
double HALTEST1_dz    = 0;
double HALTEST1_d     = 1;
int HALTEST1_stage = 0;
double HALTEST1_delta = 49.9; // +-50 mm (square 100x100)

void displayHALTest(int test) {
  switch (HALTEST1_stage) {
    case 0:
      HALTEST1_dy = HALTEST1_dy + HALTEST1_d;
      if (HALTEST1_dy >= HALTEST1_delta) HALTEST1_stage++;
      break;
    case 1:
      HALTEST1_dx = HALTEST1_dx + HALTEST1_d;
      if (HALTEST1_dx >= HALTEST1_delta) HALTEST1_stage++;
      break;
    case 2:
      HALTEST1_dy = HALTEST1_dy - HALTEST1_d;
      if (HALTEST1_dy <= -HALTEST1_delta) HALTEST1_stage++;
      break;
    case 3:
      HALTEST1_dx = HALTEST1_dx - HALTEST1_d;
      if (HALTEST1_dx <= -HALTEST1_delta) HALTEST1_stage=0;
      break;
    default:
      menuBack();
  }

  display.print("Stage ");
  display.println(HALTEST1_stage);

  display.print("dx:");
  display.println(HALTEST1_dx);
  display.print("dy:");
  display.println(HALTEST1_dy);

  displayHALTest1_LEGLF(legs[LEGLF]);
  displayHALTest1_LEGRF(legs[LEGRF]);
  displayHALTest1_LEGLH(legs[LEGLH]);
  displayHALTest1_LEGRH(legs[LEGRH]);

  displayHALAngles();
}

void displayHALTest1_LEGLF(leg &_leg) {
  _leg.foot.x = -LEG_POINT_X + HALTEST1_dx;
  _leg.foot.y =  LEG_POINT_Y + HALTEST1_dy;
  _leg.foot.z = -LEG_POINT_Z + HALTEST1_dz;
}

void displayHALTest1_LEGRF(leg &_leg) {
  _leg.foot.x =  LEG_POINT_X + HALTEST1_dx;
  _leg.foot.y =  LEG_POINT_Y + HALTEST1_dy;
  _leg.foot.z = -LEG_POINT_Z + HALTEST1_dz;
}


void displayHALTest1_LEGLH(leg &_leg) {
  _leg.foot.x = -LEG_POINT_X + HALTEST1_dx;
  _leg.foot.y = -LEG_POINT_Y + HALTEST1_dy;
  _leg.foot.z = -LEG_POINT_Z + HALTEST1_dz;
}

void displayHALTest1_LEGRH(leg &_leg) {
  _leg.foot.x =  LEG_POINT_X + HALTEST1_dx;
  _leg.foot.y = -LEG_POINT_Y + HALTEST1_dy;
  _leg.foot.z = -LEG_POINT_Z + HALTEST1_dz;
}


// ------------------

// TODO too much copy-paste!!!

void displayHALMoveBodyAngle(int axis) {
  displayHALMoveBody(axis, true);
}

void displayHALMoveBodyPosition(int axis) {
  displayHALMoveBody(axis, false);
}
