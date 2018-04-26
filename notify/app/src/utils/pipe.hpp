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
protected:
	RdKafka::Message *_pMessage;
public:
	PipeEntry();
	PipeEntry(RdKafka::Message *);
	virtual ~PipeEntry();
	const RdKafka::Message * getMessagePtr(void);
};


class PipeException : public std::exception {};

class Pipe
{
public:
	typedef std::shared_ptr<Pipe> ShPtr;
	const static bool NONBLOCKING = true;
	const static bool BLOCKING = false;
protected:
	int _count;
	std::mutex _mutex;
	std::queue<PipeEntry::ShPtr> _queue;
public:
	bool pushBack(PipeEntry::ShPtr entry, bool try_lock = Pipe::BLOCKING);
	PipeEntry::ShPtr popFront(bool try_lock, bool *result);
	bool isEmpty(bool try_lock, bool *result);
	size_t getSize(bool try_lock, bool *result);
};

