uint16_t ticksPerGaitItem    = 0;
uint16_t ticksToNextGaitItem = 0;
uint8_t currentGait          = 0;

// Gait
gaitConfig GAIT_CONFIG = {
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
  4,           // 4 items in sequence
  LOOP_TIME,   // loop time to correclty calculate number of sub moves per gate item
  20,          // move on 20mm
  40,          // max move on 40 mm
  20,          // above the ground on swing, 20mm
  1000,        // swing duration 1 second
  1000         // sequence items duration 1 second
};

gait gaitLegLF(GAIT_CONFIG, legs[LEGLF]);
gait gaitLegRF(GAIT_CONFIG, legs[LEGRF]);
gait gaitLegLH(GAIT_CONFIG, legs[LEGLH]);
gait gaitLegRH(GAIT_CONFIG, legs[LEGRH]);


void initGait() {
  ticksPerGaitItem = GAIT_CONFIG.duration/GAIT_CONFIG.loopTime;
  ticksToNextGaitItem = ticksPerGaitItem;
}

void updateGait() {

  // code
  gaitLegLF.next(currentGait);
  gaitLegRF.next(currentGait);
  gaitLegLH.next(currentGait);
  gaitLegRH.next(currentGait);
  ticksToNextGaitItem--;
  if (ticksToNextGaitItem > 0) {
    // ???
  } else {
    ticksToNextGaitItem = ticksPerGaitItem;
    currentGait++;
    if (currentGait >= GAIT_CONFIG.sequenceLength) currentGait=0;
  }
}
