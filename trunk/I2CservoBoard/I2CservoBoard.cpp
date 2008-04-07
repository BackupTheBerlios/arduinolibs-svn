#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <inttypes.h>
#include <I2CservoBoard.h>
#include <Wire.h>



I2CservoBoard::I2CservoBoard(int myAddr,int maxServos)
{
  _addr = myAddr;
  _activeServos = maxServos ;
  int tamano = 6 ;

  pos = (int*) calloc(tamano, sizeof(int));
  oldpos = (int*) calloc(tamano, sizeof(int));


  for (int i = 0; i < tamano; i++){
	pos[i] = 0x7F;
	oldpos[i] = 0x7F;
  }  
  initialized = 0 ;
}

void I2CservoBoard::init()
{
//  overwrite default if needed
	pos[0] = 0x7F;
	pos[1] = 0x7F;
	pos[2] = 0x7F;
	pos[3] = 0x7F;
  	initialized = 1 ;

    for (int s = 0; s<_activeServos; s++) {
		moveServo (s) ;
    }  

}


void I2CservoBoard::setServoPos (int s, int tpos)
{
	int i = s ;
	oldpos[i] = pos[i] ;
	pos[i] = tpos ;
}


void I2CservoBoard::moveServo (int s)
{
	if (initialized == 1){
		if (oldpos[s] != pos[s]){ 
			Wire.beginTransmission(_addr); 
			int regBase = 63 + s ;
			Wire.send(regBase);              // sends one byte  
			Wire.send(pos[s]);             
			Wire.endTransmission();    // stop transmitting
			oldpos[s] = pos[s] ;
		} 
	}
}

void I2CservoBoard::moveSpeedServo (int s)
{
// I2COUT SDA, SD21, Servo1, [Speed, Servo.LOWBYTE, Servo.HIGHBYTE]
	if (initialized == 1){
		if (oldpos[s] != pos[s]){ 
			Wire.beginTransmission(_addr); 
			int regBase = s ;
			Wire.send(regBase);              // sends one byte  
			Wire.send(0x100);              // sends one byte  
			Wire.send(pos[s] & 0xFF);             
			Wire.send(pos[s] >> 8);             
			Wire.endTransmission();    // stop transmitting
			oldpos[s] = pos[s] ;
		} 
	}
}



void I2CservoBoard::read()
{
/*
    Wire.requestFrom(_addr, 65);    // solitica 6 bytes del dispostivo #68 
 
    while(Wire.available())    // slave may send less than requested 
    { 
      char c = Wire.receive(); // receive a byte as character 
    } 
*/    
}


int I2CservoBoard::getServoPos(int s)
{
	return pos[s] ;
}

