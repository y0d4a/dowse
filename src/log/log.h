#ifndef __LOG_H__
#define __LOG_H__

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

// to quickly return 404
#define HTTP404 err("HTTP 404, %s:%u, %s()",	  \
                      __FILE__, __LINE__, __func__);	  \
	http_response(req, 404, NULL, 0); \
	return(KORE_RESULT_OK)

// for use in debugging
#define FLAG func("reached: %s:%u, %s()", __FILE__, __LINE__, __func__)


void func(const char *fmt, ...);

void err(const char *fmt, ...);


#endif