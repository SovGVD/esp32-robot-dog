// Gait
gaitConfig GAIT_CONFIG = {
//  {
//    {SWING,  STANCE, STANCE, STANCE},
//    {STANCE, STANCE, SWING,  STANCE},
//    {STANCE, SWING,  STANCE, STANCE},
//    {STANCE, STANCE, STANCE, SWING }
//  },
  {
    { SWING,  STANCE, STANCE, SWING  },
    { STANCE, SWING,  SWING,  STANCE }
  },
  2,           // items in sequence
  LOOP_TIME,   // loop time to correclty calculate number of sub moves per gate item
  20,          // move on 20mm
  40,          // max move on 40 mm
  30,          // above the ground on swing, 30mm
  500,         // swing duration
  500          // sequence items duration
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
  ticksToNextGaitItem--;

  gaitLegLF.next(currentGait);
  gaitLegRF.next(currentGait);
  gaitLegLH.next(currentGait);
  gaitLegRH.next(currentGait);

  if (ticksToNextGaitItem <= 0) {
    ticksToNextGaitItem = ticksPerGaitItem;
    currentGait++;
    if (currentGait >= GAIT_CONFIG.sequenceLength) currentGait=0;
  }
}
