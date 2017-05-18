
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


/**
 * @file captive_portal_admin.c
 * @author Nicola Rossi <nicola@dyne.org>
 * @date Stardate -305623.39963850833
 * @brief This function serve the captive_portal_admin page request.
 *
 *
 * In this function will be rendered the captive_portal_admin page request, providing:
 *  - aggregate state of all things in the Dowse network or rather all things are on or off
 *  - event grouped by mac address and typology
 *  - Temporarily, changing the redirection to captive_portal_admin disabling it, until the next event will be triggered.
 *
 */

int captive_portal_admin(struct http_request * req) {
    log_entering();
    template_t tmpl;
    attributes_set_t attr;
    u_int8_t *html_rendered;
    struct kore_buf *out;
    size_t len;
    out = kore_buf_alloc(0);
	attr=attrinit();

    /* aggregate state of all things */
    sprintf(line,"select value as cur_state from parameter where variable='state all things'");
    sql_select_into_attributes(line,NULL,&attr);

    load_current_identity(req,&attr);

    /* event grouped by mac address and tipology */
    sql_select_into_attributes(
            "SELECT count(id) as how_much, min(age) as first_age,max(age) as last_age,E.* "
            "FROM event E WHERE recognized=0 "
            "GROUP BY macaddr,description ",
            "captive_portal_event",
            &attr);

    /* Change the redirection to captive_portal_admin disabling it, until the next event will be triggered. */
    sql_execute("CALL redirect_admin_to_captive_portal('admin');",&attr);

    /* Render the page */
    template_load("assets/captive_portal_admin.html",&tmpl);
    template_apply(&tmpl,attr,out);

	/* Free resource */
    html_rendered = kore_buf_release(out, &len);
    http_response(req, 200, html_rendered, len);

    /**/
    kore_free(html_rendered);
	attrfree(attr);

    return (KORE_RESULT_OK);
}
