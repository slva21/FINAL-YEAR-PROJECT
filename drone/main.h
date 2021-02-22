#pragma once //makes sure the header file is not included more than on in a file

#include <RadioHead.h>
#include <TinyGPS++.h>
#include <Servo.h>
#include <NoDelay.h>
//servo setup.......

#include <RH_ASK.h>
// Include dependant SPI Library
#include <SPI.h>
#include "Wire.h" // This library allows you to communicate with for imu
#include "imu.h"
#include <HardwareSerial.h>
#include "motors.h"
#include "detection.h"
#include "avoidance.h"
#include "kalman.h"
#include <Streaming.h>
#include "pid.h"
#include "rf.h"
#include "PID_v1.h"

//****object declerations****
RH_ASK rf_driver; // Create Amplitude Shift Keying Object
TinyGPSPlus gps;  // Create a TinyGPS++ object
IMU imu;          // Create imu object
Servo myservo;    // create servo object to control a servo
Motors myMotor;
Detection detect;
Avoidance avoid;
Kalman kalmanX; // Create the Kalman instances
Kalman kalmanY;
RF radio;
AutoLevel autoLevel;
//scl= blue
//sda = orange

PID rollPID(&autoLevel.roll, &autoLevel.pid_roll_pwm_output, &autoLevel.Setpoint, autoLevel.Kp, autoLevel.Ki, autoLevel.Kd, DIRECT);

PID pitchPID(&autoLevel.pitch, &autoLevel.pid_pitch_pwm_output, &autoLevel.Setpoint, autoLevel.Kp, autoLevel.Ki, autoLevel.Kd, DIRECT);

//**defines*****

//Ultrasonic setup.................
#define echoPin 23 // attach pin D12 Arduino to pin Echo of HC-SR04
#define trigPin 25 //attach pin D13 Arduino to pin Trig of HC-SR04
#define buzzer 45  //black

int IRSensor1 = 36; // green to black
int IRSensor2 = 38; //white
int IRSensor3 = 40; //grey back
int IRSensor4 = 2;  //brown
int IRSensor5 = 39; //blue
int IRSensor6 = 22; //white
int IRSensor7 = 42; //yellow

float greenDistance = 1;
float blueDistance = 0.75;
float YellowDistance = 0.5;
// redDiance < 0.5

//imu setup
const int MPU_ADDR = 0x68; // I2C address of the MPU-6050. If AD0 pin is set to HIGH, the I2C address will be 0x69.

//........
long duration; // variable for the duration of sound wave travel
const unsigned long velocityInterval = 20;
const unsigned long buzzInterval = 1000;
unsigned long previousTimeVelocity = 0;
unsigned long previousTimeBuzzer = 0;

float previous_distance;
float current_distance;
float velocity;
volatile bool clear = true; // variable is used inside ISR

int GPSLed = 49;    //yellow;
int ledGreen = 52;  //green
int ledBlue = 53;   //blue
int ledYellow = 51; //black
int ledRed = 50;    //red

int INA1 = 11;
int INB1 = 13;
int INB2 = 8;
int INA2 = 7;
int INA3 = 6;
int INB3 = 5;
int INA4 = 4;
int INB4 = 7;

const int left = 180;
const int right = 10;

//******declare functions****.....

void positioning_sub_system();

char *convert_int16_to_str(int16_t i);
