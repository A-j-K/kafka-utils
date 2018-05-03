
#include <exception>
#include <curl/curl.h>

#include "utils.hpp"
#include "callback.hpp"

Callback::Callback()
{}

Callback::Callback(AbsConfig::ShPtr &config, bool thd):
	_pConfig(config),
	_pCurler(Curler::ShPtr(new Curler(config))),
	_pInputPipe(Pipe::ShPtr(new Pipe))
{
	if(thd) {
		_pThread = ThreadShPtr(new std::thread(Callback::static_run, this));
	}
}

Callback::Callback(
	AbsConfig::ShPtr &config,
	Curler::ShPtr &curler,
	Pipe::ShPtr &pipe
):
	_pConfig(config),
	_pCurler(curler),
	_pInputPipe(pipe)
{}

Callback::~Callback()
{
}

void
Callback::static_run(Callback *self)
{
	self->run(true);
}

bool
Callback::static_run_once(Callback *self, bool blocking)
{
	return self->run_once(blocking);
}

CurlerRval::ShPtr
Callback::send(PipeEntry::ShPtr& spEntry)
{
	std::stringstream oss;
	Utils::StringVector headers;
	RdKafka::MessageTimestamp ts;

	const RdKafka::Message *pMsg = spEntry->getMessagePtr();
	
	oss << "X-Kafka-Key: " << pMsg->key();
	headers.push_back(oss.str());
	oss.str(""); oss.clear();

	oss << "X-Kafka-Topic: " << pMsg->topic_name();
	headers.push_back(oss.str());
	oss.str(""); oss.clear();

	oss << "X-Kafka-Partition: " << pMsg->partition();
	headers.push_back(oss.str());
	oss.str(""); oss.clear();
	
	oss << "X-Kafka-Offset: " << pMsg->offset();
	headers.push_back(oss.str());
	oss.str(""); oss.clear();

	ts = pMsg->timestamp();
	oss << "X-Kafka-Timestamp: " << ts.timestamp;
	headers.push_back(oss.str());
	oss.str(""); oss.clear();
	
	oss << "X-Kafka-Latency: " << pMsg->latency();
	headers.push_back(oss.str());

	return _pCurler->send((char*)pMsg->payload(), pMsg->len(), headers);
}

bool
Callback::run_once(bool blocking) 
{
	bool valid = false;
	PipeEntry::ShPtr spEntry;
	CurlerRval::ShPtr spResult;
	if(blocking) {
		spEntry = _pInputPipe->popFront(Pipe::BLOCKING, &valid);
	}
	else {
		spEntry = _pInputPipe->popFront(Pipe::NONBLOCKING, &valid);
	}
	if(valid) {
		PipeEntry::msgType type = spEntry->getType();
		switch(type) {
			case PipeEntry::eTHREAD_TERM: 
				return false;
				break;

			case PipeEntry::eKAFKA_MSG: 
				spResult = send(spEntry);
				if(spResult->_result != CURLE_OK) {
					std::string s = _pCurler->xlateCode2str(spResult->_result);
					throw std::runtime_error(s);
					// Handle error better than crash.
				}
				break;

			default:
				break;
		}
	}
	return true;
}

bool
Callback::run(bool blocking) 
{
	while(run_once(blocking)) ;
	return true;
}
	


