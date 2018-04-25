#pragma once

#include "config.hpp" 

class JsonConfig : public Config
{
public:
	JsonConfig(const std::string &filename);
	int loadFromFile(const std::string &filename); 
};


