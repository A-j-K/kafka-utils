
#include <sstream>
#include <stdexcept>
#include "jsonconfig.hpp" 

int
JsonConfig::load(json_t *pjsonconfig)
{
	if(!json_is_object(pjsonconfig)) {
		throw std::invalid_argument("JSON is not an OBJECT");
	}
	load_consumer(pjsonconfig);
	load_callback(pjsonconfig);
	_verified = true;
	return 0;
}

void
JsonConfig::load_consumer_brokers(json_t *pjsonbrokers)
{
	if(pjsonbrokers && json_is_array(pjsonbrokers)) {
		size_t index;
		json_t *pvalue;
		json_array_foreach(pjsonbrokers, index, pvalue) {
			const char *pstr = json_string_value(pvalue);
			std::string s(pstr);
			_brokers.push_back(s);	
		}
	}
}

void
JsonConfig::load_consumer_options(json_t *pjsonoptions)
{
	if(pjsonoptions && json_is_array(pjsonoptions)) {
		size_t index;
		json_t *pvalue;
		json_array_foreach(pjsonoptions, index, pvalue) {
			if(json_is_object(pvalue)) {
				json_t *p1, *p2;
				p1 = json_object_get(pvalue, "name");
				p2 = json_object_get(pvalue, "value");
				if(p1 && json_is_string(p1) && p2 && json_is_string(p2)) {
					std::string s1(json_string_value(p1));
					std::string s2(json_string_value(p2));
					_options[s1] = s2;
				}
			}
		}	
	}
}

void
JsonConfig::load_consumer_topic(json_t *pjsontopic)
{
	if(pjsontopic && json_is_object(pjsontopic)) {
		json_t *p = json_object_get(pjsontopic, "name");
		if(p && json_is_string(p)) {
			std::string s(json_string_value(p));
			_topic = s;
		}
		else {
			throw std::invalid_argument("No topic name supplied");
		}
		p = json_object_get(pjsontopic, "partition");
		if(p && json_is_integer(p)) {
			_partition = (int)json_integer_value(p);
		}
	}
}

void
JsonConfig::load_consumer(json_t *pjsonconfig)
{
	json_t *ptop, *ptemp;

	if((ptop = json_object_get(pjsonconfig, "consumer")) == NULL) {
		throw std::invalid_argument("consumer not found");
	}
	ptemp = json_object_get(ptop, "group");
	if(ptemp && json_is_string(ptemp)) {
		std::string s(json_string_value(ptemp));
		_consumerGroup = s;	
	}
	ptemp = json_object_get(ptop, "brokers");
	load_consumer_brokers(ptemp);
	ptemp = json_object_get(ptop, "options");
	load_consumer_options(ptemp);
	ptemp = json_object_get(ptop, "topic");
	load_consumer_topic(ptemp);
}

void
JsonConfig::load_callback(json_t *pjsonconfig)
{
	json_t *ptop, *ptemp;

	if((ptop = json_object_get(pjsonconfig, "callback")) == NULL) {
		throw std::invalid_argument("callback not found");
	}
	ptemp = json_object_get(ptop, "expect_response_code");
	if(ptemp && json_is_integer(ptemp)) {
		_expectResponseCode = json_integer_value(ptemp);
	}
	ptemp = json_object_get(ptop, "url");
	if(ptemp && json_is_string(ptemp)) {
		std::string s(json_string_value(ptemp));
		_apiUrl = s;
	}
	else {
		throw std::invalid_argument("No callback URL supplied");
	}
	ptemp = json_object_get(ptop, "headers");
	if(ptemp && json_is_array(ptemp)) { // Headers are optional.
		size_t index;
		json_t *pvalue;
		json_array_foreach(ptemp, index, pvalue) {
			if(json_is_object(pvalue)) {
				json_t *p1, *p2;
				p1 = json_object_get(pvalue, "name");
				p2 = json_object_get(pvalue, "value");
				if(p1 && json_is_string(p1) && p2 && json_is_string(p2)) {
					std::string s1(json_string_value(p1));
					std::string s2(json_string_value(p2));
					_requestHeaders[s1] = s2;
				}
			}
		}
	}
}

int
JsonConfig::loadFromFile(const std::string &filename)
{
	int rval = -1;
	json_error_t err;
	json_t *pjsonconfig = json_load_file(filename.c_str(), 0, &err);
	if(!pjsonconfig) {
		std::stringstream oss;
		oss << err.text << " at line " << err.line << " in column " << err.column;
		throw std::invalid_argument(oss.str().c_str());
	}
	try {
		rval = load(pjsonconfig);
	}
	catch(std::invalid_argument e) {
		rval = -2;
	}
	json_decref(pjsonconfig);
	return rval;
}

int 
JsonConfig::loadFromString(const std::string &json)
{
	int rval;
	json_error_t err;
	json_t *pjsonconfig = json_loads(json.c_str(), 0, &err);
	if(!pjsonconfig) {
		std::stringstream oss;
		oss << err.text << " at line " << err.line << " in column " << err.column;
		throw std::invalid_argument(oss.str().c_str());
	}
	rval = load(pjsonconfig);
	json_decref(pjsonconfig);
	return rval;
}

JsonConfigFromFile::JsonConfigFromFile(const std::string &filename)
{
	loadFromFile(filename); // Used for runtime
}

JsonConfigFromString::JsonConfigFromString(const std::string &json)
{
	loadFromString(json); // Used for unit testing
}


