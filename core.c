/* core.c */

#include <libguile.h>
#include <gtk/gtk.h>
#include <webkit2/webkit2.h>
#include <stdlib.h>

#include "core.h"

const char* browser_name = "luna";

static const char* type_name = "luna_core";
static scm_t_bits luna_core_tag;

static print_core(SCM luna_core_smob,
		  SCM port,
		  scm_print_state *pstate);


static GtkWidget* create_browser_window(GtkApplication* application);


SCM create_core(GtkApplication* application)
{
  SCM smob;
  LunaCore* lc;

  luna_core_tag = scm_make_smob_type(type_name, sizeof(LunaCore));
  
  if ( (lc = calloc(1, sizeof(LunaCore))) == NULL )
    exit(1);
  else {
    lc->window = create_browser_window(application);
    lc->current_focused = lc->window;
  
    smob = scm_new_smob(luna_core_tag, lc);
    scm_set_smob_print(luna_core_tag, print_core);
    scm_c_define("core", smob);

    return smob;
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
  LunaCore* lc;
  scm_assert_smob_type(luna_core_tag, core_smob);
  lc = (LunaCore *) SCM_SMOB_DATA(core_smob);
  return lc->window;
}


static GtkWidget* create_browser_window(GtkApplication* application)
{
  GtkWidget* window;

  if ( (window = gtk_application_window_new(application)) == NULL )
    exit(1);
  else {
    gtk_window_set_title(GTK_WINDOW(window), browser_name);
    gtk_window_set_default_size(GTK_WINDOW(window), 200, 200);
    return window;
  }
}
