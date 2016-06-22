//We always have to include the library
#include "LedControl.h"
#include <MD_DS1307.h>
#include <Wire.h>
#include <Time.h>

/*
 Now we need a LedControl to work with.
 ***** These pin numbers will probably not work with your hardware *****
 pin 12 is connected to the DataIn 
 pin 11 is connected to the CLK 
 pin 10 is connected to LOAD 
 We have only a single MAX72XX.
 */

#define MAX_DEVICES 4

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

  Serial.begin(9600);
  Serial.println("[MD_DDS1307_Example]");
  
//  usage();
  Serial.println();
  Serial.println(__DATE__);
  Serial.println(__TIME__);
  sscanf(__TIME__, "%d:%d:%d", &RTC.h, &RTC.m, &RTC.s);
  //sscanf(__DATE__, 
  if (0==1)
  {
  RTC.yyyy = 2015;
  RTC.mm = 10;
  RTC.dd = 26;
  RTC.writeTime();
  }
}

  /* here is the data for the characters */
  byte   S[5]={  B00000000,   B00001110,   B10010001,   B10010001,   B01100010};
  byte   P[5]={  B00000000,   B01100000,   B10010000,   B10010000,   B11111111};
  byte   M[5]={  B00000000,   B11111111,   B01000000,   B01000000,   B11111111};
  byte   V[5]={  B00000000,   B11110000,   B00001100,   B00000011,   B11110000};
  byte  d0[5]={  B00000000,   B01111110,   B10000001,   B10000001,   B01111110};
  byte  d1[5]={  B00000000,   B00000000,   B11111111,   B01000000,   B00000000};
  byte  d2[5]={  B00000000,   B01100011,   B10010001,   B10001001,   B01000111};
  byte  d3[5]={  B00000000,   B01101110,   B10010001,   B10010001,   B01000010};
  byte  d4[5]={  B00000000,   B00001000,   B11111111,   B00101000,   B00011000};
  byte  d5[5]={  B00000000,   B10001110,   B10010001,   B10010001,   B11110010};
  byte  d6[5]={  B00000000,   B01001110,   B10010001,   B10010001,   B01111110};
  byte  d7[5]={  B00000000,   B11000000,   B10110000,   B10001111,   B10000000};
  byte  d8[5]={  B00000000,   B01101110,   B10010001,   B10010001,   B01101110};
  byte  d9[5]={  B00000000,   B01111110,   B10010001,   B10010001,   B01100010};
  byte cls[5]={  B00000000,   B00000000,   B00000000,   B00000000,   B00000000};
  byte col[5]={  B00000000,   B00100100,   B00100100,   B00000000,   B00000000};
 
  int w = 5;
  int l = 0*4;
  const int N = 9;
  byte binClock[N] = {0, 0, 0, 0, 0, 0, 0, 0};
  byte *tab[N] = {col, col, col, col, col, col, col, col, cls};
  byte *dig[10] = {d0, d1, d2, d3, d4, d5, d6, d7,  d8, d9};
  const int bmpWidth = 39;
  byte bmp[bmpWidth];
  
void putChar(byte x, int nCols, byte *chr)
{
  byte xcol;
  for(byte i = 0; i < nCols; i++)
  {
    xcol = nCols - i - 1;
    if (x + i < bmpWidth)
    {
       bmp[x + i] = chr[xcol];
    }
  }
}

/*
 This method will display the characters for the
 word "Arduino" one after the other on the matrix. 
 (you need at least 5x7 leds to see the whole chars)
 */
void showTime() 
{
  for(int s = 0; s < bmpWidth; s++)
  {
      for(int col = 0; col < 8 * MAX_DEVICES; col++)
      {
         lc.setColumn(col / 8, col % 8, bmp[(s+col) % bmpWidth]);
      }   
    delay(250);
    l++;
    int x = 0;

  RTC.readTime();
  putChar(x, w, dig[RTC.h / 10]);
  x += w;
  putChar(x, w, dig[RTC.h % 10]);
  x += w;

  putChar(x, 2, col);
  x += 2;

  putChar(x, w, dig[RTC.m / 10]);
  x += w;
  putChar(x, w, dig[RTC.m % 10]);
  x += w;

  putChar(x, 2, col);
  x += 2;

  putChar(x, w, dig[RTC.s / 10]);
  x += w;
  putChar(x, w, dig[RTC.s % 10]);
  x += w;
  putChar(x, 3, cls);
  }
}

void writeBinClock() 
{
   for(int col = 0; col < 8; col++)
   {
     lc.setColumn(0,col, binClock[col]);
   }   
   delay(200);
  RTC.readTime();
  binClock[0] = RTC.h / 10;
  binClock[1] = RTC.h % 10;

  binClock[3] = RTC.m / 10;
  binClock[4] = RTC.m % 10;

  binClock[6] = RTC.s / 10;
  binClock[7] = RTC.s % 10;
  
}

time_t tm;

void p2dig(uint8_t v, uint8_t mode)
// print 2 digits leading zero
{
  uint8_t n = 0;

  switch(mode)
  {
    case HEX: n = 16;  break;
    case DEC: n = 10;  break;
  }

  if (v < n) Serial.print("0");
  Serial.print(v, mode);
  
  return;
}

void printTime()
{
  Serial.print(RTC.yyyy, DEC);
  Serial.print("-");
  p2dig(RTC.mm, DEC);
  Serial.print("-");
  p2dig(RTC.dd, DEC);
  Serial.print(" ");
  p2dig(RTC.h, DEC);
  Serial.print(":");
  p2dig(RTC.m, DEC);
  Serial.print(":");
  p2dig(RTC.s, DEC);
  if (RTC.status(DS1307_12H) == DS1307_ON)
    Serial.print(RTC.pm ? " pm" : " am");
//  Serial.println(dow2String(RTC.dow));
Serial.println();
}

void loop() { 
  showTime();
//  writeBinClock();
  Serial.print("TIME: ");
  printTime();

}
