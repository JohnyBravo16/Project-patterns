#include <iostream>
#include <list>
#include <iterator>

using namespace std;

class Subject;
class ConcreteSubject;
class Observer;
class ConcreteObserver;

class Subject
{
 public:
    virtual ~Subject(){};
    virtual void Attach(Observer*);
    virtual void Detach();
    virtual void Notify();
 protected:
    Subject(){};
 private:
    list<Observer*> listObservers;
};

class Observer
{
 public:
    virtual ~Observer(){};
    virtual void Update(Subject* zmiana) = 0; 
 protected:
    Observer(int id)
    {
        this->id = id;
    };
 private:
    int id;
};

class ConcreteSubject : public Subject
{
 public:
    ConcreteSubject();
    bool GetState();
    void SetState(bool state);
 private:
    bool subjectState;
};

class ConcreteObserver : public Observer
{
 public:
    ConcreteObserver(ConcreteSubject* conSub, int id);
    ~ConcreteObserver();
    void Update(Subject* subj);
 private:
    ConcreteSubject* sub;
    int id;
    bool observerState;
};

void Subject::Attach(Observer* obs)
{
    listObservers.push_back(obs);
}

void Subject::Detach()
{
    listObservers.pop_back();
}

void Subject::Notify()
{
    for(auto &i : listObservers)
    {
        i->Update(this);
    }
}

ConcreteSubject::ConcreteSubject()
{
    subjectState = true;
}

bool ConcreteSubject::GetState()
{
    return subjectState;
}

void ConcreteSubject::SetState(bool state)
{
    this->subjectState = state;
    Subject::Notify();
}

ConcreteObserver::ConcreteObserver(ConcreteSubject* conSub, int id) : Observer(id)
{
    sub = conSub;
    this->observerState = sub->GetState();
    this->id = id;
    sub->Attach(this);
}

ConcreteObserver::~ConcreteObserver()
{
    sub->Detach();
}

void ConcreteObserver::Update(Subject* subj)
{
    observerState = sub->GetState();
    cout<<"Powiadomiono o zmianie stanu observer: "<<this->id<<", jego stan: "<<observerState<<endl;
}

int main()
{
    ConcreteSubject* subject = new ConcreteSubject;
    Observer* observer = new ConcreteObserver(subject, 1);
    Observer* observer2 = new ConcreteObserver(subject, 2);
    Observer* observer3 = new ConcreteObserver(subject, 3);

    cout<<subject->GetState()<<endl;
    subject->SetState(false);
    cout<<subject->GetState()<<endl;
    subject->Detach();
    subject->SetState(true);


    return 0;
}