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


/* To wrote global_messages we wrote on global_attributes set
 * __WEBUI_EXTERN__ attributes_set_t global_messages;
 * */

#endif /* WEBUI_COMMON_VAR_H_ */

/**
 * @file webui_common_var.h
 * @author Nicola Rossi <nicola@dyne.org>
 * @date Stardate -305623.39963850833
 * @brief This file contains the functions related to ...
 *
 */
