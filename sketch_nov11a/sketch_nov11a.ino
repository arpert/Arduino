
union conv
{
  byte bajty[6];
  struct Finder
  {
    unsigned int b2;
    unsigned long b4;
  } finder;
};

conv tablica[800];

conv kod;

void setup() {
  // put your setup code here, to run once:
   kod.bajty[0] = 1;
   kod.bajty[1] = 1;
   kod.bajty[2] = 1;
   kod.bajty[3] = 1;
   kod.bajty[4] = 1;
   kod.bajty[5] = 1;

   kod.finder.b2 = kod.finder.b4 >> 16;
   
}

void loop() {
  // put your main code here, to run repeatedly:
  kod.finder.b4 = kod.bajty[2];
}
