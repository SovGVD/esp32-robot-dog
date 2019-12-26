MPU9250 mpu;

#define ROLL  0
#define PITCH 1
#define YAW   2

float IMU_DATA[3] = {0, 0, 0};

void initIMU()
{
  display.println("Init IMU...");
  display.display();
  mpu.setup();
}

void calibrateIMU()
{
  display.clearDisplay();
  display.setCursor(0,0);
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
  display.clearDisplay();
  display.setCursor(0,0);
  display.print("Roll:  ");
  display.println(IMU_DATA[ROLL],6);
  display.print("Pitch: ");
  display.println(IMU_DATA[PITCH],6);
  display.print("Yaw:   ");
  display.println(IMU_DATA[YAW],6);

}
