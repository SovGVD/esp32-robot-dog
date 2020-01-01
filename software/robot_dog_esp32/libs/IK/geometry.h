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
	double pitch;   // X axis
	double roll;    // Y axis
	double yaw;     // Z axis
} angle;

//body
typedef struct {
	point position;
	angle orientation;
} figure;


#endif
