//
// example for Nunchuck library
// Author: alonso.brain@yahoo.es 
// Date: 30.03.2008
//

#include <Wire.h>
#include <string.h>
// #include <stdio.h>
#include <Nunchuck.h>


Nunchuck myNunchuck (0x52);

int cnt = 0;
int ledPin = 13;


int enviar = 0 ;


void setup (){
  beginSerial (19200);
  Serial.print ("Finished setup\n");
  Wire.begin (); // join i2c bus with address 0x52
  myNunchuck.init (); // send the initilization handshake
}





void loop ()
{
  myNunchuck.read () ;
  print ();
  myNunchuck.sendZero (); // send the request for next bytes
  delay (25);
}





void print ()
{

  if (Serial.available() > 0) {
      int incomingByte = Serial.read();
      enviar=1;
  }      
  if (myNunchuck.enviar == 1) enviar = 1 ;

  if (enviar==1) {
        digitalWrite (ledPin, HIGH); // sets the LED on
	Serial.print (myNunchuck.joy_x_axis);
	Serial.print ("\t");

	Serial.print (myNunchuck.joy_y_axis);
	Serial.print ("\t");

	Serial.print ((myNunchuck.accel_x_axis >> 8) & 0xFF);
	Serial.print ("\t");
	Serial.print ((myNunchuck.accel_x_axis) & 0xFF);
	Serial.print ("\t");

	Serial.print ((myNunchuck.accel_y_axis >> 8) & 0xFF);
	Serial.print ("\t");
	Serial.print ((myNunchuck.accel_y_axis) & 0xFF);
	Serial.print ("\t");

	Serial.print ((myNunchuck.accel_z_axis >> 8) & 0xFF);
	Serial.print ("\t");
	Serial.print ((myNunchuck.accel_z_axis) & 0xFF);
	Serial.print ("\t");

	Serial.print (myNunchuck.z_button);
	Serial.print ("\t");
	Serial.print (myNunchuck.c_button);
	Serial.print ("\n");}
        digitalWrite (ledPin, LOW); // sets the LED off
 }
