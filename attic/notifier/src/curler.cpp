
#include <sstream>
#include "curler.hpp"


#ifdef __cplusplus
extern "C" { // C callbacks for libcurl
#endif
static size_t
callback_header_writer(char* pbuffer, size_t size, size_t nitems, void* puserdata)
{
        size_t actualsize = size * nitems; 
        CurlHeaderHolder *h = (CurlHeaderHolder*)puserdata;
        h->addHeader(pbuffer, actualsize);
        return actualsize;
}
static size_t
callback_body_writer(char* pbuffer, size_t size, size_t nitems, void* puserdata)
{                           
        size_t actualsize = size * nitems; 
        CurlBodyHolder *b = (CurlBodyHolder*)puserdata;
        b->addBody(pbuffer, actualsize);
        return actualsize;  
}                           
#ifdef __cplusplus          
}                           
#endif                     

int  Curler::_counter = 0;

Curler::Curler()
{
	_pCurl = curl_easy_init();
	std::lock_guard<std::mutex> lock(_counter_mtx);
	if(Curler::_counter == 0) {
		curl_global_init(CURL_GLOBAL_ALL);
	}
	Curler::_counter++;
}

Curler::~Curler()
{
	if(_pCurl) {
		curl_easy_cleanup(_pCurl);
		_pCurl = NULL;
	}
	std::lock_guard<std::mutex> lock(_counter_mtx);
	Curler::_counter--;
	if(Curler::_counter < 1) {
		curl_global_cleanup();
	}
}

Curler::Curler(AbsConfig::ShPtr pConfig) :
	_pConfig(pConfig)
{
}
	
std::string
Curler::xlateCode2str(CURLcode code) 
{
	return std::string(curl_easy_strerror(code));
}

CurlerRval::ShPtr
Curler::send(char *p, int len, Utils::StringVector& pExtraHeaders)
{
	curl_slist *pHeaders = NULL;
	CurlBodyHolder::ShPtr spBody;
	CurlHeaderHolder::ShPtr spHeader;
	CurlerRval::ShPtr pRval(new CurlerRval);
	Utils::KeyValue headers = _pConfig->getRequestHeaders();

	pRval->_pBody = spBody;
	pRval->_pHeader = spHeader;

	curl_easy_setopt(_pCurl, CURLOPT_URL, 
		_pConfig->getApiUrl().c_str());
	curl_easy_setopt(_pCurl, CURLOPT_CUSTOMREQUEST,
		_pConfig->getHttpVerb().c_str());

	pHeaders = curl_slist_append(pHeaders, "Connection: keep-alive");
	pHeaders = curl_slist_append(pHeaders, "User-Agent: Kafka-Notifier-0.1.0");
	pHeaders = curl_slist_append(pHeaders, "Accept:"); // Disable header
	pHeaders = curl_slist_append(pHeaders,
		_pConfig->getContentType().c_str());

	Utils::KeyValue::iterator itor_config = headers.begin();
	while(itor_config != headers.end()) {
		std::stringstream oss;
		oss << itor_config->first << ": " << itor_config->second;
		pHeaders = curl_slist_append(pHeaders, oss.str().c_str());
		itor_config++;
	}
	Utils::StringVector::iterator itor_extra = pExtraHeaders.begin();
	while(itor_extra != pExtraHeaders.end()) {
		pHeaders = curl_slist_append(pHeaders, itor_extra->c_str());
		itor_extra++;
	}
	
	curl_easy_setopt(_pCurl, CURLOPT_WRITEFUNCTION, callback_body_writer);
	curl_easy_setopt(_pCurl, CURLOPT_WRITEDATA, (void*)spBody.get());
	curl_easy_setopt(_pCurl, CURLOPT_HEADERFUNCTION, callback_header_writer);
	curl_easy_setopt(_pCurl, CURLOPT_HEADERDATA, (void*)spHeader.get());

	curl_easy_setopt(_pCurl, CURLOPT_NOSIGNAL, 1L);
	curl_easy_setopt(_pCurl, CURLOPT_NOPROGRESS, 1L);
	curl_easy_setopt(_pCurl, CURLOPT_VERBOSE, 0L);
	
	curl_easy_setopt(_pCurl, CURLOPT_FOLLOWLOCATION, 0L);
	curl_easy_setopt(_pCurl, CURLOPT_MAXREDIRS, 0L);

	curl_easy_setopt(_pCurl, CURLOPT_HTTPHEADER, pHeaders);
	curl_easy_setopt(_pCurl, CURLOPT_POSTFIELDSIZE, len);
	curl_easy_setopt(_pCurl, CURLOPT_COPYPOSTFIELDS, p);

	pRval->_result = curl_easy_perform(_pCurl);

	curl_slist_free_all(pHeaders);

	return pRval;
}

