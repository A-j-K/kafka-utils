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

// General
protected:
	bool _verified;
public:
	Config(); 
	virtual bool getVerified(void) { return _verified; }

// Broker definition API
protected:
	int _partition;
	std::string _topic;
	std::string _consumerGroup;
	KeyValue _options;
	StringVector _brokers;
public:
	virtual int getPartition(void) { return _partition; }
	virtual std::string getTopic(void) { return _topic; }
	virtual std::string getConsumerGroup(void) { return _consumerGroup; }
	virtual const StringVector& getBrokers(void) { return _brokers; }
	virtual const KeyValue& getClientOptions(void) { return _options; }
	virtual std::string getBrokersAsString(void);  

// API Caller definition API
protected:
	int _expectResponseCode;
	std::string _apiUrl;
	KeyValue _requestHeaders;
public:
	virtual int getExpectResponseCode(void) { return _expectResponseCode; }
	virtual const std::string& getApiUrl(void) { return _apiUrl; }	
	virtual const KeyValue& getRequestHeaders(void) { return _requestHeaders; }

};


