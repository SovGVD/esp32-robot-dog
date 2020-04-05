const gait GAIT_CONFIG = {
  {
    {SWING,  STANCE, STANCE, STANCE},
    {STANCE, STANCE, SWING,  STANCE},
    {STANCE, SWING,  STANCE, STANCE},
    {STANCE, STANCE, STANCE, SWING }
  },
//  {
//    {SWING,  STANCE, SWING,  STANCE},
//    {STANCE, SWING,  STANCE, SWING }
//  },
  4,      // 4 items in sequince
  20,     // move on 20mm
  40,     // max move on 40 mm
  20,     // above the ground on swing, 20mm
  1000,   // swing duration 1 second
  1000    // sequince items duration 1 second
};

void initGait() {
  
}

void updateGait() {
  
}
