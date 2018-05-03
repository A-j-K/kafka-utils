
#include <sstream>
#include "config.hpp"

Config::Config() : _verified(false) 
{}

std::string
Config::getBrokersAsString(void) 
{ 
	bool skipfirst = true;
	std::string rval;
	std::stringstream oss;
	StringVector::iterator itor = _brokers.begin();
	while(itor != _brokers.end()) {
		if(!skipfirst) {
			oss << ",";
		}
		oss << *itor;
		skipfirst = false;	
		itor++;
	}
	return oss.str(); 
}

