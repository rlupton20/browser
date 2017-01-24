#include <libguile.h>
#include <gtk/gtk.h>
#include <webkit2/webkit2.h>

#include "context.h"
#include "view.h"

const char* browser_name = "luna";
const char* gtk_identifier = "com.github.rlupton20.luna";

static void inner_main(void* closure, int argc, char** argv);
static void activate(GtkApplication* application, gpointer user_data);

// Temporarily global
static GtkWidget* window;

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


  scm_boot_guile(0, 0, inner_main, 0);
  
  WebKitWebView * view = WEBKIT_WEB_VIEW(webkit_web_view_new());
  gtk_container_add(GTK_CONTAINER(window), GTK_WIDGET(view));
  
  /* Load an example web page */
  webkit_web_view_load_uri(view, "http://www.google.com/");

  gtk_widget_show_all(window);
}


static void inner_main(void* closure, int argc, char** argv)
{
  init_luna_view_type();
  register_window_context(window);
  scm_c_primitive_load("luna.scm");
  scm_shell(argc, argv);
}
