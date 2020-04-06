#ifndef gait_h
#define gait_h

#include "../IK/IK.h"

/* Gait actions */
#define IGNORE 0 // Leg ignored
#define STANCE 1 // Leg on ground
#define SWING  2 // Leg off ground


typedef struct gaitSequence_t {
	const uint8_t leg[4];
} gaitSequence;

typedef struct gaitConfig_t {
	const gaitSequence sequence[16];
	const uint8_t      sequenceLength;
	const double       loopTime;       // loop time to correclty calculate number of sub moves per gate item, milliseconds
	double       defaultDelta;   // default full leg move, in mm
	double       maxDelta;       // maximal full leg move, in mm
	double       offTheGround;   // in mm
	double       swingDuration;  // duration of swing in milliseconds (1sec = 1000 millisec, 1sec = 1000000microsec)
	double       duration;       // duration of gaitSequence item, in milliseconds (1sec = 1000 millisec), should be equal or longer than swingDuration
} gaitConfig;

class gait
{
	public:
		gait(gaitConfig &config, leg &legObj);
		void next(uint8_t currentGait);
	private:
		gaitConfig *_config;
		leg        *_leg;
		uint16_t   ticksToStop = 0;
		uint8_t    _currentGait = 255;
		void start();
	
};
#endif
