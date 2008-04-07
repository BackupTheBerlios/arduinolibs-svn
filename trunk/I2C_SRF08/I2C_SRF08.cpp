#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <inttypes.h>
#include <I2C_SRF08.h>
#include <Wire.h>



I2C_SRF08::I2C_SRF08(int myAddr)
{
	_addr = myAddr;
}

void I2C_SRF08::init()
{
	validate = 0 ;
	readable = 0 ;
	
	Wire.beginTransmission(_addr); 
	// sets register pointer to the command register (0x00)  
	Wire.send(0x00);             
	// command sensor to measure in "inches" (0x50) 
    // use 0x51 for centimeters
    // use 0x52 for ping microseconds
	Wire.send(0x50);
	Wire.endTransmission();      // stop transmitting

	Wire.beginTransmission(_addr); 
	Wire.send(0x02);             
	// 0x00 43mm
	// 0x01 86mm
	// 0x18 1m
	// 0x8C 6m
	// 0xFF 11m
	Wire.send(0x8C);
	Wire.endTransmission();      // stop transmitting

}



void I2C_SRF08::read()
{
	int numBytes = 2 ;
	char reading = 0xFF;
	validate = 0 ;
	Wire.beginTransmission(_addr); 
	Wire.send(0x02);              // sends one byte  
	Wire.endTransmission();    // stop transmitting
	
	Wire.requestFrom(_addr, numBytes);
	if(Wire.available() >=numBytes)    // if two bytes were received
	{
		reading = Wire.receive();  // receive high byte (overwrites previous reading)
		reading = reading << 8;    // shift high byte to be high 8 bits
		reading |= Wire.receive(); // receive low byte as lower 8 bits
		validate = 1 ;
	}
	distancia = reading +1;

}




int I2C_SRF08::getDistance()
{
	return distancia ;
} 

int I2C_SRF08::getReadable()
{
	return readable ;
} 

void I2C_SRF08::setReadable(int s)
{
	readable = s ;
} 


void I2C_SRF08::changeAddress(unsigned char oldAddress, unsigned char newAddress)
{
  Wire.beginTransmission(oldAddress);
  Wire.send(0x00);
  Wire.send(0xA0);
  Wire.endTransmission();

  Wire.beginTransmission(oldAddress);
  Wire.send(0x00);
  Wire.send(0xAA);
  Wire.endTransmission();

  Wire.beginTransmission(oldAddress);
  Wire.send(0x00);
  Wire.send(0xA5);
  Wire.endTransmission();

  Wire.beginTransmission(oldAddress);
  Wire.send(0x00);
  Wire.send(newAddress);
  Wire.endTransmission();
  _addr = newAddress >> 1 ;
}


