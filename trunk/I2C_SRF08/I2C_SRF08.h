#ifndef I2C_SRF08_h
#define I2C_SRF08_h

#include <inttypes.h>


class I2C_SRF08
{
  public:
	I2C_SRF08(int myAddr);	
	void init();
	void read();
	int getDistance();
	int getReadable();
	void setReadable(int s);
	void changeAddress(unsigned char oldAddress, unsigned char newAddress) ;
  private:
	int _addr ;
	int distancia;	
	int validate;
	int readable;
};

#endif


