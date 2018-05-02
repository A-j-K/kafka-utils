#pragma once

#ifdef __cplusplus
extern "C" { // C callbacks for libcurl
#endif

size_t
callback_header_writer(char* pbuffer, size_t size, size_t nitems, void* puserdata);

size_t
callback_body_writer(char* pbuffer, size_t size, size_t nitems, void* puserdata);

#ifdef __cplusplus          
}                           
#endif                     

