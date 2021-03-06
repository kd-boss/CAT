#ifndef CAT_H
#define CAT_H
#include<string>
#include<exception>
#include<stdexcept>
#include<type_traits>
//VFOA to VFOB

template<typename E, E first, E head>
void advanceEnum(E& v)
{
    if(v == head)
        v = first;
}

template<typename E, E first, E head, E next, E... tail>
void advanceEnum(E& v)
{
    if(v == head)
        v = next;
    else
        advanceEnum<E,first,next,tail...>(v);
}

template<typename E, E first, E... values>
struct EnumValues
{
    static void advance(E& v)
    {
        advanceEnum<E, first, first, values...>(v);
    }
};

namespace Yaesu {
	namespace FT891 {
		namespace Commands {

			enum class KeyerMemoryChannel
			{
				Memory1 = 1,
				Memory2,
				Memory3,
				Memory4,
				Memory5,
				Message1,
				Message2,
				Message3,
				Message4,
				Message5
			};


			enum class Band : int {
				m160 = 0,
				m80 = 1,
				m60 = 2,
				m40 = 3,
				m30 = 4,
				m20 = 5,
				m17 = 6,
				m15 = 7,
				m12 = 8,
				m10 = 9,
				m6 = 10,
				GEN = 11,
				MW = 12
			};

			enum class InformationState : int {
				OFF,
				ON
			};

			enum class TunerState : int
			{
				OFF,
				ON,
				Start

			};

			enum class NotchState
			{
				OFF,
				ON
			};

			enum class BreakInState : int {
				OFF,
				ON
			};


			enum class CTCSSState
			{
				CTCSS_OFF,
				CTCSS_ENC_DEC_ON,
				CTCSS_ENC_ON,
				CTCSS_DCS_ON
			};


			enum class CWSpotState : int
			{
				OFF,
				ON
			};


			enum class EncoderType : int
			{
				MAIN_ENCODER,
				MULTI_FUNCTION = 8
			};

			enum class MenuFunction : int
			{
				AGC_FAST_DELAY = 101,
				AGC_MID_DELAY,
				AGC_SLOW_DELAY,
				LCD_CONTRAST = 201,
				DIMMER_BACKLIT,
				DIMMER_LCD,
				DIMMER_TX_BUSY,
				PEAK_HOLD,
				ZIN_LED,
				POPUP_MENU,
				DVS_RX_OUT_LVL = 301,
				DVS_TX_OUT_LVL,
				KEYER_TYPE = 401,
				KEYER_DOT_DASH_ORDER,
				CW_WEIGHT,
				BEACON_INTERVAL,
				NUMBER_STYLE,
				CONTEST_NUMBER,
				CW_MEMORY_1,
				CW_MEMORY_2,
				CW_MEMORY_3,
				CW_MEMORY_4,
				CW_MEMORY_5,
				NB_WIDTH = 501,
				NB_REJECTION,
				NB_LEVEL,
				BEEP_LEVEL,
				RF_SQL_VR,
				CAT_RATE,
				CAT_TOT,
				CAT_RTS,
				MEM_GROUP,
				FM_SETTING,
				REC_SETTING,
				ATAS_SETTING,
				QUICK_SPL_FREQ,
				TX_TOT,
				MIC_SCAN,
				MIC_SCAN_RESUME,
				REF_FEQ_ADJ,
				CLAR_SELECT,
				APO,
				FAN_CONTROL,
				AM_LCUT_FREQ = 601,
				AM_LCUT_SLOPE,
				AM_HCUT_FREQ,
				AM_HCUT_SLOPE,
				AM_MIC_SELECT,
				AM_OUT_LEVEL,
				AM_PTT_SELECT,
				CW_LCUT_FREQ = 701,
				CW_LCUT_SLOPE,
				CW_HCUT_FREQ,
				CW_HCUT_SLOPE,
				CW_OUT_LEVEL,
				CW_AUTO_MODE,
				CW_BFO,
				CW_BK_IN_TYPE,
				CW_BK_IN_DELAY,
				CW_WAVE_SHAPE,
				CW_FREQ_DISPLAY,
				PC_KEYING,
				QSK_DELAY_TIME,
				DATA_MODE = 801,
				PSK_TONE,
				OTHER_DISP,
				OTHER_SHIFT,
				DATA_LCUT_FREQ,
				DATA_LCUT_SLOPE,
				DATA_HCUT_FREQ,
				DATA_HCUT_SLOPE,
				DATA_IN_SELECT,
				DATA_PTT_SELECT,
				DATA_OUT_LEVEL,
				DATA_BFO,
				FM_MIC_SELECT = 901,
				FM_OUT_LEVEL,
				PKT_PTT_SELECT,
				RPT_SHIFT_28MHZ,
				RPT_SHIFT_50MHZ,
				DCS_POLARITY,
				RTTY_LCUT_FREQ = 1001,
				RTTY_LCUT_SLOPE,
				RTTY_HCUT_FREQ,
				RTTY_HCUT_SLOPE,
				RTTY_SHIFT_PORT,
				RTTY_POLARITY_R,
				RTTY_POLARITY_T,
				RTTY_OUT_LEVEL,
				RTTY_SHIFT_FREQ,
				RTTY_MARK_FREQ,
				RTTY_BFO,
				SSB_LCUT_FREQ = 1101,
				SSB_LCUT_SLOPE,
				SSB_HCUT_FREQ,
				SSB_HCUT_SLOPE,
				SSB_MIC_SELECT,
				SSB_OUT_LEVEL,
				SSB_BFO,
				SSB_PTT_SELECT,
				SSB_TX_BPF,
				APF_WIDTH = 1201,
				CONTOUR_LEVEL,
				CONTOUR_WIDTH,
				IF_NOTCH_WIDTH,
				SCP_START_CYCLE = 1301,
				SCP_SPAN_FREQ,
				QUICK_DIAL = 1401,
				SSB_DIAL_STEP,
				AM_DIAL_STEP,
				FM_DIAL_STEP,
				DIAL_STEP,
				AM_CH_STEP,
				FM_CH_STEP,
				EQ1_FREQ = 1501,
				EQ1_LEVEL,
				EQ1_BWTH,
				EQ2_FREQ,
				EQ2_LEVEL,
				EQ2_BWTH,
				EQ3_FREQ,
				EQ3_LEVEL,
				EQ3_BWTH,
				P_EQ1_FREQ,
				P_EQ1_LEVEL,
				P_EQ1_BWTH,
				P_EQ2_FREQ,
				P_EQ2_LEVEL,
				P_EQ2_BWTH,
				P_EQ3_FREQ,
				P_EQ3_LEVEL,
				P_EQ3_BWTH,
				HF_SSB_PWR = 1601,
				HF_AM_PWR,
				HF_PWR,
				SSB_POWER_50M,
				AM_POWER_50M,
				VHF_PWR,
				SSB_MIC_GAIN,
				AM_MIC_GAIN,
				FM_MIC_GAIN,
				DATA_MIC_GAIN,
				SSB_DATA_GAIN,
				AM_DATA_GAIN,
				FM_DATA_GAIN,
				DATA_GAIN,
				TUNER_SELECT,
				VOX_SELECT,
				VOX_GAIN,
				VOX_DELAY,
				ANTI_VOX_GAIN,
				DATA_VOX_GAIN,
				DATA_VOX_DELAY,
				DATA_ANTIVOX_GAIN,
				EMERGENCY_FREQ,
				RESET = 1701,
				MAIN_VERSION = 1801,
				DSP_VERSION,
				LCD_VERSION
			};

			enum class PeakHoldType : int {
				OFF,
				sec05,
				sec10,
				sec20
			};

			enum class PopUpMenuStyle {
				UPPER,
				LOWER
			};

			enum class KeyerTypeValue : int {
				OFF,
				BUG,
				ELEKEY_A,
				ELEKEY_B,
				ELEKEY_Y,
				ACS

			};

			enum class KeyerDotDashValue : int {
				NOR,
				REV
			};

			enum class NumberStyleValue : int {
				_1290,
				AUNO,
				AUNT,
				A2NO,
				A2NT,
				_12NO,
				_12NT
			};

			enum class CWMemoryTypeValue : int {
				TEXT,
				MESSAGE
			};

			enum NBWidthValue : int {
				msec1,
				msec3,
				msec10
			};

			enum class NBRejectionValue : int {
				db10,
				db30,
				db50
			};

			enum class RfSqlVrValue : int {
				RF,
				SQL
			};

			enum class CatRateValue : int {
				_4800bps,
				_9600bps,
				_19200bps,
				_38400bps
			};

			enum class CatTOTValue : int {
				_10msec,
				_100msec,
				_1000msec,
				_3000msec
			};

			enum class EnableDisableValue : int {
				DISABLE,
				ENABLE
			};

			enum class MicScanResumeValue : int
			{
				PAUSE,
				TIME
			};

			enum class ClarSelectValue : int
			{
				RX,
				TX,
				TRX
			};

			enum class APOValue : int
			{
				OFF,
				hr1,
				hr2,
				hr4,
				hr6,
				hr8,
				hr10,
				hr12
			};

			enum class FanControlValue : int
			{
				NORMAL,
				CONTEST
			};

			enum class FreqSlopeValue : int
			{
				DbOct_6,
				DbOct_18
			};

			enum class FreqHighCutValue : int
			{
				OFF,
				_700hz,
				_750hz,
				_800hz,
				_850hz,
				_900hz,
				_950hz,
				_1000hz,
				_1050hz,
				_1100hz,
				_1150hz,
				_2000hz,
				_2050hz,
				_2100hz,
				_2150hz,
				_2200hz,
				_2250hz,
				_2300hz,
				_2350hz,
				_2400hz,
				_2450hz,
				_2500hz,
				_2550hz,
				_2600hz,
				_2650hz,
				_2700hz,
				_2750hz,
				_2800hz,
				_2850hz,
				_2900hz,
				_2950hz,
				_3000hz,
				_3050hz,
				_3100hz,
				_3150hz,
				_3200hz,
				_3250hz,
				_3300hz,
				_3350hz,
				_3400hz,
				_3450hz,
				_3500hz,
				_3550hz,
				_3600hz,
				_3650hz,
				_3700hz,
				_3750hz,
				_3800hz,
				_3850hz,
				_3900hz,
				_3950hz,
				_4000hz
			};

			enum class FreqLowCutValue : int
			{
				OFF,
				_100hz,
				_150hz,
				_200hz,
				_250hz,
				_300hz,
				_350hz,
				_400hz,
				_450hz,
				_500hz,
				_550hz,
				_600hz,
				_650hz,
				_700hz,
				_750hz,
				_800hz,
				_850hz,
				_900hz,
				_950hz,
				_1000hz,

			};

			enum class CwAutoModeValue : int
			{
				OFF,
				_50M,
				ON
			};

			enum class BfoValue : int
			{
				USB,
				LSB,
				AUTO
			};

			enum class CwBreakInType :int
			{
				SEMI,
				FULL
			};

			enum class CwWaveShapeValue : int
			{
				_2msec = 1,
				_4msec
			};

			enum class CwFreqDisplayValue : int
			{
				FREQ,
				PITCH
			};

			enum class PCKeyingValue : int
			{
				OFF,
				DKAY,
				RTS,
				DTR
			};

			enum class QskDelayTimeValue : int
			{
				_15msec,
				_20msec,
				_25msec,
				_30msec
			};

			enum class DataModeValue : int
			{
				PSK,
				OTHERS
			};

			enum class PSKToneValue : int
			{
				_1000hz,
				_1500hz,
				_2000hz
			};

			enum class AudioInputValue : int
			{
				MIC,
				REAR
			};

			enum class PTTSelectValue :int
			{
				DAKY,
				RTS,
				DTR
			};

			enum class DCSPolarityValue : int
			{
				Tn_Rn,
				Tn_Riv,
				Tiv_Rn,
				Tiv_Riv
			};

			enum class RTTYShiftPortValue : int
			{
				SHIFT,
				DTR,
				RTS
			};

			enum class RTTYPolarityValue : int
			{
				NOR,
				REV
			};

			enum class RTTYShiftFreqValue : int
			{
				_170hz,
				_200hz,
				_425hz,
				_850hz
			};

			enum class RTTYMarkFreq : int
			{
				_1275hz,
				_2125hz
			};

			enum class DataBfoValue : int
			{
				USB,
				LSB
			};

			enum class SSBTXBandPassValue : int
			{
				_100_3000,
				_100_2900,
				_200_2800,
				_300_2700,
				_400_2600
			};

			enum class APFWidthValue : int
			{
				NARROW,
				MEDIUM,
				WIDE
			};

			enum class IFNotchWidthValue : int
			{
				NARROW,
				WIDE
			};

			enum class SCPStartCycleValue : int
			{
				OFF,
				_3sec,
				_5sec,
				_10sec
			};

			enum class SCPSpanFreqValue : int
			{
				_37_5khz,
				_75khz,
				_150khz,
				_375khz,
				_750khz
			};

			enum class QuickDialValue : int
			{
				_50khz,
				_100khz,
				_500khz
			};

			enum class SSBDialStep : int
			{
				_2hz,
				_5hz,
				_10hz
			};

			enum class AMDialStep : int
			{
				_10Hz,
				_100Hz
			};

			enum class FMDialStep : int
			{
				_10Hz,
				_100Hz
			};

			enum class DialStep : int
			{
				_2hz,
				_5hz,
				_10hz
			};

			enum class AMChannelStepValue : int
			{
				_2_5khz,
				_5khz,
				_9khz,
				_10khz,
				_12_5khz,
				_25khz
			};

			enum class FMChannelStepValue : int
			{
				_5kHz,
				_6_26kHz,
				_10kHz,
				_12_5kHz,
				_15kHz,
				_20kHz,
				_25kHz
			};

			enum class EQ1FreqValue : int
			{
				OFF,
				_100Hz,
				_200Hz,
				_300Hz,
				_400Hz,
				_500Hz,
				_600Hz,
				_700Hz
			};

			enum class EQ2FreqValue : int
			{
				OFF,
				_700Hz,
				_800Hz,
				_900Hz,
				_1000Hz,
				_1100Hz,
				_1200Hz,
				_1300Hz,
				_1400Hz
			};

			enum class EQ3FreqValue : int
			{
				OFF,
				_1500Hz,
				_1600Hz,
				_1700Hz,
				_1800Hz,
				_1900Hz,
				_2000Hz,
				_2100Hz,
				_2200Hz,
				_2300Hz,
				_2400Hz,
				_2500Hz,
				_2600Hz,
				_2700Hz,
				_2800Hz,
				_2900Hz,
				_3000Hz,
				_3100Hz,
				_3200Hz
			};

			enum class TunerSelectValue : int
			{
				OFF,
				EXTERNAL,
				ATAS,
				LAMP
			};

			enum class VoxSelectValue : int
			{
				MIC,
				DATA
			};

			enum class ResetValue : int
			{
				ALL,
				DATA,
				FUNC
			};

			enum class NotchCommandType
			{
				ON_OFF,
				LEVEL
			};

			

			enum class CTCSSModeType : int {
				CTCSS,
				DCS
			};

			enum class ContourType : int
			{
				ContourOnOff,
				ContourFrequency,
				APFOnOff,
				APFFrequency
			};

			enum class ContourState
			{
				OFF,
				ON
			};

			enum class VFOFastStepValue
			{
				OFF,
				ON
			};

			enum class AGCSetValue
			{
				OFF,
				FAST,
				MID,
				SLOW,
				AUTO
			};

			enum class AGCReadValue
			{
				OFF,
				FAST,
				MID,
				SLOW,
				AUTO_FAST,
				AUTO_MID,
				AUTO_SLOW
			};

			

			enum class KeyPitchValue
			{
				_300Hz,
				_310Hz,
				_320Hz,
				_330Hz,
				_340Hz,
				_350Hz,
				_360Hz,
				_370Hz,
				_380Hz,
				_390Hz,
				_400Hz,
				_410Hz,
				_420Hz,
				_430Hz,
				_440Hz,
				_450Hz,
				_460Hz,
				_470Hz,
				_480Hz,
				_490Hz,
				_500Hz,
				_510Hz,
				_520Hz,
				_530Hz,
				_540Hz,
				_550Hz,
				_560Hz,
				_570Hz,
				_580Hz,
				_590Hz,
				_600Hz,
				_610Hz,
				_620Hz,
				_630Hz,
				_640Hz,
				_650Hz,
				_660Hz,
				_670Hz,
				_680Hz,
				_690Hz,
				_700Hz,
				_710Hz,
				_720Hz,
				_730Hz,
				_740Hz,
				_750Hz,
				_760Hz,
				_770Hz,
				_780Hz,
				_790Hz,
				_800Hz,
				_810Hz,
				_820Hz,
				_830Hz,
				_840Hz,
				_850Hz,
				_860Hz,
				_870Hz,
				_880Hz,
				_890Hz,
				_900Hz,
				_910Hz,
				_920Hz,
				_930Hz,
				_940Hz,
				_950Hz,
				_960Hz,
				_970Hz,
				_980Hz,
				_990Hz,
				_1000Hz,
				_1010Hz,
				_1020Hz,
				_1030Hz,
				_1040Hz,
				_1050Hz

			};

			enum class KeyerSpeedVal
			{
				_4wpm = 4,
				_5wpm,
				_6wpm,
				_7wpm,
				_8wpm,
				_9wpm,
				_10wpm,
				_11wpm,
				_12wpm,
				_13wpm,
				_14wpm,
				_15wpm,
				_16wpm,
				_17wpm,
				_18wpm,
				_19wpm,
				_20wpm,
				_21wpm,
				_22wpm,
				_23wpm,
				_24wpm,
				_25wpm,
				_26wpm,
				_27wpm,
				_28wpm,
				_29wpm,
				_30wpm,
				_31wpm,
				_32wpm,
				_33wpm,
				_34wpm,
				_35wpm,
				_36wpm,
				_37wpm,
				_38wpm,
				_39wpm,
				_40wpm,
				_41wpm,
				_42wpm,
				_43wpm,
				_44wpm,
				_45wpm,
				_46wpm,
				_47wpm,
				_48wpm,
				_49wpm,
				_50wpm,
				_51wpm,
				_52wpm,
				_53wpm,
				_54wpm,
				_55wpm,
				_56wpm,
				_57wpm,
				_58wpm,
				_59wpm,
				_60wpm
			};

			enum class DVSRecordingValue
			{
				STOP,
				CH1,
				CH2,
				CH3,
				CH4,
				CH5
			};

			enum class MonitorFunction : int
			{
				MontiorOnOff,
				MontiorLevel
			};			
			enum class MeterType
			{
				COMP,
				ALC,
				PO,
				SWR,
				ID
			};
			enum class TagValue {
				OFF,
				ON
			};
			enum class VFOChannelTypeValue
			{
				VFO,
				Memory,
				MemoryTune,
				QuickMemoryBank,
				QMB_MT,
				PMS,
				HOME
			};
			enum class OperationType
			{
				Simplex,
				PlusShift,
				MinusShift
			};
			enum class ModeValue
			{
				SSB_BFOA = 1,
				SSB_BFOB,
				CW,
				FM,
				AM,
				RTTY_BFOA,
				CW_BFOA,
				DATA_BFOA,
				RTTY_BFOB,
				FM_N = 11,
				DATA_BFOB,
				AM_N
			};
			enum class UpDownState
			{
				UP,
				DOWN
			};
			enum class IfShiftValue
			{
				OFF,
				ON
			};
			enum class SpeechProcessorType
			{
				Processor,
				ParametricEqualizer
			};
			enum class SpeechProcessorState
			{
				OFF,
				ON
			};			
			enum PowerSwitchValue
			{
				OFF,
				ON
			};	
			enum class ReadMeterType
			{
				AutoA,
				S,
				AutoB,
				COMP,
				ALC,
				PO,
				SWR,
				ID
			};
			enum class RadioStatusValue
			{
				NORMAL,
				MENU
			};
			enum class ScanState
			{
				OFF,
				UP,
				DOWN
			};
			enum class WidthState
			{
				OFF,
				ON
			};
			enum class MemoryChannelModeValue : int
			{
				LSB = 1,
				USB,
				CW,
				FM,
				AM,
				RTTY_LSB,
				CW_R,
				DATA_LSB,
				RTTY_USB,
				FM_N = 11,
				DATA_USB,
				AM_N
			};

			enum class MemoryChannelValue
			{
				_1 = 1,
				_2,
				_3,
				_4,
				_5,
				_6,
				_7,
				_8,
				_9,
				_10,
				_11,
				_12,
				_13,
				_14,
				_15,
				_16,
				_17,
				_18,
				_19,
				_20,
				_21,
				_22,
				_23,
				_24,
				_25,
				_26,
				_27,
				_28,
				_29,
				_30,
				_31,
				_32,
				_33,
				_34,
				_35,
				_36,
				_37,
				_38,
				_39,
				_40,
				_41,
				_42,
				_43,
				_44,
				_45,
				_46,
				_47,
				_48,
				_49,
				_50,
				_51,
				_52,
				_53,
				_54,
				_55,
				_56,
				_57,
				_58,
				_59,
				_60,
				_61,
				_62,
				_63,
				_64,
				_65,
				_66,
				_67,
				_68,
				_69,
				_70,
				_71,
				_72,
				_73,
				_74,
				_75,
				_76,
				_77,
				_78,
				_79,
				_80,
				_81,
				_82,
				_83,
				_84,
				_85,
				_86,
				_87,
				_88,
				_89,
				_90,
				_91,
				_92,
				_93,
				_94,
				_95,
				_96,
				_97,
				_98,
				_99,
				P1L,
				P1U,
				P2L,
				P2U,
				P3L,
				P3U,
				P4L,
				P4U,
				P5L,
				P5U,
				P6L,
				P6U,
				P7L,
				P7U,
				P8L,
				P8U,
				P9L,
				P9U,
				_5351_5mhz = 501,
				_5354mhz,
				_5357mhz,
				_5360mhz,
				_5363mhz,
				_5366mhz,
				EMG = 600

			};
				       
			enum class InformationType {
				HI_SWR,
				REC = 3,
				PLAY,
				TX_LED = 10,
				RX_LED
			};
			enum class RfAttenuatorState
			{
				OFF,
				ON
			};
			enum class BusyState
			{
				OFF,
				ON
			};
			enum class  ClarifierState : int
			{
				OFF,
				ON
			};
			enum class MonitorOnOffValue : int
			{
				OFF,
				ON
			};
			enum class DialLockValue
			{
				OFF,
				ON
			};
			enum class KeyerValue
			{
				OFF,
				ON
			};


			std::string DisplayMonitorFunction(MonitorFunction v);
			std::string DisplayNotchState(NotchState v);
			std::string DisplayKeyerMemory(KeyerMemoryChannel v);
			std::string DisplayInformationState(InformationState v);
			std::string DisplayBreakInState(BreakInState v);
			std::string DisplayCTCSSState(CTCSSState v);
			std::string DisplayCwSpotState(CWSpotState v);
			std::string DisplayMemoryChannelValue(MemoryChannelValue v);
			std::string DisplayInformationType(InformationType v);
			std::string DisplayBusyState(BusyState v);
			std::string DisplayClarifierState(ClarifierState v);
			std::string DisplayDialLockValue(DialLockValue v);
			std::string DisplayKeyerValue(KeyerValue v);
			std::string DisplayVFOChannelType(VFOChannelTypeValue v);
			std::string DisplayOperationType(OperationType v);
			std::string DisplayModeValue(ModeValue v);
			std::string DisplayMonitorOnOffValue(MonitorOnOffValue v);
			std::string DisplayTagValue(TagValue v);
			std::string DisplayRFAttenuatorState(RfAttenuatorState v);
			std::string DisplayIfShift(IfShiftValue v);
			std::string DisplaySpeechProcessorType(SpeechProcessorType v);
			std::string DisplaySpeechProcessorState(SpeechProcessorState v);
			std::string DisplayPowerSwitch(PowerSwitchValue v);
			std::string DisplayReadMeterType(ReadMeterType v);
			std::string DisplayRadioStatus(RadioStatusValue v);
			std::string DisplayMemoryChannelModeValue(MemoryChannelModeValue v);
			std::string DisplayScanState(ScanState v);
			std::string DisplayWidthState(WidthState v);
			std::string DisplayMenuFunction(MenuFunction f);
			std::string DisplayTunerSelect(TunerSelectValue v);
			std::string DisplayEQ3Value(EQ3FreqValue v);
			std::string DisplayEQ2Value(EQ2FreqValue v);
			std::string DisplayEQ1Value(EQ1FreqValue v);
			std::string DisplayFMChStep(FMChannelStepValue v);
			std::string DisplayAMChStep(AMChannelStepValue v);
			std::string DisplayDialStep(DialStep v);
			std::string DisplayAmFMDialStep(FMDialStep v);
			std::string DisplayAmFMDialStep(AMDialStep v);
			std::string DisplaySSBDialStep(SSBDialStep v);
			std::string DisplayQuickDial(QuickDialValue v);
			std::string DisplaySCPSpanFreq(SCPSpanFreqValue v);
			std::string DisplaySCPStart(SCPStartCycleValue v);
			std::string DisplayAPWidth(APFWidthValue v);
			std::string DisplaySSBTxBandPass(SSBTXBandPassValue v);
			std::string DisplayRTTYMarkFreq(RTTYMarkFreq v);
			std::string DisplayRTTYShiftFreq(RTTYShiftFreqValue v);
			std::string DisplayRTTYShiftPort(RTTYShiftPortValue v);
			std::string DisplayDCSPolarity(DCSPolarityValue v);
			std::string DisplayPSKTone(PSKToneValue v);
			std::string DisplayQskDelay(QskDelayTimeValue v);
			std::string DisplayBFO(DataBfoValue v);
			std::string DisplayPCKeying(PCKeyingValue v);
			std::string DisplayBFO(BfoValue v);
			std::string DisplayCwAutoMode(CwAutoModeValue v);
			std::string DisplayPTTSelect(PTTSelectValue v);
			std::string DisplayFreqHighCut(FreqHighCutValue v);
			std::string DisplayFreqLowCut(FreqLowCutValue v);
			std::string DisplayClarSelect(ClarSelectValue v);
			std::string DisplayAPO(APOValue v);
			std::string DisplayCatTOT(CatTOTValue v);
			std::string DisplayCatRate(CatRateValue v);
			std::string DisplayNbRejection(NBRejectionValue v);
			std::string DisplayNbWidth(NBWidthValue v);
			std::string DisplayNumberStyle(NumberStyleValue v);
			std::string DisplayBeaconInterval(int i);
			std::string DisplayPeakHold(PeakHoldType t);
			std::string DisplayEnableDisable(EnableDisableValue v);
			std::string DisplayKeyerType(KeyerTypeValue v);
			std::string DisplayBand(Band v);
			std::string DisplayCwWeight(int weight);
			std::string DisplayFrequency(int freq);

			struct ManualNotchValue
			{
				NotchCommandType Command;
				union Value
				{
					NotchState state;
					int iValue;
				};
				Value Value;
			};

			struct CTCSSToneFreqencyValue {
				CTCSSModeType Mode;
				int Value;
			};

			struct DimmerValues {
				int LCD_Contrast;
				int BacklightLevel;
				int LCD_Level;
				int TX_Indicator;
			};

			struct ContourValue {
				ContourType Type;
				union Value
				{
					ContourState state;
					int Freq;
				};
				Value Value;
			};

			struct InformationValue {
				MemoryChannelValue MemoryChannel;
				int VFOAFreq;
				int ClarifierFreq;
				ClarifierState Clarifier;
				ModeValue Mode;
				VFOChannelTypeValue VFO;
				CTCSSState CTCSS;
				OperationType Operation;
			};

			struct OppositeInformationValue {
				MemoryChannelValue MemoryChannel;
				int VFOBFreq;
				int ClarifierFreq;
				ClarifierState Clarifier;
				ModeValue Mode;
				VFOChannelTypeValue VFO;
				CTCSSState CTCSS;
				OperationType Operation;
			};

			struct IfShiftResultValue
			{
				IfShiftValue State;
				int Frequency;
			};

			struct KeyerMemoryValue
			{
				int ChannelNumber;
				std::string Message;
			};

			struct MonitorLevelValue
			{


				MonitorFunction f;
				union Value {
					MonitorOnOffValue eVal;
					int iVal;
				};
				Value val;
			};

			struct MemoryChannelTagValue {
				MemoryChannelTagValue() {
					TagString = "";
				}
				MemoryChannelValue MemoryChannel;
				int VFOAFreq;
				int ClarifierFreq;
				ClarifierState Clarifier;
				MemoryChannelModeValue Mode;
				CTCSSState CTCSS;
				OperationType Operation;
				TagValue TAG;
				std::string TagString;
			};

			struct MemoryChannelWriteValue {
				MemoryChannelValue MemoryChannel;
				int VFOAFreq;
				int ClarifierFreq;
				ClarifierState Clarifier;
				MemoryChannelModeValue Mode;
				CTCSSState CTCSS;
				OperationType Operation;
			};

			struct MemoryChannelReadValue {
				MemoryChannelValue MemoryChannel;
				int VFOAFreq;
				int ClarifierFreq;
				VFOChannelTypeValue ChannelType;
				ClarifierState Clarifier;
				MemoryChannelModeValue Mode;
				CTCSSState CTCSS;
				OperationType Operation;

			};

			struct SpeechProcessorSetting
			{
				SpeechProcessorType type;
				SpeechProcessorState state;
			};

			struct RadioInfoVal {
				InformationType Type;
				InformationState Value;
			};

			struct MeterVal
			{
				ReadMeterType Type;
				int Value;
			};

			struct WidthValue {
				WidthState State;
				int WidthCommand;
			};

			class VFO_A_TO_VFO_B
			{
			public:
				static std::string Set();
			};

			class AntennaTunerControl
			{
			public:
				static std::string Set(TunerState state);
				static std::string Read();
				static TunerState Answer(std::string data);
			};

			class VolumeLevel
			{
			public:
				static std::string Set(int Value);
				static std::string Read();
				static int Answer(std::string data);
			};

			class AutoInformation
			{
			public:


				static std::string Set(InformationState Value);
				static std::string Read();
				static InformationState Answer(std::string data);
			};

			class VFO_A_To_Memory
			{
			public:
				static std::string Set();
			};

			class VFO_B_TO_VFO_A
			{
			public:
				static std::string Set();
			};

			class AutoNotch
			{
			public:

				static std::string Set(NotchState Value);
				static std::string Read();
				static NotchState Answer(std::string data);
			};

			class BandDown
			{
			public:
				static std::string Set();
			};

			class BreakIn
			{
			public:

				static std::string Set(BreakInState Value);
				static std::string Read();
				static BreakInState Answer(std::string data);
			};

			class ManualNotch
			{
			public:
				static std::string Set(ManualNotchValue val);
				static std::string Read();
				static ManualNotchValue Answer(std::string data);
			};

			class BandSelect
			{
			public:


				static std::string Set(Band Value);
			};

			class BandUP
			{
			public:
				static std::string Set();
			};

			class Busy
			{
			public:

				static std::string Read();

				static BusyState Answer(std::string data);

			};

			class Clarifier
			{
			public:

				static std::string Set(ClarifierState Value);
				static std::string Read();
				static ClarifierState Answer(std::string data);
			};

			class Channel_Up_Down
			{
			public:

				static std::string Set(UpDownState Value);
			};

			class CTCSSToneFrequency
			{
			public:
				static std::string Set(CTCSSToneFreqencyValue val);
				static std::string Read(CTCSSModeType mode);
				static CTCSSToneFreqencyValue Answer(std::string data);
			};

			class Contour
			{
			public:
				static std::string Set(ContourValue Type);
				static std::string Read(ContourValue Type);
				static ContourValue Answer(std::string data);
			};

			class CWSpot
			{
			public:

				static std::string Set(CWSpotState Value);
				static std::string Read();
				static CWSpotState Answer(std::string data);
			};

			class CTCSS
			{
			public:


				static std::string Set(CTCSSState Value);
				static std::string Read();
				static CTCSSState Answer(std::string data);
			};

			class Dimmer
			{
			public:

				static std::string set(DimmerValues val);
				static std::string Read();
				static DimmerValues Answer(std::string data);
			};

			class Mic_Down
			{
			public:
				static std::string Set();
			};

			class EncoderDown
			{
			public:

				static std::string Set(EncoderType enc, int Steps);

			};

			class EnterKey
			{
			public:
				static std::string Set();
			};

			class EncoderUp
			{
			public:
				static std::string Set(EncoderType enc, int Steps);
			};

			class BadMenuItemException : public std::runtime_error
			{
				MenuFunction _s;
			public:

				BadMenuItemException(MenuFunction s) : std::runtime_error("Bad Menu Function Parse!")
				{
					_s = s;
				}

				MenuFunction ParsedFunction() { return _s; }
			};

			class Menu
			{
				static std::string set(std::string s);
			public:
				static std::string SetAgcFastDelay(int msecs);

				static std::string ReadAgcFastDelay();

				static int AnswerAgcFastDelay(std::string dat);

				static std::string SetAgcMidDelay(int msecs);

				static std::string ReadAgcMidDelay();

				static int AnswerAgcMidDelay(std::string dat);

				static std::string SetAgcSlowDelay(int msecs);

				static std::string ReadAgcSlowDelay();

				static int AnswerAgcSlowDelay(std::string dat);

				static std::string SetLcdContrast(int level);

				static std::string ReadLcdContrast();

				static int AnswerLcdContrast(std::string data);

				static std::string SetBackliteDimmer(int level);

				static std::string ReadBackliteDimmer();

				static int AnswerBackliteDimmer(std::string data);

				static std::string SetLcdDimmer(int level);

				static std::string ReadLcdDimmer();

				static int AnswerLcdDimmer(std::string data);

				static std::string SetTxBusyDimmer(int level);

				static std::string ReadTxBusyDimmer();

				static int AnswerTxBusyDimmer(std::string data);

				static std::string SetPeakHold(PeakHoldType value);

				static std::string ReadPeakHold();

				static PeakHoldType AnswerPeakHold(std::string data);

				static std::string SetZinLed(EnableDisableValue value);

				static std::string ReadZinLed();

				static EnableDisableValue AnswerZinLed(std::string data);

				static std::string SetPopupMenuStyle(PopUpMenuStyle style);

				static std::string ReadPopupMenuStyle();

				static PopUpMenuStyle AnswerPopupMenuStyle(std::string data);

				static std::string SetDvsRxOutLevel(int Level);

				static std::string ReadDvsRxOutLevel();

				static int AnswerDvsRxOutLevel(std::string data);

				static std::string SetDvsTxOutLevel(int Level);

				static std::string ReadDvsTxOutLevel();

				static int AnswerDvsTxOutLevel(std::string data);

				static std::string SetKeyerType(KeyerTypeValue val);

				static std::string ReadKeyerType();

				static KeyerTypeValue AnswerKeyerType(std::string data);

				static std::string SetKeyerDotDash(KeyerDotDashValue val);

				static std::string ReadKeyerDotDash();

				static KeyerDotDashValue AnswerKeyerDotDash(std::string data);

				static std::string SetCwWeight(int Weight);

				static std::string ReadCwWeight();

				static int AnswerCwWeight(std::string data);

				static std::string SetBeaconInterval(int value);

				static std::string ReadBeaconInterval();

				static int AnswerBeaconInterval(std::string data);

				static std::string SetNumberStyle(NumberStyleValue val);

				static std::string ReadNumberStyle();

				static NumberStyleValue AnswerNumberStyle(std::string data);

				static std::string SetContestNumber(int Value);

				static std::string ReadContestNumber();

				static int AnswerContestNumber(std::string data);

				static std::string SetCWMemory1(CWMemoryTypeValue val);

				static std::string ReadCWMemory1();

				static CWMemoryTypeValue AnswerCWMemory1(std::string data);

				static std::string SetCWMemory2(CWMemoryTypeValue val);

				static std::string ReadCWMemory2();

				static CWMemoryTypeValue AnswerCWMemory2(std::string data);

				static std::string SetCWMemory3(CWMemoryTypeValue val);

				static std::string ReadCWMemory3();

				static CWMemoryTypeValue AnswerCWMemory3(std::string data);

				static std::string SetCWMemory4(CWMemoryTypeValue val);

				static std::string ReadCWMemory4();

				static CWMemoryTypeValue AnswerCWMemory4(std::string data);

				static std::string SetCWMemory5(CWMemoryTypeValue val);

				static std::string ReadCWMemory5();

				static CWMemoryTypeValue AnswerCWMemory5(std::string data);

				static std::string SetNbWidth(NBWidthValue value);

				static std::string ReadNbWidth();

				static NBWidthValue AnswerNbWidth(std::string data);

				static std::string SetNbRejection(NBRejectionValue value);

				static std::string ReadNbRejection();

				static NBRejectionValue AnswerNbRejection(std::string data);

				static std::string SetNbLevel(int level);

				static std::string ReadNbLevel();

				static int AnswerNbLevel(std::string data);

				static std::string SetBeepLevel(int level);

				static std::string ReadBeepLevel();

				static int AnswerBeepLevel(std::string data);

				static std::string SetRfSqlVr(RfSqlVrValue val);

				static std::string ReadRfSqlVr();

				static RfSqlVrValue AnswerRfSqlVr(std::string data);

				static std::string SetCatRate(CatRateValue val);

				static std::string ReadCatRate();

				static CatRateValue AnswerCatRate(std::string data);

				static std::string SetCatTOT(CatTOTValue val);

				static std::string ReadCatTOT();

				static CatTOTValue AnswerCatTOT(std::string data);

				static std::string SetCatRTS(EnableDisableValue val);

				static std::string ReadCatRTS();

				static EnableDisableValue AnswerCatRTS(std::string data);

				static std::string SetMemGroup(EnableDisableValue val);

				static std::string ReadMemGroup();

				static EnableDisableValue AnswerMemGroup(std::string data);

				static std::string SetFMSetting(EnableDisableValue val);

				static std::string ReadFMSetting();

				static EnableDisableValue AnswerFMSetting(std::string data);

				static std::string SetRecSetting(EnableDisableValue val);

				static std::string ReadRecSetting();

				static EnableDisableValue AnswerRecSetting(std::string data);

				static std::string SetATASSetting(EnableDisableValue val);

				static std::string ReadATASSetting();

				static EnableDisableValue AnswerATASSetting(std::string data);

				static std::string SetQuickSplitFreq(int val);

				static std::string ReadQuickSplitFreq();

				static int AnswerQuickSplitFreq(std::string data);

				static std::string SetTxTOT(int val);

				static std::string ReadTXTOT();

				static int AnswerTXTOT(std::string data);

				static std::string SetMicScan(EnableDisableValue val);

				static std::string ReadMicScan();

				static EnableDisableValue AnswerMicScan(std::string data);

				static std::string SetMicScanResume(MicScanResumeValue val);

				static std::string ReadMicScanResume();

				static MicScanResumeValue AnswerMicScanResume(std::string data);

				static std::string SetRefFreqAdjust(int val);

				static std::string ReadRefFreqAdjust();

				static int AnswerRefFreqAdjust(std::string data);

				static std::string SetClarSelect(ClarSelectValue val);

				static std::string ReadClarSelect();

				static ClarSelectValue AnswerClarSelect(std::string data);

				static std::string SetApo(APOValue val);

				static std::string ReadApo();

				static APOValue AnswerApo(std::string data);

				static std::string SetFanControl(FanControlValue val);

				static std::string ReadFanControl();

				static FanControlValue AnswerFanControl(std::string data);

				static std::string SetAMLowCutFreq(FreqLowCutValue val);

				static std::string ReadAMLowCutFreq();

				static FreqLowCutValue AnswerAMLowCutFreq(std::string data);

				static std::string SetAMLowCutSlope(FreqSlopeValue val);

				static std::string ReadAMLowCutSlope();

				static FreqSlopeValue AnswerAMLowCutSlope(std::string data);

				static std::string SetAMHighCutFreq(FreqHighCutValue val);

				static std::string ReadAMHighCutFreq();

				static FreqHighCutValue AnswerAMHighCutFreq(std::string data);

				static std::string SetAMHighCutSlope(FreqSlopeValue val);

				static std::string ReadAMHighCutSlope();

				static FreqSlopeValue AnswerAMHighCutSlope(std::string data);

				static std::string SetAMMicSelect(AudioInputValue val);

				static std::string ReadAMMicSelect();

				static AudioInputValue AnswerAMMicSelect(std::string data);

				static std::string SetAMOutLevel(int val);

				static std::string ReadAMOutLevel();

				static int AnswerAMOutLevel(std::string data);

				static std::string SetAMMicLevel(int val);

				static std::string ReadAMMicLevel();

				static int AnswerAMMicLevel(std::string data);

				static std::string SetAMPTTSelect(PTTSelectValue val);

				static std::string ReadAMPTTSelect();

				static PTTSelectValue AnswerAMPTTSelect(std::string data);

				static std::string SetCWLowCutFreq(FreqLowCutValue val);

				static std::string ReadCWLowCutFreq();

				static FreqLowCutValue AnswerCWLowCutFreq(std::string data);

				static std::string SetCWLowCutSlope(FreqSlopeValue val);

				static std::string ReadCWLowCutSlope();

				static FreqSlopeValue AnswerCWLowCutSlope(std::string data);

				static std::string SetCWHighCutFreq(FreqHighCutValue val);

				static std::string ReadCWHighCutFreq();

				static FreqHighCutValue AnswerCWHighCutFreq(std::string data);

				static std::string SetCWHighCutSlope(FreqSlopeValue val);

				static std::string ReadCWHighCutSlope();

				static FreqSlopeValue AnswerCWHighCutSlope(std::string data);

				static std::string SetCWOutLevel(int val);

				static std::string ReadCWOutLevel();

				static int AnswerCWOutLevel(std::string data);

				static std::string SetCWAutoMode(CwAutoModeValue val);

				static std::string ReadCWAutoMode();

				static CwAutoModeValue AnswerCWAutoMode(std::string data);

				static std::string SetCWBFO(BfoValue val);

				static std::string ReadCWBFO();

				static BfoValue AnswerCWBFO(std::string data);

				static std::string SetCWBreakkInType(CwBreakInType val);

				static std::string ReadCWBreakInType();

				static CwBreakInType AnswerCWBreakInType(std::string data);

				static std::string SetCWBreakkInDelay(int val);

				static std::string ReadCWBreakInDelay();

				static int AnswerCWBreakInDelay(std::string data);

				static std::string SetCWWaveShape(CwWaveShapeValue val);

				static std::string ReadCWWaveShape();

				static CwWaveShapeValue AnswerCWWaveShape(std::string data);

				static std::string SetCWFreqDisplay(CwFreqDisplayValue val);

				static std::string ReadCWFreqDisplay();

				static CwFreqDisplayValue AnswerCWFreqDisplay(std::string data);

				static std::string SetPCKeying(PCKeyingValue val);

				static std::string ReadPCKeying();

				static PCKeyingValue AnswerPCKeying(std::string data);

				static std::string SetQSKDelayTime(QskDelayTimeValue val);

				static std::string ReadQSKDelayTime();

				static QskDelayTimeValue AnswerQSKDelayTime(std::string data);

				static std::string SetDataMode(DataModeValue val);

				static std::string ReadDataMode();

				static DataModeValue AnswerDataMode(std::string data);

				static std::string SetPSKTone(PSKToneValue val);

				static std::string ReadPSKTone();

				static PSKToneValue AnswerPSKTone(std::string data);

				static std::string SetOtherDisp(int val);

				static std::string ReadOtherDisp();

				static int AnswerOtherDisp(std::string data);

				static std::string SetOtherShift(int val);

				static std::string ReadOtherShift();

				static int AnswerOtherShift(std::string data);

				static std::string SetDATALowCutFreq(FreqLowCutValue val);

				static std::string ReadDATALowCutFreq();

				static FreqLowCutValue AnswerDATALowCutFreq(std::string data);

				static std::string SetDATALowCutSlope(FreqSlopeValue val);

				static std::string ReadDATALowCutSlope();

				static FreqSlopeValue AnswerDATALowCutSlope(std::string data);

				static std::string SetDATAHighCutFreq(FreqHighCutValue val);

				static std::string ReadDATAHighCutFreq();

				static FreqHighCutValue AnswerDATAHighCutFreq(std::string data);

				static std::string SetDATAHighCutSlope(FreqSlopeValue val);

				static std::string ReadDATAHighCutSlope();

				static FreqSlopeValue AnswerDATAHighCutSlope(std::string data);

				static std::string SetDATAInSelect(AudioInputValue val);

				static std::string ReadDATAInSelect();

				static AudioInputValue AnswerDATAInSelect(std::string data);

				static std::string SetDATAPTTSelect(PTTSelectValue val);

				static std::string ReadDATAPTTSelect();

				static PTTSelectValue AnswerDATAPTTSelect(std::string data);

				static std::string SetDATAOutLevel(int val);

				static std::string ReadDATAOutLevel();

				static int AnswerDATAOutLevel(std::string data);

				static std::string SetDATABFO(DataBfoValue val);

				static std::string ReadDATABFO();

				static DataBfoValue AnswerDATABFO(std::string data);

				static std::string SetFMMicSelect(AudioInputValue val);

				static std::string ReadFMMicSelect();

				static AudioInputValue AnswerFMMicSelect(std::string data);

				static std::string SetFMOutLevel(int val);

				static std::string ReadFMOutLevel();

				static int AnswerFMOutLevel(std::string data);

				static std::string SetPktPTTSelect(PTTSelectValue val);

				static std::string ReadPktPTTSelect();

				static PTTSelectValue AnswerPktPTTSelect(std::string data);

				static std::string SetRptShift28MHZ(int val);

				static std::string ReadRptShift28MHZ();

				static int AnswerRptShift28MHZ(std::string data);

				static std::string SetRptShift50MHZ(int val);

				static std::string ReadRptShift50MHZ();

				static int AnswerRptShift50MHZ(std::string data);

				static std::string SetDCSPolarity(DCSPolarityValue val);

				static std::string ReadDCSPolarity();

				static DCSPolarityValue AnswerDCSPolarity(std::string data);

				static std::string SetRTTYLowCutFreq(FreqLowCutValue val);

				static std::string ReadRTTYLowCutFreq();

				static FreqLowCutValue AnswerRTTYLowCutFreq(std::string data);

				static std::string SetRTTYLowCutSlope(FreqSlopeValue val);

				static std::string ReadRTTYLowCutSlope();

				static FreqSlopeValue AnswerRTTYLowCutSlope(std::string data);

				static std::string SetRTTYHighCutFreq(FreqHighCutValue val);

				static std::string ReadRTTYHighCutFreq();

				static FreqHighCutValue AnswerRTTYHighCutFreq(std::string data);

				static std::string SetRTTYHighCutSlope(FreqSlopeValue val);

				static std::string ReadRTTYHighCutSlope();

				static FreqSlopeValue AnswerRTTYHighCutSlope(std::string data);

				static std::string SetRTTYShiftPort(RTTYShiftPortValue val);

				static std::string ReadRTTYShiftPort();

				static RTTYShiftPortValue AnswerRTTYShiftPort(std::string data);

				static std::string SetRTTYPolarityR(RTTYPolarityValue val);

				static std::string ReadRTTYPolarityR();

				static RTTYPolarityValue AnswerRTTYPolarityR(std::string data);

				static std::string SetRTTYPolarityT(RTTYPolarityValue val);

				static std::string ReadRTTYPolarityT();

				static RTTYPolarityValue AnswerRTTYPolarityT(std::string data);

				static std::string SetRTTYOutLevel(int val);

				static std::string ReadRTTYOutLevel();

				static int AnswerRTTYOutLevel(std::string data);

				static std::string SetRTTYShiftFreq(RTTYShiftFreqValue val);

				static std::string ReadRTTYShiftFreq();

				static RTTYShiftFreqValue AnswerRTTYShiftFreq(std::string data);

				static std::string SetRTTYMarkFreq(RTTYMarkFreq val);

				static std::string ReadRTTYMarkFreq();

				static RTTYMarkFreq AnswerRTTYMarkFreq(std::string data);

				static std::string SetRTTYBFO(DataBfoValue val);

				static std::string ReadRTTYBFO();

				static DataBfoValue AnswerRTTYBFO(std::string data);

				static std::string SetSSBLowCutFreq(FreqLowCutValue val);

				static std::string ReadSSBLowCutFreq();

				static FreqLowCutValue AnswerSSBLowCutFreq(std::string data);

				static std::string SetSSBLowCutSlope(FreqSlopeValue val);

				static std::string ReadSSBLowCutSlope();

				static FreqSlopeValue AnswerSSBLowCutSlope(std::string data);

				static std::string SetSSBHighCutFreq(FreqHighCutValue val);

				static std::string ReadSSBHighCutFreq();

				static FreqHighCutValue AnswerSSBHighCutFreq(std::string data);

				static std::string SetSSBHighCutSlope(FreqSlopeValue val);

				static std::string ReadSSBHighCutSlope();

				static FreqSlopeValue AnswerSSBHighCutSlope(std::string data);

				static std::string SetSSBMicSelect(AudioInputValue val);

				static std::string ReadSSBMicSelect();

				static AudioInputValue AnswerSSBMicSelect(std::string data);

				static std::string SetSSBOutLevel(int val);

				static std::string ReadSSBOutLevel();

				static int AnswerSSBOutLevel(std::string data);

				static std::string SetSSBBFO(BfoValue val);

				static std::string ReadSSBBFO();

				static BfoValue AnswerSSBBFO(std::string data);

				static std::string SetSSBPTTSelect(PTTSelectValue val);

				static std::string ReadSSBPTTSelect();

				static PTTSelectValue AnswerSSBPTTSelect(std::string data);

				static std::string SetSSBTxBPF(SSBTXBandPassValue val);

				static std::string ReadSSBTxBPF();

				static SSBTXBandPassValue AnswerSSBTxBPF(std::string data);

				static std::string SetAPFWidth(APFWidthValue val);

				static std::string ReadAPFWidth();

				static APFWidthValue AnswerAPFWidth(std::string data);

				static std::string SetCountourLevel(int val);

				static std::string ReadCountourLevel();

				static int AnswerCountourLevel(std::string data);

				static std::string SetCountourWidth(int val);

				static std::string ReadCountourWidth();

				static int AnswerCountourWidth(std::string datadata);

				static std::string SetIFNotchWidth(IFNotchWidthValue val);

				static std::string ReadIFNotchWidth();

				static IFNotchWidthValue AnswerIFNotchWidth(std::string data);

				static std::string SetSCPStartCycle(SCPStartCycleValue val);

				static std::string ReadSCPStartCycle();

				static SCPStartCycleValue AnswerSCPStartCycle(std::string data);

				static std::string SetSCPSpanFreq(SCPSpanFreqValue val);

				static std::string ReadSCPSpanFreq();

				static SCPSpanFreqValue AnswerSCPSpanFreq(std::string data);

				static std::string SetQuickDial(QuickDialValue val);

				static std::string ReadQuickDial();

				static QuickDialValue AnswerQuickDial(std::string data);

				static std::string SetAMDialStep(AMDialStep val);

				static std::string ReadAMDialStep();

				static AMDialStep AnswerAMDialStep(std::string data);

				static std::string SetSSBDialStep(SSBDialStep val);

				static std::string ReadSSBDialStep();

				static SSBDialStep AnswerSSBDialStep(std::string data);

				static std::string SetFMDialStep(FMDialStep val);

				static std::string ReadFMDialStep();

				static FMDialStep AnswerFMDialStep(std::string data);

				static std::string SetDialStep(DialStep val);

				static std::string ReadDialStep();

				static DialStep AnswerDialStep(std::string data);

				static std::string SetAmChStep(AMChannelStepValue val);

				static std::string ReadAmChStep();

				static AMChannelStepValue AnswerAmChStep(std::string data);

				static std::string SetFmChStep(FMChannelStepValue val);

				static std::string ReadFmChStep();

				static FMChannelStepValue AnswerFmChStep(std::string data);

				static std::string SetEQ1Freq(EQ1FreqValue val);

				static std::string ReadEQ1Freq();

				static EQ1FreqValue AnswerEQ1Freq(std::string data);

				static std::string SetEQ1Level(int val);

				static std::string ReadEQ1Level();

				static int AnswerEQ1Level(std::string data);

				static std::string SetEQ1Bwth(int val);

				static std::string ReadEQ1Bwth();

				static int AnswerEQ1Bwth(std::string data);

				static std::string SetEQ2Freq(EQ2FreqValue val);

				static std::string ReadEQ2Freq();

				static EQ2FreqValue AnswerEQ2Freq(std::string data);

				static std::string SetEQ2Level(int val);

				static std::string ReadEQ2Level();

				static int AnswerEQ2Level(std::string data);

				static std::string SetEQ2Bwth(int val);

				static std::string ReadEQ2Bwth();

				static int AnswerEQ2Bwth(std::string data);

				static std::string SetEQ3Freq(EQ3FreqValue val);

				static std::string ReadEQ3Freq();

				static EQ3FreqValue AnswerEQ3Freq(std::string data);

				static std::string SetEQ3Level(int val);

				static std::string ReadEQ3Level();

				static int AnswerEQ3Level(std::string data);

				static std::string SetEQ3Bwth(int val);

				static std::string ReadEQ3Bwth();

				static int AnswerEQ3Bwth(std::string data);

				static std::string SetPEQ1Freq(EQ1FreqValue val);

				static std::string ReadPEQ1Freq();

				static EQ1FreqValue AnswerPEQ1Freq(std::string data);

				static std::string SetPEQ1Level(int val);

				static std::string ReadPEQ1Level();

				static int AnswerPEQ1Level(std::string data);

				static std::string SetPEQ1Bwth(int val);

				static std::string ReadPEQ1Bwth();

				static int AnswerPEQ1Bwth(std::string data);

				static std::string SetPEQ2Freq(EQ2FreqValue val);

				static std::string ReadPEQ2Freq();

				static EQ2FreqValue AnswerPEQ2Freq(std::string data);

				static std::string SetPEQ2Level(int val);

				static std::string ReadPEQ2Level();

				static int AnswerPEQ2Level(std::string data);

				static std::string SetPEQ2Bwth(int val);

				static std::string ReadPEQ2Bwth();

				static int AnswerPEQ2Bwth(std::string data);

				static std::string SetPEQ3Freq(EQ3FreqValue val);

				static std::string ReadPEQ3Freq();

				static EQ3FreqValue AnswerPEQ3Freq(std::string data);

				static std::string SetPEQ3Level(int val);

				static std::string ReadPEQ3Level();

				static int AnswerPEQ3Level(std::string data);

				static std::string SetPEQ3Bwth(int val);

				static std::string ReadPEQ3Bwth();

				static int AnswerPEQ3Bwth(std::string data);

				static std::string SetHfSsbPwr(int val);

				static std::string ReadHfSsbPwr();

				static int AnswerHfSsbPwr(std::string data);

				static std::string SetHfAmPwr(int val);

				static std::string ReadHfAmPwr();

				static int AnswerHfAmPwr(std::string data);

				static std::string SetHfPwr(int val);

				static std::string ReadHfPwr();

				static int AnswerHfPwr(std::string data);

				static std::string Set50mSsbPwr(int val);

				static std::string Read50mSsbPwr();

				static int Answer50mSsbPwr(std::string data);

				static std::string Set50mAmPwr(int val);

				static std::string Read50mAmPwr();

				static int Answer50mAmPwr(std::string data);

				static std::string Set50mPwr(int val);

				static std::string Read50mPwr();

				static int Answer50mPwr(std::string data);

				static std::string SetSSBMicGain(int val);

				static std::string ReadSSBMicGain();

				static int AnswerSSBMicGain(std::string data);

				static std::string SetAMMicGain(int val);

				static std::string ReadAMMicGain();

				static int AnswerAMMicGain(std::string data);

				static std::string SetFMMicGain(int val);

				static std::string ReadFMMicGain();

				static int AnswerFMMicGain(std::string data);

				static std::string SetDATAMicGain(int val);

				static std::string ReadDATAMicGain();

				static int AnswerDATAMicGain(std::string data);

				static std::string SetSSBDataGain(int val);

				static std::string ReadSSBDataGain();

				static int AnswerSSBDataGain(std::string data);

				static std::string SetAMDataGain(int val);

				static std::string ReadAMDataGain();

				static int AnswerAMDataGain(std::string data);

				static std::string SetFMDataGain(int val);

				static std::string ReadFMDataGain();

				static int AnswerFMDataGain(std::string data);

				static std::string SetDataDataGain(int val);

				static std::string ReadDataDataGain();

				static int AnswerDataDataGain(std::string data);

				static std::string SetTunerSelect(TunerSelectValue val);

				static std::string ReadTunerSelect();

				static TunerSelectValue AnswerTunerSelect(std::string data);

				static std::string SetVoxSelect(VoxSelectValue val);

				static std::string ReadVoxSelect();

				static VoxSelectValue AnswerVoxSelect(std::string data);

				static std::string SetVoxGain(int val);

				static std::string ReadVoxGain();

				static int AnswerVoxGain(std::string data);

				static std::string SetVoxDelay(int val);

				static std::string ReadVoxDelay();

				static int AnswerVoxDelay(std::string data);

				static std::string SetAntiVoxGain(int val);

				static std::string ReadAntiVoxGain();

				static int AnswerAntiVoxGain(std::string data);

				static std::string SetDataVoxGain(int val);

				static std::string ReadDataVoxGain();

				static int AnswerDataVoxGain(std::string data);

				static std::string SetDataVoxDelay(int val);

				static std::string ReadDataVoxDelay();

				static int AnswerDataVoxDelay(std::string data);

				static std::string SetDataAntiVoxGain(int val);

				static std::string ReadDataAntiVoxGain();

				static int AnswerDataAntiVoxGain(std::string data);

				static std::string SetEmergencyFreq(EnableDisableValue val);

				static std::string ReadEmergencyFreq();

				static EnableDisableValue AnswerEmergencyFreq(std::string data);

				static std::string SetReset(ResetValue val);

				static std::string ReadMainVersion();

				static std::string AnswerMainVersion(std::string data);

				static std::string ReadDSPVersion();

				static std::string AnswerDSPVersion(std::string data);

				static std::string ReadLCDVersion();

				static std::string AnswerLCDVersion(std::string data);
			};//end class Menu

			class VFO_A_FREQ
			{
			public:
				static std::string Set(int val);
				static std::string Read();
				static int Answer(std::string data);
			};

			class VFO_B_FREQ
			{
			public:
				static std::string Set(int val);
				static std::string Read();
				static int Answer(std::string data);
			};

			class FAST_STEP
			{
			public:


				static std::string Set(VFOFastStepValue val);
				static std::string Read();
				static VFOFastStepValue Answer(std::string data);
			};



			class AGC_FUNCTION
			{
			public:

				static std::string Set(AGCSetValue val);
				static std::string Read();
				static AGCReadValue Answer(std::string data);
			};

			class IDENTIFICATION
			{
			public:
				static std::string Read();
				static std::string Answer(std::string data);
			};




			class INFORMATION
			{
			public:
				static std::string Read();
				static InformationValue Answer(std::string data);
			};


			class IF_SHIFT
			{
			public:

				static std::string Set(IfShiftValue val, int freq);
				static std::string Read();
				static IfShiftResultValue Answer(std::string data);
			};



			class KeyerMemory
			{
			public:
				static std::string Set(KeyerMemoryValue val);
				static std::string Read(int MemoryChannel);
				static KeyerMemoryValue Answer(std::string data);
			};



			class KeyPitch
			{
			public:
				static std::string Set(KeyPitchValue val);
				static std::string Read();
				static KeyPitchValue Answer(std::string data);
			};




			class Keyer
			{
			public:

				static std::string Set(KeyerValue val);
				static std::string Read();
				static KeyerValue Answer(std::string data);
			};


			class KeyerSpeed
			{
			public:
				static std::string Set(KeyerSpeedVal val);
				static std::string Read();
				static KeyerSpeedVal Answer(std::string data);
			};



			class CWKeyingPlayback
			{
			public:
				static std::string Set(KeyerMemoryChannel Val);
			};




			class VFODialLock
			{
			public:

				static std::string Set(DialLockValue val);
				static std::string Read();
				static DialLockValue Answer(std::string data);
			};


			class LoadMessage
			{
			public:
				static std::string Set(DVSRecordingValue val);
				static std::string Read(DVSRecordingValue val);
				static DVSRecordingValue Answer(std::string data);
			};

			class MemoryChannelToVFOA
			{
			public:
				static std::string Set();
			};



			class MemoryChannel
			{
			public:
				static std::string Set(MemoryChannelValue val);
				static std::string Read();
				static MemoryChannelValue Answer(std::string data);
			};

			class OperatingMode
			{
			public:
				static std::string Set(ModeValue val);
				static std::string Read();
				static ModeValue Answer(std::string data);
			};

			class MicGain
			{
			public:
				static std::string Set(int val);
				static std::string Read();
				static int Answer(std::string data);
			};




			class MonitorLevel
			{
			public:
				static std::string Set(MonitorLevelValue val);
				static std::string Read(MonitorFunction val);
				static MonitorLevelValue Answer(std::string data);
			};


			class MemoryChannelRead
			{
			public:
				static std::string Read(MemoryChannelValue val);
				static MemoryChannelReadValue Answer(std::string data);
			};


			class MeterSW
			{
			public:
				static std::string Set(MeterType val);
				static std::string Read();
				static MeterType Answer(std::string data);
			};





			class MemoryWriteTag
			{
			public:
				static std::string Set(MemoryChannelTagValue val);
				static std::string Read(MemoryChannelValue val);
				static MemoryChannelTagValue Answer(std::string data);

			};



			class MemoryChannelWrite
			{
			public:
				static std::string Set(MemoryChannelWriteValue val);
			};

			enum class MoxSetVal
			{
				OFF,
				ON
			};

			class MoxSet
			{
			public:

				static std::string Set(MoxSetVal val);
				static std::string Read();
				static MoxSetVal Answer(std::string data);
			};

			enum class NarrowValue
			{
				OFF,
				ON
			};

			class Narrow
			{
			public:

				static std::string Set(NarrowValue val);
				static std::string Read();
				static NarrowValue Answer(std::string data);
			};

			enum class NoiseBlankerStatusValue
			{
				OFF,
				ON
			};

			class NoiseBlankerStatus
			{
			public:

				static std::string Set(NoiseBlankerStatusValue val);
				static std::string Read();
				static NoiseBlankerStatusValue Answer(std::string data);
			};

			class NoiseBlankerLevel
			{
			public:
				/// <param name="val"> - Values between 0 and 10</param>
				/// <returns>std::string</returns>
				static std::string Set(int val);
				static std::string Read();
				static int Answer(std::string data);
			};

			enum class NoiseReductionValue
			{
				OFF,
				ON
			};

			class NoiseReduction
			{
			public:

				static std::string Set(NoiseReductionValue val);
				static std::string Read();
				static NoiseReductionValue Answer(std::string data);
			};

			class OppositeBandInformation
			{
			public:
				static std::string Read();
				static OppositeInformationValue Answer(std::string data);
			};

			class OffSet
			{
			public:
				static std::string Set(OperationType val);
				static std::string Read();
				static OperationType Answer(std::string data);
			};

			enum class PreAmpValue
			{
				IPO,
				AMP
			};

			class PreAmp
			{
			public:

				static std::string Set(PreAmpValue val);
				static std::string Read();
				static PreAmpValue Answer(std::string data);
			};

			class PlayBack
			{
			public:
				static std::string Set(DVSRecordingValue val);
				static std::string Read();
				static DVSRecordingValue Answer(std::string data);
			};

			class PowerControl
			{
			public:
				/// <param name="val"> - Values between 0 and 100</param>
				/// <returns>std::string</returns>
				static std::string Set(int val);
				static std::string Read();
				static int Answer(std::string data);
			};

			class SpeechProcessorLevel
			{
			public:

				/// <param name="val"> - Values between 0 and 100</param>
				/// <returns>std::string</returns>
				static std::string Set(int val);
				static std::string Read();
				static int Answer(std::string data);
			};


			class SpeechProcessor
			{
			public:


				static std::string Set(SpeechProcessorSetting val);
				static std::string Read(SpeechProcessorType state);
				static SpeechProcessorSetting Answer(std::string data);
			};




			class PowerSwitch
			{
			public:

				static std::string Set(PowerSwitchValue val);
				static std::string Read();
				static PowerSwitchValue Answer(std::string data);
			};

			class QMBStore
			{
			public:
				static std::string Set();
			};

			class QMBRecall
			{
			public:
				static std::string Set();
			};

			class QMBSplit
			{
			public:
				static std::string Set();
			};


			class RFAttenuator
			{
			public:

				static std::string Set(RfAttenuatorState val);
				static std::string Read();
				static RfAttenuatorState Answer(std::string data);
			};

			class ClarClear
			{
			public:
				static std::string Set();
			};

			class ClarDown
			{
			public:

				/// <param name="val">Values between 0 and 9999.</param>
				/// <returns></returns>
				static std::string Set(int val);
			};

			class RFGain
			{
			public:

				/// <param name="val"> - Values between 0 and 30</param>
				/// <returns></returns>
				static std::string Set(int val);
				static std::string Read();
				static int Answer(std::string data);
			};



			class RadioInformation
			{
			public:
				enum StateType
				{
					HI_SWR,
					REC = 3,
					PLAY,
					TX_LED = 10,
					RX_LED = 11
				};
				enum Value
				{
					OFF,
					ON
				};
				static std::string Read(StateType type);
				static RadioInfoVal Answer(std::string data);
			};



			class NoiseReductionLevel
			{
			public:
				static std::string Set(int Val);
				static std::string Read();
				static int Answer(std::string data);
			};


			class ReadMeter
			{
			public:


				static std::string Read(ReadMeterType type);
				static MeterVal Answer(std::string data);
			};



			class RadioStatus
			{
			public:

				static std::string Read();
				static RadioStatusValue Answer(std::string data);
			};

			class RxClarifierPlusOffset
			{
			public:
				static std::string Set(int val);
			};


			class Scan
			{
			public:

				static std::string Set(ScanState val);
				static std::string Read();
				static ScanState Answer(std::string data);
			};

			class CWBreakInDelay
			{
			public:
				static std::string Set(int val);
				static std::string Read();
				static int Answer(std::string data);
			};



			class Width
			{
			public:

				static std::string Set(WidthValue val);
				static std::string Read();
				static WidthValue Answer(std::string data);
			};


			class SMeterReading
			{
			public:
				static std::string Read();
				static int Answer(std::string data);

			};

			class SquelchLevel
			{
			public:
				static std::string Set(int val);
				static std::string Read();
				static int Answer(std::string data);
			};

			enum class SplitValue
			{
				OFF,
				ON,
				ON_5KU

			};

			class Split
			{
			public:


				static std::string Set(SplitValue val);
				static std::string Read();
				static SplitValue Answer(std::string data);
			};

			class SwapVfo
			{
			public:
				static std::string Set();
			};

			enum class TXWValue
			{
				OFF,
				ON
			};

			class TXW
			{
			public:


				static std::string Set(TXWValue val);
				static std::string Read();
				static TXWValue Answer(std::string data);
			};

			enum class TxSetValue
			{
				RadioTxOff_CatTxOff,
				RadioTxOff_CatTxOn,
				RadioTxOn_CatTxOff
			};
			class TxSet
			{
			public:

				static std::string Set(TxSetValue val);
				static std::string Read();
				static TxSetValue Answer(std::string data);
			};

			enum class LockValue
			{
				Locked,
				Unlocked
			};

			class PLLUnlockStatus
			{
			public:


				static std::string Read();
				static LockValue Answer(std::string data);
			};

			class Up
			{
			public:
				static std::string Set();
			};

			class VoxDelayTime
			{
			public:
				static std::string Set(int val);
				static std::string Read();
				static int Answer(std::string data);
			};

			class VoxGain
			{
			public:
				static std::string Set(int val);
				static std::string Read();
				static int Answer(std::string data);
			};

			class VFO_A_toMemoryChannel
			{
			public:
				static std::string Set();
			};

			enum class VoxStatusValue
			{
				OFF,
				ON
			};
			class VoxStatus
			{
			public:

				static std::string Set(VoxStatusValue val);
				static std::string Read();
				static VoxStatusValue Answer(std::string data);
			};

			class ZeroIn
			{
			public:
				static std::string Set();
			};


		}; //end Commands
	}; //end FT891
}; //end Yeasu

#endif