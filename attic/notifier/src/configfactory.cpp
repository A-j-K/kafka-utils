
#include "configfactory.hpp" 
#include "jsonconfig.hpp"


AbsConfig::ShPtr
ConfigFactory::getConfigByFile(const std::string &filename)
{
	return AbsConfig::ShPtr(new JsonConfigFromFile(filename));
}

AbsConfig::ShPtr
ConfigFactory::getConfigByJsonString(const std::string &json)
{
	return AbsConfig::ShPtr(new JsonConfigFromString(json));
}



