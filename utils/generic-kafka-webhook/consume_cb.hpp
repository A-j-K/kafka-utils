#pragma once

#include <memory>
#include <sstream>
#include <iostream>
#include <librdkafka/rdkafkacpp.h>

#include "hexdump.hpp"

namespace GenericKafkaWebhook {

class ConsumeCb :  
	public RdKafka::ConsumeCb,
	protected KafkaUtils::Hexdump
{
public:
	typedef std::shared_ptr<ConsumeCb> ShPtr;

	void            *_puserdata;
	std::ostream    *_poutput;

	ConsumeCb();
	~ConsumeCb();
	ConsumeCb(std::ostream *pstream);

	virtual ConsumeCb&
        setOutputStream(std::ostream *pstream);

	virtual void
        consume_cb(RdKafka::Message&, void*);

}; // class ConsumeCb

}; // namespace GenericKafkaWebhook 
