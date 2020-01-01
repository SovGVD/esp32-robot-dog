MPU9250 mpu;

#define ROLL  0
#define PITCH 1
#define YAW   2

float IMU_DATA[3] = {0, 0, 0};

void initIMU()
{
  display.println("Init IMU");
  display.display();
  mpu.setup();
}

void calibrateIMU()
{
  displayReset();
  display.println("Calibrating ACC and GYRO in 5 seconds. Put device on flat leveled surface.");
  display.display();
  delay(5000);
  display.print("Calibration...");
  display.display();
  mpu.calibrateAccelGyro();
  display.println("Done.");
  display.display();
  delay(3000);
  menuBack();
}

void updateIMU()
{
  mpu.update();

  IMU_DATA[ROLL]  = mpu.getRoll();
  IMU_DATA[PITCH] = mpu.getPitch();
  IMU_DATA[YAW]   = mpu.getYaw();
  
}

void displayIMU()
{
  displayReset();
  display.print("Roll:  ");
  display.println(IMU_DATA[ROLL], DISPLAY_DIGITS);
  display.print("Pitch: ");
  display.println(IMU_DATA[PITCH], DISPLAY_DIGITS);
  display.print("Yaw:   ");
  display.println(IMU_DATA[YAW], DISPLAY_DIGITS);

}
