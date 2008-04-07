//
// example for compass library
//
// Author: alonso.brain@yahoo.es 
// Date: 07.04.2008
//


#include <I2C_compass.h>


////////////////////////////////////////////////////////////////////////////////
#include <Wire.h>
#include <string.h>
#include <stdio.h>



unsigned long lastUpdateEnviarDatos = 0 ;
unsigned short refreshTimeEnvio = 1000;

unsigned long lastUpdateCompass = 0 ;
unsigned long lastCallCompass;
unsigned short refreshTimeCompass = 80;
I2C_compass myCompass(0x60);






void setup(){
  myCompass.init();
  myCompass.checkVersion();
}




void loop(){

  if (millis() - lastUpdateEnviarDatos >= refreshTimeEnvio){
    enviarDatos = true ;
    lastUpdateEnviarDatos = millis ();
  }  
  
  
  if (millis() - lastUpdateCompass >= refreshTimeCompass){
    myCompass.read();
    lastUpdateCompass = millis() ;
  }


  if (enviarDatos){  
    enviarDatos = false ;
    Serial.print (",C,") ;
    Serial.print (myCompass.getBearingByte());
    Serial.flush();
  }    

}



