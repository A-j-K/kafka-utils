#pragma once

#include <string>
#include <memory>

#include "utils.hpp"

class AbstractConfig
{
public:
	typedef std::shared_ptr<AbstractConfig> ShPtr;

// General
protected:
	bool _verified;
public:
	AbstractConfig(); 
	virtual bool getVerified(void) { return _verified; }

// Broker definition API
protected:
	int _partition;
	std::string _topic;
	Utils::KeyValue _options;
	Utils::StringVector _brokers;
public:
	virtual int getPartition(void) const { return _partition; }
	virtual std::string getTopic(void) const { return _topic; }
	virtual const Utils::StringVector& getBrokers(void) const { return _brokers; }
	virtual const Utils::KeyValue& getClientOptions(void) const { return _options; }
	virtual std::string getBrokersAsString(void) const;  

// API Caller definition API
protected:
	int _expectResponseCode;
	std::string _apiUrl;
	std::string _httpVerb;
	std::string _contentType;
	Utils::KeyValue _requestHeaders;
public:
	virtual int getExpectResponseCode(void) const { return _expectResponseCode; }
	virtual const std::string& getApiUrl(void) const { return _apiUrl; }	
	virtual const Utils::KeyValue& getRequestHeaders(void) const { return _requestHeaders; }
	virtual const std::string getHttpVerb(void) const { return _httpVerb; }
	virtual const std::string getContentType(void) const { return _contentType; }
};


