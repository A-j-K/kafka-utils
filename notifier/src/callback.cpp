
#include <curl/curl.h>

#include "callback.hpp"

Callback::Callback()
{}

Callback::Callback(AbsConfig::ShPtr &config):
	_pConfig(config),
	_pCurler(Curler::ShPtr(new Curler(config))),
	_pInputPipe(Pipe::ShPtr(new Pipe)),
	_pThread(ThreadShPtr(new std::thread(Callback::static_run, this)))
{}

Callback::Callback(
	AbsConfig::ShPtr &config,
	Curler::ShPtr &curler
):
	_pConfig(config),
	_pCurler(curler)
{}

Callback::~Callback()
{
}

void 
Callback::static_run(Callback *self)
{
	self->run();
}

CurlerRval::ShPtr
Callback::send(PipeEntry::ShPtr& spEntry)
{
	CurlerRval::ShPtr spResult;
	std::stringstream oss;
	const RdKafka::Message *pMsg = spEntry->getMessagePtr();
	curl_slist *pHeaders = NULL;
	oss << "X-Kafka-Msg-Key: " << pMsg->key();
	pHeaders = curl_slist_append(pHeaders, oss.str().c_str()); 
	oss.str(""); 
	oss.clear();
	oss << "X-Kafka-Topic: " << pMsg->topic_name();
	pHeaders = curl_slist_append(pHeaders, oss.str().c_str()); 
	oss.str(""); 
	oss.clear();
	oss << "X-Kafka-Partition: " << pMsg->partition();
	pHeaders = curl_slist_append(pHeaders, oss.str().c_str()); 
	spResult = _pCurler->send((char*)pMsg->payload(), pMsg->len(), pHeaders);
	curl_slist_free_all(pHeaders);
	return spResult;
}

void
Callback::run() 
{
	bool loop_control = true;
	while(loop_control) {
		PipeEntry::ShPtr spEntry;
		CurlerRval::ShPtr spResult;
		spEntry = _pInputPipe->popFront(Pipe::BLOCKING, NULL);
		PipeEntry::msgType type = spEntry->getType();
		switch(type) {
			case PipeEntry::eTHREAD_TERM: 
				loop_control = false;
				break;

			case PipeEntry::eKAFKA_MSG: 
				spResult = send(spEntry);
				if(spResult->_result != CURLE_OK) {
					// Handle error
				}
				break;

			default:
				break;
		}
	}
}


