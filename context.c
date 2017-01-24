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


void register_window_context(GtkWidget* window)
{
  SCM smob;
  luna_context* lc;

  luna_context_tag = scm_make_smob_type(type_name, sizeof(luna_context));
  
  lc = (luna_context *) scm_gc_malloc(sizeof(luna_context), type_name);
  lc->window = window;
  smob = scm_new_smob(luna_context_tag, lc);
  scm_set_smob_print(luna_context_tag, print_context);
  scm_c_define("window", smob);
}


static print_context(SCM luna_context_smob,
		     SCM port,
		     scm_print_state *pstate)
{
  scm_puts("<#context>", port);
  return 1;
}
