/*
 *
 * Read the serial com where the arduino running nunchuck2USB.pde is connected
 *
 * \libraries\Nunchuck\examples\nunchuck2USB.pde
 *
 * alonso.brain at yahoo dot es
 */
 
import processing.serial.*;

Serial port;        // The serial port
int thisByte = -1;  // Variable to hold keystoke values
int whichKey = -1;  // Incoming serial data
PFont fontA;        // Font for printing
int lf = 10;    // Linefeed in ASCII
String myString = null;
String inString;  // Input string from serial port: 
int[] serialInArray = new int[32]; // Where we’ll put what we receive
int[] newOrder = new int[32];
int i = 0;
int serialCount = 0; // A count of how many bytes we receive
boolean firstContact = false; // Whether we’ve heard from the microcontroller
int tempIn =0;

String data; //declare variable
int coord[]; // declare array




void setup() {

  size(450, 250);

  // Load and prep fonts to print to window
  fontA = loadFont("CourierNewPSMT-24.vlw");
  textFont(fontA, 12);

  // List all the available serial ports:
  println(Serial.list());

  // I know that the first port in the serial list on my mac
  // is always my  Keyspan adaptor, so I open Serial.list()[0].
  // In Windows, this usually opens COM1.
  // Open whatever port is the one you're using.
  port = new Serial(this, "COM5", 19200);
  
}

void draw() {
  background(0);
  // If there are bytes available in the input buffer,
  // Read them and print them:
  
  while (port.available() > 0) {
    myString = port.readStringUntil(lf);
    if (myString != null) {
      coord = int(split(myString, '\t')); 
      print(myString);
      if (coord.length==7){
          println (coord[0]) ;
          println (coord[1]) ;
      }
            
    }
  }


  stroke(255);
  noFill();
}

 






