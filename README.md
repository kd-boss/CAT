# CAT
Cat library for Yaesu. Currently only the FT-891, FTDX101, and FT991 with others to come. 

This library is for serializing and de serializing the data sent to and received from the Yaesu radios. 

Motivation:
Currently there's a few projects that encompass this functionality but they're limited in scope. HamLib for instance controls a radio just fine, but won't write memory channels. Chirp does, but won't let you change the dimmer level on your FT-891's buttons on the fly. I want to make my own programs to control my radios at home and in the field on low power devices such as a Rasbperry PI. Perhaps you do as well, or have other interesting idea's for your radio, and I'd like to hear about them. If you're using this library for your projects feel free to email me and tell me about them (ky4ct@arrl.net). 

It's in standard C++, the only prerequisites for building the library into your own project is the [fmt library](https://github.com/fmtlib/fmt), or if your compiler already supports std::format a global find/replace in the header and cpp file and you won't even need the libfmt. 

The library has a standard structure. 

namespace Yeasu::Commands holds all the rig specific commands, structures and enums grouped by their namespace

Yaesu::Commands::FT891 
Yaesu::Commands::FT991
Yaesu::Commands::FTDX101

there's Set, Read, and Answer for all of the commands of a radio that support each function. Some commands only have a Set, such as switching between VFOA and VFOB. 

Read commands always request a response from the radio.
Answer commands always take the response of the radio and returns the approperate type.
Set commands set some state of the radio. 



namespace Yaesu handles figuring out what radio it's talking to with the IDENTIFICATION commands and the RigType enum. As ne radio's are added, the RigType enum will be expanded. This is particularly useful with the FTDX101 series as many feilds are 200 on the MP model and only 100 on the D model. The following is a simple illiustration of how to use this library and boost::asio with the FT891 to set the meter type of the display. 


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

MeterSW is a command in the manual to change what the meter displays when transmitting, Compression level, ALC, etc. 

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
