#pragma once

class DataFrame
{
private:
    int dataLength;
    int deviceId; //20 = imu
    int infoID;   //1 = roll and 2 = pitch

public:
    void sendData(const int &payload, const int &sequence);

    DataFrame(int device_id, int info_id);
};