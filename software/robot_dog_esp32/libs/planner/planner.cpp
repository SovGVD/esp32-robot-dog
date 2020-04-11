/**
 * Planner
 *
 * MIT Licence
 * Developed by Gleb Devyatkin (SovGVD) in 2020
 */

#include "planner.h"

planner::planner(moveVector &vector, figure &bodyObj, leg &legLF, leg &legRF, leg &legLH, leg &legRH)
{
	_vector = &vector;
	_body   = &bodyObj;
	_legLF  = &legLF;
	_legRF  = &legRF;
	_legLH  = &legLH;
	_legRH  = &legRH;
}
