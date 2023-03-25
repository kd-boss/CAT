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
#include <algorithm>



class MemoryEditor : public Fl_Scroll {
    Fl_Tile* m_tile;
    int handle(int event);
    public:
    std::vector<std::string> channelNames;
    std::vector<std::string> frequencies;
    std::vector<std::string> clarifiervalues;
    Yaesu::Commands::FT891::MemoryChannelTagValue* m_newChannel;
    std::vector<Yaesu::Commands::FT891::MemoryChannelTagValue> m_channels;    
    MemoryEditor(int X, int Y, int W, int H, const std::vector<Yaesu::Commands::FT891::MemoryChannelTagValue>& channels, const char* L);
    MemoryEditor(int X, int Y, int W, int H, const std::vector<Yaesu::Commands::FT891::MemoryChannelTagValue>& chanels, Yaesu::Commands::FT891::MemoryChannelTagValue* newChannel, const char* L);
    Fl_Button* Ok;
    Fl_Widget*** w;
    static char** names;
    
};
#endif