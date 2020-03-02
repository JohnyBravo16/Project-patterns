#include <iostream>

using namespace std;

class Komponent;
class Potwierdzenie;
class DekoratorPotwierdzenia;
class DekoratorNaglowka;
class DekoratorNaglowka2;
class DekoratorStopki;
class DekoratorStopki2;

class Komponent
{
 public:
    virtual void drukuj() = 0;
};

class Potwierdzenie : public Komponent
{
 public:
    void drukuj()
    {
        cout<<"POTWIERDZENIE"<<endl;
    }
};

class DekoratorPotwierdzenia : public Komponent
{
 public:
    virtual void drukuj() = 0;
    DekoratorPotwierdzenia(Komponent* komp);
 private:
    Komponent* mojKomponent;
};

class DekoratorNaglowka : public DekoratorPotwierdzenia
{
 public:
    DekoratorNaglowka(Komponent *komp) : DekoratorPotwierdzenia(komp)
    {

    }
    void drukuj();
};

class DekoratorNaglowka2 : public DekoratorPotwierdzenia
{
 public:
    DekoratorNaglowka2(Komponent *komp) : DekoratorPotwierdzenia(komp)
    {
        
    }
    void drukuj();
};

class DekoratorStopki : public DekoratorPotwierdzenia
{
 public:
    DekoratorStopki(Komponent *komp) : DekoratorPotwierdzenia(komp)
    {
        
    }
    void drukuj();
};

class DekoratorStopki2 : public DekoratorPotwierdzenia
{
 public:
    DekoratorStopki2(Komponent *komp) : DekoratorPotwierdzenia(komp)
    {
        
    }
    void drukuj();
};

DekoratorPotwierdzenia::DekoratorPotwierdzenia(Komponent* komp)
{
    mojKomponent = komp;
}

void DekoratorPotwierdzenia::drukuj()
{
    if(mojKomponent)
    {
        mojKomponent->drukuj();
    }
}

void DekoratorNaglowka::drukuj()
{
    cout<<"NAGLOWEK 1"<<endl;
    DekoratorPotwierdzenia::drukuj();
}

void DekoratorNaglowka2::drukuj()
{
    cout<<"NAGLOWEK 2"<<endl;
    DekoratorPotwierdzenia::drukuj();
}

void DekoratorStopki::drukuj()
{
    DekoratorPotwierdzenia::drukuj();
    cout<<"STOPKA 1"<<endl;
}

void DekoratorStopki2::drukuj()
{
    DekoratorPotwierdzenia::drukuj();
    cout<<"STOPKA 2"<<endl;
}

class Konfiguracja
{
 public:
    Komponent* pobierzPotwierdzenie(string format)
    {
        if(format == "N1PS1S2")
        {
            Komponent *komp = new DekoratorNaglowka(new DekoratorStopki2(new DekoratorStopki(new Potwierdzenie)));
            return komp;
        }

        if(format == "N1N2PS2")
        {
            Komponent *komp = new DekoratorNaglowka(new DekoratorNaglowka2(new DekoratorStopki2(new Potwierdzenie)));
            return komp;
        }
    }
};

int main()
{
    Konfiguracja conf;
    
    Komponent *komp = conf.pobierzPotwierdzenie("N1PS1S2");
    
    komp->drukuj();

    cout<<endl;

    Komponent *komp2 = conf.pobierzPotwierdzenie("N1N2PS2");

    komp2->drukuj();

    return 0;
}