
const int AVGN = 40; // współczynnik uśredniania
const int SENSN = 4; // liczba sensorów

int mes[SENSN][AVGN];
float avgv[SENSN];

int getSensor(int sensnr) // zwraca wartość pomiaru z czujnika nr sensnr 
{
  return random(255);
}

void setup() {
  // put your setup code here, to run once:
  for(int i = 0; i < AVGN; i++)
  {
    for(int j = 0; j < SENSN; j++)
    {
      mes[j][i] = 0;
    }
  }

    for(int j = 0; j < SENSN; j++)
    {
      avgv[j] = 0.0;
    }
}

int curmes = 0;

void calcAvg()
{
  for(int i = 0; i < SENSN; i++)
  {
    avgv[i] = 0;
  }

  for(int j = 0; j < AVGN; j++)
  {
    for(int i = 0; i < SENSN; i++)
    {
      avgv[i] += mes[i][j];
    }
  }

  for(int i = 0; i < SENSN; i++)
  {
    avgv[i] /= AVGN;
  }
}

void loop() {
  // odczytaj czujniki
  for(int i = 0; i < SENSN; i++)
  {
    mes[i][curmes] = getSensor(i);
  }

  // metoda 1
//  calcAvg(); // proste i kosztowne

  // metoda 2 - nie trzeba skanować za każdym raem bufora
  for(int i = 0; i < SENSN; i++)
  {
    avgv[i] = ((avgv[i] * AVGN) - mes[i][(curmes - 1 + AVGN) % AVGN] + mes[i][curmes]) / AVGN;
  }
  
//  display(); // TODO - wyświetlanie wyniku
  curmes = (curmes + 1) % AVGN;
}
