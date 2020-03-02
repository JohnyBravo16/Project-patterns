#include <iostream>

using namespace std;

class SzablonZapytania
{
 public:
    void wykonajZapytanie(string nazwaBD, string specZapyt)
    {
        string komendaBD;
        komendaBD = formatujConnect(nazwaBD);
        cout<<komendaBD<<endl;

        komendaBD = formatujSelect(specZapyt);
        cout<<komendaBD<<endl;
    }
 protected:
    virtual string formatujConnect(string) = 0;
    virtual string formatujSelect(string) = 0;
};

class ZapytanieSQLServer : public SzablonZapytania
{
    string formatujConnect(string nazwaBD)
    {
        string komenda = "Polaczenie z baza: " + nazwaBD;
        return komenda;
    }
    string formatujSelect(string specZapyt)
    {

        string komenda = "Wykonywanie zapytania: " + specZapyt;
        return komenda;
    }
};

class ZapytanieOracle : public SzablonZapytania
{
    string formatujConnect(string nazwaBD)
    {
        string komenda = "Polaczenie z baza: " + nazwaBD;
        return komenda;
    }
    string formatujSelect(string specZapyt)
    {
        string komenda = "Wykonywanie zapytania: " + specZapyt + ";";
        return komenda;
    }
};

int main()
{
    ZapytanieOracle a;
    a.wykonajZapytanie("Jakas baza 1", "select * from ksiazki");

    ZapytanieSQLServer b;
    b.wykonajZapytanie("Jakas baza 2", "select * from ksiazki");

    return 0;
}