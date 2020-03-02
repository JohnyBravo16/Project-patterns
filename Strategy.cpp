#include <iostream>
#include <iomanip>
#define N 3

using namespace std;

class Zamowienie;
class ObliczPodatek;
class PodatekPolska;
class PodatekNiemcy;

class Zamowienie
{
 protected:
    ObliczPodatek* pPodatek;
 public:
    double tab[N];
    Zamowienie()
    {
        tab[0] = 10.50;
        tab[1] = 50;
        tab[2] = 100.20;
    }
    double obliczPodatek(string);
    /*
    void wypisz()
    {
        for(int i=0;i<N;i++)
        {
            cout<<setprecision(2)<<fixed<<tab[i]<<" ";
        }
        cout<<endl;
    }
    */
};

class ObliczPodatek
{
 public:
    virtual double kwotaPodatku(double*) = 0;
};

class PodatekPolska : public ObliczPodatek
{
 public:
    double kwotaPodatku(double *tab)
    {
        for(int i=0;i<N;i++)
        {
            tab[i] *= 1.23;
                cout<<setprecision(2)<<fixed<<tab[i]<<" ";
        }
        cout<<endl;
        return *tab;
    }
};

class PodatekNiemcy : public ObliczPodatek
{
 public:
    double kwotaPodatku(double *tab)
    {
        for(int i=0;i<N;i++)
        {
            tab[i] *= 1.19;
            cout<<setprecision(2)<<fixed<<tab[i]<<" ";
        }
        cout<<endl;
        return *tab;
    }
};

double Zamowienie::obliczPodatek(string kraj)
{
    delete pPodatek;
    if(kraj == "PL")
    {
        pPodatek = new PodatekPolska();
        return pPodatek->kwotaPodatku(tab);
    }
    if(kraj == "DE")
    {
        pPodatek = new PodatekNiemcy();
        return pPodatek->kwotaPodatku(tab);
    }
}

int main()
{
    Zamowienie a;
    //a.wypisz();

    a.obliczPodatek("PL");
    cout<<"_____________________"<<endl;
    a.obliczPodatek("DE");
    return 0;
}