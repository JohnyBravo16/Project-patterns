#include <iostream>
#include <ctime>
typedef int Topic;
const Topic NO_HELP_TOPIC = -1;


using namespace std;

class HelpHandler{public:HelpHandler(HelpHandler* = 0, Topic = NO_HELP_TOPIC);virtual bool HasHelp();virtual void SetHandler(HelpHandler*, Topic);virtual void HandleHelp();private:HelpHandler* successor;Topic topic;};

HelpHandler::HelpHandler(HelpHandler* h, Topic t): successor(h), topic(t){}bool HelpHandler::HasHelp(){return topic != NO_HELP_TOPIC;}void HelpHandler::HandleHelp(){if (successor)successor->HandleHelp();}

class Widget : public HelpHandler{protected:Widget(Widget*, Topic = NO_HELP_TOPIC);private:Widget* parent;};Widget::Widget(Widget* w, Topic t): HelpHandler(w, t){parent = w;}

class Button : public Widget{public:Button(Widget* p, Topic t = NO_HELP_TOPIC);virtual void HandleHelp();};Button::Button(Widget* p, Topic t): Widget(p, t){}

void Button::HandleHelp(){if (HasHelp()){}else{HelpHandler::HandleHelp();}}

class Dialog : public Widget{public:Dialog(HelpHandler*, Topic = NO_HELP_TOPIC);virtual void HandleHelp();};Dialog::Dialog(HelpHandler* h, Topic t): Widget(0){SetHandler(h, t);}

void Dialog::HandleHelp(){if (HasHelp()){}else{HelpHandler::HandleHelp();}}

class Application : public HelpHandler{public:Application(Topic t);virtual void HandleHelp();};Application::Application(Topic t): HelpHandler(0, t){}

int main()
{

    const Topic PRINT_TOPIC = 1;const Topic PAGE_SETUP_TOPIC = 2;const Topic APPLICATION_TOPIC = 3;Application* app = new Application(APPLICATION_TOPIC);Dialog* dlg = new Dialog(app, PRINT_TOPIC);Button* button = new Button(dlg, PAGE_SETUP_TOPIC);button->HandleHelp();

    return 0;
}