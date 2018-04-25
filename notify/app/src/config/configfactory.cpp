
#include "configfactory.hpp" 
#include "jsonconfig.hpp"

Config::ShPtr
ConfigFactory::loadFromFile(const std::string &filename)
{
	// Here we can return teh correct type depending
	// upon filename. However, right now it's only json.
	return Config::ShPtr(new JsonConfig(filename));
}



