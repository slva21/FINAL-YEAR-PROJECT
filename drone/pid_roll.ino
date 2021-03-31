#include "main.h"
#include "pid_roll.h"

void PID_Roll_Control::autolevel(const int &angle)
{
    roll = map(angle, -90, 90, 0, 255);
    controll_roll_left.Compute();
    controll_roll_right.Compute();
}
