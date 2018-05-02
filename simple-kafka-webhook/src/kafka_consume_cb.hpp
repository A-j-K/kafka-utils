#pragma once

#include <sstream>
#include <iostream>
#include "utils.hpp"

class KafkaConsumeCallback : public RdKafka::ConsumeCb
{
protected:

	std::ostream	*_poutput;

	void
	send(RdKafka::Message*, Curler*);

public:
	
	KafkaConsumeCallback();
	~KafkaConsumeCallback();

	KafkaConsumeCallback(std::ostream *pstream) : _poutput(&std::cout) {}

	virtual void 
	consume_cb(RdKafka::Message*, void*); 

	virtual KafkaConsumeCallback&
	setOutputStream(std::ostream *pstream); 
};


