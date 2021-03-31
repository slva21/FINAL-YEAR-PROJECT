#include <ESP8266WiFi.h>
const char *ssid = "MEWS-WB7";                              //wifi name
const char *password = "derate-topnotch-cantata";           //wifi password. **Dont share my password lol.**
const char *host = "secure-everglades-35219.herokuapp.com"; //sever host address
bool payloadReady;
String payload;

void setup()
{
    Serial.begin(115200);
    delay(100);
    //connecting to a WiFi network
    Serial.print("Connecting to ");
    Serial.println(ssid);
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED)
    { //connect to wifi network
        delay(500);
        Serial.print("WIFI CONNECTING");
    }

    Serial.println("");
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
}

void loop()
{

    while (Serial.available())
    { //read the payload sent over by the arduino mega board
        payload = Serial.readString();
        payloadReady = true;
    }

    if (payloadReady)
    {
        sendPost(); //send the payload to the server
        payloadReady = false;
    }
}

void sendPost()
{
    WiFiClient client; //create a client instance
    const int httpPort = 80;
    if (!client.connect(host, httpPort))
    { //connect to the server
        Serial.println("Server failed");
        return;
    }

    //start post request....
    Serial.print("Requesting POST: ");
    // Send request to the server:
    client.println("POST /api/302maa/blackbox HTTP/1.1");
    client.println("Host: secure-everglades-35219.herokuapp.com");
    client.println("Accept: */*");
    client.println("Content-Type: application/json");
    client.print("Content-Length: ");
    client.println(payload.length());
    client.println();
    client.print(payload);
    Serial.print("SENT"); //indicat to the aruino that the payload has been sent

    delay(500); // Can be changed
    if (client.connected())
    {
        client.stop(); // DISCONNECT FROM THE SERVER
    }
    delay(5000);
}