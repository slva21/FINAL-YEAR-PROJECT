#include "motors.h"
#include "main.h"

void Motors::set_motor_1(int mode)
{
    analogWrite(INB1, mode);
    digitalWrite(INA1, LOW);
}
void Motors::set_motor_2(int mode)
{
    analogWrite(INA2, mode);
    digitalWrite(INB2, LOW);
}
void Motors::set_motor_3(int mode)
{
    analogWrite(INB3, mode);
    digitalWrite(INA3, LOW);
}
void Motors::set_motor_4(int mode)
{
    analogWrite(INA4, mode);
    digitalWrite(INB4, LOW);
}

void Motors::command_drone_climb()
{
    set_motor_1(upVector);
    set_motor_2(upVector);
    set_motor_3(upVector);
    set_motor_4(upVector);
}

void Motors::command_drone_hover()
{
    set_motor_1(hover);
    set_motor_2(hover);
    set_motor_3(hover);
    set_motor_4(hover);
}

void Motors::command_drone_roll_right()
{
    set_motor_1(downVector);
    set_motor_2(downVector);
    set_motor_3(upVector);
    set_motor_4(upVector);
}

void Motors::command_drone_roll_left()
{
    set_motor_3(downVector);
    set_motor_4(downVector);
    set_motor_1(upVector);
    set_motor_2(upVector);
}
void Motors::command_drone_decend()
{
    set_motor_1(downVector);
    set_motor_2(downVector);
    set_motor_3(downVector);
    set_motor_4(downVector);
}
void Motors::command_drone_yaw_right()
{
    set_motor_1(downVector);
    set_motor_2(upVector);
    set_motor_3(downVector);
    set_motor_4(upVector);
}
void Motors::command_drone_yaw_left()
{
    set_motor_1(upVector);
    set_motor_2(downVector);
    set_motor_3(upVector);
    set_motor_4(downVector);
}
void Motors::command_drone_foward()
{
    set_motor_1(upVector);
    set_motor_2(hover);
    set_motor_3(hover);
    set_motor_4(upVector);
}

void Motors::roll_control(const int &desired_angle)
{
    pid_roll_control.Setpoint = desired_angle; //set the PID desired roll angle
    manouverTime.start();                      //start a 3 second timer

    while (!manouverTime) //run for at least 3 seconds
    {
        pid_roll_control.autolevel(imu.get_roll_angle()); //compute the pwm outputs based on the current roll angle

        set_motor_1(pid_roll_control.left_output);
        set_motor_2(pid_roll_control.left_output);
        set_motor_3(pid_roll_control.right_output);
        set_motor_4(pid_roll_control.right_output);
    }
}

void Motors::pitch_control(const int &desired_angle)
{
    pid_pitch_control.Setpoint = desired_angle; //set the PID desired roll angle
    manouverTime.start();

    while (!manouverTime) //run for at least 3 seconds
    {
        pid_pitch_control.autolevel(imu.get_pitch_angle()); //compute the pwm values based on the current roll angle

        set_motor_1(pid_pitch_control.left_output);
        set_motor_4(pid_pitch_control.left_output);
        set_motor_2(pid_pitch_control.right_output);
        set_motor_3(pid_pitch_control.right_output);
    }
}
