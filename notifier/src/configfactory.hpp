#pragma once

#include "absconfig.hpp" 

class ConfigFactory
{
public:
	static AbsConfig::ShPtr
	getConfigByFile(const std::string &filename); 

	static AbsConfig::ShPtr
	getConfigByJsonString(const std::string &json); 
};


