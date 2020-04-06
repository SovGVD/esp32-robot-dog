/**
 * Configuration file
 */

/* main loop */
#define LOOP_TIME 50   // milliseconds

// Serial
#define SERIAL_BAUD 115200 

/*
 * I2C devices
 *  - PWM PCA9685
 *  - SD1306 OLED 128x64
 *  - IMU MPU 9250
 */

#define PWM_CONTROLLER_ADDRESS 0x40
#define PWM_CONTROLLER_TYPE    PCA9685

#define IMU_ADDRESS            0x68
#define IMU_TYPE               MPU9250

#define SCREEN_ADDRESS         0x3C
#define SCREEN_TYPE            OLED_SD1306_128_64
#define SCREEN_WIDTH           128 // OLED display width, in pixels
#define SCREEN_HEIGHT          64 // OLED display height, in pixels


// Buttons config
#define BUTTON_ADC_PIN  32
#define BUTTON_DEADBAND 100


// Robot config

#define LEG_NUM 4

// Size of leg parts in mm
#define LEG_SIZE_L1   40.6
#define LEG_SIZE_L2  166.0
#define LEG_SIZE_L3  186.0

// default angles for init state
#define LEG_ANGLE_ALPHA M_PI/2
#define LEG_ANGLE_BETA  M_PI/2
#define LEG_ANGLE_GAMMA M_PI/2

// angle limits
#define LEG_ANGLE_ALPHA_MIN 0
#define LEG_ANGLE_ALPHA_MAX M_PI

#define LEG_ANGLE_BETA_MIN  0
#define LEG_ANGLE_BETA_MAX  M_PI

#define LEG_ANGLE_GAMMA_MIN 0
#define LEG_ANGLE_GAMMA_MAX M_PI

// default legs state (TODO measure it!!!)
#define LEG_BODY_X   82.0
#define LEG_BODY_Y  155.0
#define LEG_BODY_Z    0.0
#define LEG_POINT_X 122.6
#define LEG_POINT_Y 155.0
#define LEG_POINT_Z 249.304

#define LEG_TRIM_INC   0.002   // radian
#define LEG_TRIM_LIMIT  0.24   // See settingsUint8ToDouble()

//Fais safe
#define FS_WS_THR 20  // 1 second = FS_WS_THR*LOOP_TIME
