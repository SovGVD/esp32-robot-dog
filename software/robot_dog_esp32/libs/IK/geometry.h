#ifndef geometry_h
#define geometry_h

// pount in 3D
typedef struct {
	double x;
	double y;
	double z;
} point;

// angle in 3D
typedef struct {
	double roll;    // X axis
	double pitch;   // Y axis
	double yaw;     // Z axis
} angle;

//body
typedef struct {
	point position;
	angle orientation;
} figure;

//move
typedef struct {
	point move;
	angle rotate;
} moveVector;


#endif
