#include "Cat.h"
#include <fmt/core.h>

namespace Yeasu {
	namespace FT891 {
		namespace Commands {
			std::string VFO_A_TO_VFO_B::Set()
			{
				return "AB;";
			}

			std::string AntennaTunerControl::Set(TunerState state)
			{
				std::string str = fmt::format("AC00{};", (int)state);
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
				return fmt::format("AG0{:0>3};", Value);
			}

			std::string VolumeLevel::Read()
			{
				return "AG0;";
			}

			int VolumeLevel::Answer(std::string data)
			{
				return std::stoi(&data[3]);
			}

			std::string AutoInformation::Set(InformationState Value)
			{
				std::string str = fmt::format("AI{};", Value);
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
				std::string str = fmt::format("BC0{:d};", Value);
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
				std::string str = fmt::format("BI{};", (char)Value);
				return str.c_str();
			}

			std::string BreakIn::Read() { return "BI;"; }

			BreakInState BreakIn::Answer(std::string data)
			{
				return (BreakInState)data[2];
			}

			std::string ManualNotch::Set(ManualNotchValue val)
			{

				std::string str = fmt::format("BP0{:d}{:0>3};", val.Command, val.Value.iValue);
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
				std::string str = fmt::format("BS{:0>2};", (int)Value);
				return str.c_str();
			}

			std::string BandUP::Set() { return "BU0;"; }

			std::string Busy::Read(BusyState Value)
			{
				return "BY;";
			}

			BusyState Busy::Answer(std::string data)
			{
				return (BusyState)std::stoi(data.substr(2, 1));
			}

			std::string Clarifier::Set(ClarifierState Value)
			{
				std::string str = fmt::format("CF0{:d}0;", Value);
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
				std::string str = fmt::format("CH{:d};", Value);
				return str.c_str();
			}

			std::string CTCSSToneFrequency::Set(CTCSSToneFreqencyValue val)
			{
				std::string str = fmt::format("CN0{:d}{:0>3};", val.Mode, val.Value);
				return str.c_str();
			}

			std::string CTCSSToneFrequency::Read(CTCSSModeType Mode)
			{
				std::string str = fmt::format("CN0{:d};", Mode);
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
				std::string str = fmt::format("CO0{:d}{:04};", val.Type, val.Value.Freq);
				return str;
			}

			std::string Contour::Read(ContourValue Type)
			{
				std::string str = fmt::format("CO0{:d};", Type.Type);
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
				std::string str = fmt::format("CS{:d};", Value);
				return str;
			}

			std::string CWSpot::Read() { return "CS;"; }

			CWSpotState CWSpot::Answer(std::string data)
			{
				return (CWSpotState)std::stoi(data.substr(2, 1));
			}

			std::string CTCSS::Set(CTCSSState Value)
			{
				std::string str = fmt::format("CT0{:d};", Value);
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
				str += fmt::format("{:0>2}{:0>2}{:0>2}{:0>2};", (int)val.LCD_Contrast, (int)val.BacklightLevel, (int)val.LCD_Level, (int)val.TX_Indicator);
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
				std::string str = "ED";
				str += (char)enc;
				str += fmt::format("{:0>2};", Steps);
				return str.c_str();
			}

			std::string EnterKey::Set() { return "EK;"; }

			std::string EncoderUp::Set(EncoderType enc, int Steps)
			{
				if (Steps > 99) Steps = 99;
				if (Steps < 1) Steps = 1;
				std::string str = fmt::format("EU{}{:0>2};", (char)enc, Steps);
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
				std::string val = fmt::format("{:04}{:03}", MenuFunction::AGC_FAST_DELAY, msecs);
				return set(val);
			}

			std::string Menu::ReadAgcFastDelay()
			{
				std::string s = fmt::format("{:04}", MenuFunction::AGC_FAST_DELAY);
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
				std::string val = fmt::format("{:04}{:0>3}", MenuFunction::AGC_MID_DELAY, msecs);
				return set(val);
			}

			std::string Menu::ReadAgcMidDelay()
			{
				std::string s = fmt::format("{:04}", MenuFunction::AGC_MID_DELAY);
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
				std::string val = fmt::format("{:04}{:04}", MenuFunction::AGC_SLOW_DELAY, msecs);
				return set(val);
			}

			std::string Menu::ReadAgcSlowDelay()
			{
				std::string s = fmt::format("{:04}", MenuFunction::AGC_SLOW_DELAY);
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
				std::string val = fmt::format("{:04}{:0>2}", MenuFunction::LCD_CONTRAST, level);
				return set(val);
			}

			std::string Menu::ReadLcdContrast()
			{
				std::string val = fmt::format("{:04}", MenuFunction::LCD_CONTRAST);
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
				std::string val = fmt::format("{:04}{:0>2}", MenuFunction::DIMMER_BACKLIT, level);
				return set(val);
			}

			std::string Menu::ReadBackliteDimmer()
			{
				std::string val = fmt::format("{:04}", MenuFunction::DIMMER_BACKLIT);
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
				std::string val = fmt::format("{:04}{:0>2}", MenuFunction::DIMMER_LCD, level);

				return set(val);
			}

			std::string Menu::ReadLcdDimmer()
			{
				std::string val = fmt::format("{:04}", MenuFunction::DIMMER_LCD);
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
				std::string val = fmt::format("{:04}{:02}", MenuFunction::DIMMER_TX_BUSY, level);

				return set(val);
			}

			std::string Menu::ReadTxBusyDimmer()
			{
				std::string val = fmt::format("{:04}", MenuFunction::DIMMER_TX_BUSY);
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
				std::string s = fmt::format("{:04}", MenuFunction::PEAK_HOLD);
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
				std::string s = fmt::format("{:04}", MenuFunction::PEAK_HOLD);
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
				std::string s = fmt::format("{:04}{:d}", MenuFunction::ZIN_LED, value);

				return set(s);
			}

			std::string Menu::ReadZinLed()
			{
				std::string s = fmt::format("{:04}", MenuFunction::ZIN_LED);
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
				std::string s = fmt::format("{:04}{:d}", MenuFunction::POPUP_MENU, style);

				return set(s);
			}

			std::string Menu::ReadPopupMenuStyle()
			{
				std::string s = fmt::format("{:04}", MenuFunction::POPUP_MENU);
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
				std::string s = fmt::format("{:04}{:03}", MenuFunction::DVS_RX_OUT_LVL, Level);
				return set(s);
			}

			std::string Menu::ReadDvsRxOutLevel()
			{
				std::string s = fmt::format("{:04}", MenuFunction::DVS_RX_OUT_LVL);
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
				std::string s = fmt::format("{:04}{:03}", MenuFunction::DVS_TX_OUT_LVL, Level);

				return set(s);
			}

			std::string Menu::ReadDvsTxOutLevel()
			{
				std::string s = fmt::format("{:04}", MenuFunction::DVS_TX_OUT_LVL);
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
				std::string s = fmt::format("{:04}{:d}", MenuFunction::KEYER_TYPE, val);
				return set(s);
			}

			std::string Menu::ReadKeyerType()
			{
				std::string s = fmt::format("{:04}", MenuFunction::KEYER_TYPE);
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
				std::string s = fmt::format("{:04}{:d}", MenuFunction::KEYER_DOT_DASH_ORDER, val);
				return set(s);
			}

			std::string Menu::ReadKeyerDotDash()
			{
				std::string s = fmt::format("{:04}", MenuFunction::KEYER_DOT_DASH_ORDER);
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
				std::string s = fmt::format("{:04}{:02}", MenuFunction::CW_WEIGHT, Weight);
				return set(s);
			}

			std::string Menu::ReadCwWeight()
			{
				std::string s = fmt::format("{:04}", MenuFunction::CW_WEIGHT);
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
				std::string s = fmt::format("{:04}{:03}", MenuFunction::BEACON_INTERVAL, value);
				return set(s);
			}

			std::string Menu::ReadBeaconInterval()
			{
				std::string s = fmt::format("{:04}", MenuFunction::BEACON_INTERVAL);
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
				std::string s = fmt::format("{:04}{:d}", MenuFunction::NUMBER_STYLE, val);
				return set(s);
			}

			std::string Menu::ReadNumberStyle()
			{
				std::string s = fmt::format("{:04}", MenuFunction::NUMBER_STYLE);
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
				std::string s = fmt::format("{:04}{:04}", MenuFunction::CONTEST_NUMBER, Value);
				return set(s);
			}

			std::string Menu::ReadContestNumber()
			{
				std::string s = fmt::format("{:04}", MenuFunction::CONTEST_NUMBER);
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
				std::string s = fmt::format("{:04}{:d}", MenuFunction::CW_MEMORY_1, (int)val);
				return set(s);
			}

			std::string Menu::ReadCWMemory1()
			{
				std::string s = fmt::format("{:04}", MenuFunction::CW_MEMORY_1);
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
				std::string s = fmt::format("{:04}{:d}", MenuFunction::CW_MEMORY_2, (int)val);

				return set(s);
			}

			std::string Menu::ReadCWMemory2()
			{
				std::string s = fmt::format("{:04}", MenuFunction::CW_MEMORY_2);
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
				std::string s = fmt::format("{:04}{:d}", MenuFunction::CW_MEMORY_3, (int)val);

				return set(s);
			}

			std::string Menu::ReadCWMemory3()
			{
				std::string s = fmt::format("{:04}", MenuFunction::CW_MEMORY_3);
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
				std::string s = fmt::format("{:04}{:d}", MenuFunction::CW_MEMORY_4, (int)val);
				return set(s);
			}

			std::string Menu::ReadCWMemory4()
			{
				std::string s = fmt::format("{:04}", MenuFunction::CW_MEMORY_4);
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
				std::string s = fmt::format("{:04}{:d}", MenuFunction::CW_MEMORY_5, (int)val);

				return set(s);
			}

			std::string Menu::ReadCWMemory5()
			{
				std::string s = fmt::format("{:04}", MenuFunction::CW_MEMORY_5);
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
				std::string s = fmt::format("{:04}{:d}", MenuFunction::NB_WIDTH, (int)value);
				return set(s);
			}

			std::string Menu::ReadNbWidth()
			{
				std::string s = fmt::format("{:04}", MenuFunction::NB_WIDTH);
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
				std::string s = fmt::format("{:04}{:d}", MenuFunction::NB_REJECTION, (int)value);
				return set(s);
			}

			std::string Menu::ReadNbRejection()
			{
				std::string s = fmt::format("{:04}", MenuFunction::NB_REJECTION);
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
				std::string s = fmt::format("{:04}{:d}", MenuFunction::NB_LEVEL, level);
				return set(s);
			}

			std::string Menu::ReadNbLevel()
			{
				std::string s = fmt::format("{:04}", MenuFunction::NB_LEVEL);
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
				std::string s = fmt::format("{:04}{:0>3}", MenuFunction::BEEP_LEVEL, level);
				return set(s);
			}

			std::string Menu::ReadBeepLevel()
			{
				std::string s = fmt::format("{:04}", MenuFunction::BEEP_LEVEL);
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
				std::string s = fmt::format("{:04}{:d}", MenuFunction::BEEP_LEVEL, (int)val);
				return set(s);
			}

			std::string Menu::ReadRfSqlVr()
			{
				std::string s = fmt::format("{:04}", MenuFunction::BEEP_LEVEL);
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
				std::string s = fmt::format("{:04}{:d}", MenuFunction::CAT_RATE, (int)val);
				return set(s);
			}

			std::string Menu::ReadCatRate()
			{
				std::string s = fmt::format("{:04}", MenuFunction::CAT_RATE);
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
				std::string s = fmt::format("{:04}{:d}", MenuFunction::CAT_TOT, (int)val);
				return set(s);
			}

			std::string Menu::ReadCatTOT()
			{
				std::string s = fmt::format("{:04}", MenuFunction::CAT_TOT);
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
				std::string s = fmt::format("{:04}{:d}", MenuFunction::CAT_RTS, (int)val);
				return set(s);
			}

			std::string Menu::ReadCatRTS()
			{
				std::string s = fmt::format("{:04}", MenuFunction::CAT_RTS);
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
				std::string s = fmt::format("{:04}{:d}", MenuFunction::MEM_GROUP, (int)val);
				return set(s);
			}

			std::string Menu::ReadMemGroup()
			{
				std::string s = fmt::format("{:04}", MenuFunction::MEM_GROUP);
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
				std::string s = fmt::format("{:04}{:d}", MenuFunction::FM_SETTING, (int)val);
				return set(s);
			}

			std::string Menu::ReadFMSetting()
			{
				std::string s = fmt::format("{:04}", MenuFunction::FM_SETTING);
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
				std::string s = fmt::format("{:04}{:d}", MenuFunction::REC_SETTING, (int)val);
				return set(s);
			}

			std::string Menu::ReadRecSetting()
			{
				std::string s = fmt::format("{:04}", MenuFunction::REC_SETTING);
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
				std::string s = fmt::format("{:04}{:d}", MenuFunction::ATAS_SETTING, (int)val);
				return set(s);
			}

			std::string Menu::ReadATASSetting()
			{
				std::string s = fmt::format("{:04}", MenuFunction::ATAS_SETTING);
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

				std::string s = fmt::format("{:04}{:+d}", MenuFunction::QUICK_SPL_FREQ, (int)val);
				return set(s);
			}

			std::string Menu::ReadQuickSplitFreq()
			{
				std::string s = fmt::format("{:04}", MenuFunction::QUICK_SPL_FREQ);
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
				std::string s = fmt::format("{:04}{:d}", MenuFunction::TX_TOT, (int)val);
				return set(s);
			}

			std::string Menu::ReadTXTOT()
			{
				std::string s = fmt::format("{:04}", MenuFunction::TX_TOT);
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
				std::string s = fmt::format("{:04}{:d}", MenuFunction::MIC_SCAN, (int)val);
				return set(s);
			}

			std::string Menu::ReadMicScan()
			{
				std::string s = fmt::format("{:04}", MenuFunction::MIC_SCAN);
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
				std::string s = fmt::format("{:04}{:d}", MenuFunction::MIC_SCAN_RESUME, (int)val);
				return set(s);
			}

			std::string Menu::ReadMicScanResume()
			{
				std::string s = fmt::format("{:04}", MenuFunction::MIC_SCAN_RESUME);
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

				std::string s = fmt::format("{:04}{:+03}", MenuFunction::REF_FEQ_ADJ, (int)val);
				return set(s);
			}

			std::string Menu::ReadRefFreqAdjust()
			{
				std::string s = fmt::format("{:04}", MenuFunction::REF_FEQ_ADJ);
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
				std::string s = fmt::format("{:04}{:d}", MenuFunction::CLAR_SELECT, (int)val);
				return set(s);
			}

			std::string Menu::ReadClarSelect()
			{
				std::string s = fmt::format("{:04}", MenuFunction::CLAR_SELECT);
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
				std::string s = fmt::format("{:04}{:d}", MenuFunction::APO, (int)val);
				return set(s);
			}

			std::string Menu::ReadApo()
			{
				std::string s = fmt::format("{:04}", MenuFunction::APO);
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
				std::string s = fmt::format("{:04}{:d}", MenuFunction::FAN_CONTROL, (int)val);
				return set(s);
			}

			std::string Menu::ReadFanControl()
			{
				std::string s = fmt::format("{:04}", MenuFunction::FAN_CONTROL);
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
				std::string s = fmt::format("{:04}{:02}", MenuFunction::AM_LCUT_FREQ, (int)val);
				return set(s);
			}

			std::string Menu::ReadAMLowCutFreq()
			{
				std::string s = fmt::format("{:04}", MenuFunction::AM_LCUT_FREQ);
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
				std::string s = fmt::format("{:04}{:d}", MenuFunction::AM_LCUT_SLOPE, (int)val);
				return set(s);
			}

			std::string Menu::ReadAMLowCutSlope()
			{
				std::string s = fmt::format("{:04}", MenuFunction::AM_LCUT_SLOPE);
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
				std::string s = fmt::format("{:04}{:02}", MenuFunction::AM_HCUT_FREQ, (int)val);
				return set(s);
			}

			std::string Menu::ReadAMHighCutFreq()
			{
				std::string s = fmt::format("{:04}", MenuFunction::AM_HCUT_FREQ);
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
				std::string s = fmt::format("{:04}{:d}", MenuFunction::AM_HCUT_SLOPE, (int)val);
				return set(s);
			}

			std::string Menu::ReadAMHighCutSlope()
			{
				std::string s = fmt::format("{:04}", MenuFunction::AM_HCUT_SLOPE);
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
				std::string s = fmt::format("{:04}{:d}", MenuFunction::AM_MIC_SELECT, (int)val);
				return set(s);
			}

			std::string Menu::ReadAMMicSelect()
			{
				std::string s = fmt::format("{:04}", MenuFunction::AM_MIC_SELECT);
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
				std::string s = fmt::format("{:04}{:03}", MenuFunction::AM_OUT_LEVEL, (int)val);
				return set(s);
			}

			std::string Menu::ReadAMOutLevel()
			{
				std::string s = fmt::format("{:04}", MenuFunction::AM_OUT_LEVEL);
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
				std::string s = fmt::format("{:04}{:03}", MenuFunction::AM_MIC_GAIN, (int)val);
				return set(s);
			}

			std::string Menu::ReadAMMicLevel()
			{
				std::string s = fmt::format("{:04}", MenuFunction::AM_MIC_GAIN);
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
				std::string s = fmt::format("{:04}{:d}", MenuFunction::AM_PTT_SELECT, (int)val);
				return set(s);
			}

			std::string Menu::ReadAMPTTSelect()
			{
				std::string s = fmt::format("{:04}", MenuFunction::AM_PTT_SELECT);
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
				std::string s = fmt::format("{:04}{:02}", MenuFunction::CW_LCUT_FREQ, (int)val);
				return set(s);
			}

			std::string Menu::ReadCWLowCutFreq()
			{
				std::string s = fmt::format("{:04}", MenuFunction::CW_LCUT_FREQ);
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
				std::string s = fmt::format("{:04}{:d}", MenuFunction::CW_LCUT_SLOPE, (int)val);
				return set(s);
			}

			std::string Menu::ReadCWLowCutSlope()
			{

				std::string s = fmt::format("{:04}", MenuFunction::CW_LCUT_SLOPE);
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
				std::string s = fmt::format("{:04}{:02}", MenuFunction::CW_HCUT_FREQ, (int)val);
				return set(s);
			}

			std::string Menu::ReadCWHighCutFreq()
			{
				std::string s = fmt::format("{:04}", MenuFunction::CW_HCUT_FREQ);
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
				std::string s = fmt::format("{:04}{:d}", MenuFunction::CW_HCUT_SLOPE, (int)val);
				return set(s);
			}

			std::string Menu::ReadCWHighCutSlope()
			{
				std::string s = fmt::format("{:04}", MenuFunction::CW_HCUT_SLOPE);
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
				std::string s = fmt::format("{:04}{:03}", MenuFunction::CW_OUT_LEVEL, val);
				return set(s);
			}

			std::string Menu::ReadCWOutLevel()
			{
				std::string s = fmt::format("{:04}", MenuFunction::CW_OUT_LEVEL);
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
				std::string s = fmt::format("{:04}{:d}", MenuFunction::CW_AUTO_MODE, (int)val);
				return set(s);
			}


			std::string Menu::ReadCWAutoMode()
			{

				std::string s = fmt::format("{:04}", MenuFunction::CW_AUTO_MODE);
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
				std::string s = fmt::format("{:04}{:d}", MenuFunction::CW_BFO, (int)val);
				return set(s);
			}

			std::string Menu::ReadCWBFO()
			{
				std::string s = fmt::format("{:04}", MenuFunction::CW_BFO);
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
				std::string s = fmt::format("{:04}{:d}", MenuFunction::CW_BK_IN_TYPE, (int)val);
				return set(s);
			}

			std::string Menu::ReadCWBreakInType()
			{
				std::string s = fmt::format("{:04}", MenuFunction::CW_BK_IN_TYPE);
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
				std::string s = fmt::format("{:04}{:04}", MenuFunction::CW_BK_IN_DELAY, val);
				return set(s);
			}

			std::string Menu::ReadCWBreakInDelay()
			{
				std::string s = fmt::format("{:04}", MenuFunction::CW_BK_IN_DELAY);
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
				std::string s = fmt::format("{:04}{:d}", MenuFunction::CW_WAVE_SHAPE, (int)val);
				return set(s);
			}

			std::string Menu::ReadCWWaveShape()
			{
				std::string s = fmt::format("{:04}", MenuFunction::CW_WAVE_SHAPE);
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
				std::string s = fmt::format("{:04}{:d}", MenuFunction::CW_FREQ_DISPLAY, (int)val);
				return set(s);
			}

			std::string Menu::ReadCWFreqDisplay()
			{
				std::string s = fmt::format("{:04}", MenuFunction::CW_FREQ_DISPLAY);
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
				std::string s = fmt::format("{:04}{:d}", MenuFunction::PC_KEYING, (int)val);
				return set(s);
			}

			std::string Menu::ReadPCKeying()
			{
				std::string s = fmt::format("{:04}", MenuFunction::PC_KEYING);
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
				std::string s = fmt::format("{:04}{:d}", MenuFunction::QSK_DELAY_TIME, (int)val);
				return set(s);
			}

			std::string Menu::ReadQSKDelayTime()
			{
				std::string s = fmt::format("{:04}", MenuFunction::QSK_DELAY_TIME);
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
				std::string s = fmt::format("{:04}{:d}", MenuFunction::DATA_MODE, (int)val);
				return set(s);
			}

			std::string Menu::ReadDataMode()
			{
				std::string s = fmt::format("{:04}", MenuFunction::DATA_MODE);
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
				std::string s = fmt::format("{:04}{:d}", MenuFunction::PSK_TONE, (int)val);
				return set(s);
			}

			std::string Menu::ReadPSKTone()
			{
				std::string s = fmt::format("{:04}", MenuFunction::PSK_TONE);
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
				std::string s = fmt::format("{:04}{:+05}", MenuFunction::OTHER_DISP, val);
				return set(s);
			}

			std::string Menu::ReadOtherDisp()
			{
				std::string s = fmt::format("{:04}", MenuFunction::OTHER_DISP);
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
				std::string s = fmt::format("{:04}{:+05}", MenuFunction::OTHER_SHIFT, val);
				return set(s);

			}

			std::string Menu::ReadOtherShift()
			{
				std::string s = fmt::format("{:04}", MenuFunction::OTHER_SHIFT);
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
				std::string s = fmt::format("{:04}{:02}", MenuFunction::DATA_LCUT_FREQ, (int)val);
				return set(s);
			}

			std::string Menu::ReadDATALowCutFreq()
			{
				std::string s = fmt::format("{:04}", MenuFunction::DATA_LCUT_FREQ);
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
				std::string s = fmt::format("{:04}{:d}", MenuFunction::DATA_LCUT_SLOPE, (int)val);
				return set(s);
			}

			std::string Menu::ReadDATALowCutSlope()
			{
				std::string s = fmt::format("{:04}", MenuFunction::DATA_LCUT_SLOPE);
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
				std::string s = fmt::format("{:04}{:02}", MenuFunction::DATA_HCUT_FREQ, (int)val);
				return set(s);
			}

			std::string Menu::ReadDATAHighCutFreq()
			{
				std::string s = fmt::format("{:04}", MenuFunction::DATA_HCUT_FREQ);
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
				std::string s = fmt::format("{:04}{:d}", MenuFunction::DATA_HCUT_SLOPE, (int)val);
				return set(s);
			}

			std::string Menu::ReadDATAHighCutSlope()
			{
				std::string s = fmt::format("{:04}", MenuFunction::DATA_HCUT_SLOPE);
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
				std::string s = fmt::format("{:04}{:d}", MenuFunction::DATA_IN_SELECT, (int)val);
				return set(s);
			}

			std::string Menu::ReadDATAInSelect()
			{
				std::string s = fmt::format("{:04}", MenuFunction::DATA_IN_SELECT);
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
				std::string s = fmt::format("{:04}{:d}", MenuFunction::DATA_PTT_SELECT, (int)val);
				return set(s);
			}

			std::string Menu::ReadDATAPTTSelect()
			{
				std::string s = fmt::format("{:04}", MenuFunction::DATA_PTT_SELECT);
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
				std::string s = fmt::format("{:04}{:03}", MenuFunction::DATA_OUT_LEVEL, (int)val);
				return set(s);
			}

			std::string Menu::ReadDATAOutLevel()
			{
				std::string s = fmt::format("{:04}", MenuFunction::DATA_OUT_LEVEL);
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
				std::string s = fmt::format("{:04}{:d}", MenuFunction::DATA_BFO, (int)val);
				return set(s);
			}

			std::string Menu::ReadDATABFO()
			{
				std::string s = fmt::format("{:04}", MenuFunction::DATA_BFO);
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
				std::string s = fmt::format("{:04}{:d}", MenuFunction::FM_MIC_SELECT, (int)val);
				return set(s);
			}

			std::string Menu::ReadFMMicSelect()
			{
				std::string s = fmt::format("{:04}", MenuFunction::FM_MIC_SELECT);
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
				std::string s = fmt::format("{:04}{:03}", MenuFunction::FM_OUT_LEVEL, (int)val);
				return set(s);
			}

			std::string Menu::ReadFMOutLevel()
			{
				std::string s = fmt::format("{:04}", MenuFunction::FM_OUT_LEVEL);
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
				std::string s = fmt::format("{:04}{:d}", MenuFunction::PKT_PTT_SELECT, (int)val);
				return set(s);
			}

			std::string Menu::ReadPktPTTSelect()
			{
				std::string s = fmt::format("{:04}", MenuFunction::PKT_PTT_SELECT);
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
				std::string s = fmt::format("{:04}{:04}", MenuFunction::RPT_SHIFT_28MHZ, val);
				return set(s);
			}

			std::string Menu::ReadRptShift28MHZ()
			{
				std::string s = fmt::format("{:04}", MenuFunction::RPT_SHIFT_28MHZ);
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
				std::string s = fmt::format("{:04}{:04}", MenuFunction::RPT_SHIFT_50MHZ, val);
				return set(s);
			}

			std::string Menu::ReadRptShift50MHZ()
			{
				std::string s = fmt::format("{:04}", MenuFunction::RPT_SHIFT_50MHZ);
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
				std::string s = fmt::format("{:04}{:d}", MenuFunction::DCS_POLARITY, (int)val);
				return set(s);
			}

			std::string Menu::ReadDCSPolarity()
			{
				std::string s = fmt::format("{:04}", MenuFunction::DCS_POLARITY);
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
				std::string s = fmt::format("{:04}{:02}", MenuFunction::RTTY_LCUT_FREQ, (int)val);
				return set(s);
			}

			std::string Menu::ReadRTTYLowCutFreq()
			{
				std::string s = fmt::format("{:04}", MenuFunction::RTTY_LCUT_FREQ);
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
				std::string s = fmt::format("{:04}{:d}", MenuFunction::RTTY_LCUT_SLOPE, (int)val);
				return set(s);
			}

			std::string Menu::ReadRTTYLowCutSlope()
			{
				std::string s = fmt::format("{:04}", MenuFunction::RTTY_LCUT_SLOPE);
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
				std::string s = fmt::format("{:04}{:02}", MenuFunction::RTTY_HCUT_FREQ, (int)val);
				return set(s);
			}

			std::string Menu::ReadRTTYHighCutFreq()
			{
				std::string s = fmt::format("{:04}", MenuFunction::RTTY_HCUT_FREQ);
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
				std::string s = fmt::format("{:04}{:d}", MenuFunction::RTTY_HCUT_SLOPE, (int)val);
				return set(s);
			}

			std::string Menu::ReadRTTYHighCutSlope()
			{
				std::string s = fmt::format("{:04}", MenuFunction::RTTY_HCUT_SLOPE);
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
				std::string s = fmt::format("{:04}{:d}", MenuFunction::RTTY_SHIFT_PORT, (int)val);
				return set(s);
			}

			std::string Menu::ReadRTTYShiftPort()
			{
				std::string s = fmt::format("{:04}", MenuFunction::RTTY_SHIFT_PORT);
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
				std::string s = fmt::format("{:04}{:d}", MenuFunction::RTTY_POLARITY_R, (int)val);
				return set(s);
			}

			std::string Menu::ReadRTTYPolarityR()
			{
				std::string s = fmt::format("{:04}", MenuFunction::RTTY_POLARITY_R);
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
				std::string s = fmt::format("{:04}{:d}", MenuFunction::RTTY_POLARITY_T, (int)val);
				return set(s);
			}

			std::string Menu::ReadRTTYPolarityT()
			{
				std::string s = fmt::format("{:04}", MenuFunction::RTTY_POLARITY_T);
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

				std::string s = fmt::format("{:04}{:03}", MenuFunction::RTTY_OUT_LEVEL, val);
				return set(s);
			}

			std::string Menu::ReadRTTYOutLevel()
			{
				std::string s = fmt::format("{:04}", MenuFunction::RTTY_OUT_LEVEL);
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
				std::string s = fmt::format("{:04}{:d}", MenuFunction::RTTY_SHIFT_FREQ, (int)val);
				return set(s);
			}

			std::string Menu::ReadRTTYShiftFreq()
			{
				std::string s = fmt::format("{:04}", MenuFunction::RTTY_SHIFT_FREQ);
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
				std::string s = fmt::format("{:04}{:d}", MenuFunction::RTTY_MARK_FREQ, (int)val);
				return set(s);
			}

			std::string Menu::ReadRTTYMarkFreq()
			{
				std::string s = fmt::format("{:04}", MenuFunction::RTTY_MARK_FREQ);
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
				std::string s = fmt::format("{:04}{:d}", MenuFunction::RTTY_BFO, (int)val);
				return set(s);
			}

			std::string Menu::ReadRTTYBFO()
			{
				std::string s = fmt::format("{:04}", MenuFunction::RTTY_BFO);
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
				std::string s = fmt::format("{:04}{:02}", MenuFunction::SSB_LCUT_FREQ, (int)val);
				return set(s);
			}

			std::string Menu::ReadSSBLowCutFreq()
			{
				std::string s = fmt::format("{:04}", MenuFunction::SSB_LCUT_FREQ);
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
				std::string s = fmt::format("{:04}{:d}", MenuFunction::SSB_LCUT_SLOPE, (int)val);
				return set(s);
			}

			std::string Menu::ReadSSBLowCutSlope()
			{
				std::string s = fmt::format("{:04}", MenuFunction::SSB_LCUT_SLOPE);
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
				std::string s = fmt::format("{:04}{:02}", MenuFunction::SSB_HCUT_FREQ, (int)val);
				return set(s);
			}

			std::string Menu::ReadSSBHighCutFreq()
			{
				std::string s = fmt::format("{:04}", MenuFunction::SSB_HCUT_FREQ);
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
				std::string s = fmt::format("{:04}{:d}", MenuFunction::SSB_HCUT_SLOPE, (int)val);
				return set(s);
			}

			std::string Menu::ReadSSBHighCutSlope()
			{
				std::string s = fmt::format("{:04}", MenuFunction::SSB_HCUT_SLOPE);
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
				std::string s = fmt::format("{:04}{:d}", MenuFunction::SSB_MIC_SELECT, (int)val);
				return set(s);
			}

			std::string Menu::ReadSSBMicSelect()
			{
				std::string s = fmt::format("{:04}", MenuFunction::SSB_MIC_SELECT);
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

				std::string s = fmt::format("{:04}{:03}", MenuFunction::SSB_OUT_LEVEL, (int)val);
				return set(s);
			}

			std::string Menu::ReadSSBOutLevel()
			{
				std::string s = fmt::format("{:04}", MenuFunction::SSB_OUT_LEVEL);
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
				std::string s = fmt::format("{:04}{:d}", MenuFunction::SSB_BFO, val);
				return set(s);
			}

			std::string Menu::ReadSSBBFO()
			{
				std::string s = fmt::format("{:04}", MenuFunction::SSB_BFO);
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
				std::string s = fmt::format("{:04}{:d}", MenuFunction::SSB_PTT_SELECT, val);
				return set(s);
			}

			std::string Menu::ReadSSBPTTSelect()
			{
				std::string s = fmt::format("{:04}", MenuFunction::SSB_PTT_SELECT);
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
				std::string s = fmt::format("{:04}{:d}", MenuFunction::SSB_TX_BPF, val);
				return set(s);
			}

			std::string Menu::ReadSSBTxBPF()
			{
				std::string s = fmt::format("{:04}", MenuFunction::SSB_TX_BPF);
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
				std::string s = fmt::format("{:04}{:d}", MenuFunction::APF_WIDTH, val);
				return set(s);
			}

			std::string Menu::ReadAPFWidth()
			{
				std::string s = fmt::format("{:04}", MenuFunction::APF_WIDTH);
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
				std::string s = fmt::format("{:04}{:+03}", MenuFunction::CONTOUR_LEVEL, val);
				return set(s);
			}

			std::string Menu::ReadCountourLevel()
			{
				std::string s = fmt::format("{:04}", MenuFunction::CONTOUR_LEVEL);
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
				std::string s = fmt::format("{:04}{:02}", MenuFunction::CONTOUR_WIDTH, val);
				return set(s);
			}

			std::string Menu::ReadCountourWidth()
			{
				std::string s = fmt::format("{:04}", MenuFunction::CONTOUR_WIDTH);
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
				std::string s = fmt::format("{:04}{:d}", MenuFunction::IF_NOTCH_WIDTH, val);
				return set(s);
			}

			std::string Menu::ReadIFNotchWidth()
			{
				std::string s = fmt::format("{:04}", MenuFunction::IF_NOTCH_WIDTH);
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
				std::string s = fmt::format("{:04}{:d}", MenuFunction::SCP_START_CYCLE, val);
				return set(s);
			}

			std::string Menu::ReadSCPStartCycle()
			{
				std::string s = fmt::format("{:04}", MenuFunction::SCP_START_CYCLE);
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
				std::string s = fmt::format("{:04}{:d}", MenuFunction::SCP_SPAN_FREQ, val);
				return set(s);
			}

			std::string Menu::ReadSCPSpanFreq()
			{
				std::string s = fmt::format("{:04}", MenuFunction::SCP_SPAN_FREQ);
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
				std::string s = fmt::format("{:04}{:d}", MenuFunction::QUICK_DIAL, val);
				return set(s);
			}

			std::string Menu::ReadQuickDial()
			{
				std::string s = fmt::format("{:04}", MenuFunction::QUICK_DIAL);
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
				std::string s = fmt::format("{:04}{:d}", MenuFunction::AM_DIAL_STEP, val);
				return set(s);
			}

			std::string Menu::ReadAMDialStep()
			{
				std::string s = fmt::format("{:04}", MenuFunction::AM_DIAL_STEP);
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
				std::string s = fmt::format("{:04}{:d}", MenuFunction::SSB_DIAL_STEP, val);
				return set(s);
			}

			std::string Menu::ReadSSBDialStep()
			{
				std::string s = fmt::format("{:04}", MenuFunction::SSB_DIAL_STEP);
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
				std::string s = fmt::format("{:04}{:d}", MenuFunction::FM_DIAL_STEP, val);
				return set(s);
			}

			std::string Menu::ReadFMDialStep()
			{
				std::string s = fmt::format("{:04}", MenuFunction::FM_DIAL_STEP);
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
				std::string s = fmt::format("{:04}{:d}", MenuFunction::DIAL_STEP, val);
				return set(s);
			}

			std::string Menu::ReadDialStep()
			{
				std::string s = fmt::format("{:04}", MenuFunction::DIAL_STEP);
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
				std::string s = fmt::format("{:04}{:d}", MenuFunction::AM_CH_STEP, val);
				return set(s);
			}

			std::string Menu::ReadAmChStep()
			{
				std::string s = fmt::format("{:04}", MenuFunction::AM_CH_STEP);
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
				std::string s = fmt::format("{:04}{:d}", MenuFunction::FM_CH_STEP, val);
				return set(s);
			}

			std::string Menu::ReadFmChStep()
			{
				std::string s = fmt::format("{:04}", MenuFunction::FM_CH_STEP);
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
				std::string s = fmt::format("{:04}{:02}", MenuFunction::EQ1_FREQ, val);
				return set(s);
			}

			std::string Menu::ReadEQ1Freq()
			{
				std::string s = fmt::format("{:04}", MenuFunction::EQ1_FREQ);
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

				std::string s = fmt::format("{:04}{:+03}", MenuFunction::EQ1_LEVEL, val);
				return set(s);
			}

			std::string Menu::ReadEQ1Level()
			{
				std::string s = fmt::format("{:04}", MenuFunction::EQ1_LEVEL);
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

				std::string s = fmt::format("{:04}{:02}", MenuFunction::EQ1_BWTH, val);
				return set(s);
			}

			std::string Menu::ReadEQ1Bwth()
			{
				std::string s = fmt::format("{:04}", MenuFunction::EQ1_BWTH);
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
				std::string s = fmt::format("{:04}{:02}", MenuFunction::EQ2_FREQ, val);
				return set(s);
			}

			std::string Menu::ReadEQ2Freq()
			{
				std::string s = fmt::format("{:04}", MenuFunction::EQ2_FREQ);
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

				std::string s = fmt::format("{:04}{:+03}", MenuFunction::EQ2_LEVEL, val);
				return set(s);
			}

			std::string Menu::ReadEQ2Level()
			{
				std::string s = fmt::format("{:04}", MenuFunction::EQ2_LEVEL);
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

				std::string s = fmt::format("{:04}{:+02}", MenuFunction::EQ2_BWTH, val);
				return set(s);
			}

			std::string Menu::ReadEQ2Bwth()
			{
				std::string s = fmt::format("{:04}", MenuFunction::EQ2_BWTH);
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
				std::string s = fmt::format("{:04}{:02}", MenuFunction::EQ3_FREQ, val);
				return set(s);
			}

			std::string Menu::ReadEQ3Freq()
			{
				std::string s = fmt::format("{:04}", MenuFunction::EQ3_FREQ);
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

				std::string s = fmt::format("{:04}{:+03}", MenuFunction::EQ3_LEVEL, val);
				return set(s);
			}

			std::string Menu::ReadEQ3Level()
			{
				std::string s = fmt::format("{:04};", MenuFunction::EQ3_LEVEL);
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

				std::string s = fmt::format("{:04}{:+02}", MenuFunction::EQ3_BWTH, val);
				return set(s);
			}

			std::string Menu::ReadEQ3Bwth()
			{
				std::string s = fmt::format("{:04}", MenuFunction::EQ3_BWTH);
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
				std::string s = fmt::format("{:04}{:02}", MenuFunction::P_EQ1_FREQ, val);
				return set(s);
			}

			std::string Menu::ReadPEQ1Freq()
			{
				std::string s = fmt::format("{:04}", MenuFunction::P_EQ1_FREQ);
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

				std::string s = fmt::format("{:04}{:+03}", MenuFunction::P_EQ1_LEVEL, val);
				return set(s);
			}

			std::string Menu::ReadPEQ1Level()
			{
				std::string s = fmt::format("{:04}", MenuFunction::P_EQ1_LEVEL);
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

				std::string s = fmt::format("{:04}{:+02}", MenuFunction::P_EQ1_BWTH, val);
				return set(s);
			}

			std::string Menu::ReadPEQ1Bwth()
			{
				std::string s = fmt::format("{:04}", MenuFunction::P_EQ1_BWTH);
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
				std::string s = fmt::format("{:04}{:02}", MenuFunction::P_EQ2_FREQ, val);
				return set(s);
			}

			std::string Menu::ReadPEQ2Freq()
			{
				std::string s = fmt::format("{:04}", MenuFunction::P_EQ2_FREQ);
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

				std::string s = fmt::format("{:04}{:+03}", MenuFunction::P_EQ2_LEVEL, val);
				return set(s);
			}

			std::string Menu::ReadPEQ2Level()
			{
				std::string s = fmt::format("{:04}", MenuFunction::P_EQ2_LEVEL);
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

				std::string s = fmt::format("{:04}{:+02}", MenuFunction::P_EQ2_BWTH, val);
				return set(s);
			}

			std::string Menu::ReadPEQ2Bwth()
			{
				std::string s = fmt::format("{:04}", MenuFunction::P_EQ2_BWTH);
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
				std::string s = fmt::format("{:04}{:02}", MenuFunction::P_EQ3_FREQ, val);
				return set(s);
			}

			std::string Menu::ReadPEQ3Freq()
			{
				std::string s = fmt::format("{:04}", MenuFunction::P_EQ3_FREQ);
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

				std::string s = fmt::format("{:04}{:+03}", MenuFunction::P_EQ2_LEVEL, val);
				return set(s);
			}

			std::string Menu::ReadPEQ3Level()
			{
				std::string s = fmt::format("{:04}", MenuFunction::P_EQ2_LEVEL);
				return set(s);
			}

			int Menu::AnswerPEQ3Level(std::string data)
			{
				MenuFunction f = (MenuFunction)std::stoi(data.substr(2, 4));
				if (f == MenuFunction::P_EQ2_LEVEL)
				{
					return std::stoi(data.substr(6, 3));
				}
				else throw new BadMenuItemException{ f };
			}

			std::string Menu::SetPEQ3Bwth(int val)
			{
				val = val < 1 ? 1 : val;
				val = val > 10 ? 10 : val;

				std::string s = fmt::format("{:04}{:+02}", MenuFunction::P_EQ2_BWTH, val);
				return set(s);
			}

			std::string Menu::ReadPEQ3Bwth()
			{
				std::string s = fmt::format("{:04}", MenuFunction::P_EQ2_BWTH);
				return set(s);
			}

			int Menu::AnswerPEQ3Bwth(std::string data)
			{
				MenuFunction f = (MenuFunction)std::stoi(data.substr(2, 4));
				if (f == MenuFunction::P_EQ2_BWTH)
				{
					return std::stoi(data.substr(6, 2));
				}
				else throw new BadMenuItemException{ f };
			}

			std::string Menu::SetHfSsbPwr(int val)
			{
				val = val < 5 ? 5 : val;
				val = val > 100 ? 100 : val;
				std::string s = fmt::format("{:04}{:03}", MenuFunction::HF_SSB_PWR, val);
				return set(s);
			}

			std::string Menu::ReadHfSsbPwr()
			{
				std::string s = fmt::format("{:04}", MenuFunction::HF_SSB_PWR);
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
				std::string s = fmt::format("{:04}{:03}", MenuFunction::HF_AM_PWR, val);
				return set(s);
			}

			std::string Menu::ReadHfAmPwr()
			{
				std::string s = fmt::format("{:04}", MenuFunction::HF_AM_PWR);
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
				std::string s = fmt::format("{:04}{:03}", MenuFunction::HF_PWR, val);
				return set(s);
			}

			std::string Menu::ReadHfPwr()
			{
				std::string s = fmt::format("{:04}", MenuFunction::HF_PWR);
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
				std::string s = fmt::format("{:04}{:03}", MenuFunction::SSB_POWER_50M, val);
				return set(s);
			}

			std::string Menu::Read50mSsbPwr()
			{
				std::string s = fmt::format("{:04}", MenuFunction::SSB_POWER_50M);
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
				std::string s = fmt::format("{:04}{:03}", MenuFunction::AM_POWER_50M, val);
				return set(s);
			}

			std::string Menu::Read50mAmPwr()
			{
				std::string s = fmt::format("{:04}", MenuFunction::AM_POWER_50M);
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
				std::string s = fmt::format("{:04}{:03}", MenuFunction::VHF_PWR, val);
				return set(s);
			}

			std::string Menu::Read50mPwr()
			{
				std::string s = fmt::format("{:04}", MenuFunction::VHF_PWR);
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
				std::string s = fmt::format("{:04}{:03}", MenuFunction::SSB_MIC_GAIN, val);
				return set(s);
			}

			std::string Menu::ReadSSBMicGain()
			{
				std::string s = fmt::format("{:04}", MenuFunction::SSB_MIC_GAIN);
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
				std::string s = fmt::format("{:04}{:03}", MenuFunction::AM_MIC_GAIN, val);
				return set(s);
			}

			std::string Menu::ReadAMMicGain()
			{
				std::string s = fmt::format("{:04}", MenuFunction::AM_MIC_GAIN);
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
				std::string s = fmt::format("{:04}{:03}", MenuFunction::FM_MIC_GAIN, val);
				return set(s);
			}

			std::string Menu::ReadFMMicGain()
			{
				std::string s = fmt::format("{:04}", MenuFunction::FM_MIC_GAIN);
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
				std::string s = fmt::format("{:04}{:03}", MenuFunction::DATA_MIC_GAIN, val);
				return set(s);
			}

			std::string Menu::ReadDATAMicGain()
			{
				std::string s = fmt::format("{:04}", MenuFunction::DATA_MIC_GAIN);
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
				std::string s = fmt::format("{:04}{:03}", MenuFunction::SSB_DATA_GAIN, val);
				return set(s);
			}

			std::string Menu::ReadSSBDataGain()
			{
				std::string s = fmt::format("{:04}", MenuFunction::SSB_DATA_GAIN);
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
				std::string s = fmt::format("{:04}{:03}", MenuFunction::AM_DATA_GAIN, val);
				return set(s);
			}

			std::string Menu::ReadAMDataGain()
			{
				std::string s = fmt::format("{:04}", MenuFunction::AM_DATA_GAIN);
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
				std::string s = fmt::format("{:04}{:03}", MenuFunction::FM_DATA_GAIN, val);
				return set(s);
			}

			std::string Menu::ReadFMDataGain()
			{
				std::string s = fmt::format("{:04}", MenuFunction::FM_DATA_GAIN);
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
				std::string s = fmt::format("{:04}{:03}", MenuFunction::DATA_GAIN, val);
				return set(s);
			}

			std::string Menu::ReadDataDataGain()
			{
				std::string s = fmt::format("{:04}", MenuFunction::DATA_GAIN);
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
				std::string s = fmt::format("{:04}{:d}", MenuFunction::TUNER_SELECT, val);
				return set(s);
			}

			std::string Menu::ReadTunerSelect()
			{
				std::string s = fmt::format("{:04}", MenuFunction::TUNER_SELECT);
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
				std::string s = fmt::format("{:04}{:d}", MenuFunction::VOX_SELECT, val);
				return set(s);
			}

			std::string Menu::ReadVoxSelect()
			{
				std::string s = fmt::format("{:04}", MenuFunction::VOX_SELECT);
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
				std::string s = fmt::format("{:04}{:04}", MenuFunction::VOX_GAIN, val);
				return set(s);
			}

			std::string Menu::ReadVoxGain()
			{
				std::string s = fmt::format("{:04}", MenuFunction::VOX_GAIN);
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
				std::string s = fmt::format("{:04}{:04}", MenuFunction::VOX_DELAY, val);
				return set(s);
			}

			std::string Menu::ReadVoxDelay()
			{
				std::string s = fmt::format("{:04}", MenuFunction::VOX_DELAY);
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
				std::string s = fmt::format("{:04}{:03}", MenuFunction::ANTI_VOX_GAIN, val);
				return set(s);
			}

			std::string Menu::ReadAntiVoxGain()
			{
				std::string s = fmt::format("{:04}", MenuFunction::ANTI_VOX_GAIN);
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
				std::string s = fmt::format("{:04}{:04}", MenuFunction::DATA_VOX_GAIN, val);
				return set(s);
			}

			std::string Menu::ReadDataVoxGain()
			{
				std::string s = fmt::format("{:04}", MenuFunction::DATA_VOX_GAIN);
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
				std::string s = fmt::format("{:04}{:04}", MenuFunction::DATA_VOX_DELAY, val);
				return set(s);
			}

			std::string Menu::ReadDataVoxDelay()
			{
				std::string s = fmt::format("{:04}", MenuFunction::DATA_VOX_DELAY);
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
				std::string s = fmt::format("{:04}{:03}", MenuFunction::DATA_ANTIVOX_GAIN, val);
				return set(s);
			}

			std::string Menu::ReadDataAntiVoxGain()
			{
				std::string s = fmt::format("{:04}", MenuFunction::DATA_ANTIVOX_GAIN);
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
				std::string s = fmt::format("{:04}{:d}", MenuFunction::EMERGENCY_FREQ, val);
				return set(s);
			}

			std::string Menu::ReadEmergencyFreq()
			{
				std::string s = fmt::format("{:04}", MenuFunction::EMERGENCY_FREQ);
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
				std::string s = fmt::format("{:04}{:d}", MenuFunction::EMERGENCY_FREQ, val);
				return set(s);
			}

			std::string Menu::ReadMainVersion()
			{
				std::string s = fmt::format("{:04}", MenuFunction::MAIN_VERSION);
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
				std::string s = fmt::format("{:04}", MenuFunction::DSP_VERSION);
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
				std::string s = fmt::format("{:04}", MenuFunction::LCD_VERSION);
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
				return fmt::format("FS{:d};", val);
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
				return fmt::format("GT{:02};", val);
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
			std::string IDENTIFICATION::Answer(std::string data)
			{
				if (data.substr(2, 4) == "0650")
					return "FT-891";
				else
					return data.substr(2, 4);
			}

			std::string IF_SHIFT::Set(IfShiftValue val, int freq)
			{
				return fmt::format("IS0{}{:+05};", val, freq);
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

				return fmt::format("KP{:02};", val);
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
				return fmt::format("KR{};", val);
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


				return fmt::format("KS{:03};", val);
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
				return fmt::format("KY{:0X};", val);
			}

			std::string VFODialLock::Set(DialLockValue val)
			{
				return fmt::format("LK{:d};", val);
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
				return fmt::format("LM0{:d};", val);
			}

			std::string LoadMessage::Read(DVSRecordingValue val)
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
				std::string retStr;
				switch (val)
				{
				case MemoryChannelValue::P1L:
					retStr = "MCP1L;";
					break;
				case MemoryChannelValue::P1U:
					retStr = "MCP1U;";
					break;
				case MemoryChannelValue::P2L:
					retStr = "MCP2L;";
					break;
				case MemoryChannelValue::P2U:
					retStr = "MCP2U;";
					break;
				case MemoryChannelValue::P3L:
					retStr = "MCP3L;";
					break;
				case MemoryChannelValue::P3U:
					retStr = "MCP3U;";
					break;
				case MemoryChannelValue::P4L:
					retStr = "MCP4L;";
					break;
				case MemoryChannelValue::P4U:
					retStr = "MCP4U;";
					break;
				case MemoryChannelValue::P5L:
					retStr = "MCP5L;";
					break;
				case MemoryChannelValue::P5U:
					retStr = "MCP5U;";
					break;
				case MemoryChannelValue::P6L:
					retStr = "MCP6L;";
					break;
				case MemoryChannelValue::P6U:
					retStr = "MCP6U;";
					break;
				case MemoryChannelValue::P7L:
					retStr = "MCP7L;";
					break;
				case MemoryChannelValue::P7U:
					retStr = "MCP7U;";
					break;
				case MemoryChannelValue::P8L:
					retStr = "MCP8L;";
					break;
				case MemoryChannelValue::P8U:
					retStr = "MCP8U;";
					break;
				case MemoryChannelValue::P9L:
					retStr = "MCP9L;";
					break;
				case MemoryChannelValue::P9U:
					retStr = "MCP9U;";
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
					retStr = fmt::format("MC{:03};", val);
					break;
				}
				return retStr;
			}

			std::string MemoryChannel::Read()
			{
				return "MC;";
			}

			MemoryChannelValue MemoryChannel::Answer(std::string data)
			{
				MemoryChannelValue ret;
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
				return fmt::format("MD0{:0X};", val);
			}

			std::string OperatingMode::Read()
			{
				return "MD0;";
			}

			ModeValue OperatingMode::Answer(std::string data)
			{
				return (ModeValue)std::stoi(data.substr(3, 1));
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
				return fmt::format("ML{:d}{:03};", val.f, val.val.iVal);
			}
			std::string MonitorLevel::Read(MonitorFunction val)
			{
				return fmt::format("ML{:d};", val);
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
				retVal.Mode = (ModeValue)std::stoi(data.substr(21, 1));
				retVal.VFO = (VFOChannelTypeValue)data[22];
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
					retStr = "MRP1L;";
					break;
				case MemoryChannelValue::P1U:
					retStr = "MRP1U;";
					break;
				case MemoryChannelValue::P2L:
					retStr = "MRP2L;";
					break;
				case MemoryChannelValue::P2U:
					retStr = "MRP2U;";
					break;
				case MemoryChannelValue::P3L:
					retStr = "MRP3L;";
					break;
				case MemoryChannelValue::P3U:
					retStr = "MRP3U;";
					break;
				case MemoryChannelValue::P4L:
					retStr = "MRP4L;";
					break;
				case MemoryChannelValue::P4U:
					retStr = "MRP4U;";
					break;
				case MemoryChannelValue::P5L:
					retStr = "MRP5L;";
					break;
				case MemoryChannelValue::P5U:
					retStr = "MRP5U;";
					break;
				case MemoryChannelValue::P6L:
					retStr = "MRP6L;";
					break;
				case MemoryChannelValue::P6U:
					retStr = "MRP6U;";
					break;
				case MemoryChannelValue::P7L:
					retStr = "MRP7L;";
					break;
				case MemoryChannelValue::P7U:
					retStr = "MRP7U;";
					break;
				case MemoryChannelValue::P8L:
					retStr = "MRP8L;";
					break;
				case MemoryChannelValue::P8U:
					retStr = "MRP8U;";
					break;
				case MemoryChannelValue::P9L:
					retStr = "MRP9L;";
					break;
				case MemoryChannelValue::P9U:
					retStr = "MRP9U;";
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
					retStr = fmt::format("MR{:03};", val);
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

			std::string MeterSW::Set(MeterType val)
			{
				return fmt::format("MS{:d};", val);
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
					retStr = fmt::format("MT{:03}", val.MemoryChannel);
					break;
				}
				ret = fmt::format("{}{:09}{:+05}{:01}0{:0X}0{:01}00{:01}{:01}{: <12};",
					retStr,
					val.VFOAFreq,
					val.ClarifierFreq,
					(int)val.Clarifier,
					(int)val.Mode,
					(int)val.CTCSS,
					(int)val.Operation,
					(int)val.TAG,
					val.TagString.substr(0, 12));

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
					retStr = fmt::format("MT{:03};", val);
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
					retStr = "";
					break;
				default:
					retStr = fmt::format("{:03}", val.MemoryChannel);
					break;
				}

				ret = fmt::format("MW{}{:09}{:+05}{:d}0{:d}0{:d}00{:d};",
					retStr,
					val.VFOAFreq,
					val.ClarifierFreq,
					val.Clarifier,
					val.Mode,
					val.CTCSS,
					val.Operation);

				return ret;
			}


			std::string MoxSet::Set(MoxSetVal val)
			{
				return fmt::format("MX{:d};", val);
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
				return fmt::format("NA0{:d};", val);
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
				return fmt::format("NB0{:d};", val);
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
				return fmt::format("NR0{:d};", val);
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
			InformationValue OppositeBandInformation::Answer(std::string data)
			{
				return INFORMATION::Answer(data);
			}

			std::string OffSet::Set(OperationType val)
			{
				return fmt::format("OS0{:d};", val);
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
				return fmt::format("PA0{:d};", val);
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
				return fmt::format("PB0{:d};", val);
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
				return fmt::format("PR{:d}{:d};", val.type, val.state);
			}

			std::string SpeechProcessor::Read(SpeechProcessorType type)
			{
				return fmt::format("PR{:d};", type);
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
				return fmt::format("PS{:d};", val);
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
				return fmt::format("RA0{:d};", val);
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
				return fmt::format("RI{:0A};", type);
			}

			RadioInfoVal RadioInformation::Answer(std::string data)
			{
				RadioInfoVal ret;
				ret.Type = (InformationType)std::stoi(data.substr(2, 1));
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
				return fmt::format("RM{:d};", type);
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
				return fmt::format("SC{:d};", val);
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
				return fmt::format("SH{:d}{:03};", val.State, val.WidthCommand);
			}
			std::string Width::Read()
			{
				return "SH;";
			}
			WidthValue Width::Answer(std::string data)
			{
				WidthValue val;
				val.State = (WidthState)std::stoi(data.substr(2, 1));
				val.WidthCommand = std::stoi(data.substr(3, 3));
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
				return fmt::format("ST{:d};", val);
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
				return fmt::format("TS{:d};", val);
			}
			std::string TXW::Read()
			{
				return "TS;";
			}

			TXWValue TXW::Answer(std::string data)
			{
				return (TXWValue)std::stoi(data.substr(2, 1));
			}

			std::string TxSet::Set(TxSetValue val)
			{
				return fmt::format("TX{:d};", val);
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
				return fmt::format("VG{:03};", val);
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
				return fmt::format("VX{:d};", val);
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
		};
	};
};