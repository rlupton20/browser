#ifndef _LUNA_CONTEXT_H
#define _LUNA_CONTEXT_H

#include <gtk/gtk.h>

typedef struct _luna_context {
  GtkWidget* window;
} luna_context;

SCM register_window_context(GtkWidget* window);

GtkWidget* get_window(SCM context_smob);

#endif
