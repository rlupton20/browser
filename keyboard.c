/* keyboard.c */

#include <libguile.h>
#include <gtk/gtk.h>
#include <gdk/gdkkeysyms.h>
#include <stdio.h>

#include "keyboard.h"


gboolean keypress_correlator(GtkWidget *widget,
			     GdkEventKey *event,
			     gpointer user_data)
{
  SCM pass_through_scm;
  static const char dispatch[1024];
  if (event->type == GDK_KEY_PRESS) {
    sprintf(dispatch, "(dispatch-keypress \"%s\")",
	    gdk_keyval_name(event->keyval));
    pass_through_scm = scm_c_eval_string(dispatch);
  }
  return 0;
}

