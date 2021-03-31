#include "dataframe.h"

void DataFrame::sendData(const int &payload, const int &sequence)
{
    dataLength = sizeof(payload); //find the length of payload

    Serial.write(0xFA);       //start
    Serial.write(dataLength); //length
    Serial.write(0x01);       //sequence
    Serial.write(deviceId);   //id of imu
    Serial.write(infoID);     //information -id. 1 = roll, 2 = pitch
    Serial.write(payload);
    Serial.write(0x96); //message end 260
}

DataFrame::DataFrame(int device_id, int info_id)
{
    //info id(1 = roll and 2 = pitch)
    deviceId = device_id;
    infoID = info_id;
}
