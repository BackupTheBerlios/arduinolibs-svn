#include <I2C_SRF08n.h>

#include <Wire.h>

unsigned char I2Cdireccion = 0xE4 >> 1 ;
unsigned char  I2Cndir = 0xEE  ;
I2C_SRF08 mySRF(I2Cdireccion) ; 
unsigned long lastUpdate ;
unsigned short refreshTime = 50;
unsigned short refreshSecurityTime = 5000;
unsigned long lastUpdatePrint ;


void setup()
{
  Wire.begin(); // join i2c bus (address optional for master)
  //setup for Serial port
  Serial.begin(115200);
  Serial.print("\tConfigurando I2C...");
  mySRF.changeAddress (I2Cdireccion,I2Cndir) ;
  delay (100);
  mySRF.init();
  delay (100);
}

int count = 0 ; 

void loop()
{
  if (millis() - lastUpdate >= refreshTime){
    mySRF.read();
    lastUpdate = millis() ;
  }
  if (millis() -lastUpdatePrint >= 500){
    Serial.print ("DISTANCIA") ;
    Serial.print (",") ;
    Serial.println (mySRF.getDistance());
    lastUpdatePrint = millis() ;
  }
}
