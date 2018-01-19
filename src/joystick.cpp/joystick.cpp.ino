/* 
Date: ----------------------------------------- December 22, 2015 
Title: ---------- JOYSTICK POTENTIOMETER CALIBRATION 
Author: --------------------- By Firas Helou ------------------------

Learn how to calibrate a joystick potentiometer with Arduino Uno

*/

int defaultY; //Setting a variable for default potentiometer data on start 
int dataY; //Variable to store data read on analog Arduino pin A0 coming from the potentiometer 
int defaultX; //Setting a variable for default potentiometer data on start 
int dataX; //Variable to store data read on analog Arduino pin A1 coming from the potentiometer 
int startTime = 0; //Time variable data type is defined as integer because we do not need more than 10 //microseconds 
int TimeGap = 10; //Defining the time gap
int B_pin = 9; //button pin
int B;// button value
int remapY; //Remap variable to store the remaped data coming from the analog Arduino pin A0
int remapX;

//VOID SETUP() FUNCTION 
void setup() { 
//Setting Serial communication at default rate 
Serial.begin(9600); 
//We set time to define the default value read on the analog Arduino pin A0, because we have a centered joystick pin, //so its default value is different than 0 
if ( micros() - startTime >= TimeGap ){ 
//Potentiometer connected to analog Arduino 
defaultY = analogRead(A0);
defaultX = analogRead(A1); 
pinMode(B, INPUT);
}

}

//VOID LOOP() FUNCTION 
void loop(){ 
//We set data value equal the one read on the analog Arduino pin A0 
dataY = analogRead(A0); //In this case, the default value read on start is 488 
dataX = analogRead(A1); 
B = digitalRead(B_pin);
if(dataY < defaultY + 1){ 
//We must remap the data value read on analog Arduino pin A0 to a smaller value between 0 and 255 
//but we must subtract 1 from the default value, because if we don't, we will not have a default value of 0 when the //stick position is centered 
//instead we will have a floating value between 1 and 0 
//so to avoid that floating problem we simply subtract - 1 
remapY = map(dataY, 0, defaultY - 1, 255, 0);

}else if(dataY >= defaultY){ 
//In this part, we do not need to subtract anything 
remapY = map(dataY, defaultY, 1023, 0, 255);

}

if(dataX < defaultX + 1){ 
//We must remap the data value read on analog Arduino pin A0 to a smaller value between 0 and 255 
//but we must subtract 1 from the default value, because if we don't, we will not have a default value of 0 when the //stick position is centered 
//instead we will have a floating value between 1 and 0 
//so to avoid that floating problem we simply subtract - 1 
remapX = map(dataX, 0, defaultX - 1, 255, 0);

}else if(dataX >= defaultX){ 
//In this part, we do not need to subtract anything 
remapX = map(dataX, defaultX, 1023, 0, 255);

}

//Serial print the values we receive 
Serial.print("X_remap: "); 
Serial.println(remapX);
//Serial.print("Y_remap: "); 
//Serial.println(remapY);
Serial.print("X: "); 
Serial.println(dataX);
//Serial.print("Y: "); 
//Serial.println(dataY);
//Serial.print("Button: "); 
//Serial.println(B);

delay(200);

}
