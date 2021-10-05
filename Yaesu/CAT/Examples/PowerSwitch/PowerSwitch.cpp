#include <iostream>
#include <boost/asio.hpp>
#include <boost/asio/serial_port.hpp>
#include "../../Cat.h"

using namespace std;
using namespace Yeasu::FT891::Commands;
using namespace boost;
using namespace posix_time;
using namespace asio;

//set this to your radio's com port, be it a COM# on windows, or a /dev/tty on linux
string port = "COM10";
int baud = 4800; //factory default baud rate of the rig. Modify if yours is different. 

string dummydata = "alslkdkinckdlikse;"; //sufficently long enough garbage data for a dummy command to set the radio into it's error state (it replies with "?;")

void PowerDown(serial_port& port)
{
	cout << "Powering Down" << endl;
	cout.flush();
	//Tell it to turn off..
	string buff = PowerSwitch::Set(PowerSwitchValue::OFF);
	port.write_some(buffer(buff.c_str(), buff.length()));
	sleep(1); // wait at least one second but not more than two. 
	//and put it back in the error state to complete turning it off. (this isn't in the CAT manual, but is required.) 
	port.write_some(buffer(dummydata.c_str(), dummydata.length()));
	buff.clear();
}

void PowerUp(serial_port& port)
{

	cout << "Powering up" << endl;
	cout.flush();
	//put it in the error state by giving it dummy data. 
	port.write_some(buffer(dummydata.c_str(), dummydata.length()));
	sleep(1); //wait at least one second but not more than two. 
	//tell it to turn on. 
	string buff = PowerSwitch::Set(PowerSwitchValue::ON);
	port.write_some(buffer(buff.c_str(), buff.length()));
	buff.clear();

	cout << "Initializing .." << endl;
}

PowerSwitchValue ReadPowerSwitch(serial_port& port)
{
	string buff;
	buff.resize(30);
	//write dummy data to the rig to put it in the error state
	port.write_some(buffer(dummydata.c_str(), dummydata.length()));
	sleep(1); // wait at least 1 second but not more than two. 
	//request the power switch state
	auto pstate = PowerSwitch::Read();
	port.write_some(buffer(pstate.c_str(), pstate.length()));

	//read the response
	int read = 0;
	while (read < 3) //it'll be at least 3 characters long, but perhaps more due to the error state replying with ?;
	{
		read = port.read_some(buffer(&buff[read], buff.size() - read));
	}

	//clear the error state from the buffer. 
	while (buff.find_first_of('?', 0) != string::npos) 
	{
		buff.erase(0, buff.find_first_of(';', 0) + 1);
	}

	//just in case there's more than one response in the buffer still. 
	size_t pos;
	pos = buff.find(";");
	auto command = buff.substr(0, pos + 1);
	//deseralize the power switch state
	return PowerSwitch::Answer(command);
}

int main()
{
	io_service io_service;
	serial_port serial(io_service);
	
	serial.open(port);
	serial.set_option(serial_port_base::baud_rate(baud));
	serial.set_option(serial_port_base::character_size(8));
	serial.set_option(serial_port_base::stop_bits(serial_port_base::stop_bits::one));
	serial.set_option(serial_port_base::parity(serial_port_base::parity::none));
	serial.set_option(serial_port_base::flow_control(serial_port_base::flow_control::none));

	try
	{
		if (ReadPowerSwitch(serial) == PowerSwitchValue::OFF)
		{
			PowerUp(serial);
		}
		else
		{
			PowerDown(serial);
		}
	}
	catch (invalid_argument e)
	{
		cout << e.what() << endl << flush;
	}
}
