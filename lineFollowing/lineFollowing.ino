/*******************************************
 Sparki Line-following example
 
 Threshold is the value that helps you 
 determine what's black and white. Sparki's 
 infrared reflectance sensors indicate white 
 as close to 900, and black as around 200.
 This example uses a threshold of 500 for 
 the example, but if you have a narrow line, 
 or perhaps a lighter black, you may need to 
 adjust.
********************************************/

#include <Sparki.h> // include the sparki library

#define FINDOBJECT 1
#define GRABOBJECT 2
#define SPIN 3
#define FOLLOWLINE 4 

const int gripTime = 1200;
const int objectDistance = 3;
const int threshold = 500;

int ping = 0;

bool  lineLeft = false,
      lineCenter = false,
      lineRight = false;
      
void setup() 
{
  sparki.gripperOpen();
}

void gripObject()
{
  sparki.moveStop();
  //state = 2;
  sparki.gripperClose();
  delay(gripTime);
  sparki.gripperStop();
}

void readSensors()
{
  //each sensor is 1 if reading white, and 0 if reading black:
  lineLeft =  sparki.lineLeft() > threshold;
  lineCenter = sparki.lineCenter() > threshold;
  lineRight =  sparki.lineRight() > threshold;
  ping = sparki.ping();
}

sparki.gripperOpen();

void loop() {
 // int threshold = 500;
  
  int lineLeft   = sparki.lineLeft();   // measure the left IR sensor
  int lineCenter = sparki.lineCenter(); // measure the center IR sensor
  int lineRight  = sparki.lineRight();  // measure the right IR sensor

  readSensors();
  
  if(ping <= 1)
  {
    gripObject();
    while(true);
  }
  
  if(ping <= 12)
  {
    sparki.moveForward();
   
  }

  if ( lineLeft < threshold ) // if line is below left line sensor
  {  
    sparki.moveLeft(); // turn left
  }

  if ( lineRight < threshold ) // if line is below right line sensor
  {  
    sparki.moveRight(); // turn right
  }

  // if the center line sensor is the only one reading a line
  if ( (lineCenter < threshold) && (lineLeft > threshold) && (lineRight > threshold) )
  {
    sparki.moveForward(); // move forward
  }  

  sparki.clearLCD(); // wipe the screen
  
  sparki.print("Line Left: "); // show left line sensor on screen
  sparki.println(lineLeft);
  
  sparki.print("Line Center: "); // show center line sensor on screen
  sparki.println(lineCenter);
  
  sparki.print("Line Right: "); // show right line sensor on screen
  sparki.println(lineRight);
  
  sparki.updateLCD(); // display all of the information written to the screen

  delay(100); // wait 0.1 seconds
}
