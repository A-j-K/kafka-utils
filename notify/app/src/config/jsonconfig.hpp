#pragma once

#include "config.hpp" 

class JsonConfig : public Config
{
public:
	int loadFromFile(const std::string &filename); 
};


