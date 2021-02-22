#pragma once //makes sure the header file is not included more than on in a file

class Detection
{
private:
    //ir sensors setup
    int IRSensor1 = 36; // green to black
    int IRSensor2 = 38; //white
    int IRSensor3 = 40; //grey back
    int IRSensor4 = 2;  //brown
    int IRSensor5 = 39; //blue
    int IRSensor6 = 22; //white
    int IRSensor7 = 42; //yellow

    float greenDistance = 1.40;
    float blueDistance = 1.10;
    float YellowDistance = 0.70;
    // redDiance < 0.5

    int statusSensor1 = digitalRead(IRSensor1);
    int statusSensor2 = digitalRead(IRSensor2);
    int statusSensor3 = digitalRead(IRSensor3);
    int statusSensor4 = digitalRead(IRSensor4);
    int statusSensor5 = digitalRead(IRSensor5);
    int statusSensor6 = digitalRead(IRSensor6);
    int statusSensor7 = digitalRead(IRSensor7);

private:
    void DistanceLedIndicatiors();
    bool check_approaching_velocity();

public:
    void handle_distance_led_indicators();
    float ultrasonic();
    void orientation();
    float updateUltrasonic();
};

void change_clear_state();