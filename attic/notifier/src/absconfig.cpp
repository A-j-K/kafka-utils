
#include <sstream>
#include "absconfig.hpp"

AbsConfig::AbsConfig() : _verified(false) 
{}

std::string
AbsConfig::getBrokersAsString(void) 
{ 
	bool skipfirst = true;
	std::string rval;
	std::stringstream oss;
	Utils::StringVector::iterator itor = _brokers.begin();
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

