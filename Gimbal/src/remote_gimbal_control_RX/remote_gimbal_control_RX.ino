/*  Gimbal control receiver
    Autor: Tech No Logic 
    Date: Jan 2018

    HC-12
    Connect HC12 "RXD" pin to Arduino Digital Pin 3
    Connect HC12 "TXD" pin to Arduino Digital Pin 2
    
    Power HC12 with a supply of at least 100 mA with 
    a 22 uF - 1000 uF reservoir capacitor.
    
    Transceivers must be at least several meters apart to work.

    Servos
    Connect Pan Servo to pin 4
    Connect Tilt Servo to pin 5
   
 */

#include "Servo.h"

// pan settings
Servo pan_servo; 
int pan_pin = 4;              // pan servo pin
int pan_angle = 90;

// tilt settings
Servo tilt_servo;
int tilt_pin = 5;             // tilt servo pin
int tilt_angle = 90;


#include <SoftwareSerial.h>

const byte HC12RxdPin = 3;                  // Recieve Pin on HC12
const byte HC12TxdPin = 2;                  // Transmit Pin on HC12

SoftwareSerial HC12(HC12TxdPin,HC12RxdPin); // Create Software Serial Port

// include the library code:
#include <LiquidCrystal.h>

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 12, en = 11, d4 = 6, d5 = 7, d6 = 8, d7 = 9;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup() {
  // Debugging
  Serial.begin(9600);
  
  HC12.begin(9600);                         // Open serial port to HC12

  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print("Angles:");

  // associate servo pins
  pan_servo.attach(4);
  tilt_servo.attach(5);

  // begin centered
  pan_servo.write(pan_angle);
  tilt_servo.write(tilt_angle);
}

void loop() {
  // If Arduino's HC12 rx buffer has data, write to servos
  if(HC12.available()>=2){                     
    pan_angle = HC12.read();
    tilt_angle = HC12.read();

    // send command to servos
    pan_servo.write(pan_angle);
    tilt_servo.write(tilt_angle);

    // lcd debug
    lcd.setCursor(0, 1);
    lcd.print(pan_angle, DEC);
    lcd.print(" ");
    lcd.print(tilt_angle, DEC);
    lcd.print("     ");
    }
  else{
    Serial.print("...");
  }  
  
  delay(100);
}
