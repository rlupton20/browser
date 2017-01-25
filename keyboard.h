#ifndef _LUNA_KEYBOARD_H
#define _LUNA_KEYBOARD_H

#include <libguile.h>
#include <gtk/gtk.h>

gboolean keypress_correlator(GtkWidget *widget,
			     GdkEvent *event,
			     gpointer user_data);

#endif
