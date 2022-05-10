#ifndef ComPortDialog_H
#define ComPortDialog_H
#include <FL\FL_Input.h>
#include <FL\Fl_Button.H>
#include <FL\Fl_Window.H>
#include <FL\Fl_Choice.H>
#include <string>

void OnOk(Fl_Button*, void*);

class ComPortDialog : public Fl_Window
{
public:
    ComPortDialog();
    Yaesu::FT891::Commands::CatRateValue Rate;
    std::string m_PortName;
    Fl_Choice* CatRateChoice;
    Fl_Input* PortName;
    Fl_Button* Ok;
    void OkClicked();
};
#endif