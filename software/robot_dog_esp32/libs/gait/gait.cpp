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
		ticksToStop--;
		progress = 1 - (float)ticksToStop/(float)ticksMax;
		
		_transition.get(progress);
		//_leg->foot = _transition.get(progress);
	}
}

void gait::start() {
	ticksToStop = _config->swingDuration/_config->loopTime;
	ticksMax    = ticksToStop;
	
	// TODO, this should be planned points
	tParams = {
		{
			_leg->defaultFoot.x,
			_leg->defaultFoot.y,
			_leg->defaultFoot.z
		},
		{
			_leg->defaultFoot.x,
			_leg->defaultFoot.y,
			_leg->defaultFoot.z
		},
		_config->offTheGround
	};
	_transition.set(tParams);
}
