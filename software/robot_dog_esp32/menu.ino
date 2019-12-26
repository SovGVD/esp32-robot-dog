#define MENU_ITEMS_NUM  10
#define MENU_GROUPS_NUM 4 //ROOT as 0, so groups+1

const menuItem MENU_ITEMS[MENU_ITEMS_NUM] = {
  { "Hardware", "2",       menuSubMenu,        1, 0 },
  { "WiFi/BT",  "__WiFi",  menuDummyFunction,  1, 0 },
  { "Tests",    "__Test",  menuDummyFunction,  1, 0 },
  { "About",    "About",    displayAbout,       1, 0 },

  { "IMU/MAG",  "3",       menuSubMenu,        2, 1 },
  { "Leg",      "__Leg",   menuDummyFunction,  2, 1 },
  { "I2C scan", "i2cscn",  displayI2CScan,     2, 1 },

  { "Status",        "DIMU",   displayIMU,         3, 2 },
  { "Calibrate IMU", "CIMU",   calibrateIMU,       3, 2 },
  { "Calibrate MAG", "__CMAG", menuDummyFunction,  3, 2 }
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
  
  display.clearDisplay();
  display.setCursor(0,0);

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
      display.setTextColor(SSD1306_BLACK, SSD1306_WHITE);
      display.print(">");
      display.setTextColor(SSD1306_WHITE);
    } else {
      display.print(" ");
    }
    display.println(MENU_ITEMS[i].title);
  }
}

void setMenuByMenuItem(menuItem m)
{
  enableMenu();
  
  MENU_CURRENT = atoi(m.funcArg);
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
      // call function with this name
      disableMenu();
      MENU_PREVIOUS = MENU_CURRENT;
  }
}
