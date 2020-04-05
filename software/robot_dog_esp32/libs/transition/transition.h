/**
 * Transitions for leg movement
 *
 * MIT Licence
 * Developed by Gleb Devyatkin (SovGVD) in 2020
 */
 
// WARNING: this is WIP and this library was not tested in any software or hardware!!!
 
/**
 * transition of the leg is the set on two parabolic (TODO) functions and line on progress=[0,1];
 * at that moment I will use just a line
 * 
 * 
 *  ^
 *  |
 *  |
 *  | TODO parabolic func
 * 1|       .----------.
 *  |      /.          .\
 *  |    /  .          .  \
 *  |  /    .          .    \
 *  | /     .          .     \
 *  |/      .          .      \
 * 0+-------*----------*-------*----> X (progress)
 *  0      0.2        0.8      1
 *
 *
 *
 *
 *   x - x1    y - y1
 *  ------- = -------
 *  x2 - x1   y2 - y1
 *
 * y = k*(x - x1) + y1;
 *
 *     y2 - y1
 * k = -------
 *     x2 - x1
 *
 *  ^
 *  |
 *  |
 *  |     point1
 * 1|     *---___
 *  |    /.      ---*point2
 *  |   / .         . \
 *  |  /  .         .  \
 *  | /k1 .   k2    . k3\
 *  |/    .         .    \ targetValue
 * 0*-----|---------|-----*----> X (progress)
 *  0    0.2        0.8    1
 * initialValue
 */
#ifndef transition_h
#define transition_h

#define TRANSITION_PROGRESS_STEP1 0.2;
#define TRANSITION_PROGRESS_STEP2 0.8;

typedef struct {
	double x;
	double y;
} transitionPoint;

typedef struct {
	transitionPoint initialValue;
	transitionPoint targetValue;
	double offTheGround;
} transitionParameters;

class transition
{
	public:
		transition();
		void set(transitionParameters param);
		transitionParameters get(double progress);
	private:
		transitionParameters _param;
		transitionPoint point1;
		transitionPoint point2;
		double getK(transitionPoint point1, transitionPoint point2);
		double progressLength;
		double k1;
		double k2;
		double k3;
};

#endif
