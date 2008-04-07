//
// example for SRF08n library
//
// read 3 SRF08 devices 
//
// Author: alonso.brain@yahoo.es 
// Date: 30.03.2008
//

#include <I2C_SRF08n.h>

#include <Wire.h>

#define MAX_SRF  3
unsigned char I2Cdireccion = 0x71 ;
I2C_SRF08n mySRF[3] ; 
unsigned long lastCall[3] ;
unsigned long lastRead[3] ;
unsigned short refreshTime = 1000;
unsigned short refreshSecurityTime = 5000;
unsigned short refreshTimeGlobal = 200;
unsigned long lastUpdatePrint ;
int firstTime[MAX_SRF]  ;


void setup()
{
  Wire.begin(); // join i2c bus (address optional for master)
  //setup for Serial port
  Serial.begin(115200);
  Serial.print("\tConfigurando I2C...");
  
  for (int i=0;i<MAX_SRF;i++){
    firstTime[i] = 1 ;
  }
  
  mySRF[0].setAddr(0x74);
  mySRF[1].setAddr(0x71);
  mySRF[2].setAddr(0x73);
}

int count = 0 ; 
void loop()
{

  for (int i=0;i<MAX_SRF;i++){
    if (millis() - lastCall[i] >= 200){
      if (firstTime[i]==0)
        mySRF[i].read();
      firstTime[i] = 0;  
      mySRF[i].init();
      lastCall[i] = millis() ;
    }
  }  
  if (millis() -lastUpdatePrint >= 500){
    Serial.print ("distance") ;
    for (int i=0;i<MAX_SRF;i++){
      Serial.print (",") ;
      Serial.print (mySRF[i].getDistance());
    }
    Serial.println ("") ;
    lastUpdatePrint = millis() ;
  }

}
