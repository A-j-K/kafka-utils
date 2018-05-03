#pragma once

#include "config.hpp" 

class ConfigFactory
{
public:
	static Config::ShPtr
	getConfigByFile(const std::string &filename); 

	static Config::ShPtr
	getConfigByJsonString(const std::string &json); 
};


