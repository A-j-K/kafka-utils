#pragma once

#include <string>
#include <vector>
#include <memory>
#include <sstream>
#include <curl/curl.h>

#include "pipe.hpp"
#include "absconfig.hpp"

struct CurlHeaderHolder
{
        typedef std::shared_ptr<CurlHeaderHolder> ShPtr;
        typedef std::vector<std::string> HeaderVec;
        HeaderVec _headers;
        void addHeader(char *in, size_t len) {
                std::string s;
                s.append(in, len);
                _headers.push_back(s);
        }
};

struct CurlBodyHolder
{
        typedef std::shared_ptr<CurlBodyHolder> ShPtr;
        typedef std::shared_ptr<std::stringstream> SteamShPtr;
        SteamShPtr _poss;
        CurlBodyHolder() { _poss = SteamShPtr(new std::stringstream); }
        void addBody(char *in, size_t len) {
                _poss->write(in,len);
        }
        SteamShPtr getStream() { return _poss; }
};

struct CurlerRval
{
	typedef std::shared_ptr<CurlerRval> ShPtr;
	CURLcode _result;
	CurlHeaderHolder::ShPtr _pHeader;
	CurlBodyHolder::ShPtr _pBody;
};

class Curler
{
public:
	typedef std::shared_ptr<Curler> ShPtr;

	static int      _counter;

	CURL		*_pCurl;

protected:
	AbsConfig::ShPtr	_pConfig;

public:
	Curler();
	virtual ~Curler();
	Curler(AbsConfig::ShPtr pConfig);

	virtual CurlerRval::ShPtr send(char *p, int len, curl_slist *pHeaders);
	
};

