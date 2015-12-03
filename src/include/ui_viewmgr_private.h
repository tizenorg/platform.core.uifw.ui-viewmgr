#ifndef _UI_VIEWMGR_PRIVATE_H
#define _UI_VIEWMGR_PRIVATE_H

#include <Elementary.h>
#include <dlog.h>
#include "ui_view.h"
#include "ui_viewmgr.h"

#define LOG_TAG "ui-viewmgr"


typedef struct _ui_view_event_callback    ui_view_event_callback;


static const char SIG_VIEW_LOAD[] = "view,load";
static const char SIG_VIEW_UNLOAD[] = "view,unload";
static const char SIG_VIEW_APPEAR_START[] = "view,appear,start";
static const char SIG_VIEW_APPEAR_FINISH[] = "view,appear,finish";
static const char SIG_VIEW_DISAPPEAR_START[] = "view,disappear,start";
static const char SIG_VIEW_DISAPPEAR_FINISH[] = "view,disappear,finish";
static const char SIG_VIEW_KEY_BACK[] = "key,back";
static const char SIG_VIEW_KEY_OPTION[] = "key,option";


struct _ui_view_event_callback
{
   const char *event;
   ui_view_event_cb func;
   void *func_data;
   char  delete_me : 1;
};


#define VIEW_MGR_CHECK(obj)    \
  if (!obj)                    \
    return

struct _ui_viewmgr
{
   Eina_List         *view_stack;
   Evas_Object       *window;
   Evas_Object       *conformant;
   Evas_Object       *base_layout;
   Ecore_Job         *animation_job;
   Evas_Object       *key_grabber;
   struct {
    ui_view* view_this;
    ui_view* view_other;
   }anim;

   Eina_Bool         animation_ongoing : 1;
};

typedef enum _ui_view_state_type
{
   VIEW_SHOWN = 0,
   VIEW_HIDDEN,
   VIEW_ABOUT_TO_DESTROY,
   VIEW_ABOUT_TO_SHOW,
   VIEW_ABOUT_TO_HIDE
} ui_view_state_type;


struct _ui_view
{
   Eina_List           *callbacks;
   Evas_Object         *content;
   const char          *style;

   ui_view_state_type  current_state;
   ui_view_state_type  previous_state;

};


#define VIEW_CHECK(obj)    \
  if (!obj)                \
    return

static inline void
_ui_view_state_set(ui_view *view, ui_view_state_type state)
{
  VIEW_CHECK(view);
  view->previous_state = view->current_state;
  view->current_state = state;
}

static inline ui_view_state_type
_ui_view_state_get(ui_view *view)
{
  VIEW_CHECK(view) VIEW_ABOUT_TO_DESTROY;
  return view->current_state;
}

static inline ui_view_state_type
_ui_view_prev_state_get(ui_view *view)
{
  VIEW_CHECK(view) VIEW_ABOUT_TO_DESTROY;
  return view->previous_state;
}

static inline Eina_Bool
_ui_view_event_callback_call(ui_view *view, const char *event, void *event_info)
{
   Eina_List *l;
   ui_view_event_callback *cb;
   const char *strshare;

   VIEW_CHECK(view) EINA_FALSE;
   if (!event) return EINA_FALSE;

   strshare = eina_stringshare_add(event);
   EINA_LIST_FOREACH(view->callbacks, l, cb) {
      if (!cb->delete_me) {
         if (cb->event == strshare) {
            eina_stringshare_del(strshare);
            return cb->func(cb->func_data, view, event_info);
         }
      }
   }
   eina_stringshare_del(strshare);
   return EINA_FALSE;
}

#endif //_UI_VIEWMGR_PRIVATE_H
