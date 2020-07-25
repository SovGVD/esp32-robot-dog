double runI2CScan(double id) {
  // We need to run that function on diferent cores
  cliFunctionFAST = runI2CScanFAST;
  runCommandFASTCore = true;

  return 1;
}

double runI2CScanFAST(double id)
{
  cliSerial->println("i2c scan FAST");
  for (byte i = 8; i < 120; i++)
  {
    Wire.beginTransmission (i);        // Begin I2C transmission Address (i)
    if (Wire.endTransmission () == 0)  // Receive 0 = success (ACK response) 
    {
      cliSerial->print(i, DEC);
      cliSerial->print(" (0x");
      cliSerial->print(i, HEX);
      cliSerial->print("), ");
    }
  }

  // run SLOW only after FAST to avoid any possile Serial issues
  cliFunctionSLOW = runI2CScanSLOW;
  runCommandSLOWCore = true;

  return 1;
}

double runI2CScanSLOW(double id)
{
  cliSerial->println("i2c scan SLOW");
  for (byte i = 8; i < 120; i++)
  {
    WireServices.beginTransmission (i);
    if (WireServices.endTransmission () == 0)
    {
      cliSerial->print(i, DEC);
      cliSerial->print(" (0x");
      cliSerial->print(i, HEX);
      cliSerial->print("), ");
    }
  }
  cliSerial->println("");

  return 1;
}
