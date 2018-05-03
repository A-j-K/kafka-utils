#pragma once


#include <memory>
#include <librdkafka/rdkafkacpp.h>

#include "pipe.hpp"
#include "absconfig.hpp"

class Kafka
{
public:
	typedef std::shared_ptr<Kafka> ShPtr;

protected:
	Pipe::ShPtr      _pPipe;
	AbsConfig::ShPtr _pConfig;
	RdKafka::Conf 	 *_pKafkaConf;
	RdKafka::KafkaConsumer *_pConsumer;

public:
	Kafka();
	virtual ~Kafka();

	Kafka(AbsConfig::ShPtr&, Pipe::ShPtr&);

	void run();

};

