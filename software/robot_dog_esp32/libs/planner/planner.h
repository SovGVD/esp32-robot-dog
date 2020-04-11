/**
 * Planner
 * Almost, it is just move body and legs to the new point
 * Also it looks like a good place to check if new possition possible
 *
 * MIT Licence
 * Developed by Gleb Devyatkin (SovGVD) in 2020
 */

#ifndef planner_h
#define planner_h

#include "../IK/geometry.h"
#include "../IK/leg.h"

class planner
{
	public:
		planner(moveVector &vector, figure &bodyObj, leg &legLF, leg &legRF, leg &legLH, leg &legRH);
	private:
		moveVector *_vector;
		figure     *_body;
		leg        *_legLF;
		leg        *_legRF;
		leg        *_legLH;
		leg        *_legRH;
};

#endif
