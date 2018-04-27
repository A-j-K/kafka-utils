#pragma once

#include <thread>
#include <memory>
#include <curl/curl.h>

#include "utils/pipe.hpp"
#include "config/config.hpp"

class Callback
{
public:
	typedef std::shared_ptr<Callback> ShPtr;
	typedef std::shared_ptr<std::thread> ThreadShPtr;

protected:
	CURL *_pCurl;
	Config::ShPtr _pConfig;
	Pipe::ShPtr _pInputPipe;
	ThreadShPtr _thread;

public:
	Callback();
	~Callback();
	Callback(Config::ShPtr &);

	Pipe::ShPtr getInputPipe(void) { return _pInputPipe; }

	void run(Callback *self);
	static void static_run(Callback *self);
};

