#pragma once

#include <thread>
#include <memory>
#include <curl/curl.h>

#include "pipe.hpp"
#include "curler.hpp"
#include "absconfig.hpp"

class Callback
{
public:
	typedef std::shared_ptr<Callback> ShPtr;
	typedef std::shared_ptr<std::thread> ThreadShPtr;

protected:
	AbsConfig::ShPtr _pConfig;
	Pipe::ShPtr _pInputPipe;
	ThreadShPtr _pThread;
	Curler::ShPtr _pCurler;

	virtual void run(); // Called statically from thread runner.

        virtual CurlerRval::ShPtr send(PipeEntry::ShPtr&);

	Callback(); // ctor protected to prevent usage.

public:
	virtual ~Callback();
	Callback(AbsConfig::ShPtr &); // ctor to use.
	
	Callback(   // ctor for DI
        	AbsConfig::ShPtr&,
	        Curler::ShPtr&
	);


	static void static_run(Callback*);

	ThreadShPtr getThread()    { return _pThread;    }
	Curler::ShPtr getCurler()  { return _pCurler;    }
	Pipe::ShPtr getInputPipe() { return _pInputPipe; }
};

