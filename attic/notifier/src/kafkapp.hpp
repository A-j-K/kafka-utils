#pragma once

// Tried to use librdkafacpp but it doesn't seem 
// to be Google Mock freindly so roll a simple wrapper.

#include <string>
#include <memory>
#include <librdkafka/rdkafka.h>

class RdKafkaConfPP
{
public:
	typedef std::shared_ptr<RdKafkaConfPP> ShPtr;

protected:
	rd_kafka_conf_t *_pConf;

public:
	RdKafkaConfPP();
	virtual ~RdKafkaConfPP();

	virtual rd_kafka_conf_t *getConf() { return _pConf; }
};

class RdKafkaTopicConfPP
{
public:
	typedef std::shared_ptr<RdKafkaTopicConfPP> ShPtr;

protected:
	rd_kafka_topic_conf_t *_pConf;

public:
	RdKafkaTopicConfPP();
	virtual ~RdKafkaTopicConfPP();

	virtual rd_kafka_topic_conf_t *getConf() { return _pConf; }
};

class RdKafkaTypePP
{
public:
	enum type {
		eProducer = RD_KAFKA_PRODUCER,
		eConsumer = RD_KAFKA_CONSUMER
	};
};

class RdKafkaPP
{
public:
	typedef std::shared_ptr<RdKafkaPP> ShPtr;

protected:
	rd_kafka_t *_pKafka;
	RdKafkaConfPP::ShPtr _spConf;
	std::string _errstr;

public:
	RdKafkaPP();
	RdKafkaPP(rd_kafka_type_t, RdKafkaConfPP::ShPtr);
	virtual ~RdKafkaPP();

	virtual RdKafkaConfPP::ShPtr getConf() { return _spConf; }
	virtual rd_kafka_t *getKafka() { return _pKafka; }
	virtual std::string getErrStr() { return _errstr; }
};



