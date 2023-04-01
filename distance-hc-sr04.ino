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

#define D5 14
#define D6 12

#define D7 13
#define D8 15

#define SAFE_DISTANCE 6

void setup() {
  
  Serial.begin (115200);

  //safeLEDPrepare();
  //warningLEDPrepare();
  //turnOnWarning();
  
  pinMode(TRIGGER, OUTPUT);
  pinMode(ECHO, INPUT);
  
//  pinMode(BUILTIN_LED, OUTPUT);
}

void safeLEDPrepare() {
  pinMode(D7, OUTPUT);     // Initialize the LED_BUILTIN pin as an output
  pinMode(D8, OUTPUT);
}

void loop() {

  long duration, 
    distance, 
    delayTime = 1000 * 5;
 
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
  
//  if (distance < SAFE_DISTANCE) {
//    turnOnWarning();  
//  } else {
//    turnOnSafe();  
//  }

  delay(delayTime);
}


void safeLEDOn() {
  digitalWrite(D8, HIGH);
  digitalWrite(D7, LOW);
}

void safeLEDOff(){
  digitalWrite(D7, HIGH);
  digitalWrite(D8, LOW);  
}

void warningLEDPrepare() {
  pinMode(D5, OUTPUT);     // Initialize the LED_BUILTIN pin as an output
  pinMode(D6, OUTPUT);
}

void warningLEDOn() {
  digitalWrite(D5, HIGH);
  digitalWrite(D6, LOW);
}

void warningLEDOff(){
  digitalWrite(D6, HIGH);
  digitalWrite(D5, LOW);  
}

void turnOnWarning() {
  safeLEDOff(); 
  warningLEDOn(); 
}

void turnOnSafe() {
  safeLEDOn();
  warningLEDOff();
}
