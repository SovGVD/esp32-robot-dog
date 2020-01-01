/**
 * Configuration file
 */

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

#define LEG_NUM 4
#define LEGLF 0
#define LEGRF 1
#define LEGLB 2
#define LEGRB 3
