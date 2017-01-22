#include <gtk/gtk.h>
#include <webkit2/webkit2.h>

const char* browser_name = "luna";
const char* gtk_identifier = "com.github.rlupton20.luna";

static void activate(GtkApplication* application, gpointer user_data);

int main(int argc, char **argv) {
  GtkApplication* application;
  int status;

  application = gtk_application_new(gtk_identifier, G_APPLICATION_FLAGS_NONE);
  g_signal_connect(application, "activate", G_CALLBACK(activate), NULL);
  status =  g_application_run(G_APPLICATION(application), argc, argv);
  g_object_unref(application);
  
  return status;
}


static void activate(GtkApplication* application, gpointer user_data) {
  GtkWidget* window = gtk_application_window_new(application);
  gtk_window_set_title(GTK_WINDOW(window), browser_name);
  gtk_window_set_default_size(GTK_WINDOW(window), 200, 200);

  WebKitWebView * view = WEBKIT_WEB_VIEW(webkit_web_view_new());
  gtk_container_add(GTK_CONTAINER(window), GTK_WIDGET(view));
  
  /* Load an example web page */
  webkit_web_view_load_uri(view, "http://www.google.com/");
  
  gtk_widget_show_all(window);
}

