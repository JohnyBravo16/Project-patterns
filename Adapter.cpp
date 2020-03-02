#include <iostream>
#define N 3
using namespace std;

class Figura{
 public:
    Figura(){

    }
    virtual void wyswietl(){
        cout<<"Figura...";    
    }
    void wypelnij(){

    }
    void usun(){

    }
    void pobierzPolozenie(){

    }
    void nadajPolozenie(){

    }
    void nadajKolor(){

    }
};

class Kwadrat: public Figura{
    public:
    Kwadrat(): Figura(){

    }
    void wyswietl(){
        cout<<"Rysuje kwadrat";    
    }
};

class Linia: public Figura{
    public:
    Linia(): Figura(){
    }
    void wyswietl(){
        cout<<"Rysuje linie";
    }
};

class XXOkrag{
 public:
    XXOkrag()
    {

    }
    void wyswietlaj(){
        cout<<"Rysuje n-ty okrag";
    }
    void wypelniaj(){

    }
    void usuwaj(){

    }
    void pobierzPolozenie(){

    }
    void nadajPolozenie(){

    }
    void ustawKolor(){

    }
};


class Okrag: public Figura{
 private:
    XXOkrag* pxc;
 public:
    Okrag(): Figura(){
        pxc = new XXOkrag;
    }
    void pobierzPolozenie(){
        pxc->pobierzPolozenie();
    }
    void nadajPolozenie(){
        pxc->nadajPolozenie();
    }
    void wyswietl(){
        pxc->wyswietlaj();
    }
    void wypelnij(){
        pxc->wyswietlaj();
    }
    void nadajKolor(){
        pxc->ustawKolor();
    }
    void usun(){
        pxc->usuwaj();
    }
};

int main() {

    Figura **tab = new Figura*[N];

    tab[0] = new Kwadrat();
    tab[1] = new Linia();
    tab[2] = new Okrag();

    for (int i=0;i<N;i++)
    {
        tab[i]->wyswietl();
        cout<<endl;
    }

    return 0;
}