// my config libs
#include <WIFIConfig.h>
#include <ThingSpeakConfig.h>

#include <ESP8266WiFi.h>
#include <ThingSpeak.h>

/*
********************************************
14CORE ULTRASONIC DISTANCE SENSOR CODE TEST
********************************************
* https://www.14core.com/wiring-esp8266-nodemcu-with-hcsr04-ultrasonic-sensor/
* https://lastminuteengineers.com/arduino-sr04-ultrasonic-sensor-tutorial/
*/

// NodeMCU Pin D1 > TRIGGER | Pin D2 > ECHO
#define TRIGGER 5
#define ECHO    4 

#define D7 13
#define D8 15

// Wi-Fi Settings
const char* ssid = WIFIConfig::ssid;
const char* password = WIFIConfig::password;
//bool wifiConnected = false;

// ThingSpeak Settings
const unsigned long channelID = ThingSpeakConfig::channelID;
const char* writeAPIKey = ThingSpeakConfig::writeAPIKey;

WiFiClient client;

bool WiFiconnect() {

  // Connect to Wifi.
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  
  WiFi.begin(ssid, password);

  // WiFi fix: https://github.com/esp8266/Arduino/issues/2186
  WiFi.persistent(false);
  WiFi.mode(WIFI_OFF);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  
  unsigned long wifiConnectStart = millis();

  Serial.print("Connecting to: ");
  Serial.println(ssid);

  Serial.print("channelID: ");
  Serial.println(channelID);

  while (WiFi.status() != WL_CONNECTED) {
    // Check to see if
    if (WiFi.status() == WL_CONNECT_FAILED) {
      Serial.println("Failed to connect to WiFi. Please verify credentials: ");
      delay(10000);
    }

    delay(500);
    Serial.println("...");
    // Only try for 5 seconds.
    if (millis() - wifiConnectStart > 15000) {
      Serial.println("Failed to connect to WiFi");
      return false;
    }
  }
  //wifiConnected = true;

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  return true;
}

void sendToThingSpeak(long distance) {

    //float distanceInMeters = (float) (distance / 100); 
    //Serial.print("Meters:");
    //Serial.println(distanceInMeters);
  
    ThingSpeak.begin(client);
    //ThingSpeak.setField(1, distanceInMeters);
    ThingSpeak.setField(1, distance);

    // write to the ThingSpeak channel
    int thingSpeakResponse = ThingSpeak.writeFields(channelID, writeAPIKey);

    if(thingSpeakResponse){
      Serial.println("Channel update successful.");
    } else{
      Serial.println("Problem updating channel. HTTP error code " + String(thingSpeakResponse));
    }
}

void setup() {
  
  Serial.begin (115200);

  ledPrepare();

  pinMode(TRIGGER, OUTPUT);
  pinMode(ECHO, INPUT);
//  pinMode(BUILTIN_LED, OUTPUT);

}

void ledPrepare() {
  pinMode(D7, OUTPUT);     // Initialize the LED_BUILTIN pin as an output
  pinMode(D8, OUTPUT);
}

void ledOn() {
  digitalWrite(D8, HIGH);
  digitalWrite(D7, LOW);
}

void ledOff(){
  digitalWrite(D7, HIGH);
  digitalWrite(D8, LOW);  
}

void loop() {

  long duration, 
    distance, 
    delayTime = 1000 * 10;
 
  bool isConnected = true;

  digitalWrite(TRIGGER, LOW);  
  delayMicroseconds(2); 
  
  digitalWrite(TRIGGER, HIGH);
  delayMicroseconds(10); 
  
  digitalWrite(TRIGGER, LOW);
  
  duration = pulseIn(ECHO, HIGH);

  Serial.print("Duration:");
  Serial.println(duration);
  
  distance = (duration/2) / 29.1;
  //distance= duration*0.034/2;

  Serial.print("Centimeters:");
  Serial.println(distance);

  if (WiFi.status() != WL_CONNECTED) {
    if (!WiFiconnect()) {
      isConnected = false;     
    }    
  }

  if (isConnected) {
    ledOn();
    sendToThingSpeak(distance);     
  } else {
    ledOff();
  }
  
  delay(delayTime);
}
