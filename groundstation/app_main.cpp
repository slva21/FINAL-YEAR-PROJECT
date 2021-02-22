#include "main.h"

//prevents any delays
noDelay interval_display_coords(2000, []() { //this lamda function will be only run after 2+ seconds has passed sisnce the last call
    lcd.clear();
    radio.fetch_coords();
    display.display_lat(radio.latitude);
    display.display_long(radio.longitude);
});

noDelay interval_display_orien(2000, []() {
    //make call///
    lcd.clear();
    radio.fetch_orien();
    display.display_pitch(radio.pitch.toInt());
    display.display_roll(radio.roll.toInt());
});

noDelay interval_blackBox_entry(5000, []() { //every minute
    BlackBox entry;
    entry.post(radio.latitude, radio.longitude, radio.roll, radio.pitch, radio.Temp);
});

void setup()
{
    Serial.begin(9600);
    Serial1.begin(115200); //WIFI

    byte smiley[] = {
        //smily face custom character :)
        B00000,
        B10001,
        B00000,
        B00000,
        B10001,
        B01110,
        B00000,
    };
    pinMode(btn, INPUT_PULLUP);

    attachInterrupt(digitalPinToInterrupt(2), changeMode, LOW);

    lcd.createChar(0, smiley);
    // set up the LCD's number of columns and rows:
    lcd.begin(16, 2);
    // Print a message to the LCD.
    lcd.setCursor(3, 0);
    lcd.print("SILVA TECH");
    lcd.setCursor(0, 3);
    lcd.print("~~~~~~~~~~~~");
    delay(5000);

    if (!driver.init()) //reciever setup
    {
        Serial.println("init failed");
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("init failed...");
        lcd.setCursor(0, 1);
        lcd.print("Check Hardware");
    }
    else
    {
        lcd.clear();
        lcd.setCursor(1, 0);
        lcd.print("Reciever Found");
        delay(1000);
    }

    // lcd.clear();
    // lcd.setCursor(0, 0);
    // lcd.print("Finding ESP8266...");
    // delay(1000);
    // lcd.clear();

    // if (sendCommand("AT", 5, "OK"))
    // {

    //     lcd.setCursor(2, 0);
    //     lcd.print("ESP8266 FOUND!");
    //     delay(500);
    //     lcd.setCursor(0, 0);
    //     sendCommand("AT+CWMODE=3", 5, "OK");
    //     lcd.clear();
    //     lcd.print("Connecting to:");
    //     lcd.setCursor(0, 1);
    //     lcd.print(AP);
    //     delay(500);
    // }
    // else
    // {
    //     lcd.setCursor(0, 0);
    //     lcd.print("ESP8266 NOT FOUND!");
    //     delay(1000);
    // }

    // if (sendCommand("AT+CWJAP=\"" + AP + "\",\"" + PASS + "\"", 20, "OK"))
    // {
    //     lcd.clear();
    //     lcd.setCursor(1, 0);
    //     lcd.print("WIFI Connected!");
    //     delay(1000);
    // }
    // else
    // {
    //     lcd.clear();
    //     lcd.setCursor(0, 0);
    //     lcd.print("CONNECTION FAILED"); //try resarting it..
    //     delay(1000);
    // }

    lcd.clear();
    lcd.setCursor(2, 0);
    lcd.print("Safe Flight!");
    lcd.setCursor(0, 2);
    lcd.print("~~~~~~~~~~~~");
    delay(4000);
    lcd.clear();
}

void loop()
{
    if (radio.fetch_init_message()) //if a the initialsed message in recieved.. store the message and return true
    {
        lcd.clear();
        display.display_msg(radio.InitMessage); //display the message
        delay(2000);
        lcd.clear();
    }
    else if (radio.fetch_message()) //if anyother message is recieved... store the message and return true
    {
        lcd.clear();
        display.display_msg(radio.Message); //display the messge stored in the instant of the radio class
        delay(2000);
        lcd.clear();
    }
    else
    {
        switch (mode)
        {
        case 1:
            interval_display_coords.update(); //update the corrds in every minimum of 2 seconds
            if (radio.pitch.length() > 2 && radio.roll.length() > 2 && radio.longitude.length() > 2 && radio.latitude.length() && radio.Temp.length() > 2)
                interval_blackBox_entry.update(); // sends flight information to server every mninute
            break;
        case 0:
            interval_display_orien.update(); //update the orentations in every minimum 2 seconds
            if (radio.pitch.length() > 2 && radio.roll.length() > 2 && radio.longitude.length() > 2 && radio.latitude.length() && radio.Temp.length() > 2)
                interval_blackBox_entry.update(); // sends flight information to server every mninute
            break;
        default:
            break;
        }
    }
}

void changeMode()
{
    if (!digitalRead(btn)) //debounce prevension
    {
        delay(50);
        if (digitalRead(btn))
        {
            mode = !mode;
        }
    }
    else
    {
        return;
    }
}
