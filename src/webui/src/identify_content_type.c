/*
 * identify_content_type.cpp
 *
 *  Created on: 03 feb 2017
 *      Author: nop
 */


#include <string.h>
#include <dowse.h>

/**
 * @file identify_content_type.c
 * @author Nicola Rossi <nicola@dyne.org>
 * @date Stardate -305623.39963850833
 * @brief This file contains the functions related to identify the type from the filename.
 *
 * This function use the suffix of the filename to return the content-type to set in the http_response
 *
 */

int ends_with(const char* suffix,const char* ending) {
    if (strlen(suffix) >= strlen(ending)) {
        return (strstr(
                suffix+(strlen(suffix)- strlen(ending)), ending)!=NULL);
    } else {
        return 0;
    }
}

const char*identify_content_type(const char*filename,char*buff,int len){
    if (ends_with(filename,".html")) {
        return "text/html";
    }
    if (ends_with(filename,".css")) {
        return "text/css";
    }
    if (ends_with(filename,".js")) {
        return "application/javascript; charset=utf-8";
    }
    if (ends_with(filename,".png")) {
        return "image/png";
    }
    if (ends_with(filename,".jpg")) {
        return "image/jpg";
    }
    if (ends_with(filename,".jpeg")) {
        return "image/jpeg";
    }

    if (ends_with(filename,".eot")) {
        return "application/octet-stream";
    }
    if (ends_with(filename,".svg")) {
        return "image/svg+xml";
    }

    if (ends_with(filename,".ttf")) {
        return "application/x-font-ttf";
    }

    if (ends_with(filename,".woff")) {
        return "application/font-woff";
    }

    if (ends_with(filename,".woff2")) {
        return "application/octet-stream";
    }

    if (ends_with(filename,".ico")) {
        return "image/x-icon";
    }


    /* TODO implementare mimetype -b nomefile ??? */
    warn("Richiesto di identificare un tipo sconosciuto [%s]",filename);
    return "text/html";
}
