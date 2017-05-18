
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

int load_global_attributes(attributes_set_t attr) {
    log_entering();
    int rv ;

    WEBUI_DEBUG
    /**/
    func("load admin device into global attributes");
    rv = sql_select_into_attributes( "SELECT (CASE WHEN upper('%s') = upper(macaddr) THEN 'yes'"
            "                   ELSE 'no' END ) as self, (@seq := @seq +1) AS seq_number,"
            "upper(macaddr) as macaddr,F.* "
            " FROM found F "
            " JOIN ( SELECT @seq := 0 ) r "
            " WHERE admin='yes'",
            "admin_device",
            &attr);


    return (rv>=0);
}

/**
 * @file load_global_attributes.c
 * @author Nicola Rossi <nicola@dyne.org>
 * @date Stardate -305623.39963850833
 * @brief This file contains the functions related to ...
 *
 */
