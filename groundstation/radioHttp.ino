#include "main.h"
#include "radioHttp.h"

Radio_Http::Radio_Http()
{
    // longitude = "";
    // latitude = "";
    // Temp = "";
    // Message = "";
    // InitMessage = "";
}

int Radio_Http::fetch_coords()
{
    String x;
    //11
    uint8_t coord[RH_ASK_MAX_MESSAGE_LEN]; //long coords..10
    uint8_t coord_len = sizeof(coord);

    if (driver.recv(coord, &coord_len)) //if coord is recived

        for (int i = 0; i < coord_len; i++) //for each bit recieved
        {
            x += (char)coord[i]; //append each bit to the string
        }
    switch (x.length())
    {
    case 10: //longitudes will arrive with 10 bytes
        longitude = x.substring(0, 9);
        return 1;
    case 11: //latitudes will arrive with 11 bytes
        latitude = x.substring(0, 9);
        return 2;

    default:
        break;
    }
    return 0;
}

int Radio_Http::fetch_orien()
{
    String x;
    //11
    uint8_t orien[RH_ASK_MAX_MESSAGE_LEN]; //long coords..10
    uint8_t orien_len = sizeof(orien);

    if (driver.recv(orien, &orien_len)) //if coord is recived

        for (int i = 0; i < orien_len; i++) //for each bit recieved
        {
            x += (char)orien[i]; //append each bit to the string
        }
    switch (x.length())
    {
    case 10: //longitudes will arrive with 10 bytes
        longitude = x.substring(0, 9);
        return 0;
    case 11: //latitudes will arrive with 11 bytes
        latitude = x.substring(0, 9);
        return 0;
    case 7:
        pitch = x;
        return 1;
    case 8:
        roll = x;
        return 2;

    default:
        break;
    }
    return 0;
}

// void Radio_Http::fetch_temp() //this function fetches the temperature reading sent by the drone
// {
//     uint8_t temp[4]; //for temp
//     uint8_t Temp_len = sizeof(temp);

//     Temp = "";
//     if (driver.recv(temp, &Temp_len)) //if temp coords is recived

//         for (int i = 0; i < Temp_len; i++) //for each bit recieved
//         {
//             Temp += (char)temp[i]; //append each bit to the string
//         }
// }

bool Radio_Http::fetch_message() //MESSAGE MUST NOT BE 12,4,10 OR 11 bytes
{
    String x;
    uint8_t Msg[RH_ASK_MAX_MESSAGE_LEN]; // Impact Warning! msg
    uint8_t Msg_len = sizeof(Msg);
    if (driver.recv(Msg, &Msg_len))
    {                                     //if the message coords is recived
        for (int i = 0; i < Msg_len; i++) //for each bit recieved
        {
            x += (char)Msg[i]; //append each bit to the string
        }
        switch (x.length())
        {
        //reserved message lengths...
        case 12:
            return false;
        case 4:
            return false;
        case 10:
            longitude = x.substring(0, 9);
            return false;
        case 11:
            latitude = x.substring(0, 9);
            return false;
        //any other lengh if valid
        case 7:
            pitch = x;
            return false;
        case 8:
            roll = x;
            return false;
        default:
            Message = x;
            return true;
        }
    }

    return false;
}

bool Radio_Http::fetch_init_message() //this fuction fetches the meaage sent by the drone when it is turned on
{
    String x;
    uint8_t InitMsg[RH_ASK_MAX_MESSAGE_LEN]; // initialized msg
    uint8_t InitMsg_len = sizeof(InitMsg);

    if (driver.recv(InitMsg, &InitMsg_len))
    {                                         //if the message coords is recived
        for (int i = 0; i < InitMsg_len; i++) //for each bit recieved
        {
            x += (char)InitMsg[i]; //append each bit to the string
        }

        switch (x.length()) //check what message was recived
        {
        case 12:
            InitMessage = x;
            return true;

        default:
            return false;
        }
    }
    return false;
}
