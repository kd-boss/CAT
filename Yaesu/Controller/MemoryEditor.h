#ifndef MemoryEditor_H
#define MemoryEditor_H
#include <FL\Fl.H>
#include <FL\Fl_Double_Window.H>
#include <FL\Fl_Scroll.H>
#include <FL\Fl_Choice.H>
#include <FL\Fl_Input.H>
#include <FL\Fl_Float_Input.H>
#include <FL\Fl_Box.H>
#include <FL\Fl_Button.H>
#include <FL\Fl_Tile.H>
#include <FL\Fl_Check_Button.H>
#include <vector>
#include "..\CAT\Cat.h"


class MemoryEditor : public Fl_Scroll {
    public:
    std::vector<std::string> channelNames;
    std::vector<std::string> frequencies;
    std::vector<std::string> clarifiervalues;
    Yaesu::FT891::Commands::MemoryChannelTagValue* m_newChannel;
    std::vector<Yaesu::FT891::Commands::MemoryChannelTagValue> m_channels;    
    MemoryEditor(int X, int Y, int W, int H, const std::vector<Yaesu::FT891::Commands::MemoryChannelTagValue>& channels, const char* L);
    MemoryEditor(int X, int Y, int W, int H, const std::vector<Yaesu::FT891::Commands::MemoryChannelTagValue>& chanels, Yaesu::FT891::Commands::MemoryChannelTagValue* newChannel, const char* L);
    Fl_Button* Ok;
    Fl_Widget*** w;
    static char** names;
};
#endif