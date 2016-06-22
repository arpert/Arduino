
class A
{
  public:
    virtual void test();  
};

class B : public A
{
  public:
    void test()
  {
    int x = 1;
  }
};

class C : public A
{
  public:
    void test()
  {
    int y = 2;
  }
};

A* tab[2];

void setup() {
  // put your setup code here, to run once:
  tab[0] = new B();
  tab[0] = new C();
}

void loop() {
  // put your main code here, to run repeatedly:
  tab[0]->test();
  tab[2]->test();

}
