#define MENU_ITEMS_NUM  55
#define MENU_GROUPS_NUM 15 //ROOT as 0, so groups+1

const menuItem MENU_ITEMS[MENU_ITEMS_NUM] = {
  { "Hardware",  2, menuSubMenu,        1, 0 },
  { "WiFi",     12, menuSubMenu,        1, 0 },
  { "Tests",     0, menuDummyFunction,  1, 0 },
  { "About",     0, displayAbout,       1, 0 }, //4

  { "IMU/MAG",  3, menuSubMenu,        2, 1 },
  { "HAL",      5, menuSubMenu,        2, 1 },
  { "Servo",    4, menuSubMenu,        2, 1 },
  { "I2C scan", 0, displayI2CScan,     2, 1 }, //8

  { "Status",        0, displayIMU,         3, 2 },
  { "Calibrate IMU", 0, calibrateIMU,       3, 2 },
  { "Calibrate MAG", 0, menuDummyFunction,  3, 2 }, //11

  { "Set to middle", 0, setServoToMiddle,   4, 2},
  { "Run test(!!!)", 0, servoTest,          4, 2},
  { "Status",        0, menuDummyFunction,  4, 2}, //14

  { "Body",    6, menuSubMenu,       5, 2 },
  { "Legs",    7, menuSubMenu,       5, 2 },
  { "Vector",  0, displayHALVector,  5, 2 },
  { "Enable",  1, displayToggleHAL,  5, 2 },
  { "Disable", 0, displayToggleHAL,  5, 2 },  //19

  { "P.MoveX (R/L)",  XAXIS, displayHALMoveBodyPosition, 6, 5 },
  { "P.MoveY (F/B)",  YAXIS, displayHALMoveBodyPosition, 6, 5 },
  { "P.MoveZ (U/D)",  ZAXIS, displayHALMoveBodyPosition, 6, 5 },
  { "A.MoveX (R/L)",  XAXIS, displayHALMoveBodyAngle,    6, 5 },
  { "A.MoveY (F/B)",  YAXIS, displayHALMoveBodyAngle,    6, 5 },
  { "A.MoveZ (U/D)",  ZAXIS, displayHALMoveBodyAngle,    6, 5 },
  { "Test",               1, displayHALTest,             6, 5 }, //26

  { "LEFT  FRONT",   8, menuSubMenu, 7, 5 },
  { "RIGHT FRONT",   9, menuSubMenu, 7, 5 },
  { "LEFT  HIND",   10, menuSubMenu, 7, 5 },
  { "RIGHT HIND",   11, menuSubMenu, 7, 5 },  //30

  { "Alpha",  ALPHA, displayHALTrimLF,        8, 7 },
  { "Beta",   BETA,  displayHALTrimLF,        8, 7 },
  { "Gamma",  GAMMA, displayHALTrimLF,        8, 7 },
  { "[Save]", LEGLF, menuDisplayHALTrimSave,  8, 7 },  //34

  { "Alpha",  ALPHA, displayHALTrimRF,        9, 7 },
  { "Beta",   BETA,  displayHALTrimRF,        9, 7 },
  { "Gamma",  GAMMA, displayHALTrimRF,        9, 7 },
  { "[Save]", LEGRF, menuDisplayHALTrimSave,  9, 7 },  //38

  { "Alpha",  ALPHA, displayHALTrimLH,       10, 7 },
  { "Beta",   BETA,  displayHALTrimLH,       10, 7 },
  { "Gamma",  GAMMA, displayHALTrimLH,       10, 7 },
  { "[Save]", LEGLH, menuDisplayHALTrimSave, 10, 7 },  //42

  { "Alpha",  ALPHA, displayHALTrimRH,       11, 7 },
  { "Beta",   BETA,  displayHALTrimRH,       11, 7 },
  { "Gamma",  GAMMA, displayHALTrimRH,       11, 7 },
  { "[Save]", LEGRH, menuDisplayHALTrimSave, 11, 7 },  //46

  { "Connect to", 14, menuSubMenu, 12, 1 },
  { "AP info",     0, WiFiInfo,    12, 1 },
  { "Mode",       13, menuSubMenu, 12, 1 },  //49

  { "AP",      AP_MODE, menuWiFiSetMode, 13, 12},
  { "Client",        1, menuWiFiSetMode, 13, 12},  //51

  { "AP 1", 1, menuWiFiSetMode, 14, 12},
  { "AP 2", 2, menuWiFiSetMode, 14, 12},
  { "AP 3", 3, menuWiFiSetMode, 14, 12},
  { "AP 4", 4, menuWiFiSetMode, 14, 12} //55

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
  MENU_ITEMS[MENU_CURRENT_GLOBAL_ITEM_INDEX].func(MENU_ITEMS[MENU_CURRENT_GLOBAL_ITEM_INDEX].funcArg);
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

void menuSubMenu(int id)
{
  setMenuByMenuItem(MENU_ITEMS[MENU_CURRENT_GLOBAL_ITEM_INDEX]);
}

void menuDummyFunction(int id)
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
