#include "main.h"
#include "pid_pitch.h"

void PID_Pitch_Control::autolevel(const int &angle)
{
    pitch = map(angle, -90, 90, 0, 255);
    controll_pitch_left.Compute();
    controll_pitch_right.Compute();
}
