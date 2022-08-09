#include "Cat.h"
#include <fmt/core.h>
#include <algorithm>
#include <cctype>
#include <locale>


namespace Yaesu
{
std::string IDENTIFICATION::Read()
{
    return "ID;";
}

RigType IDENTIFICATION::Answer(std::string data)
{
    return static_cast<Yaesu::RigType>(std::stoi(data.substr(2,4)));
}



    namespace Commands
    {
        namespace FT991 {
            std::string VFO_A_To_VFO_B::Set()
            {
                return "AB;";
            }
            
            std::string AntennaTunerControl::Set(AntennaTunerControlValue value)
            {
                return fmt::format("AC00{:1d};",static_cast<int>(value));
            }
            
            std::string AntennaTunerControl::Read()
            {
                return "AC;";
            }
            
            AntennaTunerControlValue AntennaTunerControl::Answer(std::string data)
            {
                return static_cast<AntennaTunerControlValue>(std::stoi(data.substr(4,1)));
            }
            
            std::string AF_GAIN::Set(int value)
            {   
               return fmt::format("AG0{:03d};",value);     
            }
            
            std::string AF_GAIN::Read()
            {
                return "AG0;";
            }
            
            int AF_GAIN::Answer(std::string data)
            {   
                return std::stoi(data.substr(3,3));
            }
            
            std::string AutoInformation::Set(OnOffValue value)
            {
                return fmt::format("AI{:1d};", static_cast<int>(value));
            }
            
            std::string AutoInformation::Read()
            {
                return "AI;";
            }
            
            OnOffValue AutoInformation::Answer(std::string data)
            {
                return static_cast<OnOffValue>(std::stoi(data.substr(2,1)));
            }
            
            std::string VFO_A_To_Memory::Set()
            {
                return "AM;";
            }

            std::string VFO_B_To_VFO_A::Set()
            {
                return "BA;";
            }

            std::string AutoNotch::Set(OnOffValue value)
            {
                return fmt::format("BC0{:1d};", static_cast<int>(value));
            }
            
            std::string AutoNotch::Read()
            {
                return "BC0;";
            }
            
            OnOffValue AutoNotch::Answer(std::string data)
            {
                return static_cast<OnOffValue>(std::stoi(data.substr(3,1)));
            }
            
            std::string BandDown::Set()
            {
                return "BD0;";
            }

            std::string BreakIn::Set(OnOffValue value)
            {
                return fmt::format("BI{:1d};",static_cast<int>(value));
            }
            
            std::string BreakIn::Read()
            {
                return "BI;";
            }
            
            OnOffValue BreakIn::Answer(std::string data)
            {
                return static_cast<OnOffValue>(std::stoi(data.substr(2,1)));
            }
            
            std::string ManualNotch::Set(ManualNotchValueType value)   
            {
                switch(value.Type)
                {
                    case ManualNotchType::OnOff:
                    {
                        return fmt::format("BP0{:1d}{:03d};",
                            static_cast<int>(value.Type),
                            static_cast<int>(value.Value.State));
                    }
                    case ManualNotchType::Level:
                    {
                    return fmt::format("BP0{:1d}{:03d};",
                        static_cast<int>(value.Type),
                        static_cast<int>(value.Value.Frequency));
                    }
                default:
                    return "";
                }
            }
            
            std::string ManualNotch::Read(ManualNotchType type)
            {
                return fmt::format("BP0{:1d};",static_cast<int>(type));
            }
            
            ManualNotchValueType ManualNotch::Answer(std::string data)
            {
                ManualNotchValueType ret;
                ret.Type = static_cast<ManualNotchType>(std::stoi(data.substr(3,1)));
                if(ret.Type == ManualNotchType::OnOff)
                {
                    ret.Value.State = static_cast<OnOffValue>(std::stoi(data.substr(4,3)));
                }
                else
                {
                    ret.Value.Frequency = std::stoi(data.substr(4,3));
                }
                return ret;
            }
            
            std::string BandSelect::Set(Band value)
            {
                return fmt::format("BS{:02};",static_cast<int>(value));
            }
            
            
            std::string BandUp::Set()
            {
                return "BU0;";
            }
            
            
            std::string Busy::Read()
            {
                return "BY;";
            }
            
            OnOffValue Busy::Answer(std::string data)
            {
                return static_cast<OnOffValue>(std::stoi(data.substr(3,1)));
            }
            
            std::string ChannelUpDown::Set(UpDownValue value)
            {
                return fmt::format("CH{:1d};",static_cast<int>(value));
            }

            std::string CTCSSToneFrequency::Set(CTCSSToneValue value)
            {
                return fmt::format("CN0{:01d}{:03d};",
                                  static_cast<int>(value.Type),
                                  value.Value);
            }
            
            std::string CTCSSToneFrequency::Read(CTCSSToneType type)
            {
                return fmt::format("CN0{:01d};",static_cast<int>(type));
            }
            
            CTCSSToneValue CTCSSToneFrequency::Answer(std::string data)
            {
                CTCSSToneValue ret;
                ret.Type = static_cast<CTCSSToneType>(std::stoi(data.substr(3,1)));
                ret.Value = std::stoi(data.substr(4,3));
                return ret;
            }
            
            std::string Countour::Set(CountourValue value)
            {
                switch(value.Type)
                {
                    case CountourType::CONTOUR_ONOFF:
                    {
                    return fmt::format("CO0{:01d}{:04d};",
                        static_cast<int>(value.Type),
                        static_cast<int>(value.Value.CountourState));
                    }
                    case CountourType::CONTOUR_FREQ:
                    {
                    return fmt::format("CO0{:01d}{:04d};",
                        static_cast<int>(value.Type),
                        static_cast<int>(value.Value.CountourFrequency));
                    }
                    case CountourType::APF_ONOFF:
                    {
                        return fmt::format("CO0{:01d}{:04d};",
                        static_cast<int>(value.Type),
                        static_cast<int>(value.Value.APFState));
                    }
                    case CountourType::APF_FREQ:
                    {
                        return fmt::format("CO0{:01d}{:04d};",
                        static_cast<int>(value.Type),
                        static_cast<int>(value.Value.APFFrequency));                                        
                    }
                default:
                    return "";
                }                
            }
            
            std::string Countour::Read(CountourType type)
            {
                return fmt::format("CO0{:01d};",static_cast<int>(type));                
            }
            
            CountourValue Countour::Answer(std::string data)
            {
                CountourValue ret;
                ret.Type = static_cast<CountourType>(std::stoi(data.substr(3,1)));
                switch(ret.Type)
                {
                     case CountourType::CONTOUR_ONOFF: 
                        ret.Value.CountourState = static_cast<OnOffValue>(std::stoi(data.substr(4,4)));
                     break;
                     case CountourType::CONTOUR_FREQ:
                         ret.Value.CountourFrequency = std::stoi(data.substr(4,4));
                     break;
                     case CountourType::APF_ONOFF:
                          ret.Value.APFState = static_cast<OnOffValue>(std::stoi(data.substr(4,4)));
                     break;
                     case CountourType::APF_FREQ:
                          ret.Value.APFFrequency = std::stoi(data.substr(4,4));
                     break;
                }
                return ret;
            }

            std::string CWSpot::Set(OnOffValue value)
            {
                return fmt::format("CS{:01d};",static_cast<int>(value));
            }
            
            std::string CWSpot::Read()
            {
                return "CS;";
            }
            
            OnOffValue CWSpot::Answer(std::string data)
            {
                return static_cast<OnOffValue>(std::stoi(data.substr(2,1)));
            }
            
            std::string CTCSS::Set(CTCSSType value)
            {
                return fmt::format("CT0{:01d};", static_cast<int>(value));
            }
            
            std::string CTCSS::Read()
            {
                return "CT0;";
            }
            
            CTCSSType CTCSS::Answer(std::string data)
            {
                return static_cast<CTCSSType>(std::stoi(data.substr(3,1)));
            }
            
            std::string DIMMER::Set(DimmerValue value)
            {
                return fmt::format("DA00{:02d}{:02d};", value.LED, value.TFT);
            }
            
            std::string DIMMER::Read()
            {
                return "DA;";
            }
            
            DimmerValue DIMMER::Answer(std::string data)
            {
                DimmerValue ret;
                ret.LED = std::stoi(data.substr(4,2));
                ret.TFT = std::stoi(data.substr(6,2));
                return ret;
            }
            std::string MIC_DWN::Set()
            {
                return "DN;";
            }

            std::string DateAndTime::Set(DateTimeValue value)
            {
                return fmt::format("DT{:01d}{}", static_cast<int>(value.Type), value.Value);
            }
            
            std::string DateAndTime::Read(DateTimeType type)
            {
                return fmt::format("DT{:01d};",static_cast<int>(type));
            }
            
            DateTimeValue DateAndTime::Answer(std::string data)
            {
                DateTimeValue ret;
                ret.Type = static_cast<DateTimeType>(std::stoi(data.substr(2,1)));
                ret.Value = data.substr(3,data.find(";",3));
                return ret;
            }
            
            std::string EncoderDown::Set(EncoderValue value)
            {
                return fmt::format("ED{:01d}{:02d};",
                    static_cast<int>(value.Type),
                    value.Steps);
            }

            std::string ENT_KEY::Set()
            {
                return "EK;";
            }

            std::string EncoderUp::Set(EncoderValue value)
            {
                 return fmt::format("EU{:01d}{:02d};",
                    static_cast<int>(value.Type),
                    value.Steps);
            }



            std::string Menu::AGC_FAST_DELAY::Set(int value)
            {
                return fmt::format("EX{:03d}{:04};",
                static_cast<int>(MenuFunction::AGC_FAST_DELAY),
                value);
            }
            
            std::string Menu::AGC_FAST_DELAY::Read()
            {
                return fmt::format("EX{:03d};", static_cast<int>(MenuFunction::AGC_FAST_DELAY));
            }
            
            int Menu::AGC_FAST_DELAY::Answer(std::string data)
            {
                return std::stoi(data.substr(5,4));
            }

            std::string Menu::AGC_MID_DELAY::Set(int value)
            {
                return fmt::format("EX{:03d}{:04};",
                static_cast<int>(MenuFunction::AGC_MID_DELAY),
                value);
            }
            
            std::string Menu::AGC_MID_DELAY::Read()
            {
                return fmt::format("EX{:03d};", static_cast<int>(MenuFunction::AGC_MID_DELAY));
            }
            
            int Menu::AGC_MID_DELAY::Answer(std::string data)
            {
                return std::stoi(data.substr(5,4));
            }
           
            std::string Menu::AGC_SLOW_DELAY::Set(int value)
            {
                return fmt::format("EX{:03d}{:04};",
                static_cast<int>(MenuFunction::AGC_SLOW_DELAY),
                value);
            }
            
            std::string Menu::AGC_SLOW_DELAY::Read()
            {
                return fmt::format("EX{:03d};", static_cast<int>(MenuFunction::AGC_SLOW_DELAY));
            }
            
            int Menu::AGC_SLOW_DELAY::Answer(std::string data)
            {
                return std::stoi(data.substr(5,4));
            }

            std::string Menu::HOME_FUNCTION::Set(HomeFunction value)
            {
                return fmt::format("EX{:03d}{:01d};", 
                                  static_cast<int>(MenuFunction::HOME),
                                  static_cast<int>(value));
            }
            
            std::string Menu::HOME_FUNCTION::Read()
            {
                return fmt::format("EX{:03d};", static_cast<int>(MenuFunction::HOME));
            }
            
            HomeFunction Menu::HOME_FUNCTION::Answer(std::string data)
            {
                return static_cast<HomeFunction>(std::stoi(data.substr(5,1)));
            }
            
            std::string Menu::MY_CALL_INDICATION::Set(int value)
            {
            return fmt::format("EX{:03d}{:01d};",
            static_cast<int>(MenuFunction::MY_CALL_INDICATION),
            static_cast<int>(value)); 
            }
            
            std::string Menu::MY_CALL_INDICATION::Read()
            {
            return fmt::format("EX{:03d};",
            static_cast<int>(MenuFunction::MY_CALL_INDICATION));
            }
            
            int Menu::MY_CALL_INDICATION::Answer(std::string data)
            {
            return static_cast<int>(std::stoi(data.substr(5,1)));
            }
            

            std::string Menu::DISPLAY_COLOR::Set(DisplayColorType value)
            {
                return fmt::format("EX{:03d}{:01d};",
                                    static_cast<int>(MenuFunction::DISPLAY_COLOR),
                                    static_cast<int>(value));          
            }
            
            std::string Menu::DISPLAY_COLOR::Read()
            {
                 return fmt::format("EX{:03d};",
                                    static_cast<int>(MenuFunction::DISPLAY_COLOR));
            }
            
            DisplayColorType Menu::DISPLAY_COLOR::Answer(std::string data)
            {
                return static_cast<DisplayColorType>(std::stoi(data.substr(5,1)));
            }
            
            std::string Menu::DIMMER_LED::Set(int value)
            {
                return fmt::format("EX{:03d}{:01d};",
                                    static_cast<int>(MenuFunction::DIMMER_LED
                                    ),
                                    value);       
            }
            
            std::string Menu::DIMMER_LED::Read()
            {
                 return fmt::format("EX{:03d};",
                                    static_cast<int>(MenuFunction::DIMMER_LED));
            }
            
            int Menu::DIMMER_LED::Answer(std::string data)
            {
                return std::stoi(data.substr(5,1));
            }
            

            std::string Menu::DIMMER_TFT::Set(int value)
            {
                return fmt::format("EX{:03d}{:02d};",
                                    static_cast<int>(MenuFunction::DIMMER_TFT
                                    ),
                                    value);       
            }
            
            std::string Menu::DIMMER_TFT::Read()
            {
                 return fmt::format("EX{:03d};",
                                    static_cast<int>(MenuFunction::DIMMER_TFT));
            }
            
            int Menu::DIMMER_TFT::Answer(std::string data)
            {
                return std::stoi(data.substr(5,2));
            }
            
            std::string Menu::BAR_MTR_PEAK_HOLD::Set(MeterHoldType value)
            {
                  return fmt::format("EX{:03d}{:01d};",
                                    static_cast<int>(MenuFunction::BAR_MTR_PEAK_HOLD),
                                    static_cast<int>(value)); 
            }
            
            std::string Menu::BAR_MTR_PEAK_HOLD::Read()
            {
             return fmt::format("EX{:03d};",
                                    static_cast<int>(MenuFunction::BAR_MTR_PEAK_HOLD));  
            }
            
            MeterHoldType Menu::BAR_MTR_PEAK_HOLD::Answer(std::string data)
            {
              return static_cast<MeterHoldType>(std::stoi(data.substr(5,1)));
            }
            
            std::string Menu::DVS_RX_OUT_LEVEL::Set(int value)
            {
                 return fmt::format("EX{:03d}{:03d};",
                                    static_cast<int>(MenuFunction::DVS_RX_OUT_LEVEL),
                                    static_cast<int>(value)); 
            }
            
            std::string Menu::DVS_RX_OUT_LEVEL::Read()
            {
                return fmt::format("EX{:03d};",
                                    static_cast<int>(MenuFunction::DVS_RX_OUT_LEVEL));  
            }
            
            int Menu::DVS_RX_OUT_LEVEL::Answer(std::string data)
            {
                 return std::stoi(data.substr(5,3));
            }
            
            std::string Menu::DVS_TX_OUT_LEVEL::Set(int value)
            {
                 return fmt::format("EX{:03d}{:03d};",
                                    static_cast<int>(MenuFunction::DVS_TX_OUT_LEVEL),
                                    static_cast<int>(value)); 
            }
            
            std::string Menu::DVS_TX_OUT_LEVEL::Read()
            {
                return fmt::format("EX{:03d};",
                                    static_cast<int>(MenuFunction::DVS_TX_OUT_LEVEL));  
            }
            
            int Menu::DVS_TX_OUT_LEVEL::Answer(std::string data)
            {
                 return std::stoi(data.substr(5,3));
            }
            
            std::string Menu::KEYER_TYPE::Set(KeyerType value)
            {
                 return fmt::format("EX{:03d}{:01d};",
                                    static_cast<int>(MenuFunction::KEYER_TYPE),
                                    static_cast<int>(value)); 
            }
            
            std::string Menu::KEYER_TYPE::Read()
            {
                 return fmt::format("EX{:03d};",
                                    static_cast<int>(MenuFunction::KEYER_TYPE)); 
            }
            
            KeyerType Menu::KEYER_TYPE::Answer(std::string data)
            {
                return static_cast<KeyerType>(std::stoi(data.substr(5,1)));
            }
            
            std::string Menu::KEYER_DOTDASH::Set(KeyerDotDashType value)
            {
                return fmt::format("EX{:03d}{:01d};",
                                    static_cast<int>(MenuFunction::KEYER_DOTDASH),
                                    static_cast<int>(value)); 
            }
            
            std::string Menu::KEYER_DOTDASH::Read()
            {
                 return fmt::format("EX{:03d};",
                                    static_cast<int>(MenuFunction::KEYER_DOTDASH)); 
            }
            
            KeyerDotDashType Menu::KEYER_DOTDASH::Answer(std::string data)
            {
                return static_cast<KeyerDotDashType>(std::stoi(data.substr(5,1)));
            }
            
            std::string Menu::CW_WEIGHT::Set(int value)
            {
                return fmt::format("EX{:03d}{:02d};",
                    static_cast<int>(MenuFunction::CW_WEIGHT),
                        static_cast<int>(value)); 
            }
            
            std::string Menu::CW_WEIGHT::Read()
            {
            return fmt::format("EX{:03d};",
                static_cast<int>(MenuFunction::CW_WEIGHT));
            }
            
            int Menu::CW_WEIGHT::Answer(std::string data)
            {
                return static_cast<int>(std::stoi(data.substr(5,2)));
            }
            
            std::string Menu::BEACON_INTERVAL::Set(int value)
            {
            return fmt::format("EX{:03d}{:03d};",
            static_cast<int>(MenuFunction::BEACON_INTERVAL),
            static_cast<int>(value)); 
            }
            
            std::string Menu::BEACON_INTERVAL::Read()
            {
            return fmt::format("EX{:03d};",
            static_cast<int>(MenuFunction::BEACON_INTERVAL));
            }
            
            int Menu::BEACON_INTERVAL::Answer(std::string data)
            {
            return static_cast<int>(std::stoi(data.substr(5,3)));
            }
            
            std::string Menu::NUMBER_STYLE::Set(NumberStyleType value)
            {
            return fmt::format("EX{:03d}{:01d};",
            static_cast<int>(MenuFunction::NUMBER_STYLE),
            static_cast<int>(value)); 
            }
            
            std::string Menu::NUMBER_STYLE::Read()
            {
            return fmt::format("EX{:03d};",
            static_cast<int>(MenuFunction::NUMBER_STYLE));
            }
            
            NumberStyleType Menu::NUMBER_STYLE::Answer(std::string data)
            {
            return static_cast<NumberStyleType>(std::stoi(data.substr(5,1)));
            }
            
            std::string Menu::CONTEST_NUMBER::Set(int value)
            {
            return fmt::format("EX{:03d}{:04d};",
            static_cast<int>(MenuFunction::CONTEST_NUMBER),
            static_cast<int>(value)); 
            }
            
            std::string Menu::CONTEST_NUMBER::Read()
            {
            return fmt::format("EX{:03d};",
            static_cast<int>(MenuFunction::CONTEST_NUMBER));
            }
            
            int Menu::CONTEST_NUMBER::Answer(std::string data)
            {
            return static_cast<int>(std::stoi(data.substr(5,4)));
            }
            
            std::string Menu::CW_MEMORY_1::Set(CwMemoryType value)
            {
            return fmt::format("EX{:03d}{:01d};",
            static_cast<int>(MenuFunction::CW_MEMORY_1),
            static_cast<int>(value)); 
            }
            
            std::string Menu::CW_MEMORY_1::Read()
            {
            return fmt::format("EX{:03d};",
            static_cast<int>(MenuFunction::CW_MEMORY_1));
            }
            
            CwMemoryType Menu::CW_MEMORY_1::Answer(std::string data)
            {
            return static_cast<CwMemoryType>(std::stoi(data.substr(5,1)));
            }
            

            std::string Menu::CW_MEMORY_2::Set(CwMemoryType value)
            {
            return fmt::format("EX{:03d}{:01d};",
            static_cast<int>(MenuFunction::CW_MEMORY_2),
            static_cast<int>(value)); 
            }
            
            std::string Menu::CW_MEMORY_2::Read()
            {
            return fmt::format("EX{:03d};",
            static_cast<int>(MenuFunction::CW_MEMORY_2));
            }
            
            CwMemoryType Menu::CW_MEMORY_2::Answer(std::string data)
            {
            return static_cast<CwMemoryType>(std::stoi(data.substr(5,1)));
            }

             std::string Menu::CW_MEMORY_3::Set(CwMemoryType value)
            {
            return fmt::format("EX{:03d}{:01d};",
            static_cast<int>(MenuFunction::CW_MEMORY_3),
            static_cast<int>(value)); 
            }
            
            std::string Menu::CW_MEMORY_3::Read()
            {
            return fmt::format("EX{:03d};",
            static_cast<int>(MenuFunction::CW_MEMORY_3));
            }
            
            CwMemoryType Menu::CW_MEMORY_3::Answer(std::string data)
            {
            return static_cast<CwMemoryType>(std::stoi(data.substr(5,1)));
            }

            std::string Menu::NB_WIDTH::Set(NbWidthType value)
            {
            return fmt::format("EX{:03d}{:01d};",
            static_cast<int>(MenuFunction::NB_WIDTH),
            static_cast<int>(value)); 
            }
            
            std::string Menu::NB_WIDTH::Read()
            {
            return fmt::format("EX{:03d};",
            static_cast<int>(MenuFunction::NB_WIDTH));
            }
            
            NbWidthType Menu::NB_WIDTH::Answer(std::string data)
            {
            return static_cast<NbWidthType>(std::stoi(data.substr(5,1)));
            }
            
            std::string Menu::NB_REJECTION::Set(NBRejectionType value)
            {
            return fmt::format("EX{:03d}{:01d};",
            static_cast<int>(MenuFunction::NB_REJECTION),
            static_cast<int>(value)); 
            }
            
            std::string Menu::NB_REJECTION::Read()
            {
            return fmt::format("EX{:03d};",
            static_cast<int>(MenuFunction::NB_REJECTION));
            }
            
            NBRejectionType Menu::NB_REJECTION::Answer(std::string data)
            {
                return static_cast<NBRejectionType>(std::stoi(data.substr(5,1)));
            }
            
            std::string Menu::NB_LEVEL::Set(int value)
            {
            return fmt::format("EX{:03d}{:02d};",
            static_cast<int>(MenuFunction::NB_LEVEL),
            static_cast<int>(value)); 
            }
            
            std::string Menu::NB_LEVEL::Read()
            {
            return fmt::format("EX{:03d};",
            static_cast<int>(MenuFunction::NB_LEVEL));
            }
            
            int Menu::NB_LEVEL::Answer(std::string data)
            {
            return static_cast<int>(std::stoi(data.substr(5,2)));
            }
            
            std::string Menu::TIME_ZONE::Set(std::string value)
            {
            return fmt::format("EX{:03d}{};",
            static_cast<int>(MenuFunction::TIME_ZONE),
            value);
            }
            
            std::string Menu::TIME_ZONE::Read()
            {
            return fmt::format("EX{:03d};",
            static_cast<int>(MenuFunction::TIME_ZONE));
            }
            
            std::string Menu::TIME_ZONE::Answer(std::string data)
            {
            return data.substr(5,5);
            }
            
            std::string Menu::GPS_RS232_SELECT::Set(GpsSelectType value)
            {
            return fmt::format("EX{:03d}{:01d};",
            static_cast<int>(MenuFunction::GPS_RS232_SELECT),
            static_cast<int>(value)); 
            }
            
            std::string Menu::GPS_RS232_SELECT::Read()
            {
            return fmt::format("EX{:03d};",
            static_cast<int>(MenuFunction::GPS_RS232_SELECT));
            }
            
            GpsSelectType Menu::GPS_RS232_SELECT::Answer(std::string data)
            {
            return static_cast<GpsSelectType>(std::stoi(data.substr(5,1)));
            }
            
            std::string Menu::RS232_RATE::Set(CatRate value)
            {
            return fmt::format("EX{:03d}{:01d};",
            static_cast<int>(MenuFunction::RS232_RATE),
            static_cast<int>(value)); 
            }
            
            std::string Menu::RS232_RATE::Read()
            {
            return fmt::format("EX{:03d};",
            static_cast<int>(MenuFunction::RS232_RATE));
            }
            
            CatRate Menu::RS232_RATE::Answer(std::string data)
            {
            return static_cast<CatRate>(std::stoi(data.substr(5,1)));
            }
            
            std::string Menu::RS232_TOT::Set(CatTOT value)
            {
            return fmt::format("EX{:03d}{:01d};",
            static_cast<int>(MenuFunction::RS232_TIME_OUT_TIMER),
            static_cast<int>(value)); 
            }
            
            std::string Menu::RS232_TOT::Read()
            {
            return fmt::format("EX{:03d};",
            static_cast<int>(MenuFunction::RS232_TIME_OUT_TIMER));
            }
            
            CatTOT Menu::RS232_TOT::Answer(std::string data)
            {
            return static_cast<CatTOT>(std::stoi(data.substr(5,1)));
            }
            
            std::string Menu::CAT_RATE::Set(CatRate value)
            {
            return fmt::format("EX{:03d}{:01d};",
            static_cast<int>(MenuFunction::CAT_RATE),
            static_cast<int>(value)); 
            }
            
            std::string Menu::CAT_RATE::Read()
            {
            return fmt::format("EX{:03d};",
            static_cast<int>(MenuFunction::CAT_RATE));
            }
            
            CatRate Menu::CAT_RATE::Answer(std::string data)
            {
            return static_cast<CatRate>(std::stoi(data.substr(5,1)));
            }
            
            std::string Menu::CAT_TOT::Set(CatTOT value)
            {
            return fmt::format("EX{:03d}{:01d};",
            static_cast<int>(MenuFunction::CAT_TIME_OUT_TIMER),
            static_cast<int>(value)); 
            }
            
            std::string Menu::CAT_TOT::Read()
            {
            return fmt::format("EX{:03d};",
            static_cast<int>(MenuFunction::CAT_TIME_OUT_TIMER));
            }
            
            CatTOT Menu::CAT_TOT::Answer(std::string data)
            {
            return static_cast<CatTOT>(std::stoi(data.substr(5,1)));
            }
            
            std::string Menu::CAT_RTS::Set(EnableDisableValue value)
            {
            return fmt::format("EX{:03d}{:01d};",
            static_cast<int>(MenuFunction::CAT_RTS),
            static_cast<int>(value)); 
            }
            
            std::string Menu::CAT_RTS::Read()
            {
            return fmt::format("EX{:03d};",
            static_cast<int>(MenuFunction::CAT_RTS));
            }
            
            EnableDisableValue Menu::CAT_RTS::Answer(std::string data)
            {
            return static_cast<EnableDisableValue>(std::stoi(data.substr(5,1)));
            }
            
            std::string Menu::MEM_GROUP::Set(EnableDisableValue value)
            {
            return fmt::format("EX{:03d}{:01d};",
            static_cast<int>(MenuFunction::MEM_GROUP),
            static_cast<int>(value)); 
            }
            
            std::string Menu::MEM_GROUP::Read()
            {
            return fmt::format("EX{:03d};",
            static_cast<int>(MenuFunction::MEM_GROUP));
            }
            
            EnableDisableValue Menu::MEM_GROUP::Answer(std::string data)
            {
            return static_cast<EnableDisableValue>(std::stoi(data.substr(5,1)));
            }
            
            std::string Menu::QUICK_SPLIT_FREQ::Set(int value)
            {
            return fmt::format("EX{:03d}{:+03d};",
            static_cast<int>(MenuFunction::QUICK_SPLIT_FREQ),
            static_cast<int>(value)); 
            }
            
            std::string Menu::QUICK_SPLIT_FREQ::Read()
            {
            return fmt::format("EX{:03d};",
            static_cast<int>(MenuFunction::QUICK_SPLIT_FREQ));
            }
            
            int Menu::QUICK_SPLIT_FREQ::Answer(std::string data)
            {
            return static_cast<int>(std::stoi(data.substr(5,3)));
            }
            
            std::string Menu::MIC_SCAN::Set(EnableDisableValue value)
            {
            return fmt::format("EX{:03d}{:01d};",
            static_cast<int>(MenuFunction::MIC_SCAN),
            static_cast<int>(value)); 
            }
            
            std::string Menu::MIC_SCAN::Read()
            {
            return fmt::format("EX{:03d};",
            static_cast<int>(MenuFunction::MIC_SCAN));
            }
            
            EnableDisableValue Menu::MIC_SCAN::Answer(std::string data)
            {
            return static_cast<EnableDisableValue>(std::stoi(data.substr(5,1)));
            }
            
            std::string Menu::MIC_SCAN_RESUME::Set(MicScanResumeValue value)
            {
            return fmt::format("EX{:03d}{:01d};",
            static_cast<int>(MenuFunction::MIC_SCAN_RESUME),
            static_cast<int>(value)); 
            }
            
            std::string Menu::MIC_SCAN_RESUME::Read()
            {
            return fmt::format("EX{:03d};",
            static_cast<int>(MenuFunction::MIC_SCAN_RESUME));
            }
            
            MicScanResumeValue Menu::MIC_SCAN_RESUME::Answer(std::string data)
            {
            return static_cast<MicScanResumeValue>(std::stoi(data.substr(5,1)));
            }
            
            std::string Menu::REF_FREQ_ADJ::Set(int value)
            {
            return fmt::format("EX{:03d}{:+03d};",
            static_cast<int>(MenuFunction::REF_FREQ_ADJ),
            static_cast<int>(value)); 
            }
            
            std::string Menu::REF_FREQ_ADJ::Read()
            {
            return fmt::format("EX{:03d};",
            static_cast<int>(MenuFunction::REF_FREQ_ADJ));
            }
            
            int Menu::REF_FREQ_ADJ::Answer(std::string data)
            {
            return static_cast<int>(std::stoi(data.substr(5,3)));
            }
            
            std::string Menu::TX_TOT::Set(int value)
            {
            return fmt::format("EX{:03d}{:02d};",
            static_cast<int>(MenuFunction::TX_TOT),
            static_cast<int>(value)); 
            }
            
            std::string Menu::TX_TOT::Read()
            {
            return fmt::format("EX{:03d};",
            static_cast<int>(MenuFunction::TX_TOT));
            }
            
            int Menu::TX_TOT::Answer(std::string data)
            {
            return static_cast<int>(std::stoi(data.substr(5,2)));
            }
            
            std::string Menu::CLAR_MODE_SELECT::Set(ClarModeType value)
            {
            return fmt::format("EX{:03d}{:01d};",
            static_cast<int>(MenuFunction::CLAR_MODE_SELECT),
            static_cast<int>(value)); 
            }
            
            std::string Menu::CLAR_MODE_SELECT::Read()
            {
            return fmt::format("EX{:03d};",
            static_cast<int>(MenuFunction::CLAR_MODE_SELECT));
            }
            
            ClarModeType Menu::CLAR_MODE_SELECT::Answer(std::string data)
            {
            return static_cast<ClarModeType>(std::stoi(data.substr(5,1)));
            }
            
            std::string Menu::AM_LCUT_FREQ::Set(FreqLowCutValue value)
            {
            return fmt::format("EX{:03d}{:02d};",
            static_cast<int>(MenuFunction::AM_LCUT_FREQ),
            static_cast<int>(value)); 
            }
            
            std::string Menu::AM_LCUT_FREQ::Read()
            {
            return fmt::format("EX{:03d};",
            static_cast<int>(MenuFunction::AM_LCUT_FREQ));
            }
            
            FreqLowCutValue Menu::AM_LCUT_FREQ::Answer(std::string data)
            {
            return static_cast<FreqLowCutValue>(std::stoi(data.substr(5,2)));
            }
            
            std::string Menu::AM_LCUT_SLOPE::Set(FreqSlopeValue value)
            {
            return fmt::format("EX{:03d}{:01d};",
            static_cast<int>(MenuFunction::AM_LCUT_SLOPE),
            static_cast<int>(value)); 
            }
            
            std::string Menu::AM_LCUT_SLOPE::Read()
            {
            return fmt::format("EX{:03d};",
            static_cast<int>(MenuFunction::AM_LCUT_SLOPE));
            }
            
            FreqSlopeValue Menu::AM_LCUT_SLOPE::Answer(std::string data)
            {
            return static_cast<FreqSlopeValue>(std::stoi(data.substr(5,1)));
            }
            
            std::string Menu::AM_HCUT_FREQ::Set(FreqHighCutValue value)
            {
            return fmt::format("EX{:03d}{:02d};",
            static_cast<int>(MenuFunction::AM_HCUT_FREQ),
            static_cast<int>(value)); 
            }
            
            std::string Menu::AM_HCUT_FREQ::Read()
            {
            return fmt::format("EX{:03d};",
            static_cast<int>(MenuFunction::AM_HCUT_FREQ));
            }
            
            FreqHighCutValue Menu::AM_HCUT_FREQ::Answer(std::string data)
            {
            return static_cast<FreqHighCutValue>(std::stoi(data.substr(5,2)));
            }
            
            std::string Menu::AM_HCUT_SLOPE::Set(FreqSlopeValue value)
            {
            return fmt::format("EX{:03d}{:01d};",
            static_cast<int>(MenuFunction::AM_HCUT_SLOPE),
            static_cast<int>(value)); 
            }
            
            std::string Menu::AM_HCUT_SLOPE::Read()
            {
            return fmt::format("EX{:03d};",
            static_cast<int>(MenuFunction::AM_HCUT_SLOPE));
            }
            
            FreqSlopeValue Menu::AM_HCUT_SLOPE::Answer(std::string data)
            {
            return static_cast<FreqSlopeValue>(std::stoi(data.substr(5,1)));
            }
            
            std::string Menu::AM_OUT_LEVEL::Set(int value)
            {
            return fmt::format("EX{:03d}{:03d};",
            static_cast<int>(MenuFunction::AM_OUT_LEVEL),
            static_cast<int>(value)); 
            }
            
            std::string Menu::AM_OUT_LEVEL::Read()
            {
            return fmt::format("EX{:03d};",
            static_cast<int>(MenuFunction::AM_OUT_LEVEL));
            }
            
            int Menu::AM_OUT_LEVEL::Answer(std::string data)
            {
            return static_cast<int>(std::stoi(data.substr(5,3)));
            }
            
            std::string Menu::AM_PTT_SELECT::Set(PTTSelectValue value)
            {
            return fmt::format("EX{:03d}{:01d};",
            static_cast<int>(MenuFunction::AM_PTT_SELECT),
            static_cast<int>(value)); 
            }
            
            std::string Menu::AM_PTT_SELECT::Read()
            {
            return fmt::format("EX{:03d};",
            static_cast<int>(MenuFunction::AM_PTT_SELECT));
            }
            
            PTTSelectValue Menu::AM_PTT_SELECT::Answer(std::string data)
            {
            return static_cast<PTTSelectValue>(std::stoi(data.substr(5,1)));
            }
            
            std::string Menu::AM_PORT_SELECT::Set(RearSelect value)
            {
            return fmt::format("EX{:03d}{:01d};",
            static_cast<int>(MenuFunction::AM_PORT_SELECT),
            static_cast<int>(value)); 
            }
            
            std::string Menu::AM_PORT_SELECT::Read()
            {
            return fmt::format("EX{:03d};",
            static_cast<int>(MenuFunction::AM_PORT_SELECT));
            }
            
            RearSelect Menu::AM_PORT_SELECT::Answer(std::string data)
            {
            return static_cast<RearSelect>(std::stoi(data.substr(5,1)));
            }
            
            std::string Menu::AM_DATA_GAIN::Set(int value)
            {
            return fmt::format("EX{:03d}{:03d};",
            static_cast<int>(MenuFunction::AM_DATA_GAIN),
            static_cast<int>(value)); 
            }
            
            std::string Menu::AM_DATA_GAIN::Read()
            {
            return fmt::format("EX{:03d};",
            static_cast<int>(MenuFunction::AM_DATA_GAIN));
            }
            
            int Menu::AM_DATA_GAIN::Answer(std::string data)
            {
            return static_cast<int>(std::stoi(data.substr(5,3)));
            }
            
            std::string Menu::CW_LCUT_FREQ::Set(FreqLowCutValue value)
            {
            return fmt::format("EX{:03d}{:02d};",
            static_cast<int>(MenuFunction::CW_LCUT_FREQ),
            static_cast<int>(value)); 
            }
            
            std::string Menu::CW_LCUT_FREQ::Read()
            {
            return fmt::format("EX{:03d};",
            static_cast<int>(MenuFunction::CW_LCUT_FREQ));
            }
            
            FreqLowCutValue Menu::CW_LCUT_FREQ::Answer(std::string data)
            {
            return static_cast<FreqLowCutValue>(std::stoi(data.substr(5,2)));
            }
            
            std::string Menu::CW_LCUT_SLOPE::Set(FreqSlopeValue value)
            {
            return fmt::format("EX{:03d}{:01d};",
            static_cast<int>(MenuFunction::CW_LCUT_SLOPE),
            static_cast<int>(value)); 
            }
            
            std::string Menu::CW_LCUT_SLOPE::Read()
            {
            return fmt::format("EX{:03d};",
            static_cast<int>(MenuFunction::CW_LCUT_SLOPE));
            }
            
            FreqSlopeValue Menu::CW_LCUT_SLOPE::Answer(std::string data)
            {
            return static_cast<FreqSlopeValue>(std::stoi(data.substr(5,1)));
            }
            
            std::string Menu::CW_HCUT_FREQ::Set(FreqHighCutValue value)
            {
            return fmt::format("EX{:03d}{:02d};",
            static_cast<int>(MenuFunction::CW_HCUT_FREQ),
            static_cast<int>(value)); 
            }
            
            std::string Menu::CW_HCUT_FREQ::Read()
            {
            return fmt::format("EX{:03d};",
            static_cast<int>(MenuFunction::CW_HCUT_FREQ));
            }
            
            FreqHighCutValue Menu::CW_HCUT_FREQ::Answer(std::string data)
            {
            return static_cast<FreqHighCutValue>(std::stoi(data.substr(5,2)));
            }
            
            std::string Menu::CW_HCUT_SLOPE::Set(FreqSlopeValue value)
            {
            return fmt::format("EX{:03d}{:01d};",
            static_cast<int>(MenuFunction::CW_HCUT_SLOPE),
            static_cast<int>(value)); 
            }
            
            std::string Menu::CW_HCUT_SLOPE::Read()
            {
            return fmt::format("EX{:03d};",
            static_cast<int>(MenuFunction::CW_HCUT_SLOPE));
            }
            
            FreqSlopeValue Menu::CW_HCUT_SLOPE::Answer(std::string data)
            {
            return static_cast<FreqSlopeValue>(std::stoi(data.substr(5,1)));
            }
            
            std::string Menu::CW_OUT_LEVEL::Set(int value)
            {
            return fmt::format("EX{:03d}{:03d};",
            static_cast<int>(MenuFunction::CW_OUT_LEVEL),
            static_cast<int>(value)); 
            }
            
            std::string Menu::CW_OUT_LEVEL::Read()
            {
            return fmt::format("EX{:03d};",
            static_cast<int>(MenuFunction::CW_OUT_LEVEL));
            }
            
            int Menu::CW_OUT_LEVEL::Answer(std::string data)
            {
            return static_cast<int>(std::stoi(data.substr(5,3)));
            }
            
            std::string Menu::CW_AUTO_MODE::Set(CWAutoModeType value)
            {
            return fmt::format("EX{:03d}{:01d};",
            static_cast<int>(MenuFunction::CW_AUTO_MODE),
            static_cast<int>(value)); 
            }
            
            std::string Menu::CW_AUTO_MODE::Read()
            {
            return fmt::format("EX{:03d};",
            static_cast<int>(MenuFunction::CW_AUTO_MODE));
            }
            
            CWAutoModeType Menu::CW_AUTO_MODE::Answer(std::string data)
            {
            return static_cast<CWAutoModeType>(std::stoi(data.substr(5,1)));
            }
            
            std::string Menu::CW_BK_IN_TYPE::Set(CwBreakInType value)
            {
            return fmt::format("EX{:03d}{:01d};",
            static_cast<int>(MenuFunction::CW_BK_IN_TYPE),
            static_cast<int>(value)); 
            }
            
            std::string Menu::CW_BK_IN_TYPE::Read()
            {
            return fmt::format("EX{:03d};",
            static_cast<int>(MenuFunction::CW_BK_IN_TYPE));
            }
            
            CwBreakInType Menu::CW_BK_IN_TYPE::Answer(std::string data)
            {
            return static_cast<CwBreakInType>(std::stoi(data.substr(5,1)));
            }
            
            std::string Menu::CW_BK_IN_DELAY::Set(int value)
            {
            return fmt::format("EX{:03d}{:04d};",
            static_cast<int>(MenuFunction::CW_BK_IN_DELAY),
            static_cast<int>(value)); 
            }
            
            std::string Menu::CW_BK_IN_DELAY::Read()
            {
            return fmt::format("EX{:03d};",
            static_cast<int>(MenuFunction::CW_BK_IN_DELAY));
            }
            
            int Menu::CW_BK_IN_DELAY::Answer(std::string data)
            {
            return static_cast<int>(std::stoi(data.substr(5,4)));
            }
            
            std::string Menu::CW_WAVE_SHAPE::Set(CWWaveShapeValue value)
            {
            return fmt::format("EX{:03d}{:01d};",
            static_cast<int>(MenuFunction::CW_WAVE_SHAPE),
            static_cast<int>(value)); 
            }
            
            std::string Menu::CW_WAVE_SHAPE::Read()
            {
            return fmt::format("EX{:03d};",
            static_cast<int>(MenuFunction::CW_WAVE_SHAPE));
            }
            
            CWWaveShapeValue Menu::CW_WAVE_SHAPE::Answer(std::string data)
            {
            return static_cast<CWWaveShapeValue>(std::stoi(data.substr(5,1)));
            }
            
            std::string Menu::CW_FREQ_DISPLAY::Set(CWFreqDisplayValue value)
            {
            return fmt::format("EX{:03d}{:01d};",
            static_cast<int>(MenuFunction::CW_FREQ_DISPLAY),
            static_cast<int>(value)); 
            }
            
            std::string Menu::CW_FREQ_DISPLAY::Read()
            {
            return fmt::format("EX{:03d};",
            static_cast<int>(MenuFunction::CW_FREQ_DISPLAY));
            }
            
            CWFreqDisplayValue Menu::CW_FREQ_DISPLAY::Answer(std::string data)
            {
            return static_cast<CWFreqDisplayValue>(std::stoi(data.substr(5,1)));
            }
            
            std::string Menu::PC_KEYING::Set(PCKeyingValue value)
            {
            return fmt::format("EX{:03d}{:01d};",
            static_cast<int>(MenuFunction::PC_KEYING),
            static_cast<int>(value)); 
            }
            
            std::string Menu::PC_KEYING::Read()
            {
            return fmt::format("EX{:03d};",
            static_cast<int>(MenuFunction::PC_KEYING));
            }
            
            PCKeyingValue Menu::PC_KEYING::Answer(std::string data)
            {
            return static_cast<PCKeyingValue>(std::stoi(data.substr(5,1)));
            }
            
            std::string Menu::QSK_DELAY_TIME::Set(QskDelayTimeValue value)
            {
            return fmt::format("EX{:03d}{:01d};",
            static_cast<int>(MenuFunction::QSK_DELAY_TIME),
            static_cast<int>(value)); 
            }
            
            std::string Menu::QSK_DELAY_TIME::Read()
            {
            return fmt::format("EX{:03d};",
            static_cast<int>(MenuFunction::QSK_DELAY_TIME));
            }
            
            QskDelayTimeValue Menu::QSK_DELAY_TIME::Answer(std::string data)
            {
            return static_cast<QskDelayTimeValue>(std::stoi(data.substr(5,1)));
            }
            
            std::string Menu::DATA_MODE::Set(DataMode value)
            {
            return fmt::format("EX{:03d}{:01d};",
            static_cast<int>(MenuFunction::DATA_MODE),
            static_cast<int>(value)); 
            }
            
            std::string Menu::DATA_MODE::Read()
            {
            return fmt::format("EX{:03d};",
            static_cast<int>(MenuFunction::DATA_MODE));
            }
            
            DataMode Menu::DATA_MODE::Answer(std::string data)
            {
            return static_cast<DataMode>(std::stoi(data.substr(5,1)));
            }
            
            std::string Menu::PSK_TONE::Set(PSKToneValue value)
            {
            return fmt::format("EX{:03d}{:01d};",
            static_cast<int>(MenuFunction::PSK_TONE),
            static_cast<int>(value)); 
            }
            
            std::string Menu::PSK_TONE::Read()
            {
            return fmt::format("EX{:03d};",
            static_cast<int>(MenuFunction::PSK_TONE));
            }
            
            PSKToneValue Menu::PSK_TONE::Answer(std::string data)
            {
            return static_cast<PSKToneValue>(std::stoi(data.substr(5,1)));
            }
            
            std::string Menu::OTHER_SHIFT::Set(int value)
            {
            return fmt::format("EX{:03d}{:+05d};",
            static_cast<int>(MenuFunction::OTHER_SHIFT),
            static_cast<int>(value)); 
            }
            
            std::string Menu::OTHER_SHIFT::Read()
            {
            return fmt::format("EX{:03d};",
            static_cast<int>(MenuFunction::OTHER_SHIFT));
            }
            
            int Menu::OTHER_SHIFT::Answer(std::string data)
            {
            return static_cast<int>(std::stoi(data.substr(5,5)));
            }
            
            std::string Menu::OTHER_DISP::Set(int value)
            {
            return fmt::format("EX{:03d}{:+05d};",
            static_cast<int>(MenuFunction::OTHER_DISP),
            static_cast<int>(value)); 
            }
            
            std::string Menu::OTHER_DISP::Read()
            {
            return fmt::format("EX{:03d};",
            static_cast<int>(MenuFunction::OTHER_DISP));
            }
            
            int Menu::OTHER_DISP::Answer(std::string data)
            {
            return static_cast<int>(std::stoi(data.substr(5,5)));
            }
            

            std::string Menu::DATA_LCUT_FREQ::Set(FreqLowCutValue value)
            {
            return fmt::format("EX{:03d}{:02d};",
            static_cast<int>(MenuFunction::DATA_LCUT_FREQ),
            static_cast<int>(value)); 
            }
            
            std::string Menu::DATA_LCUT_FREQ::Read()
            {
            return fmt::format("EX{:03d};",
            static_cast<int>(MenuFunction::DATA_LCUT_FREQ));
            }
            
            FreqLowCutValue Menu::DATA_LCUT_FREQ::Answer(std::string data)
            {
            return static_cast<FreqLowCutValue>(std::stoi(data.substr(5,2)));
            }
            
            std::string Menu::DATA_LCUT_SLOPE::Set(FreqSlopeValue value)
            {
            return fmt::format("EX{:03d}{:01d};",
            static_cast<int>(MenuFunction::DATA_LCUT_SLOPE),
            static_cast<int>(value)); 
            }
            
            std::string Menu::DATA_LCUT_SLOPE::Read()
            {
            return fmt::format("EX{:03d};",
            static_cast<int>(MenuFunction::DATA_LCUT_SLOPE));
            }
            
            FreqSlopeValue Menu::DATA_LCUT_SLOPE::Answer(std::string data)
            {
            return static_cast<FreqSlopeValue>(std::stoi(data.substr(5,1)));
            }
            
            std::string Menu::DATA_HCUT_FREQ::Set(FreqHighCutValue value)
            {
            return fmt::format("EX{:03d}{:02d};",
            static_cast<int>(MenuFunction::DATA_HCUT_FREQ),
            static_cast<int>(value)); 
            }
            
            std::string Menu::DATA_HCUT_FREQ::Read()
            {
            return fmt::format("EX{:03d};",
            static_cast<int>(MenuFunction::DATA_HCUT_FREQ));
            }
            
            FreqHighCutValue Menu::DATA_HCUT_FREQ::Answer(std::string data)
            {
            return static_cast<FreqHighCutValue>(std::stoi(data.substr(5,2)));
            }
            
            std::string Menu::DATA_HCUT_SLOPE::Set(FreqSlopeValue value)
            {
            return fmt::format("EX{:03d}{:01d};",
            static_cast<int>(MenuFunction::DATA_HCUT_SLOPE),
            static_cast<int>(value)); 
            }
            
            std::string Menu::DATA_HCUT_SLOPE::Read()
            {
            return fmt::format("EX{:03d};",
            static_cast<int>(MenuFunction::DATA_HCUT_SLOPE));
            }
            
            FreqSlopeValue Menu::DATA_HCUT_SLOPE::Answer(std::string data)
            {
            return static_cast<FreqSlopeValue>(std::stoi(data.substr(5,1)));
            }
            
            std::string Menu::DATA_IN_SELECT::Set(ModulationSource value)
            {
            return fmt::format("EX{:03d}{:01d};",
            static_cast<int>(MenuFunction::DATA_IN_SELECT),
            static_cast<int>(value)); 
            }
            
            std::string Menu::DATA_IN_SELECT::Read()
            {
            return fmt::format("EX{:03d};",
            static_cast<int>(MenuFunction::DATA_IN_SELECT));
            }
            
            ModulationSource Menu::DATA_IN_SELECT::Answer(std::string data)
            {
            return static_cast<ModulationSource>(std::stoi(data.substr(5,1)));
            }
            
            std::string Menu::DATA_PTT_SELECT::Set(PTTSelectValue value)
            {
            return fmt::format("EX{:03d}{:01d};",
            static_cast<int>(MenuFunction::DATA_PTT_SELECT),
            static_cast<int>(value)); 
            }
            
            std::string Menu::DATA_PTT_SELECT::Read()
            {
            return fmt::format("EX{:03d};",
            static_cast<int>(MenuFunction::DATA_PTT_SELECT));
            }
            
            PTTSelectValue Menu::DATA_PTT_SELECT::Answer(std::string data)
            {
            return static_cast<PTTSelectValue>(std::stoi(data.substr(5,1)));
            }
            
            std::string Menu::DATA_OUT_LEVEL::Set(int value)
            {
            return fmt::format("EX{:03d}{:03d};",
            static_cast<int>(MenuFunction::DATA_OUT_LEVEL),
            static_cast<int>(value)); 
            }
            
            std::string Menu::DATA_OUT_LEVEL::Read()
            {
            return fmt::format("EX{:03d};",
            static_cast<int>(MenuFunction::DATA_OUT_LEVEL));
            }
            
            int Menu::DATA_OUT_LEVEL::Answer(std::string data)
            {
            return static_cast<int>(std::stoi(data.substr(5,3)));
            }
            
            std::string Menu::FM_MIC_SELECT::Set(ModulationSource value)
            {
            return fmt::format("EX{:03d}{:01d};",
            static_cast<int>(MenuFunction::FM_MIC_SELECT),
            static_cast<int>(value)); 
            }
            
            std::string Menu::FM_MIC_SELECT::Read()
            {
            return fmt::format("EX{:03d};",
            static_cast<int>(MenuFunction::FM_MIC_SELECT));
            }
            
            ModulationSource Menu::FM_MIC_SELECT::Answer(std::string data)
            {
            return static_cast<ModulationSource>(std::stoi(data.substr(5,1)));
            }
            
            std::string Menu::FM_OUT_LEVEL::Set(int value)
            {
            return fmt::format("EX{:03d}{:03d};",
            static_cast<int>(MenuFunction::FM_OUT_LEVEL),
            static_cast<int>(value)); 
            }
            
            std::string Menu::FM_OUT_LEVEL::Read()
            {
            return fmt::format("EX{:03d};",
            static_cast<int>(MenuFunction::FM_OUT_LEVEL));
            }
            
            int Menu::FM_OUT_LEVEL::Answer(std::string data)
            {
            return static_cast<int>(std::stoi(data.substr(5,3)));
            }
            
            std::string Menu::FM_PKT_PTT_SELECT::Set(PTTSelectValue value)
            {
            return fmt::format("EX{:03d}{:01d};",
            static_cast<int>(MenuFunction::FM_PKT_PTT_SELECT),
            static_cast<int>(value)); 
            }
            
            std::string Menu::FM_PKT_PTT_SELECT::Read()
            {
            return fmt::format("EX{:03d};",
            static_cast<int>(MenuFunction::FM_PKT_PTT_SELECT));
            }
            
            PTTSelectValue Menu::FM_PKT_PTT_SELECT::Answer(std::string data)
            {
            return static_cast<PTTSelectValue>(std::stoi(data.substr(5,1)));
            }
            
            std::string Menu::DATA_PORT_SELECT::Set(RearSelect value)
            {
            return fmt::format("EX{:03d}{:01d};",
            static_cast<int>(MenuFunction::DATA_PORT_SELECT),
            static_cast<int>(value)); 
            }
            
            std::string Menu::DATA_PORT_SELECT::Read()
            {
            return fmt::format("EX{:03d};",
            static_cast<int>(MenuFunction::DATA_PORT_SELECT));
            }
            
            RearSelect Menu::DATA_PORT_SELECT::Answer(std::string data)
            {
            return static_cast<RearSelect>(std::stoi(data.substr(5,1)));
            }

            std::string Menu::FM_PKT_PORT_SELECT::Set(RearSelect value)
            {
            return fmt::format("EX{:03d}{:01d};",
            static_cast<int>(MenuFunction::FM_PKT_PORT_SELECT),
            static_cast<int>(value)); 
            }
            
            std::string Menu::FM_PKT_PORT_SELECT::Read()
            {
            return fmt::format("EX{:03d};",
            static_cast<int>(MenuFunction::FM_PKT_PORT_SELECT));
            }
            
            RearSelect Menu::FM_PKT_PORT_SELECT::Answer(std::string data)
            {
            return static_cast<RearSelect>(std::stoi(data.substr(5,1)));
            }
            
            std::string Menu::FM_PKT_TX_GAIN::Set(int value)
            {
            return fmt::format("EX{:03d}{:03d};",
            static_cast<int>(MenuFunction::FM_PKT_TX_GAIN),
            static_cast<int>(value)); 
            }
            
            std::string Menu::FM_PKT_TX_GAIN::Read()
            {
            return fmt::format("EX{:03d};",
            static_cast<int>(MenuFunction::FM_PKT_TX_GAIN));
            }
            
            int Menu::FM_PKT_TX_GAIN::Answer(std::string data)
            {
            return static_cast<int>(std::stoi(data.substr(5,3)));
            }

            std::string Menu::FM_PKT_MODE::Set(PKTMode value)
            {
            return fmt::format("EX{:03d}{:01d};",
            static_cast<int>(MenuFunction::FM_PKT_MODE),
            static_cast<int>(value)); 
            }
            
            std::string Menu::FM_PKT_MODE::Read()
            {
            return fmt::format("EX{:03d};",
            static_cast<int>(MenuFunction::FM_PKT_MODE));
            }
            
            PKTMode Menu::FM_PKT_MODE::Answer(std::string data)
            {
            return static_cast<PKTMode>(std::stoi(data.substr(5,1)));
            }
            
            std::string Menu::RPT_SHIFT_28MHZ::Set(int value)
            {
             //over our max?
             value = value > 1000 ? 1000 : value;
             //under our min?
             value = value < 0 ? 0 : value;
             //not a 10 kHz step?
             value = (value - value % 10);
            return fmt::format("EX{:03d}{:04d};",
            static_cast<int>(MenuFunction::RPT_SHIFT_28MHZ),
            static_cast<int>(value)); 
            }
            
            std::string Menu::RPT_SHIFT_28MHZ::Read()
            {
            return fmt::format("EX{:03d};",
            static_cast<int>(MenuFunction::RPT_SHIFT_28MHZ));
            }
            
            int Menu::RPT_SHIFT_28MHZ::Answer(std::string data)
            {
            return static_cast<int>(std::stoi(data.substr(5,4)));
            }
            
            std::string Menu::RPT_SHIFT_50MHZ::Set(int value)
            {
                   //over our max?
             value = value > 4000 ? 4000 : value;
             //under our min?
             value = value < 0 ? 0 : value;
             //not a 10 kHz step?
             value = (value - (value % 10));
            return fmt::format("EX{:03d}{:04d};",
            static_cast<int>(MenuFunction::RPT_SHIFT_50MHZ),
            static_cast<int>(value)); 
            }
            
            std::string Menu::RPT_SHIFT_50MHZ::Read()
            {
            return fmt::format("EX{:03d};",
            static_cast<int>(MenuFunction::RPT_SHIFT_50MHZ));
            }
            
            int Menu::RPT_SHIFT_50MHZ::Answer(std::string data)
            {
            return static_cast<int>(std::stoi(data.substr(5,4)));
            }
            
            std::string Menu::RPT_SHIFT_144MHZ::Set(int value)
            {
                //over our max?
             value = value > 4000 ? 4000 : value;
             //under our min?
             value = value < 0 ? 0 : value;
             //not a 10 kHz step?
             value = (value - (value % 10));
            return fmt::format("EX{:03d}{:04d};",
            static_cast<int>(MenuFunction::RPT_SHIFT_144MHZ),
            static_cast<int>(value)); 
            }
            
            std::string Menu::RPT_SHIFT_144MHZ::Read()
            {
            return fmt::format("EX{:03d};",
            static_cast<int>(MenuFunction::RPT_SHIFT_144MHZ));
            }
            
            int Menu::RPT_SHIFT_144MHZ::Answer(std::string data)
            {
            return static_cast<int>(std::stoi(data.substr(5,4)));
            }
            
            std::string Menu::RPT_SHIFT_430MHZ::Set(int value)
            {
                  //over our max?
             value = value > 10000 ? 10000 : value;
             //under our min?
             value = value < 0 ? 0 : value;
             //not a 10 kHz step?
             value = (value - (value % 10));
            return fmt::format("EX{:03d}{:05d};",
            static_cast<int>(MenuFunction::RPT_SHIFT_430MHZ),
            static_cast<int>(value)); 
            }
            
            std::string Menu::RPT_SHIFT_430MHZ::Read()
            {
            return fmt::format("EX{:03d};",
            static_cast<int>(MenuFunction::RPT_SHIFT_430MHZ));
            }
            
            int Menu::RPT_SHIFT_430MHZ::Answer(std::string data)
            {
            return static_cast<int>(std::stoi(data.substr(5,5)));
            }
            
            std::string Menu::ARS_144MHZ::Set(OnOffValue value)
            {
            return fmt::format("EX{:03d}{:01d};",
            static_cast<int>(MenuFunction::ARS_144MHZ),
            static_cast<int>(value)); 
            }
            
            std::string Menu::ARS_144MHZ::Read()
            {
            return fmt::format("EX{:03d};",
            static_cast<int>(MenuFunction::ARS_144MHZ));
            }
            
            OnOffValue Menu::ARS_144MHZ::Answer(std::string data)
            {
            return static_cast<OnOffValue>(std::stoi(data.substr(5,1)));
            }
            
            std::string Menu::ARS_430MHZ::Set(OnOffValue value)
            {
            return fmt::format("EX{:03d}{:01d};",
            static_cast<int>(MenuFunction::ARS_430MHZ),
            static_cast<int>(value)); 
            }
            
            std::string Menu::ARS_430MHZ::Read()
            {
            return fmt::format("EX{:03d};",
            static_cast<int>(MenuFunction::ARS_430MHZ));
            }
            
            OnOffValue Menu::ARS_430MHZ::Answer(std::string data)
            {
            return static_cast<OnOffValue>(std::stoi(data.substr(5,1)));
            }
            
            std::string Menu::DCS_POLARITY::Set(DCSPolarityValue value)
            {
            return fmt::format("EX{:03d}{:01d};",
            static_cast<int>(MenuFunction::DCS_POLARITY),
            static_cast<int>(value)); 
            }
            
            std::string Menu::DCS_POLARITY::Read()
            {
            return fmt::format("EX{:03d};",
            static_cast<int>(MenuFunction::DCS_POLARITY));
            }
            
            DCSPolarityValue Menu::DCS_POLARITY::Answer(std::string data)
            {
            return static_cast<DCSPolarityValue>(std::stoi(data.substr(5,1)));
            }
            
            std::string Menu::RADIO_ID::Read()
            {
            return fmt::format("EX{:03d};",
            static_cast<int>(MenuFunction::RADIO_ID));
            }
            
            std::string Menu::RADIO_ID::Answer(std::string data)
            {
            return data.substr(5,5);
            }
            
            std::string Menu::GM_DISPLAY::Set(GMDisplayType value)
            {
            return fmt::format("EX{:03d}{:01d};",
            static_cast<int>(MenuFunction::GM_DISPLAY),
            static_cast<int>(value)); 
            }
            
            std::string Menu::GM_DISPLAY::Read()
            {
            return fmt::format("EX{:03d};",
            static_cast<int>(MenuFunction::GM_DISPLAY));
            }
            
            GMDisplayType Menu::GM_DISPLAY::Answer(std::string data)
            {
            return static_cast<GMDisplayType>(std::stoi(data.substr(5,1)));
            }
            
            std::string Menu::DISTANCE::Set(DistanceType value)
            {
            return fmt::format("EX{:03d}{:01d};",
            static_cast<int>(MenuFunction::DISTANCE),
            static_cast<int>(value)); 
            }
            
            std::string Menu::DISTANCE::Read()
            {
            return fmt::format("EX{:03d};",
            static_cast<int>(MenuFunction::DISTANCE));
            }
            
            DistanceType Menu::DISTANCE::Answer(std::string data)
            {
            return static_cast<DistanceType>(std::stoi(data.substr(5,1)));
            }
            
            std::string Menu::AMS_TX_MODE::Set(AMSTxModeValue value)
            {
            return fmt::format("EX{:03d}{:01d};",
            static_cast<int>(MenuFunction::AMS_TX_MODE),
            static_cast<int>(value)); 
            }
            
            std::string Menu::AMS_TX_MODE::Read()
            {
            return fmt::format("EX{:03d};",
            static_cast<int>(MenuFunction::AMS_TX_MODE));
            }
            
            AMSTxModeValue Menu::AMS_TX_MODE::Answer(std::string data)
            {
            return static_cast<AMSTxModeValue>(std::stoi(data.substr(5,1)));
            }
            
            std::string Menu::STANDBY_BEEP::Set(OnOffValue value)
            {
            return fmt::format("EX{:03d}{:01d};",
            static_cast<int>(MenuFunction::STANDBY_BEEP),
            static_cast<int>(value)); 
            }
            
            std::string Menu::STANDBY_BEEP::Read()
            {
            return fmt::format("EX{:03d};",
            static_cast<int>(MenuFunction::STANDBY_BEEP));
            }
            
            OnOffValue Menu::STANDBY_BEEP::Answer(std::string data)
            {
            return static_cast<OnOffValue>(std::stoi(data.substr(5,1)));
            }
            
            std::string Menu::RTTY_LCUT_FREQ::Set(FreqLowCutValue value)
            {
            return fmt::format("EX{:03d}{:02d};",
            static_cast<int>(MenuFunction::RTTY_LCUT_FREQ),
            static_cast<int>(value)); 
            }
            
            std::string Menu::RTTY_LCUT_FREQ::Read()
            {
            return fmt::format("EX{:03d};",
            static_cast<int>(MenuFunction::RTTY_LCUT_FREQ));
            }
            
            FreqLowCutValue Menu::RTTY_LCUT_FREQ::Answer(std::string data)
            {
            return static_cast<FreqLowCutValue>(std::stoi(data.substr(5,2)));
            }
            
            std::string Menu::RTTY_LCUT_SLOPE::Set(FreqSlopeValue value)
            {
            return fmt::format("EX{:03d}{:01d};",
            static_cast<int>(MenuFunction::RTTY_LCUT_SLOPE),
            static_cast<int>(value)); 
            }
            
            std::string Menu::RTTY_LCUT_SLOPE::Read()
            {
            return fmt::format("EX{:03d};",
            static_cast<int>(MenuFunction::RTTY_LCUT_SLOPE));
            }
            
            FreqSlopeValue Menu::RTTY_LCUT_SLOPE::Answer(std::string data)
            {
            return static_cast<FreqSlopeValue>(std::stoi(data.substr(5,1)));
            }
            
            std::string Menu::RTTY_HCUT_FREQ::Set(FreqHighCutValue value)
            {
            return fmt::format("EX{:03d}{:02d};",
            static_cast<int>(MenuFunction::RTTY_HCUT_FREQ),
            static_cast<int>(value)); 
            }
            
            std::string Menu::RTTY_HCUT_FREQ::Read()
            {
            return fmt::format("EX{:03d};",
            static_cast<int>(MenuFunction::RTTY_HCUT_FREQ));
            }
            
            FreqHighCutValue Menu::RTTY_HCUT_FREQ::Answer(std::string data)
            {
            return static_cast<FreqHighCutValue>(std::stoi(data.substr(5,2)));
            }
            
            std::string Menu::RTTY_HCUT_SLOPE::Set(FreqSlopeValue value)
            {
            return fmt::format("EX{:03d}{:01d};",
            static_cast<int>(MenuFunction::RTTY_HCUT_SLOPE),
            static_cast<int>(value)); 
            }
            
            std::string Menu::RTTY_HCUT_SLOPE::Read()
            {
            return fmt::format("EX{:03d};",
            static_cast<int>(MenuFunction::RTTY_HCUT_SLOPE));
            }
            
            FreqSlopeValue Menu::RTTY_HCUT_SLOPE::Answer(std::string data)
            {
            return static_cast<FreqSlopeValue>(std::stoi(data.substr(5,1)));
            }
            
            std::string Menu::RTTY_SHIFT_PORT::Set(ShiftPortValue value)
            {
            return fmt::format("EX{:03d}{:01d};",
            static_cast<int>(MenuFunction::RTTY_SHIFT_PORT),
            static_cast<int>(value)); 
            }
            
            std::string Menu::RTTY_SHIFT_PORT::Read()
            {
            return fmt::format("EX{:03d};",
            static_cast<int>(MenuFunction::RTTY_SHIFT_PORT));
            }
            
            ShiftPortValue Menu::RTTY_SHIFT_PORT::Answer(std::string data)
            {
            return static_cast<ShiftPortValue>(std::stoi(data.substr(5,1)));
            }
            
            std::string Menu::RTTY_POLARITY_RX::Set(RTTYPolarityValue value)
            {
            return fmt::format("EX{:03d}{:01d};",
            static_cast<int>(MenuFunction::RTTY_POLARITY_RX),
            static_cast<int>(value)); 
            }
            
            std::string Menu::RTTY_POLARITY_RX::Read()
            {
            return fmt::format("EX{:03d};",
            static_cast<int>(MenuFunction::RTTY_POLARITY_RX));
            }
            
            RTTYPolarityValue Menu::RTTY_POLARITY_RX::Answer(std::string data)
            {
            return static_cast<RTTYPolarityValue>(std::stoi(data.substr(5,1)));
            }
            
            std::string Menu::RTTY_POLARITY_TX::Set(RTTYPolarityValue value)
            {
            return fmt::format("EX{:03d}{:01d};",
            static_cast<int>(MenuFunction::RTTY_POLARITY_TX),
            static_cast<int>(value)); 
            }
            
            std::string Menu::RTTY_POLARITY_TX::Read()
            {
            return fmt::format("EX{:03d};",
            static_cast<int>(MenuFunction::RTTY_POLARITY_TX));
            }
            
            RTTYPolarityValue Menu::RTTY_POLARITY_TX::Answer(std::string data)
            {
            return static_cast<RTTYPolarityValue>(std::stoi(data.substr(5,1)));
            }
            
            std::string Menu::RTTY_OUT_LEVEL::Set(int value)
            {
            return fmt::format("EX{:03d}{:03d};",
            static_cast<int>(MenuFunction::RTTY_OUT_LEVEL),
            static_cast<int>(value)); 
            }
            
            std::string Menu::RTTY_OUT_LEVEL::Read()
            {
            return fmt::format("EX{:03d};",
            static_cast<int>(MenuFunction::RTTY_OUT_LEVEL));
            }
            
            int Menu::RTTY_OUT_LEVEL::Answer(std::string data)
            {
            return static_cast<int>(std::stoi(data.substr(5,3)));
            }
            
            std::string Menu::RTTY_SHIFT_FREQ::Set(RTTYShiftFreqValue value)
            {
            return fmt::format("EX{:03d}{:01d};",
            static_cast<int>(MenuFunction::RTTY_SHIFT_FREQ),
            static_cast<int>(value)); 
            }
            
            std::string Menu::RTTY_SHIFT_FREQ::Read()
            {
            return fmt::format("EX{:03d};",
            static_cast<int>(MenuFunction::RTTY_SHIFT_FREQ));
            }
            
            RTTYShiftFreqValue Menu::RTTY_SHIFT_FREQ::Answer(std::string data)
            {
            return static_cast<RTTYShiftFreqValue>(std::stoi(data.substr(5,1)));
            }
            
            std::string Menu::RTTY_MARK_FREQ::Set(RTTYMarkFreq value)
            {
            return fmt::format("EX{:03d}{:01d};",
            static_cast<int>(MenuFunction::RTTY_MARK_FREQ),
            static_cast<int>(value)); 
            }
            
            std::string Menu::RTTY_MARK_FREQ::Read()
            {
            return fmt::format("EX{:03d};",
            static_cast<int>(MenuFunction::RTTY_MARK_FREQ));
            }
            
            RTTYMarkFreq Menu::RTTY_MARK_FREQ::Answer(std::string data)
            {
            return static_cast<RTTYMarkFreq>(std::stoi(data.substr(5,1)));
            }
            
            std::string Menu::SSB_LCUT_FREQ::Set(FreqLowCutValue value)
            {
            return fmt::format("EX{:03d}{:02d};",
            static_cast<int>(MenuFunction::SSB_LCUT_FREQ),
            static_cast<int>(value)); 
            }
            
            std::string Menu::SSB_LCUT_FREQ::Read()
            {
            return fmt::format("EX{:03d};",
            static_cast<int>(MenuFunction::SSB_LCUT_FREQ));
            }
            
            FreqLowCutValue Menu::SSB_LCUT_FREQ::Answer(std::string data)
            {
            return static_cast<FreqLowCutValue>(std::stoi(data.substr(5,2)));
            }
            
            std::string Menu::SSB_LCUT_SLOPE::Set(FreqSlopeValue value)
            {
            return fmt::format("EX{:03d}{:01d};",
            static_cast<int>(MenuFunction::SSB_LCUT_SLOPE),
            static_cast<int>(value)); 
            }
            
            std::string Menu::SSB_LCUT_SLOPE::Read()
            {
            return fmt::format("EX{:03d};",
            static_cast<int>(MenuFunction::SSB_LCUT_SLOPE));
            }
            
            FreqSlopeValue Menu::SSB_LCUT_SLOPE::Answer(std::string data)
            {
            return static_cast<FreqSlopeValue>(std::stoi(data.substr(5,1)));
            }
            
            std::string Menu::SSB_HCUT_FREQ::Set(FreqHighCutValue value)
            {
            return fmt::format("EX{:03d}{:02d};",
            static_cast<int>(MenuFunction::SSB_HCUT_FREQ),
            static_cast<int>(value)); 
            }
            
            std::string Menu::SSB_HCUT_FREQ::Read()
            {
            return fmt::format("EX{:03d};",
            static_cast<int>(MenuFunction::SSB_HCUT_FREQ));
            }
            
            FreqHighCutValue Menu::SSB_HCUT_FREQ::Answer(std::string data)
            {
            return static_cast<FreqHighCutValue>(std::stoi(data.substr(5,2)));
            }
            
            std::string Menu::SSB_MIC_SELECT::Set(ModulationSource value)
            {
            return fmt::format("EX{:03d}{:01d};",
            static_cast<int>(MenuFunction::SSB_MIC_SELECT),
            static_cast<int>(value)); 
            }
            
            std::string Menu::SSB_MIC_SELECT::Read()
            {
            return fmt::format("EX{:03d};",
            static_cast<int>(MenuFunction::SSB_MIC_SELECT));
            }
            
            ModulationSource Menu::SSB_MIC_SELECT::Answer(std::string data)
            {
            return static_cast<ModulationSource>(std::stoi(data.substr(5,1)));
            }
            
            std::string Menu::SSB_OUT_LEVEL::Set(int value)
            {
            return fmt::format("EX{:03d}{:03d};",
            static_cast<int>(MenuFunction::SSB_OUT_LEVEL),
            static_cast<int>(value)); 
            }
            
            std::string Menu::SSB_OUT_LEVEL::Read()
            {
            return fmt::format("EX{:03d};",
            static_cast<int>(MenuFunction::SSB_OUT_LEVEL));
            }
            
            int Menu::SSB_OUT_LEVEL::Answer(std::string data)
            {
            return static_cast<int>(std::stoi(data.substr(5,3)));
            }
            
            std::string Menu::SSB_PTT_SELECT::Set(PTTSelectValue value)
            {
            return fmt::format("EX{:03d}{:01d};",
            static_cast<int>(MenuFunction::SSB_PTT_SELECT),
            static_cast<int>(value)); 
            }
            
            std::string Menu::SSB_PTT_SELECT::Read()
            {
            return fmt::format("EX{:03d};",
            static_cast<int>(MenuFunction::SSB_PTT_SELECT));
            }
            
            PTTSelectValue Menu::SSB_PTT_SELECT::Answer(std::string data)
            {
            return static_cast<PTTSelectValue>(std::stoi(data.substr(5,1)));
            }
            
            std::string Menu::SSB_PORT_SELECT::Set(RearSelect value)
            {
            return fmt::format("EX{:03d}{:01d};",
            static_cast<int>(MenuFunction::SSB_PORT_SELECT),
            static_cast<int>(value)); 
            }
            
            std::string Menu::SSB_PORT_SELECT::Read()
            {
            return fmt::format("EX{:03d};",
            static_cast<int>(MenuFunction::SSB_PORT_SELECT));
            }
            
            RearSelect Menu::SSB_PORT_SELECT::Answer(std::string data)
            {
            return static_cast<RearSelect>(std::stoi(data.substr(5,1)));
            }
            
            std::string Menu::SSB_TX_BPF::Set(SSBTXBandPassValue value)
            {
            return fmt::format("EX{:03d}{:01d};",
            static_cast<int>(MenuFunction::SSB_TX_BPF),
            static_cast<int>(value)); 
            }
            
            std::string Menu::SSB_TX_BPF::Read()
            {
            return fmt::format("EX{:03d};",
            static_cast<int>(MenuFunction::SSB_TX_BPF));
            }
            
            SSBTXBandPassValue Menu::SSB_TX_BPF::Answer(std::string data)
            {
            return static_cast<SSBTXBandPassValue>(std::stoi(data.substr(5,1)));
            }
            
            std::string Menu::APF_WIDTH::Set(APFWidthValue value)
            {
            return fmt::format("EX{:03d}{:01d};",
            static_cast<int>(MenuFunction::APF_WIDTH),
            static_cast<int>(value)); 
            }
            
            std::string Menu::APF_WIDTH::Read()
            {
            return fmt::format("EX{:03d};",
            static_cast<int>(MenuFunction::APF_WIDTH));
            }
            
            APFWidthValue Menu::APF_WIDTH::Answer(std::string data)
            {
            return static_cast<APFWidthValue>(std::stoi(data.substr(5,1)));
            }
            
            std::string Menu::COUNTOUR_LEVEL::Set(int value)
            {
                value = value < -40 ? -40 : value;
                value = value > 20 ? 20 : value;

            return fmt::format("EX{:03d}{:+03d};",
            static_cast<int>(MenuFunction::COUNTOUR_LEVEL),
            static_cast<int>(value)); 
            }
            
            std::string Menu::COUNTOUR_LEVEL::Read()
            {
            return fmt::format("EX{:03d};",
            static_cast<int>(MenuFunction::COUNTOUR_LEVEL));
            }
            
            int Menu::COUNTOUR_LEVEL::Answer(std::string data)
            {
            return static_cast<int>(std::stoi(data.substr(5,3)));
            }
            
            std::string Menu::COUNTOUR_WIDTH::Set(int value)
            {
            return fmt::format("EX{:03d}{:02d};",
            static_cast<int>(MenuFunction::COUNTOUR_WIDTH),
            static_cast<int>(value)); 
            }
            
            std::string Menu::COUNTOUR_WIDTH::Read()
            {
            return fmt::format("EX{:03d};",
            static_cast<int>(MenuFunction::COUNTOUR_WIDTH));
            }
            
            int Menu::COUNTOUR_WIDTH::Answer(std::string data)
            {
            return static_cast<int>(std::stoi(data.substr(5,2)));
            }
            
            std::string Menu::IF_NOTCH_WIDTH::Set(IFNotchWidth value)
            {
            return fmt::format("EX{:03d}{:01d};",
            static_cast<int>(MenuFunction::IF_NOTCH_WIDTH),
            static_cast<int>(value)); 
            }
            
            std::string Menu::IF_NOTCH_WIDTH::Read()
            {
            return fmt::format("EX{:03d};",
            static_cast<int>(MenuFunction::IF_NOTCH_WIDTH));
            }
            
            IFNotchWidth Menu::IF_NOTCH_WIDTH::Answer(std::string data)
            {
            return static_cast<IFNotchWidth>(std::stoi(data.substr(5,1)));
            }
            
            std::string Menu::SCP_DISPLAY_MODE::Set(ScopeDisplayMode value)
            {
            return fmt::format("EX{:03d}{:01d};",
            static_cast<int>(MenuFunction::SCP_DISPLAY_MODE),
            static_cast<int>(value)); 
            }
            
            std::string Menu::SCP_DISPLAY_MODE::Read()
            {
            return fmt::format("EX{:03d};",
            static_cast<int>(MenuFunction::SCP_DISPLAY_MODE));
            }
            
            ScopeDisplayMode Menu::SCP_DISPLAY_MODE::Answer(std::string data)
            {
            return static_cast<ScopeDisplayMode>(std::stoi(data.substr(5,1)));
            }
            
            std::string Menu::SCP_SPAN_FREQ::Set(ScopeSpan value)
            {
            return fmt::format("EX{:03d}{:02d};",
            static_cast<int>(MenuFunction::SCP_SPAN_FREQ),
            static_cast<int>(value)); 
            }
            
            std::string Menu::SCP_SPAN_FREQ::Read()
            {
            return fmt::format("EX{:03d};",
            static_cast<int>(MenuFunction::SCP_SPAN_FREQ));
            }
            
            ScopeSpan Menu::SCP_SPAN_FREQ::Answer(std::string data)
            {
            return static_cast<ScopeSpan>(std::stoi(data.substr(5,2)));
            }
            
            std::string Menu::SPECTRUM_COLOR::Set(SpectrumColor value)
            {
            return fmt::format("EX{:03d}{:01d};",
            static_cast<int>(MenuFunction::SPECTRUM_COLOR),
            static_cast<int>(value)); 
            }
            
            std::string Menu::SPECTRUM_COLOR::Read()
            {
            return fmt::format("EX{:03d};",
            static_cast<int>(MenuFunction::SPECTRUM_COLOR));
            }
            
            SpectrumColor Menu::SPECTRUM_COLOR::Answer(std::string data)
            {
            return static_cast<SpectrumColor>(std::stoi(data.substr(5,1)));
            }
            
            std::string Menu::WATERFALL_COLOR::Set(WaterfallColor value)
            {
            return fmt::format("EX{:03d}{:01d};",
            static_cast<int>(MenuFunction::WATERFALL_COLOR),
            static_cast<int>(value)); 
            }
            
            std::string Menu::WATERFALL_COLOR::Read()
            {
            return fmt::format("EX{:03d};",
            static_cast<int>(MenuFunction::WATERFALL_COLOR));
            }
            
            WaterfallColor Menu::WATERFALL_COLOR::Answer(std::string data)
            {
            return static_cast<WaterfallColor>(std::stoi(data.substr(5,1)));
            }
            
            std::string Menu::PRMTRC_EQ1_FREQ::Set(EQ1FreqValue value)
            {
            return fmt::format("EX{:03d}{:02d};",
            static_cast<int>(MenuFunction::PRMTRC_EQ1_FREQ),
            static_cast<int>(value)); 
            }
            
            std::string Menu::PRMTRC_EQ1_FREQ::Read()
            {
            return fmt::format("EX{:03d};",
            static_cast<int>(MenuFunction::PRMTRC_EQ1_FREQ));
            }
            
            EQ1FreqValue Menu::PRMTRC_EQ1_FREQ::Answer(std::string data)
            {
            return static_cast<EQ1FreqValue>(std::stoi(data.substr(5,2)));
            }
            
            std::string Menu::PRMTRC_EQ1_LEVEL::Set(int value)
            {
            return fmt::format("EX{:03d}{:+03d};",
            static_cast<int>(MenuFunction::PRMTRC_EQ1_LEVEL),
            static_cast<int>(value)); 
            }
            
            std::string Menu::PRMTRC_EQ1_LEVEL::Read()
            {
            return fmt::format("EX{:03d};",
            static_cast<int>(MenuFunction::PRMTRC_EQ1_LEVEL));
            }
            
            int Menu::PRMTRC_EQ1_LEVEL::Answer(std::string data)
            {
            return static_cast<int>(std::stoi(data.substr(5,3)));
            }
            
            std::string Menu::PRMTRC_EQ1_BWTH::Set(int value)
            {
            return fmt::format("EX{:03d}{:02d};",
            static_cast<int>(MenuFunction::PRMTRC_EQ1_BWTH),
            static_cast<int>(value)); 
            }
            
            std::string Menu::PRMTRC_EQ1_BWTH::Read()
            {
            return fmt::format("EX{:03d};",
            static_cast<int>(MenuFunction::PRMTRC_EQ1_BWTH));
            }
            
            int Menu::PRMTRC_EQ1_BWTH::Answer(std::string data)
            {
            return static_cast<int>(std::stoi(data.substr(5,2)));
            }
            
            std::string Menu::PRMTRC_EQ2_FREQ::Set(EQ2FreqValue value)
            {
            return fmt::format("EX{:03d}{:02d};",
            static_cast<int>(MenuFunction::PRMTRC_EQ2_FREQ),
            static_cast<int>(value)); 
            }
            
            std::string Menu::PRMTRC_EQ2_FREQ::Read()
            {
            return fmt::format("EX{:03d};",
            static_cast<int>(MenuFunction::PRMTRC_EQ2_FREQ));
            }
            
            EQ2FreqValue Menu::PRMTRC_EQ2_FREQ::Answer(std::string data)
            {
            return static_cast<EQ2FreqValue>(std::stoi(data.substr(5,2)));
            }
            
            std::string Menu::PRMTRC_EQ2_LEVEL::Set(int value)
            {
            return fmt::format("EX{:03d}{:+03d};",
            static_cast<int>(MenuFunction::PRMTRC_EQ2_LEVEL),
            static_cast<int>(value)); 
            }
            
            std::string Menu::PRMTRC_EQ2_LEVEL::Read()
            {
            return fmt::format("EX{:03d};",
            static_cast<int>(MenuFunction::PRMTRC_EQ2_LEVEL));
            }
            
            int Menu::PRMTRC_EQ2_LEVEL::Answer(std::string data)
            {
            return static_cast<int>(std::stoi(data.substr(5,3)));
            }
            
            std::string Menu::PRMTRC_EQ2_BWTH::Set(int value)
            {
            return fmt::format("EX{:03d}{:02d};",
            static_cast<int>(MenuFunction::PRMTRC_EQ2_BWTH),
            static_cast<int>(value)); 
            }
            
            std::string Menu::PRMTRC_EQ2_BWTH::Read()
            {
            return fmt::format("EX{:03d};",
            static_cast<int>(MenuFunction::PRMTRC_EQ2_BWTH));
            }
            
            int Menu::PRMTRC_EQ2_BWTH::Answer(std::string data)
            {
            return static_cast<int>(std::stoi(data.substr(5,2)));
            }
            
            std::string Menu::PRMTRC_EQ3_FREQ::Set(EQ3FreqValue value)
            {
            return fmt::format("EX{:03d}{:02d};",
            static_cast<int>(MenuFunction::PRMTRC_EQ3_FREQ),
            static_cast<int>(value)); 
            }
            
            std::string Menu::PRMTRC_EQ3_FREQ::Read()
            {
            return fmt::format("EX{:03d};",
            static_cast<int>(MenuFunction::PRMTRC_EQ3_FREQ));
            }
            
            EQ3FreqValue Menu::PRMTRC_EQ3_FREQ::Answer(std::string data)
            {
            return static_cast<EQ3FreqValue>(std::stoi(data.substr(5,2)));
            }
            
            std::string Menu::PRMTRC_EQ3_LEVEL::Set(int value)
            {
            return fmt::format("EX{:03d}{:+03d};",
            static_cast<int>(MenuFunction::PRMTRC_EQ3_LEVEL),
            static_cast<int>(value)); 
            }
            
            std::string Menu::PRMTRC_EQ3_LEVEL::Read()
            {
            return fmt::format("EX{:03d};",
            static_cast<int>(MenuFunction::PRMTRC_EQ3_LEVEL));
            }
            
            int Menu::PRMTRC_EQ3_LEVEL::Answer(std::string data)
            {
            return static_cast<int>(std::stoi(data.substr(5,3)));
            }
            
            std::string Menu::PRMTRC_EQ3_BWTH::Set(int value)
            {
            return fmt::format("EX{:03d}{:02d};",
            static_cast<int>(MenuFunction::PRMTRC_EQ3_BWTH),
            static_cast<int>(value)); 
            }
            
            std::string Menu::PRMTRC_EQ3_BWTH::Read()
            {
            return fmt::format("EX{:03d};",
            static_cast<int>(MenuFunction::PRMTRC_EQ3_BWTH));
            }
            
            int Menu::PRMTRC_EQ3_BWTH::Answer(std::string data)
            {
            return static_cast<int>(std::stoi(data.substr(5,2)));
            }
            
            std::string Menu::TX_MAX_POWER_HF::Set(int value)
            {
            return fmt::format("EX{:03d}{:03d};",
            static_cast<int>(MenuFunction::TX_MAX_POWER_HF),
            static_cast<int>(value)); 
            }
            
            std::string Menu::TX_MAX_POWER_HF::Read()
            {
            return fmt::format("EX{:03d};",
            static_cast<int>(MenuFunction::TX_MAX_POWER_HF));
            }
            
            int Menu::TX_MAX_POWER_HF::Answer(std::string data)
            {
            return static_cast<int>(std::stoi(data.substr(5,3)));
            }
            
            std::string Menu::TX_MAX_POWER_50MHZ::Set(int value)
            {
            return fmt::format("EX{:03d}{:03d};",
            static_cast<int>(MenuFunction::TX_MAX_POWER_50MHZ),
            static_cast<int>(value)); 
            }
            
            std::string Menu::TX_MAX_POWER_50MHZ::Read()
            {
            return fmt::format("EX{:03d};",
            static_cast<int>(MenuFunction::TX_MAX_POWER_50MHZ));
            }
            
            int Menu::TX_MAX_POWER_50MHZ::Answer(std::string data)
            {
            return static_cast<int>(std::stoi(data.substr(5,3)));
            }
            
            std::string Menu::TX_MAX_POWER_144MHZ::Set(int value)
            {
            return fmt::format("EX{:03d}{:02d};",
            static_cast<int>(MenuFunction::TX_MAX_POWER_144MHZ),
            static_cast<int>(value)); 
            }
            
            std::string Menu::TX_MAX_POWER_144MHZ::Read()
            {
            return fmt::format("EX{:03d};",
            static_cast<int>(MenuFunction::TX_MAX_POWER_144MHZ));
            }
            
            int Menu::TX_MAX_POWER_144MHZ::Answer(std::string data)
            {
            return static_cast<int>(std::stoi(data.substr(5,2)));
            }
            
            std::string Menu::TX_MAX_POWER_430MHZ::Set(int value)
            {
            return fmt::format("EX{:03d}{:02d};",
            static_cast<int>(MenuFunction::TX_MAX_POWER_430MHZ),
            static_cast<int>(value)); 
            }
            
            std::string Menu::TX_MAX_POWER_430MHZ::Read()
            {
            return fmt::format("EX{:03d};",
            static_cast<int>(MenuFunction::TX_MAX_POWER_430MHZ));
            }
            
            int Menu::TX_MAX_POWER_430MHZ::Answer(std::string data)
            {
            return static_cast<int>(std::stoi(data.substr(5,2)));
            }

            std::string Menu::TUNER_SELECT::Set(TunerSelectValue value)
            {
            return fmt::format("EX{:03d}{:01d};",
            static_cast<int>(MenuFunction::TUNER_SELECT),
            static_cast<int>(value)); 
            }
            
            std::string Menu::TUNER_SELECT::Read()
            {
            return fmt::format("EX{:03d};",
            static_cast<int>(MenuFunction::TUNER_SELECT));
            }
            
            TunerSelectValue Menu::TUNER_SELECT::Answer(std::string data)
            {
            return static_cast<TunerSelectValue>(std::stoi(data.substr(5,1)));
            }
            
            std::string Menu::VOX_SELECT::Set(VoxSelectValue value)
            {
            return fmt::format("EX{:03d}{:01d};",
            static_cast<int>(MenuFunction::VOX_SELECT),
            static_cast<int>(value)); 
            }
            
            std::string Menu::VOX_SELECT::Read()
            {
            return fmt::format("EX{:03d};",
            static_cast<int>(MenuFunction::VOX_SELECT));
            }
            
            VoxSelectValue Menu::VOX_SELECT::Answer(std::string data)
            {
            return static_cast<VoxSelectValue>(std::stoi(data.substr(5,1)));
            }
            
            std::string Menu::VOX_GAIN::Set(int value)
            {
            return fmt::format("EX{:03d}{:03d};",
            static_cast<int>(MenuFunction::VOX_GAIN),
            static_cast<int>(value)); 
            }
            
            std::string Menu::VOX_GAIN::Read()
            {
            return fmt::format("EX{:03d};",
            static_cast<int>(MenuFunction::VOX_GAIN));
            }
            
            int Menu::VOX_GAIN::Answer(std::string data)
            {
            return static_cast<int>(std::stoi(data.substr(5,3)));
            }
            
            std::string Menu::VOX_DELAY::Set(int value)
            {
            return fmt::format("EX{:03d}{:04d};",
            static_cast<int>(MenuFunction::VOX_DELAY),
            static_cast<int>(value)); 
            }
            
            std::string Menu::VOX_DELAY::Read()
            {
            return fmt::format("EX{:03d};",
            static_cast<int>(MenuFunction::VOX_DELAY));
            }
            
            int Menu::VOX_DELAY::Answer(std::string data)
            {
            return static_cast<int>(std::stoi(data.substr(5,4)));
            }
            
            std::string Menu::ANTI_VOX_GAIN::Set(int value)
            {
            return fmt::format("EX{:03d}{:03d};",
            static_cast<int>(MenuFunction::ANTI_VOX_GAIN),
            static_cast<int>(value)); 
            }
            
            std::string Menu::ANTI_VOX_GAIN::Read()
            {
            return fmt::format("EX{:03d};",
            static_cast<int>(MenuFunction::ANTI_VOX_GAIN));
            }
            
            int Menu::ANTI_VOX_GAIN::Answer(std::string data)
            {
            return static_cast<int>(std::stoi(data.substr(5,3)));
            }

            std::string Menu::DATA_VOX_GAIN::Set(int value)
            {
            return fmt::format("EX{:03d}{:03d};",
            static_cast<int>(MenuFunction::DATA_VOX_GAIN),
            static_cast<int>(value)); 
            }
            
            std::string Menu::DATA_VOX_GAIN::Read()
            {
            return fmt::format("EX{:03d};",
            static_cast<int>(MenuFunction::DATA_VOX_GAIN));
            }
            
            int Menu::DATA_VOX_GAIN::Answer(std::string data)
            {
            return static_cast<int>(std::stoi(data.substr(5,3)));
            }
            
            std::string Menu::DATA_VOX_DELAY::Set(int value)
            {
            return fmt::format("EX{:03d}{:04d};",
            static_cast<int>(MenuFunction::DATA_VOX_DELAY),
            static_cast<int>(value)); 
            }
            
            std::string Menu::DATA_VOX_DELAY::Read()
            {
            return fmt::format("EX{:03d};",
            static_cast<int>(MenuFunction::DATA_VOX_DELAY));
            }
            
            int Menu::DATA_VOX_DELAY::Answer(std::string data)
            {
            return static_cast<int>(std::stoi(data.substr(5,4)));
            }
            
            std::string Menu::ANTI_DVOX_GAIN::Set(int value)
            {
            return fmt::format("EX{:03d}{:03d};",
            static_cast<int>(MenuFunction::ANTI_DVOX_GAIN),
            static_cast<int>(value)); 
            }
            
            std::string Menu::ANTI_DVOX_GAIN::Read()
            {
            return fmt::format("EX{:03d};",
            static_cast<int>(MenuFunction::ANTI_DVOX_GAIN));
            }
            
            int Menu::ANTI_DVOX_GAIN::Answer(std::string data)
            {
            return static_cast<int>(std::stoi(data.substr(5,3)));
            }
            
            std::string Menu::EMERGENCY_FREQ_TX::Set(EnableDisableValue value)
            {
            return fmt::format("EX{:03d}{:01d};",
            static_cast<int>(MenuFunction::EMERGENCY_FREQ_TX),
            static_cast<int>(value)); 
            }
            
            std::string Menu::EMERGENCY_FREQ_TX::Read()
            {
            return fmt::format("EX{:03d};",
            static_cast<int>(MenuFunction::EMERGENCY_FREQ_TX));
            }
            
            EnableDisableValue Menu::EMERGENCY_FREQ_TX::Answer(std::string data)
            {
            return static_cast<EnableDisableValue>(std::stoi(data.substr(5,1)));
            }
            
            std::string Menu::PRT_WIRES_FREQ::Set(WiresFreqencyType value)
            {
            return fmt::format("EX{:03d}{:01d};",
            static_cast<int>(MenuFunction::PRT_WIRES_FREQ),
            static_cast<int>(value)); 
            }
            
            std::string Menu::PRT_WIRES_FREQ::Read()
            {
            return fmt::format("EX{:03d};",
            static_cast<int>(MenuFunction::PRT_WIRES_FREQ));
            }
            
            WiresFreqencyType Menu::PRT_WIRES_FREQ::Answer(std::string data)
            {
            return static_cast<WiresFreqencyType>(std::stoi(data.substr(5,1)));
            }
            
            std::string Menu::PRESET_FREQUENCY::Set(int value)
            {
            return fmt::format("EX{:03d}{:08d};",
            static_cast<int>(MenuFunction::PRESET_FREQUENCY),
            static_cast<int>(value)); 
            }
            
            std::string Menu::PRESET_FREQUENCY::Read()
            {
            return fmt::format("EX{:03d};",
            static_cast<int>(MenuFunction::PRESET_FREQUENCY));
            }
            
            int Menu::PRESET_FREQUENCY::Answer(std::string data)
            {
            return static_cast<int>(std::stoi(data.substr(5,8)));
            }
            
            std::string Menu::SEARCH_SETUP::Set(SearchSetupType value)
            {
            return fmt::format("EX{:03d}{:01d};",
            static_cast<int>(MenuFunction::SEARCH_SETUP),
            static_cast<int>(value)); 
            }
            
            std::string Menu::SEARCH_SETUP::Read()
            {
            return fmt::format("EX{:03d};",
            static_cast<int>(MenuFunction::SEARCH_SETUP));
            }
            
            SearchSetupType Menu::SEARCH_SETUP::Answer(std::string data)
            {
            return static_cast<SearchSetupType>(std::stoi(data.substr(5,1)));
            }
            
            std::string Menu::WIRES_DG_ID::Set(WiresDGID value)
            {
            return fmt::format("EX{:03d}{:02d};",
            static_cast<int>(MenuFunction::WIRES_DG_ID),
            static_cast<int>(value)); 
            }
            
            std::string Menu::WIRES_DG_ID::Read()
            {
            return fmt::format("EX{:03d};",
            static_cast<int>(MenuFunction::WIRES_DG_ID));
            }
            
            WiresDGID Menu::WIRES_DG_ID::Answer(std::string data)
            {
            return static_cast<WiresDGID>(std::stoi(data.substr(5,2)));
            }
            
            std::string FrequencyVFOA::Set(int value)
            {
                return fmt::format("FA{:08d};",value);
            }
            
            std::string FrequencyVFOA::Read()
            {
                return "FA;";
            }
            
            int FrequencyVFOA::Answer(std::string data)
            {
                return std::stoi(data.substr(2,8));
            }
            
            std::string FrequencyVFOB::Set(int value)
            {
                return fmt::format("FB{:08d};",value);
            }
            
            std::string FrequencyVFOB::Read()
            {
                return "FB;";
            }
            
            int FrequencyVFOB::Answer(std::string data)
            {
                return std::stoi(data.substr(2,8));
            }            

            std::string FastStep::Set(OnOffValue value)
            {
                return fmt::format("FS{:01d};", static_cast<int>(value));
            }
            
            std::string FastStep::Read()
            {
                return "FS;";
            }
            
            OnOffValue FastStep::Answer(std::string data)
            {
                return static_cast<OnOffValue>(std::stoi(data.substr(2,1)));
            }
            
            std::string FunctionTX::Set(FunctionTxValue value)
            {
                return fmt::format("FT{:01d}", 2 + static_cast<int>(value));
            }
            
            std::string FunctionTX::Read()
            {
                return "FT;";
            }
            
            FunctionTxValue FunctionTX::Answer(std::string data)
            {
                return static_cast<FunctionTxValue>(std::stoi(data.substr(2,1)));
            }
            
            std::string AGCFunction::Set(AGCSetValue value)
            {
                return fmt::format("GT0{:01d};", static_cast<int>(value));
            }
            
            std::string AGCFunction::Read()
            {
                return "GT0;";
            }
            
            AGCStateValue AGCFunction::Answer(std::string data)
            {
                return static_cast<AGCStateValue>(std::stoi(data.substr(3,1)));
            }
            
 
            
            std::string Information::Read()
            {
                return "IF;";
            }
            
            InformationValue Information::Answer(std::string data)
            {
                InformationValue ret;
                ret.MemoryChannel = static_cast<MemoryChannelValue>(std::stoi(data.substr(2,3)));
                ret.VFOAFreq = std::stoi(data.substr(5, 9));
                ret.ClarifierFreq = std::stoi(data.substr(14,5));
                ret.RxClarifier = static_cast<ClarifierState>(std::stoi(data.substr(19,1)));
                ret.TxClarifier = static_cast<ClarifierState>(std::stoi(data.substr(20,1)));
                ret.Mode = static_cast<ModeValue>(std::stoi(data.substr(21,1),0,16));
                ret.VFO = static_cast<VFOChannelTypeValue>(std::stoi(data.substr(22,1)));
                ret.CTCSS = static_cast<CTCSSState>(std::stoi(data.substr(23,1)));
                ret.Operation = static_cast<OperationType>(std::stoi(data.substr(26,1)));

                return ret;    
            }
            
            std::string IF_Shift::Set(int value)
            {
                return fmt::format("IS0{:+05d};", value);
            }
            
            std::string IF_Shift::Read()
            {
                return "IS0;";
            }
            
            int IF_Shift::Answer(std::string data)
            {
                return std::stoi(data.substr(3,5));
            }
            
            std::string KeyerMemory::Set(KeyerMemoryValue value)
            {
                return fmt::format("KM{:01d}{:50s};",static_cast<int>(value.Channel),
                                   value.Message.substr(0,50));
            }
            
            std::string KeyerMemory::Read(KeyerMemoryChannel channel)
            {
                return fmt::format("KM{:01d};",static_cast<int>(channel));                
            }
            
            KeyerMemoryValue KeyerMemory::Answer(std::string data)
            {
                KeyerMemoryValue ret;
                ret.Channel = static_cast<KeyerMemoryChannel>(std::stoi(data.substr(2,1)));
                ret.Message = data.substr(3, data.find(";") - 1);
                return ret;
            }
            
            std::string KeyPitch::Set(KeyPitchValue value)
            {
                return fmt::format("KP{:02d};", static_cast<int>(value));
            }
            
            std::string KeyPitch::Read()
            {
                return "KP;";
            }
            
            KeyPitchValue KeyPitch::Answer(std::string data)
            {
                return static_cast<KeyPitchValue>(std::stoi(data.substr(2,2)));
            }
            
            std::string Keyer::Set(OnOffValue value)
            {
                return fmt::format("KR{:01d};",static_cast<int>(value));
            }
            
            std::string Keyer::Read()
            {
                return "KR;";
            }
            
            OnOffValue Keyer::Answer(std::string data)
            {
                return static_cast<OnOffValue>(std::stoi(data.substr(2,1)));
            }
            
            std::string KeySpeed::Set(int value)
            {
                return fmt::format("KS{:03};",value);
            }
            
            std::string KeySpeed::Read()
            {
                return "KS;";
            }
            
            int KeySpeed::Answer(std::string data)
            {   
                return std::stoi(data.substr(2,3));
            }
            
            std::string CWKeying::Set(CWKeyingPlaybackValue value)
            {
                return fmt::format("KY{:0x};", static_cast<int>(value));
            }   
            
            std::string Lock::Set(OnOffValue value)
            {
                return fmt::format("LK{:01d};", static_cast<int>(value));
            }
            
            std::string Lock::Read()
            {
                return "LK;";
            }
            
            OnOffValue Lock::Answer(std::string data)
            {
                return static_cast<OnOffValue>(std::stoi(data.substr(2,1)));                
            }
            

           std::string LoadMessage::Set(DVSRecordingValue value)
           {
                return fmt::format("LM0{:01d};",static_cast<int>(value));
           }
           
           std::string LoadMessage::Read()
           {
                return "LM0;";
           }
           
           DVSRecordingValue LoadMessage::Answer(std::string data)
           {
               return static_cast<DVSRecordingValue>(std::stoi(data.substr(3,1)));
           }
           
            std::string MemoryChannel_To_VFOA::Set( )
            {
                return "MA;";
            }
            
            std::string MemoryChannel::Set(MemoryChannelValue value)
            {
                return fmt::format("MC{:03d};",static_cast<int>(value));
            }
            
            std::string MemoryChannel::Read()
            {
                return "MC;";
            }
            
            MemoryChannelValue MemoryChannel::Answer(std::string data)
            {
                return static_cast<MemoryChannelValue>(std::stoi(data.substr(2,3)));
            }
            
            std::string OperatingMode::Set(ModeValue value)
            {
                return fmt::format("MD0{:01x};", static_cast<int>(value));
            }
            
            std::string OperatingMode::Read()
            {
                return "MD0;";
            }
            
            ModeValue OperatingMode::Answer(std::string data)
            {
                return static_cast<ModeValue>(std::stoi(data.substr(3,1),0,16));
            }
            
            std::string MicGain::Set(int value)
            {
                return fmt::format("MG{:03d};",value);
            }
            
            std::string MicGain::Read()
            {
                return "MG;";
            }
            
            int MicGain::Answer(std::string data)
            {
                return std::stoi(data.substr(2,3));
            }
            
            std::string MonitorLevel::Set(MonitorLevelValue value)
            {
                switch(value.f)
                {
                    case MonitorFunction::OnOff:
                    return fmt::format("ML{:01d}{:03d};",
                    static_cast<int>(value.f),
                    static_cast<int>(value.val.eVal));
                    break;
                    case MonitorFunction::Level:
                    return fmt::format("ML{:01d}{:03d};",
                    static_cast<int>(value.f),
                    value.val.iVal);
                    break;
                    default:
                    return "";
                }
            }
            
            std::string MonitorLevel::Read(MonitorFunction f)
            {
                return fmt::format("ML{:01d};", static_cast<int>(f));
            }
            
            MonitorLevelValue MonitorLevel::Answer(std::string data)
            {
                MonitorLevelValue ret;
                ret.f = static_cast<MonitorFunction>(std::stoi(data.substr(2,1)));
                switch(ret.f)
                {
                    case MonitorFunction::OnOff:
                    {
                        ret.val.eVal = static_cast<OnOffValue>(std::stoi(data.substr(3,3)));
                        break;
                    }
                    case MonitorFunction::Level:
                    {
                        ret.val.iVal = std::stoi(data.substr(3,3));
                        break;
                    }

                }
                return ret;
            }
            
            
            
            std::string MemoryChannelRead::Read(MemoryChannelValue chan)
            {
                return fmt::format("MR{:03d};",static_cast<int>(chan));
            }
            
            MemoryChannelTag MemoryChannelRead::Answer(std::string data)
            {
                MemoryChannelTag ret;
                ret.MemoryChannel = static_cast<MemoryChannelValue>(std::stoi(data.substr(2,3)));
                ret.VFOAFreq = std::stoi(data.substr(5, 9));
                ret.ClarifierFreq = std::stoi(data.substr(14,5));
                ret.RxClarifier = static_cast<ClarifierState>(std::stoi(data.substr(19,1)));
                ret.TxClarifier = static_cast<ClarifierState>(std::stoi(data.substr(20,1)));
                ret.Mode = static_cast<ModeValue>(std::stoi(data.substr(21,1),0,16));
                ret.VFO = static_cast<VFOChannelTypeValue>(std::stoi(data.substr(22,1)));
                ret.CTCSS = static_cast<CTCSSState>(std::stoi(data.substr(23,1)));
                ret.Operation = static_cast<OperationType>(std::stoi(data.substr(26,1)));
                ret.Tag = "";
                return ret;
            }
            
            std::string MeterSW::Set(MeterType value)
            {   
                return fmt::format("MS{:01d};",static_cast<int>(value));
            }
            
            std::string MeterSW::Read()
            {
                return "MS;";
            }
            
            MeterType MeterSW::Answer(std::string data)
            {
                return static_cast<MeterType>(std::stoi(data.substr(2,1)));
            }
            
            std::string MemoryChannelWriteTag::Set(MemoryChannelTag value)
            {
                return fmt::format("MT{:03d}{:09d}{:05d}{:01d}{:01d}{:01x}0{:01d}00{:01d}0{};",
                static_cast<int>(value.MemoryChannel),
                value.VFOAFreq,
                value.ClarifierFreq,
                static_cast<int>(value.RxClarifier),
                static_cast<int>(value.TxClarifier),
                static_cast<int>(value.Mode),
                static_cast<int>(value.CTCSS),
                static_cast<int>(value.Operation),
                value.Tag.substr(0,12));
            }
            
            std::string MemoryChannelWriteTag::Read(MemoryChannelValue chan)
            {
                return fmt::format("MT{:03d};",static_cast<int>(chan));
            }
            
            MemoryChannelTag MemoryChannelWriteTag::Answer(std::string data)
            {
                MemoryChannelTag ret;
                ret.MemoryChannel = static_cast<MemoryChannelValue>(std::stoi(data.substr(2,3)));
                ret.VFOAFreq = std::stoi(data.substr(5, 9));
                ret.ClarifierFreq = std::stoi(data.substr(14,5));
                ret.RxClarifier = static_cast<ClarifierState>(std::stoi(data.substr(19,1)));
                ret.TxClarifier = static_cast<ClarifierState>(std::stoi(data.substr(20,1)));
                ret.Mode = static_cast<ModeValue>(std::stoi(data.substr(21,1),0,16));
                ret.VFO = static_cast<VFOChannelTypeValue>(std::stoi(data.substr(22,1)));
                ret.CTCSS = static_cast<CTCSSState>(std::stoi(data.substr(23,1)));
                ret.Operation = static_cast<OperationType>(std::stoi(data.substr(26,1)));
                ret.Tag = data.substr(27, data.find_first_of(';',27) - 28);
                return ret;
            }
            
            std::string MemoryChannelWrite(MemoryChannelTag value)
            {
                return fmt::format("MT{:03d}{:09d}{:05d}{:01d}{:01d}{:01x}0{:01d}00{:01d};",
                static_cast<int>(value.MemoryChannel),
                value.VFOAFreq,
                value.ClarifierFreq,
                static_cast<int>(value.RxClarifier),
                static_cast<int>(value.TxClarifier),
                static_cast<int>(value.Mode),
                static_cast<int>(value.CTCSS),
                static_cast<int>(value.Operation));
            }

            std::string MoxSet::Set(OnOffValue value)
            {
                return fmt::format("MX{:01d};",static_cast<int>(value));
            }
            
            std::string MoxSet::Read()
            {
                return "MX;";
            }
            
            OnOffValue MoxSet::Answer(std::string data)
            {
                return static_cast<OnOffValue>(std::stoi(data.substr(2,1)));
            }
            
            std::string Narrow::Set(OnOffValue value)
            {
                return fmt::format("MA0{:01d};",static_cast<int>(value));
            }
            
            std::string Narrow::Read()
            {
                return "MA0;";
            }
            
            OnOffValue Narrow::Answer(std::string data)
            {
                return static_cast<OnOffValue>(std::stoi(data.substr(3,1)));
            }
            
            std::string NoiseBlankerStatus::Set(OnOffValue value)
            {
                return fmt::format("NB0{:01d};",static_cast<int>(value));
            }
            
            std::string NoiseBlankerStatus::Read()
            {
                return "NB0;";
            }
            
            OnOffValue NoiseBlankerStatus::Answer(std::string data)
            {
                return static_cast<OnOffValue>(std::stoi(data.substr(3,1)));
            }
            
            std::string NoiseBlankerLevel::Set(int value)
            {
                value = value > 10 ? 10 : value;
                value = value < 0 ? 0 : value;
                return fmt::format("NL0{:03d};", value);
            }
            
            std::string NoiseBlankerLevel::Read()
            {
                return "NL0;";
            }
            
            int NoiseBlankerLevel::Answer(std::string data)
            {
                return std::stoi(data.substr(3,3));
            }
            
            std::string NoiseReduction::Set(OnOffValue value)
            {
                return fmt::format("NR0{:01d};",static_cast<int>(value));
            }
            
            std::string NoiseReduction::Read()
            {
                return "NR0;";
            }
            
            OnOffValue NoiseReduction::Answer(std::string data)
            {
                return static_cast<OnOffValue>(std::stoi(data.substr(3,1)));
            }
            
            std::string OppisateBandInformation::Read()
            {
                return "OI;";
            }
            
            OppositeInformationValue OppisateBandInformation::Answer(std::string data)
            {
                OppositeInformationValue ret;
                ret.MemoryChannel = static_cast<MemoryChannelValue>(std::stoi(data.substr(2,3)));
                ret.VFOBFreq = std::stoi(data.substr(5, 9));
                ret.ClarifierFreq = std::stoi(data.substr(14,5));
                ret.RxClarifier = static_cast<ClarifierState>(std::stoi(data.substr(19,1)));
                ret.TxClarifier = static_cast<ClarifierState>(std::stoi(data.substr(20,1)));
                ret.Mode = static_cast<ModeValue>(std::stoi(data.substr(21,1),0,16));
                ret.VFO = static_cast<VFOChannelTypeValue>(std::stoi(data.substr(22,1)));
                ret.CTCSS = static_cast<CTCSSState>(std::stoi(data.substr(23,1)));
                ret.Operation = static_cast<OperationType>(std::stoi(data.substr(26,1)));

                return ret;    
            }

            
            std::string Offset::Set(OperationType value)
            {
                return fmt::format("OS0{:01d};",static_cast<int>(value));
            }
            
            std::string Offset::Read()
            {
                return "OS0;";
            }
            
            OperationType Offset::Answer(std::string data)
            {
                return static_cast<OperationType>(std::stoi(data.substr(3,1)));
            }
            
            std::string PreAmp::Set(PreampType value)
            {
                return fmt::format("PA0{:01d};",static_cast<int>(value));
            }
            
            std::string PreAmp::Read()
            {
                return "PA0;";
            }
            
            PreampType PreAmp::Answer(std::string data)
            {
                return static_cast<PreampType>(std::stoi(data.substr(3,1)));
            }
            
            std::string PlayBack::Set(DVSRecordingValue value)
            {
                return fmt::format("PB0{:01d};",static_cast<int>(value));
            }
            
            std::string PlayBack::Read()
            {
                return "PB0;";
            }
            
            DVSRecordingValue PlayBack::Answer(std::string data)
            {
                return static_cast<DVSRecordingValue>(std::stoi(data.substr(3,1)));
            }
            
            std::string PowerControl::Set(int value)
            {
                value = value < 5 ? 5 : value;
                value = value > 100 ? 100 : value;
                return fmt::format("PC{:03d};",value);
            }
            
            std::string PowerControl::Read()
            {
                return "PC;";
            }
            
            int PowerControl::Answer(std::string data)
            {
                return std::stoi(data.substr(2,3));
            }
            
            std::string SpeechProcessorLevel::Set(int value)
            {
                return fmt::format("PL{:03d};",value);
            }
            
            std::string SpeechProcessorLevel::Read()
            {
                return "PL;";
            }
            
            int SpeechProcessorLevel::Answer(std::string data)
            {
                return std::stoi(data.substr(2,3));
            }
            
            std::string SpeechProcessor::Set(SpeechProcessorSetting value)
            {
                return fmt::format("PR{:01d}{:01d};", static_cast<int>(value.Type),
                    static_cast<int>(value.State));
            }
            
            std::string SpeechProcessor::Read(SpeechProcessorType type)
            {
                return fmt::format("PR{:01d};",static_cast<int>(type));
            }
            
            SpeechProcessorSetting SpeechProcessor::Answer(std::string data)
            {
                SpeechProcessorSetting ret;
                ret.Type = static_cast<SpeechProcessorType>(std::stoi(data.substr(2,1)));
                ret.State = static_cast<OnOffValue>(std::stoi(data.substr(3,1)));
                return ret;
            }
            
            std::string PowerSwitch::Set(OnOffValue value)
            {
                return fmt::format("PS{:01d};",static_cast<int>(value));
            }
            
            std::string PowerSwitch::Read()
            {
                return "PS;";
            }
            
            OnOffValue PowerSwitch::Answer(std::string data)
            {
                return static_cast<OnOffValue>(std::stoi(data.substr(2,1)));
            }
            
            std::string QMB_Store::Set()
            {       
                return "QI;";   
            }
            
            std::string QMB_Recall::Set()
            {
                return "QR;";
            }

            std::string QuickSplit::Set()
            {
                return "QS;";
            }

            std::string RFAttenuator::Set(OnOffValue value)
            {
                return fmt::format("RA0{:01d};",static_cast<int>(value));
            }
            
            std::string RFAttenuator::Read()
            {
                return "RA0;";
            }
            
            OnOffValue RFAttenuator::Answer(std::string data)
            {
                return static_cast<OnOffValue>(std::stoi(data.substr(3,1)));
            }
            
            std::string ClarClear::Set()
            {
                return "RC;";
            }
            std::string ClarDown::Set(int value)
            {
                value = value > 9999 ? 9999 : value;
                value = value < 0 ? 0 : value;
                return fmt::format("RD{:04d};", value);
            }

            std::string RFGain::Set(int value)
            {
                value = value > 255 ? 255 : value;
                value = value < 0 ? 0 : value;                
                return fmt::format("RG0{:03d};", value);
            }
            
            std::string RFGain::Read()
            {
                return "RG0;";
            }
            
            int RFGain::Answer(std::string data)
            {
                return std::stoi(data.substr(3,3));
            }
            
           
            
            std::string RadioInformation::Read(RadioInformationType type)
            {
                return fmt::format("RI{:01d};",static_cast<int>(type));
            }
            
            RadioInformationValue RadioInformation::Answer(std::string data)
            {
                RadioInformationValue ret;
                ret.Type = static_cast<RadioInformationType>(std::stoi(data.substr(2,1)));
                ret.State = static_cast<OnOffValue>(std::stoi(data.substr(3,1)));
                return ret;
            }
            
            std::string NoiseReductionLevel::Set(int value)
            {
                value = value > 15 ? 15 : value;
                value = value < 1 ? 1 : value;
                return fmt::format("RL0{:02d};",value);
            }
            
            std::string NoiseReductionLevel::Read()
            {
                return "RL0;";
            }
            
            int NoiseReductionLevel::Answer(std::string data)
            {
                return std::stoi(data.substr(3,2));
            }
        
            std::string ReadMeter::Read(ReadMeterType value)
            {
                return fmt::format("RM{:01d};", static_cast<int>(value));
            }
            
            ReadMeterValue ReadMeter::Answer(std::string data)
            {   
                ReadMeterValue ret;
                ret.Type = static_cast<ReadMeterType>(std::stoi(data.substr(2,1)));
                ret.Value = std::stoi(data.substr(3,3));
                return ret;
            }
            
                        
            std::string RadioStatus::Read()
            {
                return "RS;";
            }
            
            RadioStatusType RadioStatus::Answer(std::string data)
            {
                return static_cast<RadioStatusType>(std::stoi(data.substr(2,1)));
            }
            
            std::string RXClarifier::Set(OnOffValue value)
            {
                return fmt::format("RT{:01d};",static_cast<int>(value));
            }
            
            std::string RXClarifier::Read()
            {
                return "RT;";
            }
            
            OnOffValue RXClarifier::Answer(std::string data)
            {
                return static_cast<OnOffValue>(std::stoi(data.substr(2,1)));
            }
            
            std::string RXClarifierPlusOffset::Set(int value)
            {
                value = value < 0 ? 0 : value;
                value = value > 9999 ? 9999 : value;
                return fmt::format("RU{:04d};",value);
            }

            std::string Scan::Set(ScanType value)
            {
                return fmt::format("SC{:01d};",static_cast<int>(value));
            }
            
            std::string Scan::Read()
            {
                return "SC;";
            }
            
            ScanType Scan::Answer(std::string data)
            {
                return static_cast<ScanType>(std::stoi(data.substr(2,1)));
            }
            
            std::string Width::Set(int value)
            {
                return fmt::format("SH0{:02d};", value);
            }
            
            std::string Width::Read()
            {
                return "SH0;";
            }
            
            int Width::Answer(std::string data)
            {
                return std::stoi(data.substr(3,2));
            }
            
                        
            std::string SMeterReading::Read()
            {
                return "SM0;";
            }
            
            int SMeterReading::Answer(std::string data)
            {
                return std::stoi(data.substr(3,3));
            }
            
            std::string SquelchLevel::Set(int value)
            {
                value = value > 100 ? 100 : value;
                value = value < 0 ? 0 : value;
                return fmt::format("SQ0{:03d};",value);
            }
            
            std::string SquelchLevel::Read()
            {
                return "SQ0;";
            }
            
            int SquelchLevel::Answer(std::string data)
            {
                return std::stoi(data.substr(3,3));
            }
            
            std::string SwapVFO::Set()
            {
                return "SV;";
            }

            std::string TXW::Set(OnOffValue value)
            {
                return fmt::format("TS{:01d};",static_cast<int>(value));
            }
            
            std::string TXW::Read()
            {
                return "TS;";
            }
            
            OnOffValue TXW::Answer(std::string data)
            {
                return static_cast<OnOffValue>(std::stoi(data.substr(2,1)));
            }
            
            std::string TXSet::Set(TXSetType value)
            {
                return fmt::format("TX{:01d};",static_cast<int>(value));
            }
            
            std::string TXSet::Read()
            {
                return "TX;";
            }
            
            TXSetType TXSet::Answer(std::string data)
            {
                return static_cast<TXSetType>(std::stoi(data.substr(2,1)));
            }
            
            
            std::string PLLUnlockStatus::Read()
            {
                return "UL;";
            }
            
            PLLLockType PLLUnlockStatus::Answer(std::string data)
            {
                return static_cast<PLLLockType>(std::stoi(data.substr(2,1)));
            }
            
            std::string UP::Set()
            {
                return "UP;";
            }

            std::string VoxDelayTime::Set(int value)
            {
                value = value < 30 ? 30 : value;
                value = value > 3000 ? 3000 : value;
                return fmt::format("VD{:04d};",value);
            }
            
            std::string VoxDelayTime::Read()
            {
                return "VD;";
            }
            
            int VoxDelayTime::Answer(std::string data)
            {
                return std::stoi(data.substr(2,4));
            }

            std::string VoxGain::Set(int value)
            {
                value = value < 0 ? 0 : value;
                value = value > 100 ? 100 : value;
                return fmt::format("VG{:03d};",value);
            }
            
            std::string VoxGain::Read()
            {
                return "VG;";
            }
            
            int VoxGain::Answer(std::string data)
            {
                return std::stoi(data.substr(2,3));
            }
            
            std::string VFOA_To_Memory::Set()
            {
                return "VM;";
            }

            std::string VoxStatus::Set(OnOffValue value)
            {
                return fmt::format("VX{:01d};", static_cast<int>(value));
            }
            
            std::string VoxStatus::Read()
            {
                return "VX;";
            }
            
            OnOffValue VoxStatus::Answer(std::string data)
            {
                return static_cast<OnOffValue>(std::stoi(data.substr(2,1)));
            }
            
            std::string TXClarifier::Set(OnOffValue value)
            {
                return fmt::format("XT{:01d};", static_cast<int>(value));
            }
            
            std::string TXClarifier::Read()
            {
                return "XT;";
            }
            
            OnOffValue TXClarifier::Answer(std::string data)
            {
                 return static_cast<OnOffValue>(std::stoi(data.substr(2,1)));
            }

            std::string ZeroIn::Set()
            {
                return "ZI;";
            }
        }    

        namespace FTDX101
        {
            std::string MainToSub::Set()
            {
                return "AB;";
            }

            std::string AntennaTunerControl::Set(TunerState state)
            {
                std::string str = fmt::format("AC00{:d};", static_cast<int>(state));
                return str.c_str();
            }

            std::string AntennaTunerControl::Read()
            {
                return "AC;";
            }

            TunerState AntennaTunerControl::Answer(const std::string& data)
            {
                return (TunerState)std::stoi(data.substr(3, 1));
            }

            std::string VolumeLevel::Set(MainSubValue band, int Value)
            {
                Value = Value > 255 ? 255 : Value;
                Value = Value < 0 ? 0 : Value;
                return fmt::format("AG{:01}{:03};", Value, static_cast<int>(band));
            }

            std::string VolumeLevel::Read(MainSubValue band)
            {
                return fmt::format("AG{:01};",static_cast<int>(band));
            }

            VolumeValue VolumeLevel::Answer(std::string data)
            {
                int b = std::stoi(data.substr(2,1));
                VolumeValue ret {static_cast<MainSubValue>(b),
                                 std::stoi(data.substr(3,3))};
                return ret;
            }

            std::string AutoInformation::Set(InformationState Value)
            {
                std::string str = fmt::format("AI{};", static_cast<int>(Value));
                return str;
            }

            std::string AutoInformation::Read()
            {
                return "AI;";
            }

            InformationState AutoInformation::Answer(std::string data)
            {
                return (InformationState)std::stoi(data.substr(2, 1));
            }

            std::string MainBandToMemoryChannel::Set()
            {
                return "AM;";
            }

            std::string AntennaNumber::Set(MainSubValue band, AntennaNumberSelection ant)
            {
                return fmt::format("AN{:01}{:01};",static_cast<int>(band),
                static_cast<int>(ant));
            }

            std::string AntennaNumber::Set(AntennaNumberValue val)
            {
                return fmt::format("AN{:01}{:01};",static_cast<int>(val.band),
                                                   static_cast<int>(val.value));
            }

            std::string AntennaNumber::Read(MainSubValue band)
            {
                return fmt::format("AN{:01};",static_cast<int>(band));
            }

            AntennaNumberValue AntennaNumber::Answer(std::string data)
            {
                AntennaNumberValue ret;
                ret.band = static_cast<MainSubValue>(std::stoi(data.substr(2,1)));
                ret.value = static_cast<AntennaNumberSelection>(std::stoi(data.substr(3,1)));
                return ret;
            }

            std::string AMCOutputLevel::Set(int value)
            {
                return fmt::format("AO{:03};",value);
            }

            std::string AMCOutputLevel::Read()
            {
                return "AO;";
            }

            int AMCOutputLevel::Answer(std::string data)
            {
                return std::stoi(data.substr(2,3));
            }

            std::string SubBandToMainBand::Set()
            {
                return "BA";
            }

            std::string AutoNotch::Set(MainSubValue band, OnOffValue value)
            {
                return fmt::format("BC{:01}{:01};", static_cast<int>(band), static_cast<int>(value));
            }

            std::string AutoNotch::Set(AutoNotchValue value)
            {
                return fmt::format("BC{:01}{:01};", static_cast<int>(value.band), static_cast<int>(value.state));
            }

            std::string AutoNotch::Read(MainSubValue band)
            {
                return fmt::format("BC{:01};", static_cast<int>(band));
            }

            AutoNotchValue AutoNotch::Answer(std::string data)
            {
                AutoNotchValue ret;
                ret.band = static_cast<MainSubValue>(std::stoi(data.substr(2,1)));
                ret.state = static_cast<OnOffValue>(std::stoi(data.substr(3,1)));
                return ret;
            }

            std::string BandDown::Set(MainSubValue band)
            {
                return fmt::format("BD{:01};", static_cast<int>(band));
            }

            std::string BreakIn::Set(OnOffValue value)
            {
                return fmt::format("BI{:01};", static_cast<int>(value));
            }

            std::string BreakIn::Read()
            {
                return "BI;";
            }

            OnOffValue BreakIn::Answer(std::string data)
            {
                return static_cast<OnOffValue>(std::stoi(data.substr(2,1)));
            }

            std::string ChannelUpDown(UpDownValue value)
            {
                return fmt::format("CH{:01};",static_cast<int>(value));
            }

            std::string CTCSSToneFrequency::Set(MainSubValue band, int value)
            {
                return fmt::format("CN{:01}0{:03};", static_cast<int>(band),value);
            }

            std::string CTCSSToneFrequency::Read(MainSubValue band)
            {
                return fmt::format("CN{:01}0;", static_cast<int>(band));
            }

            CTCSSToneValue CTCSSToneFrequency::Answer(std::string data)
            {
                CTCSSToneValue ret;
                ret.band = static_cast<MainSubValue>(std::stoi(data.substr(2,1)));
                ret.value = std::stoi(data.substr(4,3));
                return ret;
            }

            std::string SubBandToMemoryChannel::Set()
            {
                return "BM;";
            }

            std::string ManualNotch::Set(MainSubValue band,ManualNotchValueType type,int value)
            {
                return fmt::format("BP{:01}{:01}{:03};",
                                    static_cast<int>(band),
                                    static_cast<int>(type),
                                    value);
            }

            std::string ManualNotch::Set(ManualNotchValue value)
            {
                return fmt::format("BP{:01}{:01}{:03};",
                                   static_cast<int>(value.band),
                                   static_cast<int>(value.type),
                                   value.value);

            }

            std::string ManualNotch::Read(ManualNotchValue value)
            {
                return fmt::format("BP{:01}{:01};",
                static_cast<int>(value.band),
                static_cast<int>(value.type));
            }

            std::string ManualNotch::Read(MainSubValue band,ManualNotchValueType type)
            {
                return fmt::format("BP{:01}{:01};",
                static_cast<int>(band),
                static_cast<int>(type));

            }

            ManualNotchValue ManualNotch::Answer(std::string data)
            {
                ManualNotchValue ret;
                ret.band = static_cast<MainSubValue>(std::stoi(data.substr(2,1)));
                ret.type = static_cast<ManualNotchValueType>(std::stoi(data.substr(3,1)));
                ret.value = std::stoi(data.substr(4,3));
                return ret;
            }

            std::string BandSelect::Set(BandSelectValue val)
            {
                return fmt::format("BS{:02};",static_cast<int>(val));
            }

            std::string BandUp::Set(MainSubValue value)
            {
                return fmt::format("BU{:01};", static_cast<int>(value));
            }

            std::string Busy::Read()
            {
                return "BY;";
            }

            BusyStateValue Busy::Answer(std::string data)
            {
                BusyStateValue ret;
                ret.band = static_cast<MainSubValue>(std::stoi(data.substr(2,1)));
                ret.state = static_cast<OnOffValue>(std::stoi(data.substr(3,1)));
                return ret;
            }

            std::string Contour::Set(ContourStateValue value)
            {
                return fmt::format("CO{:01}{:01}{:04};",
                    static_cast<int>(value.band),
                    static_cast<int>(value.type),
                    value.RequestValue);
            }

            std::string Contour::Set(MainSubValue band,ContourRequestType type, int value)
            {
                return fmt::format("CO{:01}{:01}{:04};",
                static_cast<int>(band),
                static_cast<int>(type),
                value);
            }

            std::string Contour::Read(ContourStateValue value)
            {
                return fmt::format("CO{:01}{:01};",
                static_cast<int>(value.band),
                static_cast<int>(value.type));
            }

            std::string Contour::Read(MainSubValue band, ContourRequestType type)
            {
                return fmt::format("CO{:01}{:01};",
                static_cast<int>(band),
                static_cast<int>(type));
            }

            ContourStateValue Contour::Answer(std::string data)
            {
                ContourStateValue ret;
                ret.band = static_cast<MainSubValue>(std::stoi(data.substr(2,1)));
                ret.type = static_cast<ContourRequestType>(std::stoi(data.substr(3,1)));
                ret.RequestValue = std::stoi(data.substr(4,4));
                return ret;
            }

            std::string CWSpot::Set(OnOffValue value)
            {
                return fmt::format("CS{:01};",
                static_cast<int>(value));
            }

            std::string CWSpot::Read()
            {
                return "CS;";
            }

            OnOffValue CWSpot::Answer(std::string data)
            {
                return static_cast<OnOffValue>(std::stoi(data.substr(2,1)));
            }

            std::string CTCSS::Set(CTCSSStateValue value)
            {
                return fmt::format("CT{:01}{:01};",
                static_cast<int>(value.band),
                static_cast<int>(value.type));
            }

            std::string CTCSS::Set(MainSubValue band,CTCSSType type)
            {
                return fmt::format("CT{:01}{:01};",
                static_cast<int>(band),
                static_cast<int>(type));
            }

            std::string CTCSS::Read(CTCSSStateValue value)
            {
                return fmt::format("CT{:01};",
                static_cast<int>(value.band));
            }

            std::string CTCSS::Read(MainSubValue band)
            {
                return fmt::format("CT{:01};",
                static_cast<int>(band));
            }

            CTCSSStateValue CTCSS::Answer(std::string data)
            {
                CTCSSStateValue ret;
                ret.band = static_cast<MainSubValue>(std::stoi(data.substr(2,1)));
                ret.type = static_cast<CTCSSType>(std::stoi(data.substr(3,1)));
                return ret;
            }

            std::string Dimmer::Set(DimmerValue value)
            {
                return fmt::format("DA0000{:02}{:02};",
                static_cast<int>(value.TFTBrightness),
                static_cast<int>(value.LEDIndicatorBrightness));
            }

            std::string Dimmer::Set(int TFT,int LED)
            {
                return fmt::format("DA0000{:02}{:02};",
                TFT,
                LED);
            }

            std::string Dimmer::Read()
            {
                return "DA;";
            }

            DimmerValue Dimmer::Answer(std::string data)
            {
                DimmerValue ret;
                ret.TFTBrightness = std::stoi(data.substr(6,2));
                ret.LEDIndicatorBrightness = std::stoi(data.substr(8,2));
                return ret;
            }

            std::string MicDown::Set()
            {
                return "DN;";
            }

            std::string DateAndTime::Set(DateTimeType type ,std::string value)
            {
                return fmt::format("DT{:01}{};",
                static_cast<int>(type),
                value);
            }

            std::string DateAndTime::Set(DateTimeValue value)
            {
                return fmt::format("DT{:01}{};",
                static_cast<int>(value.type),
                value.value);
            }

            std::string DateAndTime::Read(DateTimeType type)
            {
                return fmt::format("DT{:01};",
                static_cast<int>(type));
            }

            std::string DateAndTime::Read(DateTimeValue val)
            {
                return fmt::format("DT{:01};",
                static_cast<int>(val.type));
            }

            DateTimeValue DateAndTime::Answer(std::string data)
            {
                DateTimeValue ret;
                ret.type = static_cast<DateTimeType>(std::stoi(data.substr(2,1)));
                ret.value = data.substr(3, data.size() - 4);
                return ret;
            }

            std::string EncoderDown::Set(EncoderValue value)
            {
                return fmt::format("ED{:01}{:02};",
                static_cast<int>(value.type),
                value.value);
            }

            std::string EncoderDown::Set(EncoderType type, int value)
            {

                return fmt::format("ED{:01}{:02};",
                static_cast<int>(type),
                value);
            }

            std::string EnocdeMemory::Set(EncodeMemoryValue value)
            {
                return fmt::format("EM{:01}{:01}{};",
                static_cast<int>(value.format),
                value.channel,
                value.message.substr(0,50));
            }
            std::string EnocdeMemory::Set(EncodeFormat format,int channel,std::string message)
            {
                return fmt::format("EM{:01}{:01}{};",
                static_cast<int>(format),
                channel,
                message.substr(0,50));
            }
            std::string EnocdeMemory::Read(EncodeMemoryValue value)
            {
                return fmt::format("EM{:01d}{:01d};",
                static_cast<int>(value.format), value.channel);
            }

            std::string EnocdeMemory::Read(EncodeFormat format,int channel)
            {
                return fmt::format("EM{:01d}{:01d};", static_cast<int>(format),channel);
            }

            EncodeMemoryValue EnocdeMemory::Answer(std::string data)
            {
                //let's chop off the ending ; from the command;
                if(data.find_last_of(';') == data.length())
                    data = data.substr(0,data.length() - 1);

                EncodeMemoryValue ret;
                ret.format = static_cast<EncodeFormat>(std::stoi(data.substr(2,1)));
                ret.channel = std::stoi(data.substr(3,1));
                ret.message = data.substr(4,50);
                return ret;
            }

            std::string Encode::Set(EncodeFormat format, int channel)
            {
                return fmt::format("EN{:01}{:01};",
                static_cast<int>(format),
                channel);
            }

            std::string EncoderUp::Set(EncoderValue value)
            {
                return fmt::format("EU{:01}{:02};",
                static_cast<int>(value.type),
                value.value);
            }

            std::string EncoderUp::Set(EncoderType type, int value)
            {

                return fmt::format("EU{:01}{:02};",
                static_cast<int>(type),
                value);
            }



            std::string Menu::RadioSetting::SSB::AGC_Fast_Delay::Set(int msec)
            {
                return fmt::format("EX{:02}{:02}{:02}{:4}",
                static_cast<int>(MenuGroup::RadioSettings),
                static_cast<int>(RadioSettingsType::ModeSSB),
                static_cast<int>(SSBSettings::AGC_FAST_DELAY),
                msec);
            }

            std::string Menu::RadioSetting::SSB::AGC_Fast_Delay::Read()
            {
                return fmt::format("EX{:02}{:02}{:02};",
                static_cast<int>(MenuGroup::RadioSettings),
                static_cast<int>(RadioSettingsType::ModeSSB),
                static_cast<int>(SSBSettings::AGC_FAST_DELAY));
            }

            int Menu::RadioSetting::SSB::AGC_Fast_Delay::Answer(std::string data)
            {
                return std::stoi(data.substr(8,4));
            }

            std::string Menu::RadioSetting::SSB::AGC_Mid_Delay::Set(int msec)
            {
                return fmt::format("EX{:02d}{:02d}{:02d}{:04d}",
                static_cast<int>(MenuGroup::RadioSettings),
                static_cast<int>(RadioSettingsType::ModeSSB),
                static_cast<int>(SSBSettings::AGC_MID_DELAY),
                msec);
            }

            std::string Menu::RadioSetting::SSB::AGC_Mid_Delay::Read()
            {
                return fmt::format("EX{:02}{:02}{:02};",
                static_cast<int>(MenuGroup::RadioSettings),
                static_cast<int>(RadioSettingsType::ModeSSB),
                static_cast<int>(SSBSettings::AGC_MID_DELAY));
            }

            int Menu::RadioSetting::SSB::AGC_Mid_Delay::Answer(std::string data)
            {
                return std::stoi(data.substr(8,4));
            }

            std::string Menu::RadioSetting::SSB::AGC_Slow_Delay::Set(int msec)
            {
                return fmt::format("EX{:02}{:02}{:02}{:4}",
                static_cast<int>(MenuGroup::RadioSettings),
                static_cast<int>(RadioSettingsType::ModeSSB),
                static_cast<int>(SSBSettings::AGC_SLOW_DELAY),
                msec);
            }

            std::string Menu::RadioSetting::SSB::AGC_Slow_Delay::Read()
            {
                return fmt::format("EX{:02}{:02}{:02};",
                static_cast<int>(MenuGroup::RadioSettings),
                static_cast<int>(RadioSettingsType::ModeSSB),
                static_cast<int>(SSBSettings::AGC_SLOW_DELAY));
            }

            int Menu::RadioSetting::SSB::AGC_Slow_Delay::Answer(std::string data)
            {
                return std::stoi(data.substr(8,4));
            }

            std::string Menu::RadioSetting::SSB::LCUT_Freq::Set(FreqLowCutValue value)
            {
                return fmt::format("EX{:02}{:02}{:02}{:2}",
                static_cast<int>(MenuGroup::RadioSettings),
                static_cast<int>(RadioSettingsType::ModeSSB),
                static_cast<int>(SSBSettings::LCUT_FREQ),
                static_cast<int>(value));
            }

            std::string Menu::RadioSetting::SSB::LCUT_Freq::Read()
            {
                return fmt::format("EX{:02}{:02}{:02};",
                static_cast<int>(MenuGroup::RadioSettings),
                static_cast<int>(RadioSettingsType::ModeSSB),
                static_cast<int>(SSBSettings::LCUT_FREQ));
            }

            FreqLowCutValue Menu::RadioSetting::SSB::LCUT_Freq::Answer(std::string data)
            {
                return static_cast<FreqLowCutValue>(std::stoi(data.substr(8,2)));
            }

            std::string Menu::RadioSetting::SSB::LCUT_Slope::Set(SlopeValue value)
            {
                return fmt::format("EX{:02}{:02}{:02}{:01d}",
                static_cast<int>(MenuGroup::RadioSettings),
                static_cast<int>(RadioSettingsType::ModeSSB),
                static_cast<int>(SSBSettings::LCUT_SLOPE),
                static_cast<int>(value));
            }

            std::string Menu::RadioSetting::SSB::LCUT_Slope::Read()
            {
                return fmt::format("EX{:02}{:02}{:02};",
                static_cast<int>(MenuGroup::RadioSettings),
                static_cast<int>(RadioSettingsType::ModeSSB),
                static_cast<int>(SSBSettings::LCUT_SLOPE));
            }

            SlopeValue Menu::RadioSetting::SSB::LCUT_Slope::Answer(std::string data)
            {
                return static_cast<SlopeValue>(std::stoi(data.substr(8,1)));
            }

            std::string Menu::RadioSetting::SSB::HCUT_Freq::Set(FreqHighCutValue value)
            {
                return fmt::format("EX{:02d}{:02d}{:02d}{:02d}",
                static_cast<int>(MenuGroup::RadioSettings),
                static_cast<int>(RadioSettingsType::ModeSSB),
                static_cast<int>(SSBSettings::HCUT_FREQ),
                static_cast<int>(value));
            }

            std::string Menu::RadioSetting::SSB::HCUT_Freq::Read()
            {
                return fmt::format("EX{:02}{:02}{:02};",
                static_cast<int>(MenuGroup::RadioSettings),
                static_cast<int>(RadioSettingsType::ModeSSB),
                static_cast<int>(SSBSettings::HCUT_FREQ));
            }

            FreqHighCutValue Menu::RadioSetting::SSB::HCUT_Freq::Answer(std::string data)
            {
                return static_cast<FreqHighCutValue>(std::stoi(data.substr(8,2)));
            }

            std::string Menu::RadioSetting::SSB::HCUT_Slope::Set(SlopeValue value)
            {
                return fmt::format("EX{:02}{:02}{:02}{:1}",
                static_cast<int>(MenuGroup::RadioSettings),
                static_cast<int>(RadioSettingsType::ModeSSB),
                static_cast<int>(SSBSettings::HCUT_SLOPE),
                static_cast<int>(value));
            }

            std::string Menu::RadioSetting::SSB::HCUT_Slope::Read()
            {
                return fmt::format("EX{:02}{:02}{:02};",
                static_cast<int>(MenuGroup::RadioSettings),
                static_cast<int>(RadioSettingsType::ModeSSB),
                static_cast<int>(SSBSettings::HCUT_SLOPE));
            }

            SlopeValue Menu::RadioSetting::SSB::HCUT_Slope::Answer(std::string data)
            {
                return static_cast<SlopeValue>(std::stoi(data.substr(8,1)));
            }


            std::string  Menu::RadioSetting::SSB::OUT_SELECT::Set(MainSubValue value)
            {
                return fmt::format("EX{:02}{:02}{:02}{:01};",
                static_cast<int>(MenuGroup::RadioSettings),
                static_cast<int>(RadioSettingsType::ModeSSB),
                static_cast<int>(SSBSettings::OUT_SELECT),
                static_cast<int>(value));
            }

            std::string  Menu::RadioSetting::SSB::OUT_SELECT::Read()
            {
                return fmt::format("EX{:02}{:02}{:02};",
                static_cast<int>(MenuGroup::RadioSettings),
                static_cast<int>(RadioSettingsType::ModeSSB),
                static_cast<int>(SSBSettings::OUT_SELECT));
            }
            MainSubValue Menu::RadioSetting::SSB::OUT_SELECT::Answer(std::string data)
            {
                return static_cast<MainSubValue>(std::stoi(data.substr(8,1)));
            }


            std::string Menu::RadioSetting::SSB::OUT_LEVEL::Set(int level)
            {
                level = level > 100 ? 100 : level;
                level = level < 0 ? 0 : level;
                return fmt::format("EX{:02}{:02}{:02}{:03};",
                static_cast<int>(MenuGroup::RadioSettings),
                static_cast<int>(RadioSettingsType::ModeSSB),
                static_cast<int>(SSBSettings::OUT_LEVEL),
                level);
            }

            std::string Menu::RadioSetting::SSB::OUT_LEVEL::Read()
            {
                return fmt::format("EX{:02}{:02}{:02};",
                static_cast<int>(MenuGroup::RadioSettings),
                static_cast<int>(RadioSettingsType::ModeSSB),
                static_cast<int>(SSBSettings::OUT_LEVEL));
            }

            int Menu::RadioSetting::SSB::OUT_LEVEL::Answer(std::string data)
            {
                return std::stoi(data.substr(8,3));
            }

            std::string Menu::RadioSetting::SSB::TX_BPF_SEL::Set(TXBandPassValue value)
            {
                return fmt::format("EX{:02}{:02}{:02}{:01};",
                static_cast<int>(MenuGroup::RadioSettings),
                static_cast<int>(RadioSettingsType::ModeSSB),
                static_cast<int>(SSBSettings::TX_BPF_SEL),
                static_cast<int>(value));
            }

            std::string Menu::RadioSetting::SSB::TX_BPF_SEL::Read()
            {
                return fmt::format("EX{:02}{:02}{:02};",
                static_cast<int>(MenuGroup::RadioSettings),
                static_cast<int>(RadioSettingsType::ModeSSB),
                static_cast<int>(SSBSettings::TX_BPF_SEL));
            }

            TXBandPassValue Menu::RadioSetting::SSB::TX_BPF_SEL::Answer(std::string data)
            {
                return static_cast<TXBandPassValue>(std::stoi(data.substr(8,1)));
            }

            std::string Menu::RadioSetting::SSB::MOD_SOURCE::Set(ModulationSource value)
            {
                return fmt::format("EX{:02}{:02}{:02}{:01};",
                static_cast<int>(MenuGroup::RadioSettings),
                static_cast<int>(RadioSettingsType::ModeSSB),
                static_cast<int>(SSBSettings::MOD_SOURCE),
                static_cast<int>(value));
            }

            std::string Menu::RadioSetting::SSB::MOD_SOURCE::Read()
            {
                return fmt::format("EX{:02}{:02}{:02};",
                static_cast<int>(MenuGroup::RadioSettings),
                static_cast<int>(RadioSettingsType::ModeSSB),
                static_cast<int>(SSBSettings::MOD_SOURCE));
            }

            ModulationSource Menu::RadioSetting::SSB::MOD_SOURCE::Answer(std::string data)
            {
                return static_cast<ModulationSource>(std::stoi(data.substr(8,1)));
            }


            std::string Menu::RadioSetting::SSB::REAR_SELECT::Set(RearSelect value)
            {
                return fmt::format("EX{:02d}{:02d}{:02d}{:01d};",
                static_cast<int>(MenuGroup::RadioSettings),
                static_cast<int>(RadioSettingsType::ModeSSB),
                static_cast<int>(SSBSettings::REAR_SELECT),
                static_cast<int>(value));
            }

            std::string Menu::RadioSetting::SSB::REAR_SELECT::Read()
            {
                return fmt::format("EX{:02}{:02}{:02};",
                static_cast<int>(MenuGroup::RadioSettings),
                static_cast<int>(RadioSettingsType::ModeSSB),
                static_cast<int>(SSBSettings::REAR_SELECT));
            }

            RearSelect  Menu::RadioSetting::SSB::REAR_SELECT::Answer(std::string data)
            {
                return static_cast<RearSelect>(std::stoi(data.substr(8,1)));
            }

            std::string Menu::RadioSetting::SSB::RPORT_GAIN::Set(int value)
            {
                return fmt::format("EX{:02}{:02}{:02}{:03};",
                static_cast<int>(MenuGroup::RadioSettings),
                static_cast<int>(RadioSettingsType::ModeSSB),
                static_cast<int>(SSBSettings::RPORT_GAIN),
                static_cast<int>(value));
            }
            std::string Menu::RadioSetting::SSB::RPORT_GAIN::Read()
            {
                return fmt::format("EX{:02}{:02}{:02};",
                static_cast<int>(MenuGroup::RadioSettings),
                static_cast<int>(RadioSettingsType::ModeSSB),
                static_cast<int>(SSBSettings::RPORT_GAIN));
            }
            int Menu::RadioSetting::SSB::RPORT_GAIN::Answer(std::string data)
            {
                return std::stoi(data.substr(8,3));
            }

            std::string Menu::RadioSetting::SSB::RPTT_SELECT::Set(RPTTSelectValue value)
            {
                return fmt::format("EX{:02}{:02}{:02}{:01};",
                static_cast<int>(MenuGroup::RadioSettings),
                static_cast<int>(RadioSettingsType::ModeSSB),
                static_cast<int>(SSBSettings::RPPT_SELECT),
                static_cast<int>(value));
            }
            std::string Menu::RadioSetting::SSB::RPTT_SELECT::Read()
            {
                return fmt::format("EX{:02}{:02}{:02};",
                static_cast<int>(MenuGroup::RadioSettings),
                static_cast<int>(RadioSettingsType::ModeSSB),
                static_cast<int>(SSBSettings::RPPT_SELECT));
            }
            RPTTSelectValue Menu::RadioSetting::SSB::RPTT_SELECT::Answer(std::string data)
            {
                return static_cast<RPTTSelectValue>(std::stoi(data.substr(8,1)));
            }

            std::string Menu::RadioSetting::AM::AGC_Fast_Delay::Set(int value)
            {
                return fmt::format("EX{:02}{:02}{:02}{:04};",
                static_cast<int>(MenuGroup::RadioSettings),
                static_cast<int>(RadioSettingsType::ModeAM),
                static_cast<int>(AMSettings::AGC_FAST_DELAY),
                static_cast<int>(value));
            }
            std::string Menu::RadioSetting::AM::AGC_Fast_Delay::Read()
            {
                return fmt::format("EX{:02}{:02}{:02};",
                static_cast<int>(MenuGroup::RadioSettings),
                static_cast<int>(RadioSettingsType::ModeAM),
                static_cast<int>(AMSettings::AGC_FAST_DELAY));
            }
            int Menu::RadioSetting::AM::AGC_Fast_Delay::Answer(std::string data)
            {
                return std::stoi(data.substr(8,4));
            }

            std::string Menu::RadioSetting::AM::AGC_Mid_Delay::Set(int value)
            {
                return fmt::format("EX{:02}{:02}{:02}{:04};",
                static_cast<int>(MenuGroup::RadioSettings),
                static_cast<int>(RadioSettingsType::ModeAM),
                static_cast<int>(AMSettings::AGC_MID_DELAY),
                static_cast<int>(value));
            }
            std::string Menu::RadioSetting::AM::AGC_Mid_Delay::Read()
            {
                return fmt::format("EX{:02}{:02}{:02};",
                static_cast<int>(MenuGroup::RadioSettings),
                static_cast<int>(RadioSettingsType::ModeAM),
                static_cast<int>(AMSettings::AGC_MID_DELAY));
            }
            int Menu::RadioSetting::AM::AGC_Mid_Delay::Answer(std::string data)
            {
                return std::stoi(data.substr(8,4));
            }

            std::string Menu::RadioSetting::AM::AGC_Slow_Delay::Set(int value)
            {
                return fmt::format("EX{:02}{:02}{:02}{:04};",
                static_cast<int>(MenuGroup::RadioSettings),
                static_cast<int>(RadioSettingsType::ModeAM),
                static_cast<int>(AMSettings::AGC_SLOW_DELAY),
                static_cast<int>(value));
            }
            std::string Menu::RadioSetting::AM::AGC_Slow_Delay::Read()
            {
                return fmt::format("EX{:02}{:02}{:02};",
                static_cast<int>(MenuGroup::RadioSettings),
                static_cast<int>(RadioSettingsType::ModeAM),
                static_cast<int>(AMSettings::AGC_SLOW_DELAY));
            }
            int Menu::RadioSetting::AM::AGC_Slow_Delay::Answer(std::string data)
            {
                return std::stoi(data.substr(8,4));
            }

            std::string Menu::RadioSetting::AM::LCUT_Freq::Set(FreqLowCutValue value)
            {
                return fmt::format("EX{:02}{:02}{:02}{:02};",
                static_cast<int>(MenuGroup::RadioSettings),
                static_cast<int>(RadioSettingsType::ModeAM),
                static_cast<int>(AMSettings::LCUT_FREQ),
                static_cast<int>(value));
            }

            std::string Menu::RadioSetting::AM::LCUT_Freq::Read()
            {
                return fmt::format("EX{:02}{:02}{:02};",
                static_cast<int>(MenuGroup::RadioSettings),
                static_cast<int>(RadioSettingsType::ModeAM),
                static_cast<int>(AMSettings::LCUT_FREQ));
            }

            FreqLowCutValue Menu::RadioSetting::AM::LCUT_Freq::Answer(std::string data)
            {
                return static_cast<FreqLowCutValue>(std::stoi(data.substr(8,2)));
            }

            std::string Menu::RadioSetting::AM::LCUT_Slope::Set(SlopeValue value)
            {
                return fmt::format("EX{:02}{:02}{:02}{:01};",
                static_cast<int>(MenuGroup::RadioSettings),
                static_cast<int>(RadioSettingsType::ModeAM),
                static_cast<int>(AMSettings::LCUT_SLOPE),
                static_cast<int>(value));
            }

            std::string Menu::RadioSetting::AM::LCUT_Slope::Read()
            {
                return fmt::format("EX{:02}{:02}{:02};",
                static_cast<int>(MenuGroup::RadioSettings),
                static_cast<int>(RadioSettingsType::ModeAM),
                static_cast<int>(AMSettings::LCUT_SLOPE));
            }

            SlopeValue Menu::RadioSetting::AM::LCUT_Slope::Answer(std::string data)
            {
                return static_cast<SlopeValue>(std::stoi(data.substr(8,1)));
            }

            std::string Menu::RadioSetting::AM::OUT_SELECT::Set(MainSubValue value)
            {
                return fmt::format("EX{:02}{:02}{:02}{:01};",
                static_cast<int>(MenuGroup::RadioSettings),
                static_cast<int>(RadioSettingsType::ModeAM),
                static_cast<int>(AMSettings::OUT_SELECT),
                static_cast<int>(value));
            }

            std::string Menu::RadioSetting::AM::OUT_SELECT::Read()
            {
                return fmt::format("EX{:02}{:02}{:02};",
                static_cast<int>(MenuGroup::RadioSettings),
                static_cast<int>(RadioSettingsType::ModeAM),
                static_cast<int>(AMSettings::OUT_SELECT));
            }

            MainSubValue Menu::RadioSetting::AM::OUT_SELECT::Answer(std::string data)
            {
                return static_cast<MainSubValue>(std::stoi(data.substr(8,1)));
            }

            std::string Menu::RadioSetting::AM::OUT_LEVEL::Set(int value)
            {
                return fmt::format("EX{:02}{:02}{:02}{:03};",
                static_cast<int>(MenuGroup::RadioSettings),
                static_cast<int>(RadioSettingsType::ModeAM),
                static_cast<int>(AMSettings::OUT_LEVEL),
                static_cast<int>(value));
            }
            std::string Menu::RadioSetting::AM::OUT_LEVEL::Read()
            {
                return fmt::format("EX{:02}{:02}{:02};",
                static_cast<int>(MenuGroup::RadioSettings),
                static_cast<int>(RadioSettingsType::ModeAM),
                static_cast<int>(AMSettings::OUT_LEVEL));
            }

            int Menu::RadioSetting::AM::OUT_LEVEL::Answer(std::string data)
            {
                return std::stoi(data.substr(8,3));
            }

            std::string Menu::RadioSetting::AM::TX_BPF_SEL::Set(TXBandPassValue value)
            {
                return fmt::format("EX{:02}{:02}{:02}{:01};",
                static_cast<int>(MenuGroup::RadioSettings),
                static_cast<int>(RadioSettingsType::ModeAM),
                static_cast<int>(AMSettings::TX_BPF_SEL),
                static_cast<int>(value));
            }

            std::string Menu::RadioSetting::AM::TX_BPF_SEL::Read()
            {
                return fmt::format("EX{:02}{:02}{:02};",
                static_cast<int>(MenuGroup::RadioSettings),
                static_cast<int>(RadioSettingsType::ModeAM),
                static_cast<int>(AMSettings::TX_BPF_SEL));
            }

            TXBandPassValue Menu::RadioSetting::AM::TX_BPF_SEL::Answer(std::string data)
            {
                return static_cast<TXBandPassValue>(std::stoi(data.substr(8,1)));
            }

            std::string Menu::RadioSetting::AM::MOD_SOURCE::Set(ModulationSource value)
            {
                return fmt::format("EX{:02}{:02}{:02}{:01};",
                static_cast<int>(MenuGroup::RadioSettings),
                static_cast<int>(RadioSettingsType::ModeAM),
                static_cast<int>(AMSettings::MOD_SOURCE),
                static_cast<int>(value));
            }

            std::string Menu::RadioSetting::AM::MOD_SOURCE::Read()
            {
                return fmt::format("EX{:02}{:02}{:02};",
                static_cast<int>(MenuGroup::RadioSettings),
                static_cast<int>(RadioSettingsType::ModeAM),
                static_cast<int>(AMSettings::MOD_SOURCE));
            }

            ModulationSource Menu::RadioSetting::AM::MOD_SOURCE::Answer(std::string data)
            {
                return static_cast<ModulationSource>(std::stoi(data.substr(8,1)));
            }

            std::string Menu::RadioSetting::AM::REAR_SELECT::Set(RearSelect value)
            {
                return fmt::format("EX{:02}{:02}{:02}{:01};",
                static_cast<int>(MenuGroup::RadioSettings),
                static_cast<int>(RadioSettingsType::ModeAM),
                static_cast<int>(AMSettings::REAR_SELECT),
                static_cast<int>(value));
            }

            std::string Menu::RadioSetting::AM::REAR_SELECT::Read()
            {
                return fmt::format("EX{:02}{:02}{:02};",
                static_cast<int>(MenuGroup::RadioSettings),
                static_cast<int>(RadioSettingsType::ModeAM),
                static_cast<int>(AMSettings::REAR_SELECT));
            }

            RearSelect Menu::RadioSetting::AM::REAR_SELECT::Answer(std::string data)
            {
                return static_cast<RearSelect>(std::stoi(data.substr(8,1)));
            }

            std::string Menu::RadioSetting::AM::RPORT_GAIN::Set(int value)
            {
                return fmt::format("EX{:02}{:02}{:02}{:03};",
                static_cast<int>(MenuGroup::RadioSettings),
                static_cast<int>(RadioSettingsType::ModeAM),
                static_cast<int>(AMSettings::RPORT_GAIN),
                static_cast<int>(value));
            }

            std::string Menu::RadioSetting::AM::RPORT_GAIN::Read()
            {
                return fmt::format("EX{:02}{:02}{:02};",
                static_cast<int>(MenuGroup::RadioSettings),
                static_cast<int>(RadioSettingsType::ModeAM),
                static_cast<int>(AMSettings::RPORT_GAIN));
            }

            int Menu::RadioSetting::AM::RPORT_GAIN::Answer(std::string data)
            {
                return std::stoi(data.substr(8,3));
            }

            std::string Menu::RadioSetting::AM::RPTT_SELECT::Set(RPTTSelectValue value)
            {
                return fmt::format("EX{:02}{:02}{:02}{:01};",
                static_cast<int>(MenuGroup::RadioSettings),
                static_cast<int>(RadioSettingsType::ModeAM),
                static_cast<int>(AMSettings::RPORT_GAIN),
                static_cast<int>(value));
            }
            std::string Menu::RadioSetting::AM::RPTT_SELECT::Read()
            {
                return fmt::format("EX{:02}{:02}{:02};",
                static_cast<int>(MenuGroup::RadioSettings),
                static_cast<int>(RadioSettingsType::ModeAM),
                static_cast<int>(AMSettings::RPORT_GAIN));
            }

            RPTTSelectValue Menu::RadioSetting::AM::RPTT_SELECT::Answer(std::string data)
            {
                return static_cast<RPTTSelectValue>(std::stoi(data.substr(8,3)));
            }

            std::string Menu::RadioSetting::FM::AGC_Fast_Delay::Set(int value)
            {
                return fmt::format("EX{:02}{:02}{:02}{:04};",
                static_cast<int>(MenuGroup::RadioSettings),
                static_cast<int>(RadioSettingsType::ModeFM),
                static_cast<int>(FMSettings::AGC_FAST_DELAY),
                static_cast<int>(value));
            }
            std::string Menu::RadioSetting::FM::AGC_Fast_Delay::Read()
            {
                return fmt::format("EX{:02}{:02}{:02};",
                static_cast<int>(MenuGroup::RadioSettings),
                static_cast<int>(RadioSettingsType::ModeFM),
                static_cast<int>(FMSettings::AGC_FAST_DELAY));
            }
            int Menu::RadioSetting::FM::AGC_Fast_Delay::Answer(std::string data)
            {
                return std::stoi(data.substr(8,4));
            }

            std::string Menu::RadioSetting::FM::AGC_Mid_Delay::Set(int value)
            {
                return fmt::format("EX{:02}{:02}{:02}{:04};",
                static_cast<int>(MenuGroup::RadioSettings),
                static_cast<int>(RadioSettingsType::ModeFM),
                static_cast<int>(FMSettings::AGC_MID_DELAY),
                static_cast<int>(value));
            }
            std::string Menu::RadioSetting::FM::AGC_Mid_Delay::Read()
            {
                return fmt::format("EX{:02}{:02}{:02};",
                static_cast<int>(MenuGroup::RadioSettings),
                static_cast<int>(RadioSettingsType::ModeFM),
                static_cast<int>(FMSettings::AGC_MID_DELAY));
            }
            int Menu::RadioSetting::FM::AGC_Mid_Delay::Answer(std::string data)
            {
                return std::stoi(data.substr(8,4));
            }

            std::string Menu::RadioSetting::FM::AGC_Slow_Delay::Set(int value)
            {
                return fmt::format("EX{:02}{:02}{:02}{:04};",
                static_cast<int>(MenuGroup::RadioSettings),
                static_cast<int>(RadioSettingsType::ModeFM),
                static_cast<int>(FMSettings::AGC_SLOW_DELAY),
                static_cast<int>(value));
            }

            std::string Menu::RadioSetting::FM::AGC_Slow_Delay::Read()
            {
                return fmt::format("EX{:02}{:02}{:02};",
                static_cast<int>(MenuGroup::RadioSettings),
                static_cast<int>(RadioSettingsType::ModeFM),
                static_cast<int>(FMSettings::AGC_SLOW_DELAY));
            }

            int Menu::RadioSetting::FM::AGC_Slow_Delay::Answer(std::string data)
            {
                return std::stoi(data.substr(8,4));
            }

            std::string Menu::RadioSetting::FM::LCUT_Freq::Set(FreqLowCutValue value)
            {
                return fmt::format("EX{:02}{:02}{:02}{:02};",
                static_cast<int>(MenuGroup::RadioSettings),
                static_cast<int>(RadioSettingsType::ModeFM),
                static_cast<int>(FMSettings::LCUT_FREQ),
                static_cast<int>(value));
            }

            std::string Menu::RadioSetting::FM::LCUT_Freq::Read()
            {
                return fmt::format("EX{:02}{:02}{:02};",
                static_cast<int>(MenuGroup::RadioSettings),
                static_cast<int>(RadioSettingsType::ModeFM),
                static_cast<int>(FMSettings::LCUT_FREQ));
            }

            FreqLowCutValue Menu::RadioSetting::FM::LCUT_Freq::Answer(std::string data)
            {
                return static_cast<FreqLowCutValue>(std::stoi(data.substr(8,2)));
            }

            std::string Menu::RadioSetting::FM::LCUT_Slope::Set(SlopeValue value)
            {
                return fmt::format("EX{:02}{:02}{:02}{:01};",
                static_cast<int>(MenuGroup::RadioSettings),
                static_cast<int>(RadioSettingsType::ModeFM),
                static_cast<int>(FMSettings::LCUT_SLOPE),
                static_cast<int>(value));
            }
            std::string Menu::RadioSetting::FM::LCUT_Slope::Read()
            {
                return fmt::format("EX{:02}{:02}{:02};",
                static_cast<int>(MenuGroup::RadioSettings),
                static_cast<int>(RadioSettingsType::ModeFM),
                static_cast<int>(FMSettings::LCUT_SLOPE));
            }
            SlopeValue Menu::RadioSetting::FM::LCUT_Slope::Answer(std::string data)
            {
                return static_cast<SlopeValue>(std::stoi(data.substr(8,1)));
            }

            std::string Menu::RadioSetting::FM::HCUT_Freq::Set(FreqHighCutValue value)
            {
                return fmt::format("EX{:02}{:02}{:02}{:02};",
                static_cast<int>(MenuGroup::RadioSettings),
                static_cast<int>(RadioSettingsType::ModeFM),
                static_cast<int>(FMSettings::HCUT_FREQ),
                static_cast<int>(value));
            }

            std::string Menu::RadioSetting::FM::HCUT_Freq::Read()
            {
                return fmt::format("EX{:02}{:02}{:02};",
                static_cast<int>(MenuGroup::RadioSettings),
                static_cast<int>(RadioSettingsType::ModeFM),
                static_cast<int>(FMSettings::HCUT_FREQ));
            }

            FreqHighCutValue Menu::RadioSetting::FM::HCUT_Freq::Answer(std::string data)
            {
                return static_cast<FreqHighCutValue>(std::stoi(data.substr(8,2)));
            }

            std::string Menu::RadioSetting::FM::HCUT_Slope::Set(SlopeValue value)
            {
                return fmt::format("EX{:02}{:02}{:02}{:01};",
                static_cast<int>(MenuGroup::RadioSettings),
                static_cast<int>(RadioSettingsType::ModeFM),
                static_cast<int>(FMSettings::HCUT_SLOPE),
                static_cast<int>(value));
            }

            std::string Menu::RadioSetting::FM::HCUT_Slope::Read()
            {
                return fmt::format("EX{:02}{:02}{:02};",
                static_cast<int>(MenuGroup::RadioSettings),
                static_cast<int>(RadioSettingsType::ModeFM),
                static_cast<int>(FMSettings::HCUT_SLOPE));
            }

            SlopeValue Menu::RadioSetting::FM::HCUT_Slope::Answer(std::string data)
            {
                return static_cast<SlopeValue>(std::stoi(data.substr(8,1)));
            }

            std::string Menu::RadioSetting::FM::OUT_SELECT::Set(MainSubValue value)
            {
                return fmt::format("EX{:02}{:02}{:02}{:01};",
                static_cast<int>(MenuGroup::RadioSettings),
                static_cast<int>(RadioSettingsType::ModeFM),
                static_cast<int>(FMSettings::OUT_SELECT),
                static_cast<int>(value));
            }

            std::string Menu::RadioSetting::FM::OUT_SELECT::Read()
            {
                return fmt::format("EX{:02}{:02}{:02};",
                static_cast<int>(MenuGroup::RadioSettings),
                static_cast<int>(RadioSettingsType::ModeFM),
                static_cast<int>(FMSettings::OUT_SELECT));
            }

            MainSubValue Menu::RadioSetting::FM::OUT_SELECT::Answer(std::string data)
            {
                return static_cast<MainSubValue>(std::stoi(data.substr(8,1)));
            }

            std::string Menu::RadioSetting::FM::OUT_LEVEL::Set(int value)
            {
                return fmt::format("EX{:02}{:02}{:02}{:03};",
                static_cast<int>(MenuGroup::RadioSettings),
                static_cast<int>(RadioSettingsType::ModeFM),
                static_cast<int>(FMSettings::OUT_LEVEL),
                static_cast<int>(value));
            }

            std::string Menu::RadioSetting::FM::OUT_LEVEL::Read()
            {
                return fmt::format("EX{:02}{:02}{:02};",
                static_cast<int>(MenuGroup::RadioSettings),
                static_cast<int>(RadioSettingsType::ModeFM),
                static_cast<int>(FMSettings::OUT_LEVEL));
            }

            int Menu::RadioSetting::FM::OUT_LEVEL::Answer(std::string data)
            {
                return std::stoi(data.substr(8,3));
            }

            std::string Menu::RadioSetting::FM::MOD_SOURCE::Set(ModulationSource value)
            {
                return fmt::format("EX{:02}{:02}{:02}{:01};",
                static_cast<int>(MenuGroup::RadioSettings),
                static_cast<int>(RadioSettingsType::ModeFM),
                static_cast<int>(FMSettings::MOD_SOURCE),
                static_cast<int>(value));
            }

            std::string Menu::RadioSetting::FM::MOD_SOURCE::Read()
            {
                return fmt::format("EX{:02}{:02}{:02};",
                static_cast<int>(MenuGroup::RadioSettings),
                static_cast<int>(RadioSettingsType::ModeFM),
                static_cast<int>(FMSettings::MOD_SOURCE));
            }

            ModulationSource Menu::RadioSetting::FM::MOD_SOURCE::Answer(std::string data)
            {
                return static_cast<ModulationSource>(std::stoi(data.substr(8,1)));
            }

            std::string Menu::RadioSetting::FM::REAR_SELECT::Set(RearSelect value)
            {
                return fmt::format("EX{:02}{:02}{:02}{:01};",
                static_cast<int>(MenuGroup::RadioSettings),
                static_cast<int>(RadioSettingsType::ModeFM),
                static_cast<int>(FMSettings::REAR_SELECT),
                static_cast<int>(value));
            }

            std::string Menu::RadioSetting::FM::REAR_SELECT::Read()
            {
                return fmt::format("EX{:02}{:02}{:02};",
                static_cast<int>(MenuGroup::RadioSettings),
                static_cast<int>(RadioSettingsType::ModeFM),
                static_cast<int>(FMSettings::REAR_SELECT));
            }

            RearSelect Menu::RadioSetting::FM::REAR_SELECT::Answer(std::string data)
            {
                return static_cast<RearSelect>(std::stoi(data.substr(8,1)));
            }

            std::string Menu::RadioSetting::FM::RPORT_GAIN::Set(int value)
            {
                return fmt::format("EX{:02}{:02}{:02}{:03};",
                static_cast<int>(MenuGroup::RadioSettings),
                static_cast<int>(RadioSettingsType::ModeFM),
                static_cast<int>(FMSettings::RPORT_GAIN),
                static_cast<int>(value));
            }

            std::string Menu::RadioSetting::FM::RPORT_GAIN::Read()
            {
                return fmt::format("EX{:02}{:02}{:02};",
                static_cast<int>(MenuGroup::RadioSettings),
                static_cast<int>(RadioSettingsType::ModeFM),
                static_cast<int>(FMSettings::RPORT_GAIN));
            }

            int Menu::RadioSetting::FM::RPORT_GAIN::Answer(std::string data)
            {
                return std::stoi(data.substr(8,3));
            }

            std::string Menu::RadioSetting::FM::RPTT_SELECT::Set(RPTTSelectValue value)
            {
                return fmt::format("EX{:02}{:02}{:02}{:01};",
                static_cast<int>(MenuGroup::RadioSettings),
                static_cast<int>(RadioSettingsType::ModeFM),
                static_cast<int>(FMSettings::RPPT_SELECT),
                static_cast<int>(value));
            }

            std::string Menu::RadioSetting::FM::RPTT_SELECT::Read()
            {
                return fmt::format("EX{:02}{:02}{:02};",
                static_cast<int>(MenuGroup::RadioSettings),
                static_cast<int>(RadioSettingsType::ModeFM),
                static_cast<int>(FMSettings::RPPT_SELECT));
            }

            RPTTSelectValue Menu::RadioSetting::FM::RPTT_SELECT::Answer(std::string data)
            {
                return static_cast<RPTTSelectValue>(std::stoi(data.substr(8,1)));
            }

            std::string Menu::RadioSetting::FM::RPT_SHIFT_28::Set(int value)
            {
                return fmt::format("EX{:02}{:02}{:02}{:04};",
                static_cast<int>(MenuGroup::RadioSettings),
                static_cast<int>(RadioSettingsType::ModeFM),
                static_cast<int>(FMSettings::RPT_SHIFT_28),
                static_cast<int>(value));
            }
            std::string Menu::RadioSetting::FM::RPT_SHIFT_28::Read()
            {
                return fmt::format("EX{:02}{:02}{:02};",
                static_cast<int>(MenuGroup::RadioSettings),
                static_cast<int>(RadioSettingsType::ModeFM),
                static_cast<int>(FMSettings::RPT_SHIFT_28));
            }
            int Menu::RadioSetting::FM::RPT_SHIFT_28::Answer(std::string data)
            {
                return std::stoi(data.substr(8,4));
            }

            std::string Menu::RadioSetting::FM::RPT_SHIFT_50::Set(int value)
            {
                return fmt::format("EX{:02}{:02}{:02}{:04};",
                static_cast<int>(MenuGroup::RadioSettings),
                static_cast<int>(RadioSettingsType::ModeFM),
                static_cast<int>(FMSettings::RPT_SHIFT_50),
                static_cast<int>(value));
            }
            std::string Menu::RadioSetting::FM::RPT_SHIFT_50::Read()
            {
                return fmt::format("EX{:02}{:02}{:02};",
                static_cast<int>(MenuGroup::RadioSettings),
                static_cast<int>(RadioSettingsType::ModeFM),
                static_cast<int>(FMSettings::RPT_SHIFT_50));
            }
            int Menu::RadioSetting::FM::RPT_SHIFT_50::Answer(std::string data)
            {
                return std::stoi(data.substr(8,4));
            }

            std::string Menu::RadioSetting::PSK_DATA::AGC_Fast_Delay::Set(int value)
            {
                return fmt::format("EX{:02}{:02}{:02}{:04};",
                static_cast<int>(MenuGroup::RadioSettings),
                static_cast<int>(RadioSettingsType::ModePSK_Data),
                static_cast<int>(PSKDataSettings::AGC_FAST_DELAY),
                static_cast<int>(value));
            }

            std::string Menu::RadioSetting::PSK_DATA::AGC_Fast_Delay::Read()
            {
                return fmt::format("EX{:02}{:02}{:02};",
                static_cast<int>(MenuGroup::RadioSettings),
                static_cast<int>(RadioSettingsType::ModePSK_Data),
                static_cast<int>(PSKDataSettings::AGC_FAST_DELAY));
            }

            int Menu::RadioSetting::PSK_DATA::AGC_Fast_Delay::Answer(std::string data)
            {
                return std::stoi(data.substr(8,4));
            }

            std::string Menu::RadioSetting::PSK_DATA::AGC_Mid_Delay::Set(int value)
            {
                return fmt::format("EX{:02}{:02}{:02}{:04};",
                static_cast<int>(MenuGroup::RadioSettings),
                static_cast<int>(RadioSettingsType::ModePSK_Data),
                static_cast<int>(PSKDataSettings::AGC_MID_DELAY),
                static_cast<int>(value));
            }

            std::string Menu::RadioSetting::PSK_DATA::AGC_Mid_Delay::Read()
            {
                return fmt::format("EX{:02}{:02}{:02};",
                static_cast<int>(MenuGroup::RadioSettings),
                static_cast<int>(RadioSettingsType::ModePSK_Data),
                static_cast<int>(PSKDataSettings::AGC_MID_DELAY));
            }

            int Menu::RadioSetting::PSK_DATA::AGC_Mid_Delay::Answer(std::string data)
            {
                return std::stoi(data.substr(8,4));
            }

            std::string Menu::RadioSetting::PSK_DATA::AGC_Slow_Delay::Set(int value)
            {
                return fmt::format("EX{:02}{:02}{:02}{:04};",
                static_cast<int>(MenuGroup::RadioSettings),
                static_cast<int>(RadioSettingsType::ModePSK_Data),
                static_cast<int>(PSKDataSettings::AGC_SLOW_DELAY),
                static_cast<int>(value));
            }

            std::string Menu::RadioSetting::PSK_DATA::AGC_Slow_Delay::Read()
            {
                return fmt::format("EX{:02}{:02}{:02};",
                static_cast<int>(MenuGroup::RadioSettings),
                static_cast<int>(RadioSettingsType::ModePSK_Data),
                static_cast<int>(PSKDataSettings::AGC_SLOW_DELAY));
            }

            int Menu::RadioSetting::PSK_DATA::AGC_Slow_Delay::Answer(std::string data)
            {
                return std::stoi(data.substr(8,4));
            }

            std::string Menu::RadioSetting::PSK_DATA::DATA_MODE::Set(DataMode value)
            {
                return fmt::format("EX{:02}{:02}{:02}{:01};",
                static_cast<int>(MenuGroup::RadioSettings),
                static_cast<int>(RadioSettingsType::ModePSK_Data),
                static_cast<int>(PSKDataSettings::DATA_MODE),
                static_cast<int>(value));
            }

            std::string Menu::RadioSetting::PSK_DATA::DATA_MODE::Read()
            {
                return fmt::format("EX{:02}{:02}{:02};",
                static_cast<int>(MenuGroup::RadioSettings),
                static_cast<int>(RadioSettingsType::ModePSK_Data),
                static_cast<int>(PSKDataSettings::DATA_MODE));
            }

            DataMode Menu::RadioSetting::PSK_DATA::DATA_MODE::Answer(std::string data)
            {
                return static_cast<DataMode>(std::stoi(data.substr(8,1)));
            }

            std::string Menu::RadioSetting::PSK_DATA::OTHER_SHIFT::Set(int value)
            {
                return fmt::format("EX{:02}{:02}{:02}{:04};",
                static_cast<int>(MenuGroup::RadioSettings),
                static_cast<int>(RadioSettingsType::ModePSK_Data),
                static_cast<int>(PSKDataSettings::OTHER_SHIFT),
                static_cast<int>(value));
            }

            std::string Menu::RadioSetting::PSK_DATA::OTHER_SHIFT::Read()
            {
                return fmt::format("EX{:02}{:02}{:02};",
                static_cast<int>(MenuGroup::RadioSettings),
                static_cast<int>(RadioSettingsType::ModePSK_Data),
                static_cast<int>(PSKDataSettings::OTHER_SHIFT));
            }

            int Menu::RadioSetting::PSK_DATA::OTHER_SHIFT::Answer(std::string data)
            {
                return std::stoi(data.substr(8,4));
            }

            std::string Menu::RadioSetting::PSK_DATA::LCUT_Freq::Set(FreqLowCutValue value)
            {
                return fmt::format("EX{:02}{:02}{:02}{:02};",
                static_cast<int>(MenuGroup::RadioSettings),
                static_cast<int>(RadioSettingsType::ModePSK_Data),
                static_cast<int>(PSKDataSettings::LCUT_FREQ),
                static_cast<int>(value));
            }

            std::string Menu::RadioSetting::PSK_DATA::LCUT_Freq::Read()
            {
                return fmt::format("EX{:02}{:02}{:02};",
                static_cast<int>(MenuGroup::RadioSettings),
                static_cast<int>(RadioSettingsType::ModePSK_Data),
                static_cast<int>(PSKDataSettings::LCUT_FREQ));
            }

            FreqLowCutValue Menu::RadioSetting::PSK_DATA::LCUT_Freq::Answer(std::string data)
            {
                return static_cast<FreqLowCutValue>(std::stoi(data.substr(8,4)));
            }

            std::string Menu::RadioSetting::PSK_DATA::LCUT_Slope::Set(SlopeValue value)
            {
                return fmt::format("EX{:02}{:02}{:02}{:01};",
                static_cast<int>(MenuGroup::RadioSettings),
                static_cast<int>(RadioSettingsType::ModePSK_Data),
                static_cast<int>(PSKDataSettings::LCUT_SLOPE),
                static_cast<int>(value));
            }

            std::string Menu::RadioSetting::PSK_DATA::LCUT_Slope::Read()
            {
                return fmt::format("EX{:02}{:02}{:02};",
                static_cast<int>(MenuGroup::RadioSettings),
                static_cast<int>(RadioSettingsType::ModePSK_Data),
                static_cast<int>(PSKDataSettings::LCUT_SLOPE));
            }

            SlopeValue Menu::RadioSetting::PSK_DATA::LCUT_Slope::Answer(std::string data)
            {
                return static_cast<SlopeValue>(std::stoi(data.substr(8,1)));
            }

            std::string Menu::RadioSetting::PSK_DATA::HCUT_Freq::Set(FreqHighCutValue value)
            {
                return fmt::format("EX{:02}{:02}{:02}{:02};",
                static_cast<int>(MenuGroup::RadioSettings),
                static_cast<int>(RadioSettingsType::ModePSK_Data),
                static_cast<int>(PSKDataSettings::HCUT_FREQ),
                static_cast<int>(value));
            }

            std::string Menu::RadioSetting::PSK_DATA::HCUT_Freq::Read()
            {
                return fmt::format("EX{:02}{:02}{:02};",
                static_cast<int>(MenuGroup::RadioSettings),
                static_cast<int>(RadioSettingsType::ModePSK_Data),
                static_cast<int>(PSKDataSettings::HCUT_FREQ));
            }

            FreqHighCutValue Menu::RadioSetting::PSK_DATA::HCUT_Freq::Answer(std::string data)
            {
                return static_cast<FreqHighCutValue>(std::stoi(data.substr(8,2)));
            }

            std::string Menu::RadioSetting::PSK_DATA::OUT_SELECT::Set(MainSubValue value)
            {
                return fmt::format("EX{:02}{:02}{:02}{:01};",
                static_cast<int>(MenuGroup::RadioSettings),
                static_cast<int>(RadioSettingsType::ModePSK_Data),
                static_cast<int>(PSKDataSettings::OUT_SELECT),
                static_cast<int>(value));
            }

            std::string Menu::RadioSetting::PSK_DATA::OUT_SELECT::Read()
            {
                return fmt::format("EX{:02}{:02}{:02};",
                static_cast<int>(MenuGroup::RadioSettings),
                static_cast<int>(RadioSettingsType::ModePSK_Data),
                static_cast<int>(PSKDataSettings::OUT_SELECT));
            }

            MainSubValue Menu::RadioSetting::PSK_DATA::OUT_SELECT::Answer(std::string data)
            {
                return static_cast<MainSubValue>(std::stoi(data.substr(8,1)));
            }

            std::string Menu::RadioSetting::PSK_DATA::OUT_LEVEL::Set(int value)
            {
                return fmt::format("EX{:02}{:02}{:02}{:03};",
                static_cast<int>(MenuGroup::RadioSettings),
                static_cast<int>(RadioSettingsType::ModePSK_Data),
                static_cast<int>(PSKDataSettings::OUT_LEVEL),
                static_cast<int>(value));
            }

            std::string Menu::RadioSetting::PSK_DATA::OUT_LEVEL::Read()
            {
                return fmt::format("EX{:02}{:02}{:02};",
                static_cast<int>(MenuGroup::RadioSettings),
                static_cast<int>(RadioSettingsType::ModePSK_Data),
                static_cast<int>(PSKDataSettings::OUT_LEVEL));
            }

            int Menu::RadioSetting::PSK_DATA::OUT_LEVEL::Answer(std::string data)
            {
                return std::stoi(data.substr(8,3));
            }

            std::string Menu::RadioSetting::PSK_DATA::TX_BPF_SEL::Set(TXBandPassValue value)
            {
                return fmt::format("EX{:02}{:02}{:02}{:01};",
                static_cast<int>(MenuGroup::RadioSettings),
                static_cast<int>(RadioSettingsType::ModePSK_Data),
                static_cast<int>(PSKDataSettings::TX_BPF_SEL),
                static_cast<int>(value));
            }

            std::string Menu::RadioSetting::PSK_DATA::TX_BPF_SEL::Read()
            {
                return fmt::format("EX{:02}{:02}{:02};",
                static_cast<int>(MenuGroup::RadioSettings),
                static_cast<int>(RadioSettingsType::ModePSK_Data),
                static_cast<int>(PSKDataSettings::TX_BPF_SEL));
            }

            TXBandPassValue Menu::RadioSetting::PSK_DATA::TX_BPF_SEL::Answer(std::string data)
            {
                return static_cast<TXBandPassValue>(std::stoi(data.substr(8,1)));
            }

            std::string Menu::RadioSetting::PSK_DATA::MOD_SOURCE::Set(ModulationSource value)
            {
                return fmt::format("EX{:02}{:02}{:02}{:01};",
                static_cast<int>(MenuGroup::RadioSettings),
                static_cast<int>(RadioSettingsType::ModePSK_Data),
                static_cast<int>(PSKDataSettings::MOD_SOURCE),
                static_cast<int>(value));
            }

            std::string Menu::RadioSetting::PSK_DATA::MOD_SOURCE::Read()
            {
                return fmt::format("EX{:02}{:02}{:02};",
                static_cast<int>(MenuGroup::RadioSettings),
                static_cast<int>(RadioSettingsType::ModePSK_Data),
                static_cast<int>(PSKDataSettings::MOD_SOURCE));
            }

            ModulationSource Menu::RadioSetting::PSK_DATA::MOD_SOURCE::Answer(std::string data)
            {
                return static_cast<ModulationSource>(std::stoi(data.substr(8,1)));
            }

            std::string Menu::RadioSetting::PSK_DATA::REAR_SELECT::Set(RearSelect value)
            {
                return fmt::format("EX{:02}{:02}{:02}{:01};",
                static_cast<int>(MenuGroup::RadioSettings),
                static_cast<int>(RadioSettingsType::ModePSK_Data),
                static_cast<int>(PSKDataSettings::REAR_SELECT),
                static_cast<int>(value));
            }

            std::string Menu::RadioSetting::PSK_DATA::REAR_SELECT::Read()
            {
                return fmt::format("EX{:02}{:02}{:02};",
                static_cast<int>(MenuGroup::RadioSettings),
                static_cast<int>(RadioSettingsType::ModePSK_Data),
                static_cast<int>(PSKDataSettings::REAR_SELECT));
            }

            RearSelect Menu::RadioSetting::PSK_DATA::REAR_SELECT::Answer(std::string data)
            {
                return static_cast<RearSelect>(std::stoi(data.substr(8,1)));
            }

            std::string Menu::RadioSetting::PSK_DATA::RPORT_GAIN::Set(int value)
            {
                return fmt::format("EX{:02}{:02}{:02}{:03};",
                static_cast<int>(MenuGroup::RadioSettings),
                static_cast<int>(RadioSettingsType::ModePSK_Data),
                static_cast<int>(PSKDataSettings::RPORT_GAIN),
                static_cast<int>(value));
            }

            std::string Menu::RadioSetting::PSK_DATA::RPORT_GAIN::Read()
            {
                return fmt::format("EX{:02}{:02}{:02};",
                static_cast<int>(MenuGroup::RadioSettings),
                static_cast<int>(RadioSettingsType::ModePSK_Data),
                static_cast<int>(PSKDataSettings::RPORT_GAIN));
            }

            int Menu::RadioSetting::PSK_DATA::RPORT_GAIN::Answer(std::string data)
            {
                return std::stoi(data.substr(8,3));
            }

            std::string Menu::RadioSetting::PSK_DATA::RPTT_SELECT::Set(RPTTSelectValue value)
            {
                return fmt::format("EX{:02}{:02}{:02}{:01};",
                static_cast<int>(MenuGroup::RadioSettings),
                static_cast<int>(RadioSettingsType::ModePSK_Data),
                static_cast<int>(PSKDataSettings::RPPT_SELECT),
                static_cast<int>(value));
            }


            std::string Menu::RadioSetting::PSK_DATA::RPTT_SELECT::Read()
            {
                return fmt::format("EX{:02}{:02}{:02};",
                static_cast<int>(MenuGroup::RadioSettings),
                static_cast<int>(RadioSettingsType::ModePSK_Data),
                static_cast<int>(PSKDataSettings::RPPT_SELECT));
            }

            RPTTSelectValue Menu::RadioSetting::PSK_DATA::RPTT_SELECT::Answer(std::string data)
            {
                return static_cast<RPTTSelectValue>(std::stoi(data.substr(8,1)));
            }

            std::string Menu::RadioSetting::RTTY::AGC_Fast_Delay::Set( int value)
            {
                return fmt::format("EX{:02}{:02}{:02}{:04};",
                static_cast<int>(MenuGroup::RadioSettings),
                static_cast<int>(RadioSettingsType::ModeRTTY),
                static_cast<int>(RTTYSettings::AGC_FAST_DELAY),
                static_cast<int>(value));
            }
            std::string Menu::RadioSetting::RTTY::AGC_Fast_Delay::Read()
            {
                return fmt::format("EX{:02d}{:02d}{:02d};",
                static_cast<int>(MenuGroup::RadioSettings),
                static_cast<int>(RadioSettingsType::ModeRTTY),
                static_cast<int>(RTTYSettings::AGC_FAST_DELAY));
            }
            int Menu::RadioSetting::RTTY::AGC_Fast_Delay::Answer(std::string data)
            {
                return std::stoi(data.substr(8,4));
            }

            std::string Menu::RadioSetting::RTTY::AGC_Mid_Delay::Set( int value)
            {
                return fmt::format("EX{:02}{:02}{:02}{:04};",
                static_cast<int>(MenuGroup::RadioSettings),
                static_cast<int>(RadioSettingsType::ModeRTTY),
                static_cast<int>(RTTYSettings::AGC_MID_DELAY),
                static_cast<int>(value));
            }

            std::string Menu::RadioSetting::RTTY::AGC_Mid_Delay::Read()
            {
                return fmt::format("EX{:02d}{:02d}{:02d};",
                static_cast<int>(MenuGroup::RadioSettings),
                static_cast<int>(RadioSettingsType::ModeRTTY),
                static_cast<int>(RTTYSettings::AGC_MID_DELAY));
            }

            int Menu::RadioSetting::RTTY::AGC_Mid_Delay::Answer(std::string data)
            {
                return std::stoi(data.substr(8,4));
            }

            std::string Menu::RadioSetting::RTTY::AGC_Slow_Delay::Set( int value)
            {
                return fmt::format("EX{:02}{:02}{:02}{:04};",
                static_cast<int>(MenuGroup::RadioSettings),
                static_cast<int>(RadioSettingsType::ModeRTTY),
                static_cast<int>(RTTYSettings::AGC_FAST_DELAY),
                static_cast<int>(value));
            }

            std::string Menu::RadioSetting::RTTY::AGC_Slow_Delay::Read()
            {
                return fmt::format("EX{:02d}{:02d}{:02d};",
                static_cast<int>(MenuGroup::RadioSettings),
                static_cast<int>(RadioSettingsType::ModeRTTY),
                static_cast<int>(RTTYSettings::AGC_FAST_DELAY));
            }

            int Menu::RadioSetting::RTTY::AGC_Slow_Delay::Answer(std::string data)
            {
                return std::stoi(data.substr(8,4));
            }

            std::string Menu::RadioSetting::RTTY::POLARITY_RX::Set(RTTYPolarityValue value)
            {
                return fmt::format("EX{:02}{:02}{:02}{:01};",
                static_cast<int>(MenuGroup::RadioSettings),
                static_cast<int>(RadioSettingsType::ModeRTTY),
                static_cast<int>(RTTYSettings::POLARITY_RX),
                static_cast<int>(value));
            }

            std::string Menu::RadioSetting::RTTY::POLARITY_RX::Read()
            {
                return fmt::format("EX{:02d}{:02d}{:02d};",
                static_cast<int>(MenuGroup::RadioSettings),
                static_cast<int>(RadioSettingsType::ModeRTTY),
                static_cast<int>(RTTYSettings::POLARITY_RX));
            }

            RTTYPolarityValue Menu::RadioSetting::RTTY::POLARITY_RX::Answer(std::string data)
            {
                return static_cast<RTTYPolarityValue>(std::stoi(data.substr(8,1)));
            }

            std::string Menu::RadioSetting::RTTY::POLARITY_TX::Set(RTTYPolarityValue value)
            {
                return fmt::format("EX{:02}{:02}{:02}{:01};",
                static_cast<int>(MenuGroup::RadioSettings),
                static_cast<int>(RadioSettingsType::ModeRTTY),
                static_cast<int>(RTTYSettings::POLARITY_TX),
                static_cast<int>(value));
            }

            std::string Menu::RadioSetting::RTTY::POLARITY_TX::Read()
            {
                return fmt::format("EX{:02d}{:02d}{:02d};",
                static_cast<int>(MenuGroup::RadioSettings),
                static_cast<int>(RadioSettingsType::ModeRTTY),
                static_cast<int>(RTTYSettings::POLARITY_TX));
            }

            RTTYPolarityValue Menu::RadioSetting::RTTY::POLARITY_TX::Answer(std::string data)
            {
                return static_cast<RTTYPolarityValue>(std::stoi(data.substr(8,1)));
            }

            std::string Menu::RadioSetting::RTTY::LCUT_Freq::Set(FreqLowCutValue value)
            {
                return fmt::format("EX{:02d}{:02d}{:02d}{:02d};",
                static_cast<int>(MenuGroup::RadioSettings),
                static_cast<int>(RadioSettingsType::ModeRTTY),
                static_cast<int>(RTTYSettings::LCUT_FREQ),
                static_cast<int>(value));
            }

            std::string Menu::RadioSetting::RTTY::LCUT_Freq::Read()
            {
                return fmt::format("EX{:02d}{:02d}{:02d};",
                static_cast<int>(MenuGroup::RadioSettings),
                static_cast<int>(RadioSettingsType::ModeRTTY),
                static_cast<int>(RTTYSettings::LCUT_FREQ));
            }

            FreqLowCutValue Menu::RadioSetting::RTTY::LCUT_Freq::Answer(std::string data)
            {
                return static_cast<FreqLowCutValue>(std::stoi(data.substr(8,2)));
            }

            std::string Menu::RadioSetting::RTTY::LCUT_Slope::Set(SlopeValue value)
            {
                return fmt::format("EX{:02d}{:02d}{:02d}{:01d};",
                static_cast<int>(MenuGroup::RadioSettings),
                static_cast<int>(RadioSettingsType::ModeRTTY),
                static_cast<int>(RTTYSettings::LCUT_SLOPE),
                static_cast<int>(value));
            }

            std::string Menu::RadioSetting::RTTY::LCUT_Slope::Read()
            {
                return fmt::format("EX{:02d}{:02d}{:02d};",
                static_cast<int>(MenuGroup::RadioSettings),
                static_cast<int>(RadioSettingsType::ModeRTTY),
                static_cast<int>(RTTYSettings::LCUT_SLOPE));
            }

            SlopeValue Menu::RadioSetting::RTTY::LCUT_Slope::Answer(std::string data)
            {
                return static_cast<SlopeValue>(std::stoi(data.substr(8,1)));
            }

            std::string Menu::RadioSetting::RTTY::HCUT_Freq::Set(FreqHighCutValue value)
            {
                return fmt::format("EX{:02d}{:02d}{:02d}{:02d};",
                static_cast<int>(MenuGroup::RadioSettings),
                static_cast<int>(RadioSettingsType::ModeRTTY),
                static_cast<int>(RTTYSettings::HCUT_FREQ),
                static_cast<int>(value));
            }

            std::string Menu::RadioSetting::RTTY::HCUT_Freq::Read()
            {
                return fmt::format("EX{:02d}{:02d}{:02d};",
                static_cast<int>(MenuGroup::RadioSettings),
                static_cast<int>(RadioSettingsType::ModeRTTY),
                static_cast<int>(RTTYSettings::HCUT_FREQ));
            }

            FreqHighCutValue Menu::RadioSetting::RTTY::HCUT_Freq::Answer(std::string data)
            {
                return static_cast<FreqHighCutValue>(std::stoi(data.substr(8,2)));
            }

            std::string Menu::RadioSetting::RTTY::HCUT_Slope::Set(SlopeValue value)
            {
                return fmt::format("EX{:02d}{:02d}{:02d}{:01d};",
                static_cast<int>(MenuGroup::RadioSettings),
                static_cast<int>(RadioSettingsType::ModeRTTY),
                static_cast<int>(RTTYSettings::HCUT_SLOPE),
                static_cast<int>(value));
            }

            std::string Menu::RadioSetting::RTTY::HCUT_Slope::Read()
            {
                return fmt::format("EX{:02d}{:02d}{:02d};",
                static_cast<int>(MenuGroup::RadioSettings),
                static_cast<int>(RadioSettingsType::ModeRTTY),
                static_cast<int>(RTTYSettings::HCUT_SLOPE));
            }

            SlopeValue Menu::RadioSetting::RTTY::HCUT_Slope::Answer(std::string data)
            {
                return static_cast<SlopeValue>(std::stoi(data.substr(8,1)));
            }

            std::string Menu::RadioSetting::RTTY::OUT_SELECT::Set(MainSubValue value)
            {
                return fmt::format("EX{:02d}{:02d}{:02d}{:01d};",
                static_cast<int>(MenuGroup::RadioSettings),
                static_cast<int>(RadioSettingsType::ModeRTTY),
                static_cast<int>(RTTYSettings::OUT_SELECT),
                static_cast<int>(value));
            }

            std::string Menu::RadioSetting::RTTY::OUT_SELECT::Read()
            {
                return fmt::format("EX{:02d}{:02d}{:02d};",
                static_cast<int>(MenuGroup::RadioSettings),
                static_cast<int>(RadioSettingsType::ModeRTTY),
                static_cast<int>(RTTYSettings::OUT_SELECT));
            }

            MainSubValue Menu::RadioSetting::RTTY::OUT_SELECT::Answer(std::string data)
            {
                return static_cast<MainSubValue>(std::stoi(data.substr(8,1)));
            }

            std::string Menu::RadioSetting::RTTY::SHIFT_PORT::Set(RTTYShiftPortValue value)
            {
                return fmt::format("EX{:02d}{:02d}{:02d}{:01d};",
                static_cast<int>(MenuGroup::RadioSettings),
                static_cast<int>(RadioSettingsType::ModeRTTY),
                static_cast<int>(RTTYSettings::SHIFT_PORT),
                static_cast<int>(value));
            }

            std::string Menu::RadioSetting::RTTY::SHIFT_PORT::Read()
            {
                return fmt::format("EX{:02d}{:02d}{:02d};",
                static_cast<int>(MenuGroup::RadioSettings),
                static_cast<int>(RadioSettingsType::ModeRTTY),
                static_cast<int>(RTTYSettings::SHIFT_PORT));

            }

            RTTYShiftPortValue Menu::RadioSetting::RTTY::SHIFT_PORT::Answer(std::string data)
            {
                return static_cast<RTTYShiftPortValue>(std::stoi(data.substr(8,1)));
            }

            std::string Menu::RadioSetting::RTTY::SHIFT_FREQ::Set(RTTYShiftFreqValue value)
            {
                return fmt::format("EX{:02d}{:02d}{:02d}{:01d};",
                static_cast<int>(MenuGroup::RadioSettings),
                static_cast<int>(RadioSettingsType::ModeRTTY),
                static_cast<int>(RTTYSettings::SHIFT_FREQUENCY),
                static_cast<int>(value));
            }

            std::string Menu::RadioSetting::RTTY::SHIFT_FREQ::Read()
            {
                return fmt::format("EX{:02d}{:02d}{:02d};",
                static_cast<int>(MenuGroup::RadioSettings),
                static_cast<int>(RadioSettingsType::ModeRTTY),
                static_cast<int>(RTTYSettings::SHIFT_FREQUENCY));
            }

            RTTYShiftFreqValue Menu::RadioSetting::RTTY::SHIFT_FREQ::Answer(std::string data)
            {
                return static_cast<RTTYShiftFreqValue>(std::stoi(data.substr(8,1)));
            }

            std::string Menu::RadioSetting::ENC_DEC_PSK::PSK_MODE::Set(PSKModeValue value)
            {
                return fmt::format("EX{:02d}{:02d}{:02d}{:01d};",
                static_cast<int>(MenuGroup::RadioSettings),
                static_cast<int>(RadioSettingsType::ENC_DEC_PSK),
                static_cast<int>(EncDecPskSettings::PSK_MODE),
                static_cast<int>(value));
            }

            std::string Menu::RadioSetting::ENC_DEC_PSK::PSK_MODE::Read()
            {
                return fmt::format("EX{:02d}{:02d}{:02d};",
                static_cast<int>(MenuGroup::RadioSettings),
                static_cast<int>(RadioSettingsType::ENC_DEC_PSK),
                static_cast<int>(EncDecPskSettings::PSK_MODE));
            }

            PSKModeValue Menu::RadioSetting::ENC_DEC_PSK::PSK_MODE::Answer(std::string data)
            {
                return static_cast<PSKModeValue>(std::stoi(data.substr(8,1)));
            }

            std::string Menu::RadioSetting::ENC_DEC_PSK::DECODE_AFC_RANGE::Set(DecodeAfcRangeValue value)
            {
                return fmt::format("EX{:02d}{:02d}{:02d}{:01d};",
                static_cast<int>(MenuGroup::RadioSettings),
                static_cast<int>(RadioSettingsType::ENC_DEC_PSK),
                static_cast<int>(EncDecPskSettings::DECODE_AFC_RANGE),
                static_cast<int>(value));
            }

            std::string Menu::RadioSetting::ENC_DEC_PSK::DECODE_AFC_RANGE::Read()
            {
                return fmt::format("EX{:02d}{:02d}{:02d};",
                static_cast<int>(MenuGroup::RadioSettings),
                static_cast<int>(RadioSettingsType::ENC_DEC_PSK),
                static_cast<int>(EncDecPskSettings::DECODE_AFC_RANGE));
            }

            DecodeAfcRangeValue Menu::RadioSetting::ENC_DEC_PSK::DECODE_AFC_RANGE::Answer(std::string data)
            {
                return static_cast<DecodeAfcRangeValue>(std::stoi(data.substr(8,1)));
            }

            std::string Menu::RadioSetting::ENC_DEC_PSK::POLARITY_RX::Set(RTTYPolarityValue value)
            {
                return fmt::format("EX{:02d}{:02d}{:02d}{:01d};",
                static_cast<int>(MenuGroup::RadioSettings),
                static_cast<int>(RadioSettingsType::ENC_DEC_PSK),
                static_cast<int>(EncDecPskSettings::POLARITY_RX),
                static_cast<int>(value));
            }

            std::string Menu::RadioSetting::ENC_DEC_PSK::POLARITY_RX::Read()
            {
                return fmt::format("EX{:02d}{:02d}{:02d};",
                static_cast<int>(MenuGroup::RadioSettings),
                static_cast<int>(RadioSettingsType::ENC_DEC_PSK),
                static_cast<int>(EncDecPskSettings::POLARITY_RX));

            }

            RTTYPolarityValue Menu::RadioSetting::ENC_DEC_PSK::POLARITY_RX::Answer(std::string data)
            {
                return static_cast<RTTYPolarityValue>(std::stoi(data.substr(8,1)));
            }

            std::string Menu::RadioSetting::ENC_DEC_PSK::POLARITY_TX::Set(RTTYPolarityValue value)
            {
                return fmt::format("EX{:02d}{:02d}{:02d}{:01d};",
                static_cast<int>(MenuGroup::RadioSettings),
                static_cast<int>(RadioSettingsType::ENC_DEC_PSK),
                static_cast<int>(EncDecPskSettings::POLARITY_TX),
                static_cast<int>(value));
            }

            std::string Menu::RadioSetting::ENC_DEC_PSK::POLARITY_TX::Read()
            {
                return fmt::format("EX{:02d}{:02d}{:02d};",
                static_cast<int>(MenuGroup::RadioSettings),
                static_cast<int>(RadioSettingsType::ENC_DEC_PSK),
                static_cast<int>(EncDecPskSettings::POLARITY_TX));

            }

            RTTYPolarityValue Menu::RadioSetting::ENC_DEC_PSK::POLARITY_TX::Answer(std::string data)
            {
                return static_cast<RTTYPolarityValue>(std::stoi(data.substr(8,1)));
            }

            std::string Menu::RadioSetting::ENC_DEC_PSK::TX_LEVEL::Set(int value)
            {
                return fmt::format("EX{:02d}{:02d}{:02d}{:03d};",
                static_cast<int>(MenuGroup::RadioSettings),
                static_cast<int>(RadioSettingsType::ENC_DEC_PSK),
                static_cast<int>(EncDecPskSettings::TX_LEVEL),
                static_cast<int>(value));
            }

            std::string Menu::RadioSetting::ENC_DEC_PSK::TX_LEVEL::Read()
            {
                return fmt::format("EX{:02d}{:02d}{:02d};",
                static_cast<int>(MenuGroup::RadioSettings),
                static_cast<int>(RadioSettingsType::ENC_DEC_PSK),
                static_cast<int>(EncDecPskSettings::TX_LEVEL));
            }

            int Menu::RadioSetting::ENC_DEC_PSK::TX_LEVEL::Answer(std::string data)
            {
                return std::stoi(data.substr(8,3));
            }

            std::string Menu::RadioSetting::ENC_DEC_RTTY::RX_USOS::Set(EnableDisableValue value)
            {
                return fmt::format("EX{:02d}{:02d}{:02d}{:01d};",
                static_cast<int>(MenuGroup::RadioSettings),
                static_cast<int>(RadioSettingsType::ENC_DEC_RTTY),
                static_cast<int>(EncDecRTTYSettings::RX_USOS),
                static_cast<int>(value));
            }

            std::string Menu::RadioSetting::ENC_DEC_RTTY::RX_USOS::Read()
            {
                return fmt::format("EX{:02d}{:02d}{:02d};",
                static_cast<int>(MenuGroup::RadioSettings),
                static_cast<int>(RadioSettingsType::ENC_DEC_RTTY),
                static_cast<int>(EncDecRTTYSettings::RX_USOS));
            }

            EnableDisableValue Menu::RadioSetting::ENC_DEC_RTTY::RX_USOS::Answer(std::string data)
            {
                return static_cast<EnableDisableValue>(std::stoi(data.substr(8,1)));
            }

            std::string Menu::RadioSetting::ENC_DEC_RTTY::TX_USOS::Set(EnableDisableValue value)
            {
                return fmt::format("EX{:02d}{:02d}{:02d}{:01d};",
                static_cast<int>(MenuGroup::RadioSettings),
                static_cast<int>(RadioSettingsType::ENC_DEC_RTTY),
                static_cast<int>(EncDecRTTYSettings::TX_USOS),
                static_cast<int>(value));
            }

            std::string Menu::RadioSetting::ENC_DEC_RTTY::TX_USOS::Read()
            {
                return fmt::format("EX{:02d}{:02d}{:02d};",
                static_cast<int>(MenuGroup::RadioSettings),
                static_cast<int>(RadioSettingsType::ENC_DEC_RTTY),
                static_cast<int>(EncDecRTTYSettings::TX_USOS));
            }

            EnableDisableValue Menu::RadioSetting::ENC_DEC_RTTY::TX_USOS::Answer(std::string data)
            {
                return static_cast<EnableDisableValue>(std::stoi(data.substr(8,1)));
            }

            std::string Menu::RadioSetting::ENC_DEC_RTTY::RX_NEW_LINE_CODE::Set(NewLineCode value)
            {
                return fmt::format("EX{:02d}{:02d}{:02d}{:01d};",
                static_cast<int>(MenuGroup::RadioSettings),
                static_cast<int>(RadioSettingsType::ENC_DEC_RTTY),
                static_cast<int>(EncDecRTTYSettings::RX_NEW_LINE),
                static_cast<int>(value));
            }

            std::string Menu::RadioSetting::ENC_DEC_RTTY::RX_NEW_LINE_CODE::Read()
            {
                return fmt::format("EX{:02d}{:02d}{:02d};",
                static_cast<int>(MenuGroup::RadioSettings),
                static_cast<int>(RadioSettingsType::ENC_DEC_RTTY),
                static_cast<int>(EncDecRTTYSettings::RX_NEW_LINE));
            }


            NewLineCode Menu::RadioSetting::ENC_DEC_RTTY::RX_NEW_LINE_CODE::Answer(std::string data)
            {
                return static_cast<NewLineCode>(std::stoi(data.substr(8,1)));
            }

            std::string Menu::RadioSetting::ENC_DEC_RTTY::TX_AUTO_CRLF::Set(EnableDisableValue value)
            {
                return fmt::format("EX{:02d}{:02d}{:02d}{:01d};",
                static_cast<int>(MenuGroup::RadioSettings),
                static_cast<int>(RadioSettingsType::ENC_DEC_RTTY),
                static_cast<int>(EncDecRTTYSettings::TX_AUTO_CR_LF),
                static_cast<int>(value));
            }

            std::string Menu::RadioSetting::ENC_DEC_RTTY::TX_AUTO_CRLF::Read()
            {
                return fmt::format("EX{:02d}{:02d}{:02d};",
                static_cast<int>(MenuGroup::RadioSettings),
                static_cast<int>(RadioSettingsType::ENC_DEC_RTTY),
                static_cast<int>(EncDecRTTYSettings::TX_AUTO_CR_LF));
            }

            EnableDisableValue Menu::RadioSetting::ENC_DEC_RTTY::TX_AUTO_CRLF::Answer(std::string data)
            {
                return static_cast<EnableDisableValue>(std::stoi(data.substr(8,1)));
            }

            std::string Menu::RadioSetting::ENC_DEC_RTTY::TX_DIDDLE::Set(TXDiddleValue value)
            {
                return fmt::format("EX{:02d}{:02d}{:02d}{:01d};",
                static_cast<int>(MenuGroup::RadioSettings),
                static_cast<int>(RadioSettingsType::ENC_DEC_RTTY),
                static_cast<int>(EncDecRTTYSettings::TX_DIDDLE),
                static_cast<int>(value));
            }

            std::string Menu::RadioSetting::ENC_DEC_RTTY::TX_DIDDLE::Read()
            {
                return fmt::format("EX{:02d}{:02d}{:02d};",
                static_cast<int>(MenuGroup::RadioSettings),
                static_cast<int>(RadioSettingsType::ENC_DEC_RTTY),
                static_cast<int>(EncDecRTTYSettings::TX_DIDDLE));
            }

            TXDiddleValue Menu::RadioSetting::ENC_DEC_RTTY::TX_DIDDLE::Answer(std::string data)
            {
                return static_cast<TXDiddleValue>(std::stoi(data.substr(8,1)));
            }

            std::string Menu::RadioSetting::ENC_DEC_RTTY::BAUDOT_CODE::Set(BaudotCodeStandard value)
            {
                return fmt::format("EX{:02d}{:02d}{:02d}{:01d};",
                static_cast<int>(MenuGroup::RadioSettings),
                static_cast<int>(RadioSettingsType::ENC_DEC_RTTY),
                static_cast<int>(EncDecRTTYSettings::BAUDOT_COODE),
                static_cast<int>(value));
            }

            std::string Menu::RadioSetting::ENC_DEC_RTTY::BAUDOT_CODE::Read()
            {
                return fmt::format("EX{:02d}{:02d}{:02d};",
                static_cast<int>(MenuGroup::RadioSettings),
                static_cast<int>(RadioSettingsType::ENC_DEC_RTTY),
                static_cast<int>(EncDecRTTYSettings::BAUDOT_COODE));
            }

            BaudotCodeStandard Menu::RadioSetting::ENC_DEC_RTTY::BAUDOT_CODE::Answer(std::string data)
            {
                return static_cast<BaudotCodeStandard>(std::stoi(data.substr(8,1)));
            }

            std::string Menu::CWSetting::ModeCW::AGC_Fast_Delay::Set(int value)
            {
                return fmt::format("EX{:02d}{:02d}{:02d}{:04d};",
                static_cast<int>(MenuGroup::CWSettings),
                static_cast<int>(CWSettingsType::ModeCW),
                static_cast<int>(ModeCWSettings::AGC_FAST_DELAY),
                static_cast<int>(value));
            }

            std::string Menu::CWSetting::ModeCW::AGC_Fast_Delay::Read()
            {
                return fmt::format("EX{:02d}{:02d}{:02d};",
                static_cast<int>(MenuGroup::CWSettings),
                static_cast<int>(CWSettingsType::ModeCW),
                static_cast<int>(ModeCWSettings::AGC_FAST_DELAY));
            }

            int Menu::CWSetting::ModeCW::AGC_Fast_Delay::Answer(std::string data)
            {
                return std::stoi(data.substr(8,4));
            }

            std::string Menu::CWSetting::ModeCW::AGC_Mid_Delay::Set(int value)
            {
                return fmt::format("EX{:02d}{:02d}{:02d}{:04d};",
                static_cast<int>(MenuGroup::CWSettings),
                static_cast<int>(CWSettingsType::ModeCW),
                static_cast<int>(ModeCWSettings::AGC_MID_DELAY),
                static_cast<int>(value));
            }

            std::string Menu::CWSetting::ModeCW::AGC_Mid_Delay::Read()
            {
                return fmt::format("EX{:02d}{:02d}{:02d};",
                static_cast<int>(MenuGroup::CWSettings),
                static_cast<int>(CWSettingsType::ModeCW),
                static_cast<int>(ModeCWSettings::AGC_MID_DELAY));
            }

            int Menu::CWSetting::ModeCW::AGC_Mid_Delay::Answer(std::string data)
            {
                return std::stoi(data.substr(8,4));
            }

            std::string Menu::CWSetting::ModeCW::AGC_Slow_Delay::Set(int value)
            {
                return fmt::format("EX{:02d}{:02d}{:02d}{:04d};",
                static_cast<int>(MenuGroup::CWSettings),
                static_cast<int>(CWSettingsType::ModeCW),
                static_cast<int>(ModeCWSettings::AGC_SLOW_DELAY),
                static_cast<int>(value));
            }

            std::string Menu::CWSetting::ModeCW::AGC_Slow_Delay::Read()
            {
                return fmt::format("EX{:02d}{:02d}{:02d};",
                static_cast<int>(MenuGroup::CWSettings),
                static_cast<int>(CWSettingsType::ModeCW),
                static_cast<int>(ModeCWSettings::AGC_SLOW_DELAY));
            }

            int Menu::CWSetting::ModeCW::AGC_Slow_Delay::Answer(std::string data)
            {
                return std::stoi(data.substr(8,4));
            }

            std::string Menu::CWSetting::ModeCW::LCUT_Freq::Set(FreqLowCutValue value)
            {
                return fmt::format("EX{:02d}{:02d}{:02d}{:02d};",
                static_cast<int>(MenuGroup::CWSettings),
                static_cast<int>(CWSettingsType::ModeCW),
                static_cast<int>(ModeCWSettings::LCUT_FREQ),
                static_cast<int>(value));
            }

            std::string Menu::CWSetting::ModeCW::LCUT_Freq::Read()
            {
                return fmt::format("EX{:02d}{:02d}{:02d};",
                static_cast<int>(MenuGroup::CWSettings),
                static_cast<int>(CWSettingsType::ModeCW),
                static_cast<int>(ModeCWSettings::LCUT_FREQ));
            }

            FreqLowCutValue Menu::CWSetting::ModeCW::LCUT_Freq::Answer(std::string data)
            {
                return static_cast<FreqLowCutValue>(std::stoi(data.substr(8,2)));
            }

            std::string Menu::CWSetting::ModeCW::LCUT_Slope::Set(SlopeValue value)
            {
                return fmt::format("EX{:02d}{:02d}{:02d}{:01d};",
                static_cast<int>(MenuGroup::CWSettings),
                static_cast<int>(CWSettingsType::ModeCW),
                static_cast<int>(ModeCWSettings::LCUT_SLOPE),
                static_cast<int>(value));
            }

            std::string Menu::CWSetting::ModeCW::LCUT_Slope::Read()
            {
                return fmt::format("EX{:02d}{:02d}{:02d};",
                static_cast<int>(MenuGroup::CWSettings),
                static_cast<int>(CWSettingsType::ModeCW),
                static_cast<int>(ModeCWSettings::LCUT_SLOPE));
            }

            SlopeValue Menu::CWSetting::ModeCW::LCUT_Slope::Answer(std::string data)
            {
                return static_cast<SlopeValue>(std::stoi(data.substr(8,1)));
            }

            std::string Menu::CWSetting::ModeCW::HCUT_Freq::Set(FreqHighCutValue value)
            {
                return fmt::format("EX{:02d}{:02d}{:02d}{:02d};",
                static_cast<int>(MenuGroup::CWSettings),
                static_cast<int>(CWSettingsType::ModeCW),
                static_cast<int>(ModeCWSettings::HCUT_FREQ),
                static_cast<int>(value));
            }

            std::string Menu::CWSetting::ModeCW::HCUT_Freq::Read()
            {
                return fmt::format("EX{:02d}{:02d}{:02d};",
                static_cast<int>(MenuGroup::CWSettings),
                static_cast<int>(CWSettingsType::ModeCW),
                static_cast<int>(ModeCWSettings::HCUT_FREQ));
            }

            FreqHighCutValue Menu::CWSetting::ModeCW::HCUT_Freq::Answer(std::string data)
            {
                return static_cast<FreqHighCutValue>(std::stoi(data.substr(8,2)));
            }

            std::string Menu::CWSetting::ModeCW::HCUT_Slope::Set(SlopeValue value)
            {
                return fmt::format("EX{:02d}{:02d}{:02d}{:01d};",
                static_cast<int>(MenuGroup::CWSettings),
                static_cast<int>(CWSettingsType::ModeCW),
                static_cast<int>(ModeCWSettings::HCUT_SLOPE),
                static_cast<int>(value));
            }

            std::string Menu::CWSetting::ModeCW::HCUT_Slope::Read()
            {
                return fmt::format("EX{:02d}{:02d}{:02d};",
                static_cast<int>(MenuGroup::CWSettings),
                static_cast<int>(CWSettingsType::ModeCW),
                static_cast<int>(ModeCWSettings::LCUT_SLOPE));
            }

            SlopeValue Menu::CWSetting::ModeCW::HCUT_Slope::Answer(std::string data)
            {
                return static_cast<SlopeValue>(std::stoi(data.substr(8,1)));
            }

            std::string Menu::CWSetting::ModeCW::OUT_SELECT::Set(MainSubValue value)
            {
                return fmt::format("EX{:02d}{:02d}{:02d}{:01d};",
                static_cast<int>(MenuGroup::CWSettings),
                static_cast<int>(CWSettingsType::ModeCW),
                static_cast<int>(ModeCWSettings::OUT_SELECT),
                static_cast<int>(value));
            }

            std::string Menu::CWSetting::ModeCW::OUT_SELECT::Read()
            {
                return fmt::format("EX{:02d}{:02d}{:02d};",
                static_cast<int>(MenuGroup::CWSettings),
                static_cast<int>(CWSettingsType::ModeCW),
                static_cast<int>(ModeCWSettings::OUT_SELECT));
            }

            MainSubValue Menu::CWSetting::ModeCW::OUT_SELECT::Answer(std::string data)
            {
                return static_cast<MainSubValue>(std::stoi(data.substr(8,1)));
            }

            std::string Menu::CWSetting::ModeCW::OUT_LEVEL::Set(int value)
            {
                return fmt::format("EX{:02d}{:02d}{:02d}{:03d};",
                static_cast<int>(MenuGroup::CWSettings),
                static_cast<int>(CWSettingsType::ModeCW),
                static_cast<int>(ModeCWSettings::OUT_LEVEL),
                static_cast<int>(value));
            }

            std::string Menu::CWSetting::ModeCW::OUT_LEVEL::Read()
            {
                return fmt::format("EX{:02d}{:02d}{:02d};",
                static_cast<int>(MenuGroup::CWSettings),
                static_cast<int>(CWSettingsType::ModeCW),
                static_cast<int>(ModeCWSettings::OUT_LEVEL));
            }

            int Menu::CWSetting::ModeCW::OUT_LEVEL::Answer(std::string data)
            {
                return std::stoi(data.substr(8,3));
            }

            std::string Menu::CWSetting::ModeCW::AUTO_MODE::Set(AutoModeValue value)
            {
                return fmt::format("EX{:02d}{:02d}{:02d}{:01d};",
                static_cast<int>(MenuGroup::CWSettings),
                static_cast<int>(CWSettingsType::ModeCW),
                static_cast<int>(ModeCWSettings::AUTO_MODE),
                static_cast<int>(value));
            }

            std::string Menu::CWSetting::ModeCW::AUTO_MODE::Read()
            {
                return fmt::format("EX{:02d}{:02d}{:02d};",
                static_cast<int>(MenuGroup::CWSettings),
                static_cast<int>(CWSettingsType::ModeCW),
                static_cast<int>(ModeCWSettings::AUTO_MODE));
            }

            AutoModeValue Menu::CWSetting::ModeCW::AUTO_MODE::Answer(std::string data)
            {
                return static_cast<AutoModeValue>(std::stoi(data.substr(8,1)));
            }

            std::string Menu::CWSetting::ModeCW::BKIN_TYPE::Set(BreakInType value)
            {
                return fmt::format("EX{:02d}{:02d}{:02d}{:01d};",
                static_cast<int>(MenuGroup::CWSettings),
                static_cast<int>(CWSettingsType::ModeCW),
                static_cast<int>(ModeCWSettings::BKIN_TYPE),
                static_cast<int>(value));
            }

            std::string Menu::CWSetting::ModeCW::BKIN_TYPE::Read()
            {
                return fmt::format("EX{:02d}{:02d}{:02d};",
                static_cast<int>(MenuGroup::CWSettings),
                static_cast<int>(CWSettingsType::ModeCW),
                static_cast<int>(ModeCWSettings::BKIN_TYPE));
            }

            BreakInType Menu::CWSetting::ModeCW::BKIN_TYPE::Answer(std::string data)
            {
                return static_cast<BreakInType>(std::stoi(data.substr(8,1)));
            }

            std::string Menu::CWSetting::ModeCW::BKIN_DELAY::Set(int value)
            {
                return fmt::format("EX{:02d}{:02d}{:02d}{:04d};",
                static_cast<int>(MenuGroup::CWSettings),
                static_cast<int>(CWSettingsType::ModeCW),
                static_cast<int>(ModeCWSettings::BKIN_DELAY),
                static_cast<int>(value));
            }

            std::string Menu::CWSetting::ModeCW::BKIN_DELAY::Read()
            {
                return fmt::format("EX{:02d}{:02d}{:02d};",
                static_cast<int>(MenuGroup::CWSettings),
                static_cast<int>(CWSettingsType::ModeCW),
                static_cast<int>(ModeCWSettings::BKIN_DELAY));
            }

            int Menu::CWSetting::ModeCW::BKIN_DELAY::Answer(std::string data)
            {
                return std::stoi(data.substr(8,4));
            }

            std::string Menu::CWSetting::ModeCW::WAVE_SHAPE::Set(WaveShapeValue value)
            {
                return fmt::format("EX{:02d}{:02d}{:02d}{:01d};",
                static_cast<int>(MenuGroup::CWSettings),
                static_cast<int>(CWSettingsType::ModeCW),
                static_cast<int>(ModeCWSettings::WAVE_SHAPE),
                static_cast<int>(value));
            }

            std::string Menu::CWSetting::ModeCW::WAVE_SHAPE::Read()
            {
                return fmt::format("EX{:02d}{:02d}{:02d};",
                static_cast<int>(MenuGroup::CWSettings),
                static_cast<int>(CWSettingsType::ModeCW),
                static_cast<int>(ModeCWSettings::WAVE_SHAPE));
            }

            WaveShapeValue Menu::CWSetting::ModeCW::WAVE_SHAPE::Answer(std::string data)
            {
                return static_cast<WaveShapeValue>(std::stoi(data.substr(8,1)));
            }

            std::string Menu::CWSetting::ModeCW::FREQ_DISPLAY::Set(FreqDisplayValue value)
            {
                return fmt::format("EX{:02d}{:02d}{:02d}{:01d};",
                static_cast<int>(MenuGroup::CWSettings),
                static_cast<int>(CWSettingsType::ModeCW),
                static_cast<int>(ModeCWSettings::FREQ_DISPLAY),
                static_cast<int>(value));
            }

            std::string Menu::CWSetting::ModeCW::FREQ_DISPLAY::Read()
            {
                return fmt::format("EX{:02d}{:02d}{:02d};",
                static_cast<int>(MenuGroup::CWSettings),
                static_cast<int>(CWSettingsType::ModeCW),
                static_cast<int>(ModeCWSettings::FREQ_DISPLAY));
            }

            FreqDisplayValue Menu::CWSetting::ModeCW::FREQ_DISPLAY::Answer(std::string data)
            {
                return static_cast<FreqDisplayValue>(std::stoi(data.substr(8,1)));
            }

            std::string Menu::CWSetting::ModeCW::PC_KEYING::Set(PCKeyingValue value)
            {
                return fmt::format("EX{:02d}{:02d}{:02d}{:01d};",
                static_cast<int>(MenuGroup::CWSettings),
                static_cast<int>(CWSettingsType::ModeCW),
                static_cast<int>(ModeCWSettings::PC_KEYING),
                static_cast<int>(value));
            }

            std::string Menu::CWSetting::ModeCW::PC_KEYING::Read()
            {
                return fmt::format("EX{:02d}{:02d}{:02d};",
                static_cast<int>(MenuGroup::CWSettings),
                static_cast<int>(CWSettingsType::ModeCW),
                static_cast<int>(ModeCWSettings::PC_KEYING));
            }

            PCKeyingValue Menu::CWSetting::ModeCW::PC_KEYING::Answer(std::string data)
            {
                return static_cast<PCKeyingValue>(std::stoi(data.substr(8,1)));
            }

            std::string Menu::CWSetting::ModeCW::QSK_DELAY_TIME::Set(QSKDelayTime value)
            {
                return fmt::format("EX{:02d}{:02d}{:02d}{:01d};",
                static_cast<int>(MenuGroup::CWSettings),
                static_cast<int>(CWSettingsType::ModeCW),
                static_cast<int>(ModeCWSettings::QSK_DELAY_TIME),
                static_cast<int>(value));
            }

            std::string Menu::CWSetting::ModeCW::QSK_DELAY_TIME::Read()
            {
                return fmt::format("EX{:02d}{:02d}{:02d};",
                static_cast<int>(MenuGroup::CWSettings),
                static_cast<int>(CWSettingsType::ModeCW),
                static_cast<int>(ModeCWSettings::QSK_DELAY_TIME));
            }

            QSKDelayTime Menu::CWSetting::ModeCW::QSK_DELAY_TIME::Answer(std::string data)
            {
                return static_cast<QSKDelayTime>(std::stoi(data.substr(8,1)));
            }

            std::string Menu::CWSetting::ModeCW::INDICATOR::Set(OnOffValue value)
            {
                return fmt::format("EX{:02d}{:02d}{:02d}{:01d};",
                static_cast<int>(MenuGroup::CWSettings),
                static_cast<int>(CWSettingsType::ModeCW),
                static_cast<int>(ModeCWSettings::QSK_DELAY_TIME),
                static_cast<int>(value));
            }

            std::string Menu::CWSetting::ModeCW::INDICATOR::Read()
            {
                return fmt::format("EX{:02d}{:02d}{:02d};",
                static_cast<int>(MenuGroup::CWSettings),
                static_cast<int>(CWSettingsType::ModeCW),
                static_cast<int>(ModeCWSettings::QSK_DELAY_TIME));
            }

            OnOffValue Menu::CWSetting::ModeCW::INDICATOR::Answer(std::string data)
            {
                return static_cast<OnOffValue>(std::stoi(data.substr(8,1)));
            }

            std::string Menu::CWSetting::Keyer::FKEYER_TYPE::Set(KeyerType value)
            {
                return fmt::format("EX{:02d}{:02d}{:02d}{:01d};",
                static_cast<int>(MenuGroup::CWSettings),
                static_cast<int>(CWSettingsType::Keyer),
                static_cast<int>(KeyerSettings::F_KEYER_TYPE),
                static_cast<int>(value));
            }

            std::string Menu::CWSetting::Keyer::FKEYER_TYPE::Read()
            {
                return fmt::format("EX{:02d}{:02d}{:02d};",
                static_cast<int>(MenuGroup::CWSettings),
                static_cast<int>(CWSettingsType::Keyer),
                static_cast<int>(KeyerSettings::F_KEYER_TYPE));
            }

            KeyerType Menu::CWSetting::Keyer::FKEYER_TYPE::Answer(std::string data)
            {
                return static_cast<KeyerType>(std::stoi(data.substr(8,1)));
            }

            std::string Menu::CWSetting::Keyer::FKEYER_DOTDASH::Set(DotDashType value)
            {
                return fmt::format("EX{:02d}{:02d}{:02d}{:01d};",
                static_cast<int>(MenuGroup::CWSettings),
                static_cast<int>(CWSettingsType::Keyer),
                static_cast<int>(KeyerSettings::F_KEYER_DOTDASH),
                static_cast<int>(value));
            }

            std::string Menu::CWSetting::Keyer::FKEYER_DOTDASH::Read()
            {
                return fmt::format("EX{:02d}{:02d}{:02d};",
                static_cast<int>(MenuGroup::CWSettings),
                static_cast<int>(CWSettingsType::Keyer),
                static_cast<int>(KeyerSettings::F_KEYER_DOTDASH));
            }

            DotDashType Menu::CWSetting::Keyer::FKEYER_DOTDASH::Answer(std::string data)
            {
                return static_cast<DotDashType>(std::stoi(data.substr(8,1)));
            }

            std::string Menu::CWSetting::Keyer::RKEYER_TYPE::Set(KeyerType value)
            {
                return fmt::format("EX{:02d}{:02d}{:02d}{:01d};",
                static_cast<int>(MenuGroup::CWSettings),
                static_cast<int>(CWSettingsType::Keyer),
                static_cast<int>(KeyerSettings::R_KEYER_TYPE),
                static_cast<int>(value));
            }

            std::string Menu::CWSetting::Keyer::RKEYER_TYPE::Read()
            {
                return fmt::format("EX{:02d}{:02d}{:02d};",
                static_cast<int>(MenuGroup::CWSettings),
                static_cast<int>(CWSettingsType::Keyer),
                static_cast<int>(KeyerSettings::R_KEYER_TYPE));
            }

            KeyerType Menu::CWSetting::Keyer::RKEYER_TYPE::Answer(std::string data)
            {
                return static_cast<KeyerType>(std::stoi(data.substr(8,1)));
            }

            std::string Menu::CWSetting::Keyer::RKEYER_DOTDASH::Set(DotDashType value)
            {
                return fmt::format("EX{:02d}{:02d}{:02d}{:01d};",
                static_cast<int>(MenuGroup::CWSettings),
                static_cast<int>(CWSettingsType::Keyer),
                static_cast<int>(KeyerSettings::R_KEYER_DOTDASH),
                static_cast<int>(value));
            }

            std::string Menu::CWSetting::Keyer::RKEYER_DOTDASH::Read()
            {
                return fmt::format("EX{:02d}{:02d}{:02d};",
                static_cast<int>(MenuGroup::CWSettings),
                static_cast<int>(CWSettingsType::Keyer),
                static_cast<int>(KeyerSettings::F_KEYER_DOTDASH));
            }

            DotDashType Menu::CWSetting::Keyer::RKEYER_DOTDASH::Answer(std::string data)
            {
                return static_cast<DotDashType>(std::stoi(data.substr(8,1)));
            }

            std::string Menu::CWSetting::Keyer::CW_WEIGHT::Set(int value)
            {
                return fmt::format("EX{:02d}{:02d}{:02d}{:02d};",
                static_cast<int>(MenuGroup::CWSettings),
                static_cast<int>(CWSettingsType::Keyer),
                static_cast<int>(KeyerSettings::WEIGHT),
                static_cast<int>(value));
            }

            std::string Menu::CWSetting::Keyer::CW_WEIGHT::Read()
            {
                return fmt::format("EX{:02d}{:02d}{:02d};",
                static_cast<int>(MenuGroup::CWSettings),
                static_cast<int>(CWSettingsType::Keyer),
                static_cast<int>(KeyerSettings::WEIGHT));
            }

            int Menu::CWSetting::Keyer::CW_WEIGHT::Answer(std::string data)
            {
                return std::stoi(data.substr(8,2));
            }

            std::string Menu::CWSetting::Keyer::NUMBER_STYLE::Set(NumberStyle value)
            {
                return fmt::format("EX{:02d}{:02d}{:02d}{:01d};",
                static_cast<int>(MenuGroup::CWSettings),
                static_cast<int>(CWSettingsType::Keyer),
                static_cast<int>(KeyerSettings::NUMBER_STYLE),
                static_cast<int>(value));
            }

            std::string Menu::CWSetting::Keyer::NUMBER_STYLE::Read()
            {
                return fmt::format("EX{:02d}{:02d}{:02d};",
                static_cast<int>(MenuGroup::CWSettings),
                static_cast<int>(CWSettingsType::Keyer),
                static_cast<int>(KeyerSettings::NUMBER_STYLE));
            }

            NumberStyle Menu::CWSetting::Keyer::NUMBER_STYLE::Answer(std::string data)
            {
                return static_cast<NumberStyle>(std::stoi(data.substr(8,1)));
            }

            std::string Menu::CWSetting::Keyer::MEMORY_1::Set(CWMemoryType value)
            {
                return fmt::format("EX{:02d}{:02d}{:02d}{:01d};",
                static_cast<int>(MenuGroup::CWSettings),
                static_cast<int>(CWSettingsType::Keyer),
                static_cast<int>(KeyerSettings::MEMORY_1),
                static_cast<int>(value));
            }

            std::string Menu::CWSetting::Keyer::MEMORY_1::Read()
            {
                return fmt::format("EX{:02d}{:02d}{:02d};",
                static_cast<int>(MenuGroup::CWSettings),
                static_cast<int>(CWSettingsType::Keyer),
                static_cast<int>(KeyerSettings::MEMORY_1));
            }

            CWMemoryType Menu::CWSetting::Keyer::MEMORY_1::Answer(std::string data)
            {
                return static_cast<CWMemoryType>(std::stoi(data.substr(8,1)));
            }

                std::string Menu::CWSetting::Keyer::MEMORY_2::Set(CWMemoryType value)
            {
                return fmt::format("EX{:02d}{:02d}{:02d}{:01d};",
                static_cast<int>(MenuGroup::CWSettings),
                static_cast<int>(CWSettingsType::Keyer),
                static_cast<int>(KeyerSettings::MEMORY_2),
                static_cast<int>(value));
            }

            std::string Menu::CWSetting::Keyer::MEMORY_2::Read()
            {
                return fmt::format("EX{:02d}{:02d}{:02d};",
                static_cast<int>(MenuGroup::CWSettings),
                static_cast<int>(CWSettingsType::Keyer),
                static_cast<int>(KeyerSettings::MEMORY_2));
            }

            CWMemoryType Menu::CWSetting::Keyer::MEMORY_2::Answer(std::string data)
            {
                return static_cast<CWMemoryType>(std::stoi(data.substr(8,1)));
            }

            std::string Menu::CWSetting::Keyer::MEMORY_3::Set(CWMemoryType value)
            {
                return fmt::format("EX{:02d}{:02d}{:02d}{:01d};",
                static_cast<int>(MenuGroup::CWSettings),
                static_cast<int>(CWSettingsType::Keyer),
                static_cast<int>(KeyerSettings::MEMORY_3),
                static_cast<int>(value));
            }

            std::string Menu::CWSetting::Keyer::MEMORY_3::Read()
            {
                return fmt::format("EX{:02d}{:02d}{:02d};",
                static_cast<int>(MenuGroup::CWSettings),
                static_cast<int>(CWSettingsType::Keyer),
                static_cast<int>(KeyerSettings::MEMORY_3));
            }

            CWMemoryType Menu::CWSetting::Keyer::MEMORY_3::Answer(std::string data)
            {
                return static_cast<CWMemoryType>(std::stoi(data.substr(8,1)));
            }

            std::string Menu::CWSetting::Keyer::MEMORY_4::Set(CWMemoryType value)
            {
                return fmt::format("EX{:02d}{:02d}{:02d}{:01d};",
                static_cast<int>(MenuGroup::CWSettings),
                static_cast<int>(CWSettingsType::Keyer),
                static_cast<int>(KeyerSettings::MEMORY_4),
                static_cast<int>(value));
            }

            std::string Menu::CWSetting::Keyer::MEMORY_4::Read()
            {
                return fmt::format("EX{:02d}{:02d}{:02d};",
                static_cast<int>(MenuGroup::CWSettings),
                static_cast<int>(CWSettingsType::Keyer),
                static_cast<int>(KeyerSettings::MEMORY_4));
            }

            CWMemoryType Menu::CWSetting::Keyer::MEMORY_4::Answer(std::string data)
            {
                return static_cast<CWMemoryType>(std::stoi(data.substr(8,1)));
            }

            std::string Menu::CWSetting::Keyer::MEMORY_5::Set(CWMemoryType value)
            {
                return fmt::format("EX{:02d}{:02d}{:02d}{:01d};",
                static_cast<int>(MenuGroup::CWSettings),
                static_cast<int>(CWSettingsType::Keyer),
                static_cast<int>(KeyerSettings::MEMORY_5),
                static_cast<int>(value));
            }

            std::string Menu::CWSetting::Keyer::MEMORY_5::Read()
            {
                return fmt::format("EX{:02d}{:02d}{:02d};",
                static_cast<int>(MenuGroup::CWSettings),
                static_cast<int>(CWSettingsType::Keyer),
                static_cast<int>(KeyerSettings::MEMORY_5));
            }

            CWMemoryType Menu::CWSetting::Keyer::MEMORY_5::Answer(std::string data)
            {
                return static_cast<CWMemoryType>(std::stoi(data.substr(8,1)));
            }

            std::string Menu::CWSetting::Keyer::REPEAT_INTERVAL::Set(int value)
            {
                return fmt::format("EX{:02d}{:02d}{:02d}{:02d};",
                static_cast<int>(MenuGroup::CWSettings),
                static_cast<int>(CWSettingsType::Keyer),
                static_cast<int>(KeyerSettings::REPEAT_INTERVAL),
                static_cast<int>(value));
            }

            std::string Menu::CWSetting::Keyer::REPEAT_INTERVAL::Read()
            {
                return fmt::format("EX{:02d}{:02d}{:02d};",
                static_cast<int>(MenuGroup::CWSettings),
                static_cast<int>(CWSettingsType::Keyer),
                static_cast<int>(KeyerSettings::REPEAT_INTERVAL));
            }

            int Menu::CWSetting::Keyer::REPEAT_INTERVAL::Answer(std::string data)
            {
                return std::stoi(data.substr(8,2));
            }

            std::string Menu::CWSetting::Decoder::DECODE_BW::Set(CWDecodeBW value)
            {
                return fmt::format("EX{:02d}{:02d}{:02d}{:02d};",
                static_cast<int>(MenuGroup::CWSettings),
                static_cast<int>(CWSettingsType::Decode_CW),
                static_cast<int>(DecodeCWSettings::DECODE_BW),
                static_cast<int>(value));
            }

            std::string Menu::CWSetting::Decoder::DECODE_BW::Read()
            {
                return fmt::format("EX{:02d}{:02d}{:02d};",
                static_cast<int>(MenuGroup::CWSettings),
                static_cast<int>(CWSettingsType::Decode_CW),
                static_cast<int>(DecodeCWSettings::DECODE_BW));
            }

            CWDecodeBW Menu::CWSetting::Decoder::DECODE_BW::Answer(std::string data)
            {
                return static_cast<CWDecodeBW>(std::stoi(data.substr(8,1)));
            }

            std::string Menu::OperationSetting::General::DECODE_RX_SELECT::Set(MainSubValue value)
            {
                return fmt::format("EX{:02d}{:02d}{:02d}{:01d};",
                static_cast<int>(MenuGroup::OperationSetting),
                static_cast<int>(OperationSettingType::General),
                static_cast<int>(GeneralSettings::DECODE_RX_SELECT),
                static_cast<int>(value));
            }

            std::string Menu::OperationSetting::General::DECODE_RX_SELECT::Read()
            {
                return fmt::format("EX{:02d}{:02d}{:02d};",
                static_cast<int>(MenuGroup::OperationSetting),
                static_cast<int>(OperationSettingType::General),
                static_cast<int>(GeneralSettings::DECODE_RX_SELECT));
            }

            MainSubValue Menu::OperationSetting::General::DECODE_RX_SELECT::Answer(std::string data)
            {
                return static_cast<MainSubValue>(std::stoi(data.substr(8,1)));
            }

            std::string Menu::OperationSetting::General::HEADPHONE_MIX::Set(HeadPhoneMixValue value)
            {
                return fmt::format("EX{:02d}{:02d}{:02d}{:01d};",
                static_cast<int>(MenuGroup::OperationSetting),
                static_cast<int>(OperationSettingType::General),
                static_cast<int>(GeneralSettings::HEADPHONE_MIX),
                static_cast<int>(value));
            }

            std::string Menu::OperationSetting::General::HEADPHONE_MIX::Read()
            {
                return fmt::format("EX{:02d}{:02d}{:02d};",
                static_cast<int>(MenuGroup::OperationSetting),
                static_cast<int>(OperationSettingType::General),
                static_cast<int>(GeneralSettings::HEADPHONE_MIX));
            }

            HeadPhoneMixValue Menu::OperationSetting::General::HEADPHONE_MIX::Answer(std::string data)
            {
                return static_cast<HeadPhoneMixValue>(std::stoi(data.substr(8,1)));
            }

            std::string Menu::OperationSetting::General::ANT3_SELECT::Set(ANT3Selection value)
            {
                return fmt::format("EX{:02d}{:02d}{:02d}{:01d};",
                static_cast<int>(MenuGroup::OperationSetting),
                static_cast<int>(OperationSettingType::General),
                static_cast<int>(GeneralSettings::ANT3_SELECT),
                static_cast<int>(value));
            }

            std::string Menu::OperationSetting::General::ANT3_SELECT::Read()
            {
                return fmt::format("EX{:02d}{:02d}{:02d};",
                static_cast<int>(MenuGroup::OperationSetting),
                static_cast<int>(OperationSettingType::General),
                static_cast<int>(GeneralSettings::ANT3_SELECT));
            }

            ANT3Selection Menu::OperationSetting::General::ANT3_SELECT::Answer(std::string data)
            {
                return static_cast<ANT3Selection>(std::stoi(data.substr(8,1)));
            }

            std::string Menu::OperationSetting::General::NB_WIDTH::Set(NBWidth value)
            {
                return fmt::format("EX{:02d}{:02d}{:02d}{:01d};",
                static_cast<int>(MenuGroup::OperationSetting),
                static_cast<int>(OperationSettingType::General),
                static_cast<int>(GeneralSettings::NB_WIDTH),
                static_cast<int>(value));
            }

            std::string Menu::OperationSetting::General::NB_WIDTH::Read()
            {
                return fmt::format("EX{:02d}{:02d}{:02d};",
                static_cast<int>(MenuGroup::OperationSetting),
                static_cast<int>(OperationSettingType::General),
                static_cast<int>(GeneralSettings::NB_WIDTH));
            }

            NBWidth Menu::OperationSetting::General::NB_WIDTH::Answer(std::string data)
            {
                return static_cast<NBWidth>(std::stoi(data.substr(8,1)));
            }

            std::string Menu::OperationSetting::General::NB_REJECTION::Set(NBRejectionValue value)
            {
                return fmt::format("EX{:02d}{:02d}{:02d}{:01d};",
                static_cast<int>(MenuGroup::OperationSetting),
                static_cast<int>(OperationSettingType::General),
                static_cast<int>(GeneralSettings::NB_REJECTION),
                static_cast<int>(value));
            }

            std::string Menu::OperationSetting::General::NB_REJECTION::Read()
            {
                return fmt::format("EX{:02d}{:02d}{:02d};",
                static_cast<int>(MenuGroup::OperationSetting),
                static_cast<int>(OperationSettingType::General),
                static_cast<int>(GeneralSettings::NB_REJECTION));
            }

            NBRejectionValue Menu::OperationSetting::General::NB_REJECTION::Answer(std::string data)
            {
                return static_cast<NBRejectionValue>(std::stoi(data.substr(8,1)));
            }

            std::string Menu::OperationSetting::General::BEEP_LEVEL::Set(int value)
            {
                return fmt::format("EX{:02d}{:02d}{:02d}{:03d};",
                static_cast<int>(MenuGroup::OperationSetting),
                static_cast<int>(OperationSettingType::General),
                static_cast<int>(GeneralSettings::BEEP_LEVEL),
                static_cast<int>(value));
            }

            std::string Menu::OperationSetting::General::BEEP_LEVEL::Read()
            {
                return fmt::format("EX{:02d}{:02d}{:02d};",
                static_cast<int>(MenuGroup::OperationSetting),
                static_cast<int>(OperationSettingType::General),
                static_cast<int>(GeneralSettings::BEEP_LEVEL));
            }

            int Menu::OperationSetting::General::BEEP_LEVEL::Answer(std::string data)
            {
                return std::stoi(data.substr(8,3));
            }

            std::string Menu::OperationSetting::General::RF_SQL_VR::Set(VRType value)
            {
                return fmt::format("EX{:02d}{:02d}{:02d}{:01d};",
                static_cast<int>(MenuGroup::OperationSetting),
                static_cast<int>(OperationSettingType::General),
                static_cast<int>(GeneralSettings::RFSQL_VR),
                static_cast<int>(value));
            }

            std::string Menu::OperationSetting::General::RF_SQL_VR::Read()
            {
                return fmt::format("EX{:02d}{:02d}{:02d};",
                static_cast<int>(MenuGroup::OperationSetting),
                static_cast<int>(OperationSettingType::General),
                static_cast<int>(GeneralSettings::RFSQL_VR));
            }

            VRType Menu::OperationSetting::General::RF_SQL_VR::Answer(std::string data)
            {
                return static_cast<VRType>(std::stoi(data.substr(8,1)));
            }

            std::string Menu::OperationSetting::General::TUNER_232C_SELECT::Set(TunerRS232Select value)
            {
                return fmt::format("EX{:02d}{:02d}{:02d}{:01d};",
                static_cast<int>(MenuGroup::OperationSetting),
                static_cast<int>(OperationSettingType::General),
                static_cast<int>(GeneralSettings::TUNER_RS232_SELECT),
                static_cast<int>(value));
            }

            std::string Menu::OperationSetting::General::TUNER_232C_SELECT::Read()
            {
                return fmt::format("EX{:02d}{:02d}{:02d};",
                static_cast<int>(MenuGroup::OperationSetting),
                static_cast<int>(OperationSettingType::General),
                static_cast<int>(GeneralSettings::TUNER_RS232_SELECT));
            }

            TunerRS232Select Menu::OperationSetting::General::TUNER_232C_SELECT::Answer(std::string data)
            {
                return static_cast<TunerRS232Select>(std::stoi(data.substr(8,1)));
            }

            std::string Menu::OperationSetting::General::RS232_RATE::Set(RS232CRate value)
            {
                return fmt::format("EX{:02d}{:02d}{:02d}{:01d};",
                static_cast<int>(MenuGroup::OperationSetting),
                static_cast<int>(OperationSettingType::General),
                static_cast<int>(GeneralSettings::RS232C_RATE),
                static_cast<int>(value));
            }

            std::string Menu::OperationSetting::General::RS232_RATE::Read()
            {
                return fmt::format("EX{:02d}{:02d}{:02d};",
                static_cast<int>(MenuGroup::OperationSetting),
                static_cast<int>(OperationSettingType::General),
                static_cast<int>(GeneralSettings::RS232C_RATE));
            }

            RS232CRate Menu::OperationSetting::General::RS232_RATE::Answer(std::string data)
            {
                return static_cast<RS232CRate>(std::stoi(data.substr(8,1)));
            }

            std::string Menu::OperationSetting::General::RS232_TIME_OUT_TIMER::Set(RS232CTimeOutValue value)
            {
                return fmt::format("EX{:02d}{:02d}{:02d}{:01d};",
                static_cast<int>(MenuGroup::OperationSetting),
                static_cast<int>(OperationSettingType::General),
                static_cast<int>(GeneralSettings::RS232C_TIME_OUT),
                static_cast<int>(value));
            }

            std::string Menu::OperationSetting::General::RS232_TIME_OUT_TIMER::Read()
            {
                return fmt::format("EX{:02d}{:02d}{:02d};",
                static_cast<int>(MenuGroup::OperationSetting),
                static_cast<int>(OperationSettingType::General),
                static_cast<int>(GeneralSettings::RS232C_TIME_OUT));
            }

            RS232CTimeOutValue Menu::OperationSetting::General::RS232_TIME_OUT_TIMER::Answer(std::string data)
            {
                return static_cast<RS232CTimeOutValue>(std::stoi(data.substr(8,1)));
            }



            std::string Menu::OperationSetting::General::CAT_RATE::Set(CATRateValue value)
            {
                return fmt::format("EX{:02d}{:02d}{:02d}{:01d};",
                static_cast<int>(MenuGroup::OperationSetting),
                static_cast<int>(OperationSettingType::General),
                static_cast<int>(GeneralSettings::CAT_RATE),
                static_cast<int>(value));
            }

            std::string Menu::OperationSetting::General::CAT_RATE::Read()
            {
                return fmt::format("EX{:02d}{:02d}{:02d};",
                static_cast<int>(MenuGroup::OperationSetting),
                static_cast<int>(OperationSettingType::General),
                static_cast<int>(GeneralSettings::CAT_RATE));
            }

            CATRateValue Menu::OperationSetting::General::CAT_RATE::Answer(std::string data)
            {
                return static_cast<CATRateValue>(std::stoi(data.substr(8,1)));
            }

            std::string Menu::OperationSetting::General::CAT_TIME_OUT_TIMER::Set(CATTimeOutValue value)
            {
                return fmt::format("EX{:02d}{:02d}{:02d}{:01d};",
                static_cast<int>(MenuGroup::OperationSetting),
                static_cast<int>(OperationSettingType::General),
                static_cast<int>(GeneralSettings::CAT_TIMEOUT),
                static_cast<int>(value));
            }

            std::string Menu::OperationSetting::General::CAT_TIME_OUT_TIMER::Read()
            {
                return fmt::format("EX{:02d}{:02d}{:02d};",
                static_cast<int>(MenuGroup::OperationSetting),
                static_cast<int>(OperationSettingType::General),
                static_cast<int>(GeneralSettings::CAT_TIMEOUT));
            }

            CATTimeOutValue Menu::OperationSetting::General::CAT_TIME_OUT_TIMER::Answer(std::string data)
            {
                return static_cast<CATTimeOutValue>(std::stoi(data.substr(8,1)));
            }

            std::string Menu::OperationSetting::General::CAT_RTS::Set(EnableDisableValue value)
            {
                return fmt::format("EX{:02d}{:02d}{:02d}{:01d};",
                static_cast<int>(MenuGroup::OperationSetting),
                static_cast<int>(OperationSettingType::General),
                static_cast<int>(GeneralSettings::CAT_RTS),
                static_cast<int>(value));
            }

            std::string Menu::OperationSetting::General::CAT_RTS::Read()
            {
                return fmt::format("EX{:02d}{:02d}{:02d};",
                static_cast<int>(MenuGroup::OperationSetting),
                static_cast<int>(OperationSettingType::General),
                static_cast<int>(GeneralSettings::CAT_RTS));
            }

            EnableDisableValue Menu::OperationSetting::General::CAT_RTS::Answer(std::string data)
            {
                return static_cast<EnableDisableValue>(std::stoi(data.substr(8,1)));
            }

            std::string Menu::OperationSetting::General::QMB_CH::Set(QMBChValue value)
            {
                return fmt::format("EX{:02d}{:02d}{:02d}{:01d};",
                static_cast<int>(MenuGroup::OperationSetting),
                static_cast<int>(OperationSettingType::General),
                static_cast<int>(GeneralSettings::QMB_CH),
                static_cast<int>(value));
            }

            std::string Menu::OperationSetting::General::QMB_CH::Read()
            {
                return fmt::format("EX{:02d}{:02d}{:02d};",
                static_cast<int>(MenuGroup::OperationSetting),
                static_cast<int>(OperationSettingType::General),
                static_cast<int>(GeneralSettings::QMB_CH));
            }

            QMBChValue Menu::OperationSetting::General::QMB_CH::Answer(std::string data)
            {
                return static_cast<QMBChValue>(std::stoi(data.substr(8,1)));
            }

            std::string Menu::OperationSetting::General::MEM_GROUP::Set(EnableDisableValue value)
            {
                return fmt::format("EX{:02d}{:02d}{:02d}{:01d};",
                static_cast<int>(MenuGroup::OperationSetting),
                static_cast<int>(OperationSettingType::General),
                static_cast<int>(GeneralSettings::MEM_GROUP),
                static_cast<int>(value));
            }

            std::string Menu::OperationSetting::General::MEM_GROUP::Read()
            {
                return fmt::format("EX{:02d}{:02d}{:02d};",
                static_cast<int>(MenuGroup::OperationSetting),
                static_cast<int>(OperationSettingType::General),
                static_cast<int>(GeneralSettings::MEM_GROUP));
            }

            EnableDisableValue Menu::OperationSetting::General::MEM_GROUP::Answer(std::string data)
            {
                return static_cast<EnableDisableValue>(std::stoi(data.substr(8,1)));
            }

            std::string Menu::OperationSetting::General::QUICK_SPLIT_INPUT::Set(EnableDisableValue value)
            {
                return fmt::format("EX{:02d}{:02d}{:02d}{:01d};",
                static_cast<int>(MenuGroup::OperationSetting),
                static_cast<int>(OperationSettingType::General),
                static_cast<int>(GeneralSettings::QUICK_SPLIT_INPUT),
                static_cast<int>(value));
            }

            std::string Menu::OperationSetting::General::QUICK_SPLIT_INPUT::Read()
            {
                return fmt::format("EX{:02d}{:02d}{:02d};",
                static_cast<int>(MenuGroup::OperationSetting),
                static_cast<int>(OperationSettingType::General),
                static_cast<int>(GeneralSettings::QUICK_SPLIT_INPUT));
            }

            EnableDisableValue Menu::OperationSetting::General::QUICK_SPLIT_INPUT::Answer(std::string data)
            {
                return static_cast<EnableDisableValue>(std::stoi(data.substr(8,1)));
            }

            std::string Menu::OperationSetting::General::QUICK_SPLIT_FREQ::Set( int value)
            {
                return fmt::format("EX{:02d}{:02d}{:02d}{:+03d};",
                static_cast<int>(MenuGroup::OperationSetting),
                static_cast<int>(OperationSettingType::General),
                static_cast<int>(GeneralSettings::QUICK_SPLIT_FREQ),
                static_cast<int>(value));
            }

            std::string Menu::OperationSetting::General::QUICK_SPLIT_FREQ::Read()
            {
                return fmt::format("EX{:02d}{:02d}{:02d};",
                static_cast<int>(MenuGroup::OperationSetting),
                static_cast<int>(OperationSettingType::General),
                static_cast<int>(GeneralSettings::QUICK_SPLIT_FREQ));
            }

            int Menu::OperationSetting::General::QUICK_SPLIT_FREQ::Answer(std::string data)
            {
                return std::stoi(data.substr(8,3));
            }

            std::string Menu::OperationSetting::General::TX_TIME_OUT_TIMER::Set(int value)
            {
                return fmt::format("EX{:02d}{:02d}{:02d}{:02d};",
                static_cast<int>(MenuGroup::OperationSetting),
                static_cast<int>(OperationSettingType::General),
                static_cast<int>(GeneralSettings::TX_TIME_OUT_TIMER),
                static_cast<int>(value));
            }

            std::string Menu::OperationSetting::General::TX_TIME_OUT_TIMER::Read()
            {
                return fmt::format("EX{:02d}{:02d}{:02d};",
                static_cast<int>(MenuGroup::OperationSetting),
                static_cast<int>(OperationSettingType::General),
                static_cast<int>(GeneralSettings::TX_TIME_OUT_TIMER));
            }

            int Menu::OperationSetting::General::TX_TIME_OUT_TIMER::Answer(std::string data)
            {
                return std::stoi(data.substr(8,2));
            }

            std::string Menu::OperationSetting::General::MIC_SCAN::Set(EnableDisableValue value)
            {
                return fmt::format("EX{:02d}{:02d}{:02d}{:01d};",
                static_cast<int>(MenuGroup::OperationSetting),
                static_cast<int>(OperationSettingType::General),
                static_cast<int>(GeneralSettings::MIC_SCAN),
                static_cast<int>(value));
            }

            std::string Menu::OperationSetting::General::MIC_SCAN::Read()
            {
                return fmt::format("EX{:02d}{:02d}{:02d};",
                static_cast<int>(MenuGroup::OperationSetting),
                static_cast<int>(OperationSettingType::General),
                static_cast<int>(GeneralSettings::MIC_SCAN));
            }

            EnableDisableValue Menu::OperationSetting::General::MIC_SCAN::Answer(std::string data)
            {
                return static_cast<EnableDisableValue>(std::stoi(data.substr(8,1)));
            }

            std::string Menu::OperationSetting::General::MIC_SCAN_RESUME::Set(MicScanResumeType value)
            {
                return fmt::format("EX{:02d}{:02d}{:02d}{:01d};",
                static_cast<int>(MenuGroup::OperationSetting),
                static_cast<int>(OperationSettingType::General),
                static_cast<int>(GeneralSettings::MIC_SCAN_RESUME),
                static_cast<int>(value));
            }

            std::string Menu::OperationSetting::General::MIC_SCAN_RESUME::Read()
            {
                return fmt::format("EX{:02d}{:02d}{:02d};",
                static_cast<int>(MenuGroup::OperationSetting),
                static_cast<int>(OperationSettingType::General),
                static_cast<int>(GeneralSettings::MIC_SCAN_RESUME));
            }

            MicScanResumeType Menu::OperationSetting::General::MIC_SCAN_RESUME::Answer(std::string data)
            {
                return static_cast<MicScanResumeType>(std::stoi(data.substr(8,1)));
            }

            std::string Menu::OperationSetting::General::REF_FREQ_ADJ::Set(int value)
            {
                return fmt::format("EX{:02d}{:02d}{:02d}{:+03d};",
                static_cast<int>(MenuGroup::OperationSetting),
                static_cast<int>(OperationSettingType::General),
                static_cast<int>(GeneralSettings::MIC_SCAN_RESUME),
                static_cast<int>(value));
            }

            std::string Menu::OperationSetting::General::REF_FREQ_ADJ::Read()
            {
                return fmt::format("EX{:02d}{:02d}{:02d};",
                static_cast<int>(MenuGroup::OperationSetting),
                static_cast<int>(OperationSettingType::General),
                static_cast<int>(GeneralSettings::MIC_SCAN_RESUME));
            }

            int Menu::OperationSetting::General::REF_FREQ_ADJ::Answer(std::string data)
            {
                return std::stoi(data.substr(8,3));
            }

            std::string Menu::OperationSetting::General::CS_DIAL::Set(CSDialType value)
            {
                return fmt::format("EX{:02d}{:02d}{:02d}{:02d};",
                static_cast<int>(MenuGroup::OperationSetting),
                static_cast<int>(OperationSettingType::General),
                static_cast<int>(GeneralSettings::CS_DIAL),
                static_cast<int>(value));
            }

            std::string Menu::OperationSetting::General::CS_DIAL::Read()
            {
                return fmt::format("EX{:02d}{:02d}{:02d};",
                static_cast<int>(MenuGroup::OperationSetting),
                static_cast<int>(OperationSettingType::General),
                static_cast<int>(GeneralSettings::CS_DIAL));
            }

            CSDialType Menu::OperationSetting::General::CS_DIAL::Answer(std::string data)
            {
                return static_cast<CSDialType>(std::stoi(data.substr(8,2)));
            }

            std::string Menu::OperationSetting::General::KEYBOARD_LANGUAGE::Set(KeyboardLangaugeValue value)
            {
                return fmt::format("EX{:02d}{:02d}{:02d}{:02d};",
                static_cast<int>(MenuGroup::OperationSetting),
                static_cast<int>(OperationSettingType::General),
                static_cast<int>(GeneralSettings::KEYBOARD_LANGUAGE),
                static_cast<int>(value));
            }

            std::string Menu::OperationSetting::General::KEYBOARD_LANGUAGE::Read()
            {
                return fmt::format("EX{:02d}{:02d}{:02d};",
                static_cast<int>(MenuGroup::OperationSetting),
                static_cast<int>(OperationSettingType::General),
                static_cast<int>(GeneralSettings::KEYBOARD_LANGUAGE));
            }

            KeyboardLangaugeValue Menu::OperationSetting::General::KEYBOARD_LANGUAGE::Answer(std::string data)
            {
                return static_cast<KeyboardLangaugeValue>(std::stoi(data.substr(8,2)));
            }

            std::string Menu::OperationSetting::RX_DSP::APF_WIDTH::Set(APFWidthValue value)
            {
                return fmt::format("EX{:02d}{:02d}{:02d}{:01d};",
                static_cast<int>(MenuGroup::OperationSetting),
                static_cast<int>(OperationSettingType::RX_DSP),
                static_cast<int>(RX_DSPSettings::APF_WIDTH),
                static_cast<int>(value));
            }

            std::string Menu::OperationSetting::RX_DSP::APF_WIDTH::Read()
            {
                return fmt::format("EX{:02d}{:02d}{:02d};",
                static_cast<int>(MenuGroup::OperationSetting),
                static_cast<int>(OperationSettingType::RX_DSP),
                static_cast<int>(RX_DSPSettings::APF_WIDTH));
            }

            APFWidthValue Menu::OperationSetting::RX_DSP::APF_WIDTH::Answer(std::string data)
            {
              return static_cast<APFWidthValue>(std::stoi(data.substr(8,1)));
            }

            std::string Menu::OperationSetting::RX_DSP::CONTOUR_LEVEL::Set(int value)
            {
                return fmt::format("EX{:02d}{:02d}{:02d}{:+03d};",
                static_cast<int>(MenuGroup::OperationSetting),
                static_cast<int>(OperationSettingType::RX_DSP),
                static_cast<int>(RX_DSPSettings::CONTOUR_LEVEL),
                static_cast<int>(value));
            }

            std::string Menu::OperationSetting::RX_DSP::CONTOUR_LEVEL::Read()
            {
                return fmt::format("EX{:02d}{:02d}{:02d};",
                static_cast<int>(MenuGroup::OperationSetting),
                static_cast<int>(OperationSettingType::RX_DSP),
                static_cast<int>(RX_DSPSettings::CONTOUR_LEVEL));
            }

            int Menu::OperationSetting::RX_DSP::CONTOUR_LEVEL::Answer(std::string data)
            {
                return std::stoi(data.substr(8,3));
            }

            std::string Menu::OperationSetting::RX_DSP::CONTOUR_WIDTH::Set(int value)
            {
                return fmt::format("EX{:02d}{:02d}{:02d}{:02d};",
                static_cast<int>(MenuGroup::OperationSetting),
                static_cast<int>(OperationSettingType::RX_DSP),
                static_cast<int>(RX_DSPSettings::CONTOUR_WIDTH),
                static_cast<int>(value));
            }

            std::string Menu::OperationSetting::RX_DSP::CONTOUR_WIDTH::Read()
            {
                return fmt::format("EX{:02d}{:02d}{:02d};",
                static_cast<int>(MenuGroup::OperationSetting),
                static_cast<int>(OperationSettingType::RX_DSP),
                static_cast<int>(RX_DSPSettings::CONTOUR_WIDTH));
            }

            int Menu::OperationSetting::RX_DSP::CONTOUR_WIDTH::Answer(std::string data)
            {
                return std::stoi(data.substr(8,2));
            }

            std::string Menu::OperationSetting::RX_DSP::DNR_LEVEL::Set(int value)
            {
                return fmt::format("EX{:02d}{:02d}{:02d}{:02d};",
                static_cast<int>(MenuGroup::OperationSetting),
                static_cast<int>(OperationSettingType::RX_DSP),
                static_cast<int>(RX_DSPSettings::DNR_LEVEL),
                static_cast<int>(value));
            }

            std::string Menu::OperationSetting::RX_DSP::DNR_LEVEL::Read()
            {
                return fmt::format("EX{:02d}{:02d}{:02d};",
                static_cast<int>(MenuGroup::OperationSetting),
                static_cast<int>(OperationSettingType::RX_DSP),
                static_cast<int>(RX_DSPSettings::DNR_LEVEL));
            }

            int Menu::OperationSetting::RX_DSP::DNR_LEVEL::Answer(std::string data)
            {
                return std::stoi(data.substr(8,2));
            }

            std::string Menu::OperationSetting::RX_DSP::IF_NOTCH_WIDTH::Set(IFNotchWidth value)
            {
                return fmt::format("EX{:02d}{:02d}{:02d}{:01d};",
                static_cast<int>(MenuGroup::OperationSetting),
                static_cast<int>(OperationSettingType::RX_DSP),
                static_cast<int>(RX_DSPSettings::IF_NOTCH_WIDTH),
                static_cast<int>(value));
            }

            std::string Menu::OperationSetting::RX_DSP::IF_NOTCH_WIDTH::Read()
            {
                return fmt::format("EX{:02d}{:02d}{:02d};",
                static_cast<int>(MenuGroup::OperationSetting),
                static_cast<int>(OperationSettingType::RX_DSP),
                static_cast<int>(RX_DSPSettings::IF_NOTCH_WIDTH));
            }

            IFNotchWidth Menu::OperationSetting::RX_DSP::IF_NOTCH_WIDTH::Answer(std::string data)
            {
                return static_cast<IFNotchWidth>(std::stoi(data.substr(8,1)));
            }

            std::string Menu::OperationSetting::TX_AUDIO::PROC_TYPE::Set(ProcType value)
            {
                return fmt::format("EX{:02d}{:02d}{:02d}{:01d};",
                static_cast<int>(MenuGroup::OperationSetting),
                static_cast<int>(OperationSettingType::TX_Audio),
                static_cast<int>(TXAudioSettings::PROC_TYPE),
                static_cast<int>(value));
            }

            std::string Menu::OperationSetting::TX_AUDIO::PROC_TYPE::Read()
            {
                return fmt::format("EX{:02d}{:02d}{:02d};",
                static_cast<int>(MenuGroup::OperationSetting),
                static_cast<int>(OperationSettingType::TX_Audio),
                static_cast<int>(TXAudioSettings::PROC_TYPE));
            }

            ProcType Menu::OperationSetting::TX_AUDIO::PROC_TYPE::Answer(std::string data)
            {
                    return static_cast<ProcType>(std::stoi(data.substr(8,1)));
            }

            std::string Menu::OperationSetting::TX_AUDIO::AMC_RELEASE_TIME::Set(AMCReleaseTime value)
            {
                return fmt::format("EX{:02d}{:02d}{:02d}{:01d};",
                static_cast<int>(MenuGroup::OperationSetting),
                static_cast<int>(OperationSettingType::TX_Audio),
                static_cast<int>(TXAudioSettings::AMC_RELEASE_TIME),
                static_cast<int>(value));
            }

            std::string Menu::OperationSetting::TX_AUDIO::AMC_RELEASE_TIME::Read()
            {
                return fmt::format("EX{:02d}{:02d}{:02d};",
                static_cast<int>(MenuGroup::OperationSetting),
                static_cast<int>(OperationSettingType::TX_Audio),
                static_cast<int>(TXAudioSettings::AMC_RELEASE_TIME));
            }

            AMCReleaseTime Menu::OperationSetting::TX_AUDIO::AMC_RELEASE_TIME::Answer(std::string data)
            {
                return static_cast<AMCReleaseTime>(std::stoi(data.substr(8,1)));
            }

            std::string Menu::OperationSetting::TX_AUDIO::EQ1_FREQ::Set(EQ1FreqValue value)
            {
                return fmt::format("EX{:02d}{:02d}{:02d}{:02d};",
                static_cast<int>(MenuGroup::OperationSetting),
                static_cast<int>(OperationSettingType::TX_Audio),
                static_cast<int>(TXAudioSettings::EQ1_FREQ),
                static_cast<int>(value));
            }

            std::string Menu::OperationSetting::TX_AUDIO::EQ1_FREQ::Read()
            {
                return fmt::format("EX{:02d}{:02d}{:02d};",
                static_cast<int>(MenuGroup::OperationSetting),
                static_cast<int>(OperationSettingType::TX_Audio),
                static_cast<int>(TXAudioSettings::EQ1_FREQ));
            }

            EQ1FreqValue Menu::OperationSetting::TX_AUDIO::EQ1_FREQ::Answer(std::string data)
            {
                return static_cast<EQ1FreqValue>(std::stoi(data.substr(8,2)));
            }

            std::string Menu::OperationSetting::TX_AUDIO::EQ1_LEVEL::Set(int value)
            {
                return fmt::format("EX{:02d}{:02d}{:02d}{:+03d};",
                static_cast<int>(MenuGroup::OperationSetting),
                static_cast<int>(OperationSettingType::TX_Audio),
                static_cast<int>(TXAudioSettings::EQ1_LEVEL),
                static_cast<int>(value));
            }

            std::string Menu::OperationSetting::TX_AUDIO::EQ1_LEVEL::Read()
            {
                return fmt::format("EX{:02d}{:02d}{:02d};",
                static_cast<int>(MenuGroup::OperationSetting),
                static_cast<int>(OperationSettingType::TX_Audio),
                static_cast<int>(TXAudioSettings::EQ1_LEVEL));
            }

            int Menu::OperationSetting::TX_AUDIO::EQ1_LEVEL::Answer(std::string data)
            {
                return std::stoi(data.substr(8,3));
            }

            std::string Menu::OperationSetting::TX_AUDIO::EQ1_BWTH::Set(int value)
            {
                return fmt::format("EX{:02d}{:02d}{:02d}{:02d};",
                static_cast<int>(MenuGroup::OperationSetting),
                static_cast<int>(OperationSettingType::TX_Audio),
                static_cast<int>(TXAudioSettings::EQ1_BWDTH),
                static_cast<int>(value));
            }

            std::string Menu::OperationSetting::TX_AUDIO::EQ1_BWTH::Read()
            {
                return fmt::format("EX{:02d}{:02d}{:02d};",
                static_cast<int>(MenuGroup::OperationSetting),
                static_cast<int>(OperationSettingType::TX_Audio),
                static_cast<int>(TXAudioSettings::EQ1_BWDTH));
            }

            int Menu::OperationSetting::TX_AUDIO::EQ1_BWTH::Answer(std::string data)
            {
                return std::stoi(data.substr(8,2));
            }

            std::string Menu::OperationSetting::TX_AUDIO::EQ2_FREQ::Set(EQ2FreqValue value)
            {
                return fmt::format("EX{:02d}{:02d}{:02d}{:02d};",
                static_cast<int>(MenuGroup::OperationSetting),
                static_cast<int>(OperationSettingType::TX_Audio),
                static_cast<int>(TXAudioSettings::EQ2_FREQ),
                static_cast<int>(value));
            }

            std::string Menu::OperationSetting::TX_AUDIO::EQ2_FREQ::Read()
            {
                return fmt::format("EX{:02d}{:02d}{:02d};",
                static_cast<int>(MenuGroup::OperationSetting),
                static_cast<int>(OperationSettingType::TX_Audio),
                static_cast<int>(TXAudioSettings::EQ2_FREQ));
            }

            EQ2FreqValue Menu::OperationSetting::TX_AUDIO::EQ2_FREQ::Answer(std::string data)
            {
                return static_cast<EQ2FreqValue>(std::stoi(data.substr(8,2)));
            }

            std::string Menu::OperationSetting::TX_AUDIO::EQ2_LEVEL::Set(int value)
            {
                return fmt::format("EX{:02d}{:02d}{:02d}{:+03d};",
                static_cast<int>(MenuGroup::OperationSetting),
                static_cast<int>(OperationSettingType::TX_Audio),
                static_cast<int>(TXAudioSettings::EQ2_LEVEL),
                static_cast<int>(value));
            }

            std::string Menu::OperationSetting::TX_AUDIO::EQ2_LEVEL::Read()
            {
                return fmt::format("EX{:02d}{:02d}{:02d};",
                static_cast<int>(MenuGroup::OperationSetting),
                static_cast<int>(OperationSettingType::TX_Audio),
                static_cast<int>(TXAudioSettings::EQ2_LEVEL));
            }

            int Menu::OperationSetting::TX_AUDIO::EQ2_LEVEL::Answer(std::string data)
            {
                return std::stoi(data.substr(8,3));
            }

            std::string Menu::OperationSetting::TX_AUDIO::EQ2_BWTH::Set(int value)
            {
                return fmt::format("EX{:02d}{:02d}{:02d}{:02d};",
                static_cast<int>(MenuGroup::OperationSetting),
                static_cast<int>(OperationSettingType::TX_Audio),
                static_cast<int>(TXAudioSettings::EQ2_BWDTH),
                static_cast<int>(value));
            }

            std::string Menu::OperationSetting::TX_AUDIO::EQ2_BWTH::Read()
            {
                return fmt::format("EX{:02d}{:02d}{:02d};",
                static_cast<int>(MenuGroup::OperationSetting),
                static_cast<int>(OperationSettingType::TX_Audio),
                static_cast<int>(TXAudioSettings::EQ2_BWDTH));
            }

            int Menu::OperationSetting::TX_AUDIO::EQ2_BWTH::Answer(std::string data)
            {
                return std::stoi(data.substr(8,2));
            }

            std::string Menu::OperationSetting::TX_AUDIO::EQ3_FREQ::Set(EQ3FreqValue value)
            {
                return fmt::format("EX{:02d}{:02d}{:02d}{:02d};",
                static_cast<int>(MenuGroup::OperationSetting),
                static_cast<int>(OperationSettingType::TX_Audio),
                static_cast<int>(TXAudioSettings::EQ3_FREQ),
                static_cast<int>(value));
            }

            std::string Menu::OperationSetting::TX_AUDIO::EQ3_FREQ::Read()
            {
                return fmt::format("EX{:02d}{:02d}{:02d};",
                static_cast<int>(MenuGroup::OperationSetting),
                static_cast<int>(OperationSettingType::TX_Audio),
                static_cast<int>(TXAudioSettings::EQ3_FREQ));
            }

            EQ3FreqValue Menu::OperationSetting::TX_AUDIO::EQ3_FREQ::Answer(std::string data)
            {
                return static_cast<EQ3FreqValue>(std::stoi(data.substr(8,2)));
            }

            std::string Menu::OperationSetting::TX_AUDIO::EQ3_LEVEL::Set(int value)
            {
                return fmt::format("EX{:02d}{:02d}{:02d}{:+03d};",
                static_cast<int>(MenuGroup::OperationSetting),
                static_cast<int>(OperationSettingType::TX_Audio),
                static_cast<int>(TXAudioSettings::EQ3_LEVEL),
                static_cast<int>(value));
            }

            std::string Menu::OperationSetting::TX_AUDIO::EQ3_LEVEL::Read()
            {
                return fmt::format("EX{:02d}{:02d}{:02d};",
                static_cast<int>(MenuGroup::OperationSetting),
                static_cast<int>(OperationSettingType::TX_Audio),
                static_cast<int>(TXAudioSettings::EQ3_LEVEL));
            }

            int Menu::OperationSetting::TX_AUDIO::EQ3_LEVEL::Answer(std::string data)
            {
                return std::stoi(data.substr(8,3));
            }

            std::string Menu::OperationSetting::TX_AUDIO::EQ3_BWTH::Set(int value)
            {
                return fmt::format("EX{:02d}{:02d}{:02d}{:02d};",
                static_cast<int>(MenuGroup::OperationSetting),
                static_cast<int>(OperationSettingType::TX_Audio),
                static_cast<int>(TXAudioSettings::EQ3_BWDTH),
                static_cast<int>(value));
            }

            std::string Menu::OperationSetting::TX_AUDIO::EQ3_BWTH::Read()
            {
                return fmt::format("EX{:02d}{:02d}{:02d};",
                static_cast<int>(MenuGroup::OperationSetting),
                static_cast<int>(OperationSettingType::TX_Audio),
                static_cast<int>(TXAudioSettings::EQ3_BWDTH));
            }

            int Menu::OperationSetting::TX_AUDIO::EQ3_BWTH::Answer(std::string data)
            {
                return std::stoi(data.substr(8,2));
            }

            std::string Menu::OperationSetting::TX_AUDIO::PEQ1_FREQ::Set(EQ1FreqValue value)
            {
                return fmt::format("EX{:02d}{:02d}{:02d}{:02d};",
                static_cast<int>(MenuGroup::OperationSetting),
                static_cast<int>(OperationSettingType::TX_Audio),
                static_cast<int>(TXAudioSettings::PEQ1_FREQ),
                static_cast<int>(value));
            }

            std::string Menu::OperationSetting::TX_AUDIO::PEQ1_FREQ::Read()
            {
                return fmt::format("EX{:02d}{:02d}{:02d};",
                static_cast<int>(MenuGroup::OperationSetting),
                static_cast<int>(OperationSettingType::TX_Audio),
                static_cast<int>(TXAudioSettings::PEQ1_FREQ));
            }

            EQ1FreqValue Menu::OperationSetting::TX_AUDIO::PEQ1_FREQ::Answer(std::string data)
            {
                return static_cast<EQ1FreqValue>(std::stoi(data.substr(8,2)));
            }

            std::string Menu::OperationSetting::TX_AUDIO::PEQ1_LEVEL::Set(int value)
            {
                return fmt::format("EX{:02d}{:02d}{:02d}{:+03d};",
                static_cast<int>(MenuGroup::OperationSetting),
                static_cast<int>(OperationSettingType::TX_Audio),
                static_cast<int>(TXAudioSettings::PEQ1_LEVEL),
                static_cast<int>(value));
            }

            std::string Menu::OperationSetting::TX_AUDIO::PEQ1_LEVEL::Read()
            {
                return fmt::format("EX{:02d}{:02d}{:02d};",
                static_cast<int>(MenuGroup::OperationSetting),
                static_cast<int>(OperationSettingType::TX_Audio),
                static_cast<int>(TXAudioSettings::PEQ1_LEVEL));
            }

            int Menu::OperationSetting::TX_AUDIO::PEQ1_LEVEL::Answer(std::string data)
            {
                return std::stoi(data.substr(8,3));
            }

            std::string Menu::OperationSetting::TX_AUDIO::PEQ1_BWTH::Set(int value)
            {
                return fmt::format("EX{:02d}{:02d}{:02d}{:02d};",
                static_cast<int>(MenuGroup::OperationSetting),
                static_cast<int>(OperationSettingType::TX_Audio),
                static_cast<int>(TXAudioSettings::PEQ1_BWDTH),
                static_cast<int>(value));
            }

            std::string Menu::OperationSetting::TX_AUDIO::PEQ1_BWTH::Read()
            {
                return fmt::format("EX{:02d}{:02d}{:02d};",
                static_cast<int>(MenuGroup::OperationSetting),
                static_cast<int>(OperationSettingType::TX_Audio),
                static_cast<int>(TXAudioSettings::PEQ1_BWDTH));
            }

            int Menu::OperationSetting::TX_AUDIO::PEQ1_BWTH::Answer(std::string data)
            {
                return std::stoi(data.substr(8,2));
            }

            std::string Menu::OperationSetting::TX_AUDIO::PEQ2_FREQ::Set(EQ2FreqValue value)
            {
                return fmt::format("EX{:02d}{:02d}{:02d}{:02d};",
                static_cast<int>(MenuGroup::OperationSetting),
                static_cast<int>(OperationSettingType::TX_Audio),
                static_cast<int>(TXAudioSettings::PEQ2_FREQ),
                static_cast<int>(value));
            }

            std::string Menu::OperationSetting::TX_AUDIO::PEQ2_FREQ::Read()
            {
                return fmt::format("EX{:02d}{:02d}{:02d};",
                static_cast<int>(MenuGroup::OperationSetting),
                static_cast<int>(OperationSettingType::TX_Audio),
                static_cast<int>(TXAudioSettings::PEQ2_FREQ));
            }

            EQ2FreqValue Menu::OperationSetting::TX_AUDIO::PEQ2_FREQ::Answer(std::string data)
            {
                return static_cast<EQ2FreqValue>(std::stoi(data.substr(8,2)));
            }

            std::string Menu::OperationSetting::TX_AUDIO::PEQ2_LEVEL::Set(int value)
            {
                return fmt::format("EX{:02d}{:02d}{:02d}{:+03d};",
                static_cast<int>(MenuGroup::OperationSetting),
                static_cast<int>(OperationSettingType::TX_Audio),
                static_cast<int>(TXAudioSettings::PEQ2_LEVEL),
                static_cast<int>(value));
            }

            std::string Menu::OperationSetting::TX_AUDIO::PEQ2_LEVEL::Read()
            {
                return fmt::format("EX{:02d}{:02d}{:02d};",
                static_cast<int>(MenuGroup::OperationSetting),
                static_cast<int>(OperationSettingType::TX_Audio),
                static_cast<int>(TXAudioSettings::PEQ2_LEVEL));
            }

            int Menu::OperationSetting::TX_AUDIO::PEQ2_LEVEL::Answer(std::string data)
            {
                return std::stoi(data.substr(8,3));
            }

            std::string Menu::OperationSetting::TX_AUDIO::PEQ2_BWTH::Set(int value)
            {
                return fmt::format("EX{:02d}{:02d}{:02d}{:02d};",
                static_cast<int>(MenuGroup::OperationSetting),
                static_cast<int>(OperationSettingType::TX_Audio),
                static_cast<int>(TXAudioSettings::PEQ2_BWDTH),
                static_cast<int>(value));
            }

            std::string Menu::OperationSetting::TX_AUDIO::PEQ2_BWTH::Read()
            {
                return fmt::format("EX{:02d}{:02d}{:02d};",
                static_cast<int>(MenuGroup::OperationSetting),
                static_cast<int>(OperationSettingType::TX_Audio),
                static_cast<int>(TXAudioSettings::PEQ2_BWDTH));
            }

            int Menu::OperationSetting::TX_AUDIO::PEQ2_BWTH::Answer(std::string data)
            {
                return std::stoi(data.substr(8,2));
            }

            std::string Menu::OperationSetting::TX_AUDIO::PEQ3_FREQ::Set(EQ3FreqValue value)
            {
                return fmt::format("EX{:02d}{:02d}{:02d}{:02d};",
                static_cast<int>(MenuGroup::OperationSetting),
                static_cast<int>(OperationSettingType::TX_Audio),
                static_cast<int>(TXAudioSettings::PEQ3_FREQ),
                static_cast<int>(value));
            }

            std::string Menu::OperationSetting::TX_AUDIO::PEQ3_FREQ::Read()
            {
                return fmt::format("EX{:02d}{:02d}{:02d};",
                static_cast<int>(MenuGroup::OperationSetting),
                static_cast<int>(OperationSettingType::TX_Audio),
                static_cast<int>(TXAudioSettings::PEQ3_FREQ));
            }

            EQ3FreqValue Menu::OperationSetting::TX_AUDIO::PEQ3_FREQ::Answer(std::string data)
            {
                return static_cast<EQ3FreqValue>(std::stoi(data.substr(8,2)));
            }

            std::string Menu::OperationSetting::TX_AUDIO::PEQ3_LEVEL::Set(int value)
            {
                return fmt::format("EX{:02d}{:02d}{:02d}{:+03d};",
                static_cast<int>(MenuGroup::OperationSetting),
                static_cast<int>(OperationSettingType::TX_Audio),
                static_cast<int>(TXAudioSettings::PEQ3_LEVEL),
                static_cast<int>(value));
            }

            std::string Menu::OperationSetting::TX_AUDIO::PEQ3_LEVEL::Read()
            {
                return fmt::format("EX{:02d}{:02d}{:02d};",
                static_cast<int>(MenuGroup::OperationSetting),
                static_cast<int>(OperationSettingType::TX_Audio),
                static_cast<int>(TXAudioSettings::PEQ3_LEVEL));
            }

            int Menu::OperationSetting::TX_AUDIO::PEQ3_LEVEL::Answer(std::string data)
            {
                return std::stoi(data.substr(8,3));
            }

            std::string Menu::OperationSetting::TX_AUDIO::PEQ3_BWTH::Set(int value)
            {
                return fmt::format("EX{:02d}{:02d}{:02d}{:02d};",
                static_cast<int>(MenuGroup::OperationSetting),
                static_cast<int>(OperationSettingType::TX_Audio),
                static_cast<int>(TXAudioSettings::PEQ3_BWDTH),
                static_cast<int>(value));
            }

            std::string Menu::OperationSetting::TX_AUDIO::PEQ3_BWTH::Read()
            {
                return fmt::format("EX{:02d}{:02d}{:02d};",
                static_cast<int>(MenuGroup::OperationSetting),
                static_cast<int>(OperationSettingType::TX_Audio),
                static_cast<int>(TXAudioSettings::PEQ3_BWDTH));
            }

            int Menu::OperationSetting::TX_AUDIO::PEQ3_BWTH::Answer(std::string data)
            {
                return std::stoi(data.substr(8,2));
            }

            std::string Menu::OperationSetting::TX_GENERAL::MAX_POWER_HF::Set(int value)
            {
                return fmt::format("EX{:02d}{:02d}{:02d}{:03d};",
                static_cast<int>(MenuGroup::OperationSetting),
                static_cast<int>(OperationSettingType::TX_General),
                static_cast<int>(TXGeneralSettings::MAX_POWER_HF),
                static_cast<int>(value));
            }

            std::string Menu::OperationSetting::TX_GENERAL::MAX_POWER_HF::Read()
            {
                return fmt::format("EX{:02d}{:02d}{:02d};",
                static_cast<int>(MenuGroup::OperationSetting),
                static_cast<int>(OperationSettingType::TX_General),
                static_cast<int>(TXGeneralSettings::MAX_POWER_HF));
            }

            int Menu::OperationSetting::TX_GENERAL::MAX_POWER_HF::Answer(std::string data)
            {
                return std::stoi(data.substr(8,3));
            }

            std::string  Menu::OperationSetting::TX_GENERAL::MAX_POWER_50M::Set(int value)
            {
                return fmt::format("EX{:02d}{:02d}{:02d}{:03d};",
                static_cast<int>(MenuGroup::OperationSetting),
                static_cast<int>(OperationSettingType::TX_General),
                static_cast<int>(TXGeneralSettings::MAX_POWER_50M),
                static_cast<int>(value));
            }

            std::string  Menu::OperationSetting::TX_GENERAL::MAX_POWER_50M::Read()
            {
                return fmt::format("EX{:02d}{:02d}{:02d};",
                static_cast<int>(MenuGroup::OperationSetting),
                static_cast<int>(OperationSettingType::TX_General),
                static_cast<int>(TXGeneralSettings::MAX_POWER_50M));
            }

            int  Menu::OperationSetting::TX_GENERAL::MAX_POWER_50M::Answer(std::string data)
            {
                return std::stoi(data.substr(8,3));
            }

            std::string Menu::OperationSetting::TX_GENERAL::MAX_POWER_70M::Set(int value)
            {
                return fmt::format("EX{:02d}{:02d}{:02d}{:03d};",
                static_cast<int>(MenuGroup::OperationSetting),
                static_cast<int>(OperationSettingType::TX_General),
                static_cast<int>(TXGeneralSettings::MAX_POWER_70M),
                static_cast<int>(value));
            }

            std::string Menu::OperationSetting::TX_GENERAL::MAX_POWER_70M::Read()
            {
                return fmt::format("EX{:02d}{:02d}{:02d};",
                static_cast<int>(MenuGroup::OperationSetting),
                static_cast<int>(OperationSettingType::TX_General),
                static_cast<int>(TXGeneralSettings::MAX_POWER_70M));
            }

            int Menu::OperationSetting::TX_GENERAL::MAX_POWER_70M::Answer(std::string data)
            {
                return std::stoi(data.substr(8,3));
            }

            std::string Menu::OperationSetting::TX_GENERAL::MAX_POWER_AM::Set(int value)
            {
                return fmt::format("EX{:02d}{:02d}{:02d}{:03d};",
                static_cast<int>(MenuGroup::OperationSetting),
                static_cast<int>(OperationSettingType::TX_General),
                static_cast<int>(TXGeneralSettings::MAX_POWER_AM),
                static_cast<int>(value));
            }

            std::string Menu::OperationSetting::TX_GENERAL::MAX_POWER_AM::Read()
            {
                return fmt::format("EX{:02d}{:02d}{:02d};",
                static_cast<int>(MenuGroup::OperationSetting),
                static_cast<int>(OperationSettingType::TX_General),
                static_cast<int>(TXGeneralSettings::MAX_POWER_AM));
            }

            int Menu::OperationSetting::TX_GENERAL::MAX_POWER_AM::Answer(std::string data)
            {
                return std::stoi(data.substr(8,3));
            }

            std::string Menu::OperationSetting::TX_GENERAL::VOX_SELECT::Set(VoxSelectValue value)
            {
                return fmt::format("EX{:02d}{:02d}{:02d}{:01d};",
                static_cast<int>(MenuGroup::OperationSetting),
                static_cast<int>(OperationSettingType::TX_General),
                static_cast<int>(TXGeneralSettings::VOX_SELECT),
                static_cast<int>(value));
            }

            std::string Menu::OperationSetting::TX_GENERAL::VOX_SELECT::Read()
            {
                return fmt::format("EX{:02d}{:02d}{:02d};",
                static_cast<int>(MenuGroup::OperationSetting),
                static_cast<int>(OperationSettingType::TX_General),
                static_cast<int>(TXGeneralSettings::VOX_SELECT));
            }

            VoxSelectValue Menu::OperationSetting::TX_GENERAL::VOX_SELECT::Answer(std::string data)
            {
                return static_cast<VoxSelectValue>(std::stoi(data.substr(8,1)));
            }

            std::string Menu::OperationSetting::TX_GENERAL::DATA_VOX_GAIN::Set(int value)
            {
                return fmt::format("EX{:02d}{:02d}{:02d}{:03d};",
                static_cast<int>(MenuGroup::OperationSetting),
                static_cast<int>(OperationSettingType::TX_General),
                static_cast<int>(TXGeneralSettings::DATA_VOX_GAIN),
                static_cast<int>(value));
            }

            std::string Menu::OperationSetting::TX_GENERAL::DATA_VOX_GAIN::Read()
            {
                return fmt::format("EX{:02d}{:02d}{:02d};",
                static_cast<int>(MenuGroup::OperationSetting),
                static_cast<int>(OperationSettingType::TX_General),
                static_cast<int>(TXGeneralSettings::DATA_VOX_GAIN));
            }

            int Menu::OperationSetting::TX_GENERAL::DATA_VOX_GAIN::Answer(std::string data)
            {
                return std::stoi(data.substr(8,3));
            }

            std::string Menu::OperationSetting::TX_GENERAL::EMERGENCY_FREQ_TX::Set(EnableDisableValue value)
            {
                return fmt::format("EX{:02d}{:02d}{:02d}{:03d};",
                static_cast<int>(MenuGroup::OperationSetting),
                static_cast<int>(OperationSettingType::TX_General),
                static_cast<int>(TXGeneralSettings::EMERGENCY_FREQ_TX),
                static_cast<int>(value));
            }

            std::string Menu::OperationSetting::TX_GENERAL::EMERGENCY_FREQ_TX::Read()
            {
                return fmt::format("EX{:02d}{:02d}{:02d};",
                static_cast<int>(MenuGroup::OperationSetting),
                static_cast<int>(OperationSettingType::TX_General),
                static_cast<int>(TXGeneralSettings::EMERGENCY_FREQ_TX));
            }

            EnableDisableValue Menu::OperationSetting::TX_GENERAL::EMERGENCY_FREQ_TX::Answer(std::string data)
            {
                return static_cast<EnableDisableValue>(std::stoi(data.substr(8,1)));
            }

            std::string  Menu::OperationSetting::TUNING::SSB_CW_DIAL_STEP::Set(SSBDialStepValue value)
            {
                return fmt::format("EX{:02d}{:02d}{:02d}{:01d};",
                static_cast<int>(MenuGroup::OperationSetting),
                static_cast<int>(OperationSettingType::Tuning),
                static_cast<int>(TuningSettings::SSB_CW_DIAL_STEP),
                static_cast<int>(value));
            }

            std::string  Menu::OperationSetting::TUNING::SSB_CW_DIAL_STEP::Read()
            {
                return fmt::format("EX{:02d}{:02d}{:02d};",
                static_cast<int>(MenuGroup::OperationSetting),
                static_cast<int>(OperationSettingType::Tuning),
                static_cast<int>(TuningSettings::SSB_CW_DIAL_STEP));
            }

            SSBDialStepValue  Menu::OperationSetting::TUNING::SSB_CW_DIAL_STEP::Answer(std::string data)
            {
                return static_cast<SSBDialStepValue>(std::stoi(data.substr(8,1)));
            }

            std::string  Menu::OperationSetting::TUNING::RTTY_PSK_DIAL_STEP::Set(RTTYPSKDialStepValue value)
            {
                return fmt::format("EX{:02d}{:02d}{:02d}{:01d};",
                static_cast<int>(MenuGroup::OperationSetting),
                static_cast<int>(OperationSettingType::Tuning),
                static_cast<int>(TuningSettings::RTTY_PSK_DIAL_STEP),
                static_cast<int>(value));
            }

            std::string  Menu::OperationSetting::TUNING::RTTY_PSK_DIAL_STEP::Read()
            {
                return fmt::format("EX{:02d}{:02d}{:02d};",
                static_cast<int>(MenuGroup::OperationSetting),
                static_cast<int>(OperationSettingType::Tuning),
                static_cast<int>(TuningSettings::RTTY_PSK_DIAL_STEP));
            }

            RTTYPSKDialStepValue  Menu::OperationSetting::TUNING::RTTY_PSK_DIAL_STEP::Answer(std::string data)
            {
                return static_cast<RTTYPSKDialStepValue>(std::stoi(data.substr(8,1)));
            }

            std::string  Menu::OperationSetting::TUNING::CH_STEP::Set(CH_StepValue value)
            {
                return fmt::format("EX{:02d}{:02d}{:02d}{:01d};",
                static_cast<int>(MenuGroup::OperationSetting),
                static_cast<int>(OperationSettingType::Tuning),
                static_cast<int>(TuningSettings::CH_STEP),
                static_cast<int>(value));
            }

            std::string  Menu::OperationSetting::TUNING::CH_STEP::Read()
            {
                return fmt::format("EX{:02d}{:02d}{:02d};",
                static_cast<int>(MenuGroup::OperationSetting),
                static_cast<int>(OperationSettingType::Tuning),
                static_cast<int>(TuningSettings::CH_STEP));
            }

            CH_StepValue  Menu::OperationSetting::TUNING::CH_STEP::Answer(std::string data)
            {
                return static_cast<CH_StepValue>(std::stoi(data.substr(8,1)));
            }

            std::string  Menu::OperationSetting::TUNING::AM_CH_STEP::Set(AMCHStepValue value)
            {
                return fmt::format("EX{:02d}{:02d}{:02d}{:01d};",
                static_cast<int>(MenuGroup::OperationSetting),
                static_cast<int>(OperationSettingType::Tuning),
                static_cast<int>(TuningSettings::AM_CH_STEP),
                static_cast<int>(value));
            }

            std::string  Menu::OperationSetting::TUNING::AM_CH_STEP::Read()
            {
                return fmt::format("EX{:02d}{:02d}{:02d};",
                static_cast<int>(MenuGroup::OperationSetting),
                static_cast<int>(OperationSettingType::Tuning),
                static_cast<int>(TuningSettings::AM_CH_STEP));
            }

            AMCHStepValue  Menu::OperationSetting::TUNING::AM_CH_STEP::Answer(std::string data)
            {
                return static_cast<AMCHStepValue>(std::stoi(data.substr(8,1)));
            }

            std::string  Menu::OperationSetting::TUNING::FM_CH_STEP::Set(FMCHStepValue value)
            {
                return fmt::format("EX{:02d}{:02d}{:02d}{:01d};",
                static_cast<int>(MenuGroup::OperationSetting),
                static_cast<int>(OperationSettingType::Tuning),
                static_cast<int>(TuningSettings::FM_CH_STEP),
                static_cast<int>(value));
            }

            std::string  Menu::OperationSetting::TUNING::FM_CH_STEP::Read()
            {
                return fmt::format("EX{:02d}{:02d}{:02d};",
                static_cast<int>(MenuGroup::OperationSetting),
                static_cast<int>(OperationSettingType::Tuning),
                static_cast<int>(TuningSettings::FM_CH_STEP));
            }

            FMCHStepValue  Menu::OperationSetting::TUNING::FM_CH_STEP::Answer(std::string data)
            {
                return static_cast<FMCHStepValue>(std::stoi(data.substr(8,1)));
            }

            std::string  Menu::OperationSetting::TUNING::MAIN_STEPS_PER_REV::Set(MainStepsPerRev value)
            {
                return fmt::format("EX{:02d}{:02d}{:02d}{:01d};",
                static_cast<int>(MenuGroup::OperationSetting),
                static_cast<int>(OperationSettingType::Tuning),
                static_cast<int>(TuningSettings::MAIN_STEPS_PER_REV),
                static_cast<int>(value));
            }

            std::string  Menu::OperationSetting::TUNING::MAIN_STEPS_PER_REV::Read()
            {
                return fmt::format("EX{:02d}{:02d}{:02d};",
                static_cast<int>(MenuGroup::OperationSetting),
                static_cast<int>(OperationSettingType::Tuning),
                static_cast<int>(TuningSettings::MAIN_STEPS_PER_REV));
            }

            MainStepsPerRev  Menu::OperationSetting::TUNING::MAIN_STEPS_PER_REV::Answer(std::string data)
            {
                return static_cast<MainStepsPerRev>(std::stoi(data.substr(8,1)));
            }

            std::string  Menu::OperationSetting::TUNING::MPVD_STEPS_PRE_REV::Set(MPVDStepsPerRev value)
            {
                return fmt::format("EX{:02d}{:02d}{:02d}{:01d};",
                static_cast<int>(MenuGroup::OperationSetting),
                static_cast<int>(OperationSettingType::Tuning),
                static_cast<int>(TuningSettings::MPVD_STEPS_PER_REV),
                static_cast<int>(value));
            }

            std::string  Menu::OperationSetting::TUNING::MPVD_STEPS_PRE_REV::Read()
            {
                return fmt::format("EX{:02d}{:02d}{:02d};",
                static_cast<int>(MenuGroup::OperationSetting),
                static_cast<int>(OperationSettingType::Tuning),
                static_cast<int>(TuningSettings::MPVD_STEPS_PER_REV));
            }

            MPVDStepsPerRev  Menu::OperationSetting::TUNING::MPVD_STEPS_PRE_REV::Answer(std::string data)
            {
                return static_cast<MPVDStepsPerRev>(std::stoi(data.substr(8,1)));
            }

            std::string Menu::DisplaySetting::DISPLAY::MY_CALL::Set(std::string value)
            {
                value.append(value.length() - 12,' ');
                return fmt::format("EX{:02d}{:02d}{:02d}{};",
                static_cast<int>(MenuGroup::DisplaySetting),
                static_cast<int>(DisplaySettingType::Display),
                static_cast<int>(DisplaySettings::MY_CALL),
                value.substr(0,12));
            }

            std::string Menu::DisplaySetting::DISPLAY::MY_CALL::Read()
            {
                return fmt::format("EX{:02d}{:02d}{:02d};",
                static_cast<int>(MenuGroup::DisplaySetting),
                static_cast<int>(DisplaySettingType::Display),
                static_cast<int>(DisplaySettings::MY_CALL));
            }

            std::string Menu::DisplaySetting::DISPLAY::MY_CALL::Answer(std::string data)
            {
                    data = data.substr(8,12);
                    data.erase(std::ranges::find_if(data.rbegin(), data.rend(), [](unsigned char ch) {
                        return !std::isspace(ch);
                    }).base(), data.end());
                    data.erase(data.begin(), std::ranges::find_if(data.begin(), data.end(), [](unsigned char ch) {
                        return !std::isspace(ch);
                    }));
                return data;
            }

            std::string Menu::DisplaySetting::DISPLAY::MY_CALL_TIME::Set(CallSignTime value)
            {
                return fmt::format("EX{:02d}{:02d}{:02d}{:01d};",
                static_cast<int>(MenuGroup::DisplaySetting),
                static_cast<int>(DisplaySettingType::Display),
                static_cast<int>(DisplaySettings::MY_CALL_TIME),
                static_cast<int>(value));
            }

            std::string Menu::DisplaySetting::DISPLAY::MY_CALL_TIME::Read()
            {
                return fmt::format("EX{:02d}{:02d}{:02d};",
                static_cast<int>(MenuGroup::DisplaySetting),
                static_cast<int>(DisplaySettingType::Display),
                static_cast<int>(DisplaySettings::MY_CALL_TIME));
            }

            CallSignTime Menu::DisplaySetting::DISPLAY::MY_CALL_TIME::Answer(std::string data)
            {
                return static_cast<CallSignTime>(std::stoi(data.substr(8,1)));
            }

            std::string Menu::DisplaySetting::DISPLAY::SCREEN_SAVER::Set(ScreenSaverTime value)
            {
                return fmt::format("EX{:02d}{:02d}{:02d}{:01d};",
                static_cast<int>(MenuGroup::DisplaySetting),
                static_cast<int>(DisplaySettingType::Display),
                static_cast<int>(DisplaySettings::SCREEN_SAVER),
                static_cast<int>(value));
            }

            std::string Menu::DisplaySetting::DISPLAY::SCREEN_SAVER::Read()
            {
                return fmt::format("EX{:02d}{:02d}{:02d};",
                static_cast<int>(MenuGroup::DisplaySetting),
                static_cast<int>(DisplaySettingType::Display),
                static_cast<int>(DisplaySettings::SCREEN_SAVER));
            }

            ScreenSaverTime Menu::DisplaySetting::DISPLAY::SCREEN_SAVER::Answer(std::string data)
            {
                return static_cast<ScreenSaverTime>(std::stoi(data.substr(8,1)));
            }

            std::string Menu::DisplaySetting::DISPLAY::TFT_CONTRAST::Set(int value)
            {
                return fmt::format("EX{:02d}{:02d}{:02d}{:02d};",
                static_cast<int>(MenuGroup::DisplaySetting),
                static_cast<int>(DisplaySettingType::Display),
                static_cast<int>(DisplaySettings::TFT_CONTRAST),
                static_cast<int>(value));
            }

            std::string Menu::DisplaySetting::DISPLAY::TFT_CONTRAST::Read()
            {
                return fmt::format("EX{:02d}{:02d}{:02d};",
                static_cast<int>(MenuGroup::DisplaySetting),
                static_cast<int>(DisplaySettingType::Display),
                static_cast<int>(DisplaySettings::TFT_CONTRAST));
            }

            int Menu::DisplaySetting::DISPLAY::TFT_CONTRAST::Answer(std::string data)
            {
                return std::stoi(data.substr(8,2));
            }

            std::string Menu::DisplaySetting::DISPLAY::DIMMER_TFT::Set(int value)
            {
                return fmt::format("EX{:02d}{:02d}{:02d}{:02d};",
                static_cast<int>(MenuGroup::DisplaySetting),
                static_cast<int>(DisplaySettingType::Display),
                static_cast<int>(DisplaySettings::DIMMER_TFT),
                static_cast<int>(value));
            }

            std::string Menu::DisplaySetting::DISPLAY::DIMMER_TFT::Read()
            {
                return fmt::format("EX{:02d}{:02d}{:02d};",
                static_cast<int>(MenuGroup::DisplaySetting),
                static_cast<int>(DisplaySettingType::Display),
                static_cast<int>(DisplaySettings::DIMMER_TFT));
            }

            int Menu::DisplaySetting::DISPLAY::DIMMER_TFT::Answer(std::string data)
            {
                return std::stoi(data.substr(8,2));
            }

            std::string Menu::DisplaySetting::DISPLAY::DIMMER_LED::Set(int value)
            {
                return fmt::format("EX{:02d}{:02d}{:02d}{:02d};",
                static_cast<int>(MenuGroup::DisplaySetting),
                static_cast<int>(DisplaySettingType::Display),
                static_cast<int>(DisplaySettings::DIMMER_LED),
                static_cast<int>(value));
            }

            std::string Menu::DisplaySetting::DISPLAY::DIMMER_LED::Read()
            {
                return fmt::format("EX{:02d}{:02d}{:02d};",
                static_cast<int>(MenuGroup::DisplaySetting),
                static_cast<int>(DisplaySettingType::Display),
                static_cast<int>(DisplaySettings::DIMMER_LED));
            }

            int Menu::DisplaySetting::DISPLAY::DIMMER_LED::Answer(std::string data)
            {
                return std::stoi(data.substr(8,2));
            }

            std::string Menu::DisplaySetting::DISPLAY::MOUSE_POINTER_SPEED::Set(int value)
            {
                return fmt::format("EX{:02d}{:02d}{:02d}{:02d};",
                static_cast<int>(MenuGroup::DisplaySetting),
                static_cast<int>(DisplaySettingType::Display),
                static_cast<int>(DisplaySettings::MOUSE_POINTER_SPEED),
                static_cast<int>(value));
            }

            std::string Menu::DisplaySetting::DISPLAY::MOUSE_POINTER_SPEED::Read()
            {
                return fmt::format("EX{:02d}{:02d}{:02d};",
                static_cast<int>(MenuGroup::DisplaySetting),
                static_cast<int>(DisplaySettingType::Display),
                static_cast<int>(DisplaySettings::MOUSE_POINTER_SPEED));
            }

            int Menu::DisplaySetting::DISPLAY::MOUSE_POINTER_SPEED::Answer(std::string data)
            {
                return std::stoi(data.substr(8,2));
            }

            std::string Menu::DisplaySetting::DISPLAY::FREQ_STYLE::Set(FREQ_STYLEValue value)
            {
                return fmt::format("EX{:02d}{:02d}{:02d}{:01d};",
                static_cast<int>(MenuGroup::DisplaySetting),
                static_cast<int>(DisplaySettingType::Display),
                static_cast<int>(DisplaySettings::FREQ_STYLE),
                static_cast<int>(value));
            }

            std::string Menu::DisplaySetting::DISPLAY::FREQ_STYLE::Read()
            {
                return fmt::format("EX{:02d}{:02d}{:02d};",
                static_cast<int>(MenuGroup::DisplaySetting),
                static_cast<int>(DisplaySettingType::Display),
                static_cast<int>(DisplaySettings::FREQ_STYLE));
            }

            FREQ_STYLEValue Menu::DisplaySetting::DISPLAY::FREQ_STYLE::Answer(std::string data)
            {
                return static_cast<FREQ_STYLEValue>(std::stoi(data.substr(8,1)));
            }

            std::string Menu::DisplaySetting::SCOPE::RBW::Set(RBWValue value)
            {
                return fmt::format("EX{:02d}{:02d}{:02d}{:01d};",
                static_cast<int>(MenuGroup::DisplaySetting),
                static_cast<int>(DisplaySettingType::Scope),
                static_cast<int>(ScopeSettings::RBW),
                static_cast<int>(value));
            }

            std::string Menu::DisplaySetting::SCOPE::RBW::Read()
            {
                return fmt::format("EX{:02d}{:02d}{:02d};",
                static_cast<int>(MenuGroup::DisplaySetting),
                static_cast<int>(DisplaySettingType::Scope),
                static_cast<int>(ScopeSettings::RBW));
            }

            RBWValue Menu::DisplaySetting::SCOPE::RBW::Answer(std::string data)
            {
                return static_cast<RBWValue>(std::stoi(data.substr(8,1)));
            }

            std::string Menu::DisplaySetting::SCOPE::SCOPE_CTR::Set(ScopeCTRValue value)
            {
                return fmt::format("EX{:02d}{:02d}{:02d}{:01d};",
                static_cast<int>(MenuGroup::DisplaySetting),
                static_cast<int>(DisplaySettingType::Scope),
                static_cast<int>(ScopeSettings::SCOPE_CTR),
                static_cast<int>(value));
            }

            std::string Menu::DisplaySetting::SCOPE::SCOPE_CTR::Read()
            {
                return fmt::format("EX{:02d}{:02d}{:02d};",
                static_cast<int>(MenuGroup::DisplaySetting),
                static_cast<int>(DisplaySettingType::Scope),
                static_cast<int>(ScopeSettings::SCOPE_CTR));
            }

            ScopeCTRValue Menu::DisplaySetting::SCOPE::SCOPE_CTR::Answer(std::string data)
            {
                    return static_cast<ScopeCTRValue>(std::stoi(data.substr(8,1)));
            }

            std::string Menu::DisplaySetting::SCOPE::DISP_SENSITIVITY_2D::Set(ScopeSensitivityValue value)
            {
                return fmt::format("EX{:02d}{:02d}{:02d}{:01d};",
                static_cast<int>(MenuGroup::DisplaySetting),
                static_cast<int>(DisplaySettingType::Scope),
                static_cast<int>(ScopeSettings::DISP_SENSISITIVITY_2D),
                static_cast<int>(value));
            }

            std::string Menu::DisplaySetting::SCOPE::DISP_SENSITIVITY_2D::Read()
            {
                return fmt::format("EX{:02d}{:02d}{:02d};",
                static_cast<int>(MenuGroup::DisplaySetting),
                static_cast<int>(DisplaySettingType::Scope),
                static_cast<int>(ScopeSettings::DISP_SENSISITIVITY_2D));
            }

            ScopeSensitivityValue Menu::DisplaySetting::SCOPE::DISP_SENSITIVITY_2D::Answer(std::string data)
            {
                return static_cast<ScopeSensitivityValue>(std::stoi(data.substr(8,1)));
            }

            std::string Menu::DisplaySetting::SCOPE::DISP_SENSITIVITY_3DSS::Set(ScopeSensitivityValue value)
            {
                return fmt::format("EX{:02d}{:02d}{:02d}{:01d};",
                static_cast<int>(MenuGroup::DisplaySetting),
                static_cast<int>(DisplaySettingType::Scope),
                static_cast<int>(ScopeSettings::DISP_SENSISITIVITY_3DSS),
                static_cast<int>(value));
            }

            std::string Menu::DisplaySetting::SCOPE::DISP_SENSITIVITY_3DSS::Read()
            {
                return fmt::format("EX{:02d}{:02d}{:02d};",
                static_cast<int>(MenuGroup::DisplaySetting),
                static_cast<int>(DisplaySettingType::Scope),
                static_cast<int>(ScopeSettings::DISP_SENSISITIVITY_3DSS));
            }

            ScopeSensitivityValue Menu::DisplaySetting::SCOPE::DISP_SENSITIVITY_3DSS::Answer(std::string data)
            {
                return static_cast<ScopeSensitivityValue>(std::stoi(data.substr(8,1)));
            }


            std::string Menu::DisplaySetting::EXT_MONITOR::EXT_DISPLAY::Set(EnableDisableValue value)
            {
                return fmt::format("EX{:02d}{:02d}{:02d}{:01d};",
                static_cast<int>(MenuGroup::DisplaySetting),
                static_cast<int>(DisplaySettingType::Ext_Monitor),
                static_cast<int>(EXT_MonitorSettings::EXT_DISPLAY),
                static_cast<int>(value));
            }

            std::string Menu::DisplaySetting::EXT_MONITOR::EXT_DISPLAY::Read()
            {
                return fmt::format("EX{:02d}{:02d}{:02d};",
                static_cast<int>(MenuGroup::DisplaySetting),
                static_cast<int>(DisplaySettingType::Ext_Monitor),
                static_cast<int>(EXT_MonitorSettings::EXT_DISPLAY));
            }

            EnableDisableValue Menu::DisplaySetting::EXT_MONITOR::EXT_DISPLAY::Answer(std::string data)
            {
                return static_cast<EnableDisableValue>(std::stoi(data.substr(8,1)));
            }

            std::string Menu::DisplaySetting::EXT_MONITOR::PIXEL::Set(PixelValue value)
            {
                return fmt::format("EX{:02d}{:02d}{:02d}{:01d};",
                static_cast<int>(MenuGroup::DisplaySetting),
                static_cast<int>(DisplaySettingType::Ext_Monitor),
                static_cast<int>(EXT_MonitorSettings::PIXEL),
                static_cast<int>(value));
            }

            std::string Menu::DisplaySetting::EXT_MONITOR::PIXEL::Read()
            {
                return fmt::format("EX{:02d}{:02d}{:02d};",
                static_cast<int>(MenuGroup::DisplaySetting),
                static_cast<int>(DisplaySettingType::Ext_Monitor),
                static_cast<int>(EXT_MonitorSettings::PIXEL));
            }

            PixelValue Menu::DisplaySetting::EXT_MONITOR::PIXEL::Answer(std::string data)
            {
                return static_cast<PixelValue>(std::stoi(data.substr(8,1)));
            }

            std::string Frequency_Main::Set(int value)
            {
                return fmt::format("FA{:09d};", value);
            }

            std::string Frequency_Main::Read()
            {
                return "FA;";
            }

            int Frequency_Main::Answer(std::string data)
            {
                return std::stoi(data.substr(2,9));
            }


            std::string Frequency_Sub::Set(int value)
            {
                return fmt::format("FB{:09d};", value);
            }

            std::string Frequency_Sub::Read()
            {
                return "FB;";
            }

            int Frequency_Sub::Answer(std::string data)
            {
                return std::stoi(data.substr(2,9));
            }

            std::string FineTuning::Set(OnOffValue value)
            {
                return fmt::format("FN{:01d}", static_cast<int>(value));
            }

            std::string FineTuning::Read()
            {
                return "FN;";
            }

            OnOffValue FineTuning::Answer(std::string data)
            {
                return static_cast<OnOffValue>(std::stoi(data.substr(3,1)));
            }

            std::string FunctionRX::Set(FunctionRXValue value)
            {
                return fmt::format("FR{:1d}{:1d};", static_cast<int>(value.Main),
                static_cast<int>( value.Sub));
            }

            std::string FunctionRX::Set(RXValue main, RXValue sub)
            {
                return fmt::format("FR{:1d}{:1d};", static_cast<int>(main),
                static_cast<int>(sub));
            }


            std::string FunctionRX::Read()
            {
                return "FR;";
            }

            FunctionRXValue FunctionRX::Answer(std::string data)
            {
                FunctionRXValue ret;
                ret.Main = static_cast<RXValue>(std::stoi(data.substr(2,1)));
                ret.Sub = static_cast<RXValue>(std::stoi(data.substr(3,1)));
                return ret;
            }

            std::string FastStep::Set(FastStepState value)
            {
                return fmt::format("FS{:1d};",static_cast<int>(value));
            }

            std::string FastStep::Read()
            {
                return "FS;";
            }

            FastStepState FastStep::Answer(std::string data)
            {
                return static_cast<FastStepState>(std::stoi(data.substr(2,1)));
            }

            std::string AGCFunction::Set(AGCSetFunction value)
            {
                return fmt::format("GT{:1d}{:1d};",static_cast<int>(value.Band),
                static_cast<int>(value.Value));
            }

            std::string AGCFunction::Read(MainSubValue Band)
            {
                return fmt::format("GT{:1d};", static_cast<int>(Band));
            }

            AGCState AGCFunction::Answer(std::string data)
            {
                AGCState ret;
                ret.Band = static_cast<MainSubValue>(std::stoi(data.substr(2,1)));
                ret.Value = static_cast<AGCStateValue>(std::stoi(data.substr(3,1)));
                return ret;
            }


            std::string IDENTIFICATION::Read()
            {
                return "ID;";
            }

            Yaesu::RigType IDENTIFICATION::Answer(std::string data)
            {
                return static_cast<Yaesu::RigType>(std::stoi(data.substr(2,4)));
            }

            std::string INFORMATION::Read()
            {
                return "IF;";
            }

            InformationValue INFORMATION::Answer(std::string data)
            {
                InformationValue ret;
                ret.MemoryChannel = static_cast<MemoryChannelValue>(std::stoi(data.substr(2,3)));
                ret.VFOAFreq = std::stoi(data.substr(5,9));
                ret.ClarifierFreq = std::stoi(data.substr(14,5));
                ret.RxClarifier = static_cast<ClarifierState>(std::stoi(data.substr(19,1)));
                ret.TxClarifier = static_cast<ClarifierState>(std::stoi(data.substr(20,1)));
                ret.Mode = static_cast<ModeValue>(std::stoi(data.substr(21,1),0,16));
                ret.VFO = static_cast<VFOChannelTypeValue>(std::stoi(data.substr(22,1)));
                ret.CTCSS = static_cast<CTCSSState>(std::stoi(data.substr(23,1)));
                ret.Operation = static_cast<OperationType>(std::stoi(data.substr(26,1)));
                return ret;
            }


            std::string IF_SHIFT::Set(IFShiftValue value)
            {
                return fmt::format("IS{:1d}0{:+05d};", static_cast<int>(value.Band),
                value.Value);
            }

            std::string IF_SHIFT::Set(MainSubValue Band, int value)
            {

                return fmt::format("IS{:1d}0{:+05d};", static_cast<int>(Band),
                value);
            }

            std::string IF_SHIFT::Read()
            {
                return "IS;";
            }

            IFShiftValue IF_SHIFT::Answer(std::string data)
            {
                IFShiftValue ret;
                ret.Band = static_cast<MainSubValue>(std::stoi(data.substr(2,1)));
                ret.Value = std::stoi(data.substr(4,5));
                return ret;
            }

            std::string KEYER_MEMORY::Set(KeyerMemoryValue value)
            {
                return fmt::format("KM{:01d}{};", value.ChannelNumber, value.Message.substr(0, 50));
            }

            std::string KEYER_MEMORY::Read(int ChannelNum)
            {
                return fmt::format("KM{:01d};", ChannelNum);
            }

            KeyerMemoryValue KEYER_MEMORY::Answer(std::string data)
            {
                KeyerMemoryValue ret;
                ret.ChannelNumber = std::stoi(data.substr(2,1));
                ret.Message = data.substr(3, data.length() - 4);
                return ret;
            }

            std::string KeyPitch::Set(KeyPitchValue value)
            {
                return fmt::format("KP{:02d};", static_cast<int>(value));
            }

            std::string KeyPitch::Read()
            {
                return "KP;";
            }

            KeyPitchValue KeyPitch::Answer(std::string data)
            {
                return static_cast<KeyPitchValue>(std::stoi(data.substr(2,2)));
            }

            std::string Keyer::Set(OnOffValue value)
            {
                return fmt::format("KR{:01d};", static_cast<int>(value));
            }

            std::string Keyer::Read()
            {
                return "KR;";
            }

            OnOffValue Keyer::Answer(std::string data)
            {
                return static_cast<OnOffValue>(std::stoi(data.substr(2,1)));
            }

            std::string KeySpeed::Set(KeyerSpeedVal value)
            {
                return fmt::format("KS{:03d};",static_cast<int>(value));
            }

            std::string KeySpeed::Read()
            {
                return "KS;";
            }

            KeyerSpeedVal KeySpeed::Answer(std::string data)
            {
                return static_cast<KeyerSpeedVal>(std::stoi(data.substr(2,3)));

            }

            std::string CW_Keying::Set(KeyerMemoryChannel value)
            {
                return fmt::format("KY{:1d};", static_cast<int>(value));
            }

            std::string Lock::Set(LockType value)
            {
                return fmt::format("LK{:1d};",static_cast<int>(value));
            }

            std::string Lock::Read()
            {
                return "LK;";
            }

            LockType Lock::Answer(std::string data)
            {
                return static_cast<LockType>(std::stoi(data.substr(2,1)));
            }

            std::string LoadMessage::Set(LoadMessageChannel value)
            {
                return fmt::format("LM0{:1d};", static_cast<int>(value));
            }

            std::string LoadMessage::Read()
            {
                return "LM0;";
            }

            LoadMessageChannel LoadMessage::Answer(std::string data)
            {
                return static_cast<LoadMessageChannel>(std::stoi(data.substr(3,1)));
            }

            std::string MemoryChannelToMain::Set()
            {
                return "MA;";
            }
            std::string MemoryChannelToSub::Set()
            {
                return "MB;";
            }

            std::string MemoryChannelSelection::Set(MemoryChannelValue value)
            {

                switch(value)
                {
                    case MemoryChannelValue::P1L:
                        return "MCP1L;";
                    case MemoryChannelValue::P1U:
                        return "MCP1U;";
                    case MemoryChannelValue::P2L:
                        return "MCP2L;";
                    case MemoryChannelValue::P2U:
                        return "MCP2U;";
                    case MemoryChannelValue::P3L:
                        return "MCP3L;";
                    case MemoryChannelValue::P3U:
                        return "MCP3U;";
                    case MemoryChannelValue::P4L:
                        return "MCP4L;";
                    case MemoryChannelValue::P4U:
                        return "MCP4U;";
                    case MemoryChannelValue::P5L:
                        return "MCP5L;";
                    case MemoryChannelValue::P5U:
                        return "MCP5U;";
                    case MemoryChannelValue::P6L:
                        return "MCP6L;";
                    case MemoryChannelValue::P6U:
                        return "MCP6U;";
                    case MemoryChannelValue::P7L:
                        return "MCP7L;";
                    case MemoryChannelValue::P7U:
                        return "MCP7U;";
                    case MemoryChannelValue::P8L:
                        return "MCP8L;";
                    case MemoryChannelValue::P8U:
                        return "MCP8U;";
                    case MemoryChannelValue::P9L:
                        return "MCP9L;";
                    case MemoryChannelValue::P9U:
                        return "MCP9U;";
                    case MemoryChannelValue::EMG:
                        return "MCEMG;";
                    default:
                        return fmt::format("MC{:03};", static_cast<int>(value));
                }


            }

            std::string MemoryChannelSelection::Read()
            {
                return "MC;";
            }

            MemoryChannelValue MemoryChannelSelection::Answer(std::string data)
            {
                MemoryChannelValue ret = MemoryChannelValue::_1;
                std::string memVal = data.substr(2, 3);
                if (memVal == "EMG") {
                    ret = MemoryChannelValue::EMG;
                }
                else if (memVal[0] == 'P') {
                    bool upper = (memVal[2] == 'U');
                    switch (std::stoi(memVal.substr(1, 1)))
                    {
                    case 1:
                        if (upper)
                        {
                            ret = MemoryChannelValue::P1U;
                        }
                        else
                        {
                            ret = MemoryChannelValue::P1L;
                        }
                        break;
                    case 2:
                        if (upper)
                        {
                            ret = MemoryChannelValue::P2U;
                        }
                        else
                        {
                            ret = MemoryChannelValue::P2L;
                        }
                        break;
                    case 3:
                        if (upper)
                        {
                            ret = MemoryChannelValue::P3U;
                        }
                        else
                        {
                            ret = MemoryChannelValue::P3L;
                        }
                        break;
                    case 4:
                        if (upper)
                        {
                            ret = MemoryChannelValue::P4U;
                        }
                        else
                        {
                            ret = MemoryChannelValue::P4L;
                        }
                        break;
                    case 5:
                        if (upper)
                        {
                            ret = MemoryChannelValue::P5U;
                        }
                        else
                        {
                            ret = MemoryChannelValue::P5L;
                        }
                        break;
                    case 6:
                        if (upper)
                        {
                            ret = MemoryChannelValue::P6U;
                        }
                        else
                        {
                            ret = MemoryChannelValue::P6L;
                        }
                        break;
                    case 7:
                        if (upper)
                        {
                            ret = MemoryChannelValue::P7U;
                        }
                        else
                        {
                            ret = MemoryChannelValue::P7L;
                        }
                        break;
                    case 8:
                        if (upper)
                        {
                            ret = MemoryChannelValue::P8U;
                        }
                        else
                        {
                            ret = MemoryChannelValue::P8L;
                        }
                        break;
                    case 9:
                        if (upper)
                        {
                            ret = MemoryChannelValue::P9U;
                        }
                        else
                        {
                            ret = MemoryChannelValue::P9L;
                        }
                        break;
                    }
                }
                else {
                    ret = (MemoryChannelValue)std::stoi(memVal);
                }
                return ret;
            }


            std::string OperatingMode::Set(ModeSettingValue value)
            {
                return fmt::format("MD{:1d}{:1d};",
                    static_cast<int>(value.Band),
                    static_cast<int>(value.Mode));
            }
            std::string OperatingMode::Set(MainSubValue Band, ModeValue Mode)
            {
                return fmt::format("MD{:1d}{:1d};",
                    static_cast<int>(Band),
                    static_cast<int>(Mode));
            }

            std::string OperatingMode::Read(MainSubValue Band)
            {
                return fmt::format("MD{:1d};", static_cast<int>(Band));
            }

            ModeSettingValue OperatingMode::Answer(std::string data)
            {
                ModeSettingValue ret;
                ret.Mode = static_cast<ModeValue>(std::stoi(data.substr(3,1),0,16));
                ret.Band = static_cast<MainSubValue>(std::stoi(data.substr(2,1)));
                return ret;
            }

            std::string MicGain::Set(int value)
            {
                return fmt::format("MG{:3d};", value);
            }

            std::string MicGain::Read()
            {
                return "MG;";
            }

            int MicGain::Answer(std::string data)
            {
                return std::stoi(data.substr(2,3));
            }

            std::string MonitorLevel::Set(MonitorLevelValue value)
            {
                return fmt::format("ML{:1d}{:3d};",
                    static_cast<int>(value.Type),
                    (value.Type == MonitorRequestType::MONITOR_ONOFF ? static_cast<int>(value.Value.eValue) : value.Value.iValue ));
            }

            std::string MonitorLevel::Read(MonitorRequestType value)
            {
                return fmt::format("ML{:1d};", static_cast<int>(value));
            }


            MonitorLevelValue MonitorLevel::Answer(std::string data)
            {
                MonitorLevelValue ret;
                ret.Type = static_cast<MonitorRequestType>(std::stoi(data.substr(2,1)));
                if(ret.Type == MonitorRequestType::MONITOR_ONOFF)
                {
                    ret.Value.eValue = static_cast<OnOffValue>(std::stoi(data.substr(3,3)));
                }
                else
                {
                    ret.Value.iValue = std::stoi(data.substr(3,3));
                }
                return ret;
            }

            std::string MemoryChannel::Set(MemoryChannelReadValue channel)
            {
                return fmt::format("MW{:3d}{:9d}{:5d}{:1d}{:1d}{:1d}0{:1d}00{:1d};",
                static_cast<int>(channel.MemoryChannel),
                channel.VFOAFreq,
                channel.ClarifierFreq,
                static_cast<int>(channel.RIT),
                static_cast<int>(channel.XIT),
                static_cast<int>(channel.Mode),
                static_cast<int>(channel.CTCSS),
                static_cast<int>(channel.Operation)
                );
            }

            std::string MemoryChannel::Read(MemoryChannelValue channel)
            {
                return fmt::format("MR{:3d};", static_cast<int>(channel));
            }

            MemoryChannelReadValue MemoryChannel::Answer(std::string data)
            {
                MemoryChannelReadValue ret;
                ret.MemoryChannel = static_cast<MemoryChannelValue>(std::stoi(data.substr(2,3)));
                ret.VFOAFreq = std::stoi(data.substr(5,9));
                ret.ClarifierFreq = std::stoi(data.substr(14,5));
                ret.RIT = static_cast<OnOffValue>(std::stoi(data.substr(19,1)));
                ret.XIT = static_cast<OnOffValue>(std::stoi(data.substr(20,1)));
                ret.Mode = static_cast<ModeValue>(std::stoi(data.substr(21,1), 0, 16));
                ret.ChannelType = static_cast<VFOChannelTypeValue>(std::stoi(data.substr(22,1)));
                ret.CTCSS = static_cast<CTCSSState>(std::stoi(data.substr(23,1)));
                ret.Operation = static_cast<OperationType>(std::stoi(data.substr(26,1)));
                return ret;
            }

            std::string MeterSW::Set(MeterTypeValue value)
            {
                return fmt::format("MS{:1d}{:1d};",
                    static_cast<int>(value.Main),
                    static_cast<int>(value.Sub));
            }

            std::string MeterSW::Read()
            {
                return "MS;";
            }

            MeterTypeValue MeterSW::Answer(std::string data)
            {
                MeterTypeValue ret;
                ret.Main = static_cast<MainMeterType>(std::stoi(data.substr(2,1)));
                ret.Sub = static_cast<SubMeterType>(std::stoi(data.substr(3,1)));
                return ret;
            }

            std::string MemoryChannelTag::Set(MemoryChannelTagValue value)
            {
                value.Tag = value.Tag.substr(0,12);
                while(value.Tag.length() < 12)
                {
                    value.Tag.push_back(' ');
                }
                return fmt::format("MT{:3d}{:9d}{:5d}{:1d}{:1d}{:1d}0{:1d}00{:1d}0{};",
                static_cast<int>(value.MemoryChannel),
                value.VFOAFreq,
                value.ClarifierFreq,
                static_cast<int>(value.RIT),
                static_cast<int>(value.XIT),
                static_cast<int>(value.Mode),
                static_cast<int>(value.CTCSS),
                static_cast<int>(value.Operation),
                value.Tag);

            }

            std::string MemoryChannelTag::Read(MemoryChannelValue channel)
            {
                switch(channel)
                {
                    case MemoryChannelValue::P1L:
                        return "MTP1L;";
                    case MemoryChannelValue::P1U:
                        return "MTP1U;";
                    case MemoryChannelValue::P2L:
                        return "MTP2L;";
                    case MemoryChannelValue::P2U:
                        return "MTP2U;";
                    case MemoryChannelValue::P3L:
                        return "MTP3L;";
                    case MemoryChannelValue::P3U:
                        return "MTP3U;";
                    case MemoryChannelValue::P4L:
                        return "MTP4L;";
                    case MemoryChannelValue::P4U:
                        return "MTP4U;";
                    case MemoryChannelValue::P5L:
                        return "MTP5L;";
                    case MemoryChannelValue::P5U:
                        return "MTP5U;";
                    case MemoryChannelValue::P6L:
                        return "MTP6L;";
                    case MemoryChannelValue::P6U:
                        return "MTP6U;";
                    case MemoryChannelValue::P7L:
                        return "MTP7L;";
                    case MemoryChannelValue::P7U:
                        return "MTP7U;";
                    case MemoryChannelValue::P8L:
                        return "MTP8L;";
                    case MemoryChannelValue::P8U:
                        return "MTP8U;";
                    case MemoryChannelValue::P9L:
                        return "MTP9L;";
                    case MemoryChannelValue::P9U:
                        return "MTP9U;";
                    case MemoryChannelValue::EMG:
                        return "MTEMG;";
                    default:
                        return fmt::format("MT{:3d};", static_cast<int>(channel));
                }


            }

            MemoryChannelTagValue MemoryChannelTag::Answer(std::string data)
            {
                MemoryChannelTagValue ret;
                std::string channelStr = data.substr(2,3);
                if(channelStr[0] == 'P')
                {
                    switch(std::stoi(channelStr.substr(1,1)))
                    {
                        case 1:
                            if(channelStr[2] == 'L')
                                ret.MemoryChannel = MemoryChannelValue::P1L;
                            else
                                ret.MemoryChannel = MemoryChannelValue::P1U;
                        break;
                        case 2:
                            if(channelStr[2] == 'L')
                                ret.MemoryChannel = MemoryChannelValue::P2L;
                            else
                                ret.MemoryChannel = MemoryChannelValue::P2U;
                        break;
                        case 3:
                            if(channelStr[2] == 'L')
                                ret.MemoryChannel = MemoryChannelValue::P3L;
                            else
                                ret.MemoryChannel = MemoryChannelValue::P3U;
                        break;
                        case 4:
                            if(channelStr[2] == 'L')
                                ret.MemoryChannel = MemoryChannelValue::P4L;
                            else
                                ret.MemoryChannel = MemoryChannelValue::P4U;
                        break;
                        case 5:
                            if(channelStr[2] == 'L')
                                ret.MemoryChannel = MemoryChannelValue::P5L;
                            else
                                ret.MemoryChannel = MemoryChannelValue::P5U;
                        break;
                        case 6:
                            if(channelStr[2] == 'L')
                                ret.MemoryChannel = MemoryChannelValue::P6L;
                            else
                                ret.MemoryChannel = MemoryChannelValue::P6U;
                        break;
                        case 7:
                            if(channelStr[2] == 'L')
                                ret.MemoryChannel = MemoryChannelValue::P7L;
                            else
                                ret.MemoryChannel = MemoryChannelValue::P7U;
                        break;
                        case 8:
                            if(channelStr[2] == 'L')
                                ret.MemoryChannel = MemoryChannelValue::P8L;
                            else
                                ret.MemoryChannel = MemoryChannelValue::P8U;
                        break;
                        case 9:
                            if(channelStr[2] == 'L')
                                ret.MemoryChannel = MemoryChannelValue::P9L;
                            else
                                ret.MemoryChannel = MemoryChannelValue::P9U;
                        break;
                    }
                }
                else if(channelStr[0] == 'E')
                {
                    ret.MemoryChannel = MemoryChannelValue::EMG;
                }
                else
                {
                    ret.MemoryChannel = static_cast<MemoryChannelValue>(std::stoi(channelStr));
                }

                ret.VFOAFreq = std::stoi(data.substr(5,9));
                ret.ClarifierFreq = std::stoi(data.substr(14,5));
                ret.RIT = static_cast<OnOffValue>(std::stoi(data.substr(19,1)));
                ret.XIT = static_cast<OnOffValue>(std::stoi(data.substr(20,1)));
                ret.Mode = static_cast<ModeValue>(std::stoi(data.substr(21,1)));
                ret.ChannelType = static_cast<VFOChannelTypeValue>(std::stoi(data.substr(22,1)));
                ret.CTCSS = static_cast<CTCSSState>(std::stoi(data.substr(23,1)));
                ret.Operation = static_cast<OperationType>(std::stoi(data.substr(26,1)));
                ret.Tag = data.substr(28,12);
                return ret;
            }

            std::string Mox::Set(OnOffValue value)
            {
                return fmt::format("MX{:1d};", static_cast<int>(value));
            }

            std::string Mox::Read()
            {
                return "MX;";
            }

            OnOffValue Mox::Answer(std::string data)
            {
                return static_cast<OnOffValue>(std::stoi(data.substr(2,1)));
            }

            std::string Narrow::Set(NarrowValue value)
            {
                return fmt::format("MA{:1d}{:1d};",
                static_cast<int>(value.Band),
                static_cast<int>(value.State));
            }

            std::string Narrow::Read(MainSubValue band)
            {
                return fmt::format("MA{:01};",
                static_cast<int>(band));
            }

            NarrowValue Narrow::Answer(std::string data)
            {
                NarrowValue ret;
                ret.Band = static_cast<MainSubValue>(std::stoi(data.substr(2,1)));
                ret.State = static_cast<OnOffValue>(std::stoi(data.substr(3,1)));
                return ret;
            }

            std::string NoiseBlanker::Set(NoiseBlankerValue value)
            {
                return fmt::format("NB{:1d}{:1d};",
                static_cast<int>(value.Band),
                static_cast<int>(value.State));
            }

            std::string NoiseBlanker::Read(MainSubValue band)
            {
                return fmt::format("NB{:01};",
                static_cast<int>(band));
            }

            NoiseBlankerValue NoiseBlanker::Answer(std::string data)
            {
                NoiseBlankerValue ret;
                ret.Band = static_cast<MainSubValue>(std::stoi(data.substr(2,1)));
                ret.State = static_cast<OnOffValue>(std::stoi(data.substr(3,1)));
                return ret;
            }

            std::string NoiseBlankerLevel::Set(int value)
            {
                return fmt::format("NL0{:3d};", value);
            }

            std::string NoiseBlankerLevel::Read()
            {
                return "NL0;";
            }

            int NoiseBlankerLevel::Answer(std::string data)
            {
                return std::stoi(data.substr(3,3));
            }

            std::string NoiseReduction::Set(NoiseReductionValue value)
            {
                return fmt::format("NR{:1d}{:1d};",
                static_cast<int>(value.Band),
                static_cast<int>(value.State));
            }

            std::string NoiseReduction::Read(MainSubValue band)
            {
                return fmt::format("NR{:1d};", static_cast<int>(band));
            }

            NoiseReductionValue NoiseReduction::Answer(std::string data)
            {
                NoiseReductionValue ret;
                ret.Band = static_cast<MainSubValue>(std::stoi(data.substr(2,1)));
                ret.State = static_cast<OnOffValue>(std::stoi(data.substr(3,1)));
                return ret;
            }


            std::string OppisateBandInformation::Read()
            {
                return "OI;";
            }

            OppisateInformation OppisateBandInformation::Answer(std::string data)
            {
                OppisateInformation ret;
                std::string channelStr = data.substr(2,3);
                if(channelStr[0] == 'P')
                {
                    switch(std::stoi(channelStr.substr(1,1)))
                    {
                        case 1:
                            if(channelStr[2] == 'L')
                                ret.MemoryChannel = MemoryChannelValue::P1L;
                            else
                                ret.MemoryChannel = MemoryChannelValue::P1U;
                        break;
                        case 2:
                            if(channelStr[2] == 'L')
                                ret.MemoryChannel = MemoryChannelValue::P2L;
                            else
                                ret.MemoryChannel = MemoryChannelValue::P2U;
                        break;
                        case 3:
                            if(channelStr[2] == 'L')
                                ret.MemoryChannel = MemoryChannelValue::P3L;
                            else
                                ret.MemoryChannel = MemoryChannelValue::P3U;
                        break;
                        case 4:
                            if(channelStr[2] == 'L')
                                ret.MemoryChannel = MemoryChannelValue::P4L;
                            else
                                ret.MemoryChannel = MemoryChannelValue::P4U;
                        break;
                        case 5:
                            if(channelStr[2] == 'L')
                                ret.MemoryChannel = MemoryChannelValue::P5L;
                            else
                                ret.MemoryChannel = MemoryChannelValue::P5U;
                        break;
                        case 6:
                            if(channelStr[2] == 'L')
                                ret.MemoryChannel = MemoryChannelValue::P6L;
                            else
                                ret.MemoryChannel = MemoryChannelValue::P6U;
                        break;
                        case 7:
                            if(channelStr[2] == 'L')
                                ret.MemoryChannel = MemoryChannelValue::P7L;
                            else
                                ret.MemoryChannel = MemoryChannelValue::P7U;
                        break;
                        case 8:
                            if(channelStr[2] == 'L')
                                ret.MemoryChannel = MemoryChannelValue::P8L;
                            else
                                ret.MemoryChannel = MemoryChannelValue::P8U;
                        break;
                        case 9:
                            if(channelStr[2] == 'L')
                                ret.MemoryChannel = MemoryChannelValue::P9L;
                            else
                                ret.MemoryChannel = MemoryChannelValue::P9U;
                        break;
                    }
                }
                else if(channelStr[0] == 'E')
                {
                    ret.MemoryChannel = MemoryChannelValue::EMG;
                }
                else
                {
                    ret.MemoryChannel = static_cast<MemoryChannelValue>(std::stoi(channelStr));
                }

                ret.VFOBFreq = std::stoi(data.substr(5,9));
                ret.ClarifierFreq = std::stoi(data.substr(14,5));
                ret.RIT = static_cast<OnOffValue>(std::stoi(data.substr(19,1)));
                ret.XIT = static_cast<OnOffValue>(std::stoi(data.substr(20,1)));
                ret.Mode = static_cast<ModeValue>(std::stoi(data.substr(21,1),0,16));
                ret.VFOType = static_cast<VFOChannelTypeValue>(std::stoi(data.substr(22,1)));
                ret.CTCSS = static_cast<CTCSSState>(std::stoi(data.substr(23,1)));
                ret.Operation = static_cast<OperationType>(std::stoi(data.substr(26,1)));
                return ret;
            }

            std::string Offset::Set(OffsetValue value)
            {
                return fmt::format("OS{:1d}{:1d};",
                static_cast<int>(value.Band),
                static_cast<int>(value.State));
            }

            std::string Offset::Read(MainSubValue band)
            {
                return fmt::format("OS{:1d};",
                static_cast<int>(band));
            }

            OffsetValue Offset::Answer(std::string data)
            {
                OffsetValue ret;
                ret.Band = static_cast<MainSubValue>(std::stoi(data.substr(2,1)));
                ret.State = static_cast<OperationType>(std::stoi(data.substr(3,1)));
                return ret;
            }

            std::string PreAmp::Set(PreAmpValue value)
            {
                return fmt::format("PA{:1d}{:1d};",
                static_cast<int>(value.Band),
                static_cast<int>(value.Value));
            }

            std::string PreAmp::Read(MainSubValue band)
            {
                return fmt::format("PA{:1d};",
                static_cast<int>(band));
            }

            PreAmpValue PreAmp::Answer(std::string data)
            {
                PreAmpValue ret;
                ret.Band = static_cast<MainSubValue>(std::stoi(data.substr(2,1)));
                ret.Value = static_cast<PreampType>(std::stoi(data.substr(3,1)));
                return ret;
            }

            std::string PlayBack::Set(DVSPlayBackMode value)
            {
                return fmt::format("PB0{:1d};", static_cast<int>(value));
            }

            std::string PlayBack::Read()
            {
                return "PB0;";
            }

            DVSPlayBackMode PlayBack::Answer(std::string data)
            {
                return static_cast<DVSPlayBackMode>(std::stoi(data.substr(3,1)));
            }


            std::string PowerControl::Set(int value)
            {
                value = value < 5 ? 5 : value;
                value = value > 100 ? 100 : value;
                return fmt::format("PC{:03d};", value);
            }

            std::string PowerControl::Read()
            {
                return "PC;";
            }

            int PowerControl::Answer(std::string data)
            {
                return std::stoi(data.substr(2,3));
            }

            std::string SpeechProcessorLevel::Set(int value)
            {
                value = value < 0 ? 0 : value;
                value = value > 100? 100 : value;
                return fmt::format("PL{:3d};",value);
            }

            std::string SpeechProcessorLevel::Read()
            {
                return "PL;";
            }

            int SpeechProcessorLevel::Answer(std::string data)
            {
                return std::stoi(data.substr(2,3));
            }

            std::string SpeechProcessor::Set(SpeechProcessorValue value)
            {
                return fmt::format("PR{:1d}{:1d};",
                static_cast<int>(value.Type),
                static_cast<int>(value.State));
            }

            std::string SpeechProcessor::Read(SpeechProcessorType type)
            {
                return fmt::format("PR{:1d};", static_cast<int>(type));
            }

            SpeechProcessorValue SpeechProcessor::Answer(std::string data)
            {
                SpeechProcessorValue ret;
                ret.Type = static_cast<SpeechProcessorType>(std::stoi(data.substr(2,1)));
                ret.State = static_cast<OnOffValue>(std::stoi(data.substr(3,1)));
                return ret;
            }

            std::string PowerSwitch::Set(OnOffValue value)
            {
                return fmt::format("PS{:1d};",static_cast<int>(value));
            }

            std::string PowerSwitch::Read()
            {
                return "PS;";
            }

            OnOffValue PowerSwitch::Answer(std::string data)
            {
                return static_cast<OnOffValue>(std::stoi(data.substr(2,1)));
            }

            std::string QMBStore::Set( )
            {
                return "QI;";
            }


            std::string QMBRecall::Set()
            {
                return "QR;";
            }

            std::string QuickSplit::Set()
            {
                return "QS;";
            }

            std::string RFAttenuator::Set(AttenuatorValue value)
            {
                return fmt::format("RA{:1d}{:1d};",
                static_cast<int>(value.Band),
                static_cast<int>(value.Type));
            }

            std::string RFAttenuator::Read(MainSubValue Band)
            {
                return fmt::format("RA{:1d};",static_cast<int>(Band));
            }

            AttenuatorValue RFAttenuator::Answer(std::string data)
            {
                AttenuatorValue ret;
                ret.Band = static_cast<MainSubValue>(std::stoi(data.substr(2,1)));
                ret.Type = static_cast<AttenuatorType>(std::stoi(data.substr(3,1)));
                return ret;
            }



            std::string ClarifierDown::Set(int freq)
            {
                return fmt::format("RD{:4d};", freq);
            }

            std::string RoofingFilter::Set(RoofingFilterValue value)
            {
                return fmt::format("RF{:1d}{:1d};",
                static_cast<int>(value.Band),
                static_cast<int>(value.Type));
            }

            std::string RoofingFilter::Read(MainSubValue Band)
            {
                return fmt::format("RF{:1d};",
                static_cast<int>(Band));
            }

            RoofingFilterValue RoofingFilter::Answer(std::string data)
            {
                RoofingFilterValue ret;
                ret.Band = static_cast<MainSubValue>(std::stoi(data.substr(2,1)));
                ret.Type = static_cast<RoofingFilterType>(std::stoi(data.substr(3,1),0,16) - 5);
                return ret;
            }

            std::string RFGain::Set(RFGainValue value)
            {
                return fmt::format("RG{:1d}{:3d};",
                static_cast<int>(value.Band),
                value.Level);
            }

            std::string RFGain::Read(MainSubValue band)
            {
                return fmt::format("RG{:1d};",static_cast<int>(band));
            }

            RFGainValue RFGain::Answer(std::string data)
            {
                RFGainValue ret;
                ret.Band = static_cast<MainSubValue>(std::stoi(data.substr(2,1)));
                ret.Level = std::stoi(data.substr(3,3));
                return ret;
            }


            std::string RadioInformation::Read(RadioInformationType type)
            {
                return fmt::format("RI{:1d};", static_cast<int>(type));
            }

            RadioInformationValue RadioInformation::Answer(std::string data)
            {
                RadioInformationValue ret;
                ret.Type = static_cast<RadioInformationType>(std::stoi(data.substr(2,1)));
                ret.State = static_cast<OnOffValue>(std::stoi(data.substr(3,1)));
                return ret;
            }

            std::string NoiseReductionLevel::Set(NoseReductionLevelValue value)
            {
                value.Level = value.Level < 1 ? 1 : value.Level;
                value.Level = value.Level > 15 ? 15 : value.Level;
                return fmt::format("RL{:1d}{:2d};",
                static_cast<int>(value.Band),
                value.Level);
            }

            std::string NoiseReductionLevel::Read(MainSubValue band)
            {
                return fmt::format("RL{:1d};", static_cast<int>(band));
            }

            NoseReductionLevelValue NoiseReductionLevel::Answer(std::string data)
            {
                NoseReductionLevelValue ret;
                ret.Band = static_cast<MainSubValue>(std::stoi(data.substr(2,1)));
                ret.Level = std::stoi(data.substr(3,2));
                return ret;
            }


            std::string ReadMeter::Read(ReadMeterType type)
            {
                return fmt::format("RM{:1d};", static_cast<int>(type));
            }

            ReadMeterValue ReadMeter::Answer(std::string data)
            {
                ReadMeterValue ret;
                ret.Type = static_cast<ReadMeterType>(std::stoi(data.substr(2,1)));
                ret.LeftSide = std::stoi(data.substr(3,3));
                ret.RightSide = std::stoi(data.substr(6,3));
                return ret;
            }

            std::string RadioStatus::Read()
            {
                return "RS;";
            }

            RadioMode RadioStatus::Answer(std::string data)
            {
                return static_cast<RadioMode>(std::stoi(data.substr(2,1)));
            }

            std::string Clarifier::Set(OnOffValue value)
            {
                return fmt::format("RT{:1d};",
                static_cast<int>(value));
            }

            std::string Clarifier::Read()
            {
                return "RT;";
            }

            OnOffValue Clarifier::Answer(std::string data)
            {
                return static_cast<OnOffValue>(std::stoi(data.substr(2,1)));
            }

            std::string ClarifierPlusOffset::Set(int value)
            {
                return fmt::format("RU{:4d};", value);
            }

            std::string Scan::Set(ScanType value)
            {
                return fmt::format("SC{:1d};", static_cast<int>(value));
            }

            std::string Scan::Read()
            {
                return "SC;";
            }

            ScanType Scan::Answer(std::string data)
            {
                return static_cast<ScanType>(std::stoi(data.substr(2,1)));
            }


            std::string VoxStatus::Set(OnOffValue value)
            {
                return fmt::format("VX{:1d};", static_cast<int>(value));
            }

            std::string VoxStatus::Read()
            {
                return "VX;";
            }

            OnOffValue VoxStatus::Answer(std::string data)
            {
                return static_cast<OnOffValue>(std::stoi(data.substr(2,1)));
            }


            std::string TxClarifier::Set(OnOffValue value)
            {
                return fmt::format("XT{:1d};", static_cast<int>(value));
            }

            std::string TxClarifier::Read()
            {
                return "XT;";
            }

            OnOffValue TxClarifier::Answer(std::string data)
            {
                return static_cast<OnOffValue>(std::stoi(data.substr(2,1)));
            }


            std::string ZeroIn::Set()
            {
                return "ZI;";
            }

            std::string ClarifierClear::Set()
            {
                return "RC;";
            }

            std::string SubDial::Set(SubDialValue value)
            {
                return fmt::format("SF{:1d}{:1X};", static_cast<int>(value.Dial),
                static_cast<int>(value.Type.MULTI));
            }

            std::string SubDial::Read(SubDialKnob type)
            {
                return fmt::format("SF{:1d};", static_cast<int>(type));
            }

            SubDialValue SubDial::Answer(std::string data)
            {
                SubDialValue ret;
                ret.Dial = static_cast<SubDialKnob>(std::stoi(data.substr(2,1)));
                if(ret.Dial == SubDialKnob::MPVD)
                {
                    ret.Type.MPVD = static_cast<MPVDDialType>(std::stoi(data.substr(3,1)));
                }
                else
                {
                    ret.Type.MULTI = static_cast<MULTIDialType>(std::stoi(data.substr(3,1)));
                }
                return ret;
            }

            std::string Width::Set(WidthValue value)
            {
                return fmt::format("SH{:1d}0{:2d};",static_cast<int>(value.Band),value.Width);
            }

            std::string Width::Read(MainSubValue Band)
            {
                return fmt::format("SH{:1d};",static_cast<int>(Band));
            }

            WidthValue Width::Answer(std::string data)
            {
                WidthValue ret;
                ret.Band = static_cast<MainSubValue>(std::stoi(data.substr(2,1)));
                ret.Width = std::stoi(data.substr(4,2));
                return ret;
            }

            std::string S_MeterReading::Read(MainSubValue Band)
            {
                return fmt::format("SM{:1};",
                static_cast<int>(Band));
            }

            SMeterValue S_MeterReading::Answer(std::string data)
            {
                SMeterValue ret;
                ret.Band = static_cast<MainSubValue>(std::stoi(data.substr(2,1)));
                ret.Value = std::stoi(data.substr(3,3));
                return ret;
            }

            std::string SquelchLevel::Set(SquelchValue value)
            {
                return fmt::format("SQ{:1d}{:3d};",
                static_cast<int>(value.Band),
                value.Value);
            }

            std::string SquelchLevel::Read(MainSubValue Band)
            {
                return fmt::format("SQ{:1d};",static_cast<int>(Band));
            }

            SquelchValue SquelchLevel::Answer(std::string data)
            {
                SquelchValue ret;
                ret.Band = static_cast<MainSubValue>(std::stoi(data.substr(2,1)));
                ret.Value = std::stoi(data.substr(3,3));
                return ret;
            }

            std::string FunctionTx::Set(TxSet value)
            {
                return fmt::format("FT{:1d}", static_cast<int>(value));
            }

            std::string FunctionTx::Read()
            {
                return "FT;";
            }

            MainSubValue FunctionTx::Answer(std::string data)
            {
                return static_cast<MainSubValue>(std::stoi(data.substr(2,1)));
            }

            std::string SpectrumScope::Read()
            {
                return "SS;";
            }

            std::string SpectrumScope::Set(MainSubValue Band, SpectrumScopeFunction function, SpectrumScopeValueType value)
            {
                std::string ret;
                switch(function)
                {
                    case SpectrumScopeFunction::SPEED:
                    ret = fmt::format("SS{:01d}{:01d}{:01d}0000;",
                                       static_cast<int>(Band),
                                       static_cast<int>(function),
                                       static_cast<int>(value.Speed));
                    break;
                    case SpectrumScopeFunction::PEAK:
                    ret = fmt::format("SS{:01d}{:01d}{:01d}0000;",
                                       static_cast<int>(Band),
                                       static_cast<int>(function),
                                       static_cast<int>(value.Peak));
                    break;
                    case SpectrumScopeFunction::MARKER:
                    ret = fmt::format("SS{:01d}{:01d}{:01d}0000;",
                                       static_cast<int>(Band),
                                       static_cast<int>(function),
                                       static_cast<int>(value.Marker));
                    break;
                    case SpectrumScopeFunction::COLOR:
                    ret = fmt::format("SS{:01d}{:01d}{:01x}{:01d}{:01d}00;",
                                       static_cast<int>(Band),
                                       static_cast<int>(function),
                                       static_cast<int>(value.Colors.DIRECT_SAMPELING),
                                       static_cast<int>(value.Colors.NARROW_BAND),
                                       static_cast<int>(value.Colors.NARROW_ENABLE));
                    break;
                    case SpectrumScopeFunction::LEVEL:
                    ret = fmt::format("SS{:01d}{:01d}{:+05.1f};",
                                       static_cast<int>(Band),
                                       static_cast<int>(function),
                                       value.Level);
                    break;
                    case SpectrumScopeFunction::SPAN:
                    ret = fmt::format("SS{:01d}{:01d}{:01d}0000;",
                                       static_cast<int>(Band),
                                       static_cast<int>(function),
                                       static_cast<int>(value.Span));
                    break;
                }
                return ret;
            }

            SpectrumScopeAnswerType SpectrumScope::Answer(std::string data)
            {
                SpectrumScopeAnswerType ret;
                ret.Band = static_cast<MainSubValue>(std::stoi(data.substr(2,1)));
                ret.Function = static_cast<SpectrumScopeFunction>(std::stoi(data.substr(3,1)));
                switch(ret.Function)
                {
                    case SpectrumScopeFunction::SPEED:
                    ret.Value.Speed = static_cast<SpectrumScopeSpeedValue>(std::stoi(data.substr(4,1)));
                    break;
                    case SpectrumScopeFunction::PEAK:
                    ret.Value.Peak = static_cast<SpectrumScopePeakValue>(std::stoi(data.substr(4,1)));
                    break;

                    case SpectrumScopeFunction::MARKER:
                    ret.Value.Marker = static_cast<SpectrumScopeMarkerValue>(std::stoi(data.substr(4,1)));
                    break;
                    case SpectrumScopeFunction::COLOR:
                    ret.Value.Colors.DIRECT_SAMPELING = static_cast<SpectrumScopeDirectSampelingValue>(std::stoi(data.substr(4,1),0,16));
                    ret.Value.Colors.NARROW_BAND = static_cast<SepctrumScopeNarrowBandValue>(std::stoi(data.substr(5,1)));
                    ret.Value.Colors.NARROW_ENABLE = static_cast<SpectrumScopeNarrowBandEnableValue>(std::stoi(data.substr(6,1)));
                    break;
                    case SpectrumScopeFunction::LEVEL:
                    ret.Value.Level = std::stof(data.substr(4,8));
                    break;
                    case SpectrumScopeFunction::SPAN:
                    ret.Value.Span = static_cast<SpectrumScopeSpanValue>(std::stoi(data.substr(4,1)));
                    break;

                }
                return ret;
            }

            std::string Split::Read()
            {
                return "ST;";
            }

            std::string Split::Set(SplitType value)
            {
                return fmt::format("ST{:0d};",static_cast<int>(value));
            }

            SplitType Split::Answer(std::string data)
            {
                return static_cast<SplitType>(std::stoi(data.substr(2,1)));
            }


            std::string SwapVFO::Set()
            {
                return "SV;";
            }


            std::string SYNC::Read()
            {
                return "SY;";
            }

            std::string SYNC::Set(SyncType value)
            {
                return fmt::format("SY{:01d};", static_cast<int>(value));
            }

            SyncType SYNC::Answer(std::string data)
            {
                return static_cast<SyncType>(std::stoi(data.substr(2,1)));
            }

            std::string TXSet::Set(TxSetValue value)
            {
                return fmt::format("TX{:01d};", static_cast<int>(value));
            }

            std::string TXSet::Read()
            {
                return "TX;";
            }

            TxSetValue TXSet::Answer(std::string data)
            {
                return static_cast<TxSetValue>(std::stoi(data.substr(2,1)));
            }


            std::string PllUnlockStatus::Read()
            {
                return "UL;";
            }

            PllLockState PllUnlockStatus::Answer(std::string data)
            {
                return static_cast<PllLockState>(std::stoi(data.substr(2,1)));
            }

            std::string MicUP::Set()
            {
                return "UP;";
            }


            std::string VoxDelayTime::Set(int Delay)
            {
                return fmt::format("VD{:04d};",Delay);
            }

            std::string VoxDelayTime::Read()
            {
                return "VD;";
            }

            int VoxDelayTime::Answer(std::string data)
            {
                return std::stoi(data.substr(2,5));
            }

            std::string VoxGain::Set(int Delay)
            {
                return fmt::format("VG{:03d};",Delay);
            }

            std::string VoxGain::Read()
            {
                return "VG;";
            }

            int VoxGain::Answer(std::string data)
            {
                return std::stoi(data.substr(2,4));
            }

            std::string VFOSelect::Set(MainSubValue value)
            {
                return fmt::format("VS{:01d};", static_cast<int>(value));
            }
            std::string VFOSelect::Read()
            {
                return "VS;";
            }
            MainSubValue VFOSelect::Answer(std::string data)
            {
                return static_cast<MainSubValue>(std::stoi(data.substr(2,1)));
            }



        }

        namespace FT891
        {


            template<typename T>
            typename std::enable_if<std::is_enum<T>::value, std::string>::type DisplayOnOffValue(T t)
            {
                switch (t)
                {
                case T::ON:
                    return "ON";
                case T::OFF:
                    return "OFF";
                default:
                    return "";
                }
            }

            std::string VFO_A_TO_VFO_B::Set()
            {
                return "AB;";
            }

            std::string AntennaTunerControl::Set(TunerState state)
            {
                std::string str = fmt::format("AC00{:01d};", static_cast<int>(state));
                return str.c_str();
            }

            std::string AntennaTunerControl::Read()
            {
                return "AC;";
            }

            TunerState AntennaTunerControl::Answer(std::string data)
            {
                return (TunerState)std::stoi(data.substr(4, 1));
            }

            std::string VolumeLevel::Set(int Value)
            {
                Value = Value > 255 ? 255 : Value;
                Value = Value < 0 ? 0 : Value;
                return fmt::format("AG0{:03};", Value);
            }

            std::string VolumeLevel::Read()
            {
                return "AG0;";
            }

            int VolumeLevel::Answer(std::string data)
            {
                return std::stoi(data.substr(3,3));
            }

            std::string AutoInformation::Set(InformationState Value)
            {
                std::string str = fmt::format("AI{};", static_cast<int>(Value));
                return str;
            }

            std::string AutoInformation::Read()
            {
                return "AI;";
            }

            InformationState AutoInformation::Answer(std::string data)
            {
                return (InformationState)std::stoi(data.substr(2, 1));
            }

            std::string VFO_A_To_Memory::Set()
            {
                return "AM;";
            }

            std::string VFO_B_TO_VFO_A::Set()
            {
                return "BA;";
            }

            std::string AutoNotch::Set(NotchState Value)
            {
                std::string str = fmt::format("BC0{:d};", static_cast<int>(Value));
                return str;
            }

            std::string AutoNotch::Read()
            {
                return "BC0;";
            }

            NotchState AutoNotch::Answer(std::string data)
            {
                return (NotchState)std::stoi(data.substr(3, 1));
            }

            std::string BandDown::Set() { return "BD0;"; }

            std::string BreakIn::Set(BreakInState Value)
            {
                std::string str = fmt::format("BI{:01};", static_cast<int>(Value));
                return str.c_str();
            }

            std::string BreakIn::Read() { return "BI;"; }

            BreakInState BreakIn::Answer(std::string data)
            {
                return (BreakInState)std::stoi(data.substr(2,1));
            }

            std::string ManualNotch::Set(ManualNotchValue val)
            {

                std::string str = fmt::format("BP0{:d}{:0>3};", static_cast<int>(val.Command), val.Value.iValue);
                return str.c_str();
            }

            std::string ManualNotch::Read()
            {
                return "BP0;";
            }

            ManualNotchValue ManualNotch::Answer(std::string data)
            {
                ManualNotchValue val;
                val.Command = (NotchCommandType)std::stoi(data.substr(3, 1));
                val.Value.iValue = std::stoi(data.substr(4, 3));
                return val;
            }


            std::string BandSelect::Set(Band Value)
            {
                std::string str = fmt::format("BS{:0>2};", static_cast<int>(Value));
                return str.c_str();
            }

            std::string BandUP::Set() { return "BU0;"; }

            std::string Busy::Read()
            {
                return "BY;";
            }

            BusyState Busy::Answer(std::string data)
            {
                return (BusyState)std::stoi(data.substr(2, 1));
            }

            std::string Clarifier::Set(ClarifierState Value)
            {
                std::string str = fmt::format("CF0{:d}0;", static_cast<int>(Value));
                return str.c_str();
            }

            std::string Clarifier::Read()
            {
                return "CF0;";
            }

            ClarifierState Clarifier::Answer(std::string data)
            {
                return (ClarifierState)std::stoi(data.substr(3, 1));
            }

            std::string Channel_Up_Down::Set(UpDownState Value)
            {
                std::string str = fmt::format("CH{:d};", static_cast<int>(Value));
                return str.c_str();
            }

            std::string CTCSSToneFrequency::Set(CTCSSToneFreqencyValue val)
            {
                std::string str = fmt::format("CN0{:d}{:0>3};", static_cast<int>(val.Mode), val.Value);
                return str.c_str();
            }

            std::string CTCSSToneFrequency::Read(CTCSSModeType Mode)
            {
                std::string str = fmt::format("CN0{:d};", static_cast<int>(Mode));
                return str;
            }

            CTCSSToneFreqencyValue CTCSSToneFrequency::Answer(std::string data)
            {
                const std::string str = data;
                CTCSSToneFreqencyValue val;
                val.Mode = (CTCSSModeType)std::stoi(str.substr(3, 1));
                val.Value = std::stoi(str.substr(4, 3));
                return val;
            }

            std::string Contour::Set(ContourValue val)
            {
                std::string str = fmt::format("CO0{:d}{:04};", static_cast<int>(val.Type), val.Value.Freq);
                return str;
            }

            std::string Contour::Read(ContourValue Type)
            {
                std::string str = fmt::format("CO0{:d};", static_cast<int>(Type.Type));
                return str;
            }

            ContourValue Contour::Answer(std::string data)
            {
                ContourValue val;
                val.Type = (ContourType)std::stoi(data.substr(3, 1));
                val.Value.Freq = std::stoi(data.substr(4, 4));
                return val;
            }

            std::string CWSpot::Set(CWSpotState Value)
            {
                std::string str = fmt::format("CS{:d};", static_cast<int>(Value));
                return str;
            }

            std::string CWSpot::Read() { return "CS;"; }

            CWSpotState CWSpot::Answer(std::string data)
            {
                return (CWSpotState)std::stoi(data.substr(2, 1));
            }

            std::string CTCSS::Set(CTCSSState Value)
            {
                std::string str = fmt::format("CT0{:d};", static_cast<int>(Value));
                return str;
            }

            std::string CTCSS::Read()
            {
                return "CT0;";
            }

            CTCSSState CTCSS::Answer(std::string data)
            {
                return (CTCSSState)std::stoi(data.substr(3, 1));
            }

            std::string Dimmer::set(DimmerValues val)
            {
                std::string str = "DA";
                str += fmt::format("{:0>2}{:0>2}{:0>2}{:0>2};", val.LCD_Contrast, val.BacklightLevel, val.LCD_Level, val.TX_Indicator);
                return str.c_str();
            }

            std::string Dimmer::Read()
            {
                return "DA;";
            }

            DimmerValues Dimmer::Answer(std::string data)
            {
                std::string str = data;
                DimmerValues a;
                a.LCD_Contrast = std::stoi(str.substr(2, 2));
                a.BacklightLevel = std::stoi(str.substr(4, 2));
                a.LCD_Level = std::stoi(str.substr(6, 2));
                a.TX_Indicator = std::stoi(str.substr(8, 2));
                return a;
            }

            std::string Mic_Down::Set()
            {
                return "DN;";
            }

            std::string EncoderDown::Set(EncoderType enc, int Steps)
            {
                if (Steps > 99) Steps = 99;
                if (Steps < 1) Steps = 1;
                std::string str = fmt::format("ED{:d}{:0>2};",static_cast<int>(enc), Steps);
                return str.c_str();
            }

            std::string EnterKey::Set() { return "EK;"; }

            std::string EncoderUp::Set(EncoderType enc, int Steps)
            {
                if (Steps > 99) Steps = 99;
                if (Steps < 1) Steps = 1;
                std::string str = fmt::format("EU{:d}{:0>2};", static_cast<int>(enc), Steps);
                return str.c_str();
            }

            std::string Menu::set(std::string s)
            {
                std::string val = fmt::format("EX{};", s);
                return val.c_str();
            }

            std::string Menu::SetAgcFastDelay(int msecs)
            {
                msecs = msecs - (msecs % 20);
                msecs = msecs > 4000 ? 4000 : msecs;
                std::string val = fmt::format("{:04}{:03}", static_cast<int>(MenuFunction::AGC_FAST_DELAY), msecs);
                return set(val);
            }

            std::string Menu::ReadAgcFastDelay()
            {
                std::string s = fmt::format("{:04}", static_cast<int>(MenuFunction::AGC_FAST_DELAY));
                return set(s);
            }

            int Menu::AnswerAgcFastDelay(std::string dat)
            {
                MenuFunction s = (MenuFunction)std::stoi(dat.substr(2, 4));
                if (s == MenuFunction::AGC_FAST_DELAY)
                {
                    return std::stoi(dat.substr(6, 4));
                }
                else throw new BadMenuItemException{ s };

            }

            std::string Menu::SetAgcMidDelay(int msecs)
            {
                msecs = msecs - (msecs % 20);
                msecs = msecs > 4000 ? 4000 : msecs;
                std::string val = fmt::format("{:04}{:0>3}", static_cast<int>(MenuFunction::AGC_MID_DELAY), msecs);
                return set(val);
            }

            std::string Menu::ReadAgcMidDelay()
            {
                std::string s = fmt::format("{:04}", static_cast<int>(MenuFunction::AGC_MID_DELAY));
                return set(s);
            }

            int Menu::AnswerAgcMidDelay(std::string dat)
            {
                MenuFunction s = (MenuFunction)std::stoi(dat.substr(2, 4));
                if (s == MenuFunction::AGC_MID_DELAY)
                {
                    return std::stoi(dat.substr(6, 4));
                }
                else throw new BadMenuItemException{ s };
            }

            std::string Menu::SetAgcSlowDelay(int msecs)
            {
                msecs = msecs - (msecs % 20);
                msecs = msecs > 4000 ? 4000 : msecs;
                std::string val = fmt::format("{:04}{:04}", static_cast<int>(MenuFunction::AGC_SLOW_DELAY), msecs);
                return set(val);
            }

            std::string Menu::ReadAgcSlowDelay()
            {
                std::string s = fmt::format("{:04}", static_cast<int>(MenuFunction::AGC_SLOW_DELAY));
                return set(s);
            }

            int Menu::AnswerAgcSlowDelay(std::string dat)
            {
                MenuFunction s = (MenuFunction)std::stoi(dat.substr(2, 4));
                if (s == MenuFunction::AGC_SLOW_DELAY)
                {
                    return std::stoi(dat.substr(6, 4));
                }
                else throw new BadMenuItemException{ s };
            }

            std::string Menu::SetLcdContrast(int level)
            {
                if (level > 15) level = 15;
                if (level < 1) level = 1;
                std::string val = fmt::format("{:04}{:0>2}", static_cast<int>(MenuFunction::LCD_CONTRAST), level);
                return set(val);
            }

            std::string Menu::ReadLcdContrast()
            {
                std::string val = fmt::format("{:04}", static_cast<int>(MenuFunction::LCD_CONTRAST));
                return set(val);
            }

            int Menu::AnswerLcdContrast(std::string data)
            {
                MenuFunction f = (MenuFunction)std::stoi(data.substr(2, 4));
                if (f == MenuFunction::LCD_CONTRAST)
                {
                    return std::stoi(data.substr(6, 2));
                }
                else throw new BadMenuItemException{ f };
            }

            std::string Menu::SetBackliteDimmer(int level)
            {
                if (level > 15) level = 15;
                if (level < 1) level = 1;
                std::string val = fmt::format("{:04}{:0>2}", static_cast<int>(MenuFunction::DIMMER_BACKLIT), level);
                return set(val);
            }

            std::string Menu::ReadBackliteDimmer()
            {
                std::string val = fmt::format("{:04}", static_cast<int>(MenuFunction::DIMMER_BACKLIT));
                return set(val);
            }

            int Menu::AnswerBackliteDimmer(std::string data)
            {
                MenuFunction f = (MenuFunction)std::stoi(data.substr(2, 4));
                if (f == MenuFunction::DIMMER_BACKLIT)
                {
                    return std::stoi(data.substr(6, 2));
                }
                else throw new BadMenuItemException{ f };
            }

            std::string Menu::SetLcdDimmer(int level)
            {
                if (level > 15) level = 15;
                if (level < 1) level = 1;
                std::string val = fmt::format("{:04}{:0>2}", static_cast<int>(MenuFunction::DIMMER_LCD), level);

                return set(val);
            }

            std::string Menu::ReadLcdDimmer()
            {
                std::string val = fmt::format("{:04}", static_cast<int>(MenuFunction::DIMMER_LCD));
                return set(val);
            }

            int Menu::AnswerLcdDimmer(std::string data)
            {
                MenuFunction f = (MenuFunction)std::stoi(data.substr(2, 4));
                if (f == MenuFunction::DIMMER_LCD)
                {
                    return std::stoi(data.substr(6, 2));
                }
                else throw new BadMenuItemException{ f };
            }

            std::string Menu::SetTxBusyDimmer(int level)
            {
                if (level > 15) level = 15;
                if (level < 1) level = 1;
                std::string val = fmt::format("{:04}{:02}", static_cast<int>(MenuFunction::DIMMER_TX_BUSY), level);

                return set(val);
            }

            std::string Menu::ReadTxBusyDimmer()
            {
                std::string val = fmt::format("{:04}", static_cast<int>(MenuFunction::DIMMER_TX_BUSY));
                return set(val);
            }

            int Menu::AnswerTxBusyDimmer(std::string data)
            {
                MenuFunction f = (MenuFunction)std::stoi(data.substr(2, 4));
                if (f == MenuFunction::DIMMER_TX_BUSY)
                {
                    return std::stoi(data.substr(6, 2));
                }
                else throw new BadMenuItemException{ f };
            }


            std::string Menu::SetPeakHold(PeakHoldType value)
            {
                std::string s = fmt::format("{:04}", static_cast<int>(MenuFunction::PEAK_HOLD));
                switch (value)
                {
                case PeakHoldType::OFF:
                    s += "0";
                    break;
                case PeakHoldType::sec05:
                    s += "1";
                    break;
                case PeakHoldType::sec10:
                    s += "2";
                    break;
                case PeakHoldType::sec20:
                    s += "3";
                    break;
                }
                return set(s);
            }

            std::string Menu::ReadPeakHold()
            {
                std::string s = fmt::format("{:04}",static_cast<int>( MenuFunction::PEAK_HOLD));
                return set(s);
            }

            PeakHoldType Menu::AnswerPeakHold(std::string data)
            {
                MenuFunction f = (MenuFunction)std::stoi(data.substr(2, 4));
                if (f == MenuFunction::PEAK_HOLD)
                {
                    return (PeakHoldType)std::stoi(data.substr(6, 1));
                }
                else throw new BadMenuItemException{ f };
            }

            std::string Menu::SetZinLed(EnableDisableValue value)
            {
                std::string s = fmt::format("{:04}{:d}", static_cast<int>(MenuFunction::ZIN_LED), static_cast<int>(value));

                return set(s);
            }

            std::string Menu::ReadZinLed()
            {
                std::string s = fmt::format("{:04}", static_cast<int>(MenuFunction::ZIN_LED));
                return set(s);
            }

            EnableDisableValue Menu::AnswerZinLed(std::string data)
            {
                MenuFunction f = (MenuFunction)std::stoi(data.substr(2, 4));
                if (f == MenuFunction::ZIN_LED)
                {
                    return (EnableDisableValue)std::stoi(data.substr(6, 1));
                }
                else throw new BadMenuItemException{ f };
            }

            std::string Menu::SetPopupMenuStyle(PopUpMenuStyle style)
            {
                std::string s = fmt::format("{:04}{:d}", static_cast<int>(MenuFunction::POPUP_MENU), static_cast<int>(style));

                return set(s);
            }

            std::string Menu::ReadPopupMenuStyle()
            {
                std::string s = fmt::format("{:04}", static_cast<int>(MenuFunction::POPUP_MENU));
                return set(s);
            }

            PopUpMenuStyle Menu::AnswerPopupMenuStyle(std::string data)
            {
                MenuFunction f = (MenuFunction)std::stoi(data.substr(2, 4));
                if (f == MenuFunction::POPUP_MENU)
                {
                    return (PopUpMenuStyle)std::stoi(data.substr(6, 1));
                }
                else throw new BadMenuItemException{ f };
            }

            std::string Menu::SetDvsRxOutLevel(int Level)
            {
                std::string s = fmt::format("{:04}{:03}", static_cast<int>(MenuFunction::DVS_RX_OUT_LVL), Level);
                return set(s);
            }

            std::string Menu::ReadDvsRxOutLevel()
            {
                std::string s = fmt::format("{:04}", static_cast<int>(MenuFunction::DVS_RX_OUT_LVL));
                return set(s);
            }

            int Menu::AnswerDvsRxOutLevel(std::string data)
            {
                MenuFunction f = (MenuFunction)std::stoi(data.substr(2, 4));
                if (f == MenuFunction::DVS_RX_OUT_LVL)
                {
                    return std::stoi(data.substr(6, 3));
                }
                else throw new BadMenuItemException{ f };
            }

            std::string Menu::SetDvsTxOutLevel(int Level)
            {
                std::string s = fmt::format("{:04}{:03}", static_cast<int>(MenuFunction::DVS_TX_OUT_LVL), Level);

                return set(s);
            }

            std::string Menu::ReadDvsTxOutLevel()
            {
                std::string s = fmt::format("{:04}", static_cast<int>(MenuFunction::DVS_TX_OUT_LVL));
                return set(s);
            }

            int Menu::AnswerDvsTxOutLevel(std::string data)
            {
                MenuFunction f = (MenuFunction)std::stoi(data.substr(2, 4));
                if (f == MenuFunction::DVS_TX_OUT_LVL)
                {
                    return std::stoi(data.substr(6, 3));
                }
                else throw new BadMenuItemException{ f };
            }

            std::string Menu::SetKeyerType(KeyerTypeValue val)
            {
                std::string s = fmt::format("{:04}{:d}", static_cast<int>(MenuFunction::KEYER_TYPE), static_cast<int>(val));
                return set(s);
            }

            std::string Menu::ReadKeyerType()
            {
                std::string s = fmt::format("{:04}", static_cast<int>(MenuFunction::KEYER_TYPE));
                return set(s);
            }

            KeyerTypeValue Menu::AnswerKeyerType(std::string data)
            {
                MenuFunction f = (MenuFunction)std::stoi(data.substr(2, 4));
                if (f == MenuFunction::KEYER_TYPE)
                {
                    return (KeyerTypeValue)std::stoi(data.substr(6, 1));
                }
                else throw new BadMenuItemException{ f };
            }

            std::string Menu::SetKeyerDotDash(KeyerDotDashValue val)
            {
                std::string s = fmt::format("{:04}{:d}", static_cast<int>(MenuFunction::KEYER_DOT_DASH_ORDER), static_cast<int>(val));
                return set(s);
            }

            std::string Menu::ReadKeyerDotDash()
            {
                std::string s = fmt::format("{:04}", static_cast<int>(MenuFunction::KEYER_DOT_DASH_ORDER));
                return set(s);
            }

            KeyerDotDashValue Menu::AnswerKeyerDotDash(std::string data)
            {
                MenuFunction f = (MenuFunction)std::stoi(data.substr(2, 4));
                if (f == MenuFunction::KEYER_DOT_DASH_ORDER)
                {
                    return (KeyerDotDashValue)std::stoi(data.substr(6, 1));
                }
                else throw new BadMenuItemException{ f };
            }

            std::string Menu::SetCwWeight(int Weight)
            {
                if (Weight < 25) Weight = 25;
                if (Weight > 45) Weight = 45;
                std::string s = fmt::format("{:04}{:02}", static_cast<int>(MenuFunction::CW_WEIGHT), Weight);
                return set(s);
            }

            std::string Menu::ReadCwWeight()
            {
                std::string s = fmt::format("{:04}", static_cast<int>(MenuFunction::CW_WEIGHT));
                return set(s);
            }

            int Menu::AnswerCwWeight(std::string data)
            {
                MenuFunction f = (MenuFunction)std::stoi(data.substr(2, 4));
                if (f == MenuFunction::CW_WEIGHT)
                {
                    return std::stoi(data.substr(6, 2));
                }
                else throw new BadMenuItemException{ f };
            }

            std::string Menu::SetBeaconInterval(int value)
            {
                std::string s = fmt::format("{:04}{:03}", static_cast<int>(MenuFunction::BEACON_INTERVAL), value);
                return set(s);
            }

            std::string Menu::ReadBeaconInterval()
            {
                std::string s = fmt::format("{:04}", static_cast<int>(MenuFunction::BEACON_INTERVAL));
                return set(s);
            }

            int Menu::AnswerBeaconInterval(std::string data)
            {
                MenuFunction f = (MenuFunction)std::stoi(data.substr(2, 4));
                if (f == MenuFunction::BEACON_INTERVAL)
                {
                    return std::stoi(data.substr(6, 3));
                }
                else throw new BadMenuItemException{ f };
            }

            std::string Menu::SetNumberStyle(NumberStyleValue val)
            {
                std::string s = fmt::format("{:04}{:d}", static_cast<int>(MenuFunction::NUMBER_STYLE), static_cast<int>(val));
                return set(s);
            }

            std::string Menu::ReadNumberStyle()
            {
                std::string s = fmt::format("{:04}", static_cast<int>(MenuFunction::NUMBER_STYLE));
                return set(s);
            }

            NumberStyleValue Menu::AnswerNumberStyle(std::string data)
            {
                MenuFunction f = (MenuFunction)std::stoi(data.substr(2, 4));
                if (f == MenuFunction::NUMBER_STYLE)
                {
                    return (NumberStyleValue)std::stoi(data.substr(6, 1));
                }
                else throw new BadMenuItemException{ f };
            }

            std::string Menu::SetContestNumber(int Value)
            {
                std::string s = fmt::format("{:04}{:04}", static_cast<int>(MenuFunction::CONTEST_NUMBER), Value);
                return set(s);
            }

            std::string Menu::ReadContestNumber()
            {
                std::string s = fmt::format("{:04}", static_cast<int>(MenuFunction::CONTEST_NUMBER));
                return set(s);
            }

            int Menu::AnswerContestNumber(std::string data)
            {
                MenuFunction f = (MenuFunction)std::stoi(data.substr(2, 4));
                if (f == MenuFunction::CONTEST_NUMBER)
                {
                    return std::stoi(data.substr(6, 4));
                }
                else throw new BadMenuItemException{ f };
            }

            std::string Menu::SetCWMemory1(CWMemoryTypeValue val)
            {
                std::string s = fmt::format("{:04}{:d}", static_cast<int>(MenuFunction::CW_MEMORY_1), static_cast<int>(val));
                return set(s);
            }

            std::string Menu::ReadCWMemory1()
            {
                std::string s = fmt::format("{:04}", static_cast<int>(MenuFunction::CW_MEMORY_1));
                return set(s);
            }

            CWMemoryTypeValue Menu::AnswerCWMemory1(std::string data)
            {
                MenuFunction f = (MenuFunction)std::stoi(data.substr(2, 4));
                if (f == MenuFunction::CW_MEMORY_1)
                {
                    return (CWMemoryTypeValue)std::stoi(data.substr(6, 1));
                }
                else throw new BadMenuItemException{ f };
            }

            std::string Menu::SetCWMemory2(CWMemoryTypeValue val)
            {
                std::string s = fmt::format("{:04}{:d}", static_cast<int>(MenuFunction::CW_MEMORY_2), static_cast<int>(val));

                return set(s);
            }

            std::string Menu::ReadCWMemory2()
            {
                std::string s = fmt::format("{:04}", static_cast<int>(MenuFunction::CW_MEMORY_2));
                return set(s);
            }

            CWMemoryTypeValue Menu::AnswerCWMemory2(std::string data)
            {
                MenuFunction f = (MenuFunction)std::stoi(data.substr(2, 4));
                if (f == MenuFunction::CW_MEMORY_2)
                {
                    return (CWMemoryTypeValue)std::stoi(data.substr(6, 1));
                }
                else throw new BadMenuItemException{ f };
            }

            std::string Menu::SetCWMemory3(CWMemoryTypeValue val)
            {
                std::string s = fmt::format("{:04}{:d}", static_cast<int>(MenuFunction::CW_MEMORY_3), static_cast<int>(val));

                return set(s);
            }

            std::string Menu::ReadCWMemory3()
            {
                std::string s = fmt::format("{:04}", static_cast<int>(MenuFunction::CW_MEMORY_3));
                return set(s);
            }

            CWMemoryTypeValue Menu::AnswerCWMemory3(std::string data)
            {
                MenuFunction f = (MenuFunction)std::stoi(data.substr(2, 4));
                if (f == MenuFunction::CW_MEMORY_3)
                {
                    return (CWMemoryTypeValue)std::stoi(data.substr(6, 1));
                }
                else throw new BadMenuItemException{ f };
            }

            std::string Menu::SetCWMemory4(CWMemoryTypeValue val)
            {
                std::string s = fmt::format("{:04}{:d}", static_cast<int>(MenuFunction::CW_MEMORY_4), static_cast<int>(val));
                return set(s);
            }

            std::string Menu::ReadCWMemory4()
            {
                std::string s = fmt::format("{:04}", static_cast<int>(MenuFunction::CW_MEMORY_4));
                return set(s);
            }

            CWMemoryTypeValue Menu::AnswerCWMemory4(std::string data)
            {
                MenuFunction f = (MenuFunction)std::stoi(data.substr(2, 4));
                if (f == MenuFunction::CW_MEMORY_4)
                {
                    return (CWMemoryTypeValue)std::stoi(data.substr(6, 1));
                }
                else throw new BadMenuItemException{ f };
            }

            std::string Menu::SetCWMemory5(CWMemoryTypeValue val)
            {
                std::string s = fmt::format("{:04}{:d}", static_cast<int>(MenuFunction::CW_MEMORY_5), static_cast<int>(val));

                return set(s);
            }

            std::string Menu::ReadCWMemory5()
            {
                std::string s = fmt::format("{:04}", static_cast<int>(MenuFunction::CW_MEMORY_5));
                return set(s);
            }

            CWMemoryTypeValue Menu::AnswerCWMemory5(std::string data)
            {
                MenuFunction f = (MenuFunction)std::stoi(data.substr(2, 4));
                if (f == MenuFunction::CW_MEMORY_5)
                {
                    return (CWMemoryTypeValue)std::stoi(data.substr(6, 1));
                }
                else throw new BadMenuItemException{ f };
            }


            std::string Menu::SetNbWidth(NBWidthValue value)
            {
                std::string s = fmt::format("{:04}{:d}", static_cast<int>(MenuFunction::NB_WIDTH), static_cast<int>(value));
                return set(s);
            }

            std::string Menu::ReadNbWidth()
            {
                std::string s = fmt::format("{:04}", static_cast<int>(MenuFunction::NB_WIDTH));
                return set(s);
            }

            NBWidthValue Menu::AnswerNbWidth(std::string data)
            {
                MenuFunction f = (MenuFunction)std::stoi(data.substr(2, 4));
                if (f == MenuFunction::NB_WIDTH)
                {
                    return (NBWidthValue)std::stoi(data.substr(6, 1));
                }
                else throw new BadMenuItemException{ f };
            }

            std::string Menu::SetNbRejection(NBRejectionValue value)
            {
                std::string s = fmt::format("{:04}{:d}", static_cast<int>(MenuFunction::NB_REJECTION), static_cast<int>(value));
                return set(s);
            }

            std::string Menu::ReadNbRejection()
            {
                std::string s = fmt::format("{:04}", static_cast<int>(MenuFunction::NB_REJECTION));
                return set(s);
            }

            NBRejectionValue Menu::AnswerNbRejection(std::string data)
            {
                MenuFunction f = (MenuFunction)std::stoi(data.substr(2, 4));
                if (f == MenuFunction::NB_REJECTION)
                {
                    return (NBRejectionValue)std::stoi(data.substr(6, 1));
                }
                else throw new BadMenuItemException{ f };
            }

            std::string Menu::SetNbLevel(int level)
            {
                level = level > 10 ? 10 : level;
                std::string s = fmt::format("{:04}{:d}", static_cast<int>(MenuFunction::NB_LEVEL), static_cast<int>(level));
                return set(s);
            }

            std::string Menu::ReadNbLevel()
            {
                std::string s = fmt::format("{:04}", static_cast<int>(MenuFunction::NB_LEVEL));
                return set(s);
            }

            int Menu::AnswerNbLevel(std::string data)
            {
                MenuFunction f = (MenuFunction)std::stoi(data.substr(2, 4));
                if (f == MenuFunction::NB_LEVEL)
                {
                    return std::stoi(data.substr(6, 2));
                }
                else throw new BadMenuItemException{ f };
            }

            std::string Menu::SetBeepLevel(int level)
            {
                level = level > 100 ? 100 : level;
                std::string s = fmt::format("{:04}{:0>3}", static_cast<int>(MenuFunction::BEEP_LEVEL), static_cast<int>(level));
                return set(s);
            }

            std::string Menu::ReadBeepLevel()
            {
                std::string s = fmt::format("{:04}", static_cast<int>(MenuFunction::BEEP_LEVEL));
                return set(s);
            }

            int Menu::AnswerBeepLevel(std::string data)
            {
                MenuFunction f = (MenuFunction)std::stoi(data.substr(2, 4));
                if (f == MenuFunction::BEEP_LEVEL)
                {
                    return std::stoi(data.substr(6, 3));
                }
                else throw new BadMenuItemException{ f };
            }

            std::string Menu::SetRfSqlVr(RfSqlVrValue val)
            {
                std::string s = fmt::format("{:04}{:d}", static_cast<int>(MenuFunction::BEEP_LEVEL), static_cast<int>(val));
                return set(s);
            }

            std::string Menu::ReadRfSqlVr()
            {
                std::string s = fmt::format("{:04}", static_cast<int>(MenuFunction::BEEP_LEVEL));
                return set(s);
            }

            RfSqlVrValue Menu::AnswerRfSqlVr(std::string data)
            {
                MenuFunction f = (MenuFunction)std::stoi(data.substr(2, 4));
                if (f == MenuFunction::BEEP_LEVEL)
                {
                    return (RfSqlVrValue)std::stoi(data.substr(6, 1));
                }
                else throw new BadMenuItemException{ f };
            }

            std::string Menu::SetCatRate(CatRateValue val)
            {
                std::string s = fmt::format("{:04}{:d}", static_cast<int>(MenuFunction::CAT_RATE), static_cast<int>(val));
                return set(s);
            }

            std::string Menu::ReadCatRate()
            {
                std::string s = fmt::format("{:04}", static_cast<int>(MenuFunction::CAT_RATE));
                return set(s);
            }

            CatRateValue Menu::AnswerCatRate(std::string data)
            {
                MenuFunction f = (MenuFunction)std::stoi(data.substr(2, 4));
                if (f == MenuFunction::CAT_RATE)
                {
                    return (CatRateValue)std::stoi(data.substr(6, 1));
                }
                else throw new BadMenuItemException{ f };
            }

            std::string Menu::SetCatTOT(CatTOTValue val)
            {
                std::string s = fmt::format("{:04}{:d}", static_cast<int>(MenuFunction::CAT_TOT), static_cast<int>(val));
                return set(s);
            }

            std::string Menu::ReadCatTOT()
            {
                std::string s = fmt::format("{:04}", static_cast<int>(MenuFunction::CAT_TOT));
                return set(s);
            }

            CatTOTValue Menu::AnswerCatTOT(std::string data)
            {
                MenuFunction f = (MenuFunction)std::stoi(data.substr(2, 4));
                if (f == MenuFunction::CAT_TOT)
                {
                    return (CatTOTValue)std::stoi(data.substr(6, 1));
                }
                else throw new BadMenuItemException{ f };
            }

            std::string Menu::SetCatRTS(EnableDisableValue val)
            {
                std::string s = fmt::format("{:04}{:d}", static_cast<int>(MenuFunction::CAT_RTS), static_cast<int>(val));
                return set(s);
            }

            std::string Menu::ReadCatRTS()
            {
                std::string s = fmt::format("{:04}", static_cast<int>(MenuFunction::CAT_RTS));
                return set(s);
            }

            EnableDisableValue Menu::AnswerCatRTS(std::string data)
            {
                MenuFunction f = (MenuFunction)std::stoi(data.substr(2, 4));
                if (f == MenuFunction::CAT_RTS)
                {
                    return (EnableDisableValue)std::stoi(data.substr(6, 1));
                }
                else throw new BadMenuItemException{ f };
            }

            std::string Menu::SetMemGroup(EnableDisableValue val)
            {
                std::string s = fmt::format("{:04}{:d}", static_cast<int>(MenuFunction::MEM_GROUP), static_cast<int>(val));
                return set(s);
            }

            std::string Menu::ReadMemGroup()
            {
                std::string s = fmt::format("{:04}", static_cast<int>(MenuFunction::MEM_GROUP));
                return set(s);
            }

            EnableDisableValue Menu::AnswerMemGroup(std::string data)
            {
                MenuFunction f = (MenuFunction)std::stoi(data.substr(2, 4));
                if (f == MenuFunction::MEM_GROUP)
                {
                    return (EnableDisableValue)std::stoi(data.substr(6, 1));
                }
                else throw new BadMenuItemException{ f };
            }

            std::string Menu::SetFMSetting(EnableDisableValue val)
            {
                std::string s = fmt::format("{:04}{:d}", static_cast<int>(MenuFunction::FM_SETTING), static_cast<int>(val));
                return set(s);
            }

            std::string Menu::ReadFMSetting()
            {
                std::string s = fmt::format("{:04}", static_cast<int>(MenuFunction::FM_SETTING));
                return set(s);
            }

            EnableDisableValue Menu::AnswerFMSetting(std::string data)
            {
                MenuFunction f = (MenuFunction)std::stoi(data.substr(2, 4));
                if (f == MenuFunction::FM_SETTING)
                {
                    return (EnableDisableValue)std::stoi(data.substr(6, 1));
                }
                else throw new BadMenuItemException{ f };
            }


            std::string Menu::SetRecSetting(EnableDisableValue val)
            {
                std::string s = fmt::format("{:04}{:d}", static_cast<int>(MenuFunction::REC_SETTING), static_cast<int>(val));
                return set(s);
            }

            std::string Menu::ReadRecSetting()
            {
                std::string s = fmt::format("{:04}", static_cast<int>(MenuFunction::REC_SETTING));
                return set(s);
            }

            EnableDisableValue Menu::AnswerRecSetting(std::string data)
            {
                MenuFunction f = (MenuFunction)std::stoi(data.substr(2, 4));
                if (f == MenuFunction::REC_SETTING)
                {
                    return (EnableDisableValue)std::stoi(data.substr(6, 1));
                }
                else throw new BadMenuItemException{ f };
            }

            std::string Menu::SetATASSetting(EnableDisableValue val)
            {
                std::string s = fmt::format("{:04}{:d}", static_cast<int>(MenuFunction::ATAS_SETTING), static_cast<int>(val));
                return set(s);
            }

            std::string Menu::ReadATASSetting()
            {
                std::string s = fmt::format("{:04}", static_cast<int>(MenuFunction::ATAS_SETTING));
                return set(s);
            }

            EnableDisableValue Menu::AnswerATASSetting(std::string data)
            {
                MenuFunction f = (MenuFunction)std::stoi(data.substr(2, 4));
                if (f == MenuFunction::ATAS_SETTING)
                {
                    return (EnableDisableValue)std::stoi(data.substr(6, 1));
                }
                else throw new BadMenuItemException{ f };
            }

            std::string Menu::SetQuickSplitFreq(int val)
            {
                val = val > 20 ? 20 : val;
                val = val < -20 ? -20 : val;

                std::string s = fmt::format("{:04}{:+d}", static_cast<int>(MenuFunction::QUICK_SPL_FREQ), val);
                return set(s);
            }

            std::string Menu::ReadQuickSplitFreq()
            {
                std::string s = fmt::format("{:04}", static_cast<int>(MenuFunction::QUICK_SPL_FREQ));
                return set(s);
            }

            int Menu::AnswerQuickSplitFreq(std::string data)
            {
                MenuFunction f = (MenuFunction)std::stoi(data.substr(2, 4));
                if (f == MenuFunction::QUICK_SPL_FREQ)
                {
                    return std::stoi(data.substr(6, 3));
                }
                else throw new BadMenuItemException{ f };
            }

            std::string Menu::SetTxTOT(int val)
            {
                val = val < 0 ? 0 : val;
                val = val > 30 ? 30 : val;
                std::string s = fmt::format("{:04}{:d}", static_cast<int>(MenuFunction::TX_TOT), val);
                return set(s);
            }

            std::string Menu::ReadTXTOT()
            {
                std::string s = fmt::format("{:04}", static_cast<int>(MenuFunction::TX_TOT));
                return set(s);
            }

            int  Menu::AnswerTXTOT(std::string data)
            {
                MenuFunction f = (MenuFunction)std::stoi(data.substr(2, 4));
                if (f == MenuFunction::TX_TOT)
                {
                    return std::stoi(data.substr(6, 2));
                }
                else throw new BadMenuItemException{ f };
            }

            std::string Menu::SetMicScan(EnableDisableValue val)
            {
                std::string s = fmt::format("{:04}{:d}", static_cast<int>(MenuFunction::MIC_SCAN), static_cast<int>(val));
                return set(s);
            }

            std::string Menu::ReadMicScan()
            {
                std::string s = fmt::format("{:04}", static_cast<int>(MenuFunction::MIC_SCAN));
                return set(s);
            }

            EnableDisableValue  Menu::AnswerMicScan(std::string data)
            {
                MenuFunction f = (MenuFunction)std::stoi(data.substr(2, 4));
                if (f == MenuFunction::MIC_SCAN)
                {
                    return (EnableDisableValue)std::stoi(data.substr(6, 1));
                }
                else throw new BadMenuItemException{ f };
            }

            std::string Menu::SetMicScanResume(MicScanResumeValue val)
            {
                std::string s = fmt::format("{:04}{:d}", static_cast<int>(MenuFunction::MIC_SCAN_RESUME), static_cast<int>(val));
                return set(s);
            }

            std::string Menu::ReadMicScanResume()
            {
                std::string s = fmt::format("{:04}", static_cast<int>(MenuFunction::MIC_SCAN_RESUME));
                return set(s);
            }

            MicScanResumeValue  Menu::AnswerMicScanResume(std::string data)
            {
                MenuFunction f = (MenuFunction)std::stoi(data.substr(2, 4));
                if (f == MenuFunction::MIC_SCAN_RESUME)
                {
                    return (MicScanResumeValue)std::stoi(data.substr(6, 1));
                }
                else throw new BadMenuItemException{ f };
            }

            std::string Menu::SetRefFreqAdjust(int val)
            {
                val = val < -25 ? -25 : val;
                val = val > 25 ? 25 : val;

                std::string s = fmt::format("{:04}{:+03}", static_cast<int>(MenuFunction::REF_FEQ_ADJ), val);
                return set(s);
            }

            std::string Menu::ReadRefFreqAdjust()
            {
                std::string s = fmt::format("{:04}", static_cast<int>(MenuFunction::REF_FEQ_ADJ));
                return set(s);
            }

            int Menu::AnswerRefFreqAdjust(std::string data)
            {
                MenuFunction f = (MenuFunction)std::stoi(data.substr(2, 4));
                if (f == MenuFunction::REF_FEQ_ADJ)
                {
                    return std::stoi(data.substr(6, 3));
                }
                else throw new BadMenuItemException{ f };
            }

            std::string Menu::SetClarSelect(ClarSelectValue val)
            {
                std::string s = fmt::format("{:04}{:d}", static_cast<int>(MenuFunction::CLAR_SELECT), static_cast<int>(val));
                return set(s);
            }

            std::string Menu::ReadClarSelect()
            {
                std::string s = fmt::format("{:04}", static_cast<int>(MenuFunction::CLAR_SELECT));
                return set(s);
            }

            ClarSelectValue  Menu::AnswerClarSelect(std::string data)
            {
                MenuFunction f = (MenuFunction)std::stoi(data.substr(2, 4));
                if (f == MenuFunction::CLAR_SELECT)
                {
                    return (ClarSelectValue)std::stoi(data.substr(6, 1));
                }
                else throw new BadMenuItemException{ f };
            }

            std::string Menu::SetApo(APOValue val)
            {
                std::string s = fmt::format("{:04}{:d}", static_cast<int>(MenuFunction::APO), static_cast<int>(val));
                return set(s);
            }

            std::string Menu::ReadApo()
            {
                std::string s = fmt::format("{:04}", static_cast<int>(MenuFunction::APO));
                return set(s);
            }

            APOValue Menu::AnswerApo(std::string data)
            {
                MenuFunction f = (MenuFunction)std::stoi(data.substr(2, 4));
                if (f == MenuFunction::APO)
                {
                    return (APOValue)std::stoi(data.substr(6, 1));
                }
                else throw new BadMenuItemException{ f };
            }

            std::string Menu::SetFanControl(FanControlValue val)
            {
                std::string s = fmt::format("{:04}{:d}", static_cast<int>(MenuFunction::FAN_CONTROL), static_cast<int>(val));
                return set(s);
            }

            std::string Menu::ReadFanControl()
            {
                std::string s = fmt::format("{:04}", static_cast<int>(MenuFunction::FAN_CONTROL));
                return set(s);
            }

            FanControlValue Menu::AnswerFanControl(std::string data)
            {
                MenuFunction f = (MenuFunction)std::stoi(data.substr(2, 4));
                if (f == MenuFunction::FAN_CONTROL)
                {
                    return (FanControlValue)std::stoi(data.substr(6, 1));
                }
                else throw new BadMenuItemException{ f };
            }

            std::string Menu::SetAMLowCutFreq(FreqLowCutValue val)
            {
                std::string s = fmt::format("{:04}{:02}", static_cast<int>(MenuFunction::AM_LCUT_FREQ), static_cast<int>(val));
                return set(s);
            }

            std::string Menu::ReadAMLowCutFreq()
            {
                std::string s = fmt::format("{:04}", static_cast<int>(MenuFunction::AM_LCUT_FREQ));
                return set(s);
            }

            FreqLowCutValue Menu::AnswerAMLowCutFreq(std::string data)
            {
                MenuFunction f = (MenuFunction)std::stoi(data.substr(2, 4));
                if (f == MenuFunction::AM_LCUT_FREQ)
                {
                    return (FreqLowCutValue)std::stoi(data.substr(6, 2));
                }
                else throw new BadMenuItemException{ f };
            }

            std::string Menu::SetAMLowCutSlope(FreqSlopeValue val)
            {
                std::string s = fmt::format("{:04}{:d}", static_cast<int>(MenuFunction::AM_LCUT_SLOPE), static_cast<int>(val));
                return set(s);
            }

            std::string Menu::ReadAMLowCutSlope()
            {
                std::string s = fmt::format("{:04}", static_cast<int>(MenuFunction::AM_LCUT_SLOPE));
                return set(s);
            }

            FreqSlopeValue Menu::AnswerAMLowCutSlope(std::string data)
            {
                MenuFunction f = (MenuFunction)std::stoi(data.substr(2, 4));
                if (f == MenuFunction::AM_LCUT_SLOPE)
                {
                    return (FreqSlopeValue)std::stoi(data.substr(6, 1));
                }
                else throw new BadMenuItemException{ f };
            }

            std::string Menu::SetAMHighCutFreq(FreqHighCutValue val)
            {
                std::string s = fmt::format("{:04}{:02}", static_cast<int>(MenuFunction::AM_HCUT_FREQ), static_cast<int>(val));
                return set(s);
            }

            std::string Menu::ReadAMHighCutFreq()
            {
                std::string s = fmt::format("{:04}", static_cast<int>(MenuFunction::AM_HCUT_FREQ));
                return set(s);
            }

            FreqHighCutValue Menu::AnswerAMHighCutFreq(std::string data)
            {
                MenuFunction f = (MenuFunction)std::stoi(data.substr(2, 4));
                if (f == MenuFunction::AM_HCUT_FREQ)
                {
                    return (FreqHighCutValue)std::stoi(data.substr(6, 2));
                }
                else throw new BadMenuItemException{ f };
            }

            std::string Menu::SetAMHighCutSlope(FreqSlopeValue val)
            {
                std::string s = fmt::format("{:04}{:d}", static_cast<int>(MenuFunction::AM_HCUT_SLOPE), static_cast<int>(val));
                return set(s);
            }

            std::string Menu::ReadAMHighCutSlope()
            {
                std::string s = fmt::format("{:04}", static_cast<int>(MenuFunction::AM_HCUT_SLOPE));
                return set(s);
            }

            FreqSlopeValue Menu::AnswerAMHighCutSlope(std::string data)
            {
                MenuFunction f = (MenuFunction)std::stoi(data.substr(2, 4));
                if (f == MenuFunction::AM_HCUT_SLOPE)
                {
                    return (FreqSlopeValue)std::stoi(data.substr(6, 1));
                }
                else throw new BadMenuItemException{ f };
            }

            std::string Menu::SetAMMicSelect(AudioInputValue val)
            {
                std::string s = fmt::format("{:04}{:d}", static_cast<int>(MenuFunction::AM_MIC_SELECT), static_cast<int>(val));
                return set(s);
            }

            std::string Menu::ReadAMMicSelect()
            {
                std::string s = fmt::format("{:04}", static_cast<int>(MenuFunction::AM_MIC_SELECT));
                return set(s);
            }

            AudioInputValue Menu::AnswerAMMicSelect(std::string data)
            {
                MenuFunction f = (MenuFunction)std::stoi(data.substr(2, 4));
                if (f == MenuFunction::AM_MIC_SELECT)
                {
                    return (AudioInputValue)std::stoi(data.substr(6, 1));
                }
                else throw new BadMenuItemException{ f };
            }

            std::string Menu::SetAMOutLevel(int val)
            {
                val = val > 100 ? 100 : val;
                val = val < 0 ? 0 : val;
                std::string s = fmt::format("{:04}{:03}", static_cast<int>(MenuFunction::AM_OUT_LEVEL), val);
                return set(s);
            }

            std::string Menu::ReadAMOutLevel()
            {
                std::string s = fmt::format("{:04}", static_cast<int>(MenuFunction::AM_OUT_LEVEL));
                return set(s);
            }

            int Menu::AnswerAMOutLevel(std::string data)
            {
                MenuFunction f = (MenuFunction)std::stoi(data.substr(2, 4));
                if (f == MenuFunction::AM_OUT_LEVEL)
                {
                    return std::stoi(data.substr(6, 3));
                }
                else throw new BadMenuItemException{ f };

            }


            std::string Menu::SetAMMicLevel(int val)
            {
                val = val > 100 ? 100 : val;
                val = val < 0 ? 0 : val;
                std::string s = fmt::format("{:04}{:03}", static_cast<int>(MenuFunction::AM_MIC_GAIN), val);
                return set(s);
            }

            std::string Menu::ReadAMMicLevel()
            {
                std::string s = fmt::format("{:04}", static_cast<int>(MenuFunction::AM_MIC_GAIN));
                return set(s);
            }

            int Menu::AnswerAMMicLevel(std::string data)
            {
                MenuFunction f = (MenuFunction)std::stoi(data.substr(2, 4));
                if (f == MenuFunction::AM_MIC_GAIN)
                {
                    return std::stoi(data.substr(6, 3));
                }
                else throw new BadMenuItemException{ f };

            }

            std::string Menu::SetAMPTTSelect(PTTSelectValue val)
            {
                std::string s = fmt::format("{:04}{:d}", static_cast<int>(MenuFunction::AM_PTT_SELECT), static_cast<int>(val));
                return set(s);
            }

            std::string Menu::ReadAMPTTSelect()
            {
                std::string s = fmt::format("{:04}", static_cast<int>(MenuFunction::AM_PTT_SELECT));
                return set(s);
            }

            PTTSelectValue Menu::AnswerAMPTTSelect(std::string data)
            {
                MenuFunction f = (MenuFunction)std::stoi(data.substr(2, 4));
                if (f == MenuFunction::AM_PTT_SELECT)
                {
                    return (PTTSelectValue)std::stoi(data.substr(6, 1));
                }
                else throw new BadMenuItemException{ f };
            }

            std::string Menu::SetCWLowCutFreq(FreqLowCutValue val)
            {
                std::string s = fmt::format("{:04}{:02}", static_cast<int>(MenuFunction::CW_LCUT_FREQ), static_cast<int>(val));
                return set(s);
            }

            std::string Menu::ReadCWLowCutFreq()
            {
                std::string s = fmt::format("{:04}", static_cast<int>(MenuFunction::CW_LCUT_FREQ));
                return set(s);
            }

            FreqLowCutValue Menu::AnswerCWLowCutFreq(std::string data)
            {
                MenuFunction f = (MenuFunction)std::stoi(data.substr(2, 4));
                if (f == MenuFunction::CW_LCUT_FREQ)
                {
                    return (FreqLowCutValue)std::stoi(data.substr(6, 2));
                }
                else throw new BadMenuItemException{ f };
            }

            std::string Menu::SetCWLowCutSlope(FreqSlopeValue val)
            {
                std::string s = fmt::format("{:04}{:d}", static_cast<int>(MenuFunction::CW_LCUT_SLOPE), static_cast<int>(val));
                return set(s);
            }

            std::string Menu::ReadCWLowCutSlope()
            {

                std::string s = fmt::format("{:04}", static_cast<int>(MenuFunction::CW_LCUT_SLOPE));
                return set(s);
            }

            FreqSlopeValue Menu::AnswerCWLowCutSlope(std::string data)
            {
                MenuFunction f = (MenuFunction)std::stoi(data.substr(2, 4));
                if (f == MenuFunction::CW_LCUT_SLOPE)
                {
                    return (FreqSlopeValue)std::stoi(data.substr(6, 1));
                }
                else throw new BadMenuItemException{ f };
            }

            std::string Menu::SetCWHighCutFreq(FreqHighCutValue val)
            {
                std::string s = fmt::format("{:04}{:02}", static_cast<int>(MenuFunction::CW_HCUT_FREQ), static_cast<int>(val));
                return set(s);
            }

            std::string Menu::ReadCWHighCutFreq()
            {
                std::string s = fmt::format("{:04}", static_cast<int>(MenuFunction::CW_HCUT_FREQ));
                return set(s);
            }

            FreqHighCutValue Menu::AnswerCWHighCutFreq(std::string data)
            {
                MenuFunction f = (MenuFunction)std::stoi(data.substr(2, 4));
                if (f == MenuFunction::CW_HCUT_FREQ)
                {
                    return (FreqHighCutValue)std::stoi(data.substr(6, 2));
                }
                else throw new BadMenuItemException{ f };
            }

            std::string Menu::SetCWHighCutSlope(FreqSlopeValue val)
            {
                std::string s = fmt::format("{:04}{:d}", static_cast<int>(MenuFunction::CW_HCUT_SLOPE), static_cast<int>(val));
                return set(s);
            }

            std::string Menu::ReadCWHighCutSlope()
            {
                std::string s = fmt::format("{:04}", static_cast<int>(MenuFunction::CW_HCUT_SLOPE));
                return set(s);
            }

            FreqSlopeValue Menu::AnswerCWHighCutSlope(std::string data)
            {
                MenuFunction f = (MenuFunction)std::stoi(data.substr(2, 4));
                if (f == MenuFunction::CW_HCUT_SLOPE)
                {
                    return (FreqSlopeValue)std::stoi(data.substr(6, 1));
                }
                else throw new BadMenuItemException{ f };
            }

            std::string Menu::SetCWOutLevel(int val)
            {
                val = val > 100 ? 100 : val;
                val = val < 0 ? 0 : val;
                std::string s = fmt::format("{:04}{:03}", static_cast<int>(MenuFunction::CW_OUT_LEVEL), val);
                return set(s);
            }

            std::string Menu::ReadCWOutLevel()
            {
                std::string s = fmt::format("{:04}", static_cast<int>(MenuFunction::CW_OUT_LEVEL));
                return set(s);
            }

            int Menu::AnswerCWOutLevel(std::string data)
            {
                MenuFunction f = (MenuFunction)std::stoi(data.substr(2, 4));
                if (f == MenuFunction::CW_OUT_LEVEL)
                {
                    return std::stoi(data.substr(6, 3));
                }
                else throw new BadMenuItemException{ f };
            }

            std::string Menu::SetCWAutoMode(CwAutoModeValue val)
            {
                std::string s = fmt::format("{:04}{:d}", static_cast<int>(MenuFunction::CW_AUTO_MODE), static_cast<int>(val));
                return set(s);
            }


            std::string Menu::ReadCWAutoMode()
            {

                std::string s = fmt::format("{:04}", static_cast<int>(MenuFunction::CW_AUTO_MODE));
                return set(s);
            }

            CwAutoModeValue Menu::AnswerCWAutoMode(std::string data)
            {
                MenuFunction f = (MenuFunction)std::stoi(data.substr(2, 4));
                if (f == MenuFunction::CW_AUTO_MODE)
                {
                    return (CwAutoModeValue)std::stoi(data.substr(6, 1));
                }
                else throw new BadMenuItemException{ f };
            }

            std::string Menu::SetCWBFO(BfoValue val)
            {
                std::string s = fmt::format("{:04}{:d}", static_cast<int>(MenuFunction::CW_BFO), static_cast<int>(val));
                return set(s);
            }

            std::string Menu::ReadCWBFO()
            {
                std::string s = fmt::format("{:04}", static_cast<int>(MenuFunction::CW_BFO));
                return set(s);
            }

            BfoValue Menu::AnswerCWBFO(std::string data)
            {
                MenuFunction f = (MenuFunction)std::stoi(data.substr(2, 4));
                if (f == MenuFunction::CW_BFO)
                {
                    return (BfoValue)std::stoi(data.substr(6, 1));
                }
                else throw new BadMenuItemException{ f };
            }

            std::string Menu::SetCWBreakkInType(CwBreakInType val)
            {
                std::string s = fmt::format("{:04}{:d}", static_cast<int>(MenuFunction::CW_BK_IN_TYPE), static_cast<int>(val));
                return set(s);
            }

            std::string Menu::ReadCWBreakInType()
            {
                std::string s = fmt::format("{:04}", static_cast<int>(MenuFunction::CW_BK_IN_TYPE));
                return set(s);
            }

            CwBreakInType Menu::AnswerCWBreakInType(std::string data)
            {
                MenuFunction f = (MenuFunction)std::stoi(data.substr(2, 4));
                if (f == MenuFunction::CW_BK_IN_TYPE)
                {
                    return (CwBreakInType)std::stoi(data.substr(6, 1));
                }
                else throw new BadMenuItemException{ f };
            }

            std::string Menu::SetCWBreakkInDelay(int val)
            {
                val = (val % 10) == 0 ? val : val - (val % 10);
                val = val > 3000 ? 3000 : val;
                val = val < 30 ? 30 : val;
                std::string s = fmt::format("{:04}{:04}", static_cast<int>(MenuFunction::CW_BK_IN_DELAY), val);
                return set(s);
            }

            std::string Menu::ReadCWBreakInDelay()
            {
                std::string s = fmt::format("{:04}", static_cast<int>(MenuFunction::CW_BK_IN_DELAY));
                return set(s);
            }

            int Menu::AnswerCWBreakInDelay(std::string data)
            {
                MenuFunction f = (MenuFunction)std::stoi(data.substr(2, 4));
                if (f == MenuFunction::CW_BK_IN_DELAY)
                {
                    return std::stoi(data.substr(6, 4));
                }
                else throw new BadMenuItemException{ f };
            }

            std::string Menu::SetCWWaveShape(CwWaveShapeValue val)
            {
                std::string s = fmt::format("{:04}{:d}", static_cast<int>(MenuFunction::CW_WAVE_SHAPE), static_cast<int>(val));
                return set(s);
            }

            std::string Menu::ReadCWWaveShape()
            {
                std::string s = fmt::format("{:04}", static_cast<int>(MenuFunction::CW_WAVE_SHAPE));
                return set(s);
            }

            CwWaveShapeValue Menu::AnswerCWWaveShape(std::string data)
            {
                MenuFunction f = (MenuFunction)std::stoi(data.substr(2, 4));
                if (f == MenuFunction::CW_WAVE_SHAPE)
                {
                    return (CwWaveShapeValue)std::stoi(data.substr(6, 1));
                }
                else throw new BadMenuItemException{ f };
            }

            std::string Menu::SetCWFreqDisplay(CwFreqDisplayValue val)
            {
                std::string s = fmt::format("{:04}{:d}", static_cast<int>(MenuFunction::CW_FREQ_DISPLAY), static_cast<int>(val));
                return set(s);
            }

            std::string Menu::ReadCWFreqDisplay()
            {
                std::string s = fmt::format("{:04}", static_cast<int>(MenuFunction::CW_FREQ_DISPLAY));
                return set(s);
            }

            CwFreqDisplayValue Menu::AnswerCWFreqDisplay(std::string data)
            {
                MenuFunction f = (MenuFunction)std::stoi(data.substr(2, 4));
                if (f == MenuFunction::CW_FREQ_DISPLAY)
                {
                    return (CwFreqDisplayValue)std::stoi(data.substr(6, 1));
                }
                else throw new BadMenuItemException{ f };
            }

            std::string Menu::SetPCKeying(PCKeyingValue val)
            {
                std::string s = fmt::format("{:04}{:d}", static_cast<int>(MenuFunction::PC_KEYING), static_cast<int>(val));
                return set(s);
            }

            std::string Menu::ReadPCKeying()
            {
                std::string s = fmt::format("{:04}", static_cast<int>(MenuFunction::PC_KEYING));
                return set(s);
            }

            PCKeyingValue Menu::AnswerPCKeying(std::string data)
            {
                MenuFunction f = (MenuFunction)std::stoi(data.substr(2, 4));
                if (f == MenuFunction::PC_KEYING)
                {
                    return (PCKeyingValue)std::stoi(data.substr(6, 1));
                }
                else throw new BadMenuItemException{ f };
            }

            std::string Menu::SetQSKDelayTime(QskDelayTimeValue val)
            {
                std::string s = fmt::format("{:04}{:d}", static_cast<int>(MenuFunction::QSK_DELAY_TIME), static_cast<int>(val));
                return set(s);
            }

            std::string Menu::ReadQSKDelayTime()
            {
                std::string s = fmt::format("{:04}", static_cast<int>(MenuFunction::QSK_DELAY_TIME));
                return set(s);
            }

            QskDelayTimeValue Menu::AnswerQSKDelayTime(std::string data)
            {
                MenuFunction f = (MenuFunction)std::stoi(data.substr(2, 4));
                if (f == MenuFunction::QSK_DELAY_TIME)
                {
                    return (QskDelayTimeValue)std::stoi(data.substr(6, 1));
                }
                else throw new BadMenuItemException{ f };
            }

            std::string Menu::SetDataMode(DataModeValue val)
            {
                std::string s = fmt::format("{:04}{:d}", static_cast<int>(MenuFunction::DATA_MODE), static_cast<int>(val));
                return set(s);
            }

            std::string Menu::ReadDataMode()
            {
                std::string s = fmt::format("{:04}", static_cast<int>(MenuFunction::DATA_MODE));
                return set(s);
            }

            DataModeValue Menu::AnswerDataMode(std::string data)
            {
                MenuFunction f = (MenuFunction)std::stoi(data.substr(2, 4));
                if (f == MenuFunction::DATA_MODE)
                {
                    return (DataModeValue)std::stoi(data.substr(6, 1));
                }
                else throw new BadMenuItemException{ f };
            }

            std::string Menu::SetPSKTone(PSKToneValue val)
            {
                std::string s = fmt::format("{:04}{:d}", static_cast<int>(MenuFunction::PSK_TONE), static_cast<int>(val));
                return set(s);
            }

            std::string Menu::ReadPSKTone()
            {
                std::string s = fmt::format("{:04}", static_cast<int>(MenuFunction::PSK_TONE));
                return set(s);
            }

            PSKToneValue Menu::AnswerPSKTone(std::string data)
            {
                MenuFunction f = (MenuFunction)std::stoi(data.substr(2, 4));
                if (f == MenuFunction::PSK_TONE)
                {
                    return (PSKToneValue)std::stoi(data.substr(6, 1));
                }
                else throw new BadMenuItemException{ f };
            }

            std::string Menu::SetOtherDisp(int val)
            {
                val = val < -3000 ? -3000 : val;
                val = val > 3000 ? 3000 : val;
                val = (val % 10) == 0 ? val : val - (val % 10);
                std::string s = fmt::format("{:04}{:+05}", static_cast<int>(MenuFunction::OTHER_DISP), val);
                return set(s);
            }

            std::string Menu::ReadOtherDisp()
            {
                std::string s = fmt::format("{:04}", static_cast<int>(MenuFunction::OTHER_DISP));
                return set(s);
            }

            int Menu::AnswerOtherDisp(std::string data)
            {
                MenuFunction f = (MenuFunction)std::stoi(data.substr(2, 4));
                if (f == MenuFunction::OTHER_DISP)
                {
                    return std::stoi(data.substr(6, 5));
                }
                else throw new BadMenuItemException{ f };
            }

            std::string Menu::SetOtherShift(int val)
            {
                val = val < -3000 ? -3000 : val;
                val = val > 3000 ? 3000 : val;
                val = (val % 10) == 0 ? val : val - (val % 10);
                std::string s = fmt::format("{:04}{:+05}", static_cast<int>(MenuFunction::OTHER_SHIFT), static_cast<int>(val));
                return set(s);

            }

            std::string Menu::ReadOtherShift()
            {
                std::string s = fmt::format("{:04}", static_cast<int>(MenuFunction::OTHER_SHIFT));
                return set(s);
            }

            int Menu::AnswerOtherShift(std::string data)
            {
                MenuFunction f = (MenuFunction)std::stoi(data.substr(2, 4));
                if (f == MenuFunction::OTHER_SHIFT)
                {
                    return std::stoi(data.substr(6, 5));
                }
                else throw new BadMenuItemException{ f };
            }

            std::string Menu::SetDATALowCutFreq(FreqLowCutValue val)
            {
                std::string s = fmt::format("{:04}{:02}", static_cast<int>(MenuFunction::DATA_LCUT_FREQ), static_cast<int>(val));
                return set(s);
            }

            std::string Menu::ReadDATALowCutFreq()
            {
                std::string s = fmt::format("{:04}", static_cast<int>(MenuFunction::DATA_LCUT_FREQ));
                return set(s);
            }

            FreqLowCutValue Menu::AnswerDATALowCutFreq(std::string data)
            {
                MenuFunction f = (MenuFunction)std::stoi(data.substr(2, 4));
                if (f == MenuFunction::DATA_LCUT_FREQ)
                {
                    return (FreqLowCutValue)std::stoi(data.substr(6, 2));
                }
                else throw new BadMenuItemException{ f };
            }

            std::string Menu::SetDATALowCutSlope(FreqSlopeValue val)
            {
                std::string s = fmt::format("{:04}{:d}", static_cast<int>(MenuFunction::DATA_LCUT_SLOPE), static_cast<int>(val));
                return set(s);
            }

            std::string Menu::ReadDATALowCutSlope()
            {
                std::string s = fmt::format("{:04}", static_cast<int>(MenuFunction::DATA_LCUT_SLOPE));
                return set(s);
            }

            FreqSlopeValue Menu::AnswerDATALowCutSlope(std::string data)
            {
                MenuFunction f = (MenuFunction)std::stoi(data.substr(2, 4));
                if (f == MenuFunction::DATA_LCUT_SLOPE)
                {
                    return (FreqSlopeValue)std::stoi(data.substr(6, 1));
                }
                else throw new BadMenuItemException{ f };
            }

            std::string Menu::SetDATAHighCutFreq(FreqHighCutValue val)
            {
                std::string s = fmt::format("{:04}{:02}", static_cast<int>(MenuFunction::DATA_HCUT_FREQ), static_cast<int>(val));
                return set(s);
            }

            std::string Menu::ReadDATAHighCutFreq()
            {
                std::string s = fmt::format("{:04}", static_cast<int>(MenuFunction::DATA_HCUT_FREQ));
                return set(s);
            }

            FreqHighCutValue Menu::AnswerDATAHighCutFreq(std::string data)
            {
                MenuFunction f = (MenuFunction)std::stoi(data.substr(2, 4));
                if (f == MenuFunction::DATA_HCUT_FREQ)
                {
                    return (FreqHighCutValue)std::stoi(data.substr(6, 2));
                }
                else throw new BadMenuItemException{ f };
            }

            std::string Menu::SetDATAHighCutSlope(FreqSlopeValue val)
            {
                std::string s = fmt::format("{:04}{:d}", static_cast<int>(MenuFunction::DATA_HCUT_SLOPE), static_cast<int>(val));
                return set(s);
            }

            std::string Menu::ReadDATAHighCutSlope()
            {
                std::string s = fmt::format("{:04}", static_cast<int>(MenuFunction::DATA_HCUT_SLOPE));
                return set(s);
            }

            FreqSlopeValue Menu::AnswerDATAHighCutSlope(std::string data)
            {
                MenuFunction f = (MenuFunction)std::stoi(data.substr(2, 4));
                if (f == MenuFunction::DATA_HCUT_SLOPE)
                {
                    return (FreqSlopeValue)std::stoi(data.substr(6, 1));
                }
                else throw new BadMenuItemException{ f };
            }

            std::string Menu::SetDATAInSelect(AudioInputValue val)
            {
                std::string s = fmt::format("{:04}{:d}", static_cast<int>(MenuFunction::DATA_IN_SELECT), static_cast<int>(val));
                return set(s);
            }

            std::string Menu::ReadDATAInSelect()
            {
                std::string s = fmt::format("{:04}", static_cast<int>(MenuFunction::DATA_IN_SELECT));
                return set(s);
            }

            AudioInputValue Menu::AnswerDATAInSelect(std::string data)
            {
                MenuFunction f = (MenuFunction)std::stoi(data.substr(2, 4));
                if (f == MenuFunction::DATA_IN_SELECT)
                {
                    return (AudioInputValue)std::stoi(data.substr(6, 1));
                }
                else throw new BadMenuItemException{ f };
            }

            std::string Menu::SetDATAPTTSelect(PTTSelectValue val)
            {
                std::string s = fmt::format("{:04}{:d}", static_cast<int>(MenuFunction::DATA_PTT_SELECT), static_cast<int>(val));
                return set(s);
            }

            std::string Menu::ReadDATAPTTSelect()
            {
                std::string s = fmt::format("{:04}", static_cast<int>(MenuFunction::DATA_PTT_SELECT));
                return set(s);
            }

            PTTSelectValue Menu::AnswerDATAPTTSelect(std::string data)
            {
                MenuFunction f = (MenuFunction)std::stoi(data.substr(2, 4));
                if (f == MenuFunction::DATA_PTT_SELECT)
                {
                    return (PTTSelectValue)std::stoi(data.substr(6, 1));
                }
                else throw new BadMenuItemException{ f };
            }



            std::string Menu::SetDATAOutLevel(int val)
            {
                val = val < 0 ? 0 : val;
                val = val > 100 ? 100 : val;
                std::string s = fmt::format("{:04}{:03}", static_cast<int>(MenuFunction::DATA_OUT_LEVEL), val);
                return set(s);
            }

            std::string Menu::ReadDATAOutLevel()
            {
                std::string s = fmt::format("{:04}", static_cast<int>(MenuFunction::DATA_OUT_LEVEL));
                return set(s);
            }

            int Menu::AnswerDATAOutLevel(std::string data)
            {
                MenuFunction f = (MenuFunction)std::stoi(data.substr(2, 4));
                if (f == MenuFunction::DATA_OUT_LEVEL)
                {
                    return std::stoi(data.substr(6, 3));
                }
                else throw new BadMenuItemException{ f };
            }

            std::string Menu::SetDATABFO(DataBfoValue val)
            {
                std::string s = fmt::format("{:04}{:d}", static_cast<int>(MenuFunction::DATA_BFO), static_cast<int>(val));
                return set(s);
            }

            std::string Menu::ReadDATABFO()
            {
                std::string s = fmt::format("{:04}", static_cast<int>(MenuFunction::DATA_BFO));
                return set(s);
            }

            DataBfoValue Menu::AnswerDATABFO(std::string data)
            {
                MenuFunction f = (MenuFunction)std::stoi(data.substr(2, 4));
                if (f == MenuFunction::DATA_BFO)
                {
                    return (DataBfoValue)std::stoi(data.substr(6, 1));
                }
                else throw new BadMenuItemException{ f };
            }

            std::string Menu::SetFMMicSelect(AudioInputValue val)
            {
                std::string s = fmt::format("{:04}{:d}", static_cast<int>(MenuFunction::FM_MIC_SELECT), static_cast<int>(val));
                return set(s);
            }

            std::string Menu::ReadFMMicSelect()
            {
                std::string s = fmt::format("{:04}", static_cast<int>(MenuFunction::FM_MIC_SELECT));
                return set(s);
            }

            AudioInputValue Menu::AnswerFMMicSelect(std::string data)
            {
                MenuFunction f = (MenuFunction)std::stoi(data.substr(2, 4));
                if (f == MenuFunction::FM_MIC_SELECT)
                {
                    return (AudioInputValue)std::stoi(data.substr(6, 1));
                }
                else throw new BadMenuItemException{ f };
            }

            std::string Menu::SetFMOutLevel(int val)
            {
                std::string s = fmt::format("{:04}{:03}", static_cast<int>(MenuFunction::FM_OUT_LEVEL), static_cast<int>(val));
                return set(s);
            }

            std::string Menu::ReadFMOutLevel()
            {
                std::string s = fmt::format("{:04}", static_cast<int>(MenuFunction::FM_OUT_LEVEL));
                return set(s);
            }

            int Menu::AnswerFMOutLevel(std::string data)
            {
                MenuFunction f = (MenuFunction)std::stoi(data.substr(2, 4));
                if (f == MenuFunction::FM_OUT_LEVEL)
                {
                    return std::stoi(data.substr(6, 3));
                }
                else throw new BadMenuItemException{ f };
            }

            std::string Menu::SetPktPTTSelect(PTTSelectValue val)
            {
                std::string s = fmt::format("{:04}{:d}", static_cast<int>(MenuFunction::PKT_PTT_SELECT), static_cast<int>(val));
                return set(s);
            }

            std::string Menu::ReadPktPTTSelect()
            {
                std::string s = fmt::format("{:04}", static_cast<int>(MenuFunction::PKT_PTT_SELECT));
                return set(s);
            }

            PTTSelectValue Menu::AnswerPktPTTSelect(std::string data)
            {
                MenuFunction f = (MenuFunction)std::stoi(data.substr(2, 4));
                if (f == MenuFunction::PKT_PTT_SELECT)
                {
                    return (PTTSelectValue)std::stoi(data.substr(6, 1));
                }
                else throw new BadMenuItemException{ f };
            }

            std::string Menu::SetRptShift28MHZ(int val)
            {
                val = val > 1000 ? 1000 : val;
                val = (val % 10) == 0 ? val : val - (val % 10);
                std::string s = fmt::format("{:04}{:04}", static_cast<int>(MenuFunction::RPT_SHIFT_28MHZ), val);
                return set(s);
            }

            std::string Menu::ReadRptShift28MHZ()
            {
                std::string s = fmt::format("{:04}", static_cast<int>(MenuFunction::RPT_SHIFT_28MHZ));
                return set(s);
            }

            int Menu::AnswerRptShift28MHZ(std::string data)
            {
                MenuFunction f = (MenuFunction)std::stoi(data.substr(2, 4));
                if (f == MenuFunction::RPT_SHIFT_28MHZ)
                {
                    return std::stoi(data.substr(6, 4));
                }
                else throw new BadMenuItemException{ f };
            }

            std::string Menu::SetRptShift50MHZ(int val)
            {
                val = val > 4000 ? 4000 : val;
                val = (val % 10) == 0 ? val : val - (val % 10);
                std::string s = fmt::format("{:04}{:04}", static_cast<int>(MenuFunction::RPT_SHIFT_50MHZ), val);
                return set(s);
            }

            std::string Menu::ReadRptShift50MHZ()
            {
                std::string s = fmt::format("{:04}", static_cast<int>(MenuFunction::RPT_SHIFT_50MHZ));
                return set(s);
            }

            int Menu::AnswerRptShift50MHZ(std::string data)
            {
                MenuFunction f = (MenuFunction)std::stoi(data.substr(2, 4));
                if (f == MenuFunction::RPT_SHIFT_50MHZ)
                {
                    return std::stoi(data.substr(6, 4));
                }
                else throw new BadMenuItemException{ f };
            }

            std::string Menu::SetDCSPolarity(DCSPolarityValue val)
            {
                std::string s = fmt::format("{:04}{:d}", static_cast<int>(MenuFunction::DCS_POLARITY), static_cast<int>(val));
                return set(s);
            }

            std::string Menu::ReadDCSPolarity()
            {
                std::string s = fmt::format("{:04}", static_cast<int>(MenuFunction::DCS_POLARITY));
                return set(s);
            }

            DCSPolarityValue Menu::AnswerDCSPolarity(std::string data)
            {
                MenuFunction f = (MenuFunction)std::stoi(data.substr(2, 4));
                if (f == MenuFunction::DCS_POLARITY)
                {
                    return (DCSPolarityValue)std::stoi(data.substr(6, 1));
                }
                else throw new BadMenuItemException{ f };
            }

            std::string Menu::SetRTTYLowCutFreq(FreqLowCutValue val)
            {
                std::string s = fmt::format("{:04}{:02}", static_cast<int>(MenuFunction::RTTY_LCUT_FREQ), static_cast<int>(val));
                return set(s);
            }

            std::string Menu::ReadRTTYLowCutFreq()
            {
                std::string s = fmt::format("{:04}", static_cast<int>(MenuFunction::RTTY_LCUT_FREQ));
                return set(s);
            }

            FreqLowCutValue Menu::AnswerRTTYLowCutFreq(std::string data)
            {
                MenuFunction f = (MenuFunction)std::stoi(data.substr(2, 4));
                if (f == MenuFunction::RTTY_LCUT_FREQ)
                {
                    return (FreqLowCutValue)std::stoi(data.substr(6, 2));
                }
                else throw new BadMenuItemException{ f };
            }

            std::string Menu::SetRTTYLowCutSlope(FreqSlopeValue val)
            {
                std::string s = fmt::format("{:04}{:d}", static_cast<int>(MenuFunction::RTTY_LCUT_SLOPE), static_cast<int>(val));
                return set(s);
            }

            std::string Menu::ReadRTTYLowCutSlope()
            {
                std::string s = fmt::format("{:04}", static_cast<int>(MenuFunction::RTTY_LCUT_SLOPE));
                return set(s);
            }

            FreqSlopeValue Menu::AnswerRTTYLowCutSlope(std::string data)
            {
                MenuFunction f = (MenuFunction)std::stoi(data.substr(2, 4));
                if (f == MenuFunction::RTTY_LCUT_SLOPE)
                {
                    return (FreqSlopeValue)std::stoi(data.substr(6, 1));
                }
                else throw new BadMenuItemException{ f };
            }

            std::string Menu::SetRTTYHighCutFreq(FreqHighCutValue val)
            {
                std::string s = fmt::format("{:04}{:02}", static_cast<int>(MenuFunction::RTTY_HCUT_FREQ), static_cast<int>(val));
                return set(s);
            }

            std::string Menu::ReadRTTYHighCutFreq()
            {
                std::string s = fmt::format("{:04}", static_cast<int>(MenuFunction::RTTY_HCUT_FREQ));
                return set(s);
            }

            FreqHighCutValue Menu::AnswerRTTYHighCutFreq(std::string data)
            {
                MenuFunction f = (MenuFunction)std::stoi(data.substr(2, 4));
                if (f == MenuFunction::RTTY_HCUT_FREQ)
                {
                    return (FreqHighCutValue)std::stoi(data.substr(6, 2));
                }
                else throw new BadMenuItemException{ f };
            }

            std::string Menu::SetRTTYHighCutSlope(FreqSlopeValue val)
            {
                std::string s = fmt::format("{:04}{:d}", static_cast<int>(MenuFunction::RTTY_HCUT_SLOPE), static_cast<int>(val));
                return set(s);
            }

            std::string Menu::ReadRTTYHighCutSlope()
            {
                std::string s = fmt::format("{:04}", static_cast<int>(MenuFunction::RTTY_HCUT_SLOPE));
                return set(s);
            }

            FreqSlopeValue Menu::AnswerRTTYHighCutSlope(std::string data)
            {
                MenuFunction f = (MenuFunction)std::stoi(data.substr(2, 4));
                if (f == MenuFunction::RTTY_HCUT_SLOPE)
                {
                    return (FreqSlopeValue)std::stoi(data.substr(6, 1));
                }
                else throw new BadMenuItemException{ f };
            }

            std::string Menu::SetRTTYShiftPort(RTTYShiftPortValue val)
            {
                std::string s = fmt::format("{:04}{:d}", static_cast<int>(MenuFunction::RTTY_SHIFT_PORT), static_cast<int>(val));
                return set(s);
            }

            std::string Menu::ReadRTTYShiftPort()
            {
                std::string s = fmt::format("{:04}", static_cast<int>(MenuFunction::RTTY_SHIFT_PORT));
                return set(s);
            }

            RTTYShiftPortValue Menu::AnswerRTTYShiftPort(std::string data)
            {
                MenuFunction f = (MenuFunction)std::stoi(data.substr(2, 4));
                if (f == MenuFunction::RTTY_SHIFT_PORT)
                {
                    return (RTTYShiftPortValue)std::stoi(data.substr(6, 1));
                }
                else throw new BadMenuItemException{ f };
            }

            std::string Menu::SetRTTYPolarityR(RTTYPolarityValue val)
            {
                std::string s = fmt::format("{:04}{:d}", static_cast<int>(MenuFunction::RTTY_POLARITY_R), static_cast<int>(val));
                return set(s);
            }

            std::string Menu::ReadRTTYPolarityR()
            {
                std::string s = fmt::format("{:04}", static_cast<int>(MenuFunction::RTTY_POLARITY_R));
                return set(s);
            }

            RTTYPolarityValue Menu::AnswerRTTYPolarityR(std::string data)
            {
                MenuFunction f = (MenuFunction)std::stoi(data.substr(2, 4));
                if (f == MenuFunction::RTTY_POLARITY_R)
                {
                    return (RTTYPolarityValue)std::stoi(data.substr(6, 1));
                }
                else throw new BadMenuItemException{ f };
            }

            std::string Menu::SetRTTYPolarityT(RTTYPolarityValue val)
            {
                std::string s = fmt::format("{:04}{:d}", static_cast<int>(MenuFunction::RTTY_POLARITY_T), static_cast<int>(val));
                return set(s);
            }

            std::string Menu::ReadRTTYPolarityT()
            {
                std::string s = fmt::format("{:04}", static_cast<int>(MenuFunction::RTTY_POLARITY_T));
                return set(s);
            }

            RTTYPolarityValue Menu::AnswerRTTYPolarityT(std::string data)
            {
                MenuFunction f = (MenuFunction)std::stoi(data.substr(2, 4));
                if (f == MenuFunction::RTTY_POLARITY_T)
                {
                    return (RTTYPolarityValue)std::stoi(data.substr(6, 1));
                }
                else throw new BadMenuItemException{ f };
            }

            std::string Menu::SetRTTYOutLevel(int val)
            {
                val = val < 0 ? 0 : val;
                val = val > 100 ? 100 : val;

                std::string s = fmt::format("{:04}{:03}", static_cast<int>(MenuFunction::RTTY_OUT_LEVEL), val);
                return set(s);
            }

            std::string Menu::ReadRTTYOutLevel()
            {
                std::string s = fmt::format("{:04}", static_cast<int>(MenuFunction::RTTY_OUT_LEVEL));
                return set(s);
            }

            int Menu::AnswerRTTYOutLevel(std::string data)
            {
                MenuFunction f = (MenuFunction)std::stoi(data.substr(2, 4));
                if (f == MenuFunction::RTTY_OUT_LEVEL)
                {
                    return std::stoi(data.substr(6, 3));
                }
                else throw new BadMenuItemException{ f };
            }

            std::string Menu::SetRTTYShiftFreq(RTTYShiftFreqValue val)
            {
                std::string s = fmt::format("{:04}{:d}", static_cast<int>(MenuFunction::RTTY_SHIFT_FREQ), static_cast<int>(val));
                return set(s);
            }

            std::string Menu::ReadRTTYShiftFreq()
            {
                std::string s = fmt::format("{:04}", static_cast<int>(MenuFunction::RTTY_SHIFT_FREQ));
                return set(s);
            }

            RTTYShiftFreqValue Menu::AnswerRTTYShiftFreq(std::string data)
            {
                MenuFunction f = (MenuFunction)std::stoi(data.substr(2, 4));
                if (f == MenuFunction::RTTY_SHIFT_FREQ)
                {
                    return (RTTYShiftFreqValue)std::stoi(data.substr(6, 1));
                }
                else throw new BadMenuItemException{ f };
            }

            std::string Menu::SetRTTYMarkFreq(RTTYMarkFreq val)
            {
                std::string s = fmt::format("{:04}{:d}", static_cast<int>(MenuFunction::RTTY_MARK_FREQ), static_cast<int>(val));
                return set(s);
            }

            std::string Menu::ReadRTTYMarkFreq()
            {
                std::string s = fmt::format("{:04}", static_cast<int>(MenuFunction::RTTY_MARK_FREQ));
                return set(s);
            }

            RTTYMarkFreq Menu::AnswerRTTYMarkFreq(std::string data)
            {
                MenuFunction f = (MenuFunction)std::stoi(data.substr(2, 4));
                if (f == MenuFunction::RTTY_MARK_FREQ)
                {
                    return (RTTYMarkFreq)std::stoi(data.substr(6, 1));
                }
                else throw new BadMenuItemException{ f };
            }

            std::string Menu::SetRTTYBFO(DataBfoValue val)
            {
                std::string s = fmt::format("{:04}{:d}", static_cast<int>(MenuFunction::RTTY_BFO), static_cast<int>(val));
                return set(s);
            }

            std::string Menu::ReadRTTYBFO()
            {
                std::string s = fmt::format("{:04}", static_cast<int>(MenuFunction::RTTY_BFO));
                return set(s);
            }

            DataBfoValue Menu::AnswerRTTYBFO(std::string data)
            {
                MenuFunction f = (MenuFunction)std::stoi(data.substr(2, 4));
                if (f == MenuFunction::RTTY_BFO)
                {
                    return (DataBfoValue)std::stoi(data.substr(6, 1));
                }
                else throw new BadMenuItemException{ f };
            }

            std::string Menu::SetSSBLowCutFreq(FreqLowCutValue val)
            {
                std::string s = fmt::format("{:04}{:02}", static_cast<int>(MenuFunction::SSB_LCUT_FREQ), static_cast<int>(val));
                return set(s);
            }

            std::string Menu::ReadSSBLowCutFreq()
            {
                std::string s = fmt::format("{:04}", static_cast<int>(MenuFunction::SSB_LCUT_FREQ));
                return set(s);
            }

            FreqLowCutValue Menu::AnswerSSBLowCutFreq(std::string data)
            {
                MenuFunction f = (MenuFunction)std::stoi(data.substr(2, 4));
                if (f == MenuFunction::SSB_LCUT_FREQ)
                {
                    return (FreqLowCutValue)std::stoi(data.substr(6, 2));
                }
                else throw new BadMenuItemException{ f };
            }

            std::string Menu::SetSSBLowCutSlope(FreqSlopeValue val)
            {
                std::string s = fmt::format("{:04}{:d}", static_cast<int>(MenuFunction::SSB_LCUT_SLOPE), static_cast<int>(val));
                return set(s);
            }

            std::string Menu::ReadSSBLowCutSlope()
            {
                std::string s = fmt::format("{:04}", static_cast<int>(MenuFunction::SSB_LCUT_SLOPE));
                return set(s);
            }

            FreqSlopeValue Menu::AnswerSSBLowCutSlope(std::string data)
            {
                MenuFunction f = (MenuFunction)std::stoi(data.substr(2, 4));
                if (f == MenuFunction::SSB_LCUT_SLOPE)
                {
                    return (FreqSlopeValue)std::stoi(data.substr(6, 1));
                }
                else throw new BadMenuItemException{ f };
            }

            std::string Menu::SetSSBHighCutFreq(FreqHighCutValue val)
            {
                std::string s = fmt::format("{:04}{:02}", static_cast<int>(MenuFunction::SSB_HCUT_FREQ), static_cast<int>(val));
                return set(s);
            }

            std::string Menu::ReadSSBHighCutFreq()
            {
                std::string s = fmt::format("{:04}", static_cast<int>(MenuFunction::SSB_HCUT_FREQ));
                return set(s);
            }

            FreqHighCutValue Menu::AnswerSSBHighCutFreq(std::string data)
            {
                MenuFunction f = (MenuFunction)std::stoi(data.substr(2, 4));
                if (f == MenuFunction::SSB_HCUT_FREQ)
                {
                    return (FreqHighCutValue)std::stoi(data.substr(6, 2));
                }
                else throw new BadMenuItemException{ f };
            }

            std::string Menu::SetSSBHighCutSlope(FreqSlopeValue val)
            {
                std::string s = fmt::format("{:04}{:d}", static_cast<int>(MenuFunction::SSB_HCUT_SLOPE), static_cast<int>(val));
                return set(s);
            }

            std::string Menu::ReadSSBHighCutSlope()
            {
                std::string s = fmt::format("{:04}", static_cast<int>(MenuFunction::SSB_HCUT_SLOPE));
                return set(s);
            }

            FreqSlopeValue Menu::AnswerSSBHighCutSlope(std::string data)
            {
                MenuFunction f = (MenuFunction)std::stoi(data.substr(2, 4));
                if (f == MenuFunction::SSB_HCUT_SLOPE)
                {
                    return (FreqSlopeValue)std::stoi(data.substr(6, 1));
                }
                else throw new BadMenuItemException{ f };
            }

            std::string Menu::SetSSBMicSelect(AudioInputValue val)
            {
                std::string s = fmt::format("{:04}{:d}", static_cast<int>(MenuFunction::SSB_MIC_SELECT), static_cast<int>(val));
                return set(s);
            }

            std::string Menu::ReadSSBMicSelect()
            {
                std::string s = fmt::format("{:04}", static_cast<int>(MenuFunction::SSB_MIC_SELECT));
                return set(s);
            }

            AudioInputValue Menu::AnswerSSBMicSelect(std::string data)
            {
                MenuFunction f = (MenuFunction)std::stoi(data.substr(2, 4));
                if (f == MenuFunction::SSB_MIC_SELECT)
                {
                    return (AudioInputValue)std::stoi(data.substr(6, 1));
                }
                else throw new BadMenuItemException{ f };
            }

            std::string Menu::SetSSBOutLevel(int val)
            {
                val = val < 0 ? 0 : val;
                val = val > 100 ? 100 : val;

                std::string s = fmt::format("{:04}{:03}", static_cast<int>(MenuFunction::SSB_OUT_LEVEL), val);
                return set(s);
            }

            std::string Menu::ReadSSBOutLevel()
            {
                std::string s = fmt::format("{:04}", static_cast<int>(MenuFunction::SSB_OUT_LEVEL));
                return set(s);
            }

            int Menu::AnswerSSBOutLevel(std::string data)
            {
                MenuFunction f = (MenuFunction)std::stoi(data.substr(2, 4));
                if (f == MenuFunction::SSB_OUT_LEVEL)
                {
                    return std::stoi(data.substr(6, 3));
                }
                else throw new BadMenuItemException{ f };
            }

            std::string Menu::SetSSBBFO(BfoValue val)
            {
                std::string s = fmt::format("{:04}{:d}", static_cast<int>(MenuFunction::SSB_BFO), static_cast<int>(val));
                return set(s);
            }

            std::string Menu::ReadSSBBFO()
            {
                std::string s = fmt::format("{:04}", static_cast<int>(MenuFunction::SSB_BFO));
                return set(s);
            }

            BfoValue Menu::AnswerSSBBFO(std::string data)
            {
                MenuFunction f = (MenuFunction)std::stoi(data.substr(2, 4));
                if (f == MenuFunction::SSB_BFO)
                {
                    return (BfoValue)std::stoi(data.substr(6, 1));
                }
                else throw new BadMenuItemException{ f };
            }

            std::string Menu::SetSSBPTTSelect(PTTSelectValue val)
            {
                std::string s = fmt::format("{:04}{:d}", static_cast<int>(MenuFunction::SSB_PTT_SELECT), static_cast<int>(val));
                return set(s);
            }

            std::string Menu::ReadSSBPTTSelect()
            {
                std::string s = fmt::format("{:04}", static_cast<int>(MenuFunction::SSB_PTT_SELECT));
                return set(s);
            }

            PTTSelectValue Menu::AnswerSSBPTTSelect(std::string data)
            {
                MenuFunction f = (MenuFunction)std::stoi(data.substr(2, 4));
                if (f == MenuFunction::SSB_PTT_SELECT)
                {
                    return (PTTSelectValue)std::stoi(data.substr(6, 1));
                }
                else throw new BadMenuItemException{ f };
            }

            std::string Menu::SetSSBTxBPF(SSBTXBandPassValue val)
            {
                std::string s = fmt::format("{:04}{:d}", static_cast<int>(MenuFunction::SSB_TX_BPF), static_cast<int>(val));
                return set(s);
            }

            std::string Menu::ReadSSBTxBPF()
            {
                std::string s = fmt::format("{:04}", static_cast<int>(MenuFunction::SSB_TX_BPF));
                return set(s);
            }

            SSBTXBandPassValue Menu::AnswerSSBTxBPF(std::string data)
            {
                MenuFunction f = (MenuFunction)std::stoi(data.substr(2, 4));
                if (f == MenuFunction::SSB_TX_BPF)
                {
                    return (SSBTXBandPassValue)std::stoi(data.substr(6, 1));
                }
                else throw new BadMenuItemException{ f };
            }

            std::string Menu::SetAPFWidth(APFWidthValue val)
            {
                std::string s = fmt::format("{:04}{:d}", static_cast<int>(MenuFunction::APF_WIDTH), static_cast<int>(val));
                return set(s);
            }

            std::string Menu::ReadAPFWidth()
            {
                std::string s = fmt::format("{:04}", static_cast<int>(MenuFunction::APF_WIDTH));
                return set(s);
            }

            APFWidthValue Menu::AnswerAPFWidth(std::string data)
            {
                MenuFunction f = (MenuFunction)std::stoi(data.substr(2, 4));
                if (f == MenuFunction::APF_WIDTH)
                {
                    return (APFWidthValue)std::stoi(data.substr(6, 1));
                }
                else throw new BadMenuItemException{ f };
            }

            std::string Menu::SetCountourLevel(int val)
            {
                val = val < -40 ? -40 : val;
                val = val > 20 ? 20 : val;
                std::string s = fmt::format("{:04}{:+03}", static_cast<int>(MenuFunction::CONTOUR_LEVEL), val);
                return set(s);
            }

            std::string Menu::ReadCountourLevel()
            {
                std::string s = fmt::format("{:04}", static_cast<int>(MenuFunction::CONTOUR_LEVEL));
                return set(s);
            }

            int Menu::AnswerCountourLevel(std::string data)
            {
                MenuFunction f = (MenuFunction)std::stoi(data.substr(2, 4));
                if (f == MenuFunction::CONTOUR_LEVEL)
                {
                    return std::stoi(data.substr(6, 3));
                }
                else throw new BadMenuItemException{ f };
            }

            std::string Menu::SetCountourWidth(int val)
            {
                val = val < 1 ? 1 : val;
                val = val > 11 ? 11 : val;
                std::string s = fmt::format("{:04}{:02}", static_cast<int>(MenuFunction::CONTOUR_WIDTH), val);
                return set(s);
            }

            std::string Menu::ReadCountourWidth()
            {
                std::string s = fmt::format("{:04}", static_cast<int>(MenuFunction::CONTOUR_WIDTH));
                return set(s);
            }

            int Menu::AnswerCountourWidth(std::string data)
            {
                MenuFunction f = (MenuFunction)std::stoi(data.substr(2, 4));
                if (f == MenuFunction::CONTOUR_WIDTH)
                {
                    return std::stoi(data.substr(6, 2));
                }
                else throw new BadMenuItemException{ f };
            }

            std::string Menu::SetIFNotchWidth(IFNotchWidthValue val)
            {
                std::string s = fmt::format("{:04}{:d}", static_cast<int>(MenuFunction::IF_NOTCH_WIDTH), static_cast<int>(val));
                return set(s);
            }

            std::string Menu::ReadIFNotchWidth()
            {
                std::string s = fmt::format("{:04}", static_cast<int>(MenuFunction::IF_NOTCH_WIDTH));
                return set(s);
            }

            IFNotchWidthValue Menu::AnswerIFNotchWidth(std::string data)
            {
                MenuFunction f = (MenuFunction)std::stoi(data.substr(2, 4));
                if (f == MenuFunction::IF_NOTCH_WIDTH)
                {
                    return (IFNotchWidthValue)std::stoi(data.substr(6, 2));
                }
                else throw new BadMenuItemException{ f };
            }

            std::string Menu::SetSCPStartCycle(SCPStartCycleValue val)
            {
                std::string s = fmt::format("{:04}{:d}", static_cast<int>(MenuFunction::SCP_START_CYCLE), static_cast<int>(val));
                return set(s);
            }

            std::string Menu::ReadSCPStartCycle()
            {
                std::string s = fmt::format("{:04}", static_cast<int>(MenuFunction::SCP_START_CYCLE));
                return set(s);
            }

            SCPStartCycleValue Menu::AnswerSCPStartCycle(std::string data)
            {
                MenuFunction f = (MenuFunction)std::stoi(data.substr(2, 4));
                if (f == MenuFunction::SCP_START_CYCLE)
                {
                    return (SCPStartCycleValue)std::stoi(data.substr(6, 1));
                }
                else throw new BadMenuItemException{ f };
            }

            std::string Menu::SetSCPSpanFreq(SCPSpanFreqValue val)
            {
                std::string s = fmt::format("{:04}{:d}", static_cast<int>(MenuFunction::SCP_SPAN_FREQ), static_cast<int>(val));
                return set(s);
            }

            std::string Menu::ReadSCPSpanFreq()
            {
                std::string s = fmt::format("{:04}", static_cast<int>(MenuFunction::SCP_SPAN_FREQ));
                return set(s);
            }

            SCPSpanFreqValue Menu::AnswerSCPSpanFreq(std::string data)
            {
                MenuFunction f = (MenuFunction)std::stoi(data.substr(2, 4));
                if (f == MenuFunction::SCP_SPAN_FREQ)
                {
                    return (SCPSpanFreqValue)std::stoi(data.substr(6, 1));
                }
                else throw new BadMenuItemException{ f };
            }

            std::string Menu::SetQuickDial(QuickDialValue val)
            {
                std::string s = fmt::format("{:04}{:d}", static_cast<int>(MenuFunction::QUICK_DIAL), static_cast<int>(val));
                return set(s);
            }

            std::string Menu::ReadQuickDial()
            {
                std::string s = fmt::format("{:04}", static_cast<int>(MenuFunction::QUICK_DIAL));
                return set(s);
            }

            QuickDialValue Menu::AnswerQuickDial(std::string data)
            {
                MenuFunction f = (MenuFunction)std::stoi(data.substr(2, 4));
                if (f == MenuFunction::QUICK_DIAL)
                {
                    return (QuickDialValue)std::stoi(data.substr(6, 1));
                }
                else throw new BadMenuItemException{ f };
            }

            std::string Menu::SetAMDialStep(AMDialStep val)
            {
                std::string s = fmt::format("{:04}{:d}", static_cast<int>(MenuFunction::AM_DIAL_STEP), static_cast<int>(val));
                return set(s);
            }

            std::string Menu::ReadAMDialStep()
            {
                std::string s = fmt::format("{:04}", static_cast<int>(MenuFunction::AM_DIAL_STEP));
                return set(s);
            }

            AMDialStep Menu::AnswerAMDialStep(std::string data)
            {
                MenuFunction f = (MenuFunction)std::stoi(data.substr(2, 4));
                if (f == MenuFunction::AM_DIAL_STEP)
                {
                    return (AMDialStep)std::stoi(data.substr(6, 1));
                }
                else throw new BadMenuItemException{ f };
            }

            std::string Menu::SetSSBDialStep(SSBDialStep val)
            {
                std::string s = fmt::format("{:04}{:d}", static_cast<int>(MenuFunction::SSB_DIAL_STEP), static_cast<int>(val));
                return set(s);
            }

            std::string Menu::ReadSSBDialStep()
            {
                std::string s = fmt::format("{:04}", static_cast<int>(MenuFunction::SSB_DIAL_STEP));
                return set(s);
            }

            SSBDialStep Menu::AnswerSSBDialStep(std::string data)
            {
                MenuFunction f = (MenuFunction)std::stoi(data.substr(2, 4));
                if (f == MenuFunction::SSB_DIAL_STEP)
                {
                    return (SSBDialStep)std::stoi(data.substr(6, 1));
                }
                else throw new BadMenuItemException{ f };
            }

            std::string Menu::SetFMDialStep(FMDialStep val)
            {
                std::string s = fmt::format("{:04}{:d}", static_cast<int>(MenuFunction::FM_DIAL_STEP), static_cast<int>(val));
                return set(s);
            }

            std::string Menu::ReadFMDialStep()
            {
                std::string s = fmt::format("{:04}", static_cast<int>(MenuFunction::FM_DIAL_STEP));
                return set(s);
            }

            FMDialStep Menu::AnswerFMDialStep(std::string data)
            {
                MenuFunction f = (MenuFunction)std::stoi(data.substr(2, 4));
                if (f == MenuFunction::FM_DIAL_STEP)
                {
                    return (FMDialStep)std::stoi(data.substr(6, 1));
                }
                else throw new BadMenuItemException{ f };
            }

            std::string Menu::SetDialStep(DialStep val)
            {
                std::string s = fmt::format("{:04}{:d}", static_cast<int>(MenuFunction::DIAL_STEP), static_cast<int>(val));
                return set(s);
            }

            std::string Menu::ReadDialStep()
            {
                std::string s = fmt::format("{:04}", static_cast<int>(MenuFunction::DIAL_STEP));
                return set(s);
            }

            DialStep Menu::AnswerDialStep(std::string data)
            {
                MenuFunction f = (MenuFunction)std::stoi(data.substr(2, 4));
                if (f == MenuFunction::DIAL_STEP)
                {
                    return (DialStep)std::stoi(data.substr(6, 1));
                }
                else throw new BadMenuItemException{ f };
            }

            std::string Menu::SetAmChStep(AMChannelStepValue val)
            {
                std::string s = fmt::format("{:04}{:d}", static_cast<int>(MenuFunction::AM_CH_STEP), static_cast<int>(val));
                return set(s);
            }

            std::string Menu::ReadAmChStep()
            {
                std::string s = fmt::format("{:04}", static_cast<int>(MenuFunction::AM_CH_STEP));
                return set(s);
            }

            AMChannelStepValue Menu::AnswerAmChStep(std::string data)
            {
                MenuFunction f = (MenuFunction)std::stoi(data.substr(2, 4));
                if (f == MenuFunction::AM_CH_STEP)
                {
                    return (AMChannelStepValue)std::stoi(data.substr(6, 1));
                }
                else throw new BadMenuItemException{ f };
            }

            std::string Menu::SetFmChStep(FMChannelStepValue val)
            {
                std::string s = fmt::format("{:04}{:d}", static_cast<int>(MenuFunction::FM_CH_STEP), static_cast<int>(val));
                return set(s);
            }

            std::string Menu::ReadFmChStep()
            {
                std::string s = fmt::format("{:04}", static_cast<int>(MenuFunction::FM_CH_STEP));
                return set(s);
            }

            FMChannelStepValue Menu::AnswerFmChStep(std::string data)
            {
                MenuFunction f = (MenuFunction)std::stoi(data.substr(2, 4));
                if (f == MenuFunction::FM_CH_STEP)
                {
                    return (FMChannelStepValue)std::stoi(data.substr(6, 1));
                }
                else throw new BadMenuItemException{ f };
            }

            std::string Menu::SetEQ1Freq(EQ1FreqValue val)
            {
                std::string s = fmt::format("{:04}{:02}", static_cast<int>(MenuFunction::EQ1_FREQ), static_cast<int>(val));
                return set(s);
            }

            std::string Menu::ReadEQ1Freq()
            {
                std::string s = fmt::format("{:04}", static_cast<int>(MenuFunction::EQ1_FREQ));
                return set(s);
            }

            EQ1FreqValue Menu::AnswerEQ1Freq(std::string data)
            {
                MenuFunction f = (MenuFunction)std::stoi(data.substr(2, 4));
                if (f == MenuFunction::EQ1_FREQ)
                {
                    return (EQ1FreqValue)std::stoi(data.substr(6, 2));
                }
                else throw new BadMenuItemException{ f };
            }

            std::string Menu::SetEQ1Level(int val)
            {
                val = val < -20 ? -20 : val;
                val = val > 20 ? 20 : val;

                std::string s = fmt::format("{:04}{:+03}", static_cast<int>(MenuFunction::EQ1_LEVEL), val);
                return set(s);
            }

            std::string Menu::ReadEQ1Level()
            {
                std::string s = fmt::format("{:04}", static_cast<int>(MenuFunction::EQ1_LEVEL));
                return set(s);
            }

            int Menu::AnswerEQ1Level(std::string data)
            {
                MenuFunction f = (MenuFunction)std::stoi(data.substr(2, 4));
                if (f == MenuFunction::EQ1_LEVEL)
                {
                    return std::stoi(data.substr(6, 3));
                }
                else throw new BadMenuItemException{ f };
            }

            std::string Menu::SetEQ1Bwth(int val)
            {
                val = val < 1 ? 1 : val;
                val = val > 10 ? 10 : val;

                std::string s = fmt::format("{:04}{:02}", static_cast<int>(MenuFunction::EQ1_BWTH), static_cast<int>(val));
                return set(s);
            }

            std::string Menu::ReadEQ1Bwth()
            {
                std::string s = fmt::format("{:04}", static_cast<int>(MenuFunction::EQ1_BWTH));
                return set(s);
            }

            int Menu::AnswerEQ1Bwth(std::string data)
            {
                MenuFunction f = (MenuFunction)std::stoi(data.substr(2, 4));
                if (f == MenuFunction::EQ1_BWTH)
                {
                    return std::stoi(data.substr(6, 2));
                }
                else throw new BadMenuItemException{ f };
            }

            std::string Menu::SetEQ2Freq(EQ2FreqValue val)
            {
                std::string s = fmt::format("{:04}{:02}", static_cast<int>(MenuFunction::EQ2_FREQ), static_cast<int>(val));
                return set(s);
            }

            std::string Menu::ReadEQ2Freq()
            {
                std::string s = fmt::format("{:04}", static_cast<int>(MenuFunction::EQ2_FREQ));
                return set(s);
            }

            EQ2FreqValue Menu::AnswerEQ2Freq(std::string data)
            {
                MenuFunction f = (MenuFunction)std::stoi(data.substr(2, 4));
                if (f == MenuFunction::EQ2_FREQ)
                {
                    return (EQ2FreqValue)std::stoi(data.substr(6, 2));
                }
                else throw new BadMenuItemException{ f };
            }

            std::string Menu::SetEQ2Level(int val)
            {
                val = val < -20 ? -20 : val;
                val = val > 20 ? 20 : val;

                std::string s = fmt::format("{:04}{:+03}", static_cast<int>(MenuFunction::EQ2_LEVEL), static_cast<int>(val));
                return set(s);
            }

            std::string Menu::ReadEQ2Level()
            {
                std::string s = fmt::format("{:04}", static_cast<int>(MenuFunction::EQ2_LEVEL));
                return set(s);
            }

            int Menu::AnswerEQ2Level(std::string data)
            {
                MenuFunction f = (MenuFunction)std::stoi(data.substr(2, 4));
                if (f == MenuFunction::EQ2_LEVEL)
                {
                    return std::stoi(data.substr(6, 3));
                }
                else throw new BadMenuItemException{ f };
            }

            std::string Menu::SetEQ2Bwth(int val)
            {
                val = val < 1 ? 1 : val;
                val = val > 10 ? 10 : val;

                std::string s = fmt::format("{:04}{:+02}", static_cast<int>(MenuFunction::EQ2_BWTH), static_cast<int>(val));
                return set(s);
            }

            std::string Menu::ReadEQ2Bwth()
            {
                std::string s = fmt::format("{:04}", static_cast<int>(MenuFunction::EQ2_BWTH));
                return set(s);
            }

            int Menu::AnswerEQ2Bwth(std::string data)
            {
                MenuFunction f = (MenuFunction)std::stoi(data.substr(2, 4));
                if (f == MenuFunction::EQ2_BWTH)
                {
                    return std::stoi(data.substr(6, 2));
                }
                else throw new BadMenuItemException{ f };
            }

            std::string Menu::SetEQ3Freq(EQ3FreqValue val)
            {
                std::string s = fmt::format("{:04}{:02}", static_cast<int>(MenuFunction::EQ3_FREQ), static_cast<int>(val));
                return set(s);
            }

            std::string Menu::ReadEQ3Freq()
            {
                std::string s = fmt::format("{:04}", static_cast<int>(MenuFunction::EQ3_FREQ));
                return set(s);
            }

            EQ3FreqValue Menu::AnswerEQ3Freq(std::string data)
            {
                MenuFunction f = (MenuFunction)std::stoi(data.substr(2, 4));
                if (f == MenuFunction::EQ3_FREQ)
                {
                    return (EQ3FreqValue)std::stoi(data.substr(6, 2));
                }
                else throw new BadMenuItemException{ f };
            }

            std::string Menu::SetEQ3Level(int val)
            {
                val = val < -20 ? -20 : val;
                val = val > 20 ? 20 : val;

                std::string s = fmt::format("{:04}{:+03}", static_cast<int>(MenuFunction::EQ3_LEVEL), static_cast<int>(val));
                return set(s);
            }

            std::string Menu::ReadEQ3Level()
            {
                std::string s = fmt::format("{:04}", static_cast<int>(MenuFunction::EQ3_LEVEL));
                return set(s);
            }

            int Menu::AnswerEQ3Level(std::string data)
            {
                MenuFunction f = (MenuFunction)std::stoi(data.substr(2, 4));
                if (f == MenuFunction::EQ3_LEVEL)
                {
                    return std::stoi(data.substr(6, 3));
                }
                else throw new BadMenuItemException{ f };
            }

            std::string Menu::SetEQ3Bwth(int val)
            {
                val = val < 1 ? 1 : val;
                val = val > 10 ? 10 : val;

                std::string s = fmt::format("{:04}{:+02}", static_cast<int>(MenuFunction::EQ3_BWTH), val);
                return set(s);
            }

            std::string Menu::ReadEQ3Bwth()
            {
                std::string s = fmt::format("{:04}", static_cast<int>(MenuFunction::EQ3_BWTH));
                return set(s);
            }

            int Menu::AnswerEQ3Bwth(std::string data)
            {
                MenuFunction f = (MenuFunction)std::stoi(data.substr(2, 4));
                if (f == MenuFunction::EQ3_BWTH)
                {
                    return std::stoi(data.substr(6, 2));
                }
                else throw new BadMenuItemException{ f };
            }


            std::string Menu::SetPEQ1Freq(EQ1FreqValue val)
            {
                std::string s = fmt::format("{:04}{:02}", static_cast<int>(MenuFunction::P_EQ1_FREQ), static_cast<int>(val));
                return set(s);
            }

            std::string Menu::ReadPEQ1Freq()
            {
                std::string s = fmt::format("{:04}", static_cast<int>(MenuFunction::P_EQ1_FREQ));
                return set(s);
            }

            EQ1FreqValue Menu::AnswerPEQ1Freq(std::string data)
            {
                MenuFunction f = (MenuFunction)std::stoi(data.substr(2, 4));
                if (f == MenuFunction::P_EQ1_FREQ)
                {
                    return (EQ1FreqValue)std::stoi(data.substr(6, 2));
                }
                else throw new BadMenuItemException{ f };
            }

            std::string Menu::SetPEQ1Level(int val)
            {
                val = val < -20 ? -20 : val;
                val = val > 20 ? 20 : val;

                std::string s = fmt::format("{:04}{:+03}", static_cast<int>(MenuFunction::P_EQ1_LEVEL), static_cast<int>(val));
                return set(s);
            }

            std::string Menu::ReadPEQ1Level()
            {
                std::string s = fmt::format("{:04}", static_cast<int>(MenuFunction::P_EQ1_LEVEL));
                return set(s);
            }

            int Menu::AnswerPEQ1Level(std::string data)
            {
                MenuFunction f = (MenuFunction)std::stoi(data.substr(2, 4));
                if (f == MenuFunction::P_EQ1_LEVEL)
                {
                    return std::stoi(data.substr(6, 3));
                }
                else throw new BadMenuItemException{ f };
            }

            std::string Menu::SetPEQ1Bwth(int val)
            {
                val = val < 1 ? 1 : val;
                val = val > 10 ? 10 : val;

                std::string s = fmt::format("{:04}{:+02}", static_cast<int>(MenuFunction::P_EQ1_BWTH), val);
                return set(s);
            }

            std::string Menu::ReadPEQ1Bwth()
            {
                std::string s = fmt::format("{:04}", static_cast<int>(MenuFunction::P_EQ1_BWTH));
                return set(s);
            }

            int Menu::AnswerPEQ1Bwth(std::string data)
            {
                MenuFunction f = (MenuFunction)std::stoi(data.substr(2, 4));
                if (f == MenuFunction::P_EQ1_BWTH)
                {
                    return std::stoi(data.substr(6, 2));
                }
                else throw new BadMenuItemException{ f };
            }

            std::string Menu::SetPEQ2Freq(EQ2FreqValue val)
            {
                std::string s = fmt::format("{:04}{:02}", static_cast<int>(MenuFunction::P_EQ2_FREQ), static_cast<int>(val));
                return set(s);
            }

            std::string Menu::ReadPEQ2Freq()
            {
                std::string s = fmt::format("{:04}", static_cast<int>(MenuFunction::P_EQ2_FREQ));
                return set(s);
            }

            EQ2FreqValue Menu::AnswerPEQ2Freq(std::string data)
            {
                MenuFunction f = (MenuFunction)std::stoi(data.substr(2, 4));
                if (f == MenuFunction::P_EQ2_FREQ)
                {
                    return (EQ2FreqValue)std::stoi(data.substr(6, 2));
                }
                else throw new BadMenuItemException{ f };
            }

            std::string Menu::SetPEQ2Level(int val)
            {
                val = val < -20 ? -20 : val;
                val = val > 20 ? 20 : val;

                std::string s = fmt::format("{:04}{:+03}", static_cast<int>(MenuFunction::P_EQ2_LEVEL), val);
                return set(s);
            }

            std::string Menu::ReadPEQ2Level()
            {
                std::string s = fmt::format("{:04}", static_cast<int>(MenuFunction::P_EQ2_LEVEL));
                return set(s);
            }

            int Menu::AnswerPEQ2Level(std::string data)
            {
                MenuFunction f = (MenuFunction)std::stoi(data.substr(2, 4));
                if (f == MenuFunction::P_EQ2_LEVEL)
                {
                    return std::stoi(data.substr(6, 3));
                }
                else throw new BadMenuItemException{ f };
            }

            std::string Menu::SetPEQ2Bwth(int val)
            {
                val = val < 1 ? 1 : val;
                val = val > 10 ? 10 : val;

                std::string s = fmt::format("{:04}{:+02}", static_cast<int>(MenuFunction::P_EQ2_BWTH), val);
                return set(s);
            }

            std::string Menu::ReadPEQ2Bwth()
            {
                std::string s = fmt::format("{:04}", static_cast<int>(MenuFunction::P_EQ2_BWTH));
                return set(s);
            }

            int Menu::AnswerPEQ2Bwth(std::string data)
            {
                MenuFunction f = (MenuFunction)std::stoi(data.substr(2, 4));
                if (f == MenuFunction::P_EQ2_BWTH)
                {
                    return std::stoi(data.substr(6, 2));
                }
                else throw new BadMenuItemException{ f };
            }

            std::string Menu::SetPEQ3Freq(EQ3FreqValue val)
            {
                std::string s = fmt::format("{:04}{:02}", static_cast<int>(MenuFunction::P_EQ3_FREQ), static_cast<int>(val));
                return set(s);
            }

            std::string Menu::ReadPEQ3Freq()
            {
                std::string s = fmt::format("{:04}", static_cast<int>(MenuFunction::P_EQ3_FREQ));
                return set(s);
            }

            EQ3FreqValue Menu::AnswerPEQ3Freq(std::string data)
            {
                MenuFunction f = (MenuFunction)std::stoi(data.substr(2, 4));
                if (f == MenuFunction::P_EQ3_FREQ)
                {
                    return (EQ3FreqValue)std::stoi(data.substr(6, 2));
                }
                else throw new BadMenuItemException{ f };
            }

            std::string Menu::SetPEQ3Level(int val)
            {
                val = val < -20 ? -20 : val;
                val = val > 20 ? 20 : val;

                std::string s = fmt::format("{:04}{:+03}", static_cast<int>(MenuFunction::P_EQ3_LEVEL), val);
                return set(s);
            }

            std::string Menu::ReadPEQ3Level()
            {
                std::string s = fmt::format("{:04}", static_cast<int>(MenuFunction::P_EQ3_LEVEL));
                return set(s);
            }

            int Menu::AnswerPEQ3Level(std::string data)
            {
                MenuFunction f = (MenuFunction)std::stoi(data.substr(2, 4));
                if (f == MenuFunction::P_EQ3_LEVEL)
                {
                    return std::stoi(data.substr(6, 3));
                }
                else throw new BadMenuItemException{ f };
            }

            std::string Menu::SetPEQ3Bwth(int val)
            {
                val = val < 1 ? 1 : val;
                val = val > 10 ? 10 : val;

                std::string s = fmt::format("{:04}{:02}", static_cast<int>(MenuFunction::P_EQ3_BWTH), val);
                return set(s);
            }

            std::string Menu::ReadPEQ3Bwth()
            {
                std::string s = fmt::format("{:04}", static_cast<int>(MenuFunction::P_EQ3_BWTH));
                return set(s);
            }

            int Menu::AnswerPEQ3Bwth(std::string data)
            {
                MenuFunction f = (MenuFunction)std::stoi(data.substr(2, 4));
                if (f == MenuFunction::P_EQ3_BWTH)
                {
                    return std::stoi(data.substr(6, 2));
                }
                else throw new BadMenuItemException{ f };
            }

            std::string Menu::SetHfSsbPwr(int val)
            {
                val = val < 5 ? 5 : val;
                val = val > 100 ? 100 : val;
                std::string s = fmt::format("{:04}{:03}", static_cast<int>(MenuFunction::HF_SSB_PWR), val);
                return set(s);
            }

            std::string Menu::ReadHfSsbPwr()
            {
                std::string s = fmt::format("{:04}", static_cast<int>(MenuFunction::HF_SSB_PWR));
                return set(s);
            }

            int Menu::AnswerHfSsbPwr(std::string data)
            {
                MenuFunction f = (MenuFunction)std::stoi(data.substr(2, 4));
                if (f == MenuFunction::HF_SSB_PWR)
                {
                    return std::stoi(data.substr(6, 3));
                }
                else throw new BadMenuItemException{ f };
            }

            std::string Menu::SetHfAmPwr(int val)
            {
                val = val < 5 ? 5 : val;
                val = val > 40 ? 40 : val;
                std::string s = fmt::format("{:04}{:03}", static_cast<int>(MenuFunction::HF_AM_PWR), val);
                return set(s);
            }

            std::string Menu::ReadHfAmPwr()
            {
                std::string s = fmt::format("{:04}", static_cast<int>(MenuFunction::HF_AM_PWR));
                return set(s);
            }

            int Menu::AnswerHfAmPwr(std::string data)
            {
                MenuFunction f = (MenuFunction)std::stoi(data.substr(2, 4));
                if (f == MenuFunction::HF_AM_PWR)
                {
                    return std::stoi(data.substr(6, 3));
                }
                else throw new BadMenuItemException{ f };
            }

            std::string Menu::SetHfPwr(int val)
            {
                val = val < 5 ? 5 : val;
                val = val > 100 ? 100 : val;
                std::string s = fmt::format("{:04}{:03}", static_cast<int>(MenuFunction::HF_PWR), val);
                return set(s);
            }

            std::string Menu::ReadHfPwr()
            {
                std::string s = fmt::format("{:04}", static_cast<int>(MenuFunction::HF_PWR));
                return set(s);
            }

            int Menu::AnswerHfPwr(std::string data)
            {
                MenuFunction f = (MenuFunction)std::stoi(data.substr(2, 4));
                if (f == MenuFunction::HF_PWR)
                {
                    return std::stoi(data.substr(6, 3));
                }
                else throw new BadMenuItemException{ f };
            }

            std::string Menu::Set50mSsbPwr(int val)
            {
                val = val < 5 ? 5 : val;
                val = val > 100 ? 100 : val;
                std::string s = fmt::format("{:04}{:03}", static_cast<int>(MenuFunction::SSB_POWER_50M), val);
                return set(s);
            }

            std::string Menu::Read50mSsbPwr()
            {
                std::string s = fmt::format("{:04}", static_cast<int>(MenuFunction::SSB_POWER_50M));
                return set(s);
            }

            int Menu::Answer50mSsbPwr(std::string data)
            {
                MenuFunction f = (MenuFunction)std::stoi(data.substr(2, 4));
                if (f == MenuFunction::SSB_POWER_50M)
                {
                    return std::stoi(data.substr(6, 3));
                }
                else throw new BadMenuItemException{ f };
            }

            std::string Menu::Set50mAmPwr(int val)
            {
                val = val < 5 ? 5 : val;
                val = val > 40 ? 40 : val;
                std::string s = fmt::format("{:04}{:03}", static_cast<int>(MenuFunction::AM_POWER_50M), val);
                return set(s);
            }

            std::string Menu::Read50mAmPwr()
            {
                std::string s = fmt::format("{:04}", static_cast<int>(MenuFunction::AM_POWER_50M));
                return set(s);
            }

            int Menu::Answer50mAmPwr(std::string data)
            {
                MenuFunction f = (MenuFunction)std::stoi(data.substr(2, 4));
                if (f == MenuFunction::AM_POWER_50M)
                {
                    return std::stoi(data.substr(6, 3));
                }
                else throw new BadMenuItemException{ f };
            }

            std::string Menu::Set50mPwr(int val)
            {
                val = val < 5 ? 5 : val;
                val = val > 100 ? 100 : val;
                std::string s = fmt::format("{:04}{:03}", static_cast<int>(MenuFunction::VHF_PWR), val);
                return set(s);
            }

            std::string Menu::Read50mPwr()
            {
                std::string s = fmt::format("{:04}", static_cast<int>(MenuFunction::VHF_PWR));
                return set(s);
            }

            int Menu::Answer50mPwr(std::string data)
            {
                MenuFunction f = (MenuFunction)std::stoi(data.substr(2, 4));
                if (f == MenuFunction::VHF_PWR)
                {
                    return std::stoi(data.substr(6, 3));
                }
                else throw new BadMenuItemException{ f };
            }

            std::string Menu::SetSSBMicGain(int val)
            {
                val = val < 0 ? 0 : val;
                val = val > 100 ? 100 : val;
                std::string s = fmt::format("{:04}{:03}", static_cast<int>(MenuFunction::SSB_MIC_GAIN), val);
                return set(s);
            }

            std::string Menu::ReadSSBMicGain()
            {
                std::string s = fmt::format("{:04}", static_cast<int>(MenuFunction::SSB_MIC_GAIN));
                return set(s);
            }

            int Menu::AnswerSSBMicGain(std::string data)
            {
                MenuFunction f = (MenuFunction)std::stoi(data.substr(2, 4));
                if (f == MenuFunction::SSB_MIC_GAIN)
                {
                    return std::stoi(data.substr(6, 3));
                }
                else throw new BadMenuItemException{ f };
            }

            std::string Menu::SetAMMicGain(int val)
            {
                val = val < 0 ? 0 : val;
                val = val > 100 ? 100 : val;
                std::string s = fmt::format("{:04}{:03}", static_cast<int>(MenuFunction::AM_MIC_GAIN), val);
                return set(s);
            }

            std::string Menu::ReadAMMicGain()
            {
                std::string s = fmt::format("{:04}", static_cast<int>(MenuFunction::AM_MIC_GAIN));
                return set(s);
            }

            int Menu::AnswerAMMicGain(std::string data)
            {
                MenuFunction f = (MenuFunction)std::stoi(data.substr(2, 4));
                if (f == MenuFunction::AM_MIC_GAIN)
                {
                    return std::stoi(data.substr(6, 3));
                }
                else throw new BadMenuItemException{ f };
            }

            std::string Menu::SetFMMicGain(int val)
            {
                val = val < 0 ? 0 : val;
                val = val > 100 ? 100 : val;
                std::string s = fmt::format("{:04}{:03}", static_cast<int>(MenuFunction::FM_MIC_GAIN), val);
                return set(s);
            }

            std::string Menu::ReadFMMicGain()
            {
                std::string s = fmt::format("{:04}", static_cast<int>(MenuFunction::FM_MIC_GAIN));
                return set(s);
            }

            int Menu::AnswerFMMicGain(std::string data)
            {
                MenuFunction f = (MenuFunction)std::stoi(data.substr(2, 4));
                if (f == MenuFunction::FM_MIC_GAIN)
                {
                    return std::stoi(data.substr(6, 3));
                }
                else throw new BadMenuItemException{ f };
            }

            std::string Menu::SetDATAMicGain(int val)
            {
                val = val < 0 ? 0 : val;
                val = val > 100 ? 100 : val;
                std::string s = fmt::format("{:04}{:03}", static_cast<int>(MenuFunction::DATA_MIC_GAIN), val);
                return set(s);
            }

            std::string Menu::ReadDATAMicGain()
            {
                std::string s = fmt::format("{:04}", static_cast<int>(MenuFunction::DATA_MIC_GAIN));
                return set(s);
            }

            int Menu::AnswerDATAMicGain(std::string data)
            {
                MenuFunction f = (MenuFunction)std::stoi(data.substr(2, 4));
                if (f == MenuFunction::DATA_MIC_GAIN)
                {
                    return std::stoi(data.substr(6, 3));
                }
                else throw new BadMenuItemException{ f };
            }

            std::string Menu::SetSSBDataGain(int val)
            {
                val = val < 0 ? 0 : val;
                val = val > 100 ? 100 : val;
                std::string s = fmt::format("{:04}{:03}", static_cast<int>(MenuFunction::SSB_DATA_GAIN), val);
                return set(s);
            }

            std::string Menu::ReadSSBDataGain()
            {
                std::string s = fmt::format("{:04}", static_cast<int>(MenuFunction::SSB_DATA_GAIN));
                return set(s);
            }

            int Menu::AnswerSSBDataGain(std::string data)
            {
                MenuFunction f = (MenuFunction)std::stoi(data.substr(2, 4));
                if (f == MenuFunction::SSB_DATA_GAIN)
                {
                    return std::stoi(data.substr(6, 3));
                }
                else throw new BadMenuItemException{ f };
            }

            std::string Menu::SetAMDataGain(int val)
            {
                val = val < 0 ? 0 : val;
                val = val > 100 ? 100 : val;
                std::string s = fmt::format("{:04}{:03}", static_cast<int>(MenuFunction::AM_DATA_GAIN), val);
                return set(s);
            }

            std::string Menu::ReadAMDataGain()
            {
                std::string s = fmt::format("{:04}", static_cast<int>(MenuFunction::AM_DATA_GAIN));
                return set(s);
            }

            int Menu::AnswerAMDataGain(std::string data)
            {
                MenuFunction f = (MenuFunction)std::stoi(data.substr(2, 4));
                if (f == MenuFunction::AM_DATA_GAIN)
                {
                    return std::stoi(data.substr(6, 3));
                }
                else throw new BadMenuItemException{ f };
            }

            std::string Menu::SetFMDataGain(int val)
            {
                val = val < 0 ? 0 : val;
                val = val > 100 ? 100 : val;
                std::string s = fmt::format("{:04}{:03}", static_cast<int>(MenuFunction::FM_DATA_GAIN), val);
                return set(s);
            }

            std::string Menu::ReadFMDataGain()
            {
                std::string s = fmt::format("{:04}", static_cast<int>(MenuFunction::FM_DATA_GAIN));
                return set(s);
            }

            int Menu::AnswerFMDataGain(std::string data)
            {
                MenuFunction f = (MenuFunction)std::stoi(data.substr(2, 4));
                if (f == MenuFunction::FM_DATA_GAIN)
                {
                    return std::stoi(data.substr(6, 3));
                }
                else throw new BadMenuItemException{ f };
            }

            std::string Menu::SetDataDataGain(int val)
            {
                val = val < 0 ? 0 : val;
                val = val > 100 ? 100 : val;
                std::string s = fmt::format("{:04}{:03}", static_cast<int>(MenuFunction::DATA_GAIN), val);
                return set(s);
            }

            std::string Menu::ReadDataDataGain()
            {
                std::string s = fmt::format("{:04}", static_cast<int>(MenuFunction::DATA_GAIN));
                return set(s);
            }

            int Menu::AnswerDataDataGain(std::string data)
            {
                MenuFunction f = (MenuFunction)std::stoi(data.substr(2, 4));
                if (f == MenuFunction::DATA_GAIN)
                {
                    return std::stoi(data.substr(6, 3));
                }
                else throw new BadMenuItemException{ f };
            }

            std::string Menu::SetTunerSelect(TunerSelectValue val)
            {
                std::string s = fmt::format("{:04}{:d}", static_cast<int>(MenuFunction::TUNER_SELECT), static_cast<int>(val));
                return set(s);
            }

            std::string Menu::ReadTunerSelect()
            {
                std::string s = fmt::format("{:04}", static_cast<int>(MenuFunction::TUNER_SELECT));
                return set(s);
            }

            TunerSelectValue Menu::AnswerTunerSelect(std::string data)
            {
                MenuFunction f = (MenuFunction)std::stoi(data.substr(2, 4));
                if (f == MenuFunction::TUNER_SELECT)
                {
                    return (TunerSelectValue)std::stoi(data.substr(6, 1));
                }
                else throw new BadMenuItemException{ f };
            }

            std::string Menu::SetVoxSelect(VoxSelectValue val)
            {
                std::string s = fmt::format("{:04}{:d}", static_cast<int>(MenuFunction::VOX_SELECT), static_cast<int>(val));
                return set(s);
            }

            std::string Menu::ReadVoxSelect()
            {
                std::string s = fmt::format("{:04}", static_cast<int>(MenuFunction::VOX_SELECT));
                return set(s);
            }

            VoxSelectValue Menu::AnswerVoxSelect(std::string data)
            {
                MenuFunction f = (MenuFunction)std::stoi(data.substr(2, 4));
                if (f == MenuFunction::VOX_SELECT)
                {
                    return (VoxSelectValue)std::stoi(data.substr(6, 1));
                }
                else throw new BadMenuItemException{ f };
            }

            std::string Menu::SetVoxGain(int val)
            {
                val = val < 0 ? 0 : val;
                val = val > 100 ? 100 : val;
                std::string s = fmt::format("{:04}{:04}", static_cast<int>(MenuFunction::VOX_GAIN), val);
                return set(s);
            }

            std::string Menu::ReadVoxGain()
            {
                std::string s = fmt::format("{:04}", static_cast<int>(MenuFunction::VOX_GAIN));
                return set(s);
            }

            int Menu::AnswerVoxGain(std::string data)
            {
                MenuFunction f = (MenuFunction)std::stoi(data.substr(2, 4));
                if (f == MenuFunction::VOX_GAIN)
                {
                    return std::stoi(data.substr(6, 4));
                }
                else throw new BadMenuItemException{ f };

            }

            std::string Menu::SetVoxDelay(int val)
            {
                val = val < 30 ? 30 : val;
                val = val > 3000 ? 3000 : val;
                std::string s = fmt::format("{:04}{:04}", static_cast<int>(MenuFunction::VOX_DELAY), val);
                return set(s);
            }

            std::string Menu::ReadVoxDelay()
            {
                std::string s = fmt::format("{:04}", static_cast<int>(MenuFunction::VOX_DELAY));
                return set(s);
            }

            int Menu::AnswerVoxDelay(std::string data)
            {
                MenuFunction f = (MenuFunction)std::stoi(data.substr(2, 4));
                if (f == MenuFunction::VOX_DELAY)
                {
                    return std::stoi(data.substr(6, 4));
                }
                else throw new BadMenuItemException{ f };

            }

            std::string Menu::SetAntiVoxGain(int val)
            {
                val = val < 0 ? 0 : val;
                val = val > 100 ? 100 : val;
                std::string s = fmt::format("{:04}{:03}", static_cast<int>(MenuFunction::ANTI_VOX_GAIN), val);
                return set(s);
            }

            std::string Menu::ReadAntiVoxGain()
            {
                std::string s = fmt::format("{:04}", static_cast<int>(MenuFunction::ANTI_VOX_GAIN));
                return set(s);
            }

            int Menu::AnswerAntiVoxGain(std::string data)
            {
                MenuFunction f = (MenuFunction)std::stoi(data.substr(2, 4));
                if (f == MenuFunction::ANTI_VOX_GAIN)
                {
                    return std::stoi(data.substr(6, 3));
                }
                else throw new BadMenuItemException{ f };
            }

            std::string Menu::SetDataVoxGain(int val)
            {
                val = val < 0 ? 0 : val;
                val = val > 100 ? 100 : val;
                std::string s = fmt::format("{:04}{:04}", static_cast<int>(MenuFunction::DATA_VOX_GAIN), val);
                return set(s);
            }

            std::string Menu::ReadDataVoxGain()
            {
                std::string s = fmt::format("{:04}", static_cast<int>(MenuFunction::DATA_VOX_GAIN));
                return set(s);
            }

            int Menu::AnswerDataVoxGain(std::string data)
            {
                MenuFunction f = (MenuFunction)std::stoi(data.substr(2, 4));
                if (f == MenuFunction::DATA_VOX_GAIN)
                {
                    return std::stoi(data.substr(6, 4));
                }
                else throw new BadMenuItemException{ f };

            }

            std::string Menu::SetDataVoxDelay(int val)
            {
                val = val < 30 ? 30 : val;
                val = val > 3000 ? 3000 : val;
                std::string s = fmt::format("{:04}{:04}", static_cast<int>(MenuFunction::DATA_VOX_DELAY), val);
                return set(s);
            }

            std::string Menu::ReadDataVoxDelay()
            {
                std::string s = fmt::format("{:04}", static_cast<int>(MenuFunction::DATA_VOX_DELAY));
                return set(s);
            }

            int Menu::AnswerDataVoxDelay(std::string data)
            {
                MenuFunction f = (MenuFunction)std::stoi(data.substr(2, 4));
                if (f == MenuFunction::DATA_VOX_DELAY)
                {
                    return std::stoi(data.substr(6, 4));
                }
                else throw new BadMenuItemException{ f };

            }

            std::string Menu::SetDataAntiVoxGain(int val)
            {
                val = val < 0 ? 0 : val;
                val = val > 100 ? 100 : val;
                std::string s = fmt::format("{:04}{:03}", static_cast<int>(MenuFunction::DATA_ANTIVOX_GAIN), val);
                return set(s);
            }

            std::string Menu::ReadDataAntiVoxGain()
            {
                std::string s = fmt::format("{:04}", static_cast<int>(MenuFunction::DATA_ANTIVOX_GAIN));
                return set(s);
            }

            int Menu::AnswerDataAntiVoxGain(std::string data)
            {
                MenuFunction f = (MenuFunction)std::stoi(data.substr(2, 4));
                if (f == MenuFunction::DATA_ANTIVOX_GAIN)
                {
                    return std::stoi(data.substr(6, 3));
                }
                else throw new BadMenuItemException{ f };
            }
            std::string Menu::SetEmergencyFreq(EnableDisableValue val)
            {
                std::string s = fmt::format("{:04}{:d}", static_cast<int>(MenuFunction::EMERGENCY_FREQ), static_cast<int>(val));
                return set(s);
            }

            std::string Menu::ReadEmergencyFreq()
            {
                std::string s = fmt::format("{:04}", static_cast<int>(MenuFunction::EMERGENCY_FREQ));
                return set(s);
            }

            EnableDisableValue Menu::AnswerEmergencyFreq(std::string data)
            {
                MenuFunction f = (MenuFunction)std::stoi(data.substr(2, 4));
                if (f == MenuFunction::EMERGENCY_FREQ)
                {
                    return (EnableDisableValue)std::stoi(data.substr(6, 1));
                }
                else throw new BadMenuItemException{ f };
            }

            std::string Menu::SetReset(ResetValue val)
            {
                std::string s = fmt::format("{:04}{:d}", static_cast<int>(MenuFunction::EMERGENCY_FREQ), static_cast<int>(val));
                return set(s);
            }

            std::string Menu::ReadMainVersion()
            {
                std::string s = fmt::format("{:04}", static_cast<int>(MenuFunction::MAIN_VERSION));
                return set(s);
            }

            std::string Menu::AnswerMainVersion(std::string data)
            {
                MenuFunction f = (MenuFunction)std::stoi(data.substr(2, 4));
                if (f == MenuFunction::MAIN_VERSION)
                {
                    return fmt::format("V{}-{}", data.substr(6, 2), data.substr(8, 2));
                }
                else throw new BadMenuItemException{ f };
            }

            std::string Menu::ReadDSPVersion()
            {
                std::string s = fmt::format("{:04}", static_cast<int>(MenuFunction::DSP_VERSION));
                return set(s);
            }

            std::string Menu::AnswerDSPVersion(std::string data)
            {
                MenuFunction f = (MenuFunction)std::stoi(data.substr(2, 4));
                if (f == MenuFunction::DSP_VERSION)
                {
                    return fmt::format("V{}-{}", data.substr(6, 2), data.substr(8, 2));
                }
                else throw new BadMenuItemException{ f };
            }

            std::string Menu::ReadLCDVersion()
            {
                std::string s = fmt::format("{:04}", static_cast<int>(MenuFunction::LCD_VERSION));
                return set(s);
            }

            std::string Menu::AnswerLCDVersion(std::string data)
            {
                MenuFunction f = (MenuFunction)std::stoi(data.substr(2, 4));
                if (f == MenuFunction::LCD_VERSION)
                {
                    return fmt::format("V{}-{}", data.substr(6, 2), data.substr(8, 2));
                }
                else throw new BadMenuItemException{ f };
            }

            std::string VFO_A_FREQ::Set(int val)
            {
                val = val < 30000 ? 30000 : val;
                val = val > 56000000 ? 56000000 : val;

                return fmt::format("FA{:09};", val);
            }
            std::string VFO_A_FREQ::Read()
            {
                return "FA;";
            }

            int VFO_A_FREQ::Answer(std::string data)
            {
                return std::stoi(data.substr(2, 9));
            }

            std::string VFO_B_FREQ::Set(int val)
            {
                val = val < 30000 ? 30000 : val;
                val = val > 56000000 ? 56000000 : val;

                return fmt::format("FB{:09};", val);
            }
            std::string VFO_B_FREQ::Read()
            {
                return "FB;";
            }

            int VFO_B_FREQ::Answer(std::string data)
            {
                return std::stoi(data.substr(2, 9));
            }

            std::string FAST_STEP::Set(VFOFastStepValue val)
            {
                return fmt::format("FS{:d};", static_cast<int>(val));
            }
            std::string FAST_STEP::Read()
            {
                return "FS;";
            }
            VFOFastStepValue FAST_STEP::Answer(std::string data)
            {
                return (VFOFastStepValue)std::stoi(data.substr(2, 1));
            }


            std::string AGC_FUNCTION::Set(AGCSetValue val)
            {
                return fmt::format("GT{:02};", static_cast<int>(val));
            }
            std::string AGC_FUNCTION::Read()
            {
                return "GT0;";
            }
            AGCReadValue AGC_FUNCTION::Answer(std::string data)
            {
                return (AGCReadValue)std::stoi(data.substr(3, 1));
            }

            std::string IDENTIFICATION::Read()
            {
                return "ID;";
            }
            Yaesu::RigType IDENTIFICATION::Answer(std::string data)
            {
                return static_cast<Yaesu::RigType>(std::stoi(data.substr(2,4)));
            }

            std::string IF_SHIFT::Set(IfShiftValue val, int freq)
            {
                freq = freq > 1200 ? 1200 : freq;
                freq = freq - (freq % 20);
                return fmt::format("IS0{:01}{:+05d};", static_cast<int>(val), freq);
            }

            std::string IF_SHIFT::Read()
            {
                return "IS0;";
            }

            IfShiftResultValue IF_SHIFT::Answer(std::string data)
            {
                IfShiftResultValue ret;
                ret.Frequency = std::stoi(data.substr(4, 5));
                ret.State = (IfShiftValue)std::stoi(data.substr(3, 1));
                return ret;
            }

            std::string KeyerMemory::Set(KeyerMemoryValue val)
            {
                return fmt::format("KM{:d}{};", val.ChannelNumber, val.Message.substr(0, 50));
            }

            std::string KeyerMemory::Read(int MemoryChannel)
            {
                return fmt::format("KM{:d};", MemoryChannel);
            }

            KeyerMemoryValue KeyerMemory::Answer(std::string data)
            {
                KeyerMemoryValue ret;
                ret.ChannelNumber = std::stoi(data.substr(2, 1));
                ret.Message = data.substr(3, data.length() - 4);
                return ret;
            }

            std::string KeyPitch::Set(KeyPitchValue val)
            {

                return fmt::format("KP{:02};", static_cast<int>(val));
            }
            std::string KeyPitch::Read()
            {
                return "KP;";
            }

            KeyPitchValue KeyPitch::Answer(std::string data)
            {
                return (KeyPitchValue)std::stoi(data.substr(2, 2));
            }

            std::string Keyer::Set(KeyerValue val)
            {
                return fmt::format("KR{};", static_cast<int>(val));
            }

            std::string Keyer::Read()
            {
                return "KR;";
            }
            KeyerValue Keyer::Answer(std::string data)
            {
                return (KeyerValue)std::stoi(data.substr(2, 1));
            }

            std::string KeyerSpeed::Set(KeyerSpeedVal val)
            {
                return fmt::format("KS{:03};", static_cast<int>(val));
            }

            std::string KeyerSpeed::Read()
            {
                return "KS;";
            }

            KeyerSpeedVal KeyerSpeed::Answer(std::string data)
            {
                return (KeyerSpeedVal)std::stoi(data.substr(2, 3));
            }

            std::string CWKeyingPlayback::Set(KeyerMemoryChannel val)
            {
                return fmt::format("KY{:0X};", static_cast<int>(val));
            }

            std::string VFODialLock::Set(DialLockValue val)
            {
                return fmt::format("LK{:d};", static_cast<int>(val));
            }
            std::string VFODialLock::Read()
            {
                return "LK;";
            }
            DialLockValue VFODialLock::Answer(std::string data)
            {
                return (DialLockValue)std::stoi(data.substr(2, 1));
            }

            std::string LoadMessage::Set(DVSRecordingValue val)
            {
                return fmt::format("LM0{:d};", static_cast<int>(val));
            }

            std::string LoadMessage::Read()
            {
                return "LM0;";
            }

            DVSRecordingValue LoadMessage::Answer(std::string data)
            {
                return (DVSRecordingValue)std::stoi(data.substr(3, 1));
            }

            std::string MemoryChannelToVFOA::Set()
            {
                return "MA;";
            }

            std::string MemoryChannel::Set(MemoryChannelValue val)
            {

                switch (val)
                {
                case MemoryChannelValue::P1L:
                    return  "MCP1L;";
                    break;
                case MemoryChannelValue::P1U:
                    return "MCP1U;";
                    break;
                case MemoryChannelValue::P2L:
                    return "MCP2L;";
                    break;
                case MemoryChannelValue::P2U:
                    return "MCP2U;";
                    break;
                case MemoryChannelValue::P3L:
                    return "MCP3L;";
                    break;
                case MemoryChannelValue::P3U:
                    return "MCP3U;";
                    break;
                case MemoryChannelValue::P4L:
                    return "MCP4L;";
                    break;
                case MemoryChannelValue::P4U:
                    return "MCP4U;";
                    break;
                case MemoryChannelValue::P5L:
                    return "MCP5L;";
                    break;
                case MemoryChannelValue::P5U:
                    return "MCP5U;";
                    break;
                case MemoryChannelValue::P6L:
                    return "MCP6L;";
                    break;
                case MemoryChannelValue::P6U:
                    return "MCP6U;";
                    break;
                case MemoryChannelValue::P7L:
                    return "MCP7L;";
                    break;
                case MemoryChannelValue::P7U:
                    return "MCP7U;";
                    break;
                case MemoryChannelValue::P8L:
                    return "MCP8L;";
                    break;
                case MemoryChannelValue::P8U:
                    return "MCP8U;";
                    break;
                case MemoryChannelValue::P9L:
                    return "MCP9L;";
                    break;
                case MemoryChannelValue::P9U:
                    return "MCP9U;";
                    break;
                case MemoryChannelValue::_5351_5mhz:
                case MemoryChannelValue::_5354mhz:
                case MemoryChannelValue::_5357mhz:
                case MemoryChannelValue::_5360mhz:
                case MemoryChannelValue::_5366mhz:
                case MemoryChannelValue::EMG:
                    return fmt::format("MC{:03};", static_cast<int>(val));;
                    break;
                default:
                    return fmt::format("MC{:03};", static_cast<int>(val));
                    break;
                }

            }

            std::string MemoryChannel::Read()
            {
                return "MC;";
            }

            MemoryChannelValue MemoryChannel::Answer(std::string data)
            {
                MemoryChannelValue ret = MemoryChannelValue::_1;
                std::string memVal = data.substr(2, 3);
                if (memVal == "EMG") {
                    ret = MemoryChannelValue::EMG;
                }
                else if (memVal[0] == 'P') {
                    bool upper = (memVal[2] == 'U');
                    switch (std::stoi(memVal.substr(1, 1)))
                    {
                    case 1:
                        if (upper)
                        {
                            ret = MemoryChannelValue::P1U;
                        }
                        else
                        {
                            ret = MemoryChannelValue::P1L;
                        }
                        break;
                    case 2:
                        if (upper)
                        {
                            ret = MemoryChannelValue::P2U;
                        }
                        else
                        {
                            ret = MemoryChannelValue::P2L;
                        }
                        break;
                    case 3:
                        if (upper)
                        {
                            ret = MemoryChannelValue::P3U;
                        }
                        else
                        {
                            ret = MemoryChannelValue::P3L;
                        }
                        break;
                    case 4:
                        if (upper)
                        {
                            ret = MemoryChannelValue::P4U;
                        }
                        else
                        {
                            ret = MemoryChannelValue::P4L;
                        }
                        break;
                    case 5:
                        if (upper)
                        {
                            ret = MemoryChannelValue::P5U;
                        }
                        else
                        {
                            ret = MemoryChannelValue::P5L;
                        }
                        break;
                    case 6:
                        if (upper)
                        {
                            ret = MemoryChannelValue::P6U;
                        }
                        else
                        {
                            ret = MemoryChannelValue::P6L;
                        }
                        break;
                    case 7:
                        if (upper)
                        {
                            ret = MemoryChannelValue::P7U;
                        }
                        else
                        {
                            ret = MemoryChannelValue::P7L;
                        }
                        break;
                    case 8:
                        if (upper)
                        {
                            ret = MemoryChannelValue::P8U;
                        }
                        else
                        {
                            ret = MemoryChannelValue::P8L;
                        }
                        break;
                    case 9:
                        if (upper)
                        {
                            ret = MemoryChannelValue::P9U;
                        }
                        else
                        {
                            ret = MemoryChannelValue::P9L;
                        }
                        break;
                    }
                }
                else {
                    ret = (MemoryChannelValue)std::stoi(memVal);
                }
                return ret;
            }

            std::string OperatingMode::Set(ModeValue val)
            {
                return fmt::format("MD0{:0X};", static_cast<int>(val));
            }

            std::string OperatingMode::Read()
            {
                return "MD0;";
            }

            ModeValue OperatingMode::Answer(std::string data)
            {
                return (ModeValue)std::stoi(data.substr(3, 1),nullptr,16);
            }

            std::string MicGain::Set(int val)
            {
                val = val > 100 ? 100 : val;
                val = val < 0 ? 0 : val;
                return fmt::format("MG{:03};", val);
            }

            std::string MicGain::Read()
            {
                return "MG;";
            }

            int MicGain::Answer(std::string data)
            {
                return std::stoi(data.substr(2, 3));
            }

            std::string MonitorLevel::Set(MonitorLevelValue val)
            {
                val.val.iVal = val.val.iVal > 100 ? 100 : val.val.iVal;
                val.val.iVal = val.val.iVal < 0 ? 0 : val.val.iVal;
                return fmt::format("ML{:d}{:03};", static_cast<int>(val.f), val.val.iVal);
            }
            std::string MonitorLevel::Read(MonitorFunction val)
            {
                return fmt::format("ML{:d};", static_cast<int>(val));
            }
            MonitorLevelValue MonitorLevel::Answer(std::string data)
            {
                MonitorLevelValue val;
                val.f = (MonitorFunction)std::stoi(data.substr(2, 1));
                val.val.iVal = std::stoi(data.substr(3, 3));
                return val;
            }

            std::string INFORMATION::Read()
            {
                return "IF;";
            }
            InformationValue INFORMATION::Answer(std::string data)
            {
                InformationValue retVal;
                std::string chStr = data.substr(2, 3);
                if (chStr == "EMG") {
                    retVal.MemoryChannel = MemoryChannelValue::EMG;
                }
                else if (chStr[0] == 'P') {
                    bool upper = chStr[2] == 'U';
                    switch (std::stoi(chStr.substr(1, 1)))
                    {
                    case 1:
                        if (upper)
                        {
                            retVal.MemoryChannel = MemoryChannelValue::P1U;
                        }
                        else
                        {
                            retVal.MemoryChannel = MemoryChannelValue::P1L;
                        }
                        break;
                    case 2:
                        if (upper)
                        {
                            retVal.MemoryChannel = MemoryChannelValue::P2U;
                        }
                        else
                        {
                            retVal.MemoryChannel = MemoryChannelValue::P2L;
                        }
                        break;
                    case 3:
                        if (upper)
                        {
                            retVal.MemoryChannel = MemoryChannelValue::P3U;
                        }
                        else
                        {
                            retVal.MemoryChannel = MemoryChannelValue::P3L;
                        }
                        break;
                    case 4:
                        if (upper)
                        {
                            retVal.MemoryChannel = MemoryChannelValue::P4U;
                        }
                        else
                        {
                            retVal.MemoryChannel = MemoryChannelValue::P4L;
                        }
                        break;
                    case 5:
                        if (upper)
                        {
                            retVal.MemoryChannel = MemoryChannelValue::P5U;
                        }
                        else
                        {
                            retVal.MemoryChannel = MemoryChannelValue::P5L;
                        }
                        break;
                    case 6:
                        if (upper)
                        {
                            retVal.MemoryChannel = MemoryChannelValue::P6U;
                        }
                        else
                        {
                            retVal.MemoryChannel = MemoryChannelValue::P6L;
                        }
                        break;
                    case 7:
                        if (upper)
                        {
                            retVal.MemoryChannel = MemoryChannelValue::P7U;
                        }
                        else
                        {
                            retVal.MemoryChannel = MemoryChannelValue::P7L;
                        }
                        break;
                    case 8:
                        if (upper)
                        {
                            retVal.MemoryChannel = MemoryChannelValue::P8U;
                        }
                        else
                        {
                            retVal.MemoryChannel = MemoryChannelValue::P8L;
                        }
                        break;
                    case 9:
                        if (upper)
                        {
                            retVal.MemoryChannel = MemoryChannelValue::P9U;
                        }
                        else
                        {
                            retVal.MemoryChannel = MemoryChannelValue::P9L;
                        }
                        break;
                    }

                }
                else {
                    retVal.MemoryChannel = (MemoryChannelValue)std::stoi(chStr);
                }

                retVal.VFOAFreq = std::stoi(data.substr(5, 9));
                retVal.ClarifierFreq = std::stoi(data.substr(14, 5));
                retVal.Clarifier = (ClarifierState)std::stoi(data.substr(19, 1));
                retVal.Mode = (ModeValue)std::stoi(data.substr(21, 1),nullptr,16);
                retVal.VFO = (VFOChannelTypeValue)std::stoi(data.substr(22,1));
                retVal.CTCSS = (CTCSSState)std::stoi(data.substr(23, 1));
                retVal.Operation = (OperationType)std::stoi(data.substr(26, 1));

                return retVal;

            }

            std::string MemoryChannelRead::Read(MemoryChannelValue val)
            {
                std::string retStr;
                switch (val)
                {
                case MemoryChannelValue::P1L:
                    return "MRP1L;";
                    break;
                case MemoryChannelValue::P1U:
                    return "MRP1U;";
                    break;
                case MemoryChannelValue::P2L:
                    return "MRP2L;";
                    break;
                case MemoryChannelValue::P2U:
                    return "MRP2U;";
                    break;
                case MemoryChannelValue::P3L:
                    return "MRP3L;";
                    break;
                case MemoryChannelValue::P3U:
                    return "MRP3U;";
                    break;
                case MemoryChannelValue::P4L:
                    return "MRP4L;";
                    break;
                case MemoryChannelValue::P4U:
                    return "MRP4U;";
                    break;
                case MemoryChannelValue::P5L:
                    return "MRP5L;";
                    break;
                case MemoryChannelValue::P5U:
                    return "MRP5U;";
                    break;
                case MemoryChannelValue::P6L:
                    return "MRP6L;";
                    break;
                case MemoryChannelValue::P6U:
                    return "MRP6U;";
                    break;
                case MemoryChannelValue::P7L:
                    return "MRP7L;";
                    break;
                case MemoryChannelValue::P7U:
                    return "MRP7U;";
                    break;
                case MemoryChannelValue::P8L:
                    return "MRP8L;";
                    break;
                case MemoryChannelValue::P8U:
                    return "MRP8U;";
                    break;
                case MemoryChannelValue::P9L:
                    return "MRP9L;";
                    break;
                case MemoryChannelValue::P9U:
                    return "MRP9U;";
                    break;
                case MemoryChannelValue::_5351_5mhz:
                case MemoryChannelValue::_5354mhz:
                case MemoryChannelValue::_5357mhz:
                case MemoryChannelValue::_5360mhz:
                case MemoryChannelValue::_5366mhz:
                case MemoryChannelValue::EMG:
                    return "";
                    break;
                default:
                    return fmt::format("MR{:03};", static_cast<int>(val));
                    break;
                }
                return retStr;
            }

            MemoryChannelReadValue MemoryChannelRead::Answer(std::string data)
            {
                MemoryChannelReadValue retVal;
                std::string chStr = data.substr(2, 3);
                if (chStr == "EMG") {
                    retVal.MemoryChannel = MemoryChannelValue::EMG;
                }
                else if (chStr[0] == 'P') {
                    bool upper = chStr[2] == 'U';
                    switch (std::stoi(chStr.substr(1, 1)))
                    {
                    case 1:
                        if (upper)
                        {
                            retVal.MemoryChannel = MemoryChannelValue::P1U;
                        }
                        else
                        {
                            retVal.MemoryChannel = MemoryChannelValue::P1L;
                        }
                        break;
                    case 2:
                        if (upper)
                        {
                            retVal.MemoryChannel = MemoryChannelValue::P2U;
                        }
                        else
                        {
                            retVal.MemoryChannel = MemoryChannelValue::P2L;
                        }
                        break;
                    case 3:
                        if (upper)
                        {
                            retVal.MemoryChannel = MemoryChannelValue::P3U;
                        }
                        else
                        {
                            retVal.MemoryChannel = MemoryChannelValue::P3L;
                        }
                        break;
                    case 4:
                        if (upper)
                        {
                            retVal.MemoryChannel = MemoryChannelValue::P4U;
                        }
                        else
                        {
                            retVal.MemoryChannel = MemoryChannelValue::P4L;
                        }
                        break;
                    case 5:
                        if (upper)
                        {
                            retVal.MemoryChannel = MemoryChannelValue::P5U;
                        }
                        else
                        {
                            retVal.MemoryChannel = MemoryChannelValue::P5L;
                        }
                        break;
                    case 6:
                        if (upper)
                        {
                            retVal.MemoryChannel = MemoryChannelValue::P6U;
                        }
                        else
                        {
                            retVal.MemoryChannel = MemoryChannelValue::P6L;
                        }
                        break;
                    case 7:
                        if (upper)
                        {
                            retVal.MemoryChannel = MemoryChannelValue::P7U;
                        }
                        else
                        {
                            retVal.MemoryChannel = MemoryChannelValue::P7L;
                        }
                        break;
                    case 8:
                        if (upper)
                        {
                            retVal.MemoryChannel = MemoryChannelValue::P8U;
                        }
                        else
                        {
                            retVal.MemoryChannel = MemoryChannelValue::P8L;
                        }
                        break;
                    case 9:
                        if (upper)
                        {
                            retVal.MemoryChannel = MemoryChannelValue::P9U;
                        }
                        else
                        {
                            retVal.MemoryChannel = MemoryChannelValue::P9L;
                        }
                        break;
                    }

                }
                else {
                    retVal.MemoryChannel = (MemoryChannelValue)std::stoi(chStr);
                }

                retVal.VFOAFreq = std::stoi(data.substr(5, 9));
                retVal.ClarifierFreq = std::stoi(data.substr(14, 5));
                retVal.Clarifier = (ClarifierState)std::stoi(data.substr(19, 1));
                retVal.Mode = (MemoryChannelModeValue)std::stoi(data.substr(21, 1));
                retVal.ChannelType = (VFOChannelTypeValue)std::stoi(data.substr(22, 1));
                retVal.CTCSS = (CTCSSState)std::stoi(data.substr(23, 1));
                retVal.Operation = (OperationType)std::stoi(data.substr(26, 1));

                return retVal;

            }

            std::string MeterSW::Set(FT891::MeterType val)
            {
                return fmt::format("MS{:d};", static_cast<int>(val));
            }

            std::string MeterSW::Read()
            {
                return "MS;";
            }

            MeterType MeterSW::Answer(std::string data)
            {
                return (MeterType)std::stoi(data.substr(2, 1));
            }

            std::string MemoryWriteTag::Set(MemoryChannelTagValue val)
            {
                std::string ret;
                std::string retStr;
                switch (val.MemoryChannel)
                {
                case MemoryChannelValue::P1L:
                    retStr = "MTP1L";
                    break;
                case MemoryChannelValue::P1U:
                    retStr = "MTP1U";
                    break;
                case MemoryChannelValue::P2L:
                    retStr = "MTP2L";
                    break;
                case MemoryChannelValue::P2U:
                    retStr = "MTP2U";
                    break;
                case MemoryChannelValue::P3L:
                    retStr = "MTP3L";
                    break;
                case MemoryChannelValue::P3U:
                    retStr = "MTP3U";
                    break;
                case MemoryChannelValue::P4L:
                    retStr = "MTP4L";
                    break;
                case MemoryChannelValue::P4U:
                    retStr = "MTP4U";
                    break;
                case MemoryChannelValue::P5L:
                    retStr = "MTP5L";
                    break;
                case MemoryChannelValue::P5U:
                    retStr = "MTP5U";
                    break;
                case MemoryChannelValue::P6L:
                    retStr = "MTP6L";
                    break;
                case MemoryChannelValue::P6U:
                    retStr = "MTP6U";
                    break;
                case MemoryChannelValue::P7L:
                    retStr = "MTP7L";
                    break;
                case MemoryChannelValue::P7U:
                    retStr = "MTP7U";
                    break;
                case MemoryChannelValue::P8L:
                    retStr = "MTP8L";
                    break;
                case MemoryChannelValue::P8U:
                    retStr = "MTP8U";
                    break;
                case MemoryChannelValue::P9L:
                    retStr = "MTP9L";
                    break;
                case MemoryChannelValue::P9U:
                    retStr = "MTP9U";
                    break;
                case MemoryChannelValue::_5351_5mhz:
                case MemoryChannelValue::_5354mhz:
                case MemoryChannelValue::_5357mhz:
                case MemoryChannelValue::_5360mhz:
                case MemoryChannelValue::_5366mhz:
                case MemoryChannelValue::EMG:
                    retStr = "";
                    break;
                default:
                    retStr = fmt::format("MT{:03}", static_cast<int>(val.MemoryChannel));
                    break;
                }
                std::string tag(12,' ');
                std::copy(val.TagString.begin(), val.TagString.end(),tag.begin());
                ret = fmt::format("{}{:09}{:+05}{:01}0{:0X}0{:01}00{:01}{:01}{};",
                    retStr,
                    static_cast<int>(val.VFOAFreq),
                    static_cast<int>(val.ClarifierFreq),
                    static_cast<int>(val.Clarifier),
                    static_cast<int>(val.Mode),
                    static_cast<int>(val.CTCSS),
                    static_cast<int>(val.Operation),
                    static_cast<int>(val.TAG),
                    tag);

                return ret;
            }

            std::string MemoryWriteTag::Read(MemoryChannelValue val)
            {

                std::string retStr;
                switch (val)
                {
                case MemoryChannelValue::P1L:
                    retStr = "MTP1L;";
                    break;
                case MemoryChannelValue::P1U:
                    retStr = "MTP1U;";
                    break;
                case MemoryChannelValue::P2L:
                    retStr = "MTP2L;";
                    break;
                case MemoryChannelValue::P2U:
                    retStr = "MTP2U;";
                    break;
                case MemoryChannelValue::P3L:
                    retStr = "MTP3L;";
                    break;
                case MemoryChannelValue::P3U:
                    retStr = "MTP3U;";
                    break;
                case MemoryChannelValue::P4L:
                    retStr = "MTP4L;";
                    break;
                case MemoryChannelValue::P4U:
                    retStr = "MTP4U;";
                    break;
                case MemoryChannelValue::P5L:
                    retStr = "MTP5L;";
                    break;
                case MemoryChannelValue::P5U:
                    retStr = "MTP5U;";
                    break;
                case MemoryChannelValue::P6L:
                    retStr = "MTP6L;";
                    break;
                case MemoryChannelValue::P6U:
                    retStr = "MTP6U;";
                    break;
                case MemoryChannelValue::P7L:
                    retStr = "MTP7L;";
                    break;
                case MemoryChannelValue::P7U:
                    retStr = "MTP7U;";
                    break;
                case MemoryChannelValue::P8L:
                    retStr = "MTP8L;";
                    break;
                case MemoryChannelValue::P8U:
                    retStr = "MTP8U;";
                    break;
                case MemoryChannelValue::P9L:
                    retStr = "MTP9L;";
                    break;
                case MemoryChannelValue::P9U:
                    retStr = "MTP9U;";
                    break;
                case MemoryChannelValue::_5351_5mhz:
                case MemoryChannelValue::_5354mhz:
                case MemoryChannelValue::_5357mhz:
                case MemoryChannelValue::_5360mhz:
                case MemoryChannelValue::_5366mhz:
                case MemoryChannelValue::EMG:
                    retStr = "";
                    break;
                default:
                    retStr = fmt::format("MT{:03};", static_cast<int>(val));
                    break;
                }
                return retStr;
            }

            MemoryChannelTagValue MemoryWriteTag::Answer(std::string data)
            {
                MemoryChannelTagValue retVal;
                std::string chStr = data.substr(2, 3);
                if (chStr == "EMG") {
                    retVal.MemoryChannel = MemoryChannelValue::EMG;

                }
                else if (chStr[0] == 'P') {
                    bool upper = chStr[2] == 'U';
                    switch (std::stoi(chStr.substr(1, 1)))
                    {
                    case 1:
                        if (upper)
                        {
                            retVal.MemoryChannel = MemoryChannelValue::P1U;
                        }
                        else
                        {
                            retVal.MemoryChannel = MemoryChannelValue::P1L;
                        }
                        break;
                    case 2:
                        if (upper)
                        {
                            retVal.MemoryChannel = MemoryChannelValue::P2U;
                        }
                        else
                        {
                            retVal.MemoryChannel = MemoryChannelValue::P2L;
                        }
                        break;
                    case 3:
                        if (upper)
                        {
                            retVal.MemoryChannel = MemoryChannelValue::P3U;
                        }
                        else
                        {
                            retVal.MemoryChannel = MemoryChannelValue::P3L;
                        }
                        break;
                    case 4:
                        if (upper)
                        {
                            retVal.MemoryChannel = MemoryChannelValue::P4U;
                        }
                        else
                        {
                            retVal.MemoryChannel = MemoryChannelValue::P4L;
                        }
                        break;
                    case 5:
                        if (upper)
                        {
                            retVal.MemoryChannel = MemoryChannelValue::P5U;
                        }
                        else
                        {
                            retVal.MemoryChannel = MemoryChannelValue::P5L;
                        }
                        break;
                    case 6:
                        if (upper)
                        {
                            retVal.MemoryChannel = MemoryChannelValue::P6U;
                        }
                        else
                        {
                            retVal.MemoryChannel = MemoryChannelValue::P6L;
                        }
                        break;
                    case 7:
                        if (upper)
                        {
                            retVal.MemoryChannel = MemoryChannelValue::P7U;
                        }
                        else
                        {
                            retVal.MemoryChannel = MemoryChannelValue::P7L;
                        }
                        break;
                    case 8:
                        if (upper)
                        {
                            retVal.MemoryChannel = MemoryChannelValue::P8U;
                        }
                        else
                        {
                            retVal.MemoryChannel = MemoryChannelValue::P8L;
                        }
                        break;
                    case 9:
                        if (upper)
                        {
                            retVal.MemoryChannel = MemoryChannelValue::P9U;
                        }
                        else
                        {
                            retVal.MemoryChannel = MemoryChannelValue::P9L;
                        }
                        break;
                    }

                }
                else {
                    retVal.MemoryChannel = (MemoryChannelValue)std::stoi(chStr);
                }


                retVal.VFOAFreq = std::stoi(data.substr(5, 9));
                retVal.ClarifierFreq = std::stoi(data.substr(14, 5));
                retVal.Clarifier = (ClarifierState)std::stoi(data.substr(19, 1));
                retVal.Mode = (MemoryChannelModeValue)std::stoi(data.substr(21, 1));
                retVal.CTCSS = (CTCSSState)std::stoi(data.substr(23, 1));
                retVal.Operation = (OperationType)std::stoi(data.substr(26, 1));
                retVal.TAG = (TagValue)std::stoi(data.substr(27, 1));
                retVal.TagString = data.substr(28, data.length() - 29);

                return retVal;
            }

            std::string MemoryChannelWrite::Set(MemoryChannelWriteValue val)
            {
                std::string ret;

                std::string retStr;
                switch (val.MemoryChannel)
                {
                case MemoryChannelValue::P1L:
                    retStr = "P1L;";
                    break;
                case MemoryChannelValue::P1U:
                    retStr = "P1U;";
                    break;
                case MemoryChannelValue::P2L:
                    retStr = "P2L;";
                    break;
                case MemoryChannelValue::P2U:
                    retStr = "P2U;";
                    break;
                case MemoryChannelValue::P3L:
                    retStr = "P3L;";
                    break;
                case MemoryChannelValue::P3U:
                    retStr = "P3U;";
                    break;
                case MemoryChannelValue::P4L:
                    retStr = "P4L;";
                    break;
                case MemoryChannelValue::P4U:
                    retStr = "P4U;";
                    break;
                case MemoryChannelValue::P5L:
                    retStr = "P5L;";
                    break;
                case MemoryChannelValue::P5U:
                    retStr = "P5U;";
                    break;
                case MemoryChannelValue::P6L:
                    retStr = "P6L;";
                    break;
                case MemoryChannelValue::P6U:
                    retStr = "P6U;";
                    break;
                case MemoryChannelValue::P7L:
                    retStr = "P7L;";
                    break;
                case MemoryChannelValue::P7U:
                    retStr = "P7U;";
                    break;
                case MemoryChannelValue::P8L:
                    retStr = "P8L;";
                    break;
                case MemoryChannelValue::P8U:
                    retStr = "P8U;";
                    break;
                case MemoryChannelValue::P9L:
                    retStr = "P9L;";
                    break;
                case MemoryChannelValue::P9U:
                    retStr = "P9U;";
                    break;
                case MemoryChannelValue::_5351_5mhz:
                case MemoryChannelValue::_5354mhz:
                case MemoryChannelValue::_5357mhz:
                case MemoryChannelValue::_5360mhz:
                case MemoryChannelValue::_5366mhz:
                case MemoryChannelValue::EMG:
                    retStr = fmt::format("{:03}", static_cast<int>(val.MemoryChannel));;
                    break;
                default:
                    retStr = fmt::format("{:03}", static_cast<int>(val.MemoryChannel));
                    break;
                }

                ret = fmt::format("MW{}{:09}{:+05}{:d}0{:d}0{:d}00{:d};",
                    retStr,
                    static_cast<int>(val.VFOAFreq),
                    static_cast<int>(val.ClarifierFreq),
                    static_cast<int>(val.Clarifier),
                    static_cast<int>(val.Mode),
                    static_cast<int>(val.CTCSS),
                    static_cast<int>(val.Operation));

                return ret;
            }


            std::string MoxSet::Set(MoxSetVal val)
            {
                return fmt::format("MX{:d};", static_cast<int>(val));
            }
            std::string MoxSet::Read()
            {
                return "MX;";
            }
            MoxSetVal MoxSet::Answer(std::string data)
            {
                return (MoxSetVal)std::stoi(data.substr(2, 1));
            }

            std::string Narrow::Set(NarrowValue val)
            {
                return fmt::format("NA0{:d};", static_cast<int>(val));
            }
            std::string Narrow::Read()
            {
                return "NA0;";
            }

            NarrowValue Narrow::Answer(std::string data)
            {
                return (NarrowValue)std::stoi(data.substr(3, 1));
            }

            std::string NoiseBlankerStatus::Set(NoiseBlankerStatusValue val)
            {
                return fmt::format("NB0{:d};", static_cast<int>(val));
            }

            std::string NoiseBlankerStatus::Read()
            {
                return "NB0;";
            }

            NoiseBlankerStatusValue NoiseBlankerStatus::Answer(std::string data)
            {
                return (NoiseBlankerStatusValue)std::stoi(data.substr(3, 1));
            }

            std::string NoiseBlankerLevel::Set(int val)
            {
                val = val > 10 ? 10 : val;
                val = val < 0 ? 0 : val;

                return fmt::format("NL0{:03};", val);
            }

            std::string NoiseBlankerLevel::Read()
            {
                return "NL0;";
            }

            int NoiseBlankerLevel::Answer(std::string data)
            {
                return std::stoi(data.substr(3, 3));
            }

            std::string NoiseReduction::Set(NoiseReductionValue val)
            {
                return fmt::format("NR0{:d};", static_cast<int>(val));
            }

            std::string NoiseReduction::Read()
            {
                return "NR0;";
            }

            NoiseReductionValue NoiseReduction::Answer(std::string data)
            {
                return (NoiseReductionValue)std::stoi(data.substr(3, 1));
            }

            std::string OppositeBandInformation::Read()
            {
                return "OI;";
            }
            OppositeInformationValue OppositeBandInformation::Answer(std::string data)
            {
                OppositeInformationValue retVal;
                std::string chStr = data.substr(2, 3);
                if (chStr == "EMG") {
                    retVal.MemoryChannel = MemoryChannelValue::EMG;
                }
                else if (chStr[0] == 'P') {
                    bool upper = chStr[2] == 'U';
                    switch (std::stoi(chStr.substr(1, 1)))
                    {
                    case 1:
                        if (upper)
                        {
                            retVal.MemoryChannel = MemoryChannelValue::P1U;
                        }
                        else
                        {
                            retVal.MemoryChannel = MemoryChannelValue::P1L;
                        }
                        break;
                    case 2:
                        if (upper)
                        {
                            retVal.MemoryChannel = MemoryChannelValue::P2U;
                        }
                        else
                        {
                            retVal.MemoryChannel = MemoryChannelValue::P2L;
                        }
                        break;
                    case 3:
                        if (upper)
                        {
                            retVal.MemoryChannel = MemoryChannelValue::P3U;
                        }
                        else
                        {
                            retVal.MemoryChannel = MemoryChannelValue::P3L;
                        }
                        break;
                    case 4:
                        if (upper)
                        {
                            retVal.MemoryChannel = MemoryChannelValue::P4U;
                        }
                        else
                        {
                            retVal.MemoryChannel = MemoryChannelValue::P4L;
                        }
                        break;
                    case 5:
                        if (upper)
                        {
                            retVal.MemoryChannel = MemoryChannelValue::P5U;
                        }
                        else
                        {
                            retVal.MemoryChannel = MemoryChannelValue::P5L;
                        }
                        break;
                    case 6:
                        if (upper)
                        {
                            retVal.MemoryChannel = MemoryChannelValue::P6U;
                        }
                        else
                        {
                            retVal.MemoryChannel = MemoryChannelValue::P6L;
                        }
                        break;
                    case 7:
                        if (upper)
                        {
                            retVal.MemoryChannel = MemoryChannelValue::P7U;
                        }
                        else
                        {
                            retVal.MemoryChannel = MemoryChannelValue::P7L;
                        }
                        break;
                    case 8:
                        if (upper)
                        {
                            retVal.MemoryChannel = MemoryChannelValue::P8U;
                        }
                        else
                        {
                            retVal.MemoryChannel = MemoryChannelValue::P8L;
                        }
                        break;
                    case 9:
                        if (upper)
                        {
                            retVal.MemoryChannel = MemoryChannelValue::P9U;
                        }
                        else
                        {
                            retVal.MemoryChannel = MemoryChannelValue::P9L;
                        }
                        break;
                    }

                }
                else {
                    retVal.MemoryChannel = (MemoryChannelValue)std::stoi(chStr);
                }

                retVal.VFOBFreq = std::stoi(data.substr(5, 9));
                retVal.ClarifierFreq = std::stoi(data.substr(14, 5));
                retVal.Clarifier = (ClarifierState)std::stoi(data.substr(19, 1));
                retVal.Mode = (ModeValue)std::stoi(data.substr(21, 1), nullptr, 16);
                retVal.VFO = (VFOChannelTypeValue)std::stoi(data.substr(22,1));
                retVal.CTCSS = (CTCSSState)std::stoi(data.substr(23, 1));
                retVal.Operation = (OperationType)std::stoi(data.substr(26, 1));

                return retVal;
            }

            std::string OffSet::Set(OperationType val)
            {
                return fmt::format("OS0{:d};", static_cast<int>(val));
            }

            std::string OffSet::Read()
            {
                return "OS0;";
            }

            OperationType OffSet::Answer(std::string data)
            {
                return (OperationType)std::stoi(data.substr(3, 1));
            }

            std::string PreAmp::Set(PreAmpValue val)
            {
                return fmt::format("PA0{:d};", static_cast<int>(val));
            }
            std::string PreAmp::Read()
            {
                return "PA0;";
            }
            PreAmpValue PreAmp::Answer(std::string data)
            {
                return (PreAmpValue)std::stoi(data.substr(3, 1));
            }

            std::string PlayBack::Set(DVSRecordingValue val)
            {
                return fmt::format("PB0{:d};", static_cast<int>(val));
            }

            std::string PlayBack::Read()
            {
                return "PB0;";
            }

            DVSRecordingValue PlayBack::Answer(std::string data)
            {
                return (DVSRecordingValue)std::stoi(data.substr(3, 1));
            }

            std::string PowerControl::Set(int val)
            {
                val = val < 5 ? 5 : val;
                val = val > 100 ? 100 : val;
                return fmt::format("PC{:03};", val);
            }
            std::string PowerControl::Read()
            {
                return "PC;";
            }

            int PowerControl::Answer(std::string data)
            {
                return std::stoi(data.substr(2, 3));
            }

            std::string SpeechProcessorLevel::Set(int val)
            {
                val = val < 0 ? 0 : val;
                val = val > 100 ? 100 : val;
                return fmt::format("PL{:03};", val);
            }
            std::string SpeechProcessorLevel::Read()
            {
                return "PL;";
            }

            int SpeechProcessorLevel::Answer(std::string data)
            {
                return std::stoi(data.substr(2, 3));
            }

            std::string SpeechProcessor::Set(SpeechProcessorSetting val)
            {
                return fmt::format("PR{:01}{:01};", static_cast<int>(val.type), static_cast<int>(val.state));
            }

            std::string SpeechProcessor::Read(SpeechProcessorType type)
            {
                return fmt::format("PR{:01};", static_cast<int>(type));
            }

            SpeechProcessorSetting SpeechProcessor::Answer(std::string data)
            {
                SpeechProcessorSetting retVal;
                retVal.type = (SpeechProcessorType)std::stoi(data.substr(2, 1));
                retVal.state = (SpeechProcessorState)std::stoi(data.substr(3, 1));
                return retVal;
            }

            std::string PowerSwitch::Set(PowerSwitchValue val)
            {
                return fmt::format("PS{:d};", static_cast<int>(val));
            }
            std::string PowerSwitch::Read()
            {
                return "PS;";
            }
            PowerSwitchValue PowerSwitch::Answer(std::string data)
            {
                return (PowerSwitchValue)std::stoi(data.substr(2, 1));
            }

            std::string QMBStore::Set()
            {
                return "QI;";
            }

            std::string QMBRecall::Set()
            {
                return "QR;";
            }

            std::string QMBSplit::Set()
            {
                return "QS;";
            }


            std::string RFAttenuator::Set(RfAttenuatorState val)
            {
                return fmt::format("RA0{:d};", static_cast<int>(val));
            }
            std::string RFAttenuator::Read()
            {
                return "RA0;";
            }
            RfAttenuatorState RFAttenuator::Answer(std::string data)
            {
                return (RfAttenuatorState)std::stoi(data.substr(3, 1));
            }

            std::string ClarClear::Set()
            {
                return "RC;";
            }

            std::string ClarDown::Set(int val)
            {
                val = val > 9999 ? 9999 : val;
                val = val < 0 ? 0 : val;
                return fmt::format("RD{:04};", val);
            }

            std::string RFGain::Set(int val)
            {
                val = val > 30 ? 30 : val;
                val = val < 0 ? 0 : val;
                return fmt::format("RG0{:03};", val);
            }

            std::string RFGain::Read()
            {
                return "RG0;";
            }

            int RFGain::Answer(std::string data)
            {
                return std::stoi(data.substr(3, 3));
            }

            std::string RadioInformation::Read(StateType type)
            {
                return fmt::format("RI{:0x};", type);
            }

            RadioInfoVal RadioInformation::Answer(std::string data)
            {
                RadioInfoVal ret;
                ret.Type = (InformationType)std::stoi(data.substr(2, 1),0,16);
                ret.Value = (InformationState)std::stoi(data.substr(3, 1));
                return ret;
            }

            std::string NoiseReductionLevel::Set(int val)
            {
                val = val > 15 ? 15 : val;
                val = val < 1 ? 1 : val;

                return fmt::format("RL0{:02};", val);
            }

            std::string NoiseReductionLevel::Read()
            {
                return "RL0;";
            }

            int NoiseReductionLevel::Answer(std::string data)
            {
                return std::stoi(data.substr(3, 2));
            }


            std::string ReadMeter::Read(ReadMeterType type)
            {
                return fmt::format("RM{:d};", static_cast<int>(type));
            }

            MeterVal ReadMeter::Answer(std::string data)
            {
                MeterVal ret;
                ret.Type = (ReadMeterType)std::stoi(data.substr(2, 1));
                ret.Value = std::stoi(data.substr(3, 3));
                return ret;
            }

            std::string RadioStatus::Read()
            {
                return "RS;";
            }

            RadioStatusValue RadioStatus::Answer(std::string data)
            {
                return (RadioStatusValue)std::stoi(data.substr(2, 1));
            }

            std::string RxClarifierPlusOffset::Set(int val)
            {
                val = val > 9999 ? 9999 : val;
                val = val < 0 ? 0 : val;
                return fmt::format("RU{:04};", val);
            }


            std::string Scan::Set(ScanState val)
            {
                return fmt::format("SC{:d};", static_cast<int>(val));
            }
            std::string Scan::Read()
            {
                return "SC;";
            }

            ScanState Scan::Answer(std::string data)
            {
                return (ScanState)std::stoi(data.substr(2, 1));
            }

            std::string CWBreakInDelay::Set(int val)
            {
                val = val > 3000 ? 3000 : val;
                val = val < 30 ? 30 : val;

                return fmt::format("SD{:04};", val);
            }
            std::string CWBreakInDelay::Read()
            {
                return "SD;";
            }

            int CWBreakInDelay::Answer(std::string data)
            {
                return std::stoi(data.substr(2, 4));
            }

            std::string Width::Set(WidthValue val)
            {
                val.WidthCommand = val.WidthCommand > 21 ? 21 : val.WidthCommand;
                val.WidthCommand = val.WidthCommand < 0 ? 0 : val.WidthCommand;
                std::string ret = fmt::format("SH0{:01}{:02};",
                static_cast<int>(val.State),
                static_cast<int>(val.WidthCommand));
                return ret;
            }
            std::string Width::Read()
            {
                return "SH0;";
            }
            WidthValue Width::Answer(std::string data)
            {
                WidthValue val;
                val.State = (WidthState)std::stoi(data.substr(3, 1));
                val.WidthCommand = std::stoi(data.substr(4, 2));
                return val;
            }

            std::string SMeterReading::Read()
            {
                return "SM0;";
            }

            int SMeterReading::Answer(std::string data)
            {
                return std::stoi(data.substr(3, 3));
            }

            std::string SquelchLevel::Set(int val)
            {
                val = val > 100 ? 100 : val;
                val = val < 0 ? 0 : val;
                return fmt::format("SQ0{:03};", val);
            }

            std::string SquelchLevel::Read()
            {
                return "SQ0;";
            }
            int SquelchLevel::Answer(std::string data)
            {
                return std::stoi(data.substr(3, 3));
            }

            std::string Split::Set(SplitValue val)
            {
                return fmt::format("ST{:d};", static_cast<int>(val));
            }

            std::string Split::Read()
            {
                return "ST;";
            }

            SplitValue Split::Answer(std::string data)
            {
                return (SplitValue)std::stoi(data.substr(2, 1));
            }

            std::string SwapVfo::Set()
            {
                return "SV;";
            }

            std::string TXW::Set(TXWValue val)
            {
                return fmt::format("TS{:d};", static_cast<int>(val));
            }
            std::string TXW::Read()
            {
                return "TS;";
            }

            TXWValue TXW::Answer(std::string data)
            {
                return (TXWValue)(std::stoi(data.substr(2, 1)));
            }

            std::string TxSet::Set(TxSetValue val)
            {
                return fmt::format("TX{:01};", static_cast<int>(val));
            }

            std::string TxSet::Read()
            {
                return "TX;";
            }

            TxSetValue TxSet::Answer(std::string data)
            {
                return (TxSetValue)std::stoi(data.substr(2, 1));
            }


            std::string PLLUnlockStatus::Read()
            {
                return "UL;";
            }

            LockValue PLLUnlockStatus::Answer(std::string data)
            {
                return (LockValue)std::stoi(data.substr(2, 1));
            }

            std::string Up::Set()
            {
                return "UP;";
            }

            std::string VoxDelayTime::Set(int val)
            {
                val = val < 30 ? 30 : val;
                val = val > 3000 ? 3000 : val;
                return fmt::format("VD{:04};", val);
            }
            std::string VoxDelayTime::Read()
            {
                return "VD;";
            }
            int VoxDelayTime::Answer(std::string data)
            {
                return std::stoi(data.substr(2, 4));
            }

            std::string VoxGain::Set(int val)
            {
                val = val < 0 ? 0 : val;
                val = val > 100 ? 100 : val;
                return fmt::format("VG{:03};", static_cast<int>(val));
            }
            std::string VoxGain::Read()
            {
                return "VG;";
            }
            int VoxGain::Answer(std::string data)
            {
                return std::stoi(data.substr(2, 3));
            }

            std::string VFO_A_toMemoryChannel::Set()
            {
                return "VM;";
            }

            std::string VoxStatus::Set(VoxStatusValue val)
            {
                return fmt::format("VX{:d};", static_cast<int>(val));
            }

            std::string VoxStatus::Read()
            {
                return "VX;";
            }

            VoxStatusValue VoxStatus::Answer(std::string data)
            {
                return (VoxStatusValue)std::stoi(data.substr(2, 1));
            }

            std::string ZeroIn::Set()
            {
                return "ZI;";
            }



            std::string DisplayFrequency(int freq)
            {
                std::string s = fmt::format("{:d}", freq);
                if (s.length() > 3)
                    s.insert(s.length() - 3, 1, '.');
                if (s.length() > 7)
                    s.insert(s.length() - 7, 1, '.');

                return s;
            }

            std::string DisplayCwWeight(int weight)
            {
                std::string ret = fmt::format("{:d}", weight);
                return ret.substr(0, 1) + "." + ret.substr(1, 1);
            }

            std::string DisplayBand(Band v)
            {
                switch (v)
                {
                case Band::m160:
                    return "1.8";
                case Band::m80:
                    return "3.5";
                case Band::m60:
                    return "5.0";
                case Band::m40:
                    return "7.0";
                case Band::m30:
                    return "10";
                case Band::m20:
                    return "14";
                case Band::m17:
                    return "18";
                case Band::m15:
                    return "21";
                case Band::m12:
                    return "24";
                case Band::m10:
                    return "28";
                case Band::m6:
                    return "50";
                case Band::GEN:
                    return "GEN";
                case Band::MW:
                    return "MW";
                default:
                    return "";
                }
            }

            std::string DisplayKeyerType(KeyerTypeValue v)
            {
                switch (v)
                {
                case KeyerTypeValue::OFF:
                    return "OFF";
                    break;
                case KeyerTypeValue::BUG:
                    return "BUG";
                    break;
                case KeyerTypeValue::ELEKEY_A:
                    return "ELEKEY-A";
                    break;
                case KeyerTypeValue::ELEKEY_B:
                    return "ELEKEY-B";
                    break;
                case KeyerTypeValue::ELEKEY_Y:
                    return "ELEKEY-Y";
                    break;
                case KeyerTypeValue::ACS:
                    return "ACS";
                    break;
                default:
                    return "";
                }
            }

            std::string DisplayEnableDisable(EnableDisableValue v)
            {
                switch (v)
                {
                case EnableDisableValue::ENABLE:
                    return "ENABLE";
                case EnableDisableValue::DISABLE:
                    return "DISABLE";
                default:
                    return "";
                }
            }

            std::string DisplayPeakHold(PeakHoldType t)
            {
                switch (t)
                {
                case PeakHoldType::OFF:
                    return "OFF";
                    break;
                case PeakHoldType::sec05:
                    return "0.5 sec";
                    break;
                case PeakHoldType::sec10:
                    return "1.0 sec";
                    break;
                case PeakHoldType::sec20:
                    return "2.0 sec";
                    break;
                default:
                    return "";
                }
            }

            std::string DisplayBeaconInterval(int i)
            {
                if (i == 0)
                {
                    return "OFF";
                }
                else
                {
                    return fmt::format("{:03} sec", i);
                }
            }

            std::string DisplayNumberStyle(NumberStyleValue v)
            {
                switch (v)
                {
                case NumberStyleValue::_1290:
                    return "1290";
                    break;
                case NumberStyleValue::AUNO:
                    return "AUNO";
                    break;
                case NumberStyleValue::AUNT:
                    return "AUNT";
                    break;
                case NumberStyleValue::A2NO:
                    return "A2NO";
                    break;
                case NumberStyleValue::A2NT:
                    return "A2NT";
                    break;
                case NumberStyleValue::_12NO:
                    return "12NO";
                    break;
                case NumberStyleValue::_12NT:
                    return "12NT";
                    break;
                default:
                    return "";
                }
            }

            std::string DisplayNbWidth(NBWidthValue v)
            {
                switch (v)
                {
                case NBWidthValue::msec1:
                    return "1 msec";
                    break;
                case NBWidthValue::msec3:
                    return "3 msec";
                    break;
                case NBWidthValue::msec10:
                    return "10 msec";
                    break;
                default:
                    return "";
                }
            }

            std::string DisplayNbRejection(NBRejectionValue v)
            {
                switch (v)
                {
                case NBRejectionValue::db10:
                    return "10 db";
                    break;
                case NBRejectionValue::db30:
                    return "30 db";
                    break;
                case NBRejectionValue::db50:
                    return "50 db";
                    break;
                default:
                    return "";
                }
            }

            std::string DisplayCatRate(CatRateValue v)
            {
                switch (v)
                {
                case CatRateValue::_4800bps:
                    return "4800 bps";
                    break;
                case CatRateValue::_9600bps:
                    return "9600 bps";
                    break;
                case CatRateValue::_19200bps:
                    return "19200 bps";
                    break;
                case CatRateValue::_38400bps:
                    return "38400 bps";
                    break;
                default:
                    return "";
                }
            }

            std::string DisplayCatTOT(CatTOTValue v)
            {
                switch (v)
                {
                case CatTOTValue::_10msec:
                    return "10 msec";
                    break;
                case CatTOTValue::_100msec:
                    return "100 msec";
                    break;
                case CatTOTValue::_1000msec:
                    return "1000 msec";
                    break;
                case CatTOTValue::_3000msec:
                    return "3000 msec";
                    break;
                default:
                    return "";
                }
            }

            std::string DisplayAPO(APOValue v)
            {
                switch (v)
                {
                case APOValue::OFF:
                    return "OFF";
                    break;
                case APOValue::hr1:
                    return "1h";
                    break;
                case APOValue::hr2:
                    return "2h";
                    break;
                case APOValue::hr4:
                    return "4h";
                    break;
                case APOValue::hr6:
                    return "6h";
                    break;
                case APOValue::hr8:
                    return "8h";
                    break;
                case APOValue::hr10:
                    return "10h";
                    break;
                case APOValue::hr12:
                    return "12h";
                    break;
                default:
                    return "";
                }
            }

            std::string DisplayClarSelect(ClarSelectValue v)
            {
                switch (v)
                {
                case ClarSelectValue::TX:
                    return "TX";
                    break;
                case ClarSelectValue::RX:
                    return "RX";
                    break;
                case ClarSelectValue::TRX:
                    return "TRX";
                default:
                    return "";
                }
            }

            std::string DisplayFreqLowCut(FreqLowCutValue v)
            {
                switch (v)
                {
                case FreqLowCutValue::OFF:
                    return "OFF";
                    break;
                case FreqLowCutValue::_100hz:
                    return "100 Hz";
                    break;
                case FreqLowCutValue::_150hz:
                    return "150 Hz";
                    break;
                case FreqLowCutValue::_200hz:
                    return "200 Hz";
                    break;
                case FreqLowCutValue::_250hz:
                    return "250 Hz";
                    break;
                case FreqLowCutValue::_300hz:
                    return "300 Hz";
                    break;
                case FreqLowCutValue::_350hz:
                    return "350 Hz";
                    break;
                case FreqLowCutValue::_400hz:
                    return "400 Hz";
                    break;
                case FreqLowCutValue::_450hz:
                    return "450 Hz";
                    break;
                case FreqLowCutValue::_500hz:
                    return "500 Hz";
                    break;
                case FreqLowCutValue::_550hz:
                    return "550 Hz";
                    break;
                case FreqLowCutValue::_600hz:
                    return "600 Hz";
                    break;
                case FreqLowCutValue::_650hz:
                    return "650 Hz";
                    break;
                case FreqLowCutValue::_700hz:
                    return "700 Hz";
                    break;
                case FreqLowCutValue::_750hz:
                    return "750 Hz";
                    break;
                case FreqLowCutValue::_800hz:
                    return "800 Hz";
                    break;
                case FreqLowCutValue::_850hz:
                    return "850 Hz";
                    break;
                case FreqLowCutValue::_900hz:
                    return "900 Hz";
                    break;
                case FreqLowCutValue::_950hz:
                    return "850 Hz";
                    break;
                case FreqLowCutValue::_1000hz:
                    return "1000 Hz";
                    break;
                default:
                    return "";
                }
            }

            std::string DisplayFreqHighCut(FreqHighCutValue v)
            {
                switch (v)
                {
                case FreqHighCutValue::OFF:
                    return "OFF";
                    break;
                case FreqHighCutValue::_700hz:
                    return "700 Hz";
                    break;
                case FreqHighCutValue::_750hz:
                    return "750 Hz";
                    break;
                case FreqHighCutValue::_800hz:
                    return "800 Hz";
                    break;
                case FreqHighCutValue::_850hz:
                    return "850 Hz";
                    break;
                case FreqHighCutValue::_900hz:
                    return "900 Hz";
                    break;
                case FreqHighCutValue::_950hz:
                    return "950 Hz";
                    break;
                case FreqHighCutValue::_1000hz:
                    return "1000 Hz";
                    break;
                case FreqHighCutValue::_1050hz:
                    return "1050 Hz";
                    break;
                case FreqHighCutValue::_1100hz:
                    return "1100 Hz";
                    break;
                case FreqHighCutValue::_1150hz:
                    return "1150 Hz";
                    break;
                case FreqHighCutValue::_2000hz:
                    return "2000 Hz";
                    break;
                case FreqHighCutValue::_2050hz:
                    return "2050 Hz";
                    break;
                case FreqHighCutValue::_2100hz:
                    return "2100 Hz";
                    break;
                case FreqHighCutValue::_2150hz:
                    return "2150 Hz";
                    break;
                case FreqHighCutValue::_2200hz:
                    return "2200 Hz";
                    break;
                case FreqHighCutValue::_2250hz:
                    return "2250 Hz";
                    break;
                case FreqHighCutValue::_2300hz:
                    return "2300 Hz";
                    break;
                case FreqHighCutValue::_2350hz:
                    return "2350 Hz";
                    break;
                case FreqHighCutValue::_2400hz:
                    return "2400 Hz";
                    break;
                case FreqHighCutValue::_2450hz:
                    return "2450 Hz";
                    break;
                case FreqHighCutValue::_2500hz:
                    return "2500 Hz";
                    break;
                case FreqHighCutValue::_2550hz:
                    return "2550 Hz";
                    break;
                case FreqHighCutValue::_2600hz:
                    return "2600 Hz";
                    break;
                case FreqHighCutValue::_2650hz:
                    return "2650 Hz";
                    break;
                case FreqHighCutValue::_2700hz:
                    return "2700 Hz";
                    break;
                case FreqHighCutValue::_2750hz:
                    return "2750 Hz";
                    break;
                case FreqHighCutValue::_2800hz:
                    return "2800 Hz";
                    break;
                case FreqHighCutValue::_2850hz:
                    return "2850 Hz";
                    break;
                case FreqHighCutValue::_2900hz:
                    return "2900 Hz";
                    break;
                case FreqHighCutValue::_2950hz:
                    return "2950 Hz";
                    break;
                case FreqHighCutValue::_3000hz:
                    return "3000 Hz";
                    break;
                case FreqHighCutValue::_3050hz:
                    return "3050 Hz";
                    break;
                case FreqHighCutValue::_3100hz:
                    return "3100 Hz";
                    break;
                case FreqHighCutValue::_3150hz:
                    return "3150 Hz";
                    break;
                case FreqHighCutValue::_3200hz:
                    return "3200 Hz";
                    break;
                case FreqHighCutValue::_3250hz:
                    return "3250 Hz";
                    break;
                case FreqHighCutValue::_3300hz:
                    return "3300 Hz";
                    break;
                case FreqHighCutValue::_3350hz:
                    return "3350 Hz";
                    break;
                case FreqHighCutValue::_3400hz:
                    return "3400 Hz";
                    break;
                case FreqHighCutValue::_3450hz:
                    return "3450 Hz";
                    break;
                case FreqHighCutValue::_3500hz:
                    return "3500 Hz";
                    break;
                case FreqHighCutValue::_3550hz:
                    return "3550 Hz";
                    break;
                case FreqHighCutValue::_3600hz:
                    return "3600 Hz";
                    break;
                case FreqHighCutValue::_3650hz:
                    return "3650 Hz";
                    break;
                case FreqHighCutValue::_3700hz:
                    return "3700 Hz";
                    break;
                case FreqHighCutValue::_3750hz:
                    return "3750 Hz";
                    break;
                case FreqHighCutValue::_3800hz:
                    return "3800 Hz";
                    break;
                case FreqHighCutValue::_3850hz:
                    return "3850 Hz";
                    break;
                case FreqHighCutValue::_3900hz:
                    return "3900 Hz";
                    break;
                case FreqHighCutValue::_3950hz:
                    return "3950 Hz";
                    break;
                case FreqHighCutValue::_4000hz:
                    return "4000 Hz";
                    break;
                default:
                    return "";
                }
            }

            std::string DisplayPTTSelect(PTTSelectValue v)
            {
                switch (v)
                {
                case PTTSelectValue::DAKY:
                    return "DAKY";
                    break;
                case PTTSelectValue::DTR:
                    return "DTR";
                    break;
                case PTTSelectValue::RTS:
                    return "RTS";
                    break;
                default:
                    return "";
                }
            }

            std::string DisplayCwAutoMode(CwAutoModeValue v)
            {
                switch (v)
                {
                case CwAutoModeValue::OFF:
                    return "OFF";
                    break;
                case CwAutoModeValue::ON:
                    return "ON";
                    break;
                case CwAutoModeValue::_50M:
                    return "50M";
                    break;
                default:
                    return "";
                }
            }

            std::string DisplayBFO(BfoValue v)
            {
                switch (v)
                {
                case BfoValue::USB:
                    return "USB";
                    break;
                case BfoValue::LSB:
                    return "LSB";
                    break;
                case BfoValue::AUTO:
                    return "AUTO";
                    break;
                default:
                    return "";
                }
            }

            std::string DisplayPCKeying(PCKeyingValue v)
            {
                switch (v)
                {
                case PCKeyingValue::OFF:
                    return "OFF";
                    break;
                case PCKeyingValue::DKAY:
                    return "DKAY";
                    break;
                case PCKeyingValue::RTS:
                    return "RTS";
                    break;
                case PCKeyingValue::DTR:
                    return "DTR";
                    break;
                default:
                    return "";
                }
            }

            std::string DisplayBFO(DataBfoValue v)
            {
                switch (v)
                {
                case DataBfoValue::USB:
                    return "USB";
                    break;
                case DataBfoValue::LSB:
                    return "LSB";
                    break;
                default:
                    return "";
                }
            }

            std::string DisplayQskDelay(QskDelayTimeValue v)
            {
                switch (v)
                {
                case QskDelayTimeValue::_15msec:
                    return "15 msec";
                    break;
                case QskDelayTimeValue::_20msec:
                    return "20 msec";
                    break;
                case QskDelayTimeValue::_25msec:
                    return "25 msec";
                    break;
                case QskDelayTimeValue::_30msec:
                    return "30 msec";
                    break;
                default:
                    return "";
                }
            }

            std::string DisplayPSKTone(PSKToneValue v)
            {
                switch (v)
                {
                case PSKToneValue::_1000hz:
                    return "1000 Hz";
                    break;
                case PSKToneValue::_1500hz:
                    return "1500 Hz";
                    break;
                case PSKToneValue::_2000hz:
                    return "2000 Hz";
                    break;
                default:
                    return "";
                }
            }

            std::string DisplayDCSPolarity(DCSPolarityValue v)
            {
                switch (v)
                {
                case DCSPolarityValue::Tn_Rn:
                    return "Tn-Rn";
                    break;
                case DCSPolarityValue::Tn_Riv:
                    return "Tn-Riv";
                    break;
                case DCSPolarityValue::Tiv_Rn:
                    return "Tiv-Rn";
                    break;
                case DCSPolarityValue::Tiv_Riv:
                    return "Tiv-Riv";
                    break;
                default:
                    return "";
                }
            }

            std::string DisplayRTTYShiftPort(RTTYShiftPortValue v)
            {
                switch (v)
                {
                case RTTYShiftPortValue::SHIFT:
                    return "SHIFT";
                    break;
                case RTTYShiftPortValue::DTR:
                    return "DTR";
                    break;
                case RTTYShiftPortValue::RTS:
                    return "RTS";
                    break;
                default:
                    return "";
                }
            }

            std::string DisplayRTTYShiftFreq(RTTYShiftFreqValue v)
            {
                switch (v)
                {
                case RTTYShiftFreqValue::_170hz:
                    return "170 Hz";
                    break;
                case RTTYShiftFreqValue::_200hz:
                    return "200 Hz";
                    break;
                case RTTYShiftFreqValue::_425hz:
                    return "425 Hz";
                    break;
                case RTTYShiftFreqValue::_850hz:
                    return "850 Hz";
                default:
                    return "";
                }
            }

            std::string DisplayRTTYMarkFreq(RTTYMarkFreq v)
            {
                switch (v)
                {
                case RTTYMarkFreq::_1275hz:
                    return "1275 Hz";
                    break;
                case RTTYMarkFreq::_2125hz:
                    return "2125 Hz";
                    break;
                default:
                    return "";
                }
            }

            std::string DisplaySSBTxBandPass(SSBTXBandPassValue v)
            {
                switch (v)
                {
                case SSBTXBandPassValue::_100_3000:
                    return "100-3000";
                    break;
                case SSBTXBandPassValue::_100_2900:
                    return "100-2900";
                    break;
                case SSBTXBandPassValue::_200_2800:
                    return "200-2800";
                    break;
                case SSBTXBandPassValue::_300_2700:
                    return "300-2700";
                    break;
                case SSBTXBandPassValue::_400_2600:
                    return "400-2600";
                    break;
                default:
                    return "";
                }
            }

            std::string DisplayAPWidth(APFWidthValue v)
            {
                switch (v)
                {
                case APFWidthValue::NARROW:
                    return "NARROW";
                    break;
                case APFWidthValue::MEDIUM:
                    return "MEDIUM";
                    break;
                case APFWidthValue::WIDE:
                    return "WIDE";
                    break;
                default:
                    return "";
                }
            }

            std::string DisplaySCPStart(SCPStartCycleValue v)
            {
                switch (v)
                {
                case SCPStartCycleValue::OFF:
                    return "OFF";
                    break;
                case SCPStartCycleValue::_3sec:
                    return "3 sec";
                    break;
                case SCPStartCycleValue::_5sec:
                    return "5 sec";
                    break;
                case SCPStartCycleValue::_10sec:
                    return"10 sec";
                    break;
                default:
                    return "";
                }
            }

            std::string DisplaySCPSpanFreq(SCPSpanFreqValue v)
            {
                switch (v)
                {
                case SCPSpanFreqValue::_37_5khz:
                    return "37.5 kHz";
                    break;
                case SCPSpanFreqValue::_75khz:
                    return "75 Khz";
                    break;
                case SCPSpanFreqValue::_150khz:
                    return "150 kHz";
                    break;
                case SCPSpanFreqValue::_375khz:
                    return "375 kHz";
                    break;
                case SCPSpanFreqValue::_750khz:
                    return "750 kHz";
                    break;
                default:
                    return "";
                }
            }

            std::string DisplayQuickDial(QuickDialValue v)
            {
                switch (v)
                {
                case QuickDialValue::_50khz:
                    return "50 kHz";
                    break;
                case QuickDialValue::_100khz:
                    return "100 kHz";
                    break;
                case QuickDialValue::_500khz:
                    return "500 kHz";
                    break;
                default:
                    return "";
                }
            }

            std::string DisplaySSBDialStep(SSBDialStep v)
            {
                switch (v)
                {
                case SSBDialStep::_2hz:
                    return "2 Hz";
                    break;
                case SSBDialStep::_5hz:
                    return "5 Hz";
                    break;
                case SSBDialStep::_10hz:
                    return "10 Hz";
                    break;
                default:
                    return "";
                }
            }

            std::string DisplayAmFMDialStep(AMDialStep v)
            {
                switch (v)
                {
                case AMDialStep::_10Hz:
                    return "10 Hz";
                    break;
                case AMDialStep::_100Hz:
                    return "100 Hz";
                default:
                    return "";
                }
            }

            std::string DisplayAmFMDialStep(FMDialStep v)
            {
                switch (v)
                {
                case FMDialStep::_10Hz:
                    return "10 Hz";
                    break;
                case FMDialStep::_100Hz:
                    return "100 Hz";
                default:
                    return "";
                }
            }

            std::string DisplayDialStep(DialStep v)
            {
                switch (v)
                {
                case DialStep::_2hz:
                    return "2 Hz";
                    break;
                case DialStep::_5hz:
                    return "5 Hz";
                    break;
                case DialStep::_10hz:
                    return "10 Hz";
                    break;
                default:
                    return "";
                }
            }

            std::string DisplayMonitorFunction(MonitorFunction v)
            {
                switch (v)
                {
                case MonitorFunction::MontiorLevel:
                    return "Monitor Level";
                case MonitorFunction::MontiorOnOff:
                    return "Monitor On/Off";
                default:
                    return "";
                }
            }

            std::string DisplayCTCSSState(CTCSSState v)
            {
                switch (v)
                {
                case CTCSSState::CTCSS_OFF:
                    return "OFF";
                case CTCSSState::CTCSS_ENC_DEC_ON:
                    return "ENC DEC";
                case CTCSSState::CTCSS_ENC_ON:
                    return "ENC";
                case CTCSSState::CTCSS_DCS_ON:
                    return "DCS";
                default:
                    return "";
                }
            }

            std::string DisplayAMChStep(AMChannelStepValue v)
            {
                switch (v)
                {
                case AMChannelStepValue::_2_5khz:
                    return "2.5 kHz";
                case AMChannelStepValue::_5khz:
                    return "5 kHz";
                case AMChannelStepValue::_9khz:
                    return "9 kHz";
                case AMChannelStepValue::_10khz:
                    return "10 kHz";
                case AMChannelStepValue::_12_5khz:
                    return "12.5 kHz";
                case AMChannelStepValue::_25khz:
                    return "25 kHz";
                default:
                    return "";

                }
            }

            std::string DisplayFMChStep(FMChannelStepValue v)
            {
                switch (v)
                {
                case FMChannelStepValue::_5kHz:
                    return "5 kHz";
                case FMChannelStepValue::_6_26kHz:
                    return "6.5 kHz";
                case FMChannelStepValue::_10kHz:
                    return "10 kHz";
                case FMChannelStepValue::_12_5kHz:
                    return "12.5 kHz";
                case FMChannelStepValue::_15kHz:
                    return "15 kHz";
                case FMChannelStepValue::_20kHz:
                    return "20 kHz";
                case FMChannelStepValue::_25kHz:
                    return "26 kHz";
                default:
                    return "";

                }
            }

            std::string DisplayMemoryChannelValue(MemoryChannelValue v)
            {

                switch (v)
                {
                case MemoryChannelValue::P1L:
                    return "P1L";
                    break;
                case MemoryChannelValue::P1U:
                    return "P1U";
                    break;
                case MemoryChannelValue::P2L:
                    return "P2L";
                    break;
                case MemoryChannelValue::P2U:
                    return "P2U";
                    break;
                case MemoryChannelValue::P3L:
                    return "P3L";
                    break;
                case MemoryChannelValue::P3U:
                    return "P3U";
                    break;
                case MemoryChannelValue::P4L:
                    return "P4L";
                    break;
                case MemoryChannelValue::P4U:
                    return "P4U";
                    break;
                case MemoryChannelValue::P5L:
                    return "P5L";
                    break;
                case MemoryChannelValue::P5U:
                    return "P5U";
                    break;
                case MemoryChannelValue::P6L:
                    return "P6L";
                    break;
                case MemoryChannelValue::P6U:
                    return "P6U";
                    break;
                case MemoryChannelValue::P7L:
                    return "P7L";
                    break;
                case MemoryChannelValue::P7U:
                    return "P7U";
                    break;
                case MemoryChannelValue::P8L:
                    return "P8L";
                    break;
                case MemoryChannelValue::P8U:
                    return "P8U";
                    break;
                case MemoryChannelValue::P9L:
                    return "P9L";
                    break;
                case MemoryChannelValue::P9U:
                    return "P9U";
                    break;
                case MemoryChannelValue::_5351_5mhz:
                    return "5335.5 MHz";
                case MemoryChannelValue::_5354mhz:
                    return "5354 MHz";
                case MemoryChannelValue::_5357mhz:
                    return "5357 Mhz";
                case MemoryChannelValue::_5360mhz:
                    return "5360 Mhz";
                case MemoryChannelValue::_5363mhz:
                    return "5363 MHz";
                case MemoryChannelValue::_5366mhz:
                    return "5366 MHz";
                case MemoryChannelValue::EMG:
                    return "EMG";
                default:
                    return fmt::format("Channel {:d}", static_cast<int>(v));
                }
            }

            std::string DisplayEQ1Value(EQ1FreqValue v)
            {
                switch (v)
                {
                case EQ1FreqValue::OFF:
                    return "OFF";
                case EQ1FreqValue::_100Hz:
                    return "100 Hz";
                case EQ1FreqValue::_200Hz:
                    return "200 Hz";
                case EQ1FreqValue::_300Hz:
                    return "300 Hz";
                case EQ1FreqValue::_400Hz:
                    return "400 Hz";
                case EQ1FreqValue::_500Hz:
                    return "500 Hz";
                case EQ1FreqValue::_600Hz:
                    return "600 Hz";
                case EQ1FreqValue::_700Hz:
                    return "700 Hz";
                default:
                    return "";
                }
            }

            std::string DisplayEQ2Value(EQ2FreqValue v)
            {
                switch (v)
                {
                case EQ2FreqValue::OFF:
                    return "OFF";
                case EQ2FreqValue::_700Hz:
                    return "700 Hz";
                case EQ2FreqValue::_800Hz:
                    return "800 Hz";
                case EQ2FreqValue::_900Hz:
                    return "900 Hz";
                case EQ2FreqValue::_1000Hz:
                    return "1000 Hz";
                case EQ2FreqValue::_1100Hz:
                    return "1100 Hz";
                case EQ2FreqValue::_1200Hz:
                    return "1200 Hz";
                case EQ2FreqValue::_1300Hz:
                    return "1300 Hz";
                case EQ2FreqValue::_1400Hz:
                    return "1400 Hz";
                default:
                    return "";
                }
            }

            std::string DisplayEQ3Value(EQ3FreqValue v)
            {
                switch (v)
                {
                case EQ3FreqValue::OFF:
                    return "OFF";
                case EQ3FreqValue::_1500Hz:
                    return "1500 Hz";
                case EQ3FreqValue::_1600Hz:
                    return "1600 Hz";
                case EQ3FreqValue::_1700Hz:
                    return "1700 Hz";
                case EQ3FreqValue::_1800Hz:
                    return "1800 Hz";
                case EQ3FreqValue::_1900Hz:
                    return "1900 Hz";
                case EQ3FreqValue::_2000Hz:
                    return "2000 Hz";
                case EQ3FreqValue::_2100Hz:
                    return "2100 Hz";
                case EQ3FreqValue::_2200Hz:
                    return "2200 Hz";
                case EQ3FreqValue::_2300Hz:
                    return "2300 Hz";
                case EQ3FreqValue::_2400Hz:
                    return "2400 Hz";
                case EQ3FreqValue::_2500Hz:
                    return "2500 Hz";
                case EQ3FreqValue::_2600Hz:
                    return "2600 Hz";
                case EQ3FreqValue::_2700Hz:
                    return "2700 Hz";
                case EQ3FreqValue::_2800Hz:
                    return "2800 Hz";
                case EQ3FreqValue::_2900Hz:
                    return "2900 Hz";
                case EQ3FreqValue::_3000Hz:
                    return "3000 Hz";
                case EQ3FreqValue::_3100Hz:
                    return "3100 Hz";
                case EQ3FreqValue::_3200Hz:
                    return "3200 Hz";
                default:
                    return "";
                }
            }

            std::string DisplayTunerSelect(TunerSelectValue v)
            {
                switch (v)
                {
                case TunerSelectValue::OFF:
                    return "OFF";
                case TunerSelectValue::EXTERNAL:
                    return "EXTERNAL";
                case TunerSelectValue::ATAS:
                    return "ATAS";
                case TunerSelectValue::LAMP:
                    return "LAMP";
                default:
                    return "";
                }
            }

            std::string DisplayMenuFunction(MenuFunction f)
            {
                std::string ret = fmt::format("{:04}", static_cast<int>(f));
                return ret.substr(0, 2) + "-" + ret.substr(2, 2);
            }

            std::string DisplayWidthState(WidthState v)
            {
                return DisplayOnOffValue(v);
            }

            std::string DisplayScanState(ScanState v)
            {
                switch (v)
                {
                case ScanState::UP:
                    return "UP";
                case ScanState::DOWN:
                    return "DOWN";
                case ScanState::OFF:
                    return "OFF";
                default:
                    return "";
                }
            }

            std::string DisplayRadioStatus(RadioStatusValue v)
            {
                switch (v)
                {
                case RadioStatusValue::MENU:
                    return "MENU";
                case RadioStatusValue::NORMAL:
                    return "NORMAL";
                default:
                    return "";
                }
            }

            std::string DisplayReadMeterType(ReadMeterType v)
            {
                switch (v)
                {
                    case ReadMeterType::AutoA:
                        return "AUTO";
                    case ReadMeterType::S:
                        return "S";
                    case ReadMeterType::AutoB:
                        return "AUTO";
                    case ReadMeterType::COMP:
                        return "COMP";
                    case ReadMeterType::ALC:
                        return "ALC";
                    case ReadMeterType::PO:
                        return "PO";
                    case ReadMeterType::SWR:
                        return "SWR";
                    case ReadMeterType::ID:
                        return "IDD";
                    default:
                        return "";
                }
            }

            std::string DisplayPowerSwitch(PowerSwitchValue v)
            {
                return DisplayOnOffValue(v);
            }

            std::string DisplaySpeechProcessorState(SpeechProcessorState v)
            {
                return DisplayOnOffValue(v);
            }

            std::string DisplaySpeechProcessorType(SpeechProcessorType v)
            {
                switch (v)
                {
                case SpeechProcessorType::ParametricEqualizer:
                    return "Parametric Equalizer";
                case SpeechProcessorType::Processor:
                    return "Processor";
                default:
                    return "";
                }
            }

            std::string DisplayMemoryChannelModeValue(MemoryChannelModeValue v)
            {
                switch (v)
                {
                case MemoryChannelModeValue::AM:
                    return "AM";
                case MemoryChannelModeValue::AM_N:
                    return "AM-N";
                case MemoryChannelModeValue::CW:
                    return "CW";
                case MemoryChannelModeValue::CW_R:
                    return "CW-R";
                case MemoryChannelModeValue::DATA_LSB:
                    return "DATA LSB";
                case MemoryChannelModeValue::DATA_USB:
                    return "DATA USB";
                case MemoryChannelModeValue::FM:
                    return "FM";
                case MemoryChannelModeValue::FM_N:
                    return "FM-N";
                case MemoryChannelModeValue::LSB:
                    return "LSB";
                case MemoryChannelModeValue::USB:
                    return "DATA USB";
                case MemoryChannelModeValue::RTTY_LSB:
                    return "RTTY LSB";
                case MemoryChannelModeValue::RTTY_USB:
                    return "RTTY USB";
                default:
                    return "";
                }
            }

            std::string DisplayIfShift(IfShiftValue v)
            {
                return DisplayOnOffValue(v);
            }

            std::string DisplayRFAttenuatorState(RfAttenuatorState v)
            {
                return DisplayOnOffValue(v);
            }

            std::string DisplayTagValue(TagValue v)
            {
                return DisplayOnOffValue(v);
            }

            std::string DisplayMonitorOnOffValue(MonitorOnOffValue v)
            {
                return DisplayOnOffValue(v);
            }

            std::string DisplayBusyState(BusyState v)
            {
                return DisplayOnOffValue(v);
            }

            std::string DisplayClarifierState(ClarifierState v)
            {
                return DisplayOnOffValue(v);
            }

            std::string DisplayDialLockValue(DialLockValue v)
            {
                return DisplayOnOffValue(v);
            }

            std::string DisplayKeyerValue(KeyerValue v)
            {
                return DisplayOnOffValue(v);
            }

            std::string DisplayInformationType(InformationType v)
            {
                switch (v)
                {
                case InformationType::HI_SWR:
                    return "HIGH SWR";
                case InformationType::REC:
                    return "REC";
                case InformationType::PLAY:
                    return "PLAY";
                case InformationType::TX_LED:
                    return "TX LED";
                case InformationType::RX_LED:
                    return "RX LED";
                default:
                    return "";
                }
            }

            std::string DisplayModeValue(ModeValue v)
            {
                switch (v)
                {
                case ModeValue::SSB_BFOA:
                    return "SSB BFOA";
                case ModeValue::SSB_BFOB:
                    return "SSB BFOB";
                case ModeValue::CW:
                    return "CW";
                case ModeValue::FM:
                    return "FM";
                case ModeValue::AM:
                    return "AM";
                case ModeValue::RTTY_BFOA:
                    return "RTTY BFOA";
                case ModeValue::CW_BFOA:
                    return "CW BFOA";
                case ModeValue::DATA_BFOA:
                    return "DATA BFOA";
                case ModeValue::RTTY_BFOB:
                    return "RTTY BFOB";
                case ModeValue::FM_N:
                    return "FM-N";
                case ModeValue::DATA_BFOB:
                    return "DATA BFOB";
                case ModeValue::AM_N:
                    return "AM-N";
                default:
                    return "";
                }
            }

            std::string DisplayOperationType(OperationType v)
            {
                switch (v)
                {
                case OperationType::Simplex:
                    return "Simplex";
                    break;
                case OperationType::MinusShift:
                    return "- Shift";
                    break;
                case OperationType::PlusShift:
                    return "+ Shift";
                default:
                    return "";
                }
            }

            std::string DisplayVFOChannelType(VFOChannelTypeValue v)
            {
                switch (v)
                {
                case VFOChannelTypeValue::VFO:
                    return "VFO";
                case VFOChannelTypeValue::Memory:
                    return "MEMORY";
                case VFOChannelTypeValue::MemoryTune:
                    return "MEMORY TUNE";
                case VFOChannelTypeValue::QuickMemoryBank:
                    return "QMB";
                case VFOChannelTypeValue::QMB_MT:
                    return "QMB MT";
                case VFOChannelTypeValue::PMS:
                    return "PMS";
                case VFOChannelTypeValue::HOME:
                    return "HOME";
                default:
                    return "";
                }
            }

            std::string DisplayKeyerMemory(KeyerMemoryChannel v)
            {
                switch (v)
                {
                case KeyerMemoryChannel::Memory1:
                    return "Memory 1";
                case KeyerMemoryChannel::Memory2:
                    return "Memory 2";
                case KeyerMemoryChannel::Memory3:
                    return "Memory 3";
                case KeyerMemoryChannel::Memory4:
                    return "Memory 4";
                case KeyerMemoryChannel::Memory5:
                    return "Memory 5";
                case KeyerMemoryChannel::Message1:
                    return "Message 1";
                case KeyerMemoryChannel::Message2:
                    return "Message 2";
                case KeyerMemoryChannel::Message3:
                    return "Message 3";
                case KeyerMemoryChannel::Message4:
                    return "Message 4";
                case KeyerMemoryChannel::Message5:
                    return "Message 5";
                default:
                    return "";
                }
            }

            std::string DisplayNotchState(NotchState v)
            {
                return DisplayOnOffValue(v);
            }

            std::string DisplayInformationState(InformationState v)
            {
                return DisplayOnOffValue(v);
            }

            std::string DisplayBreakInState(BreakInState v)
            {
                return DisplayOnOffValue(v);
            }

            std::string DisplayCwSpotState(CWSpotState v)
            {
                return DisplayOnOffValue(v);
            }

        };
    };
};
