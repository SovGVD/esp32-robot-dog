#define MENU_ITEMS_NUM  45
#define MENU_GROUPS_NUM 12 //ROOT as 0, so groups+1

// TODO use second INT value not only for the menu, but also for other functions
//      it should reduce amount of copy-pasted functions
//      e.g. 0, displayHALTrimLF[Alpha|Beta|Gamma] -> [ALPHA, BETA, GAMMA], displayHALTrimLF
//      DONT THINK ABOUT use MENU_ITEMS[MENU_CURRENT_GLOBAL_ITEM_INDEX] - it is terrible solution... or may be not =)

const menuItem MENU_ITEMS[MENU_ITEMS_NUM] = {
  { "Hardware", 2, menuSubMenu,        1, 0 },
  { "WiFi/BT",  0, menuDummyFunction,  1, 0 },
  { "Tests",    0, menuDummyFunction,  1, 0 },
  { "About",    0, displayAbout,       1, 0 },

  { "IMU/MAG",  3, menuSubMenu,        2, 1 },
  { "HAL",      5, menuSubMenu,        2, 1 },
  { "Servo",    4, menuSubMenu,        2, 1 },
  { "I2C scan", 0, displayI2CScan,     2, 1 },

  { "Status",        0, displayIMU,         3, 2 },
  { "Calibrate IMU", 0, calibrateIMU,       3, 2 },
  { "Calibrate MAG", 0, menuDummyFunction,  3, 2 },

  { "Set to middle", 0, setServoToMiddle,   4, 2},
  { "Run test(!!!)", 0, servoTest,          4, 2},
  { "Status",        0, menuDummyFunction,  4, 2},

  { "Body",    6, menuSubMenu,       5, 2 },
  { "Legs",    7, menuSubMenu,       5, 2 },
  { "Enable",  0, displayEnableHAL,  5, 2 },
  { "Disable", 0, displayDisableHAL, 5, 2 },

  { "P.MoveX (R/L)",  0, displayHALMoveBodyXPosition, 6, 5 },
  { "P.MoveY (F/B)",  0, displayHALMoveBodyYPosition, 6, 5 },
  { "P.MoveZ (U/D)",  0, displayHALMoveBodyZPosition, 6, 5 },
  { "A.MoveX (R/L)",  0, displayHALMoveBodyXAngle,    6, 5 },
  { "A.MoveY (F/B)",  0, displayHALMoveBodyYAngle,    6, 5 },
  { "A.MoveZ (U/D)",  0, displayHALMoveBodyZAngle,    6, 5 },
  { "Test",           0, displayHALTest1,             6, 5 },

  { "LEFT  FRONT",   8, menuSubMenu, 7, 5 },
  { "RIGHT FRONT",   9, menuSubMenu, 7, 5 },
  { "LEFT  HIND",   10, menuSubMenu, 7, 5 },
  { "RIGHT HIND",   11, menuSubMenu, 7, 5 },

  { "Alpha",  0, displayHALTrimLFAlpha,  8, 7 },
  { "Beta",   0, displayHALTrimLFBeta,   8, 7 },
  { "Gamma",  0, displayHALTrimLFGamma,  8, 7 },
  { "[Save]", 0, displayHALTrimLFSave,   8, 7 },

  { "Alpha",  0, displayHALTrimRFAlpha,  9, 7 },
  { "Beta",   0, displayHALTrimRFBeta,   9, 7 },
  { "Gamma",  0, displayHALTrimRFGamma,  9, 7 },
  { "[Save]", 0, displayHALTrimRFSave,   9, 7 },

  { "Alpha",  0, displayHALTrimLHAlpha, 10, 7 },
  { "Beta",   0, displayHALTrimLHBeta,  10, 7 },
  { "Gamma",  0, displayHALTrimLHGamma, 10, 7 },
  { "[Save]", 0, displayHALTrimLHSave,  10, 7 },

  { "Alpha",  0, displayHALTrimRHAlpha, 11, 7 },
  { "Beta",   0, displayHALTrimRHBeta,  11, 7 },
  { "Gamma",  0, displayHALTrimRHGamma, 11, 7 },
  { "[Save]", 0, displayHALTrimRHSave,  11, 7 }

};

menuGroup MENU_GROUPS_LENGTH[MENU_GROUPS_NUM];

#define MENU_LINE_HEIGHT 8
#define MENU_LINES       8  //must be multiply 2, e.g 2,4,6...

unsigned int MENU_CURRENT = 0;
unsigned int MENU_PREVIOUS = 0;
int MENU_CURRENT_ITEM_INDEX = 0;
int MENU_CURRENT_GLOBAL_ITEM_INDEX = 0;
unsigned int MENU_LIST_LENGTH = 0;
int MENU_START_INDEX = 0;
int MENU_END_INDEX = 0;

bool MENU_DISPLAY = true;


void initMenu()
{
  MENU_CURRENT = 1;
  MENU_CURRENT_ITEM_INDEX = 0;

  // find length of available menu groups
  for (int i=0;i<MENU_ITEMS_NUM;i++) {
    if (MENU_GROUPS_LENGTH[MENU_ITEMS[i].menuId].menuLength == 0) MENU_GROUPS_LENGTH[MENU_ITEMS[i].menuId].startIndex = i;
    MENU_GROUPS_LENGTH[MENU_ITEMS[i].menuId].menuLength++;
  }
}

void disableMenu()
{
  MENU_DISPLAY = false;
}

void enableMenu()
{
  MENU_DISPLAY = true;
}

bool isMenuDisplay()
{
  return (MENU_DISPLAY && MENU_CURRENT > 0);
}

void displayMenuActivity()
{
  if (isMenuDisplay()) return;
  displayReset();
  MENU_ITEMS[MENU_CURRENT_GLOBAL_ITEM_INDEX].func();
}

bool isMenuSpaceAvailable()
{
  return ((MENU_END_INDEX-MENU_START_INDEX+1) < MENU_LINES) && ((MENU_END_INDEX-MENU_START_INDEX+1) < MENU_GROUPS_LENGTH[MENU_CURRENT].menuLength);
}

void displayMenu()
{
  displayButtonsProcess();
  
  if (!isMenuDisplay()) return;
  
  displayReset();

  MENU_START_INDEX = MENU_CURRENT_ITEM_INDEX - MENU_LINES/2;
  MENU_END_INDEX   = MENU_CURRENT_ITEM_INDEX + MENU_LINES/2;

  if (MENU_END_INDEX   > (MENU_GROUPS_LENGTH[MENU_CURRENT].menuLength-1)) MENU_END_INDEX = MENU_GROUPS_LENGTH[MENU_CURRENT].menuLength-1;
  if (MENU_START_INDEX < 0) MENU_START_INDEX = 0;

  while (isMenuSpaceAvailable()) 
  {
    if (MENU_START_INDEX > 0) {
      MENU_START_INDEX--;
    }
    if (!isMenuSpaceAvailable()) break;
    if (MENU_END_INDEX < (MENU_GROUPS_LENGTH[MENU_CURRENT].menuLength-1)) {
      MENU_END_INDEX++;
    }
    if (!isMenuSpaceAvailable()) break;
  }
  
  MENU_START_INDEX = MENU_START_INDEX + MENU_GROUPS_LENGTH[MENU_CURRENT].startIndex;
  MENU_END_INDEX   = MENU_END_INDEX + MENU_GROUPS_LENGTH[MENU_CURRENT].startIndex;

  for (int i=MENU_START_INDEX;i<=MENU_END_INDEX;i++) {
    if (i == MENU_CURRENT_ITEM_INDEX+MENU_GROUPS_LENGTH[MENU_CURRENT].startIndex) {
      displayHighlightBegin();
      display.print(">");
      displayHighlightEnd();
    } else {
      display.print(" ");
    }
    display.println(MENU_ITEMS[i].title);
  }
}

void setMenuByMenuItem(menuItem m)
{
  enableMenu();
  
  MENU_CURRENT = m.funcArg;
  MENU_PREVIOUS = m.menuId;
  MENU_CURRENT_ITEM_INDEX = 0;
}

void menuSubMenu()
{
  setMenuByMenuItem(MENU_ITEMS[MENU_CURRENT_GLOBAL_ITEM_INDEX]);
}

void menuDummyFunction()
{
  enableMenu();
}

void menuBack() {
  enableMenu();
  if (MENU_PREVIOUS > 0) {
    MENU_CURRENT = MENU_PREVIOUS;
    MENU_PREVIOUS = 0;
  } else {
    MENU_CURRENT = MENU_ITEMS[MENU_CURRENT_GLOBAL_ITEM_INDEX].menuParentId;
  }
  if (MENU_CURRENT == 0) MENU_CURRENT = 1;
  MENU_CURRENT_ITEM_INDEX = 0;
  
}

void displayButtonsProcess()
{
  if (!isMenuDisplay()) return;
  
  if (BUTTON_STATE[BUTTON_UP]) {
    MENU_CURRENT_ITEM_INDEX--;
  } else if (BUTTON_STATE[BUTTON_DOWN]) {
    MENU_CURRENT_ITEM_INDEX++;
  }

  if (MENU_CURRENT_ITEM_INDEX < 0) MENU_CURRENT_ITEM_INDEX = MENU_GROUPS_LENGTH[MENU_CURRENT].menuLength-1;
  if (MENU_CURRENT_ITEM_INDEX > MENU_GROUPS_LENGTH[MENU_CURRENT].menuLength-1) MENU_CURRENT_ITEM_INDEX = 0;
  MENU_CURRENT_GLOBAL_ITEM_INDEX = MENU_CURRENT_ITEM_INDEX + MENU_GROUPS_LENGTH[MENU_CURRENT].startIndex;


  // Action
  if (BUTTON_STATE[BUTTON_OK]) {
      // call function with this name with `displayMenuActivity` in main loop
      disableMenu();
      MENU_PREVIOUS = MENU_CURRENT;
  }
}
