#pragma once

#include <sstream>
#include <iostream>
#include "utils.hpp"
#include "curler.hpp"

class KafkaConsumeCallback : public RdKafka::ConsumeCb
{
protected:

	void		*_puserdata;
	std::ostream	*_poutput;


public:
	
	KafkaConsumeCallback();
	~KafkaConsumeCallback();

	KafkaConsumeCallback(std::ostream *pstream) : _poutput(&std::cout) {}

	virtual void 
	consume_cb(RdKafka::Message&, void*); 

	virtual CurlerRval::ShPtr
	send(RdKafka::Message*, Curler*);

	virtual KafkaConsumeCallback&
	setOutputStream(std::ostream *pstream); 

	virtual KafkaConsumeCallback&
	setUserdata(void *); 
};


