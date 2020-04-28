#include "EspMQTTClient.h"
#include "Servo.h"

EspMQTTClient client( //Inställningar för mqtt
  "HK2",           // Wifi ssid HK2
  "Teaowilmer07",           // Wifi password Teaowilmer07
  "maqiatto.com",  // MQTT broker ip
  1883,             // MQTT broker port
  "tea.edelborg@abbindustrigymnasium.se",            // MQTT username
  "Hejsan",       // MQTT password
  "Bruhmoment",          // Client name
  onConnectionEstablished, // Connection established callback
  true,             // Enable web updater
  true              // Enable debug messages
);

Servo mittservo; //anger namnet på servo
#define motorPinRightDir 0 //D2
#define motorPinRightSpeed 5//D1

#define motorPinLeftDir 2
#define motorPinLeftSpeed 4

int deg = 0; //definerar värden som kommer användas
int fart = 0;
bool go = false;
  
void setup() {

  Serial.begin(9600);
  pinMode(motorPinRightDir, OUTPUT);
  pinMode(motorPinRightSpeed, OUTPUT);
  pinMode(motorPinLeftDir, OUTPUT);
  pinMode(motorPinLeftSpeed, OUTPUT);
  mittservo.attach(15); 
  mittservo.write(90);
}
void onConnectionEstablished() //funktion hämtar värdena från mqtt och gör om värdena för motorn och servot
{
  client.subscribe("tea.edelborg@abbindustrigymnasium.se/speed", [](const String &payload) { //hämtar från topicen speed
    fart = payload.toInt(); //gör om stringen till en int
    if (go==true) { //körs bara om bilen har satts på
    Serial.println(fart);
    digitalWrite(motorPinRightSpeed, fart); //sätter farten till båda hjulen
    digitalWrite(motorPinLeftSpeed, fart);
    }
  });
  client.subscribe("tea.edelborg@abbindustrigymnasium.se/backforward", [](const String &payload) { //hämtar värdet från backforward topicen
    Serial.println(payload);
    if (go == true) {
    if (payload == "1") //Om payload är 1 kör bilen bakåt
    {
      digitalWrite(motorPinRightDir, 1);
      digitalWrite(motorPinLeftDir, 1);
    }
    else if (payload == "0") //annars kör den framåt
    {
      digitalWrite(motorPinRightDir, 0);
      digitalWrite(motorPinLeftDir, 0);
    }
    }
  });
  client.subscribe("tea.edelborg@abbindustrigymnasium.se/drive", [](const String &payload) { //om bilen är på eller inte, beroende om sidan är på eller inte
    Serial.println(payload);
    if (payload == "1") //om den är på kan de andra värdena ändras
    {
      go = true;
    }
    else if (payload == "0") //om det är false sätts farten till 0
    {
      go = false;
      digitalWrite(motorPinRightSpeed, 0);
      digitalWrite(motorPinLeftSpeed, 0);
    }
  });
  client.subscribe("tea.edelborg@abbindustrigymnasium.se/deg", [](const String &payload) { //hämtar vinkeln till servot
    deg= payload.toInt(); //gör om det till en int
    mittservo.write(deg); //sätter servot till det värdet
  });
}
void loop() {
  client.loop(); //kör setup om och om igen

}
