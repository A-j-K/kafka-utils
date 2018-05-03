
#include <exception>

#include "utils.hpp"
#include "kafka.hpp"

Kafka::Kafka()
{}

Kafka::~Kafka()
{}


Kafka::Kafka(AbsConfig::ShPtr& pConfig, Pipe::ShPtr& pPipe) :
	_pConfig(pConfig),
	_pPipe(pPipe)
{
	std::string errstr;
	Utils::KeyValue options;
	Utils::KeyValue::iterator itor = options.begin();
	RdKafka::Conf *pKafkaTopicConf = RdKafka::Conf::create(RdKafka::Conf::CONF_TOPIC);
	_pKafkaConf = RdKafka::Conf::create(RdKafka::Conf::CONF_GLOBAL);
	while(itor != options.end()) {
		size_t topic_pos;
		std::string name = itor->first;
		std::string value = itor->second;
		RdKafka::Conf::ConfResult res = RdKafka::Conf::CONF_UNKNOWN;
		topic_pos = name.find("topic.", 0);
		if(topic_pos != std::string::npos && topic_pos == 0) {
			std::string newname = name.substr(sizeof("topic.")-1);
			res = pKafkaTopicConf->set(newname, value, errstr);
		}
		else {
			res = _pKafkaConf->set(name, value, errstr);
		}
		if(res == RdKafka::Conf::CONF_UNKNOWN) {
			throw new std::invalid_argument(errstr);
		}
		
		itor++;
	}

	_pKafkaConf->set("metadata.broker.list", _pConfig->getTopic(), errstr);
	_pKafkaConf->set("default_topic_conf", pKafkaTopicConf, errstr);
	delete pKafkaTopicConf;
}

void 
Kafka::run()
{
	std::string errstr;
	_pConsumer = RdKafka::KafkaConsumer::create(_pKafkaConf, errstr);
	if(!_pConsumer) {
		throw new std::invalid_argument(errstr);
	}
}

