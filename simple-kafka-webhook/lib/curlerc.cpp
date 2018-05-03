
#include <sstream>
#include "curler.hpp"

#ifdef __cplusplus
extern "C" { // C callbacks for libcurl
#endif

size_t
callback_header_writer(char* pbuffer, size_t size, size_t nitems, void* puserdata)
{
        size_t actualsize = size * nitems; 
        CurlHeaderHolder *h = (CurlHeaderHolder*)puserdata;
        h->addHeader(pbuffer, actualsize);
        return actualsize;
}

size_t
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

