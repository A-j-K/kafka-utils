
#include <sstream>
#include <iostream>
#include <stdexcept>
#include <exception>

#include "utils.hpp"
#include "kafka.hpp"

Kafka::Kafka()
{} 

Kafka::~Kafka()
{}

void
Kafka::configure(const AbstractConfig *pConfig, 
	RdKafka::Conf *pConf,
	RdKafka::Conf *pTopic
)
{
	std::string errstr;
	RdKafka::Conf::ConfResult result;
	Utils::KeyValue options = pConfig->getClientOptions();
	Utils::KeyValue::const_iterator itor_options = options.begin();
	while(itor_options != options.end()) {
		size_t topic_pos;
		std::string name = itor_options->first;
		std::string value = itor_options->second;
		topic_pos = name.find("topic.", 0);
		if(topic_pos != std::string::npos && topic_pos == 0) {
			std::string newname = name.substr(sizeof("topic.")-1);
			result = pTopic->set(newname, value, errstr);
			if(result != RdKafka::Conf::ConfResult::CONF_OK) {
				throw new std::invalid_argument(
					stringbuilder()
					<< "Configure failure at line "
					<< __LINE__ << errstr
				);
			}
		}
		else {
			result = pConf->set(name, value, errstr);
			if(result != RdKafka::Conf::ConfResult::CONF_OK) {
				throw new std::invalid_argument(
					stringbuilder()
					<< "Configure failure at line "
					<< __LINE__ << errstr
				);
			}
		}
		if(name == "group.id") {
			pConf->set("offset.store.method", "broker", errstr);
		}
		itor_options++;
	}

	pConf->set(std::string("default_topic_conf"), pTopic, errstr);
}

