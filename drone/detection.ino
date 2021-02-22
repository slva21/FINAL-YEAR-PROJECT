#include "detection.h"
#include "main.h"

float Detection::updateUltrasonic()
{
    return 0.0001;
}

float Detection::ultrasonic()
{

    float distance_cm; // variable for centimeters measurement
    float distance_m;

    // while (distance_m >20){//ultra sonic sensor is buggy :(
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    // Sets the trigPin HIGH (ACTIVE) for 10 microseconds
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    // Reads the echoPin, returns the sound wave travel time in microseconds
    duration = pulseIn(echoPin, HIGH);

    // Calculating the distance
    distance_cm = (duration * 0.034) / 2.00; // Speed of sound wave divided by 2 (go and back)
                                             //  Serial.println(distance_cm);

    distance_m = distance_cm * 0.01;

    return distance_m;
}

void Detection::DistanceLedIndicatiors()
{
    float distance = ultrasonic();
    // Serial.println(distance);
    if (distance > greenDistance)
    {
        digitalWrite(ledGreen, HIGH); // Turn the LED on
        digitalWrite(ledBlue, LOW);   // Turn the LED on
        digitalWrite(ledYellow, LOW); // Turn the LED on
        digitalWrite(ledRed, LOW);    // Turn the LED on
    }
    if (distance < greenDistance and distance >= blueDistance)
    {
        digitalWrite(ledGreen, HIGH); // Turn the LED on
        digitalWrite(ledBlue, HIGH);  // Turn the LED on
        digitalWrite(ledYellow, LOW); // Turn the LED on
        digitalWrite(ledRed, LOW);    // Turn the LED on
    }
    if (distance < blueDistance and distance >= YellowDistance)
    {
        digitalWrite(ledGreen, HIGH);  // Turn the LED on
        digitalWrite(ledBlue, HIGH);   // Turn the LED on
        digitalWrite(ledYellow, HIGH); // Turn the LED on
        digitalWrite(ledRed, LOW);     // Turn the LED on
    }
    if (distance < YellowDistance)
    {
        digitalWrite(ledGreen, HIGH);  // Turn the LED on
        digitalWrite(ledBlue, HIGH);   // Turn the LED on
        digitalWrite(ledYellow, HIGH); // Turn the LED on
        digitalWrite(ledRed, HIGH);    // Turn the LED on
    }
}

bool Detection::check_approaching_velocity()
{
    previous_distance = ultrasonic();
    unsigned long currentTimeVelocity = millis();
    if (currentTimeVelocity - previousTimeVelocity >= velocityInterval)
    {
        current_distance = ultrasonic();
        digitalWrite(buzzer, LOW); //raise the voltage sent out of the pin by 1
        velocity = (current_distance - previous_distance) / (velocityInterval * 0.001);
        if (velocity >= 30)
        { // if absolulte velocity >= 30m/s
            previousTimeVelocity = currentTimeVelocity;
            return true;
        }
        else
        {
            previousTimeVelocity = currentTimeVelocity;
            return false;
        }
    };
}

void Detection::orientation()
{
    int ax = imu.accelx().toInt();

    if (ax > 4000)
    {
        myservo.write(150);
    }
    else if (ax < -4000)
    {
        myservo.write(30);
    }
    else
    {
        myservo.write(90);
    }
}

void Detection::handle_distance_led_indicators()
{
    if (statusSensor1 == 0 or statusSensor2 == 0 or statusSensor3 == 0 or statusSensor4 == 0 or statusSensor5 == 0 or statusSensor6 == 0 or statusSensor7 == 0)
    {
        digitalWrite(ledGreen, HIGH);  // Turn the LED on
        digitalWrite(ledBlue, HIGH);   // Turn the LED on
        digitalWrite(ledYellow, HIGH); // Turn the LED on
        digitalWrite(ledRed, HIGH);    // Turn the LED on
    }
    else
    {
        DistanceLedIndicatiors(); // leds are lit based on distance recorded by the ultrasonic sensor..
    }
}

void change_clear_state()
{
    clear = false;
}

