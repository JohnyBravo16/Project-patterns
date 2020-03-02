#include <iostream>
#include <typeinfo>

using namespace std;

class BazaDanych;
class BazaDanychSQLServer;
class BazaDanychOracle;

class BazaDanych
{
 public:
    virtual void wyslijZapytanie(string) = 0;
    virtual void polaczBaza(string) = 0;
};

class BazaDanychSQLServer : public BazaDanych
{
 public:
    void wyslijZapytanie(string);
    void polaczBaza(string);
};

class BazaDanychOracle : public BazaDanych
{
 public:
    void wyslijZapytanie(string);
    void polaczBaza(string);
};

class SzablonZapytania
{
 public:
    SzablonZapytania();
    BazaDanych* GetProduct();
    void wykonajZapytanie(string nazwaBD, string specZapyt)
    {
        prod = utworzBD();

        string komendaBD;
        komendaBD = formatujConnect(nazwaBD);
        prod->polaczBaza(komendaBD);

        komendaBD = formatujSelect(specZapyt);
        prod->wyslijZapytanie(komendaBD);

    }
 protected:
    virtual BazaDanych* utworzBD() = 0;
    virtual string formatujConnect(string) = 0;
    virtual string formatujSelect(string) = 0;
 private:
    BazaDanych* prod;
};

class ZapytanieSQLServer : public SzablonZapytania
{
 public:
    BazaDanych* utworzBD()
    {
        return new BazaDanychSQLServer;
    } 
    string formatujConnect(string nazwaBD)
    {
        string komenda = nazwaBD;
        return komenda;
    }
    string formatujSelect(string specZapyt)
    {
        string komenda = specZapyt;
        return komenda;
    }
};

class ZapytanieOracle : public SzablonZapytania
{
 public:
    BazaDanych* utworzBD()
    {
        return new BazaDanychOracle;
    } 
    string formatujConnect(string nazwaBD)
    {
        string komenda = nazwaBD;
        return komenda;
    }
    string formatujSelect(string specZapyt)
    {
        string komenda = specZapyt + ";";
        return komenda;
    }
};

void BazaDanychSQLServer::polaczBaza(string baza)
{
    cout<<"Wykonywanie polaczenia z baza SQL: "<<baza<<endl;
}

void BazaDanychSQLServer::wyslijZapytanie(string zapytanie)
{
    cout<<"Przetwarzanie zapytania: "<<zapytanie<<endl;
}

void BazaDanychOracle::polaczBaza(string baza)
{
    cout<<"Wykonywanie polaczenia z baza Oracle: "<<baza<<endl;
}

void BazaDanychOracle::wyslijZapytanie(string zapytanie)
{
    cout<<"Przetwarzanie zapytania: "<<zapytanie<<endl;
}

SzablonZapytania::SzablonZapytania()
{
    prod = 0;
}

BazaDanych* SzablonZapytania::GetProduct()
{
    if(!prod)
        prod = utworzBD();

    return prod;
}


int main()
{
    ZapytanieOracle oracle;
    oracle.wykonajZapytanie("baza1", "select * from data");

    cout<<"_________________________"<<endl<<endl;

    ZapytanieSQLServer sql;
    sql.wykonajZapytanie("baza2", "select * from data");

    return 0;
}