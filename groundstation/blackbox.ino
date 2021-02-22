#include "blackbox.h"
#include "ArduinoJson.h"
#include "main.h"

bool BlackBox::sendPayload(String &payload, int maxTime, char readReplay[])
{
    Serial.print(countTrueCommand);
    Serial.print("payload => ");
    Serial.print(payload);
    Serial.print(" ");
    while (countTimeCommand < (maxTime * 1))
    {
        Serial1.println(payload);     //at+cipsend
        if (Serial1.find(readReplay)) //ok
        {
            found = true;
            break;
        }

        countTimeCommand++;
    }

    if (found == true)
    {
        Serial.println("YES");
        countTrueCommand++;
        countTimeCommand = 0;
        return true;
    }

    if (found == false)
    {
        Serial.println(Serial1.read());
        countTrueCommand = 0;
        countTimeCommand = 0;
        return false;
    }

    found = false;
}

bool BlackBox::post(String &lat, String &Long, String &roll, String &pitch, String &temp)
{

    StaticJsonBuffer<256> jsonBuffer;

    JsonObject &root = jsonBuffer.createObject();
    root["pitch"] = pitch;
    root["roll"] = roll;
    root["long"] = Long;
    root["lat"] = lat;
    root["temp"] = temp;

    root.printTo(payload); //generates the json onjectand prints it to the class variable payload

    if (sendPayload(payload, 30, "SENT"))
    {
        lcd.clear();
        display.display_msg("BB-SENT");
        delay(1000);
        return true;
    }

    else
    {
        lcd.clear();
        display.display_msg("BB-ERROR");
        delay("1000");
        return false;
    }
}
