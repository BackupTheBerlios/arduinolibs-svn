#ifndef Nunchuck_h
#define Nunchuck_h
#include <inttypes.h>

class Nunchuck
{
  public:
	Nunchuck(int myAddr);
    void init();
    void read();
    void write();
    void sendZero();
	char decodeByte (char x);
    int _addr;
	int joy_x_axis ;
	int joy_y_axis ;
	int accel_x_axis;
	int accel_y_axis;
	int accel_z_axis;
	int z_button;
	int c_button;
	int enviar;
  private:
	int outbuf[6]; // array to store arduino output
	int _joy_x_axis ;
	int _joy_y_axis ;
	int _accel_x_axis;
	int _accel_y_axis;
	int _accel_z_axis;
	int _z_button;
	int _c_button;
	
};

#endif

