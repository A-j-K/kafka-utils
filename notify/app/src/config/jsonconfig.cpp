

#include "jsonconfig.hpp" 


JsonConfig::JsonConfig(const std::string &filename) 
{
	_verified = false;	
}

int
JsonConfig::loadFromFile(const std::string &filename)
{
	_verified = true;
	return 0;
}


