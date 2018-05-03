
// Tried to use librdkafacpp but it doesn't seem 
// to be Google Mock freindly so roll a simple wrapper.

#include <exception>
#include "kafkapp.hpp"


RdKafkaConfPP::RdKafkaConfPP()
{
	_pConf = rd_kafka_conf_new();
}

RdKafkaConfPP::~RdKafkaConfPP()
{
	if(_pConf) {
		rd_kafka_conf_destroy(_pConf);
		_pConf = 0;
	}
}

RdKafkaPP::RdKafkaPP()
{}

RdKafkaPP::RdKafkaPP(rd_kafka_type_t type, RdKafkaConfPP::ShPtr spConf) :
	_spConf(spConf)
{
	char errstr[512];
	_pKafka = rd_kafka_new(type, spConf->getConf(), errstr, sizeof(errstr));
	if(!_pKafka) {
		_errstr = std::string(errstr);
		throw new std::exception(_errstr);
	}
}

RdKafkaPP::~RdKafkaPP()
{}




