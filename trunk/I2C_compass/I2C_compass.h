#ifndef I2C_compass_h
#define I2C_compass_h

#include <inttypes.h>


class I2C_compass
{
  public:
	I2C_compass(int myAddr);	
	void init();
	void read();
	int getBearing();
	int getBearingL();
	int getBearingH();
	int getBearingByte();
	int	getVersion();
	void checkVersion();
	void calibrate();
  private:
	int _addr ;
	int direccion;	
	char direccion1byte;
	char dirH ;
	char dirL ;
	int validate;
	int initialized;
	int version;
};

#endif


