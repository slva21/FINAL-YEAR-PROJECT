#pragma once //makes sure the header file is not included more than on in a file

class Motors
{
public:
    int hover = 160;
    int upVector = 255;
    int downVector = 100;

    void set_motor_1(int mode);
    void set_motor_2(int mode);
    void set_motor_3(int mode);
    void set_motor_4(int mode);

public:
    void command_drone_climb();
    void command_drone_roll_right();
    void command_drone_roll_left();
    void command_drone_decend();
    void command_drone_yaw_right();
    void command_drone_yaw_left();
    void command_drone_hover();
    void command_drone_foward();

public:
    void roll_control(const int &desired_angle);

    void pitch_control(const int &desired_angle);
};
