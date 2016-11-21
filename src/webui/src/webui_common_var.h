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
__WEBUI_EXTERN__ struct kore_buf *buf;

__WEBUI_EXTERN__ char line[ml];
__WEBUI_EXTERN__ char where_condition[ml];
__WEBUI_EXTERN__ char *macaddr;
__WEBUI_EXTERN__ template_t tmpl;

#endif /* WEBUI_COMMON_VAR_H_ */