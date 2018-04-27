
#include <sstream>

#include "callback.hpp"

Callback::Callback()
{}

Callback::Callback(Config::ShPtr &config):
	_pConfig(config)
{
	curl_global_init(CURL_GLOBAL_ALL);
	_pCurl = curl_easy_init();
	curl_easy_setopt(_pCurl, CURLOPT_NOSIGNAL, 1L);
	curl_easy_setopt(_pCurl, CURLOPT_NOPROGRESS, 1L);
	curl_easy_setopt(_pCurl, CURLOPT_VERBOSE, 0L);
	_pInputPipe = Pipe::ShPtr(new Pipe);
	_thread = ThreadShPtr(new std::thread(Callback::static_run, this));
}

Callback::~Callback()
{
	if(_pCurl) {
		curl_easy_cleanup(_pCurl);
	}
	curl_global_cleanup();
}

void
Callback::static_run(Callback *self) 
{
	bool keep = true;
	while(keep) {
		PipeEntry::ShPtr spEntry;
		Config::KeyValue headers;
		spEntry = self->_pInputPipe->popFront(Pipe::BLOCKING, NULL);
		headers = self->_pConfig->getRequestHeaders();
		// https://curl.haxx.se/libcurl/c/curl_easy_setopt.html
		curl_easy_setopt(self->_pCurl, CURLOPT_URL, self->_pConfig->getApiUrl().c_str());
		curl_easy_setopt(self->_pCurl, CURLOPT_HEADER, "Connection: keep-alive");
		Config::KeyValue::iterator itor = headers.begin();
		while(itor != headers.end()) {
			std::stringstream oss;
			oss << itor->first << ": " << itor->second;
			curl_easy_setopt(self->_pCurl, CURLOPT_HEADER, oss.str().c_str());
		}

	}
}
