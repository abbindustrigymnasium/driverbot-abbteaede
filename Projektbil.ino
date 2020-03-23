#include "EspMQTTClient.h"
//#include "Servo.h"
//#include "PubSubClient.h"

//void onConnectionEstablished();

EspMQTTClient client(
  "HK2",           // Wifi ssid
  "Teaowilmer07",           // Wifi password
  "maqiatto.com",  // MQTT broker ip
  1883,             // MQTT broker port
  "tea.edelborg@abbindustrigymnasium.se",            // MQTT username
  "Hejsan",       // MQTT password
  "Bruhmoment",          // Client name
  onConnectionEstablished, // Connection established callback
  true,             // Enable web updater
  true              // Enable debug messages
);

//Servo mittservo; //anger namnet på servo
#define motorPinRightDir 0 //D2
#define motorPinRightSpeed 5//D1

#define motorPinLeftDir 2
#define motorPinLeftSpeed 4

int fart = 0;
bool go = false;
  
void setup() {

  Serial.begin(9600);
  pinMode(motorPinRightDir, OUTPUT);
  pinMode(motorPinRightSpeed, OUTPUT);
  pinMode(motorPinLeftDir, OUTPUT);
  pinMode(motorPinLeftSpeed, OUTPUT);
  //mittservo.attach(14);
  //mittservo.write(0);
}
void onConnectionEstablished()
{
  client.subscribe("tea.edelborg@abbindustrigymnasium.se/speed", [](const String &payload) {
    fart = payload.toInt();
    if (go==true) {
    Serial.println(fart);
    digitalWrite(motorPinRightSpeed, fart);
    digitalWrite(motorPinLeftSpeed, fart);
    }
  });
  client.subscribe("tea.edelborg@abbindustrigymnasium.se/backforward", [](const String &payload) {
    if (go == true) {
    if (payload == "framåt")
    {
      digitalWrite(motorPinRightDir, 0);
      digitalWrite(motorPinLeftDir, 0);
    }
    else
    {
      digitalWrite(motorPinRightDir, 1);
      digitalWrite(motorPinLeftDir, 1);
    }
    }
  });
  client.subscribe("tea.edelborg@abbindustrigymnasium.se/drive", [](const String &payload) {
    Serial.println(payload);
    if (payload == "1")
    {
      go = true;
    }
    else if (payload == "0")
    {
      go = false;
      digitalWrite(motorPinRightSpeed, 0);
      digitalWrite(motorPinLeftSpeed, 0);
    }
  });
}
void loop() {
  // put your main code here, to run repeatedly:
  client.loop();

}

//connecta till MQTT
//includa libraries
//defina hjulen
//defina allting i void setup
//gör en funktion där du kopplar upp dig till MQTT och lägg allt annat i den
//fixa en av och på 
//Om det är på hämta senaste värdet från MQTT och kö så snabbt, även ta om det är bakåt eller framåt
//Gör en funktion för att svänga, ta då om talet är större än 90 grader sväng höger, om talet är mindre än 90 grader sväng vänster
//När talet är en av dem så sätter man degress till ett visst värde och inte tex 10000, görs med en if sats
//Lampa som blinkar när man backar
