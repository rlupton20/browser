#ifndef _LUNA_CORE_H
#define _LUNA_CORE_H

#include <gtk/gtk.h>

typedef struct _luna_core {
  GtkWidget* window;
} LunaCore;

SCM create_core(GtkApplication* application);

GtkWidget* get_window(SCM core_smob);

#endif
