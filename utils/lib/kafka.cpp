
#include <sstream>
#include <iostream>
#include <stdexcept>
#include <exception>

#include "utils.hpp"
#include "kafka.hpp"

Kafka::Kafka()
{}

Kafka::Kafka(AbstractConfig *pConfig) :
	_pConfig(pConfig)
{}

Kafka::Kafka(RdKafka::KafkaConsumer *pConsumer) :
	_pKafkaConsumer(pConsumer)
{}

Kafka::~Kafka()
{}

Kafka&
Kafka::setConfig(AbstractConfig *inpConfig)
{
	_pConfig = inpConfig;
	return *this;
}

RdKafka::KafkaConsumer*
Kafka::prepare(AbstractConfig *pConfig, std::string &outErrstr)
{
	RdKafka::Conf *_pKafkaConf = RdKafka::Conf::create(RdKafka::Conf::CONF_GLOBAL);
	configure(pConfig, _pKafkaConf);
	return (_pKafkaConsumer = RdKafka::KafkaConsumer::create(_pKafkaConf, outErrstr));
}

void
Kafka::configure(const AbstractConfig *inpConfig, 
	RdKafka::Conf *inpConf,
	RdKafka::Conf *inpTopic
)
{
	bool deleteTopic = false,
	     addDefaultTopicConf = false;
	std::string errstr;
	RdKafka::Conf::ConfResult result;
	RdKafka::Conf *pTopic = inpTopic ? inpTopic : 0;
	Utils::KeyValue options = inpConfig->getClientOptions();
	Utils::KeyValue::const_iterator itor_options = options.begin();
	while(itor_options != options.end()) {
		size_t topic_pos;
		std::string name = itor_options->first;
		std::string value = itor_options->second;
		topic_pos = name.find("topic.", 0);
		if(topic_pos != std::string::npos && topic_pos == 0) {
			std::string newname = name.substr(sizeof("topic.")-1);
			if(!pTopic) {
				pTopic = RdKafka::Conf::create(RdKafka::Conf::CONF_TOPIC);
				deleteTopic = true;
			}
			result = pTopic->set(newname, value, errstr);
			addDefaultTopicConf = true;
			if(result != RdKafka::Conf::ConfResult::CONF_OK) {
				throw new std::invalid_argument(
					stringbuilder()
					<< "Configure failure at line "
					<< __LINE__ << " " << errstr
				);
			}
		}
		else {
			result = inpConf->set(name, value, errstr);
			if(result != RdKafka::Conf::ConfResult::CONF_OK) {
				throw new std::invalid_argument(
					stringbuilder()
					<< "Configure failure at line "
					<< __LINE__ << " " << errstr
				);
			}
		}
		if(name == "group.id") {
			inpConf->set("offset.store.method", "broker", errstr);
		}
		itor_options++;
	}

	if(addDefaultTopicConf) {
		inpConf->set(std::string("default_topic_conf"), pTopic, errstr);
	}
	if(deleteTopic) {
		delete pTopic;
	}
}

