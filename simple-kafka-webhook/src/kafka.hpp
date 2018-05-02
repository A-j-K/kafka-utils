#pragma once

#include <memory>
#include <librdkafka/rdkafkacpp.h>

#include "curler.hpp"
#include "config/abstract_config.hpp"

class Kafka
{
public:
	typedef std::shared_ptr<Kafka> ShPtr;
	typedef std::shared_ptr<RdKafka::Conf> RdKafkaConfShPtr;


PROTECTED:
	
	RdKafkaConfShPtr	_spKafkaConf;
	

public:
	Kafka(); 
	virtual ~Kafka();

	void	
	configure(const AbstractConfig *pConfig, 
		RdKafka::Conf *outpConf, RdKafka::Conf *pTopic);
};

