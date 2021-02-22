#pragma once

class AutoLevel
{

public:
    double Setpoint = 10; // will be the desired angle
    double roll;
    double pitch; // from imu
    //PID parameters
    double Kp = 2, Ki = 5, Kd = 1;

public:
    double pid_roll_pwm_output, pid_pitch_pwm_output;

    // AutoLevel();

public:
    void init();
};
