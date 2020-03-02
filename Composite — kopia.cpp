#include <iostream>
#include <vector>
#define N 2

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
    virtual void Remove(Graphic* x)
    {

    }
    virtual void GetChild(int x)
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
    vector <Graphic*> children;
 public:
    void Draw();
    void Add(Graphic* x);
    void Remove(Graphic*);
    void GetChild(int);
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
    for(int i=0;i<children.size();i++)
        children[i]->Draw();
}

void Picture::Add(Graphic* x)
{
    children.push_back(x);
}

void Picture::Remove(Graphic* x)
{
    
}

void Picture::GetChild(int index)
{
    
}

int main()
{
    Picture kompozyt[N];
    
    kompozyt[1].Add(new Text);
    kompozyt[1].Add(new Line);
    kompozyt[1].Add(new Rectangle);

    kompozyt[0].Add(new Line);
    kompozyt[0].Add(new Rectangle);
    kompozyt[0].Add(&(kompozyt[1]));
    kompozyt[0].Add(new Line);


    for(int i=0;i<N;i++)
    {
        kompozyt[i].Draw();
        cout<<endl;
    }

    return 0;
}