/**
 * Some usuful defines
 */

#define LEGLF 0   // left  front leg
#define LEGRF 1   // right front leg
#define LEGLH 2   // left  hind  leg
#define LEGRH 3   // right hind  leg

#define ALPHA 0
#define BETA  1
#define GAMMA 2

#define XAXIS     0
#define YAXIS     1
#define ZAXIS     2
#define PITCHAXIS 3
#define ROLLAXIS  4
#define YAWAXIS   5

#define DISPLAY_DIGITS 1  // Number of digits to display after the decimal point

#define BUTTON_BACK 0
#define BUTTON_OK   1
#define BUTTON_UP   2
#define BUTTON_DOWN 3
#define BUTTON_NONE 99999;

/*
 *  0(back)  2(up)
 *  1(ok)    3(down)
 */



#define PCA9685 100
#define MPU9650 101
#define SD1306  102

/* OLED screen defaults */
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)

#define SOFTWARE_CORE_VERSION 1

/* Math */
#define RADTODEGREE 180/PI


/* Debug (SLOW!!!)*/
//#define DEBUG_HAL_LEG
