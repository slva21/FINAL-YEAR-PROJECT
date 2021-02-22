#include "main.h"
#include "rf.h"
//read me
//--Thie file is contains the posotioning sub system of the drone
//-- modules included are -- GPS, GPSLED and Transmitter

void positioning_sub_system()
{
  //**responsible for GPS and transmitter and GPS lED

  // This sketch displays information every time a new sentence is correctly encoded.
  while (Serial1.available() > 0)
    while (gps.encode(Serial1.read()))
    {
      displayInfo();
    }

  // If 5000 milliseconds pass and there are no characters coming in
  // over the software serial port, show a "No GPS detected" error
  if (millis() > 5000 && gps.charsProcessed() < 10)
  {
    Serial.println("No GPS detected");
  }
  /* code */
}

void displayInfo()
{
  String latitude;
  String longitude;

  if (gps.location.isValid())
  {
    digitalWrite(GPSLed, HIGH);

    Serial.print("Latitude: ");
    Serial.println(gps.location.lat(), 8);
    latitude = String(gps.location.lat(), 8);
    Serial.print("Longitude: ");
    Serial.println(gps.location.lng(), 6);
    longitude = String(gps.location.lng(), 7);
    Serial.print("Altitude: ");
    Serial.println(gps.altitude.meters());

    //transmit the the coordiantes
    // transmit(latitude, longitude);
  }
  else
  {
    Serial.println("Location: Not Available");
    digitalWrite(GPSLed, LOW); //indicate that the gps connection is not available and is not broadcasting.
  }

  Serial.print("Date: ");
  if (gps.date.isValid())
  {
    Serial.print(gps.date.month());
    Serial.print("/");
    Serial.print(gps.date.day());
    Serial.print("/");
    Serial.println(gps.date.year());
  }
  else
  {
    Serial.println("Not Available");
  }

  Serial.print("Time: ");
  if (gps.time.isValid())
  {
    if (gps.time.hour() < 10)
      Serial.print(F("0"));
    Serial.print(gps.time.hour());
    Serial.print(":");
    if (gps.time.minute() < 10)
      Serial.print(F("0"));
    Serial.print(gps.time.minute());
    Serial.print(":");
    if (gps.time.second() < 10)
      Serial.print(F("0"));
    Serial.print(gps.time.second());
    Serial.print(".");
    if (gps.time.centisecond() < 10)
      Serial.print(F("0"));
    Serial.println(gps.time.centisecond());
  }
  else
  {
    Serial.println("Not Available");
  }

  if (gps.location.isValid() && interval_gps.update())
  {
    radio.transmit_Lat(String(latitude).c_str()); //string must be 11bits
    int y = radio.transmit_long(String(longitude).c_str());
    Serial << strlen(String(latitude).c_str()) << endl;
  }

  Serial.println();
  Serial.println();
  // delay(1000);
}
