#pragma once

#include <string>
#include <memory>

#include "utils.hpp"

class AbsConfig
{
public:
	typedef std::shared_ptr<AbsConfig> ShPtr;

// General
protected:
	bool _verified;
public:
	AbsConfig(); 
	virtual bool getVerified(void) { return _verified; }

// Broker definition API
protected:
	int _partition;
	std::string _topic;
	std::string _consumerGroup;
	Utils::KeyValue _options;
	Utils::StringVector _brokers;
public:
	virtual int getPartition(void) { return _partition; }
	virtual std::string getTopic(void) { return _topic; }
	virtual std::string getConsumerGroup(void) { return _consumerGroup; }
	virtual const Utils::StringVector& getBrokers(void) { return _brokers; }
	virtual const Utils::KeyValue& getClientOptions(void) { return _options; }
	virtual std::string getBrokersAsString(void);  

// API Caller definition API
protected:
	int _expectResponseCode;
	std::string _apiUrl;
	std::string _httpVerb;
	std::string _contentType;
	Utils::KeyValue _requestHeaders;
public:
	virtual int getExpectResponseCode(void) { return _expectResponseCode; }
	virtual const std::string& getApiUrl(void) { return _apiUrl; }	
	virtual const Utils::KeyValue& getRequestHeaders(void) { return _requestHeaders; }
	virtual const std::string getHttpVerb(void) { return _httpVerb; }
	virtual const std::string getContentType(void) { return _contentType; }
};


