
#include <sstream>
#include "curler.hpp"
#include "curlerc.hpp"

Curler::Curler()
{
	curl_global_init(CURL_GLOBAL_ALL);
	_pCurl = curl_easy_init();
}

Curler::~Curler()
{
	if(_pCurl) {
		curl_easy_cleanup(_pCurl);
		_pCurl = NULL;
	}
	curl_global_cleanup();
}

Curler::Curler(AbstractConfig::ShPtr pConfig) :
	_pConfig(pConfig)
{
}
	
void
Curler::startup(void)
{
	curl_global_init(CURL_GLOBAL_ALL);
}

void
Curler::shutdown(void)
{
	curl_global_cleanup();
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

