//We always have to include the library
#include "LedControl.h"

/*
 Now we need a LedControl to work with.
 ***** These pin numbers will probably not work with your hardware *****
 pin 12 is connected to the DataIn 
 pin 11 is connected to the CLK 
 pin 10 is connected to LOAD 
 We have only a single MAX72XX.
 */

#define MAX_DEVICES 1

#define CLK_PIN   10  
#define DATA_PIN  12  
#define CS_PIN    11  
 
LedControl lc=LedControl(DATA_PIN, CLK_PIN, CS_PIN, MAX_DEVICES);

/* we always wait a bit between updates of the display */
unsigned long delaytime=500;

void setup() {
  /*
   The MAX72XX is in power-saving mode on startup,
   we have to do a wakeup call
   */
  lc.shutdown(0,false);
  lc.shutdown(1,false);
  lc.shutdown(2,false);
  lc.shutdown(3,false);
  /* Set the brightness to a medium values */
  lc.setIntensity(0,0);
  lc.setIntensity(1,0);
  lc.setIntensity(2,0);
  lc.setIntensity(3,0);
  /* and clear the display */
  lc.clearDisplay(0);
  lc.clearDisplay(1);
  lc.clearDisplay(2);
  lc.clearDisplay(3);
}

  /* here is the data for the characters */
  byte   S[5]={  B00000000,   B00001110,   B10010001,   B10010001,   B01100010};
  byte   P[5]={  B00000000,   B01100000,   B10010000,   B10010000,   B11111111};
  byte   M[5]={  B00000000,   B11111111,   B01000000,   B01000000,   B11111111};
  byte   V[5]={  B00000000,   B11110000,   B00001100,   B00000011,   B11110000};
  byte  d0[5]={  B00000000,   B01111110,   B10000001,   B10000001,   B01111110};
  byte  d1[5]={  B00000000,   B00000000,   B11111111,   B01000000,   B00000000};
  byte  d2[5]={  B00000000,   B01100011,   B10010001,   B10000101,   B01000011};
  byte  d3[5]={  B00000000,   B01101110,   B10010001,   B10010001,   B01000010};
  byte  d4[5]={  B00000000,   B00001000,   B11111111,   B00101000,   B00011000};
  byte  d5[5]={  B00000000,   B10001110,   B10010001,   B10010001,   B11110010};
  byte  d6[5]={  B00000000,   B01001110,   B10010001,   B10010001,   B01111110};
  byte  d7[5]={  B00000000,   B11000000,   B10110000,   B10001111,   B10000000};
  byte  d8[5]={  B00000000,   B01101110,   B10010001,   B10010001,   B01101110};
  byte  d9[5]={  B00000000,   B01111110,   B10010001,   B10010001,   B01100010};
  byte cls[5]={  B00000000,   B00000000,   B00000000,   B00000000,   B00000000};
  byte col[5]={  B00000000,   B00000000,   B00100100,   B00000000,   B00000000};
 
  int w = 5;
  int l = 0*4;
  const int N = 5;
  byte *tab[N] = {d2, d3, d5, d1, cls};
  byte *dig[10] = {d0, d1, d2, d3, d4, d5, d6, d7,  d8, d9};
/*
 This method will display the characters for the
 word "Arduino" one after the other on the matrix. 
 (you need at least 5x7 leds to see the whole chars)
 */
void writeSp5msv() 
{
  for(int s = 0; s < N*w; s++)
  {
      for(int col = 0; col < 8; col++)
      {
        int ch = (s + col) / (w);
        ch = ch % N;
        lc.setColumn(0,col, tab[ch][(N*w+w+9-col-s)%w]);
      }   
    delay(200);
    l++;
    int x = l / 5; 
    tab[3] = dig[x%10]; x /= 10;
    tab[2] = dig[x%10]; x /= 10;
    tab[1] = dig[x%10]; x /= 10;
    tab[0] = dig[x%10]; //x /= 10;
  }
}

void loop() { 
  writeSp5msv();
}
