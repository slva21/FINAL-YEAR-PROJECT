#include "main.h"
#include "imu.h"

#include <Streaming.h>

void IMU::init()
{

    Wire.beginTransmission(MPU_ADDR);
    Wire.write(0x3B);                        // starting with register 0x3B (ACCEL_XOUT_H) [MPU-6000 and MPU-6050 Register Map and Descriptions Revision 4.2, p.40]
    Wire.endTransmission(false);             // the parameter indicates that the Arduino will send a restart. As a result, the connection is kept active.
    Wire.requestFrom(MPU_ADDR, 7 * 2, true); // request a total of 7*2=14 registers

    accelerometer_x = Wire.read() << 8 | Wire.read(); // reading registers: 0x3B (ACCEL_XOUT_H) and 0x3C (ACCEL_XOUT_L)
    accelerometer_y = Wire.read() << 8 | Wire.read(); // reading registers: 0x3D (ACCEL_YOUT_H) and 0x3E (ACCEL_YOUT_L)
    accelerometer_z = Wire.read() << 8 | Wire.read(); // reading registers: 0x3F (ACCEL_ZOUT_H) and 0x40 (ACCEL_ZOUT_L)
    IMU_temperature = Wire.read() << 8 | Wire.read(); // reading registers: 0x41 (TEMP_OUT_H) and 0x42 (TEMP_OUT_L)
    gyro_x = Wire.read() << 8 | Wire.read();          // reading registers: 0x43 (GYRO_XOUT_H) and 0x44 (GYRO_XOUT_L)
    gyro_y = Wire.read() << 8 | Wire.read();          // reading registers: 0x45 (GYRO_YOUT_H) and 0x46 (GYRO_YOUT_L)
    gyro_z = Wire.read() << 8 | Wire.read();          // reading registers: 0x47 (GYRO_ZOUT_H) and 0x48 (GYRO_ZOUT_L)
    gyro_x = gyro_x + 0.56;                           // GyroErrorX ~(-0.56)
    gyro_y = gyro_y - 2;                              // GyroErrorY ~(2)
    gyro_z = gyro_z + 0.79;                           // GyroErrorZ ~ (-0.8)

    getFiltered(); //filter the values
}

// send warning message with the postion and distance ehrn collition is present
//     mathamatical exaplantions..maybe ffrom the aero dynamics point of view
//         some calculations
//             show some pwm curves fpr motors..relationship between speed and voltage..

String
IMU::accelx()
{
    init();
    return convert_int16_to_str(accelerometer_x);
}
String IMU::accely()
{
    init();
    return convert_int16_to_str(accelerometer_y);
}
String IMU::accelz()
{
    init();
    return convert_int16_to_str(accelerometer_z);
}
String IMU::temp()
{
    init();
    return convert_int16_to_str((IMU_temperature / 340.00 + 36.53));
}
String IMU::gyrox()
{
    init();
    return convert_int16_to_str(gyro_x);
}
String IMU::gyroy()
{
    init();
    return convert_int16_to_str(gyro_y);
}
String IMU::gyroz()
{
    init();
    return convert_int16_to_str(gyro_z);
}

double IMU::get_pitch_angle()
{
    init();
    return kalAngleX;
}

double IMU::get_roll_angle()
{
    init();
    return kalAngleY;
}

void IMU::getFiltered()
{

    double dt = (double)(micros() - timer) / 1000000; // Calculate delta time
    timer = micros();

    double gyroXrate = gyro_x / 131.0; // Convert to deg/s
    double gyroYrate = gyro_y / 131.0; // Convert to deg/s

    double roll = (atan(accelerometer_y / sqrt(pow(accelerometer_x, 2) + pow(accelerometer_z, 2))) * 180 / PI) - 0.58;
    double pitch = atan2(-accelerometer_x, accelerometer_z) * RAD_TO_DEG + 0.1;

    if ((pitch < -90 && kalAngleY > 90) || (pitch > 90 && kalAngleY < -90))
    {
        kalmanY.setAngle(pitch);
        kalAngleY = pitch;
        gyroYangle = pitch;
    }
    else
        kalAngleY = kalmanY.getAngle(pitch, gyroYrate, dt); // Calculate the angle using a Kalman filter

    if (abs(kalAngleY) > 90)
        gyroXrate = -gyroXrate; // Invert rate, so it fits the restriced accelerometer reading
    kalAngleX = kalmanX.getAngle(roll, gyroXrate, dt);
}