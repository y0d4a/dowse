
/*  Dowse - embedded WebUI based on Kore.io
 *
 *  (c) Copyright 2016 Dyne.org foundation, Amsterdam
 *  Written by Nicola Rossi <nicola@dyne.org>
 *
 * This source code is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Public License as published
 * by the Free Software Foundation; either version 3 of the License,
 * or (at your option) any later version.
 *
 * This source code is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * Please refer to the GNU Public License for more details.
 *
 * You should have received a copy of the GNU Public License along with
 * this source code; if not, write to:
 * Free Software Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 *
 */

#include <webui.h>
#include <signal.h>



/**
 * @file change_authorization_to_browse.c
 * @author Nicola Rossi <nicola@dyne.org>
 * @date Stardate -305623.39963850833
 * @brief This file contains the functions related to changing the authorization to browse.
 *
 * In the Dowse network a things may be:
 *  - authorized to browse
 *  - denied to browse
 *  - not yet authorized or denied
 *
 */


int received_ack_or_timeout =0;


char key_name[256];
typedef void (*sighandler_t)(int);

void  timeout_handler(int sig)
{
 redisReply   *reply = NULL;

 redisContext *redis = NULL;
  signal(SIGALRM, SIG_IGN);
  /* Connecting with Redis */
  redis = connect_redis(REDIS_HOST, REDIS_PORT, db_dynamic);
  reply = cmd_redis(redis,"DEL ACK_%s",key_name);

  notice("timeout expired about request %s ",key_name);
  if(reply) freeReplyObject(reply);

}

/**/
/* This function send to pendulum the command to change the authorization level on the Dowse eco-system.
 *
 * To succeed on it, it is used an REQUEST + ACK protocol structured in this way:
 *
 *  - the WebUI  set on Redis the ACK request related to the command that we are going to send
 *    -  and the EXPIRE time
 *  - publish on the command fifo the command request
 *  - set the timeout handler to delete the ack request on redis if not solved on timeout.
 *  - wait the accomplish of the task or the
 *
 * */
int change_authorization_to_browse(struct http_request * req,char*macaddr,const char*ip4,const char*ip6,redisContext *redis ,char *action){
    char command[256];
    redisReply   *reply = NULL;

    char epoch[256];
    /* Calculating calling IP extracting from request */
    char *ipaddr_type,*calling_ipaddr;
    get_ip_from_request(req,&ipaddr_type,&calling_ipaddr);

    WEBUI_DEBUG;

    /* calculating Epoch time*/
    struct timeval tp;
    struct timezone tz;
    gettimeofday(&tp,&tz);

    /* timeout */
    int timeout_sec = 5;

    snprintf(epoch,sizeof(epoch),"%lu",tp.tv_sec);    WEBUI_DEBUG;

    /* Construct command to publish on Redis channel */
    snprintf(command,sizeof(command),"CMD,%s,%s,%s,%s,%s,%s",calling_ipaddr,action,epoch,to_upper(macaddr),(ip4?ip4:""),(ip6?ip6:""));    WEBUI_DEBUG;

    /* We prepare the ack request */
    snprintf(key_name,sizeof(key_name),"ACK_%s_%s",action,epoch);    WEBUI_DEBUG;

    /* the WebUI  set on Redis the ACK request related to the command that we are going to send */
    reply = cmd_redis(redis,"SET %s ACK_REQUESTED",key_name);
    if(reply) freeReplyObject(reply);

    WEBUI_DEBUG;

    /* the WebUI  set on Redis the  expire time for the request */
    reply = cmd_redis(redis,"EXPIRE  %s %d",key_name,2*timeout_sec);
    if(reply) freeReplyObject(reply);

    /* Publish the command on redis channel */
    reply = cmd_redis(redis,"PUBLISH %s %s", CHAN,command,calling_ipaddr);
    if(reply) freeReplyObject(reply);

    /* set the timeout handler to delete the ack request */
    sighandler_t old_signal_handler;
    old_signal_handler=signal(SIGALRM, timeout_handler);

    /* we wait the ACK of the command */
    alarm(timeout_sec);

    int to_exit=0;
    while (!to_exit) {
        reply = cmd_redis(redis,"GET %s ", key_name);
        if (reply) {
            if (reply->type == REDIS_REPLY_STRING ) {
                notice("...waiting accomplish of task %s of %s",action,epoch);
            } else {
                to_exit=1;
            }
            freeReplyObject(reply);
        }
        sleep(1);
    };
    signal(SIGALRM, old_signal_handler);
    if ((old_signal_handler!=SIG_IGN)
        && (old_signal_handler!=SIG_DFL)
        && (old_signal_handler!=SIG_ERR)
    ){
        alarm(1);
    }
    WEBUI_DEBUG;

    return KORE_RESULT_OK;
}
