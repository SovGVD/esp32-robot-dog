#ifndef leg_h
#define leg_h

// Just pount in 3D
typedef struct {
	double x;
	double y;
	double z;
} legpoint;


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

// Leg sensors
typedef struct {
	bool onGround;
} legsensor;

// Leg structure
typedef struct {
	const legpoint  body;
	const legsize   size;
	const leghal    pin;
	const legangle  min;	// setup limits of angles
	const legangle  max;	// setup limits of angles
	legpoint  foot;
	legangle  angle;
	legangle  trim;
	legsensor sensor;
} leg;

#endif
