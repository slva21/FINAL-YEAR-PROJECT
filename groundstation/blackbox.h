#pragma once

class BlackBox
{
public:
    bool post(String &lat, String &Long, String &roll, String &pitch, String &temp);

private:
    String payload;
    String AP = "MEWS-WB7";
    String PASS = "derate-topnotch-cantata";
    int countTrueCommand;
    int countTimeCommand;
    boolean found = false;

private:
    bool sendPayload(String &payload, int maxTime, char readReplay[]);
};
