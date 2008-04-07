// Original code is from Chad Phillips: http://www.windmeadow.com/node/42
// white to the Arduino's ground, 
// red to 5 volt+, 
// green to analog pin 4, 
// yellow to analog pin 5. 
//
//
//
// I have loose the references and names of contributors to this code
// I just convert it to library
// March 2008. alonso brain
//

#include <Nunchuck.h>
#include <Wire.h>


Nunchuck::Nunchuck(int myAddr)
{
  _addr = myAddr;
  
}

void Nunchuck::init()
{
  Wire.beginTransmission (_addr); // transmit to device 0x52
  Wire.send (0x40); // sends memory address
  Wire.send (0x00); // sends sent a zero.
  Wire.endTransmission (); // stop transmitting
  int cnt = 0 ;
  while (Wire.available ()){
    outbuf[cnt] = decodeByte (Wire.receive ()); // receive byte as an integer
    cnt++;
  }
  
}

void Nunchuck::write()
{
}


// Print the input data we have recieved
// accel data is 10 bits long
// We only send the 8 most significant bits
// If need the 10 bits int, you could write this:
// int accel_x_axis = outbuf[2] <<4;
// if ((outbuf[5] >> 2) & 1)
// accel_x_axis += 2;
// if ((outbuf[5] >> 3) & 1)
// accel_x_axis += 1;
// but be careful that the serial only send
// the 8 least significant bits of an int

void Nunchuck::read()
{
  int cnt = 0 ;
  Wire.requestFrom (_addr, 6); // request data from nunchuck
  while (Wire.available ())
  {
    outbuf[cnt] = decodeByte (Wire.receive ()); // receive byte as an integer
    cnt++;
  }
  

  _joy_x_axis = joy_x_axis;
  _joy_y_axis = joy_y_axis;
  _accel_x_axis = _accel_x_axis;
  _accel_y_axis = _accel_y_axis;
  _accel_z_axis = _accel_z_axis;

  _z_button = z_button;
  _c_button = c_button;
  
  joy_x_axis = outbuf[0];
  joy_y_axis = outbuf[1];
  accel_x_axis = outbuf[2] <<2;
  accel_y_axis = outbuf[3] <<2;
  accel_z_axis = outbuf[4] <<2;

  z_button = 0;
  c_button = 0;

// byte outbuf[5] contains bits for z and c buttons
  if ((outbuf[5] >> 0) & 1) z_button = 1;
  if ((outbuf[5] >> 1) & 1) c_button = 1;
  if ((outbuf[5] >> 0) & 1) z_button = 1;
  if ((outbuf[5] >> 1) & 1) c_button = 1;
  if ((outbuf[5] >> 2) & 1) accel_x_axis += 2;
  if ((outbuf[5] >> 3) & 1) accel_x_axis += 1;
  if ((outbuf[5] >> 4) & 1) accel_y_axis += 2;
  if ((outbuf[5] >> 5) & 1) accel_y_axis += 1;
  if ((outbuf[5] >> 6) & 1) accel_z_axis += 2;
  if ((outbuf[5] >> 7) & 1) accel_z_axis += 1;

  enviar = 0 ;
  if (joy_x_axis != _joy_x_axis) enviar = 1 ;
  if (joy_y_axis != _joy_y_axis) enviar = 1 ;
  if (accel_x_axis != _accel_x_axis) enviar = 1 ;
  if (accel_y_axis != _accel_y_axis) enviar = 1 ;
  if (accel_z_axis != _accel_z_axis) enviar = 1 ;
  if (z_button != _z_button) enviar = 1 ;
  if (c_button != _c_button) enviar = 1 ;
  
}

void Nunchuck::sendZero()
{
  Wire.beginTransmission (_addr); // transmit to device 0x52
  Wire.send (0x00); // sends one byte
  Wire.endTransmission (); // stop transmitting
}

char Nunchuck::decodeByte (char x)
{
  x = (x ^ 0x17) + 0x17;
  return x;
}

