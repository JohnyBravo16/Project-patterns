#include <iostream>

using namespace std;

class Figura;
class Prostokat;
class Okrag;
class Biblioteka;
class BibliotekaV1;
class BibliotekaV2;
class BG1;
class BG2;


//klasa abstrakcyjna
class Figura
{
 public:
    Figura(Biblioteka* lib) : x_lib(lib)
    {

    }
    virtual void rysuj() = 0;
 protected:
    Biblioteka* x_lib;

    void rysujLinie();
    void rysujOkrag();
};

class Prostokat : public Figura
{
 public:
    Prostokat(Biblioteka* lib) : Figura(lib)
    {

    }
    void rysuj()
    {
        rysujLinie();
    }
};

class Okrag : public Figura
{
 public:
    Okrag(Biblioteka* lib) : Figura(lib)
    {

    }
    void rysuj()
    {
        rysujOkrag();
    }
};

//implementor
class Biblioteka
{
 public:
    virtual void rysujLinie() = 0;
    virtual void rysujOkrag() = 0;
};

class BG1
{
 public:
    void rysuj_linie()
    {
        cout<<"Rysuje linie za pomoca biblioteki graficznej BG1";
    }
    void rysuj_okrag()
    {
        cout<<"Rysuje okrag za pomoca biblioteki graficznej BG1";
    }
};

class BG2
{
 public:
    void narysuj_linie()
    {
        cout<<"Rysuje linie za pomoca biblioteki graficznej BG2";
    }
    void narysuj_okrag()
    {
        cout<<"Rysuje okrag za pomoca biblioteki graficznej BG2";
    }
};

class BibliotekaV1 : public Biblioteka
{
 protected:
    BG1* bg1;
 public:
    void rysujLinie()
    {
        bg1->rysuj_linie();
    }
    void rysujOkrag()
    {
        bg1->rysuj_okrag();
    }
};

class BibliotekaV2 : public Biblioteka
{
 protected:
    BG2* bg2;
 public:
    void rysujLinie()
    {
        bg2->narysuj_linie();
    }
    void rysujOkrag()
    {
        bg2->narysuj_okrag();
    }
};

void Figura::rysujLinie()
{
    x_lib->rysujLinie();
};

void Figura::rysujOkrag()
{
    x_lib->rysujOkrag();
};


int main()
{
    BibliotekaV1 v1;
    BibliotekaV2 v2;

    Okrag o1(&v1);
    Okrag o2(&v2);

    Prostokat p1(&v1);
    Prostokat p2(&v2);
    
    o1.rysuj();
    cout<<endl;
    o2.rysuj();
    cout<<endl<<"____________________________________________"<<endl;
    p1.rysuj();
    cout<<endl;
    p2.rysuj();

    return 0;
}