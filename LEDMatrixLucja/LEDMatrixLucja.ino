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
void writeSprites() {
  /* here is the data for the characters */
byte sprites[][9] = {
        {0x07, 0x00, 0x20, 0x10, 0xAE, 0x7E, 0xAE, 0x10, 0x20},  // Code for char
        {0x07, 0x00, 0x20, 0x20, 0xAE, 0x7E, 0xAE, 0x20, 0x20},  // Code for char 
        {0x07, 0x00, 0x20, 0x40, 0xAE, 0x7E, 0xAE, 0x40, 0x20},  // Code for char 
        {0x08, 0x88, 0x50, 0x20, 0xF8, 0x24, 0x70, 0x70, 0x70},  // Code for char 
        {0x07, 0x00, 0xF0, 0x09, 0xEA, 0xFC, 0xEA, 0x09, 0xF0},  // Code for char 
        {0x06, 0x00, 0x00, 0x00, 0x90, 0xAE, 0xFE, 0xAE, 0x90},  // Code for char 
        {0x06, 0x00, 0x00, 0x00, 0x20, 0x17, 0xFF, 0x57, 0x48},  // Code for char 
        {0x08, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA},  // Code for char 
        {0x08, 0x38, 0x44, 0x93, 0x80, 0x80, 0x93, 0x44, 0x38},  // Code for char 
        {0x07, 0x00, 0x82, 0x7C, 0xC7, 0x10, 0xC7, 0x7C, 0x82},  // Code for char   
        {0x08, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF},  // Code for char 
        {0x08, 0x81, 0x42, 0x24, 0x18, 0x18, 0x24, 0x42, 0x81},  // Code for char 
        {0x08, 0x81, 0x42, 0x3C, 0x3C, 0x3C, 0x3C, 0x42, 0x81},  // Code for char 
        {0x08, 0x81, 0x7E, 0x7E, 0x7E, 0x7E, 0x7E, 0x7E, 0x81},  // Code for char 
        {0x08, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x05, 0x07},  // Code for char 
        {0x08, 0x1C, 0x14, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04}   // Code for char 
        };

byte sprite[][9] = {
        {0x07, 0x04, 0x88, 0x57, 0x3F, 0x57, 0x88, 0x04, 0x00},  // Code for char
        {0x07, 0x08, 0x90, 0x57, 0x3F, 0x57, 0x90, 0x08, 0x00},  // Code for char 
        {0x07, 0x10, 0x90, 0x57, 0x3F, 0x57, 0x90, 0x10, 0x00},  // Code for char 
        {0x07, 0x20, 0x90, 0x57, 0x3F, 0x57, 0x90, 0x20, 0x00},  // Code for char 
        {0x07, 0x40, 0xA0, 0x57, 0x3F, 0x57, 0xA0, 0x40, 0x00},  // Code for char 
        {0x07, 0x20, 0x90, 0x57, 0x3F, 0x57, 0x90, 0x20, 0x00},  // Code for char 
        {0x07, 0x10, 0x90, 0x57, 0x3F, 0x57, 0x90, 0x10, 0x00},  // Code for char 
        {0x07, 0x08, 0x90, 0x57, 0x3F, 0x57, 0x90, 0x08, 0x00}  // Code for char 
     };
                
  for(int l = 0; l < 8; l++)
  {
     for(int col = 1; col < 9; col++)
     {
        lc.setColumn(0,col-1,sprite[l][col]);
     }   
  delay(50);
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
  writeSprites();
//  rows();
//  columns();
//  single();
}
