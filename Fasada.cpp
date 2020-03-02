#include <iostream>

using namespace std;

class Wektor3D{
 public:
    float x, y, z;
    Wektor3D()
    {
        x = 0;
        y = 0;
        z = 0;
    }
    Wektor3D(float x, float y, float z)
    {
        this->x = x;
        this->y = y;
        this->z = z;
    }
    void wyswietl()
    {
        cout<<"x = "<<x<<", "<<"y = "<<y<<", "<<"z = "<<z<<endl;
    }
    Wektor3D suma3D(const Wektor3D &i, const Wektor3D &j)
    {
        Wektor3D temp(i.x + j.x, i.y + j.y, i.z + j.z);
        return temp;
    }
    
};

class Wektor2D{
 public:
    int x, y, z;
    
    Wektor3D wektor3D;
    Wektor2D()
    {
        wektor3D = Wektor3D();
    }
    Wektor2D(float vx, float vy)
    {
        wektor3D = Wektor3D(vx, vy, 0);
    }
    Wektor2D suma2D(Wektor2D w1, Wektor2D w2)
    {
        Wektor3D temp1 = Wektor3D(w1.wektor3D.x, w1.wektor3D.y, 0);
        Wektor3D temp2 = Wektor3D(w2.wektor3D.x, w1.wektor3D.y, 0);

        temp1 = temp1.suma3D(temp1, temp2);
        
        w1.wektor3D.x = temp1.x;
        w1.wektor3D.y = temp1.y;

        return w1;
    }
    void wyswietl(Wektor2D wektor)
    {
        cout<<"x = "<<wektor.wektor3D.x<<", "<<"y = "<<wektor.wektor3D.y<<endl;
    }
};

int main(){

    Wektor3D a(3, 4, 5);
    Wektor3D b(1, 2, 3);
    a.wyswietl();
    b.wyswietl();

    Wektor3D c = a.suma3D(a, b);

    c.wyswietl();

    Wektor2D facade;
    Wektor2D v1(5, 10);
    Wektor2D v2(25, 40);
    Wektor2D v3;

    cout<<"v1:"<<endl;
    v1.wyswietl(v1);
    cout<<"v2:"<<endl;
    v2.wyswietl(v2);
    cout<<"Suma v1 + v2:"<<endl;
    v3 = facade.suma2D(v1, v2);
    v3.wyswietl(v3);

    return 0;
}