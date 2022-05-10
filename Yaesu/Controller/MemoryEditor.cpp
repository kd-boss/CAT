#include "MemoryEditor.h"
#include <fmt\format.h>

void OnMemoryEditorOk( void* o, void* v)
{

}


void OnMemoryEditorClarifierStateChange(Fl_Widget* o, void* v)
{
    MemoryEditor* window = (MemoryEditor*)v;
     for(int i = 0; i < 118;i++)
    {
        if(window->w[i][4] == o)
        {           
           auto x = std::find_if(window->m_channels.begin(), window->m_channels.end(), [i](auto e){ return ((int)e.MemoryChannel) == i; });
           auto cl = static_cast<Yaesu::FT891::Commands::ClarifierState>(((Fl_Choice*)o)->value());
           x->Clarifier = cl;            
        }
    }
    
}

void OnMemoryEditorOperatingMode(Fl_Widget* o, void* v)
{
    MemoryEditor* window = (MemoryEditor*)v;
    for(int i = 0; i < 118;i++)
    {
        if(window->w[i][8] == o)
        {            
            auto x = std::find_if(window->m_channels.begin(), window->m_channels.end(), [i](auto e){ return ((int)e.MemoryChannel) == i; });
            auto op = static_cast<Yaesu::FT891::Commands::OperationType>(((Fl_Choice*)o)->value());
            x->Operation = op;
        }
    }
}

void OnMemoryEditorCTCSS(Fl_Widget* o, void* v)
{
    MemoryEditor* window = (MemoryEditor*)v;

}


void OnMemoryEditorTag(Fl_Check_Button* o, void* v)
{
    MemoryEditor* window = (MemoryEditor*)v;
    for(int i = 0; i < 118;i++)
    {
        if(window->w[i][8] == o)
        {
            if(o->value())
            {
                 window->w[i][9]->activate();
                 std::find_if(window->m_channels.begin(), window->m_channels.end(), [i](auto e){ return static_cast<int>(e.MemoryChannel) == i;})->TAG = Yaesu::FT891::Commands::TagValue::ON;
                 return;
            }   
            else
            {
                window->w[i][9]->deactivate();
                std::find_if(window->m_channels.begin(), window->m_channels.end(), [i](auto e){ return static_cast<int>(e.MemoryChannel) == i;})->TAG = Yaesu::FT891::Commands::TagValue::OFF;
                return;
            }
                
        }
    }

}

void OnTagEdit(Fl_Input* o, void* v)
{
    MemoryEditor* window = (MemoryEditor*)v;
    for(int i = 0; i < 118;i++)
    {
        if(window->w[i][9] == o)
        {
            auto x = std::find_if(window->m_channels.begin(), window->m_channels.end(), [i](auto e){ return static_cast<int>(e.MemoryChannel) == i; });
            if(x != window->m_channels.end())
            {
                x->TagString = std::string();
                x->TagString = o->value();
                return;
            }                               
        }
    }
}

void OnModeChange(Fl_Widget* o, void* v)
{
    MemoryEditor* window = (MemoryEditor*)v;
    for(int i = 0; i < 118;i++)
    {
        if(window->w[i][5] == o)
        {            
            auto x = std::find_if(window->m_channels.begin(), window->m_channels.end(), [i](auto e){ return static_cast<int>(e.MemoryChannel) == i; });
            if(x != window->m_channels.end())
            {
                x->Mode = static_cast<Yaesu::FT891::Commands::MemoryChannelModeValue>(((Fl_Choice*)o)->value() + 1);
            }                            
            return;
        }
    }
}

void OnRepeaterMode(Fl_Widget* o, void* v)
{

    MemoryEditor* window = (MemoryEditor*)v;
    
        for(int i = 0; i < 118;i++)
        {
            if(window->w[i][7] == o)
            {
                
                window->m_newChannel->Operation = static_cast<Yaesu::FT891::Commands::OperationType>(((Fl_Choice*)o)->value() - 1);
                
                return;
            }
        }
    
    
}

void OnFreqInput(Fl_Input* o, void* v)
{
    MemoryEditor* window = (MemoryEditor*)v;
    std::string sfreq = o->value();
    int pos = 1;
    while((pos = sfreq.find_first_of(".")) != std::string::npos)
	{
		sfreq = sfreq.erase(pos,1);
	}
    int freq = std::stoi(sfreq);
    for(int i = 0; i < 118;i++)
    {
        if(window->w[i][2] == o)
        {
            auto x = std::find_if(window->m_channels.begin(), window->m_channels.end(), [i](auto e){ return static_cast<int>(e.MemoryChannel) == i; });
            if(x != window->m_channels.end())
            {
                x->VFOAFreq = freq;
            }                            
        }
    }
}

void OnChannnelEnabled(Fl_Check_Button* o, void* v)
{
    MemoryEditor* window = (MemoryEditor*)v;
    for(int i = 0; i < 118;i++)
    {
        if(window->w[i][0] == o)
        {            
            if(o->value())
            {            
                window->w[i][1]->activate();
                window->w[i][2]->activate();
                window->w[i][3]->activate();
                window->w[i][4]->activate();
                window->w[i][5]->activate();
                window->w[i][6]->activate();
                window->w[i][7]->activate();
                window->w[i][8]->activate();
                
                if(window->m_newChannel)
                {
                    window->m_newChannel->MemoryChannel = static_cast<Yaesu::FT891::Commands::MemoryChannelValue>(i);
                    window->frequencies[i] = Yaesu::FT891::Commands::DisplayFrequency(window->m_newChannel->VFOAFreq);
                    window->clarifiervalues[i] = fmt::format("{}", window->m_newChannel->ClarifierFreq);
                    ((Fl_Input*)window->w[i][2])->value(window->frequencies[i].c_str());
                    ((Fl_Input*)window->w[i][2])->redraw();
                    ((Fl_Choice*)window->w[i][4])->value((int)window->m_newChannel->Clarifier);
                    ((Fl_Choice*)window->w[i][5])->value((int)window->m_newChannel->Mode - 1);
                    ((Fl_Choice*)window->w[i][6])->value((int)window->m_newChannel->CTCSS);
                    ((Fl_Choice*)window->w[i][7])->value((int)window->m_newChannel->Operation);
                    ((Fl_Check_Button*)window->w[i][8])->value((int)window->m_newChannel->TAG);                   
                    ((Fl_Input*)window->w[i][9])->value(window->m_newChannel->TagString.c_str());
                     window->m_channels.push_back(*window->m_newChannel);                     
                     window->m_newChannel = nullptr;
                }
                
                
                return;
            }
            else
            {
                window->w[i][1]->deactivate();
                window->w[i][2]->deactivate();
                window->w[i][3]->deactivate();
                window->w[i][4]->deactivate();
                window->w[i][5]->deactivate();
                window->w[i][6]->deactivate();
                window->w[i][7]->deactivate();
                window->w[i][8]->deactivate();
                window->w[i][9]->deactivate();
                return;
            }
        }
    }
}

MemoryEditor::MemoryEditor(int X, int Y, int W, int H, const std::vector<Yaesu::FT891::Commands::MemoryChannelTagValue> &channels, const char *L) : Fl_Scroll(X, Y, W, H, L),m_newChannel(nullptr)
{
    int colx = 100;
    int colh = 30;
    int xx = X, yy = Y;
    m_channels = channels;
    channelNames.reserve(119);

  
        w = (Fl_Widget ***)new void *[118][10];
        for (int i = 0; i < 118; i++)
        {
            w[i] = (Fl_Widget **)new void *[10];
        }

        static const char *header[10] = {
            "", "Channel", "Freqency", "ClarifierValue", "ClarifierState",
            "Mode", "CTCSS", "RepeaterMode", "Name", "Channel Name"};

        Fl_Tile *tile = new Fl_Tile(X, Y, colx * 10, colh * 118, "");
        for (int i = 0; i < 10; i++)
        {
            Fl_Box *box = new Fl_Box(xx + (i * colx), yy, colx, colh, header[i]);
            box->box(FL_BORDER_BOX);
        }

        int channelidx = 1;
        yy += colh;
        for (int i = 1; i < (int)Yaesu::FT891::Commands::MemoryChannelValue::P9U; i++)
        {
            Yaesu::FT891::Commands::MemoryChannelTagValue val;
            std::vector<Yaesu::FT891::Commands::MemoryChannelTagValue>::iterator ix = m_channels.end();
            if ((ix = std::find_if(m_channels.begin(), m_channels.end(), [i](Yaesu::FT891::Commands::MemoryChannelTagValue e)
                                   { return static_cast<int>(e.MemoryChannel) == i; })) != m_channels.end())
            {

                std::string channelString = Yaesu::FT891::Commands::DisplayMemoryChannelValue(ix->MemoryChannel);
                // Channel
                channelNames.push_back(channelString.substr(7, channelString.length() - 7));

                Fl_Check_Button *Enabled = new Fl_Check_Button(xx, yy, colx, colh, "");
                Enabled->callback((Fl_Callback *)&OnChannnelEnabled, this);
                Enabled->value(1);
                w[i][0] = Enabled;

                xx += colx;

                Fl_Box *box = new Fl_Box(xx, yy, colx, colh, channelNames.back().c_str());
                box->box(FL_BORDER_BOX);
                w[i][1] = box;

                xx += colx;

                // Frequency
                frequencies.push_back(Yaesu::FT891::Commands::DisplayFrequency(ix->VFOAFreq));
                Fl_Input *freq = new Fl_Input(xx, yy, colx, colh);
                freq->box(FL_BORDER_BOX);
                freq->value(frequencies.back().c_str());
                freq->callback((Fl_Callback *)&OnFreqInput, this);
                freq->when(FL_KEYUP);
                w[i][2] = freq;
                xx += colx;

                // ClarifierValue
                clarifiervalues.push_back(fmt::format("{0}", ix->ClarifierFreq));
                Fl_Input *clar = new Fl_Input(xx, yy, colx, colh);
                clar->value(clarifiervalues.back().c_str());
                w[i][3] = clar;
                xx += colx;

                Fl_Choice *clarState = new Fl_Choice(xx, yy, colx, colh);
                clarState->add("ON", 0, OnMemoryEditorClarifierStateChange, this, 0);
                clarState->add("OFF", 0, OnMemoryEditorClarifierStateChange, this, 0);
                clarState->value(static_cast<int>(ix->Clarifier));
                w[i][4] = clarState;

                xx += colx;
                Fl_Choice *OperatingMode = new Fl_Choice(xx, yy, colx, colh, "");
                OperatingMode->add("LSB", 0, OnModeChange, this, 0);
                OperatingMode->add("USB", 0, OnModeChange, this, 0);
                OperatingMode->add("CW", 0, OnModeChange, this, 0);
                OperatingMode->add("FM", 0, OnModeChange, this, 0);
                OperatingMode->add("AM", 0, OnModeChange, this, 0);
                OperatingMode->add("RTTY_LSB", 0, OnModeChange, this, 0);
                OperatingMode->add("CW-R", 0, OnModeChange, this, 0);
                OperatingMode->add("DATA-LSB", 0, OnModeChange, this, 0);
                OperatingMode->add("RTTY-USB", 0, OnModeChange, this, 0);
                OperatingMode->add("-", 0, OnModeChange, this, 0);
                OperatingMode->add("FM-N", 0, OnModeChange, this, 0);
                OperatingMode->add("DATA-USB", 0, OnModeChange, this, 0);
                OperatingMode->add("AM-N", 0, OnModeChange, this, 0);
                OperatingMode->value(static_cast<int>(ix->Mode) - 1);
                OperatingMode->callback((Fl_Callback*)&OnModeChange, this);
                w[i][5] = OperatingMode;

                xx += colx;

                Fl_Choice *CTCSS = new Fl_Choice(xx, yy, colx, colh, "");
                CTCSS->add("OFF", 0, OnMemoryEditorOperatingMode, this, 0);
                CTCSS->add("ENC/DEC", 0, OnMemoryEditorOperatingMode, this, 0);
                CTCSS->add("ENC", 0, OnMemoryEditorOperatingMode, this, 0);
                CTCSS->value(static_cast<int>(ix->CTCSS));
                w[i][6] = CTCSS;

                xx += colx;

                Fl_Choice *RepeaterMode = new Fl_Choice(xx, yy, colx, colh, "");
                RepeaterMode->add("Simplex", 0, OnMemoryEditorOperatingMode, this, 0);
                RepeaterMode->add("Plus Shift", 0, OnMemoryEditorOperatingMode, this, 0);
                RepeaterMode->add("Minus Shift", 0, OnMemoryEditorOperatingMode, this, 0);
                RepeaterMode->value(static_cast<int>(ix->Operation));
                RepeaterMode->callback((Fl_Callback*)&OnRepeaterMode, this);
                w[i][7] = RepeaterMode;

                xx += colx;

                Fl_Check_Button *TagOnOff = new Fl_Check_Button(xx, yy, colx, colh, "");
                TagOnOff->callback((Fl_Callback *)&OnMemoryEditorTag, this);
                TagOnOff->value(static_cast<int>(ix->TAG));
                w[i][8] = TagOnOff;

                xx += colx;
                Fl_Input *tag = new Fl_Input(xx, yy, colx, colh);
                tag->callback((Fl_Callback *)&OnTagEdit, this);
                tag->box(FL_BORDER_BOX);
                w[i][9] = tag;
                if (ix->TAG == Yaesu::FT891::Commands::TagValue::ON)
                    tag->value(ix->TagString.c_str());

                if (ix->TAG == Yaesu::FT891::Commands::TagValue::OFF)
                {
                    tag->deactivate();
                }
                else
                {
                    tag->activate();
                }
            }
            else
            {
                Fl_Check_Button *Enabled = new Fl_Check_Button(xx, yy, colx, colh, "");
                Enabled->callback((Fl_Callback *)&OnChannnelEnabled, this);
                Enabled->value(0);
                w[i][0] = Enabled;

                xx += colx;

                std::string channelName = Yaesu::FT891::Commands::DisplayMemoryChannelValue(static_cast<Yaesu::FT891::Commands::MemoryChannelValue>(i));
                if (channelName.find("Channel") != std::string::npos)
                    channelName = channelName.replace(0, 7, "");
                channelNames.push_back(channelName);
                Fl_Box *box = new Fl_Box(xx, yy, colx, colh, channelNames.back().c_str());
                box->box(FL_BORDER_BOX);
                box->deactivate();
                w[i][1] = box;

                xx += colx;

                // Frequency                
                frequencies.emplace_back("");
                Fl_Input *freq = new Fl_Input(xx, yy, colx, colh);
                freq->box(FL_BORDER_BOX);
                freq->value(frequencies.back().c_str());
                freq->deactivate();
                w[i][2] = freq;

                xx += colx;

                // ClarifierValue
                clarifiervalues.push_back(fmt::format("{0}", 0));
                Fl_Input *clar = new Fl_Input(xx, yy, colx, colh);
                clar->value(clarifiervalues.back().c_str());
                clar->deactivate();
                w[i][3] = clar;

                xx += colx;

                Fl_Choice *clarState = new Fl_Choice(xx, yy, colx, colh);
                clarState->add("ON", 0, OnMemoryEditorClarifierStateChange, this, 0);
                clarState->add("OFF", 0, OnMemoryEditorClarifierStateChange, this, 0);
                clarState->value(static_cast<int>(Yaesu::FT891::Commands::ClarifierState::OFF));
                clarState->deactivate();
                w[i][4] = clarState;

                xx += colx;
                Fl_Choice *OperatingMode = new Fl_Choice(xx, yy, colx, colh, "");
                OperatingMode->add("LSB", 0, OnMemoryEditorOperatingMode, this, 0);
                OperatingMode->add("USB", 0, OnMemoryEditorOperatingMode, this, 0);
                OperatingMode->add("CW", 0, OnMemoryEditorOperatingMode, this, 0);
                OperatingMode->add("FM", 0, OnMemoryEditorOperatingMode, this, 0);
                OperatingMode->add("AM", 0, OnMemoryEditorOperatingMode, this, 0);
                OperatingMode->add("RTTY_LSB", 0, OnMemoryEditorOperatingMode, this, 0);
                OperatingMode->add("CW-R", 0, OnMemoryEditorOperatingMode, this, 0);
                OperatingMode->add("DATA-LSB", 0, OnMemoryEditorOperatingMode, this, 0);
                OperatingMode->add("RTTY-USB", 0, OnMemoryEditorOperatingMode, this, 0);
                OperatingMode->add("-", 0, OnMemoryEditorOperatingMode, this, 0);
                OperatingMode->add("FM-N", 0, OnMemoryEditorOperatingMode, this, 0);
                OperatingMode->add("DATA-USB", 0, OnMemoryEditorOperatingMode, this, 0);
                OperatingMode->add("AM-N", 0, OnMemoryEditorOperatingMode, this, 0);
                OperatingMode->value(static_cast<int>(9));
                OperatingMode->callback((Fl_Callback*)&OnModeChange, this);
                w[i][5] = OperatingMode;
                OperatingMode->deactivate();

                xx += colx;

                Fl_Choice *CTCSS = new Fl_Choice(xx, yy, colx, colh, "");
                CTCSS->add("OFF", 0, OnMemoryEditorOperatingMode, this, 0);
                CTCSS->add("ENC/DEC", 0, OnMemoryEditorOperatingMode, this, 0);
                CTCSS->add("ENC", 0, OnMemoryEditorOperatingMode, this, 0);
                CTCSS->value(static_cast<int>(0));
                CTCSS->deactivate();
                w[i][6] = CTCSS;

                xx += colx;

                Fl_Choice *RepeaterMode = new Fl_Choice(xx, yy, colx, colh, "");
                RepeaterMode->add("Simplex", 0, OnMemoryEditorOperatingMode, this, 0);
                RepeaterMode->add("Plus Shift", 0, OnMemoryEditorOperatingMode, this, 0);
                RepeaterMode->add("Minus Shift", 0, OnMemoryEditorOperatingMode, this, 0);
                RepeaterMode->value(static_cast<int>(0));
                RepeaterMode->deactivate();
                RepeaterMode->callback((Fl_Callback*)&OnRepeaterMode, this);
                w[i][7] = RepeaterMode;

                xx += colx;

                Fl_Check_Button *TagOnOff = new Fl_Check_Button(xx, yy, colx, colh, "");
                TagOnOff->callback((Fl_Callback *)&OnMemoryEditorTag, this);
                TagOnOff->value(static_cast<int>(0));
                TagOnOff->deactivate();
                w[i][8] = TagOnOff;

                xx += colx;
                Fl_Input *tag = new Fl_Input(xx, yy, colx, colh);
                tag->callback((Fl_Callback *)&OnTagEdit, this);
                tag->box(FL_BORDER_BOX);
                tag->deactivate();
                w[i][9] = tag;
            }

            yy += colh;
            xx = X;
        }

        tile->end();
        this->end();
    
}

MemoryEditor::MemoryEditor(int X, 
                           int Y, 
                           int W, 
                           int H, 
                           const std::vector<Yaesu::FT891::Commands::MemoryChannelTagValue> &channels, 
                           Yaesu::FT891::Commands::MemoryChannelTagValue* newChannel,
                           const char *L) : Fl_Scroll(X, Y, W, H, L), m_newChannel(newChannel)
{
    int colx = 100;
    int colh = 30;
    int xx = X, yy = Y;
    m_channels = channels;
    channelNames.reserve(119);
    



        w = (Fl_Widget ***)new void *[118][10];
        for (int i = 0; i < 118; i++)
        {
            w[i] = (Fl_Widget **)new void *[10];
        }

        static const char *header[10] = {
            "", "Channel", "Freqency", "ClarifierValue", "ClarifierState",
            "Mode", "CTCSS", "RepeaterMode", "Name", "Channel Name"};

        Fl_Tile *tile = new Fl_Tile(X, Y, colx * 10, colh * 118, "");
        for (int i = 0; i < 10; i++)
        {
            Fl_Box *box = new Fl_Box(xx + (i * colx), yy, colx, colh, header[i]);
            box->box(FL_BORDER_BOX);
        }

        int channelidx = 1;
        yy += colh;
        for (int i = 1; i < (int)Yaesu::FT891::Commands::MemoryChannelValue::P9U; i++)
        {
            Yaesu::FT891::Commands::MemoryChannelTagValue val;
            std::vector<Yaesu::FT891::Commands::MemoryChannelTagValue>::iterator ix = m_channels.end();
            if ((ix = std::find_if(m_channels.begin(), m_channels.end(), [i](Yaesu::FT891::Commands::MemoryChannelTagValue e)
                                   { return static_cast<int>(e.MemoryChannel) == i; })) != m_channels.end())
            {

                std::string channelString = Yaesu::FT891::Commands::DisplayMemoryChannelValue(ix->MemoryChannel);
                // Channel
                channelNames.push_back(channelString.substr(7, channelString.length() - 7));

                Fl_Check_Button *Enabled = new Fl_Check_Button(xx, yy, colx, colh, "");
                Enabled->callback((Fl_Callback *)&OnChannnelEnabled, this);
                Enabled->value(1);
                w[i][0] = Enabled;

                xx += colx;

                Fl_Box *box = new Fl_Box(xx, yy, colx, colh, channelNames.back().c_str());
                box->box(FL_BORDER_BOX);
                w[i][1] = box;

                xx += colx;

                // Frequency
                frequencies.push_back(Yaesu::FT891::Commands::DisplayFrequency(ix->VFOAFreq));
                Fl_Input *freq = new Fl_Input(xx, yy, colx, colh);
                freq->box(FL_BORDER_BOX);
                freq->value(frequencies.back().c_str());
                freq->callback((Fl_Callback*)&OnFreqInput,this);
                w[i][2] = freq;
                xx += colx;

                // ClarifierValue
                clarifiervalues.push_back(fmt::format("{0}", ix->ClarifierFreq));
                Fl_Input *clar = new Fl_Input(xx, yy, colx, colh);
                clar->value(clarifiervalues.back().c_str());
                w[i][3] = clar;
                xx += colx;

                Fl_Choice *clarState = new Fl_Choice(xx, yy, colx, colh);
                clarState->add("OFF", 0, OnMemoryEditorClarifierStateChange, this, 0);
                clarState->add("ON", 0, OnMemoryEditorClarifierStateChange, this, 0);
                clarState->value(static_cast<int>(ix->Clarifier));
                w[i][4] = clarState;

                xx += colx;
                Fl_Choice *OperatingMode = new Fl_Choice(xx, yy, colx, colh, "");
                OperatingMode->add("LSB", 0, OnModeChange, this, 0);
                OperatingMode->add("USB", 0, OnModeChange, this, 0);
                OperatingMode->add("CW", 0, OnModeChange, this, 0);
                OperatingMode->add("FM", 0, OnModeChange, this, 0);
                OperatingMode->add("AM", 0, OnModeChange, this, 0);
                OperatingMode->add("RTTY_LSB", 0, OnModeChange, this, 0);
                OperatingMode->add("CW-R", 0, OnModeChange, this, 0);
                OperatingMode->add("DATA-LSB", 0, OnModeChange, this, 0);
                OperatingMode->add("RTTY-USB", 0, OnModeChange, this, 0);
                OperatingMode->add("-", 0, OnModeChange, this, 0);
                OperatingMode->add("FM-N", 0, OnModeChange, this, 0);
                OperatingMode->add("DATA-USB", 0, OnModeChange, this, 0);
                OperatingMode->add("AM-N", 0, OnModeChange, this, 0);
                OperatingMode->value(static_cast<int>(ix->Mode) - 1);
                OperatingMode->callback((Fl_Callback*)&OnModeChange, this);
                w[i][5] = OperatingMode;

                xx += colx;

                Fl_Choice *CTCSS = new Fl_Choice(xx, yy, colx, colh, "");
                CTCSS->add("OFF", 0, OnMemoryEditorOperatingMode, this, 0);
                CTCSS->add("ENC/DEC", 0, OnMemoryEditorOperatingMode, this, 0);
                CTCSS->add("ENC", 0, OnMemoryEditorOperatingMode, this, 0);
                CTCSS->value(static_cast<int>(ix->CTCSS));
                w[i][6] = CTCSS;

                xx += colx;

                Fl_Choice *RepeaterMode = new Fl_Choice(xx, yy, colx, colh, "");
                RepeaterMode->add("Simplex", 0, OnMemoryEditorOperatingMode, this, 0);
                RepeaterMode->add("Plus Shift", 0, OnMemoryEditorOperatingMode, this, 0);
                RepeaterMode->add("Minus Shift", 0, OnMemoryEditorOperatingMode, this, 0);
                RepeaterMode->value(static_cast<int>(ix->Operation));
                RepeaterMode->callback((Fl_Callback*)&OnRepeaterMode, this);
                w[i][7] = RepeaterMode;

                xx += colx;

                Fl_Check_Button *TagOnOff = new Fl_Check_Button(xx, yy, colx, colh, "");
                TagOnOff->callback((Fl_Callback *)&OnMemoryEditorTag, this);
                TagOnOff->value(static_cast<int>(ix->TAG));
                w[i][8] = TagOnOff;

                xx += colx;
                Fl_Input *tag = new Fl_Input(xx, yy, colx, colh);
                tag->callback((Fl_Callback *)&OnTagEdit, this);
                tag->box(FL_BORDER_BOX);
                w[i][9] = tag;
                if (ix->TAG == Yaesu::FT891::Commands::TagValue::ON)
                    tag->value(ix->TagString.c_str());

                if (ix->TAG == Yaesu::FT891::Commands::TagValue::OFF)
                {
                    tag->deactivate();
                }
                else
                {
                    tag->activate();
                }
            }
            else
            {
                Fl_Check_Button *Enabled = new Fl_Check_Button(xx, yy, colx, colh, "");
                Enabled->callback((Fl_Callback *)&OnChannnelEnabled, this);
                Enabled->value(0);
                w[i][0] = Enabled;

                xx += colx;

                std::string channelName = Yaesu::FT891::Commands::DisplayMemoryChannelValue(static_cast<Yaesu::FT891::Commands::MemoryChannelValue>(i));
                if (channelName.find("Channel") != std::string::npos)
                    channelName = channelName.replace(0, 7, "");
                channelNames.push_back(channelName);
                Fl_Box *box = new Fl_Box(xx, yy, colx, colh, channelNames.back().c_str());
                box->box(FL_BORDER_BOX);
                box->deactivate();
                w[i][1] = box;

                xx += colx;

                // Frequency
                frequencies.push_back("");
                Fl_Input *freq = new Fl_Input(xx, yy, colx, colh);
                freq->box(FL_BORDER_BOX);
                freq->value(frequencies.back().c_str());
                freq->deactivate();
                w[i][2] = freq;

                xx += colx;

                // ClarifierValue
                clarifiervalues.push_back(fmt::format("{0}", 0));
                Fl_Input *clar = new Fl_Input(xx, yy, colx, colh);
                clar->value(clarifiervalues.back().c_str());
                clar->deactivate();
                w[i][3] = clar;

                xx += colx;

                Fl_Choice *clarState = new Fl_Choice(xx, yy, colx, colh);
                clarState->add("OFF", 0, OnMemoryEditorClarifierStateChange, this, 0);
                clarState->add("ON", 0, OnMemoryEditorClarifierStateChange, this, 0);
                clarState->value(static_cast<int>(Yaesu::FT891::Commands::ClarifierState::OFF));
                clarState->deactivate();
                w[i][4] = clarState;

                xx += colx;
                Fl_Choice *OperatingMode = new Fl_Choice(xx, yy, colx, colh, "");
                OperatingMode->add("LSB", 0, OnModeChange, this, 0);
                OperatingMode->add("USB", 0, OnModeChange, this, 0);
                OperatingMode->add("CW", 0, OnModeChange, this, 0);
                OperatingMode->add("FM", 0, OnModeChange, this, 0);
                OperatingMode->add("AM", 0, OnModeChange, this, 0);
                OperatingMode->add("RTTY_LSB", 0, OnModeChange, this, 0);
                OperatingMode->add("CW-R", 0, OnModeChange, this, 0);
                OperatingMode->add("DATA-LSB", 0, OnModeChange, this, 0);
                OperatingMode->add("RTTY-USB", 0, OnModeChange, this, 0);
                OperatingMode->add("-", 0, OnModeChange, this, 0);
                OperatingMode->add("FM-N", 0, OnModeChange, this, 0);
                OperatingMode->add("DATA-USB", 0, OnModeChange, this, 0);
                OperatingMode->add("AM-N", 0, OnModeChange, this, 0);
                OperatingMode->value(static_cast<int>(9));         
                w[i][5] = OperatingMode;
                OperatingMode->deactivate();

                xx += colx;

                Fl_Choice *CTCSS = new Fl_Choice(xx, yy, colx, colh, "");
                CTCSS->add("OFF", 0, OnMemoryEditorCTCSS, this, 0);
                CTCSS->add("ENC/DEC", 0, OnMemoryEditorCTCSS, this, 0);
                CTCSS->add("ENC", 0, OnMemoryEditorCTCSS, this, 0);
                CTCSS->value(static_cast<int>(0));
                CTCSS->deactivate();
                w[i][6] = CTCSS;

                xx += colx;

                Fl_Choice *RepeaterMode = new Fl_Choice(xx, yy, colx, colh, "");
                RepeaterMode->add("Simplex", 0, OnMemoryEditorOperatingMode, this, 0);
                RepeaterMode->add("Plus Shift", 0, OnMemoryEditorOperatingMode, this, 0);
                RepeaterMode->add("Minus Shift", 0, OnMemoryEditorOperatingMode, this, 0);
                RepeaterMode->value(static_cast<int>(0));
                RepeaterMode->deactivate();
                RepeaterMode->callback((Fl_Callback*)&OnRepeaterMode, this);
                w[i][7] = RepeaterMode;

                xx += colx;

                Fl_Check_Button *TagOnOff = new Fl_Check_Button(xx, yy, colx, colh, "");
                TagOnOff->callback((Fl_Callback *)&OnMemoryEditorTag, this);
                TagOnOff->value(static_cast<int>(0));
                TagOnOff->deactivate();
                w[i][8] = TagOnOff;

                xx += colx;
                Fl_Input *tag = new Fl_Input(xx, yy, colx, colh);
                tag->callback((Fl_Callback *)&OnTagEdit, this);
                tag->box(FL_BORDER_BOX);
                tag->deactivate();
                w[i][9] = tag;
            }

            yy += colh;
            xx = X;
        }

        tile->end();
        this->end();
    
}