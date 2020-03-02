#include <iostream>
#include <math.h>

using namespace std;

class Calculaction
{
 public:
    virtual void liczKwadrat(double, double, double) = 0;
    virtual void wypiszPierwiastki() = 0;
    ~Calculaction() {};
 protected:
    Calculaction() {};
};

class Square : public Calculaction
{
 public:
    Square();
    void liczKwadrat(double, double, double);
    void wypiszPierwiastki();
    double GetX1()
    {
        return this->x_1;
    }
    double GetX2()
    {
        return this->x_2;
    }
    ~Square();
 private:
    double x_1, x_2;
};

class SquareProxy : public Calculaction
{
 public:
    SquareProxy();
    ~SquareProxy();
    void liczKwadrat(double, double, double);
    void wypiszPierwiastki();
 private:
    Square* sqr;
    double proxy_a, proxy_b, proxy_c, x_1, x_2;
};

//Rownanie kwadratowe
Square::Square()
{
    this->x_1 = 0;
    this->x_2 = 0;
}

Square::~Square()
{
    
}

void Square::liczKwadrat(double a, double b, double c)
{
    cout<<"[Liczenie pierwiastka ze Square]"<<endl;
    double delta = (b*b) - 4 * a * c;
    if(delta < 0)
    {
        cout<<"Brak pierwiastkow."<<endl;
    }
    if(delta == 0)
    {
        this->x_1 = (-b)/2 * a;
        wypiszPierwiastki();
        //this->x_2 = NULL;
    }
    else
    {
        this->x_1 = (-b - sqrt(delta))/2*a;
        this->x_2 = (-b + sqrt(delta))/2*a;
        wypiszPierwiastki();  
    }
}

void Square::wypiszPierwiastki()
{
    cout<<"Pierwiastki rownania: "<<endl<<"x1 = "<<this->x_1<<endl<<"x2 = "<<this->x_2<<endl;
}

//Proxy
SquareProxy::SquareProxy()
{
    sqr = 0;
}

SquareProxy::~SquareProxy()
{
    delete sqr;
}

void SquareProxy::liczKwadrat(double a, double b, double c)
{
    if(proxy_a != a && proxy_b != b && proxy_c != c)
    {
        this->proxy_a = a;
        this->proxy_b = b;
        this->proxy_b = c;

        if(!sqr) 
            sqr = new Square();

        sqr->liczKwadrat(a, b, c);
        this->x_1 = sqr->GetX1();
        this->x_2 = sqr->GetX2();
        //cout<<"DANE Z PROXY: "<<this->x_1<<" "<<x_2<<endl;  
    }
    else
    {
        cout<<"[Pierwiastek z SquareProxy]"<<endl;
        wypiszPierwiastki();
    }
    /*
    else
    {
        cout<<"[Liczenie pierwiastka z SquareProxy]"<<endl;
        double delta = (b*b) - 4 * a * c;
        if(delta < 0)
        {
            cout<<"Brak pierwiastkow."<<endl;
        }
        if(delta == 0)
        {
            this->x_1 = (-b)/2 * a;
            wypiszPierwiastki();
            //this->x_2 = NULL;
        }
        else
        {
            this->x_1 = (-b - sqrt(delta))/2*a;
            this->x_2 = (-b + sqrt(delta))/2*a;
            wypiszPierwiastki();  
        }
    }
    */
}

void SquareProxy::wypiszPierwiastki()
{
    if(!sqr)
        sqr = new Square();
    
    sqr->wypiszPierwiastki();
}

int main()
{

    SquareProxy sqrp;
    sqrp.liczKwadrat(1, -5, 6);
    cout<<"______________________________"<<endl<<endl;
    sqrp.liczKwadrat(1, -5, 6);

    return 0;
}