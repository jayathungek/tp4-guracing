#include <Servo.h>
Servo servo1;
Servo servo2;
int x_key = A1;                                               
int y_key = A0;                                               
int x_pos;
int y_pos;
int servo1_pin = 8;
int servo2_pin = 9;  
int initial_position = 90;
int initial_position1 = 90;

void setup ( ) {
  Serial.begin (9600) ;
  servo1.attach (servo1_pin ); 
  servo2.attach (servo2_pin ) ; 
  servo1.write (initial_position);
  servo2.write (initial_position1);
  pinMode (x_key, INPUT);                     
  pinMode (y_key, INPUT);     
  pinMode (LED_BUILTIN, OUTPUT);                 
}

void loop() {
  x_pos = analogRead(x_key);
  y_pos = analogRead(y_key);

  if(x_pos < 300){
    if (initial_position < 10) {}
    else {
      initial_position = initial_position - 20;
      servo1.write(initial_position);
      delay(100);
    }
  }

  if(x_pos > 700){
    if(initial_position > 180) {}
    else {
      initial_position = initial_position + 20;
      servo1.write(initial_position);
      delay(100);
    }
  }

  if(y_pos < 300){
    if (initial_position1 < 10) {}
    else {
      initial_position1 = initial_position1 - 20;
      servo2.write(initial_position1);
      delay(100);
    }
  }

  if(y_pos > 700){
    if(initial_position > 180) {}
    else {
      initial_position1 = initial_position1 + 20;
      servo2.write(initial_position1);
      delay(100);
    }
  }

  Serial.print("X: ");
  Serial.print(x_pos);
  Serial.print(" | Y: ");
  Serial.print(y_pos);
  Serial.print(" | initial position x: ");
  Serial.println(initial_position);
  Serial.print(" | initial position y");
  Serial.println(initial_position1);
  digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(100);                       // wait for a second
  digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
  delay(100);
}

