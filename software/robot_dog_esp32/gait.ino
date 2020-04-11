// Gait
/*gaitConfig GAIT_CONFIG = {
  {
    { SWING,  STANCE, STANCE, SWING  },
    { STANCE, SWING,  SWING,  STANCE }
  },
  2,           // items in sequence
  LOOP_TIME,   // loop time to correclty calculate number of sub moves per gate item
  20,          // move on 20mm
  40,          // max move on 40 mm
  30,          // above the ground on swing, 30mm
  200,         // swing duration
  200          // sequence items duration
};
*/

gaitConfig GAIT_CONFIG = {
  {
    {SWING,  STANCE, STANCE, STANCE},
    {STANCE, STANCE, SWING,  STANCE},
    {STANCE, SWING,  STANCE, STANCE},
    {STANCE, STANCE, STANCE, SWING }
  },
  4,           // items in sequence
  LOOP_TIME,   // loop time to correclty calculate number of sub moves per gate item
  20,          // move on 20mm
  40,          // max move on 40 mm
  30,          // above the ground on swing, 30mm
  2000,         // swing duration
  2000          // sequence items duration
};


gait gaitLegLF(GAIT_CONFIG, legs[LEGLF]);
gait gaitLegRF(GAIT_CONFIG, legs[LEGRF]);
gait gaitLegLH(GAIT_CONFIG, legs[LEGLH]);
gait gaitLegRH(GAIT_CONFIG, legs[LEGRH]);


void initGait() {
  ticksPerGaitItem = GAIT_CONFIG.duration/GAIT_CONFIG.loopTime;
  ticksToNextGaitItem = ticksPerGaitItem;
}

uint8_t getNextGait()
{
  nextGait = currentGait + 1;
  if (nextGait >= GAIT_CONFIG.sequenceLength) nextGait = 0;
  return nextGait;
}

void updateGait() {
  ticksToNextGaitItem--;

  gaitProgress[LEGLF] = gaitLegLF.next(currentGait);
  gaitProgress[LEGRF] = gaitLegRF.next(currentGait);
  gaitProgress[LEGLH] = gaitLegLH.next(currentGait);
  gaitProgress[LEGRH] = gaitLegRH.next(currentGait);


// TODO we need predict next position of robot to begin move of CoM at 0.8 progress of current and until 0.2 progress of future gait
  //bodyBalance.setBody(bodyBalance.getCenter());

  if (ticksToNextGaitItem <= 0) {
    ticksToNextGaitItem = ticksPerGaitItem;
    currentGait++;
    if (currentGait >= GAIT_CONFIG.sequenceLength) currentGait = 0;
  }
}
