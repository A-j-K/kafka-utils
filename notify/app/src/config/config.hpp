#pragma once

#include <map>
#include <string>
#include <vector>
#include <memory>

class Config
{
public:
	typedef std::shared_ptr<Config> ShPtr;
	typedef std::map<std::string, std::string> KeyValue;
	typedef std::vector<std::string> StringVector;

protected:
	bool _verified;
	KeyValue _options;
	StringVector _brokers;

public:
	virtual StringVector& getBrokers(void) {
		return _brokers;
	} 

	virtual KeyValue& getClientOptions(void) {
		return _options;
	}	

	virtual bool getVerified(void) {
		return _verified;
	}
};


