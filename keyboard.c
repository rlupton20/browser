/* keyboard.c */

#include <libguile.h>
#include <gtk/gtk.h>
#include <gdk/gdkkeysyms.h>
#include <stdio.h>
#include <assert.h>

#include "keyboard.h"

static const int PASS_ON = 0;

gboolean keypress_correlator(GtkWidget *widget,
			     GdkEventKey *event,
			     gpointer user_data)
{
  SCM pass_through;

  assert(widget != 0);
  assert(event != 0);

  if (event->type == GDK_KEY_PRESS) {
    pass_through = scm_call_2( scm_c_eval_string("dispatch-keypress"),
			       scm_from_int(event->state),
			       scm_from_int(event->keyval) );
    return scm_to_bool(pass_through);
  }
  else {
    return PASS_ON;
  }
}

