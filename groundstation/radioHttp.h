#pragma once

class Radio_Http
{

public:
    String longitude;
    String latitude;
    String Temp = "24.5";
    String Message;
    String InitMessage;
    String pitch;
    String roll;

private:
public:
    Radio_Http();

    int fetch_orien();

    // returns 1 if longitude was recieved and 2 if latitude, 0 if nothing
    int fetch_coords();

    void fetch_temp(); //this function fetches the temperature reading sent by the drone

    //MESSAGE MUST NOT BE 12,4,10 OR 11 bytes
    bool fetch_message(); //this function fetches the any other message sent by the drone thats not

    bool fetch_init_message(); //this fuction fetches the meaage sent by the drone when it is turned on
};
