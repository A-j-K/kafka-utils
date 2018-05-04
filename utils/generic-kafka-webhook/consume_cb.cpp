
#include <cctype>
#include <cstdio>
#include <cstring>

#include "utils.hpp"
#include "consume_cb.hpp"

namespace GenericKafkaWebhook {


ConsumeCb::ConsumeCb() :
	_poutput(&std::cout)
{}

ConsumeCb::~ConsumeCb()
{}

ConsumeCb::ConsumeCb(std::ostream *pstream) :
	_poutput(pstream) 
{}



ConsumeCb&
ConsumeCb::setOutputStream(std::ostream *pstream)
{
	_poutput = pstream;
	return *this;
}

void
ConsumeCb::consume_cb(RdKafka::Message &inMsg, void *inpUserdata)
{
	std::stringstream oss;

	 (*_poutput) << "CB Comsume : message\n";

	switch(inMsg.err()) {
		case RdKafka::ERR__TIMED_OUT:
			(*_poutput) << "Callback timed out\n";
			break;
		case RdKafka::ERR_NO_ERROR:
			oss << "Message Key: " << inMsg.key() << std::endl;
			oss << "Topic      : " << inMsg.topic_name() << std::endl;
			oss << "Offset     : " << inMsg.offset() << std::endl;
			oss << "Latency    : " << inMsg.latency() << std::endl;
			oss << hexdump(inMsg.payload(), inMsg.len());
			(*_poutput) << oss.str() << std::endl;
			break;		
		default:
			(*_poutput) << "Other\n";
			break;
	}
}

}; // namespace GenericKafkaWebhook 

