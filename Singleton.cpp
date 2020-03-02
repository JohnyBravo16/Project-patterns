#include <iostream>

using namespace std;

class Singleton
{
 private:
    static Singleton* inst;
    //prywatny konstruktor zeby zapobiec instancjonowaniu
    Singleton();
 public:
    static Singleton* getInstance();
    static void wypisz()
    {
        cout<<"Tekst..";
    }
};

Singleton* Singleton::inst = 0;

Singleton* Singleton::getInstance()
{
    if (inst == 0)
    {
        inst = new Singleton();
    }
    
    return inst;
}

Singleton::Singleton()
{
    cout<<"Konstruktor..";
}


int main() {

    Singleton* s1 = Singleton::getInstance();
    Singleton* s2 = Singleton::getInstance();

    return 0;
}