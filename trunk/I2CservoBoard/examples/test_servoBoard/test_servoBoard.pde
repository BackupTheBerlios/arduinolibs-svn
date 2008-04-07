#include <I2C_SRF08n.h>
#include <I2CservoBoard.h>
#include <I2C_compass.h>

// include the SoftwareSerial library
#include <SoftwareSerial.h>

////////////////////////////////////////////////////////////////////////////////
#include <Wire.h>
#include <string.h>
#include <stdio.h>

int ledPin = 13;
////////////////////////////////////////////////////////////////////////////////




unsigned long lastUpdateEnviarDatos = 0 ;
unsigned short refreshTimeEnvio = 1000;


unsigned long lastSignal[4] ;
unsigned short refreshTime = 50;
unsigned short refreshSecurityTime = 2000;
unsigned long lastUpdatedTime, timeLastFast;
boolean vaciarI2CBuffer = false ;

int MAXSERVOS = 4 ;
I2CservoBoard myBoard(0x61,MAXSERVOS) ; 

int posiciones[4] ;




void setup(){
}





void loop(){

    for (int s = 0; s< MAXSERVOS; s++) {
		// here you must program your adquisition data system
		//
		posiciones[s]= random (255) ;
		//
		myBoard.setServoPos (s,posiciones[s] ;
    }    

    for (int s = 0; s< MAXSERVOS; s++) {
          if (millis() - lastSignal[s] >= refreshTime){
            myBoard.moveServo(s) ;
            Serial.print (s);
            Serial.print ("::");
            Serial.println (myBoard.getServoPos(s) ) ;
            lastSignal[s] = millis();
            myBoard.read();
          }  
    }  
  
 
}



