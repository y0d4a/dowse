/*
 * test_admin.c
 *
 *  Created on: 15 nov 2016
 *      Author: Nicola 
 */

#include <webui.h>

int test_admin(struct http_request * req) {
    log_entering();
    char message[256];

    sprintf(message,"Hello this is the Admin's page");
    http_response(req, 200, message, strlen(message));


    return (KORE_RESULT_OK);
}

/**
 * @file test_admin.c
 * @author Nicola Rossi <nicola@dyne.org>
 * @date Stardate -305623.39963850833
 * @brief This file contains the functions related to ...
 *
 */
