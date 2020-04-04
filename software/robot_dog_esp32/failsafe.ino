void initFailsafe () {
  
}

void updateFailsafe() {
  if (FS_WS_count >= FS_WS_THR) {
    setFailsafe();
    return;
  }
  
  FS_FAIL = false;
}

void setFailsafe() {
  vector.x    = 0;
  vector.y    = 0;
  vector.z    = 0;
  vector.angZ = 0;

  FS_WS_count = FS_WS_THR;  
  FS_FAIL     = true;
}
