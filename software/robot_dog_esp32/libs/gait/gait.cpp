/**
 * MIT Licence
 * Developed by Gleb Devyatkin (SovGVD) in 2020
 */

#include "gait.h"

gait::gait(gaitConfig &config, leg &legObj)
{
	_config = &config;
	_leg    = &legObj;
}

void gait::next(uint8_t currentGait) {
	if (_currentGait != currentGait && ticksToStop == 0) {
		_currentGait = currentGait;
		if (_config->sequence[_currentGait].leg[_leg->id.id] == SWING) {
			start();
		}
	}
	
	if (ticksToStop > 0) {
		// TODO transition and leg update
		ticksToStop--;
	}
}

void gait::start() {
	ticksToStop = _config->swingDuration/_config->loopTime;
	Serial.print("Start leg ");
	Serial.print(_leg->id.id);
	Serial.print(" ");
	Serial.print(ticksToStop);
	Serial.println();

	// TODO calc points for transition
}
