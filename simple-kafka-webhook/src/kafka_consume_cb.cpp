
#include <cstdio>

#include "kafka.hpp"
#include "kafka_consume_cb.hpp"

#include "utils.hpp"
#include "curler.hpp"

KafkaConsumeCallback::KafkaConsumeCallback()
{
	_poutput = &(std::cout);
}

KafkaConsumeCallback::~KafkaConsumeCallback()
{}


KafkaConsumeCallback&
KafkaConsumeCallback::setOutputStream(std::ostream *pstream) { 
	_poutput = pstream; 
	return *this; 
}

void 
KafkaConsumeCallback::send(RdKafka::Message *inpMsg, Curler *inpCurler)
{
	Utils::StringVector headers;
	inpCurler->send(NULL, 0, headers);
}

void 
KafkaConsumeCallback::consume_cb(RdKafka::Message *pmsg, void *puserdata) 
{
	Kafka *pKafka = reinterpret_cast<Kafka*>(puserdata);
	Curler *pCurler = pKafka->getCurler();
	Utils::StringVector headers;
	
	switch(pmsg->err()) {

	case RdKafka::ERR_NO_ERROR:
		send(pmsg, pCurler);
		break;


	// end switch
	}


}


