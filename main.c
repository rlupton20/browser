#include <libguile.h>
#include <gtk/gtk.h>
#include <webkit2/webkit2.h>

#include "core.h"
#include "view.h"

const char* gtk_identifier = "com.github.rlupton20.luna";

static void activate(GtkApplication* application, gpointer user_data);

int main(int argc, char **argv)
{
  GtkApplication* application;
  int status;

  application = gtk_application_new(gtk_identifier, G_APPLICATION_FLAGS_NONE);
  g_signal_connect(application, "activate", G_CALLBACK(activate), NULL);
  status =  g_application_run(G_APPLICATION(application), argc, argv);
  g_object_unref(application);
  
  return status;
}


static void activate(GtkApplication* application, gpointer user_data)
{
  SCM core_smob;
  
  scm_init_guile();

  core_smob = create_core(application);
  init_luna_view_type();
  
  scm_c_primitive_load("luna.scm");

  gtk_widget_show_all(get_window(core_smob));
}
