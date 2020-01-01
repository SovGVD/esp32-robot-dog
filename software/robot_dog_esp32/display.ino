bool DISPLAY_PING = true;


void initDisplay()
{
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

  display.println("Init display");
  display.display();
}

void displayReset() {
  display.clearDisplay();
  display.setCursor(0,0);  
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

  display.setCursor(64, 55);
  display.print(loopTime);
  display.display();
}
