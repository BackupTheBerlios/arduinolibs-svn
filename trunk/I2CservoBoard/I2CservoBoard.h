#ifndef I2CservoBoard_h
#define I2CservoBoard_h

#include <inttypes.h>


class I2CservoBoard
{
  public:
	I2CservoBoard(int myAddr,int maxServos);	
	void init();
	void setServoPos (int s, int tpos);
	void moveServo (int s);
	void moveSpeedServo (int s);
	void read();
	int  getServoPos (int s);
  private:
	int _addr ;	
	int _activeServos ;
	int initialized ;
	int* pos ;
	int* oldpos ;
};

#endif

