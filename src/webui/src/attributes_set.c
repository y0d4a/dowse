#include <kore.h>

#include <attributes_set.h>
#include "webui_debug.h"

#include <libdowse/dowse.h>



/**
 * @file attributes_set.c
 * @author Nicola Rossi <nicola@dyne.org>
 * @date Stardate -305623.39963850833
 * @brief This file contains the functions related to the manipulation of attribute set.
 *
 * This file contains the functions related to the manipulation of attribute set used
 * in rendering of HTML page powered by <a href="http://ctemplate.sourceforge.net/">CTemplate library</a>
 *
 *
 */


/**
 * @brief Initialize attributes_set_t structure
 *
 * Initialize attributes_set_t structure that will be de-initialized using attrfree()
 *
 * */
attributes_set_t attrinit(){  
  attributes_set_t rv=(attributes_set_t) malloc(sizeof(pointed_attributes_set_t));
  rv->loop=NULL;
  rv->varlist=NULL;
  return rv;
}


/**
 * @brief This function store a key-value tuple in the attributes_set_t structure
 *
 * This function store a simple key-value tuple in the attributes_set_t structure.
 *  e.g., a template like
 *  `<p><!--TMPL_VAR name="name_of_author"--></p>`
 *  will be rendered into
 * `<p>Nicola</p>`
 *
 * @param key a string indicating the key in the template i.e., name_of_author
 * @param value a string indicating the value that should be substituted at key in the template i.e., Nicola
 *
 *
 * */
attributes_set_t attrcat(attributes_set_t hm, const char*key,const char* value) {
  hm->varlist=TMPL_add_var(hm->varlist,key,value,0);
  return hm;
}

/**
 * @brief This function store a key-structure tuple in the attributes_set_t structure
 *
 * @param key a string indicating the key in the template i.e., name_of_team_members
 * @param structure the attribute_set_t indicating the key-value map that should be associated with key
 *  in the example may be a structure like:
 *   "name_of_author" : "Nicola"
 *
 *
 * This function store a more structured key-value tuple in the attributes_set_t structure.
 *  e.g., a template like:
 *
 `<&excl;--TMPL_LOOP name="name_of_team_members"-->`

 `<p><&excl;--TMPL_VAR name="name_of_author"></p>`

 `<&excl;--/TMPL_LOOP-->`

 *
 *  will be rendered into:
 *
 * `<p>Parazyd</p>`
 *
 * `<p>Jaromil</p>`
 *
 * `<p>Nicola</p>`
 *
 *
 * */

attributes_set_t attr_add(attributes_set_t hm, const char*key,attributes_set_t value) {
  TMPL_loop *loop;
  loop= TMPL_add_varlist(hm->loop, value->varlist);
  hm->loop=loop;
  hm->varlist=TMPL_add_loop(hm->varlist,key,loop);
  return hm;
}
 

/**
 * @brief This function deallocate the resource associated to the attributes_set_t structure
 *
 * @param the structure to deallocate
 *
 */
void attrfree(attributes_set_t hm) {
    if (!hm) return;
    if (hm->varlist) TMPL_free_varlist(hm->varlist);
//    if (hm->loop) TMPL_free_looplist(hm->loop);
    free(hm);
}


