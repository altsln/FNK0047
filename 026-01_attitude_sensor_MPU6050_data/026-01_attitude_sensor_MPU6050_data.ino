/**********************************************************************
* Filename    : 026-01_attitude_sensor_MPU6050_data
* Description : Using MPU6050 attitude sensor to read more data
* not only Angle.
* Auther      : Alternatives Solutions
* Modification: 2026/03/26
**********************************************************************/
#include <MPU6050_tockn.h>
#include <Wire.h>

// --- Configuration ---
const int MPU_SDA_PIN = 14;
const int MPU_SCL_PIN = 5;

const int DELAY_TIME = 1000;

MPU6050 mpu(Wire);  //attach the i2c

void setup() {
  Serial.begin(115200);
  setupMPU();
  Serial.println("System Ready!");
  //}
}

void loop() {
  mpu.update(); // Updates the internal calculations

  // Every sec, print the data
  static unsigned long lastPrint = 0;
  if (millis() - lastPrint > DELAY_TIME) {
    logAngle();
    logAcc();
    logGhyros();
    logTemp();
    lastPrint = millis();
  }
}


void setupMPU() {
  //1. Initialize I2C with your specific pins
  Wire.begin(MPU_SDA_PIN, MPU_SCL_PIN);

  // 2. Initialize MPU
  mpu.begin();

  Serial.println("========================================");
  Serial.println("Placing MPU6050 on a flat surface...");
  Serial.println("Calculating offsets, do not move!");
  
  // This takes about 2-3 seconds and is vital for accuracy
  mpu.calcGyroOffsets(true); 
  
  Serial.println("Calibration Done!");
  Serial.println("========================================");

}


void logAngle() {
  Serial.print("AngleX: "); Serial.print(mpu.getAngleX());
  Serial.print("\tAngleY: "); Serial.print(mpu.getAngleY());
  Serial.print("\tAngleZ: "); Serial.println(mpu.getAngleZ());
}

void logAcc() {
  Serial.print("ACC X: "); Serial.print(mpu.getAccX());
  Serial.print("\tY: "); Serial.print(mpu.getAccY());
  Serial.print("\tZ: "); Serial.println(mpu.getAccZ());
}

void logGhyros() {
  Serial.print("Gyrosc X: "); Serial.print(mpu.getGyroX());
  Serial.print("\tY: "); Serial.print(mpu.getGyroY());
  Serial.print("\tZ: "); Serial.println(mpu.getGyroZ());
}

void logTemp() {
  Serial.print("Temp: "); Serial.println(mpu.getTemp());
}
