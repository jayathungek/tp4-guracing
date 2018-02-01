#include <Servo.h>
Servo servo1;
Servo servo2;
int x_key = A1;                                               
int y_key = A0;                                               
int x_pos;
int y_pos;
int initial_position = 90;
int initial_position1 = 90;
int buttonState = 0;
int step = 10;
int delayValue = 500; // in ms

const int servo1_pin = 8;
const int servo2_pin = 9;  
const int buttonPin = 7;

void setup() {
  Serial.begin (9600) ;
  servo1.attach (servo1_pin ); 
  servo2.attach (servo2_pin ) ; 
  servo1.write (initial_position);
  servo2.write (initial_position1);
  pinMode (x_key, INPUT);                     
  pinMode (y_key, INPUT);
  pinMode(buttonPin, INPUT);     
  pinMode (LED_BUILTIN, OUTPUT);                 
}

void loop() {
  buttonState = digitalRead(buttonPin);

  if(buttonState == HIGH) {
    initial_position = 90;
    servo1.write(initial_position);
    delay(100);
    initial_position1 = 90;
    servo2.write(initial_position1);
    delay(100);
    digitalWrite(LED_BUILTIN, HIGH);
  } else {
    digitalWrite(LED_BUILTIN, LOW);
  }
 
  x_pos = analogRead(x_key);
  y_pos = analogRead(y_key);

  if(x_pos < 300){
    if (initial_position < 10) {}
    else {
      initial_position = initial_position - step;
      servo1.write(initial_position);
      delay(delayValue);
    }
  }

  if(x_pos > 700){
    if(initial_position > 180) {}
    else {
      initial_position = initial_position + step;
      servo1.write(initial_position);
      delay(delayValue);
    }
  }

  if(y_pos < 300){
    if (initial_position1 < 10) {}
    else {
      initial_position1 = initial_position1 - step;
      servo2.write(initial_position1);
      delay(delayValue);
    }
  }

  if(y_pos > 700){
    if(initial_position > 180) {}
    else {
      initial_position1 = initial_position1 + step;
      servo2.write(initial_position1);
      delay(delayValue);
    }
  }

  //Serial.print("X: ");
  //Serial.println(x_pos);
  //Serial.print("Y: ");
  //Serial.println(y_pos);
  //Serial.print(" | initial position x: ");
  //Serial.println(initial_position);
  //Serial.print(" | initial position y: ");
  //Serial.print(initial_position1);
  Serial.print(" | Button State");
  Serial.println(buttonState); 
  
}

