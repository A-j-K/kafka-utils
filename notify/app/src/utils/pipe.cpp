
#include "pipe.hpp"

PipeEntry::PipeEntry() : 
	_pMessage(0) 
{}

PipeEntry::PipeEntry(RdKafka::Message *pmsg) : 
	_pMessage(pmsg) 
{}

PipeEntry::~PipeEntry() 
{
	if(_pMessage) {
		delete _pMessage;
	}
}

const RdKafka::Message *
PipeEntry::getMessagePtr(void)
{
	return _pMessage;
}

bool 
Pipe::pushBack(PipeEntry::ShPtr entry, bool try_lock)
{
	if(try_lock) {
		if(_mutex.try_lock()) {
			_queue.push(entry);
			_mutex.unlock();
			return true;
		}
		return false;
	}
	_mutex.lock();
	_queue.push(entry);
	_mutex.unlock();
	return true;
}

PipeEntry::ShPtr 
Pipe::popFront(bool try_lock, bool *result)
{
	PipeEntry::ShPtr sp;
	if(try_lock) {
		if(_mutex.try_lock()) {
			sp = _queue.front();
			_queue.pop();
			_mutex.unlock();
			if(result) *result = true;
			return sp;
		}
		if(result) *result = false;
	}
	_mutex.lock();
	sp = _queue.front();
	_queue.pop();
	_mutex.unlock();
	if(result) *result = true;
	return sp;
}

bool 
Pipe::isEmpty(bool try_lock, bool *result)
{
	bool rval;
	if(try_lock) {
		if(_mutex.try_lock()) {
			rval = _queue.size() == 0;
			_mutex.unlock();
			if(result) *result = true;
			return rval;
		}
		if(result) *result = false;
		return false;
	}
	_mutex.lock();
	rval = _queue.size() == 0;
	_mutex.unlock();
	if(result) *result = true;
	return rval;
}

size_t
Pipe::getSize(bool try_lock, bool *result)
{
	size_t rval;
	if(try_lock) {
		if(_mutex.try_lock()) {
			rval = _queue.size();
			_mutex.unlock();
			if(result) *result = true;
			return rval;
		}
		if(result) *result = true;
	}
	_mutex.lock();
	rval = _queue.size();
	_mutex.unlock();
	if(result) *result = true;
	return rval;
}
