#pragma once

#include "config.hpp" 

class ConfigFactory
{
public:
	static Config::ShPtr
	loadFromFile(const std::string &filename); 
};


