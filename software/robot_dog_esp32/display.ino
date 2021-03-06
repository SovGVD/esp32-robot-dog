bool DISPLAY_PING = true;


void initDisplay()
{
  Serial.print("Display ");

  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    return;
  }
  display.clearDisplay();
  display.display();

  display.setTextSize(1);      // Normal 1:1 pixel scale
  display.setTextColor(SSD1306_WHITE); // Draw white text
  display.setCursor(0, 0);     // Start at top-left corner
  display.cp437(true);         // Use full 256 char 'Code Page 437' font
  Serial.println();
}

void displayReset() {
  display.clearDisplay();
  display.setCursor(0,0);  
}

double displayAngle(double angleRad)
{
  return angleRad*RADTODEGREE;
}

void displayHighlightBegin()
{
  display.setTextColor(SSD1306_BLACK, SSD1306_WHITE);
}

void displayHighlightEnd()
{
  display.setTextColor(SSD1306_WHITE);
}

void displayPing()
{
  DISPLAY_PING = !DISPLAY_PING;
  display.drawPixel(127, 63, DISPLAY_PING ? SSD1306_WHITE : SSD1306_BLACK);

  // leg on ground state
  display.drawPixel(1, 62, SSD1306_WHITE);  // TODO this should show is body in CoM or not
  display.drawPixel(0, 63, gaitProgress[LEGLF] == 0 ? SSD1306_WHITE : SSD1306_BLACK);
  display.drawPixel(0, 61, gaitProgress[LEGRF] == 0 ? SSD1306_WHITE : SSD1306_BLACK);
  display.drawPixel(2, 63, gaitProgress[LEGLH] == 0 ? SSD1306_WHITE : SSD1306_BLACK);
  display.drawPixel(2, 61, gaitProgress[LEGRH] == 0 ? SSD1306_WHITE : SSD1306_BLACK);


  display.setCursor(88, 55);
  display.print(loopTime);
  //display.print("/");
  //display.print(LOOP_TIME);
  display.print(" ");
  display.print(ticksPerGaitItem);
  display.display();
}
