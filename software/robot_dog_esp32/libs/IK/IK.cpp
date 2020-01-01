/**
 * Inverse Kinematics for quadruped (four legs) robot
 * Boston Dynamics Spot style
 *
 * MIT Licence
 * Developed by Gleb Devyatkin (SovGVD) in 2020
 */

#include "math.h" 
#include "leg.h"
#include "IK.h"

IK::IK(leg &legObj)
{
	_leg = &legObj;
}

legangle IK::solve()
{
	legangle angle;
	
	// TODO: what can I do with limits?
	double lx = _leg->body.x - _leg->foot.y;
	double ly = _leg->body.y - _leg->foot.y;
	double lz = _leg->body.z - _leg->foot.z;
	
	double a = lx*lx + lz*lz;	// square of hypotenuse between leg.body and leg.foot in XZ-plane
	double d = a - _leg->size.l1*_leg->size.l1;
	
	angle.alpha = M_PI - ikAtan2(lx, lz) - ikAcos(_leg->size.l1/sqrt(a));
	angle.beta  = ikAsin(ly/sqrt(d)) + M_PI/2; 
	angle.gamma = ikAcos( (d - _leg->size.l2*_leg->size.l2 - _leg->size.l3*_leg->size.l3) / (2 * _leg->size.l2 * _leg->size.l3) );
	
	return angle;
}

double IK::normalizeAngleRad(double angleRad)
{
    angleRad = fmod(angleRad,M_2_PI);
    if (angleRad < 0) angleRad += M_2_PI;
    return angleRad;
}

// this can be update to use table of angles (faster) insted of using trigonometry functions
double IK::ikAtan2(double x, double y)
{
	return normalizeAngleRad(atan2(x, y));
}

double IK::ikAcos(double angleRad)
{
	return normalizeAngleRad(acos(angleRad));
}

double IK::ikAsin(double angleRad)
{
	return normalizeAngleRad(asin(angleRad));
}
