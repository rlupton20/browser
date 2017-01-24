#ifndef _LUNA_VIEW_H
#define _LUNA_VIEW_H

#include <libguile.h>
#include <gtk/gtk.h>
#include <webkit2/webkit2.h>

typedef struct _luna_view {
  WebKitWebView * view;
} luna_view;

void init_luna_view_type(void);

WebKitWebView* get_view(SCM luna_view_smob);

#endif
