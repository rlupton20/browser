/* view.c */

#include <libguile.h>
#include <gtk/gtk.h>
#include <webkit2/webkit2.h>
#include <stdlib.h>

#include "view.h"

static const char* type_name = "luna_view";
static scm_t_bits luna_view_tag;

static SCM make_luna_view(void);
static size_t free_luna_view(SCM luna_view_smob);
static int print_luna_view(SCM luna_view_smob,
			   SCM port,
			   scm_print_state *pstate);

static SCM make_luna_view(void)
{
  SCM smob;
  luna_view *l_view;

  l_view = (luna_view *) scm_gc_malloc(sizeof(luna_view), type_name);
  WebKitWebView * view = WEBKIT_WEB_VIEW(webkit_web_view_new());

  l_view->view = view;
  smob = scm_new_smob(luna_view_tag, l_view);

  return smob;
}


static size_t free_luna_view(SCM luna_view_smob)
{
  luna_view* view = (luna_view *) SCM_SMOB_DATA(luna_view_smob);
  free(view->view);
  scm_gc_free(view, sizeof(luna_view), type_name);
  return 0;
}


static int print_luna_view(SCM luna_view_smob,
			   SCM port,
			   scm_print_state *pstate)
{
  scm_puts("<#luna_view>", port);
  return 1;
}


void init_luna_view_type(void)
{
  luna_view_tag = scm_make_smob_type(type_name, sizeof(luna_view));
  scm_set_smob_free(luna_view_tag, free_luna_view);
  scm_set_smob_print(luna_view_tag, print_luna_view);

  scm_c_define_gsubr("new-view", 0, 0, 0, make_luna_view);
}


WebKitWebView* get_view(SCM luna_view_smob)
{
  luna_view * view;
  scm_assert_smob_type(luna_view_tag, luna_view_smob);
  view = (luna_view *) SCM_SMOB_DATA (luna_view_smob);
  return view->view;
}
  
