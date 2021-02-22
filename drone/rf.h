#pragma once

class RF
{
private:
    const char *warning; //must be 19 bytes
    const char *msg;
    const char *Long;        //must be 10 bytes
    const char *Lat;         //must be 11 bites
    const char *temperature; //must be 19 bytes

    const char *Pitch; //must be 7 bytes
    const char *Roll;  //must be 8 bytes
public:
    //this function uses the radio transmitter module to broadcast the location of the drone(causes 2second delay)
    int transmit_Lat(const char *lat); //string must be 11bits

    int transmit_long(const char *LonG); //must be 10 bits

    //this function uses the radio transmitter module to broadcasts a collision warning from the drone(causes 2second delay)
    void transmit_warning();

    //.. msg must be 12 bytes
    int transmit_any(const char *msg);

    //must be 4 bytes
    void trasnmit_temp(const char *temp);

    int transmit_roll(const char *roll);

    int transmit_pitch(const char *pitch);

    RF();
};
