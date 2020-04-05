/**
 * Transitions for leg movement
 *
 * MIT Licence
 * Developed by Gleb Devyatkin (SovGVD) in 2020
 */

#include "math.h"
#include "transition.h"

transition::transition()
{
}

void transition::set(transitionParameters param)
{
	_param = param;
	progressLength = _param.targetValue.x - _param.initialValue.x;
	point1.x = _param.initialValue.x + TRANSITION_PROGRESS_STEP1*progressLength;
	point1.y = _param.initialValue.y + offTheGround;
	
	point2.x = _param.targetValue.x + TRANSITION_PROGRESS_STEP2*progressLength;
	point1.y = _param.targetValue.y + offTheGround;
	
	k1 = getK(_param.initialValue, point1);
	k2 = getK(point1, point2);
	k3 = getK(point2, _param.targetValue);
}

/**
 * progress [0,1];
 */
transitionPoint transition::get(double progress)
{
	double x = progressLength*progress;
	double k = 0;
	double x1 = 0;
	double y1 = 0;
	if (progress <= TRANSITION_PROGRESS_STEP1) {
		k = k1;
		x1 = _param.initialValue.x;
		y1 = _param.initialValue.y;
	} else if (progress >= TRANSITION_PROGRESS_STEP2) {
		k = k2;
		x1 = _param.point1.x;
		y1 = _param.point1.y;
	} else {
		k = k3;
		x1 = _param.point2.x;
		y1 = _param.point2.y;
	}
	
	return k*(x - x1) + y1;
}

double transition::getK(transitionPoint point1, transitionPoint point2)
{
	return (point2.y - point1.y) / (point2.x - point1.x);
}
