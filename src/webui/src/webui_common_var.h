/*
 * webui_common_var.h
 *
 *  Created on: 15 nov 2016
 *      Author: nop
 */

#ifndef __WEBUI_MAIN_FILE__
#define __WEBUI_EXTERN__ extern
#else
#define __WEBUI_EXTERN__
#endif

#ifndef WEBUI_COMMON_VAR_H_
#define WEBUI_COMMON_VAR_H_


// used with kore_buf_(create/appendf/free)

__WEBUI_EXTERN__ char line[ml];
__WEBUI_EXTERN__ char where_condition[ml];
__WEBUI_EXTERN__ struct template_t tmpl;
//__WEBUI_EXTERN__  attributes_set_t global_attributes;
__WEBUI_EXTERN__  attributes_set_t startup_attributes;
__WEBUI_EXTERN__  int error_during_startup;
__WEBUI_EXTERN__ struct identity_t{
        char ipaddr_type[32];
        char ipaddr_value[64];
        char macaddr[32];
} identity;


typedef struct performance_context{
   #define SIZE_OF_TIME_STACK (32)
   int perf_stack;
   struct timeval time_stack[SIZE_OF_TIME_STACK];
   const char *file_stack[SIZE_OF_TIME_STACK];
   const char *function_stack[SIZE_OF_TIME_STACK];
   int row_stack[SIZE_OF_TIME_STACK];

} performance_context;

__WEBUI_EXTERN__ performance_context perf_cont;
__WEBUI_EXTERN__ map_t assetmap;

/* To wrote global_messages we wrote on global_attributes set
 * __WEBUI_EXTERN__ attributes_set_t global_messages;
 * */

#endif /* WEBUI_COMMON_VAR_H_ */
