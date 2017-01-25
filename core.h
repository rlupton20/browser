#ifndef _LUNA_CORE_H
#define _LUNA_CORE_H

#include <gtk/gtk.h>

typedef struct _luna_core {
  GtkWidget* window;
} luna_core;

SCM register_window_context(GtkWidget* window);

GtkWidget* get_window(SCM core_smob);

#endif
