#pragma once //makes sure the header file is not included more than on in a file

class IMU
{

private:
  int16_t accelerometer_x, accelerometer_y, accelerometer_z;
  int16_t IMU_temperature;        // variables for temperature
  int16_t gyro_x, gyro_y, gyro_z; // variables for gyro raw data
  uint32_t timer;
  double kalAngleX, kalAngleY;   // Calculated angle using a Kalman filter
  double gyroXangle, gyroYangle; // Angle calculate using the gyro only
  void getFiltered();
  void init(); //declear the the init function
               //declear the public functions

public:
  String accelx();
  String accely();
  String accelz();
  String temp();
  String gyrox();
  String gyroy();
  String gyroz();
  double get_pitch_angle();
  double get_roll_angle();

public:
  IMU() //constructor
  {
    timer = millis();
  }
};