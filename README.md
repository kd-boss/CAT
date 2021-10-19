# CAT
Cat library for Yaesu. Currently only the FT-891, but others to come. 

This library is for serializing and de serializing the data sent to and received from the Yeasu radios. 

Motivation:
Currently there's a few projects that encompass this functionality but they're limited in scope. HamLib for instance controls a radio just fine, but won't write memory channels. Chirp does, but won't let you change the dimmer level on your FT-891's buttons on the fly. I want to make my own programs to control my ft-891 in the field on a Rasbperry PI. Perhaps you do as well, or have other interesting idea's for your radio, and I'd like to hear about them. 

It's in standard C++, the only prerequisites for building the library into your own project is the [fmt library](https://github.com/fmtlib/fmt), or if your compiler already supports std::format a global find/replace in the header and cpp file and you won't even need the libfmt. 

The library has a standard structure. 

there's Set, Read, and Answer for all of the commands of the radio that support each function. Some functions only have a Set, such as switching between VFOA and VFOB. 

Set generates the data to be sent to the radio to change a setting, such as VFO, and the commands all have an appropriate type.

```
\\your code
void SetMeterType(serial_port& port, MeterType v)
{
	string buff = MeterSW::Set(v); 
	port.write_some(buffer(buff.c_str(), buff.length()));
}


//Cat.h
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
  string buff = MeterSW::Read();
  string rbuff;
  rbuff.resize(45);
	port.write_some(buffer(buff.c_str(), buff.length()));
  port.read_some(buffer(&rbuff[0],rbuff.size()));
  return MeterSW::Answer(rbuff);
}

```

This isn't how I'd recommend writing anything for the radio, it's just the simplest pseudocode (real code, really) that illustrates how this library is used, and is useful.

