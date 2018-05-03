
#include <cstdio>
#include <stdexcept>

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

KafkaConsumeCallback&
KafkaConsumeCallback::setUserdata(void *p) { 
	_puserdata = p; 
	return *this; 
}
CurlerRval::ShPtr
KafkaConsumeCallback::send(RdKafka::Message *inpMsg, Curler *inpCurler)
{
	CurlerRval::ShPtr spRval;
	Utils::StringVector headers;
	headers.push_back(stringbuilder()
		<< "X-Kafka: "
		<< inpMsg->key() << ";"
		<< inpMsg->topic()->name() << ";"
		<< inpMsg->partition() << ";"
		<< inpMsg->offset());
	spRval = inpCurler->send((char*)inpMsg->payload(), inpMsg->len(), headers);
	if(spRval->_result != CURLE_OK) {
		// ToDo. For now, throw an exception
		throw new std::runtime_error(
			stringbuilder() << "Need to handle this error"
		);		
	}
}

void 
KafkaConsumeCallback::consume_cb(RdKafka::Message &msg, void *puserdata) 
{
	Kafka *pKafka = reinterpret_cast<Kafka*>(puserdata);
	Curler *pCurler = pKafka->getCurler();
	Utils::StringVector headers;
	
	switch(msg.err()) {
		case RdKafka::ERR_NO_ERROR:
			send(&msg, pCurler);
			break;
	}


}


