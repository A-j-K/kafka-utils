#pragma once

#include <mutex>
#include <queue>
#include <memory>
#include <exception>

#include "librdkafka/rdkafkacpp.h"

class PipeEntry 
{
public:
	typedef std::shared_ptr<PipeEntry> ShPtr;
	enum msgType {
		eTHREAD_TERM,
		eKAFKA_MSG
	};
protected:
	RdKafka::Message *_pMessage;
	msgType _type;
public:
	PipeEntry();
	PipeEntry(RdKafka::Message *);
	virtual ~PipeEntry();
	const RdKafka::Message * getMessagePtr(void);
	PipeEntry& setType(msgType type) { _type = type; }
	msgType getType() { return _type; }
};


class PipeException : public std::exception {};

class Pipe
{
public:
	typedef std::shared_ptr<Pipe> ShPtr;
	const static bool NONBLOCKING = true;
	const static bool BLOCKING = false;
protected:
	int _maxCount;
	std::mutex _mutex;
	std::queue<PipeEntry::ShPtr> _queue;
public:
	Pipe();
	Pipe(int max);
	virtual ~Pipe();
	virtual bool pushBack(PipeEntry::ShPtr entry, bool try_lock = Pipe::BLOCKING);
	virtual PipeEntry::ShPtr popFront(bool try_lock, bool *result);
	virtual bool isEmpty(bool try_lock, bool *result);
	//virtual bool isFull(bool try_lock, bool *result);
	virtual Pipe& setMaxCount(int max, bool try_lock, bool *result);
	virtual size_t getSize(bool try_lock, bool *result);
};

