#include "main.h"
#include "pid.h"

// AutoLevel::AutoLevel()
// {
//     pitchPID.SetMode(AUTOMATIC);
//     rollPID.SetMode(AUTOMATIC);
//     pitchPID.SetTunings(Kp, Ki, Kd);
//     rollPID.SetTunings(Kp, Ki, Kd);
// }
void AutoLevel::init()
//i will can this to be running in the main loop
{
    //Read the value from the imu. We map is to a value from 0 to 255 as it's used for our PWM function.
    roll = map(imu.get_roll_angle(), -90, 90, 90, 255);
    pitch = map(imu.get_pitch_angle(), -90, 90, 90, 255);
    rollPID.Compute();
    pitchPID.Compute();
}
