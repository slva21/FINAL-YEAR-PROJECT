#include "main.h"

noDelay interval_gps(5000);

void setup()
{
  pitchPID.SetMode(AUTOMATIC);
  rollPID.SetMode(AUTOMATIC);

  Serial.begin(9600);
  Serial1.begin(9600); //for gps

  Wire.begin();
  Wire.beginTransmission(MPU_ADDR);
  Wire.write(0x6B);
  Wire.write(0);
  Wire.endTransmission(true);

  myservo.attach(9); // attaches the servo on pin 9 to the servo object

  pinMode(trigPin, OUTPUT); // Sets the trigPin as an OUTPUT
  pinMode(echoPin, INPUT);  // Sets the echoPin as an INPUT
  pinMode(buzzer, OUTPUT);  //tell arduino the buzzer is an output device

  pinMode(ledGreen, OUTPUT);  // Declare the LED as an output
  pinMode(ledBlue, OUTPUT);   // Declare the LED as an output
  pinMode(ledYellow, OUTPUT); // Declare the LED as an output
  pinMode(ledRed, OUTPUT);    // Declare the LED as an output

  //..ir sensors
  pinMode(IRSensor1, INPUT);
  pinMode(IRSensor2, INPUT);
  pinMode(IRSensor3, INPUT);
  pinMode(IRSensor4, INPUT); // sensor pin INPUT
  pinMode(IRSensor5, INPUT);
  pinMode(IRSensor6, INPUT);
  pinMode(IRSensor7, INPUT);

  pinMode(GPSLed, OUTPUT);
  rf_driver.init();
  delay(200);
  positioning_sub_system();
  pinMode(INA1, OUTPUT);
  pinMode(INB1, OUTPUT);
  pinMode(INA2, OUTPUT);
  pinMode(INB2, OUTPUT);
  pinMode(INA3, OUTPUT);
  pinMode(INB3, OUTPUT);
  pinMode(INA4, OUTPUT);
  pinMode(INB4, OUTPUT);

  digitalWrite(INA1, LOW);
  digitalWrite(INB1, LOW);
  digitalWrite(INA2, LOW);
  digitalWrite(INB2, LOW);
  digitalWrite(INA3, LOW);
  digitalWrite(INB3, LOW);
  digitalWrite(INA4, LOW);
  digitalWrite(INB4, LOW);

  attachInterrupt(digitalPinToInterrupt(2), change_clear_state, FALLING);

  radio.transmit_any("Initialized!");
}

void loop()
{

  while (clear)
  {
    positioning_sub_system();

    double roll = imu.get_roll_angle();
    double pitch = imu.get_pitch_angle();

    radio.transmit_pitch(convert_double_to_string_with_len(pitch, 7).c_str());
    radio.transmit_roll(convert_double_to_string_with_len(roll, 8).c_str());
  }

  avoid.avoidance();
  radio.transmit_warning();

  clear = true;
}

// //front = 5,4

// //side =  6,7

// //back = 2, 3, ,1
