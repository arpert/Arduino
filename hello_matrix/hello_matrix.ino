#include <Sprite.h>
#include <Matrix.h>

// Hello Matrix
// by Nicholas Zambetti <http://www.zambetti.com>

// Demonstrates the use of the Matrix library
// For MAX7219 LED Matrix Controllers
// Blinks welcoming face on screen

// Created 13 February 2006

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

void setup()
{
  myMatrix.setBrightness(0);
}
int i = 0;
void loop()
{
  myMatrix.clear(); // clear display
  myMatrix.write(0, i, HIGH);
  myMatrix.write(7, 7-i, HIGH);
  i = (i + 1) % 8;
  delay(500);

  // turn some pixels on
  myMatrix.write(1, 5, HIGH);
  myMatrix.write(2, 2, HIGH);
  myMatrix.write(2, 6, HIGH);
  myMatrix.write(3, 6, HIGH);
  myMatrix.write(4, 6, HIGH);
  myMatrix.write(5, 2, HIGH);
  myMatrix.write(5, 6, HIGH);
  myMatrix.write(6, 5, HIGH);
  //myMatrix.
  delay(500);
}

