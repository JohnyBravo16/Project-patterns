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
 private:
    string name;
    Topic topic;
};

class SaveDialog : public HelpHandler
{
 public:
    SaveDialog(Topic);
    void HandleHelp(Topic);
    void ShowHelp();
 private:
    Topic topic;
};

class PrintDialog : public HelpHandler
{
 public:
    PrintDialog(Topic);
    void HandleHelp(Topic);
    void ShowHelp();
 private:
    Topic topic;
};

class PrintButton : public HelpHandler
{
 public:
    PrintButton(Topic);
    void HandleHelp(Topic);
    void ShowHelp();
 private:
    Topic topic;
};

class OKButton : public HelpHandler
{
 public:
    OKButton(Topic);
    void HandleHelp(Topic);
    void ShowHelp();
 private:
    Topic topic;
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
            cout<<"anApplication: nie potrafie obsluzyc zadania. Przekazuje dalej"<<endl;
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

SaveDialog::SaveDialog(Topic t)
{
    topic = t;
}

void SaveDialog::HandleHelp(Topic t)
{
    if(topic == t)
    {
        ShowHelp();
    }
    else
    {
        if(handler != NULL)
        {
            cout<<"aSaveDialog: nie potrafie obsluzyc zadania. Przekazuje dalej"<<endl;
            handler->HandleHelp(t);
        }
        else
        {
            cout<<"BRAK KOLEJNEGO HANDLERA"<<endl;
        }
    }
}

void SaveDialog::ShowHelp()
{
    cout<<"aSaveDialog: potrafie obsluzyc zadanie. Wyswietlam pomoc."<<endl;
}

PrintDialog::PrintDialog(Topic t)
{
    topic = t;
}

void PrintDialog::HandleHelp(Topic t)
{
    if(topic == t)
    {
        ShowHelp();
    }
    else
    {
        if(handler != NULL)
        {
            cout<<"aPrintDialog: nie potrafie obsluzyc zadania. Przekazuje dalej"<<endl;
            handler->HandleHelp(t);
        }
        else
        {
            cout<<"BRAK KOLEJNEGO HANDLERA"<<endl;
        }
    }
}

void PrintDialog::ShowHelp()
{
    cout<<"aPrintDialog: potrafie obsluzyc zadanie. Wyswietlam pomoc."<<endl;
}

PrintButton::PrintButton(Topic t)
{
    topic = t;
}

void PrintButton::HandleHelp(Topic t)
{
    if(topic == t)
    {
        ShowHelp();
    }
    else
    {
        if(handler != NULL)
        {
            cout<<"aPrintButton: nie potrafie obsluzyc zadania. Przekazuje dalej"<<endl;
            handler->HandleHelp(t);
        }
        else
        {
            cout<<"BRAK KOLEJNEGO HANDLERA"<<endl;
        }
    }
}

void PrintButton::ShowHelp()
{
    cout<<"aPrintButton: potrafie obsluzyc zadanie. Wyswietlam pomoc."<<endl;
}

OKButton::OKButton(Topic t)
{
    topic = t;
}

void OKButton::HandleHelp(Topic t)
{
    if(topic == t)
    {
        ShowHelp();
    }
    else
    {
        if(handler != NULL)
        {
            cout<<"aOKButton: nie potrafie obsluzyc zadania. Przekazuje dalej"<<endl;
            handler->HandleHelp(t);
        }
        else
        {
            cout<<"BRAK KOLEJNEGO HANDLERA"<<endl;
        }
    }
}

void OKButton::ShowHelp()
{
    cout<<"aOKButton: potrafie obsluzyc zadanie. Wyswietlam pomoc."<<endl;
}

int main ()
{
    Application* app = new Application(PRINT_BUTTON_TOPIC);

    SaveDialog* sd = new SaveDialog(SAVE_TOPIC);

    PrintDialog* pd = new PrintDialog(PRINT_DIALOG_TOPIC);

    //PrintButton* pb = new PrintButton(PRINT_BUTTON_TOPIC);

    OKButton* ob = new OKButton(OK_TOPIC);

    sd->SetHandler(app);
    pd->SetHandler(app);

    ob->SetHandler(pd);

    ob->HandleHelp(1);
    cout<<"________________"<<endl<<endl;
    sd->HandleHelp(1);
    cout<<"________________"<<endl<<endl;
    ob->HandleHelp(2);

	return 0;
}
