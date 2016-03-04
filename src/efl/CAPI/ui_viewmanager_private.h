#ifndef UI_VIEWMGR_PRIVATE_H
#define UI_VIEWMGR_PRIVATE_H

#include "../mobile/ui_viewmanager.h"
#include "ui_viewmanager.h"



typedef struct _ui_view_event_callback    ui_view_event_callback;

struct _ui_view_event_callback
{
	ui_view *view;
    const char *event;
    ui_view_event_cb func;
    void *func_data;
    char  delete_me : 1;
};

list<ui_view_event_callback *> callback_list;

#endif /* UI_VIEWMGR_PRIVATE_H */
