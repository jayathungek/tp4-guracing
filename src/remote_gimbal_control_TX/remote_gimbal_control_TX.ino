/*  Remote gimbal control using thumb joystick
    
    Author: Tech No Logic
    Date: Jan 2018

    HC-12
    Connect HC12 "RXD" pin to Arduino Digital Pin 8
    Connect HC12 "TXD" pin to Arduino Digital Pin 9

    Power HC12 with a supply of at least 100 mA with 
    a 22 uF - 1000 uF reservoir capacitor.

    Joystick
    Connect "VRX" pin to Arduino Analog Pin 0
    Connect "VRY" pin to Arduino Analog Pin 1
    Connect "SW" pin to Arduino Digital Pin 3
      
 */

// pan settings
int pan_angle = 90, old_pan = 90;
float pan_delta = 0;  
int joy_x = A0;           // VRX pin on joystick
int a_in_x;

//tilt settings
int tilt_angle = 90, old_tilt = 90;
float tilt_delta = 0;  
int joy_y = A1;           // VRY pin on joystick
int a_in_y;
int tilt_low_lim = 10, tilt_high_lim = 170;

// switch
int SW_pin = 3;           // SW pin on joystick

const float coef = 0.039;

// HC-12
#include <SoftwareSerial.h>

const byte HC12RxdPin = 8;                  // Recieve Pin on HC12
const byte HC12TxdPin = 9;                  // Transmit Pin on HC12

SoftwareSerial HC12(HC12TxdPin,HC12RxdPin); // Create Software Serial Port


void setup() {
  // activate button
  pinMode(SW_pin, INPUT);
  digitalWrite(SW_pin, HIGH);

  // Open serial port to HC12
  HC12.begin(9600);
  
  // Debugging
  Serial.begin(9600);
}

void loop() {
  // deal with pan
  a_in_x = analogRead(joy_x); // reading joy_x range 0 and 1023
  
  // calculate delta
  if (a_in_x < 470 or a_in_x > 550) {
    pan_delta = coef * a_in_x - 20;
    }
  else{
    pan_delta = 0;
  }
  
  // adjust angle
  pan_angle += pan_delta;
  if (pan_angle < 0) {pan_angle = 0;}
  if (pan_angle > 180) {pan_angle = 180;}
  
  
  // deal with tilt
  a_in_y = analogRead(joy_y); // reading joy_x range 0 and 1023
  
  // calculate delta
  if (a_in_y < 470 or a_in_y > 550) {
    tilt_delta = coef * a_in_y - 20;
    }
  else{
    tilt_delta = 0;
  }
  
  // adjust angle
  tilt_angle += tilt_delta;
  if (tilt_angle < tilt_low_lim) {tilt_angle = tilt_low_lim;}
  if (tilt_angle > tilt_high_lim) {tilt_angle = tilt_high_lim;}


  // if button pressed -- reset position
  if (digitalRead(SW_pin) == 0){
    pan_angle = 90;
    tilt_angle = 90;  
  }

  // only send if at least one value changes (saves energy)
  if (pan_angle != old_pan or tilt_angle != old_tilt){
  // send commands
    HC12.write(pan_angle); 
    HC12.write(tilt_angle);

    old_pan = pan_angle;
    old_tilt = tilt_angle;

    // debug
    Serial.println(pan_angle);
    Serial.println(tilt_angle);
  }
  
  delay(100);
}
