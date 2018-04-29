
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
	bool rval = false;
	if(try_lock) {
		if(_mutex.try_lock()) {
			if(_queue.size() < _maxCount) {
				_queue.push(entry);
				rval = true;
			}
			_mutex.unlock();
			return rval;
		}
		return rval;
	}
	_mutex.lock();
	if(_queue.size() < _maxCount) {
		_queue.push(entry);
		rval = true;
	}
	_mutex.unlock();
	return rval;
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
		return sp;
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
		if(result) *result = false;
		return -1;
	}
	_mutex.lock();
	rval = _queue.size();
	_mutex.unlock();
	if(result) *result = true;
	return rval;
}

Pipe& 
Pipe::setMaxCount(int max, bool try_lock, bool *result)
{
	if(try_lock) {
		if(_mutex.try_lock()) {
			_maxCount = max;
			_mutex.unlock();
			if(result) *result = true;
			return *this;
		}
		if(result) *result = false;
		return *this;
	}
	_mutex.lock();
	_maxCount = max;
	_mutex.unlock();
	if(result) *result = true;
	return *this;
}
