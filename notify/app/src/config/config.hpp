#pragma once

#include <map>
#include <string>
#include <vector>

class Config
{
public:
	typedef std::map<std::string, std::string> KeyValue;
	typedef std::vector<std::string> StringVector;

protected:
	KeyValue _options;
	StringVector _brokers;

public:
	virtual StringVector& getBrokers(void) {
		return _brokers;
	} 

	virtual KeyValue& getClientOptions(void) {
		return _options;
	}	
};


