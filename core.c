/* core.c */

#include <libguile.h>
#include <gtk/gtk.h>
#include <webkit2/webkit2.h>
#include <stdlib.h>

#include "core.h"

static const char* type_name = "luna_core";
static scm_t_bits luna_core_tag;

static print_core(SCM luna_core_smob,
		     SCM port,
		     scm_print_state *pstate);


SCM register_window_context(GtkWidget* window)
{
  SCM smob;
  luna_core* lc;

  luna_core_tag = scm_make_smob_type(type_name, sizeof(luna_core));
  
  if ( lc = calloc(1, sizeof(luna_core)) ) {
    lc->window = window;
    smob = scm_new_smob(luna_core_tag, lc);
    scm_set_smob_print(luna_core_tag, print_core);
    scm_c_define("core", smob);
    return smob;
  }
  else {
    exit(1);
  }
}


static print_core(SCM luna_core_smob,
		  SCM port,
		  scm_print_state *pstate)
{
  scm_puts("<#core>", port);
  return 1;
}


GtkWidget* get_window(SCM core_smob)
{
  luna_core* lc;
  scm_assert_smob_type(luna_core_tag, core_smob);
  lc = (luna_core *) SCM_SMOB_DATA(core_smob);
  return lc->window;
}
