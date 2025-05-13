# CAT
Cat library for Yaesu. Currently, only the FT-891, FTDX101, FTDX10, FT991, FT-710, and others are to come. 

This library is for serializing and deserializing the data sent to and received from the Yaesu radios. 

Motivation:
Currently, a few projects encompass this functionality, but they need more scope. HamLib, for instance, controls a radio just fine but won't write memory channels. Chirp does, but it won't let you change the dimmer level on your FT-891 buttons on the fly. I want to make my own programs to control my radios at home and in the field on low-power devices such as a Raspberry PI. You may do as well, or have other exciting ideas for your radio, and I'd like to hear about them. If you use this library for your projects, please email me (kd5eax@hotmail.com). 

It's in standard C++. The only prerequisites for building the library into your project is the [fmt library](https://github.com/fmtlib/fmt), or if your compiler already supports std::format a global find/replace in the header and cpp file and you won't even need the libfmt. 

The library has a standard structure. 

Namespace Yeasu::Commands holds all the rig-specific commands, structures, and enums grouped by their namespace.
```
Yaesu::Commands::FT891 
Yaesu::Commands::FT991
Yaesu::Commands::FTDX101
Yeasu::Commands::FTDX10
Yeasu::Commands::FT710
```
The radio commands that support each function are Set(), Read(), and Answer() if available. Some commands only have a Set, such as switching between VFOA and VFOB. Others only have read and answer, such as Information. 

Read commands always request a response from the radio.
Answer commands always take the response of a Read Command sent to the radio and return the appropriate type.
Set commands set some state of the radio. 



Namespace Yaesu handles figuring out what radio it's talking to with the IDENTIFICATION commands and the RigType enum. As new radios are added, the RigType enum will be expanded. This is particularly useful with the FTDX101 series, as with the power commands 200 in the MP model and only 100 in the D model. The following is a simple illustration of how to use this library and boost::asio with the FT891 to set the meter type of the display. 


```
\\ code
void SetMeterType(serial_port& port, MeterType v)
{
	string buff = Yaesu::Commands::FT891::MeterSW::Set(v); 
	port.write_some(buffer(buff.c_str(), buff.length()));
}


//from Yaesu::Commands::FT891 in Cat.h
enum class MeterType
			{
				COMP,
				ALC,
				PO,
				SWR,
				ID
			};

```

MeterSW is a command in the manual that changes what the meter displays when transmitting, such as the Compression level, ALC, etc. 

```

MeterType GetMeterType(serial_port& port)
{
  string buff = Yaesu::Commands::FT891::MeterSW::Read();
  string rbuff;
  rbuff.resize(45);
	port.write_some(buffer(buff.c_str(), buff.length()));
  port.read_some(buffer(&rbuff[0],rbuff.size()));
  return Yaesu::Commands::FT891::MeterSW::Answer(rbuff);
}

```
