#include "ui_viewmgr_private.h"
#include "ui_view.h"

EAPI ui_view *
ui_view_add(Evas_Object *content)
{
   ui_view *view = calloc(1, sizeof(ui_view));
   if(!view)
      return NULL;

   view->content = content;
   view->style = eina_stringshare_add("default");
   view->current_state = VIEW_ABOUT_TO_SHOW;
   view->previous_state = VIEW_ABOUT_TO_SHOW;
   return view;
}

EAPI void
ui_view_del(ui_view *view)
{
   VIEW_CHECK(view);
   ui_view_event_callback *cb;

   if(view->content)
      evas_object_del(view->content);

   EINA_LIST_FREE(view->callbacks,cb) {
      eina_stringshare_del(cb->event);
      free(cb);
   }

   eina_stringshare_del(view->style);

   free(view);
}

EAPI Eina_Bool
ui_view_content_set(ui_view *view, Evas_Object *content)
{
   VIEW_CHECK(view) EINA_FALSE;
   // if same content
   if(view->content == content)
      return EINA_TRUE;

   // if already content exists delete it
   if(view->content)
      evas_object_del(view->content);

   // update the new content
   view->content = content;

   return EINA_TRUE;
}

EAPI Evas_Object *
ui_view_content_unset(ui_view *view)
{
   Evas_Object *content;

   VIEW_CHECK(view) NULL;
   content = view->content;
   view->content = NULL;

   return content;
}

EAPI Evas_Object *
ui_view_content_get(ui_view *view)
{
   VIEW_CHECK(view) NULL;
   return view->content;
}

EAPI void
ui_view_style_set(ui_view* view, const char *style)
{
   VIEW_CHECK(view);
   eina_stringshare_replace(&view->style,style);
}

EAPI const char *
ui_view_style_get(ui_view* view)
{
   VIEW_CHECK(view) "";
   return view->style;
}

EAPI void
ui_view_event_callback_add(ui_view *view, const char *event, ui_view_event_cb func, const void *data)
{
   ui_view_event_callback *cb;
   VIEW_CHECK(view);
   if (!event) return;
   if (!func) return;
   cb = calloc(1,sizeof(ui_view_event_callback));
   cb->event = eina_stringshare_add(event);
   cb->func = func;
   cb->func_data = (void *)data;
   view->callbacks = eina_list_append(view->callbacks,cb);
}

EAPI void *
ui_view_event_callback_del(ui_view *view, const char *event, ui_view_event_cb func)
{
   Eina_List *l;
   ui_view_event_callback *cb;

   VIEW_CHECK(view) NULL;
   if (!event) return NULL;
   if (!func) return NULL;

   EINA_LIST_FOREACH(view->callbacks, l, cb) {
      if ((!strcmp(cb->event, event)) && (cb->func == func)) {
         void *data;

         data = cb->func_data;
         cb->delete_me = 1;
         return data;
      }
   }
   return NULL;
}
