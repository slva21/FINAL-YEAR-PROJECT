#pragma once

class Display
{

private:
private:
    // this sets the longitude and latitude template.
    void setCoordTemplate();

    void setMessageTemplate();

    void setOrenTemplate();

public:
    void display_lat(String lat);

    void display_long(String Long);

    void display_msg(String Msg);

    void display_pitch(int pitch);

    void display_roll(int roll);

    // void display_temp(String Temp);
};
