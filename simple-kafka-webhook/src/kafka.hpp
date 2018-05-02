#pragma once

#include <memory>
#include <librdkafka/rdkafkacpp.h>

#include "utils.hpp"
#include "curler.hpp"
#include "config/abstract_config.hpp"

class Kafka
{
public:
	typedef std::shared_ptr<Kafka> ShPtr;


PROTECTED:
	RdKafka::Conf		*_pKafkaConf;
	RdKafka::KafkaConsumer	*_pKafkaConsumer;

	Curler			*_pCurler;
	AbstractConfig		*_pConfig;

	RdKafka::KafkaConsumer*
		prepare(AbstractConfig*, std::string &);

public:
	Kafka(); 
	Kafka(AbstractConfig*);
	virtual ~Kafka();

	Kafka(RdKafka::KafkaConsumer*);

	virtual Kafka&
		setConfig(AbstractConfig*);

	virtual void	
		configure(const AbstractConfig *pConfig, 
			RdKafka::Conf *outpConf, RdKafka::Conf *pTopic = 0);

	virtual Curler* getCurler() { return _pCurler; }
};

