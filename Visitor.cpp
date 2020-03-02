#include <iostream>

using namespace std;

class Zwierzeta;
class Ssak;
class Ptak;
class Gad;
class Ryba;
class Visitor;
class SumaOficjalna;
class SumaCzarnorynkowa;

class Zwierzeta
{
 public:
    Zwierzeta(double c, bool ch, double cc = -1)
    {
        cena = c;
        chore = ch;
        cena_czarnorynkowa = cc;
    };
    virtual void Accept(class Visitor &v) = 0;
    virtual void Wypisz()
    {
        cout<<Typ()<<" ";
        cout<<cena<<", "<<chore<<", "<<cena_czarnorynkowa<<endl;
    }
    virtual double SumaOficjalna()
    {
        return this->cena;
    }
    virtual double SumaCzarnorynkowa()
    {
        if(this->cena_czarnorynkowa <= 0)
        {
            return this->cena;
        }
        else
        {
            return this->cena_czarnorynkowa;
        }    
    }
    virtual bool Choroba()
    {
        return this->chore;
    }
    virtual string Typ() = 0;
 protected:
    double cena, cena_czarnorynkowa;
    bool chore;
};

class Visitor
{
 public:
    virtual void VisitElementA(Ssak *s) = 0;
    virtual void VisitElementA(Ptak *s) = 0;
    virtual void VisitElementA(Gad *s) = 0;
    virtual void VisitElementA(Ryba *s) = 0;
    virtual void PrintSum(){};
};

class Ssak : public Zwierzeta
{
 public:
    void Accept(Visitor &v);
    string Typ()
    {
        return "Ssak";
    }
 public:
    Ssak(double c, bool ch) : Zwierzeta(c, ch){};
};

class Ptak : public Zwierzeta
{
 public:
    void Accept(Visitor &v);
    string Typ()
    {
        return "Ptak";
    }
 public:
    Ptak(double c, bool ch, double cc) : Zwierzeta(c, ch, cc)
    {
        cena_cz = cc;
    };
 private:
    double cena_cz;
};

class Gad : public Zwierzeta
{
 public:
    void Accept(Visitor &v);
    string Typ()
    {
        return "Gad";
    }
 public:
    Gad(double c, bool ch) : Zwierzeta(c, ch){};
};

class Ryba : public Zwierzeta
{
 public:
    void Accept(Visitor &v);
    string Typ()
    {
        return "Ryba";
    }
 public:
    Ryba(double c, bool ch) : Zwierzeta(c, ch){};
};

void Ssak::Accept(Visitor &v)
{
    v.VisitElementA(this);
}

void Ptak::Accept(Visitor &v)
{
    v.VisitElementA(this);
}

void Gad::Accept(Visitor &v)
{
    v.VisitElementA(this);
}

void Ryba::Accept(Visitor &v)
{
    v.VisitElementA(this);
}

class SumaOficjalna : public Visitor
{
 public:
    SumaOficjalna()
    {
        sumaKompletna = 0;
    }
    void VisitElementA(Ssak *s);
    void VisitElementA(Ptak *s);
    void VisitElementA(Gad *s);
    void VisitElementA(Ryba *s);
    void PrintSum()
    {
        cout<<"Suma kolekcji: "<<sumaKompletna<<endl;
    }
 private:
    double sumaKompletna;
};

class SumaCzarnorynkowa : public Visitor
{
 public:
    SumaCzarnorynkowa()
    {
        sumaCzarorynkowa = 0;
    }
    void VisitElementA(Ssak *s);
    void VisitElementA(Ptak *s);
    void VisitElementA(Gad *s);
    void VisitElementA(Ryba *s);
    void PrintSum()
    {
        cout<<"Suma kolekcji: "<<sumaCzarorynkowa<<endl;
    }
 private:
    double sumaCzarorynkowa;
};

class Weterynarz : public Visitor
{
 public:
    Weterynarz()
    {

    }
    void VisitElementA(Ssak *s);
    void VisitElementA(Ptak *s);
    void VisitElementA(Gad *s);
    void VisitElementA(Ryba *s);
};

void SumaOficjalna::VisitElementA(Ssak *s)
{
    double temp = s->SumaOficjalna();
    sumaKompletna += temp;
}

void SumaOficjalna::VisitElementA(Ptak *s)
{
    double temp = s->SumaOficjalna();
    sumaKompletna += temp;
}

void SumaOficjalna::VisitElementA(Gad *s)
{
    double temp = s->SumaOficjalna();
    sumaKompletna += temp;
}

void SumaOficjalna::VisitElementA(Ryba *s)
{
    double temp = s->SumaOficjalna();
    sumaKompletna += temp;
}

void SumaCzarnorynkowa::VisitElementA(Ssak *s)
{
    double temp = s->SumaCzarnorynkowa();
    sumaCzarorynkowa += temp;
}

void SumaCzarnorynkowa::VisitElementA(Ptak *s)
{
    double temp = s->SumaCzarnorynkowa();
    sumaCzarorynkowa += temp;
}

void SumaCzarnorynkowa::VisitElementA(Gad *s)
{
    double temp = s->SumaCzarnorynkowa();
    sumaCzarorynkowa += temp;
}

void SumaCzarnorynkowa::VisitElementA(Ryba *s)
{
    double temp = s->SumaCzarnorynkowa();
    sumaCzarorynkowa += temp;
}

//

void Weterynarz::VisitElementA(Ssak *s)
{
    if((s->Choroba()) == true)
    {
        if(s->Typ() == "Ptak")
        {
            if(s->SumaCzarnorynkowa() >= (s->SumaOficjalna()*2))
                cout<<"Odwiedzane zwierze: Ptak. Diagnoza: choroba. Zabrane do lecznicy."<<endl;
            else
            {
                cout<<"Odwiedzane zwierze: Ptak. Diagnoza: choroba. Leczenie: antybiotyki, dieta."<<endl;
            }
        }
        else
        {
            cout<<"Odwiedzane zwierze: "<<s->Typ()<<". Diagnoza: choroba. Leczenie: antybiotyki."<<endl;
        }
    }
    else
    {
        cout<<"Zwierze nie jest chore."<<endl;
    }
}

void Weterynarz::VisitElementA(Ptak *s)
{
    if((s->Choroba()) == true)
    {
        if(s->Typ() == "Ptak")
        {
            if(s->SumaCzarnorynkowa() >= (s->SumaOficjalna()*2))
                cout<<"Odwiedzane zwierze: Ptak. Diagnoza: choroba. Zabrane do lecznicy."<<endl;
            else
            {
                cout<<"Odwiedzane zwierze: Ptak. Diagnoza: choroba. Leczenie: antybiotyki, dieta."<<endl;
            }
        }
        else
        {
            cout<<"Odwiedzane zwierze: "<<s->Typ()<<". Diagnoza: choroba. Leczenie: antybiotyki."<<endl;
        }
    }
    else
    {
        cout<<"Zwierze nie jest chore."<<endl;
    }
}

void Weterynarz::VisitElementA(Gad *s)
{
    if((s->Choroba()) == true)
    {
        if(s->Typ() == "Ptak")
        {
            if(s->SumaCzarnorynkowa() >= (s->SumaOficjalna()*2))
                cout<<"Odwiedzane zwierze: Ptak. Diagnoza: choroba. Zabrane do lecznicy."<<endl;
            else
            {
                cout<<"Odwiedzane zwierze: Ptak. Diagnoza: choroba. Leczenie: antybiotyki, dieta."<<endl;
            }
        }
        else
        {
            cout<<"Odwiedzane zwierze: "<<s->Typ()<<". Diagnoza: choroba. Leczenie: antybiotyki."<<endl;
        }
    }
    else
    {
        cout<<"Zwierze nie jest chore."<<endl;
    }
}

void Weterynarz::VisitElementA(Ryba *s)
{
    if((s->Choroba()) == true)
    {
        if(s->Typ() == "Ptak")
        {
            if(s->SumaCzarnorynkowa() >= (s->SumaOficjalna()*2))
                cout<<"Odwiedzane zwierze: Ptak. Diagnoza: choroba. Zabrane do lecznicy."<<endl;
            else
            {
                cout<<"Odwiedzane zwierze: Ptak. Diagnoza: choroba. Leczenie: antybiotyki, dieta."<<endl;
            }
        }
        else
        {
            cout<<"Odwiedzane zwierze: "<<s->Typ()<<". Diagnoza: choroba. Leczenie: antybiotyki."<<endl;
        }
    }
    else
    {
        cout<<"Zwierze nie jest chore."<<endl;
    }
}

int main()
{
    Zwierzeta *list[] = 
    {
        new Ssak(10, true), 
        new Ptak(15, false, 50), 
        new Gad(5, false),
        new Gad(7, true),
        new Ptak(20, true, 10),
        new Ptak(5, true, 40)
    };

    SumaOficjalna v1;
    SumaCzarnorynkowa v2;
    Weterynarz v3;
    
    for(int i=0;i<6;i++)
    {
        list[i]->Accept(v1);
        list[i]->Wypisz();
    }
    v1.PrintSum();
    
    cout<<"_________________________________"<<endl<<endl;

    for(int i=0;i<6;i++)
    {
        list[i]->Accept(v2);
        list[i]->Wypisz();
    }
    v2.PrintSum();

    cout<<"_________________________________"<<endl<<endl;

    for(int i=0;i<6;i++)
    {
        list[i]->Accept(v3);
        list[i]->Wypisz();
    }

    return 0;
}