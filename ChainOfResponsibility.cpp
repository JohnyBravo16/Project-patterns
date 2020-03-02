#include <iostream>
using namespace std;

typedef int Topic;
const Topic NO_HELP_TOPIC = -1;
const Topic PRINT_BUTTON_TOPIC = 1;
const Topic PRINT_DIALOG_TOPIC = 2;
const Topic APPLICATION_TOPIC = 3;
const Topic SAVE_TOPIC = 4;
const Topic OK_TOPIC = 4;

class HelpHandler
{
 protected:
    HelpHandler* handler;
 public:
    HelpHandler();
    virtual void HandleHelp(Topic) = 0;
    virtual void SetHandler(HelpHandler* hh)
    {
        handler = hh;
    }
};

HelpHandler::HelpHandler()
{
    handler = 0;
}

class Application : public HelpHandler
{
 public:
    Application(Topic);
    void HandleHelp(Topic);
    void ShowHelp();
 private:
    Topic topic;
};

class Widget : public HelpHandler
{
 public:
    Widget(Topic t):HelpHandler(){};
    virtual void HandleHelp(Topic t)
    {
        if(topic == t)
        {
            ShowHelp();
        }
        else
        {
            if(handler != NULL)
            {
                cout<<name<<": nie potrafie obsluzyc zadania. Przekazuje dalej"<<endl;
                handler->HandleHelp(t);
            }
            else
            {
                cout<<"BRAK KOLEJNEGO HANDLERA"<<endl;
            }
        }
    }
    virtual void ShowHelp()
    {
        cout<<name<<": potrafie obsluzyc zadanie. Wyswietlam pomoc."<<endl;
    }
 protected:
    string name;
    Topic topic;
};

class SaveDialog : public Widget
{
 public:
    SaveDialog(Topic);
};

class PrintDialog : public Widget
{
 public:
    PrintDialog(Topic);
};

class PrintButton : public Widget
{
 public:
    PrintButton(Topic);
};

class OKButton : public Widget
{
 public:
    OKButton(Topic);
};

class Konfiguracja
{
 public:
    Konfiguracja()
    {
        app = new Application(PRINT_BUTTON_TOPIC);
        sd = new SaveDialog(SAVE_TOPIC);
        pd = new PrintDialog(PRINT_DIALOG_TOPIC);
        ob = new OKButton(OK_TOPIC);
    }
    HelpHandler* GetApp()
    {
        return this->app;
    }
    HelpHandler* GetSaveDialog()
    {
        return this->sd;
    }
    HelpHandler* GetPrintDialog()
    {
        return this->pd;
    }
    HelpHandler* GetOb()
    {
        return this->ob;
    }
 private:
    Application* app;
    SaveDialog* sd;
    PrintDialog* pd;
    OKButton* ob;
};

Application::Application(Topic t)
{
    topic = t;
}

void Application::HandleHelp(Topic t)
{
    if(topic == t)
    {
        ShowHelp();
    }
    else
    {
        if(handler != NULL)
        {
            cout<<"Application: nie potrafie obsluzyc zadania. Przekazuje dalej"<<endl;
            handler->HandleHelp(t);
        }
        else
        {
            cout<<"BRAK KOLEJNEGO HANDLERA"<<endl;
        }
    }
}

void Application::ShowHelp()
{
    cout<<"anApplication: potrafie obsluzyc zadanie. Wyswietlam pomoc."<<endl;
}

SaveDialog::SaveDialog(Topic t) : Widget(t)
{
    name = "SaveDialog";
    topic = t;
}

PrintDialog::PrintDialog(Topic t) : Widget(t)
{
    name = "PrintDialog";
    topic = t;
}

PrintButton::PrintButton(Topic t) : Widget(t)
{
    name = "PrintButton";
    topic = t;
}

OKButton::OKButton(Topic t) : Widget(t)
{
    name = "OkButton";
    topic = t;
}

int main ()
{
    Konfiguracja conf;

    conf.GetOb()->SetHandler(conf.GetPrintDialog());
    conf.GetPrintDialog()->SetHandler(conf.GetApp());
    conf.GetSaveDialog()->SetHandler(conf.GetApp());
    conf.GetOb()->HandleHelp(1);
    cout<<"________________"<<endl<<endl;
    conf.GetSaveDialog()->HandleHelp(4);

	return 0;
}
