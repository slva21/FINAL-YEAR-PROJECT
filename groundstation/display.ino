#include "main.h"
#include "display.h"

// this sets the longitude and latitude template.
void Display::setCoordTemplate()
{
    lcd.setCursor(0, 0);
    lcd.print("LAT:");
    lcd.setCursor(0, 1);
    lcd.print("LNG:");
}
void Display::setMessageTemplate()
{

    lcd.setCursor(0, 0);
    lcd.print("Msg:");
}

void Display::setOrenTemplate()
{
    lcd.setCursor(0, 0);
    lcd.print("PCH:");
    lcd.setCursor(0, 1);
    lcd.print("RLL:");
}

void Display::display_lat(String Lat)
{
    setCoordTemplate();
    lcd.setCursor(4, 0);
    lcd.print(Lat);
}
void Display::display_long(String Long)
{
    setCoordTemplate();
    lcd.setCursor(4, 1);
    lcd.print(Long);
}

void Display::display_msg(String Msg)
{
    setMessageTemplate();
    lcd.setCursor(0, 1);
    lcd.print(Msg);
}

void Display::display_pitch(int pitch)
{
    setOrenTemplate();
    lcd.setCursor(4, 0);
    lcd.print(pitch);
}

void Display::display_roll(int roll)
{
    setOrenTemplate();
    lcd.setCursor(4, 1);
    lcd.print(roll);
}
