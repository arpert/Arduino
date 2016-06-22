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

#define PIN_H 2
#define PIN_M 3

byte state_h = 0;
byte state_m = 0;
 
LedControl lc=LedControl(DATA_PIN, CLK_PIN, CS_PIN, MAX_DEVICES);

/* we always wait a bit between updates of the display */
unsigned long delaytime=500;
unsigned scorr = 8; // take back 8 sec every day to coorrect clock
boolean doCorrection = true;

void setupTime()
{
  char cmon[5] = {"****"};
  int imon = -7;
  sscanf(__DATE__, "%3c %2d %4d", &cmon, &RTC.dd, &RTC.yyyy); 
  sscanf(__TIME__, "%2d:%2d:%2d", &RTC.h, &RTC.m, &RTC.s);
  RTC.s = RTC.s > 60 - 7 ? 59 : RTC.s + 7;
  if (strcmp(cmon, "Jan") == 0) imon =  1;  
  if (strcmp(cmon, "Feb") == 0) imon =  2;  
  if (strcmp(cmon, "Mar") == 0) imon =  3;  
  if (strcmp(cmon, "Apr") == 0) imon =  4;  
  if (strcmp(cmon, "May") == 0) imon =  5;  
  if (strcmp(cmon, "Jun") == 0) imon =  6;  
  if (strcmp(cmon, "Jul") == 0) imon =  7;  
  if (strcmp(cmon, "Aug") == 0) imon =  8;  
  if (strcmp(cmon, "Sep") == 0) imon =  9;  
  if (strcmp(cmon, "Oct") == 0) imon = 10;  
  if (strcmp(cmon, "Nov") == 0) imon = 11;  
  if (strcmp(cmon, "Dec") == 0) imon = 12;  
  Serial.println(cmon);
  RTC.mm = imon;
  RTC.writeTime();
}

void setup() {
  pinMode(PIN_H, INPUT_PULLUP);
  pinMode(PIN_M, INPUT_PULLUP);
  
  /*
   The MAX72XX is in power-saving mode on startup,
   we have to do a wakeup call
   */
  for(int i = 0; i < MAX_DEVICES; i++)
  { 
    lc.shutdown(i, false);
    /* Set the brightness to a medium values */
    lc.setIntensity(i,0);
    /* and clear the display */
    lc.clearDisplay(i);
  }
  Serial.begin(9600);
//  Serial.println("[MD_DDS1307_Example]");
  
//  usage();
  RTC.readTime();
  printTime();
  Serial.print("Date & time: ");
  Serial.print(__DATE__);
  Serial.print(" ");
  Serial.println(__TIME__);
  if (digitalRead(2) == LOW)
    setupTime();
  RTC.writeTime();
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
  byte col[2]={  B00000000,   B00100100};
  byte col2[2]={ B00000000,   B01000010};

  byte  dn0[5]={  B00000000,  B00111110,  B01000001,  B00111110};
  byte  dn1[5]={  B00000000,  B00000000,  B01111111,  B00100000};
  byte  dn2[5]={  B00000000,  B00110001,  B01001101,  B00100011};
  byte  dn3[5]={  B00000000,  B00110110,  B01001001,  B00100010};
  byte  dn4[5]={  B00000000,  B01111111,  B00100100,  B00011100};
  byte  dn5[5]={  B00000000,  B01001110,  B01010001,  B01110010};
  byte  dn6[5]={  B00000000,  B00100110,  B01001001,  B00111110};
  byte  dn7[5]={  B00000000,  B01100000,  B01011000,  B01000111};
  byte  dn8[5]={  B00000000,  B00110110,  B01001001,  B00110110};
  byte  dn9[5]={  B00000000,  B00111110,  B01001001,  B00110010};

  int w = 5;
  int l = 0*4;
  const int N = 9;

  byte *dig[10] = {d0, d1, d2, d3, d4, d5, d6, d7,  d8, d9};
  byte *dign[10] = {dn0, dn1, dn2, dn3, dn4, dn5, dn6, dn7,  dn8, dn9};
  const int bmpWidth = 8 * MAX_DEVICES;
  byte bmp[bmpWidth];
  
void putChar(byte x, int nCols, byte *chr)
{
  byte xcol;
  for(byte i = 0; i < nCols; i++)
  {
    xcol = nCols - i - 1;
    //xcol = nCols;
    if (x + i < bmpWidth)
    {
       bmp[x + i] = chr[xcol];
    }
  }
}

void putChar(byte x, int nCols, byte *chr, byte del)
{
  byte xcol;
  for(byte i = 0; i < nCols; i++)
  {
    xcol = nCols - i - 1;
    //xcol = nCols;
    if (x + i < bmpWidth)
    {
       bmp[x + i] = chr[xcol];
    }
  }
}

void showBitmap()
{
   int maxcol = 8 * MAX_DEVICES;
   if (maxcol > bmpWidth) maxcol > bmpWidth;
  
   for(int col = 0; col < maxcol; col++)
   {
      lc.setColumn(MAX_DEVICES-(col / 8)-1, (col % 8), bmp[col]);
   }   
}

void drawTime() 
{
  int x = 0;

  putChar(x, w, dig[RTC.h / 10]);
  x += w;
  putChar(x, w, dig[RTC.h % 10]);
  x += w;

  putChar(x, 2, ((RTC.s % 2) == 0) ? col : col2);
  x += 2;

  putChar(x, w, dig[RTC.m / 10]);
  x += w;
  putChar(x, w, dig[RTC.m % 10]);
  x += w;

  putChar(x, 2, ((RTC.s % 2) == 0) ? col : col2);
  x += 2;

  putChar(x, w-1, dign[RTC.s / 10]);
  x += w-1;
  putChar(x, w-1, dign[RTC.s % 10]);
  x += w-1;
  putChar(x, 3, cls);
}

void drawBinDigits() 
{
   for(int i = 0; i < bmpWidth; i++)
   {
      bmp[i] = i;
   }
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
Serial.println(__DATE__);
}

int prevs = 0;

void loop() 
{ 
  RTC.readTime();
  int s = RTC.s;
  if (prevs != s)
  {
  drawTime();
//  drawBinDigits();
//  writeBinClock();
  showBitmap();
  Serial.print("TIME: ");
  printTime();
  prevs = s;
  }
  if ((23 == RTC.h) && !doCorrection)
     doCorrection = true;
  if ((0 == RTC.h) && (0 == RTC.m) && (scorr + 1 == RTC.s) && doCorrection)
  {
    // correct time
    RTC.s = 1;
    RTC.writeTime();
    doCorrection = false;
  }
  
  if ((digitalRead(PIN_H) != state_h))
  {
    state_h = digitalRead(PIN_H) ? 1 : 0;
    if (state_h == 0)
    {
      RTC.h < 23 ? RTC.h++ : RTC.h = 0;
      RTC.writeTime();
    }
  }

  if ((digitalRead(PIN_M) != state_m))
  {
    state_m = digitalRead(PIN_M) ? 1 : 0;
    if (state_m == 0)
    {
      RTC.m < 59 ? RTC.m++ : RTC.m = 0;
      RTC.writeTime();
    }
  }

  delay(100);
}


