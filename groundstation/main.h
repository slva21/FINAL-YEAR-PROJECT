#pragma once
#include <RH_ASK.h>
#include <LiquidCrystal.h>
#include <Streaming.h>
#include "radioHttp.h"
#include "display.h"
#include "blackbox.h"
#include <NoDelay.h>

Radio_Http radio;
Display display;
RH_ASK driver;
const char *longitude;
const char *latitude;
const char *Temp;
const char *Message;
bool Init = false;

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 12, en = 10, d4 = 5, d5 = 4, d6 = 7, d7 = 6;
const int btn = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

//1 for displaying long and lat and temp, 0 for displaying pitch and roll
bool mode = true;