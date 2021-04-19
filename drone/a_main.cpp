#include "main.h"

noDelay interval_gps(5000);

void setup()
{
  controll_roll_left.SetMode(AUTOMATIC);
  controll_roll_left.SetOutputLimits(90.0, 255.0);
  controll_roll_right.SetMode(AUTOMATIC);
  controll_roll_right.SetOutputLimits(90.0, 255.0);

  controll_pitch_left.SetMode(AUTOMATIC);
  controll_pitch_left.SetOutputLimits(90.0, 255.0);
  controll_pitch_right.SetMode(AUTOMATIC);
  controll_pitch_right.SetOutputLimits(90.0, 255.0);

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

  //attachInterrupt(digitalPinToInterrupt(2), change_clear_state, FALLING);

  radio.transmit_any("Initialized!");
}

void loop()
{

  pid_pitch_control.autolevel(imu.get_pitch_angle());
  pid_roll_control.autolevel(imu.get_roll_angle());

  Serial << pid_pitch_control.left_output << "," << pid_pitch_control.right_output << ","
         << imu.get_pitch_angle() << endl;

  myMotor.pid_pitch_control(pid_pitch_control.left_output, pid_pitch_control.right_output);

  myMotor.pid_roll_control(pid_roll_control.left_output, pid_roll_control.right_output);
  // transmitRoll.sendData(imu.get_roll_angle(), 1);
  // transmitPitch.sendData(imu.get_pitch_angle(), 1);
  //Serial << detect.ultrasonic() << endl;
  //myMotor.set_motor_4(myMotor.upVector);
  //myMotor.set_motor_2(myMotor.upVector);
  //myMotor.set_motor_3(myMotor.upVector);
  //myMotor.set_motor_1(myMotor.upVector);

  //myMotor.set_motor_4(myMotor.downVector);
  // myMotor.command_drone_hover();
  //digitalWrite(ledRed, HIGH);
  //digitalWrite(ledBlue, HIGH);
  //digitalWrite(ledGreen, HIGH);
  //digitalWrite(ledYellow, HIGH);
  // while (clear)
  // {
  //   positioning_sub_system();

  //   double roll = imu.get_roll_angle();
  //   double pitch = imu.get_pitch_angle();

  //   radio.transmit_pitch(convert_double_to_string_with_len(pitch, 7).c_str());
  //   radio.transmit_roll(convert_double_to_string_with_len(roll, 8).c_str());
  // }

  // avoid.avoidance();
  // radio.transmit_warning();

  // clear = true;

  // if (digitalRead(IRSensor1) == 0)
  // {
  //   Serial << "1" << endl;
  // }
  // if (digitalRead(IRSensor2) == 0)
  // {
  //   Serial << "2" << endl;
  // }
  // if (digitalRead(IRSensor3) == 0)
  // {
  //   Serial << "3" << endl;
  // }
  // if (digitalRead(IRSensor4) == 0)
  // {
  //   Serial << "4" << endl;
  // }
  // if (digitalRead(IRSensor5) == 0)
  // {
  //   Serial << "5" << endl;
  // }
  // if (digitalRead(IRSensor6) == 0)
  // {
  //   Serial << "6" << endl;
  // }
  // if (digitalRead(IRSensor7) == 0)
  // {
  //   Serial << "7" << endl;
  // }
}

// //front = 5,4

// //side =  6,7

// //back = 2, 3, ,1
