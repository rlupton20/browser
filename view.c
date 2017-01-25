/* view.c */

#include <libguile.h>
#include <gtk/gtk.h>
#include <webkit2/webkit2.h>
#include <stdlib.h>

#include "view.h"
#include "core.h"

static const char* type_name = "luna_view";
static scm_t_bits luna_view_tag;

static SCM make_luna_view(void);
static size_t free_luna_view(SCM luna_view_smob);
static int print_luna_view(SCM luna_view_smob,
			   SCM port,
			   scm_print_state *pstate);

static SCM load_uri(SCM view, SCM uri);
static SCM focus_view(SCM context, SCM view);
static SCM go_back_p(SCM view);
static SCM go_back(SCM view);


static SCM make_luna_view(void)
{
  SCM smob;
  LunaView *l_view;

  l_view = (LunaView *) scm_gc_malloc(sizeof(LunaView), type_name);
  WebKitWebView * view = WEBKIT_WEB_VIEW(webkit_web_view_new());

  l_view->view = view;
  smob = scm_new_smob(luna_view_tag, l_view);

  return smob;
}


static size_t free_luna_view(SCM luna_view_smob)
{
  LunaView* view = (LunaView *) SCM_SMOB_DATA(luna_view_smob);
  free(view->view);
  scm_gc_free(view, sizeof(LunaView), type_name);
  return 0;
}


static int print_luna_view(SCM luna_view_smob,
			   SCM port,
			   scm_print_state *pstate)
{
  scm_puts("<#luna_view>", port);
  return 1;
}


WebKitWebView* get_view(SCM luna_view_smob)
{
  LunaView * view;
  scm_assert_smob_type(luna_view_tag, luna_view_smob);
  view = (LunaView *) SCM_SMOB_DATA(luna_view_smob);
  return view->view;
}
  

static SCM load_uri(SCM view, SCM uri)
{
  char* c_uri;
  scm_assert_smob_type(luna_view_tag, view);
  
  c_uri = scm_to_locale_string(uri);
  webkit_web_view_load_uri(get_view(view), c_uri);

  free(c_uri);
  return uri;
}


static SCM focus_view(SCM context, SCM view)
{
  GtkWidget* window = get_window(context);
  scm_assert_smob_type(luna_view_tag, view);
  gtk_container_add(GTK_CONTAINER(window), GTK_WIDGET(get_view(view)));
  return view;
}

static SCM go_back_p(SCM view)
{
  int res;
  scm_assert_smob_type(luna_view_tag, view);
  res = webkit_web_view_can_go_back(get_view(view));
  return scm_from_bool(res);
}


static SCM go_back(SCM view)
{
  scm_assert_smob_type(luna_view_tag, view);
  webkit_web_view_go_back(get_view(view));
  return view;
}


void init_luna_view_type(void)
{
  luna_view_tag = scm_make_smob_type(type_name, sizeof(LunaView));
  scm_set_smob_free(luna_view_tag, free_luna_view);
  scm_set_smob_print(luna_view_tag, print_luna_view);

  scm_c_define_gsubr("new-view", 0, 0, 0, make_luna_view);
  scm_c_define_gsubr("load-uri", 2, 0, 0, load_uri);
  scm_c_define_gsubr("focus-view", 2, 0, 0, focus_view);
  scm_c_define_gsubr("back-page-p", 1, 0, 0, go_back_p);
  scm_c_define_gsubr("back-page", 1, 0, 0, go_back);
}
