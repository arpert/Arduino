#include <Sprite.h>
#include <Matrix.h>

// Sprite Animation
// by Nicholas Zambetti <http://www.zambetti.com>

// Demonstrates the use of the Matrix & Sprite libraries
// Displays animated waveform graphic on screen

// Created 29 March 2006

/* create a new Matrix instance
   pin 0: data  (din)
   pin 1: load  (load)
   pin 2: clock (clk)
*/
#define MAX_DEVICES 1

#define CLK_PIN   10  
#define DATA_PIN  12  
#define CS_PIN    11  

Matrix myMatrix = Matrix(DATA_PIN, CLK_PIN, CS_PIN, MAX_DEVICES);

/* create a new Sprite instance
   8 pixels wide, 4 pixels tall
*/
Sprite wave = Sprite(
  8, 4,
  B00011000,
  B00100100,
  B01000010,
  B10000001
);

void setup()
{ 
  myMatrix.setBrightness(0);
}

int x = 0;

void loop()
{
  myMatrix.write(x-8, 2, wave);     // place sprite on screen
  myMatrix.write(x, 2, wave);     // place sprite on screen
  myMatrix.write(x + 8, 2, wave); // place sprite again, elsewhere on screen
  myMatrix.write(x + 16, 2, wave); // place sprite again, elsewhere on screen
  myMatrix.write(x + 24, 2, wave);     // place sprite on screen
//  myMatrix.write((x + 4) % 8, 0, HIGH);     // dot
//  myMatrix.write((x + 0) % 8, 7, HIGH);     // dot
  delay(75);                      // wait a little bit
  myMatrix.clear();               // clear the screen for next animation frame
  x = (x + 1) % 8;                      // if reached end of animation sequence
}

