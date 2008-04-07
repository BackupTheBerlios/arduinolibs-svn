#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <inttypes.h>
#include <I2C_SRF08n.h>
#include <Wire.h>


I2C_SRF08n::I2C_SRF08n() : _addr(0xFF),distancia(0),validate(0),readable(0)
{}


void I2C_SRF08n::setAddr(int myAddr)
{
	_addr = myAddr;
}

void I2C_SRF08n::init()
{
	validate = 0 ;
	readable = 0 ;
	Wire.beginTransmission(_addr); 
	// sets register pointer to the command register (0x00)  
	Wire.send(0x00);             

	// command sensor to measure in "inches" (0x50) 
    // use 0x51 for centimeters
    // use 0x52 for ping microseconds
	Wire.send(0x51);
	Wire.endTransmission();      // stop transmitting
}



void I2C_SRF08n::read()
{
	int numBytes = 2 ;
	char reading = 0xFF;
	validate = 0 ;
	Wire.beginTransmission(_addr); 
	Wire.send(0X02);              // sends one byte  
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




int I2C_SRF08n::getDistance()
{
	return distancia ;
} 

int I2C_SRF08n::getReadable()
{
	return readable ;
} 

void I2C_SRF08n::setReadable(int s)
{
	readable = s ;
} 


void I2C_SRF08n::changeAddress(unsigned char oldAddress, unsigned char newAddress)
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
  _addr = newAddress ;
}


