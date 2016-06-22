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
#define  MAX_DEVICES 4

#define CLK_PIN   13  
#define DATA_PIN  11  
#define CS_PIN    10  

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

Sprite Digits[] = {
Sprite( 7, 8, // 0
  B0111110,
  B1100011,
  B1100011,
  B1100011,
  B1100011,
  B1100011,
  B1100011,
  B0111110  
  ),
Sprite( 7, 8, // 1
  B0000100,
  B0001100,
  B0011100,
  B0001100,
  B0001100,
  B0001100,
  B0001100,
  B0111111  
  ),
Sprite(  7, 8, // 2
  B0111110,
  B1100011,
  B0000011,
  B0000110,
  B0001100,
  B0011000,
  B0110000,
  B1111111  
  ),
Sprite(  7, 8, // 3
  B0111110,
  B1100011,
  B0000011,
  B0001110,
  B0000011,
  B0000011,
  B1100011,
  B0111110  
  ),
Sprite(  7, 8, // 4
  B0001100,
  B0011100,
  B0111100,
  B1101100,
  B1111111,
  B0001100,
  B0001100,
  B0011110  
  ),
Sprite(  7, 8, // 5
  B1111111,
  B1100000,
  B1100000,
  B1111110,
  B0000011,
  B0000011,
  B1100011,
  B0111110  
  ),
Sprite(  7, 8, // 6
  B0111110,
  B1100011,
  B1100000,
  B1111110,
  B1100011,
  B1100011,
  B1100011,
  B0111110  
  ),
Sprite(  7, 8, //7
  B1111111,
  B0000011,
  B0000110,
  B0001100,
  B0001100,
  B0011000,
  B0011000,
  B0011000  
  ),
Sprite(  7, 8, // 8
  B0111110,
  B1100011,
  B1100011,
  B0111110,
  B1100011,
  B1100011,
  B1100011,
  B0111110  
  ),
Sprite(  7, 8, // 9
  B0111110,
  B1100011,
  B1100011,
  B1100011,
  B0111111,
  B0000011,
  B1100011,
  B0111110  
  )
};

Sprite Dig6[] = {
Sprite( 6, 8, // 0
  B011110,
  B110011,
  B110011,
  B110011,
  B110011,
  B110011,
  B110011,
  B011110  
  ),
Sprite( 6, 8, // 1
  B000100,
  B001100,
  B011100,
  B001100,
  B001100,
  B001100,
  B001100,
  B001100  
  ),
Sprite(  6, 8, // 2
  B011110,
  B110011,
  B000011,
  B000110,
  B001100,
  B011000,
  B110000,
  B111111  
  ),
Sprite(  6, 8, // 3
  B011110,
  B110011,
  B000011,
  B000110,
  B000011,
  B000011,
  B110011,
  B011110  
  ),
Sprite(  6, 8, // 4
  B000110,
  B001110,
  B010110,
  B010110,
  B100110,
  B111111,
  B000110,
  B000110  
  ),
Sprite(  6, 8, // 5
  B111111,
  B110000,
  B110000,
  B111110,
  B000011,
  B000011,
  B110011,
  B011110  
  ),
Sprite(  6, 8, // 6
  B011110,
  B110011,
  B110000,
  B111110,
  B110011,
  B110011,
  B110011,
  B011110  
  ),
Sprite(  6, 8, //7
  B011111,
  B000011,
  B000011,
  B000110,
  B000110,
  B001100,
  B001100,
  B001100  
  ),
Sprite(  6, 8, // 8
  B011110,
  B110011,
  B110011,
  B011110,
  B110011,
  B110011,
  B110011,
  B011110  
  ),
Sprite(  6, 8, // 9
  B011110,
  B110011,
  B110011,
  B110011,
  B011111,
  B000011,
  B110011,
  B011110  
  )
};

Sprite Dig5[] = 
{
Sprite(  5, 8, 
  // @0 '0' (5 pixels wide)
  B01110, //  ### 
  B10001, // #   #
  B10001, // #   #
  B10001, // #   #
  B10001, // #   #
  B10001, // #   #
  B10001, // #   #
  B01110  //  ###
),
Sprite(  5, 8, 
  // @9 '1' (3 pixels wide)
  B00100, //   #
  B11100, // ###
  B00100, //   #
  B00100, //   #
  B00100, //   #
  B00100, //   #
  B00100, //   #
  B00100  //   #
),
Sprite(  5, 8, 
  // @18 '2' (5 pixels wide)
  B01110, //  ### 
  B10001, // #   #
  B00001, //     #
  B00010, //    # 
  B00100, //   #  
  B01000, //  #   
  B10000, // #    
  B11111 // #####
),
Sprite(  5, 8, 
  // @27 '3' (5 pixels wide)
  B01110, //  ### 
  B10001, // #   #
  B00001, //     #
  B00110, //   ## 
  B00001, //     #
  B00001, //     #
  B10001, // #   #
  B01110  //  ### 
),
Sprite(  5, 8, 
  // @36 '4' (5 pixels wide)
  B00010, //    # 
  B00110, //   ## 
  B01010, //  # # 
  B01010, //  # # 
  B10010, // #  # 
  B11111, // #####
  B00010, //    # 
  B00010  //    # 
),
Sprite(  5, 8, 
  // @45 '5' (5 pixels wide)
  B11111, // #####
  B10000, // #    
  B10000, // #    
  B11110, // #### 
  B00001, //     #
  B00001, //     #
  B10001, // #   #
  B01110  //  ### 
),
Sprite(  5, 8, 
  // @54 '6' (5 pixels wide)
  B01110, //  ### 
  B10001, // #   #
  B10000, // #    
  B11110, // #### 
  B10001, // #   #
  B10001, // #   #
  B10001, // #   #
  B01110  //  ### 
),
Sprite(  5, 8, 
  // @63 '7' (5 pixels wide)
  B11111, // #####
  B00001, //     #
  B00010, //    # 
  B00100, //   #  
  B00100, //   #  
  B01000, //  #   
  B01000, //  #   
  B01000  //  #   
),
Sprite(  5, 8, 
  // @72 '8' (5 pixels wide)
  B01110, //  ### 
  B10001, // #   #
  B10001, // #   #
  B01110, //  ### 
  B10001, // #   #
  B10001, // #   #
  B10001, // #   #
  B01110  //  ### 
),
Sprite(  5, 8, 
  // @81 '9' (5 pixels wide)
  B01110, //  ### 
  B10001, // #   #
  B10001, // #   #
  B10001, // #   #
  B01111, //  ####
  B00001, //     #
  B10001, // #   #
  B01110  //  ### 
)
};
  
void setup()
{ 
  myMatrix.setBrightness(0);
}

void kolon(byte x, bool set)
{
   myMatrix.write(x, 2, set);
   myMatrix.write(x, 3, set);
   myMatrix.write(x, 5, set);
   myMatrix.write(x, 6, set);
   myMatrix.write(x+1, 2, set);
   myMatrix.write(x+1, 3, set);
   myMatrix.write(x+1, 5, set);
   myMatrix.write(x+1, 6, set);
}


int n = 0;
bool b = (1==0);

void loop()
{
//  if (n % 5 == 0)  
  {
    b = !b;
//    n = 0;
//    myMatrix.clear();               // clear the screen for next animation frame
  }
  if ((n/10) % 10 == 6) n += 40;
  if ((n/100) % 100 == 24) n = 0;
  int y = n;
  int N = 10;
  int W = 8;
     
  for(int i = 0; i < MAX_DEVICES; i++)
  {
     if (i < 3 || n >= 1000)
     myMatrix.write( (i>1?2:0) + W * i, 0, Dig6[y % N]);
     y /= N;
  }   
  kolon(15, b);
//  if (b) 
//     myMatrix.write(n % 32, (n/32) % 8, b);
//  else
//     myMatrix.write((n / 8) % 32, n % 8, b);
  delay(1000);
 
  n = (n + 1) % (N*N*N*N);                      // if reached end of animation sequence
}

