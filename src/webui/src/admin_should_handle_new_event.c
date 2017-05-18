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



/**
 * @file admin_should_handle_new_event.c
 * @author Nicola Rossi <nicola@dyne.org>
 * @date Stardate -305623.39963850833
 * @brief This file contain the function related to admin captive portal redirect .
 *
 */

#include <webui.h>



/**
 * @brief Function to evaluate if administrator should handle Dowse event
 *
 * Function to evaluate if administrator should handle Dowse event.
 * It checks on Redis DB if is present the key authorization-mac-<CONNECTING-MAC-ADDRESS>
 * and return 1 it's value is equal to the constant __R_ADMIN_SHOULD_CHECK = "admin_should_check"
 *
 */

int admin_should_handle_new_event(char*macaddr) {
    char key[256];
    char value[256];
    sprintf(key,"authorization-mac-%s",to_upper(macaddr));
    redis_get_key(key,value,sizeof(value));

    return (strcmp(value,__R_ADMIN_SHOULD_CHECK)==0);

}

/**
 *  @brief Function to get on Redis the value of a key
 *
 *   This function hidden some "boilerplate" code
 *
 * */
int redis_get_key(const char* key, char*value, int sizeof_value) {
    redisContext *redis = NULL;
    redisReply *reply = NULL;
    /* Connecting with Redis */
    redis = connect_redis(REDIS_HOST, REDIS_PORT, db_dynamic);
    if (!redis) {
        const char m[] = "Redis server is not running";
        err(m);
        return KORE_RESULT_ERROR;
    }

    /* Print command on redis channel */
    reply = cmd_redis(redis, "GET %s", key);
    if (reply->len) {
        snprintf(value, sizeof_value, reply->str);
    } else {
        value[0] = 0;
    }
    /* Free resources */
    if (reply)
        freeReplyObject(reply);
    if (redis)
        redisFree(redis);
    return KORE_RESULT_OK;

}

/**
 * @brief This function check if there are event that the admin should recognize.
 *
 * This function is used in the management of dowse-events.
 * It's different by admin_should_handle_new_event because it check on the DB,
 *  if there are event to recognize or not.
 *
 * eg: an event is triggered in the dowse ecosystem,
 *   then the admin should be redirected on the dowse captive_portal_admin page.
 *   the admin evaluate him navigation more important that the recognition of the event so leaves it in stand-by .
 *   The admin_should_handle_new_event will return "0" but "there_are_event_not_recognized" should return "1"
 *
 */
int there_are_event_not_recognized() {
    char sql[] =
            "SELECT * FROM event WHERE not recognized and description='new_mac_address'";
    attributes_set_t dummy_attribute;
    dummy_attribute=attrinit();
    int rv = sql_select_into_attributes(sql, "dummy", &dummy_attribute);
    attrfree(dummy_attribute);
    func(" admin_should_handle_new_event = %d", rv);
    if (rv > 0) {
        return 1;
    } else {
        return 0;
    }
}


