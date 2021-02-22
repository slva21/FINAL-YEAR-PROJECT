#include "main.h"
#include "rf.h"
#include <Streaming.h>

//error 3 means bytes lenght wrong
//error 2 means coords is the same since last tranmission

int RF::transmit_Lat(const char *lat)
{
    if (strlen(lat) != 11)
    {
        return 3; //error 3 means # bytes wring
    }
    // if (strcmp(Lat, lat)) //if the lat has changed
    // {
    Lat = lat;
    for (int i = 0; i < 3; i++)
    {

        rf_driver.send((uint8_t *)Lat, strlen(Lat));
        rf_driver.waitPacketSent();
        delay(200);
    }
    return 1;
    // }
    // else
    // {
    // return 2;
    // }
}

//error 3 means bytes lenght wrong
//error 2 means coords is the same since last tranmission
int RF::transmit_long(const char *LonG)
{
    if (strlen(LonG) != 10)
    {
        return 3; //error 3 means # bytes wrong
    }
    // if (strcmp(Long, LonG)) //if the lat has changed
    // {
    Long = LonG;
    for (int i = 0; i < 3; i++)
    {

        rf_driver.send((uint8_t *)Long, strlen(Long));
        rf_driver.waitPacketSent();
        delay(200);
    }
    return 1;
}

int RF::transmit_pitch(const char *pitch)
{

    if (strlen(pitch) != 7)
    {
        return 3; //error 3 means # bytes wrong
    }

    Pitch = pitch;
    for (int i = 0; i < 3; i++)
    {

        rf_driver.send((uint8_t *)Pitch, strlen(Pitch));
        // rf_driver.waitPacketSent();
        delay(200);
    }
    return 1;
}
int RF::transmit_roll(const char *roll)
{

    if (strlen(roll) != 8)
    {
        return 3; //error 3 means # bytes wrong
    }

    Roll = roll;
    for (int i = 0; i < 3; i++)
    {

        rf_driver.send((uint8_t *)Roll, strlen(Roll));
        // rf_driver.waitPacketSent();
        delay(200);
    }
    return 1;
}

//this function uses the radio transmitter module to broadcasts a collision warning from the drone(causes 2second delay)
void RF::transmit_warning()
{
    warning = "Impact Warning!";
    for (int i = 0; i < 3; i++)
    {
        rf_driver.send((uint8_t *)warning, strlen(warning));
        rf_driver.waitPacketSent();
        delay(200);
    }
}

int RF::transmit_any(const char *msg)
{

    for (int i = 0; i < 3; i++)
    {
        rf_driver.send((uint8_t *)msg, strlen(msg));
        rf_driver.waitPacketSent();
        delay(200);
    }
    return 1;
}

void RF::trasnmit_temp(const char *temp)
{
    if (temperature != String(temp).c_str()) //if the temp has changed
    {
        for (int i = 0; i < 3; i++)
        {
            temperature = String(temp).c_str(); //uses the string class to convert to char*
            rf_driver.send((uint8_t *)temperature, strlen(temperature));
            rf_driver.waitPacketSent();
            delay(200);
        }
    }
    else
    {
        return;
    }
}

RF::RF() //construstor
{
    // Initialize ASK Object
    rf_driver.init();
    Serial << "here" << endl;
}
