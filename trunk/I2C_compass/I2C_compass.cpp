#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <inttypes.h>
#include <I2C_compass.h>
#include <Wire.h>



I2C_compass::I2C_compass(int myAddr)
{
	_addr = myAddr;
	initialized = 0 ;
}

void I2C_compass::init()
{
	direccion = 0 ;
	validate = 0 ;
	initialized = 1 ;
	version = -1 ;
}


/*
void I2C_compass::read1()
{
    if (initialized == 1) {
	  	int registro = 2 ;
  		int numBytes = 2 ;
		char reading = 0xFF;
 	 	Wire.beginTransmission(_addr); 
 	 	Wire.send(registro);              // sends one byte  
 	 	Wire.endTransmission();    // stop transmitting
  	
 	 	Wire.requestFrom(_addr, numBytes);
 	 	if(Wire.available() >=numBytes)    // if two bytes were received
 	 	{
  			reading = Wire.receive();  // receive high byte (overwrites previous reading)
  			reading = reading << 8;    // shift high byte to be high 8 bits
 	 		reading |= Wire.receive(); // receive low byte as lower 8 bits
  			validate = 1 ;
  		}
	  	direccion = reading ;
    }
}
*/

void I2C_compass::read()
{
    if (initialized == 1) {
	  	int registro = 0 ;
  		int numBytes = 4 ;
		char reading = 0xFF;
 	 	Wire.beginTransmission(_addr); 
 	 	Wire.send(registro);              // sends one byte  
 	 	Wire.endTransmission();    // stop transmitting
  	
 	 	Wire.requestFrom(_addr, numBytes);
 	 	if(Wire.available() >=numBytes)    // if two bytes were received
 	 	{
  			version = Wire.receive();  // receive high byte (overwrites previous reading)
  			reading = Wire.receive();  // receive high byte (overwrites previous reading)
			direccion1byte = reading ;
//			direccion1byte = (int)(reading * 360 /255) ;
  			dirH = Wire.receive();  // receive high byte (overwrites previous reading)
  			reading = dirH << 8;    // shift high byte to be high 8 bits
  			dirL = Wire.receive();  // receive high byte (overwrites previous reading)
 	 		reading |= dirL; // receive low byte as lower 8 bits
  			validate = 1 ;
  		}
	  	direccion = reading ;
    }
}

void I2C_compass::checkVersion()
{
    if (initialized == 1) {
	  	int registro = 0 ;
  		int numBytes = 1 ;
		char reading = 0xFF;
 	 	Wire.beginTransmission(_addr); 
 	 	Wire.send(registro);              // sends one byte  
 	 	Wire.endTransmission();    // stop transmitting
  	
 	 	Wire.requestFrom(_addr, numBytes);
 	 	if(Wire.available() >=numBytes)    // if two bytes were received
 	 	{
  			reading = Wire.receive();  // receive high byte (overwrites previous reading)
  		}
	  	version = reading ;
    }
}



void I2C_compass::calibrate()
{
  Wire.beginTransmission (_addr); 
  Wire.send (15); // sends memory address
  Wire.send (0xFF); // sends sent a zero.
  Wire.endTransmission (); // stop transmitting
}


int I2C_compass::getBearing()
{
	return direccion ;
} 

int I2C_compass::getBearingL()
{
	return dirL ;
} 

int I2C_compass::getBearingH()
{
	return dirH ;
} 

int I2C_compass::getBearingByte()
{
	return direccion1byte ;
} 


int I2C_compass::getVersion()
{
	return version ;
} 

