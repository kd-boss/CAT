#include "..\CAT\Cat.h"
#include "ComPortDialog.h"

void OnOk(Fl_Button* o, void* v)
{
	ComPortDialog* pthis = (ComPortDialog*)v;
	pthis->OkClicked();
}

void OnCatChoice(Fl_Widget* pitem, void* v)
{

}

ComPortDialog::ComPortDialog() : Fl_Window(300,200)
{
	this->label("Port Settings");
	PortName = new Fl_Input(150,20,100,30,"Port Name:");
	PortName->align(FL_ALIGN_LEFT);
	CatRateChoice = new Fl_Choice(150,70, 100, 30, "Baud Rate:");
	CatRateChoice->add("4800 bps", 0,OnCatChoice , this, 0);
	CatRateChoice->add("9600 bps", 0,OnCatChoice , this, 0);
	CatRateChoice->add("19200 bps", 0, OnCatChoice, this, 0);
	CatRateChoice->add("38400 bps", 0, OnCatChoice, this, 0);
	Ok = new Fl_Button(300 - 50, 200 - 30, 50, 30, "OK");
	Ok->callback((Fl_Callback*)&::OnOk,this);
}

void ComPortDialog::OkClicked()
{
	Rate = static_cast<Yaesu::Commands::FT891::CatRateValue>(CatRateChoice->value());
	m_PortName = PortName->value();
	this->hide();
}
