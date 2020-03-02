#include <iostream>
#include <vector>
#include <list>
#include <iterator>

#define N 3

using namespace std;

class Graphic;
class Line;
class Rectangle;
class Test;
class Picture;

class Graphic
{
 public:
    virtual void Draw() = 0;
    virtual void Add(Graphic* x)
    {

    }
    virtual void Remove()
    {

    }
    virtual Graphic* GetChild(int x)
    {

    }
};

class Line : public Graphic
{
 public:
    void Draw();
};

class Rectangle : public Graphic
{
 public:
    void Draw();
};

class Text : public Graphic
{
 public:
    void Draw();
};

class Picture : public Graphic
{
 public:
    void Draw();
    void Add(Graphic* x);
    void Remove();
    Graphic* GetChild(int);
 private:
    list<Graphic*> children;
};

void Line::Draw()
{
    cout<<"Rysuje linie. ";
}

void Rectangle::Draw()
{
    cout<<"Rysuje prostokat. ";
}

void Text::Draw()
{
    cout<<"Rysuje tekst. ";
}

void Picture::Draw()
{
    for(auto &i : children)
    {
        i->Draw();
    }
}

void Picture::Add(Graphic* x)
{
    children.push_back(x);
}

void Picture::Remove()
{
    children.pop_back();
}

Graphic* Picture::GetChild(int index)
{
    list<Graphic*>::iterator it = children.begin();
    advance(it, index - 1);

    return *it;
}

int main()
{
//Nie bylem pewien, czy pierwsza linijka [aPicture] powinna wypisywac skladowe, dlatego dodalem dodatkowy kompozyt
//W razie koniecznosci mozna usunac jeden z nich i wypisywac tylko dwie linijki bez pierwszej

    Picture kompozyt[N];
    
    kompozyt[2].Add(new Text);
    kompozyt[2].Add(new Line);
    kompozyt[2].Add(new Rectangle);

    kompozyt[1].Add(new Line);
    kompozyt[1].Add(new Rectangle);
    kompozyt[1].Add(&(kompozyt[2]));
    kompozyt[1].Add(new Line);

    kompozyt[0].Add(&kompozyt[1]);

    for(int i=0;i<N;i++)
    {
        kompozyt[i].Draw();
        cout<<endl;
    }
    
    

    return 0;
}