/* context.c */

#include <libguile.h>
#include <gtk/gtk.h>
#include <webkit2/webkit2.h>
#include <stdlib.h>

#include "context.h"

static const char* type_name = "luna_context";
static scm_t_bits luna_context_tag;

static print_context(SCM luna_context_smob,
		     SCM port,
		     scm_print_state *pstate);


SCM register_window_context(GtkWidget* window)
{
  SCM smob;
  luna_context* lc;

  luna_context_tag = scm_make_smob_type(type_name, sizeof(luna_context));
  
  if ( lc = calloc(1, sizeof(luna_context)) ) {
    lc->window = window;
    smob = scm_new_smob(luna_context_tag, lc);
    scm_set_smob_print(luna_context_tag, print_context);
    scm_c_define("window", smob);
    return smob;
  }
  else {
    exit(1);
  }
}


static print_context(SCM luna_context_smob,
		     SCM port,
		     scm_print_state *pstate)
{
  scm_puts("<#context>", port);
  return 1;
}


GtkWidget* get_window(SCM context_smob) {
  luna_context* lc;
  scm_assert_smob_type(luna_context_tag, context_smob);
  lc = (luna_context *) SCM_SMOB_DATA(context_smob);
  return lc->window;
}
