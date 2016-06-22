#include <Adafruit_NeoPixel.h>
 
#define PIN 6
#define LICZBADIOD 4
 
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(LICZBADIOD, PIN, NEO_GRB + NEO_KHZ800);

int lvl = 0; 
void setup()
{
  pinMode(13, OUTPUT);
  pixels.begin(); // Inicjalizacja biblioteki
}
 
void loop()
{
//  digitalWrite(13, HIGH);
  delay(50); // Opoznienie 500ms przed zaswieceniem kolejnej diody
  digitalWrite(13, LOW);

  pixels.setPixelColor(random(LICZBADIOD), 
              (32 * random(4)) % 256, 
              (32 * random(4)) % 256, 
              (32 * random(4)) % 256); 
  pixels.show(); // Wysylamy dane do lancucha
  delay(100); // Opoznienie przed zaswieceniem kolejnej diody
}
