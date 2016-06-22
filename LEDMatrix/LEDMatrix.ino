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

/*
 This method will display the characters for the
 word "Arduino" one after the other on the matrix. 
 (you need at least 5x7 leds to see the whole chars)
 */
void writeArduinoOnMatrix() {
  /* here is the data for the characters */
  byte a[5]={B00111111,B01001000,B01001000,B01001000,B00111111};
  byte r[5]={B00111110,B00010000,B00100000,B00100000,B00010000};
  byte d[5]={B00011100,B00100010,B00100010,B00010010,B11111110};
  byte u[5]={B00111100,B00000010,B00000010,B00000100,B00111110};
  byte i[5]={B00000000,B00100010,B10111110,B00000010,B00000000};
  byte n[5]={B00111110,B00010000,B00100000,B00100000,B00011110};
  byte o[5]={B00011100,B00100010,B00100010,B00100010,B00011100};
  byte cls[5]={B00000000,B00000000,B00000000,B00000000,B00000000};

  byte S[6]={
    B00000000,
    B00001110,
    B10010001,
    B10010001,
    B10010001,
    B01100010};
  byte P[6]={
    B00000000,
    B01100000,
    B10010000,
    B10010000,
    B10010000,
    B11111111};
  byte M[6]={
    B00000000,
    B11111111,
    B01000000,
    B00110000,
    B01000000,
    B11111111};
  byte V[6]={
    B00000000,
    B11110000,
    B00001100,
    B00000011,
    B00001100,
    B11110000};
  byte d5[6]={
    B00000000,
    B10001110,
    B10010001,
    B10010001,
    B10010001,
    B11110010};

  byte *tab[] = {cls, S, P, d5, M, S, V, cls};
  /* now display them one by one with a small delay */
  int w = 6;
  for(int s = 0; s < 2*w; s--)
  {
      for(int col = 0; col < 8; col++)
      {
        int ch = (s + col) / w;
        if (ch > 1)
        ch = 1;
        else ch = 2;
        lc.setRow(0,col, tab[ch][(64+col+s)%w]);
    delay(10);
      }   
    delay(400);
  }
}

/*
  This function lights up a some Leds in a row.
 The pattern will be repeated on every row.
 The pattern will blink along with the row-number.
 row number 4 (index==3) will blink 4 times etc.
 */
void rows() {
  for(int row=0;row<8;row++) {
    delay(delaytime);
    lc.setRow(0,row,B10100000);
    delay(delaytime);
    lc.setRow(0,row,(byte)0);
    for(int i=0;i<row;i++) {
      delay(delaytime);
      lc.setRow(0,row,B10100000);
      delay(delaytime);
      lc.setRow(0,row,(byte)0);
    }
  }
}

/*
  This function lights up a some Leds in a column.
 The pattern will be repeated on every column.
 The pattern will blink along with the column-number.
 column number 4 (index==3) will blink 4 times etc.
 */
void columns() {
  for(int col=0;col<8;col++) {
    delay(delaytime);
    lc.setColumn(0,col,B10100000);
    delay(delaytime);
    lc.setColumn(0,col,(byte)0);
    for(int i=0;i<col;i++) {
      delay(delaytime);
      lc.setColumn(0,col,B10100000);
      delay(delaytime);
      lc.setColumn(0,col,(byte)0);
    }
  }
}

/* 
 This function will light up every Led on the matrix.
 The led will blink along with the row-number.
 row number 4 (index==3) will blink 4 times etc.
 */
void single() {
  for(int row=0;row<8;row++) {
    for(int col=0;col<8;col++) {
      delay(delaytime);
      lc.setLed(0,row,col,true);
      delay(delaytime);
      for(int i=0;i<col;i++) {
        lc.setLed(0,row,col,false);
        delay(delaytime);
        lc.setLed(0,row,col,true);
        delay(delaytime);
      }
    }
  }
}

void loop() { 
  writeArduinoOnMatrix();
//  rows();
//  columns();
//  single();
}
