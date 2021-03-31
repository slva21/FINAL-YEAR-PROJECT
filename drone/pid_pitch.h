#pragma once

class PID_Pitch_Control
{

public:
    double Kp = 3.44, Ki = 0.048, Kd = 1.92;
    double Setpoint = map(0, -90, 90, 0, 255); // will be the desired angle
    double pitch;
    //PID parameters
    void autolevel(const int &angle);

public:                 //left side motors(1 and 4)
    double left_output; //rememder to devide this by two when inputted to the motors

public:                  //right side motors(2 and 3)
    double right_output; //rememder to devide this by two when inputted to the motors
};

