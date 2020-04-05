typedef struct gaitSequence_t {
  const uint8_t leg[4];
} gaitSequence;

typedef struct gait_t {
  const gaitSequence sequnce[16];
  const uint8_t      sequnceLength;
  const double       offTheGround;   // in mm
  const double       swingDuration;  // duration of swing in milliseconds (1sec = 1000 millisec)
  const double       duration;       // duration of gaitSequence item, in milliseconds (1sec = 1000 millisec), should be equal or longer than swingDuration
} gait;
