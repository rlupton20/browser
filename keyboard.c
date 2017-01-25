/* keyboard.c */

#include <libguile.h>
#include <gtk/gtk.h>
#include <gdk/gdkkeysyms.h>

#include "keyboard.h"

gboolean keypress_correlator(GtkWidget *widget,
			     GdkEventKey *event,
			     gpointer user_data)
{
  if (event->type == GDK_KEY_PRESS && event->keyval == GDK_KEY_H) {
    scm_c_eval_string("(back-page view)");
    return 1;
  }
  else
    return 0;
}
