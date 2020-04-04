int bytesToInt16(uint8_t byte1, uint8_t byte2) {
  return (byte1 << 8) | byte2;
}

void pMove(uint8_t* data) {
  // TODO RC failsafe on disconnect
  vector.x    = float(bytesToInt16(data[1], data[2]))/10000-1;
  vector.y    = float(bytesToInt16(data[3], data[4]))/10000-1;
  vector.z    = float(bytesToInt16(data[5], data[6]))/10000-1;
  vector.angZ = float(bytesToInt16(data[7], data[8]))/10000-1;
}
