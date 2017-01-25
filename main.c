#include <libguile.h>
#include <gtk/gtk.h>
#include <webkit2/webkit2.h>

#include "core.h"
#include "view.h"

const char* browser_name = "luna";
const char* gtk_identifier = "com.github.rlupton20.luna";

static void activate(GtkApplication* application, gpointer user_data);

// Temporarily global
GtkWidget* window;

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
  window = gtk_application_window_new(application);
  gtk_window_set_title(GTK_WINDOW(window), browser_name);
  gtk_window_set_default_size(GTK_WINDOW(window), 200, 200);

  scm_init_guile();
  init_luna_view_type();
  register_window_context(window);
  scm_c_primitive_load("luna.scm");

  luna_view* view = (luna_view*) SCM_SMOB_DATA(scm_c_eval_string("view"));
  gtk_widget_show_all(window);
}
