
#include "configfactory.hpp" 
#include "jsonconfig.hpp"


Config::ShPtr
ConfigFactory::getConfigByFile(const std::string &filename)
{
	return Config::ShPtr(new JsonConfigFromFile(filename));
}

Config::ShPtr
ConfigFactory::getConfigByJsonString(const std::string &json)
{
	return Config::ShPtr(new JsonConfigFromString(json));
}



