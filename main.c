#include <gtk/gtk.h>

const char* browser_name = "luna";
const char* gtk_identifier = "com.github.rlupton20.luna";

void activate(GtkApplication* application, gpointer user_date);

int main(int argc, char *argv[]) {
  GtkApplication* application;
  int status;

  application = gtk_application_new(gtk_identifier, G_APPLICATION_FLAGS_NONE);
  g_signal_connect(application, "activate", G_CALLBACK(activate), NULL);
  status =  g_application_run(G_APPLICATION(application), argc, argv);
  g_object_unref(application);
  
  return status;
}


void activate(GtkApplication* application, gpointer user_date) {
  GtkWidget* window;

  window = gtk_application_window_new(application);
  gtk_window_set_title(GTK_WINDOW(window), browser_name);
  gtk_window_set_default_size(GTK_WINDOW(window), 200, 200);
  gtk_widget_show_all(window);
}

