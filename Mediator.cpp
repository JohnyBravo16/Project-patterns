#include <iostream>
#include <stdlib.h>

using namespace std;

class Director;
class Widget;
class Cwiczenia;
class Wyklad;
class Przedmiot;
class Koniec;
class DialogDirector;

class Director
{
 public:
    virtual ~Director();
    virtual void WidgetChanged(Widget*) = 0;
 protected:
    Director();
};

class DialogDirector : public Director
{
 public:
    DialogDirector();
    ~DialogDirector();
    void WidgetChanged(Widget*);
    void HandleEvent(int);
 private:
    Cwiczenia* cw;
    Wyklad* wy;
    Przedmiot* prz;
    Koniec* kon;
};

class Widget
{
 public:
    Widget(Director*);
    virtual void Changed();
 protected:
    virtual void UtworzOkno(string) = 0;
 private:
    Director* dir;
};

class Cwiczenia : public Widget
{
 public:
    Cwiczenia(Director* dir) : Widget(dir){};
    void UtworzOkno(string dialog = "")
    {
        cout<<"1. Cwiczenia zaliczone." + dialog<<endl;
    }
};

class Wyklad : public Widget
{
 public:
    Wyklad(Director* dir) : Widget(dir){};
    void UtworzOkno(string dialog = "")
    {
        cout<<"2. Wyklad (egzamin) zaliczony." + dialog<<endl;
    }
};

class Przedmiot : public Widget
{
 public:
    Przedmiot(Director* dir) : Widget(dir){};
    void UtworzOkno(string dialog = "")
    {
        cout<<"3. Przedmiot zaliczony (wygrany konkurs)." + dialog<<endl;
    }    
};

class Koniec : public Widget
{
 public:
    Koniec(Director* dir) : Widget(dir){};
    void UtworzOkno(string = "")
    {
        cout<<"4. Wyjscie z programu."<<endl;
    }    
};

Director::Director()
{

}

Director::~Director()
{
    
}

DialogDirector::DialogDirector()
{
    this->cw = new Cwiczenia(this);
    this->prz = new Przedmiot(this);
    this->wy = new Wyklad(this);
    this->kon = new Koniec(this);
    
    cw->UtworzOkno();
    wy->UtworzOkno();
    prz->UtworzOkno();
    kon->UtworzOkno();
}

DialogDirector::~DialogDirector()
{
    delete this->cw;
    delete this->prz;
    delete this->wy;
    delete this->kon;
}

void DialogDirector::WidgetChanged(Widget* wid)
{
    if(wid == cw)
    {
        cw->UtworzOkno("X");
        wy->UtworzOkno();
        prz->UtworzOkno();
    }
    else if(wid == prz)
    {
        cw->UtworzOkno("X");
        wy->UtworzOkno("X");
        prz->UtworzOkno();
    }
    else if(wid == wy)
    {
        cw->UtworzOkno("X");
        wy->UtworzOkno("X");
        prz->UtworzOkno("X");
    }
    else if(wid == kon)
    {
        exit(EXIT_SUCCESS);
    }
    kon->UtworzOkno();
}

void DialogDirector::HandleEvent(int choice)
{
    switch (choice)
    {
    case 1:
        this->cw->Changed();
        break;
    case 2:
        this->prz->Changed();
        break;  
    case 3:
        this->wy->Changed();
        break;
    case 4:
        this->kon->Changed();
    default:
        break;
    }
}

Widget::Widget(Director* dir)
{
    this->dir = dir;
}

void Widget::Changed()
{
    this->dir->WidgetChanged(this);
}


int main()
{
    DialogDirector* dd = new DialogDirector;
    
    cout<<"Wybierz jedna z opcji [1 - 4]: ";
    
    int i;

  cin >> i;
  
  cout<<endl;

  while (i)
  {
    dd->HandleEvent(i);
    cout<<"Wybierz jedna z opcji [1 - 4]: ";
    cin >> i;
    cout<<endl;
  }

    
    return 0;
}