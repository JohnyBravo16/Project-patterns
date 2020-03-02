#include <iostream>

using namespace std;

class ApNadzorujaca;
class FabrykaSter;
class SterownikEkranu;
class SterownikDrukarki;
class SterEkrnNisRozdz;
class SterDrukNisRozdz;
class SterEkrnWysRozdz;
class SterDrukWysRozdz;
class SENR;
class SDNR;
class SEWR;
class SDWR;
class Konfiguracja;

class ApNadzorujaca
{
 private:
    FabrykaSter *fab;
 public:
    ApNadzorujaca(FabrykaSter *f);
    void rysujEkran();
    void rysujDrukarka();
};

class SterownikEkranu
{
 public:
    virtual void rysuj() = 0;
};

class SterEkrnNisRozdz : public SterownikEkranu
{
 public:
    SterEkrnNisRozdz();
    void rysuj();
 private:
    SENR* sterEkrn;
};

class SterEkrnWysRozdz : public SterownikEkranu
{
 public:
    SterEkrnWysRozdz();
    void rysuj();
 private:
    SEWR* sterEkrn;
};  

class SterownikDrukarki
{
 public:
    virtual void rysuj() = 0;
};

class SterDrukNisRozdz : public SterownikDrukarki
{
 public:
    SterDrukNisRozdz();
    void rysuj();
 private:
    SDNR* sterDrk;
};

class SterDrukWysRozdz : public SterownikDrukarki
{
 public:
    SterDrukWysRozdz();
    void rysuj();
 private:
    SDWR* sterDrk;
};

class FabrykaSter
{
 public:
    virtual SterownikEkranu* pobierzSterEkrn() = 0;
    virtual SterownikDrukarki* pobierzSterDruk() = 0;
};

class FabrykaNisRozdz : public FabrykaSter
{
 public:
    SterownikEkranu* pobierzSterEkrn();
    SterownikDrukarki* pobierzSterDruk();
};

class FabrykaWysRozdz : public FabrykaSter
{
 public:
    SterownikEkranu* pobierzSterEkrn();
    SterownikDrukarki* pobierzSterDruk();
};

class SENR : public SterownikEkranu
{
 public:
    SENR()
    {

    }
    void rysuj()
    {
        cout<<"Rysuje figure sterownikiem ekranu niskiej rozdzielczosci";
    }
};

class SDNR : public SterownikDrukarki
{
 public:
    SDNR()
    {

    }
    void rysuj()
    {
        cout<<"Rysuje figure sterownikiem drukarki niskiej rozdzielczosci";
    }
};

class SEWR : public SterownikEkranu
{
 public:
    SEWR()
    {

    }
    void rysuj()
    {
        cout<<"Rysuje figure sterownikiem ekranu wysokiej rozdzielczosci";
    }
};

class SDWR : public SterownikDrukarki
{
 public:
    SDWR()
    {

    }
    void rysuj()
    {
        cout<<"Rysuje figure sterownikiem drukarki wysokiej rozdzielczosci";
    }
};

//Konstruktory i metody klas sterownikow
SterEkrnNisRozdz::SterEkrnNisRozdz()
{
    sterEkrn = new SENR;
}

void SterEkrnNisRozdz::rysuj()
{
    sterEkrn->rysuj();
}

SterDrukNisRozdz::SterDrukNisRozdz()
{
    sterDrk = new SDNR;
}

void SterDrukNisRozdz::rysuj()
{
    sterDrk->rysuj();
}

SterEkrnWysRozdz::SterEkrnWysRozdz()
{
    sterEkrn = new SEWR;
}

void SterEkrnWysRozdz::rysuj()
{
    sterEkrn->rysuj();
}

SterDrukWysRozdz::SterDrukWysRozdz()
{
    sterDrk = new SDWR;
}

void SterDrukWysRozdz::rysuj()
{
    sterDrk->rysuj();
}

//Metody fabryk
SterownikEkranu* FabrykaNisRozdz::pobierzSterEkrn()
{
    return new SENR();
}

SterownikDrukarki* FabrykaNisRozdz::pobierzSterDruk()
{
    return new SDNR();
}

SterownikEkranu* FabrykaWysRozdz::pobierzSterEkrn()
{
    return new SEWR();
}

SterownikDrukarki* FabrykaWysRozdz::pobierzSterDruk()
{
    return new SDWR();
}

//Konstruktor i metody klasy typu client (ApNadzorujaca)
ApNadzorujaca::ApNadzorujaca(FabrykaSter *f)
{
    fab = f;
}

void ApNadzorujaca::rysujEkran()
{
    SterownikEkranu *sterEkran = fab->pobierzSterEkrn();
    sterEkran->rysuj();
}

void ApNadzorujaca::rysujDrukarka()
{
    SterownikDrukarki *sterDruk = fab->pobierzSterDruk();
    sterDruk->rysuj();
}

class Konfiguracja
{
 public:
    Konfiguracja();
    FabrykaSter* getFabNis();
    FabrykaSter* getFabWys();
 private:
    FabrykaSter* fabNis;
    FabrykaSter* fabWys;
};

Konfiguracja::Konfiguracja()
{
    fabNis = new FabrykaNisRozdz;
    fabWys = new FabrykaWysRozdz;
}

FabrykaSter* Konfiguracja::getFabNis()
{
    return fabNis;
}

FabrykaSter* Konfiguracja::getFabWys()
{
    return fabWys;
}

int main()
{
    Konfiguracja conf;

    ApNadzorujaca *client = new ApNadzorujaca(conf.getFabNis());

    client->rysujEkran();
    cout<<endl;
    client->rysujDrukarka();
    
    cout<<endl<<"____________________________________________________"<<endl<<endl;

    FabrykaSter *fabWys;

    client = new ApNadzorujaca(conf.getFabWys());

    client->rysujEkran();
    cout<<endl;
    client->rysujDrukarka();

    return 0;
}