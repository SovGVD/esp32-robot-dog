#ifndef leg_h
#define leg_h

#include "geometry.h"

// see IK.h
typedef struct {
	double alpha;
	double beta;
	double gamma;
} legangle;

// see IK.h
typedef struct {
	double l1;
	double l2;
	double l3;
} legsize;

// Hardware pin numbers
typedef struct {
	int alpha;
	int beta;
	int gamma;
} leghal;

// Leg sensor
typedef struct {
	bool onGround;  // State
	int pin;        // Settings
	int threshold;
} legsensor;

// Leg IK helpers (this is moslty need to set where is leg: left or right side, to inverse some values)
typedef struct {
	bool x;
	bool y;
	bool z;
} leginverse;

// Leg structure
typedef struct {
	const point     body;
	const legsize   size;
	const leghal    pin;
	const legangle  min;	// setup limits of angles
	const legangle  max;	// setup limits of angles
	point           foot;
	legangle        angle;
	legangle        trim;
	leginverse      inverse;
	legsensor       sensor;
} leg;

#endif
