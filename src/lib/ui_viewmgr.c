#include "ui_viewmgr.h"
#include "ui_view.h"
#include "ui_viewmgr_private.h"
#include "utilX.h"

//@TODO, Currently the view manager can only show
// two overlay views visible on the screen . to show any number of overlay views 
// simultaneously visible on the screen we need some kind of stack layout.
// elm_grid can be used to simulate a stack layout , but currently it has soem issue 
// which prevents us to use it. So as a future work we need to integrate the elm_grid
// as a stack layout to show any number of overlay views simultaneously visible on the 
// screen.

static Evas_Object *
_create_conformant(Evas_Object *parent)
{
   Evas_Object *conform;

   if (parent == NULL) return NULL;

   conform = elm_conformant_add(parent);
   evas_object_size_hint_weight_set(conform, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
   elm_win_resize_object_add(parent, conform);
   evas_object_show(conform);

   return conform;
}

static Evas_Object *
_create_layout(Evas_Object *parent, const char *style)
{
   Evas_Object *layout;
   char group[100] = {0};

   // create a layout using given style
   layout = elm_layout_add(parent);
   snprintf(group, sizeof(group), "layout/viewmgr/%s", style);
   elm_layout_file_set(layout, "/usr/share/edje/ui-viewmgr/ui-viewmgr.edj", group);
   return layout;
}

static void
_appear_finished_cb(void *data, Evas_Object *obj , const char *emission EINA_UNUSED, const char *source EINA_UNUSED)
{
   ui_viewmgr *view_mgr = data;

   _ui_view_state_set(view_mgr->anim.view_this, VIEW_SHOWN);
   _ui_view_state_set(view_mgr->anim.view_other, VIEW_HIDDEN);

   _ui_view_event_callback_call(view_mgr->anim.view_this, SIG_VIEW_APPEAR_FINISH, "");
   _ui_view_event_callback_call(view_mgr->anim.view_other, SIG_VIEW_DISAPPEAR_FINISH, "");

   elm_object_part_content_set(view_mgr->base_layout, "swallow.back", obj);

   evas_object_freeze_events_set(elm_object_part_content_get(obj, "swallow.view.this"), EINA_FALSE);

   view_mgr->anim.view_this = NULL;
   view_mgr->anim.view_other = NULL;
   view_mgr->animation_ongoing = EINA_FALSE;
}

static void
_disappear_finished_cb(void *data, Evas_Object *obj, const char *emission EINA_UNUSED, const char *source EINA_UNUSED)
{
   ui_viewmgr *view_mgr = data;

   _ui_view_state_set(view_mgr->anim.view_this, VIEW_HIDDEN);
   _ui_view_state_set(view_mgr->anim.view_other, VIEW_SHOWN);

   _ui_view_event_callback_call(view_mgr->anim.view_this, SIG_VIEW_DISAPPEAR_FINISH, "");
   _ui_view_event_callback_call(view_mgr->anim.view_other, SIG_VIEW_APPEAR_FINISH, "");

   elm_object_part_content_set(view_mgr->base_layout, "swallow.back", obj);

   // notify the view deletion
   _ui_view_event_callback_call(view_mgr->anim.view_this,SIG_VIEW_UNLOAD,"");

   evas_object_freeze_events_set(elm_object_part_content_get(obj, "swallow.view.this"), EINA_FALSE);
   evas_object_freeze_events_set(elm_object_part_content_get(obj, "swallow.view.other"), EINA_FALSE);

   //destroy the view
   // remove it from the view stack
   view_mgr->view_stack = eina_list_remove(view_mgr->view_stack, view_mgr->anim.view_this);
   elm_object_part_content_unset(obj,"swallow.view.this");
   ui_view_del(view_mgr->anim.view_this);

   view_mgr->anim.view_this = NULL;
   view_mgr->anim.view_other = NULL;
   view_mgr->animation_ongoing = EINA_FALSE;

}

static void
_delete_layout(Evas_Object* layout)
{
   Evas_Object *content;
   if(layout) {
      content = elm_object_part_content_unset(layout, "swallow.view.this");
      if(content)
         evas_object_hide(content);
      content = elm_object_part_content_unset(layout, "swallow.view.other");
      if(content)
         evas_object_hide(content);
      evas_object_del(layout);
   }
}

static void
_appear_effect(ui_viewmgr* view_mgr)
{
   Evas_Object *layout;
   layout = _create_layout(view_mgr->base_layout, ui_view_style_get(view_mgr->anim.view_this));
   elm_object_part_content_set(view_mgr->base_layout, "swallow.front", layout);
   evas_object_show(layout);

   // setup for view_this 
   if(!ui_view_content_get(view_mgr->anim.view_this) || (_ui_view_prev_state_get(view_mgr->anim.view_this) == VIEW_ABOUT_TO_SHOW)) {
      _ui_view_event_callback_call(view_mgr->anim.view_this,SIG_VIEW_LOAD, "");
   }

   if(ui_view_content_get(view_mgr->anim.view_this)) {
      evas_object_freeze_events_set(ui_view_content_get(view_mgr->anim.view_this), EINA_TRUE);
      elm_object_part_content_set(layout,"swallow.view.this", ui_view_content_get(view_mgr->anim.view_this));
   }
      _ui_view_event_callback_call(view_mgr->anim.view_this, SIG_VIEW_APPEAR_START,"");

   // setup for view_other
   if(view_mgr->anim.view_other) {
      if(ui_view_content_get(view_mgr->anim.view_other)) {
         elm_object_part_content_set(layout, "swallow.view.other", ui_view_content_get(view_mgr->anim.view_other));
         evas_object_freeze_events_set(ui_view_content_get(view_mgr->anim.view_other), EINA_TRUE);
      }
      _ui_view_event_callback_call(view_mgr->anim.view_other, SIG_VIEW_DISAPPEAR_START, "");
   }

   // delete old layout if any
   _delete_layout(elm_object_part_content_get(view_mgr->base_layout, "swallow.back"));

   // start the animation
   elm_object_signal_emit(layout, "appear,effect", "elm");
   elm_object_signal_callback_add(layout, "appear,effect,finished", "*", _appear_finished_cb, view_mgr);
}

static void
_disappear_effect(ui_viewmgr* view_mgr)
{
   Evas_Object *layout;
   layout = _create_layout(view_mgr->base_layout, ui_view_style_get(view_mgr->anim.view_this));
   elm_object_part_content_set(view_mgr->base_layout, "swallow.front", layout);
   evas_object_show(layout);

   // setup for view_this
   elm_object_part_content_set(layout,"swallow.view.this", ui_view_content_get(view_mgr->anim.view_this));
   _ui_view_event_callback_call(view_mgr->anim.view_this, SIG_VIEW_DISAPPEAR_START, "");

   // setup for view_other
   elm_object_part_content_set(layout,"swallow.view.other", ui_view_content_get(view_mgr->anim.view_other));
   if((!ui_view_content_get(view_mgr->anim.view_other)) || (_ui_view_state_get(view_mgr->anim.view_other) == VIEW_ABOUT_TO_SHOW)) {
      _ui_view_event_callback_call(view_mgr->anim.view_other, SIG_VIEW_LOAD, "");
   }
   _ui_view_event_callback_call(view_mgr->anim.view_other, SIG_VIEW_APPEAR_START, "");

   evas_object_freeze_events_set(ui_view_content_get(view_mgr->anim.view_this), EINA_TRUE);
   evas_object_freeze_events_set(ui_view_content_get(view_mgr->anim.view_other), EINA_TRUE);

   // delete old layout if any
   _delete_layout(elm_object_part_content_get(view_mgr->base_layout, "swallow.back"));

   // start the animation
   elm_object_signal_emit(layout, "disappear,effect", "elm");
   elm_object_signal_callback_add(layout, "disappear,effect,finished", "*", _disappear_finished_cb, view_mgr);
}

static void
_animation_cb(void *data)
{
   ui_view *view;
   Eina_List *l;
   ui_viewmgr *view_mgr = data;
   view_mgr->animation_job = NULL;

   if(view_mgr->animation_ongoing) {
      view_mgr->animation_job = ecore_job_add(_animation_cb, view_mgr);
      return;
   } else {
      view_mgr->animation_ongoing = EINA_TRUE;
   }

   view_mgr->anim.view_this = eina_list_data_get(eina_list_last(view_mgr->view_stack));

   if(_ui_view_state_get(view_mgr->anim.view_this) == VIEW_ABOUT_TO_SHOW) { // Appear case
      EINA_LIST_REVERSE_FOREACH(view_mgr->view_stack, l, view) {
         if (_ui_view_state_get(view) == VIEW_SHOWN) {
            // this is our other view
            view_mgr->anim.view_other = view;
            break;
         }
      }
      _appear_effect(view_mgr);
   }

   if(_ui_view_state_get(view_mgr->anim.view_this) == VIEW_ABOUT_TO_HIDE) { // Disappear case  
      EINA_LIST_REVERSE_FOREACH(view_mgr->view_stack, l, view) {
         ui_view_state_type type = _ui_view_state_get(view);
         if ( (type == VIEW_HIDDEN) || (type == VIEW_ABOUT_TO_SHOW)) {
            // this is our other view
            view_mgr->anim.view_other = view;
            break;
         }
      }
      if(view_mgr->anim.view_other)
         _disappear_effect(view_mgr);
   }
}

static void
_key_grabber_key_up_cb(void *data, Evas *e, Evas_Object *obj,
                            void *event_info)
{
   Evas_Event_Key_Down *ev = event_info;
   ui_viewmgr *view_mgr = data;

   if (!strcmp(ev->keyname, KEY_BACK)) {
      // send the signal to current view
      ui_view *top_view = ui_viewmgr_top_view_get(view_mgr);
      if(top_view && (_ui_view_state_get(top_view) == VIEW_SHOWN)) {
         Eina_Bool handled = _ui_view_event_callback_call(top_view, SIG_VIEW_KEY_BACK, ev->keyname);
         if(!handled) {
            ui_viewmgr_view_pop(view_mgr);
         }
      }

   } else if(!strcmp(ev->keyname, KEY_SEND)) {
      // send the signal to current view
      ui_view *top_view = ui_viewmgr_top_view_get(view_mgr);
      if(top_view && (_ui_view_state_get(top_view) == VIEW_SHOWN))
         _ui_view_event_callback_call(top_view, SIG_VIEW_KEY_OPTION, ev->keyname);
   } else {
      return;
   }
}

static Eina_Bool
_init_key_grabber(ui_viewmgr *view_mgr)
{
   // initialize key grabber.
   view_mgr->key_grabber = evas_object_rectangle_add(evas_object_evas_get(view_mgr->window));

   evas_object_event_callback_add(view_mgr->key_grabber, EVAS_CALLBACK_KEY_UP,
                                  _key_grabber_key_up_cb, view_mgr);

   if (!evas_object_key_grab(view_mgr->key_grabber, KEY_SEND, 0, 0, EINA_FALSE))
      return EINA_FALSE;
   if(!evas_object_key_grab(view_mgr->key_grabber, KEY_BACK, 0, 0, EINA_FALSE))
      return EINA_FALSE;

   return EINA_TRUE;
}

void
_window_delete_cb(void *data, Evas* e EINA_UNUSED, Evas_Object *obj EINA_UNUSED, void *event_info EINA_UNUSED)
{
   ui_viewmgr *viewmgr = data;
   ui_viewmgr_del(viewmgr);
}

void
ui_viewmgr_del(ui_viewmgr *view_mgr)
{
   ui_view *view;
   VIEW_MGR_CHECK(view_mgr);
   EINA_LIST_FREE(view_mgr->view_stack, view)
   {
      _ui_view_event_callback_call(view, SIG_VIEW_UNLOAD, "");
      ui_view_del(view);
   }

}

EAPI ui_viewmgr *
ui_viewmgr_add(Evas_Object *window)
{
   if(!window)
      return NULL;
   if (!evas_object_smart_type_check(window, "elm_win"))
      return NULL;

   // check wheather window has any view manager.
   if(evas_object_data_get(window, "viewmgr"))
      return NULL;

   ui_viewmgr *view_mgr = calloc(1, sizeof(ui_viewmgr));
   if(!view_mgr)
   {
      return NULL;
   }
   view_mgr->window = window;
   // Add a callback for window deletion notification.
   evas_object_event_callback_add(view_mgr->window, EVAS_CALLBACK_DEL, _window_delete_cb, view_mgr);

   //create conformant
   //@TODO future work, create conformant based on  configuration.
   view_mgr->conformant = _create_conformant(window);
   elm_win_indicator_mode_set(view_mgr->window, ELM_WIN_INDICATOR_SHOW);

   view_mgr->base_layout = _create_layout(view_mgr->conformant, "baselayout");
   evas_object_size_hint_weight_set(view_mgr->base_layout, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
   elm_object_part_content_set(view_mgr->conformant, "elm.swallow.content", view_mgr->base_layout);

   _init_key_grabber(view_mgr);

   // update the window regarding view manager
   evas_object_data_set(window,"viewmgr", view_mgr);

   return view_mgr;
}


EAPI Eina_Bool
ui_viewmgr_view_push(ui_viewmgr *view_mgr, ui_view *view)
{

   VIEW_MGR_CHECK(view_mgr) EINA_FALSE;

   if(!view) // check for invalid view
      return EINA_FALSE;

   _ui_view_state_set(view, VIEW_ABOUT_TO_SHOW);
   // append to the stack
   view_mgr->view_stack = eina_list_append(view_mgr->view_stack, view);

   if(!view_mgr->animation_job)
      view_mgr->animation_job = ecore_job_add(_animation_cb, view_mgr);

   return EINA_TRUE;

}

EAPI Eina_Bool
ui_viewmgr_view_promote(ui_viewmgr *view_mgr, ui_view *view)
{
   VIEW_MGR_CHECK(view_mgr) EINA_FALSE;

   if(!view) // check for invalid view
      return EINA_FALSE;
   if(!view_mgr->view_stack)
      return EINA_FALSE;
   if(eina_list_data_find(view_mgr->view_stack, view)) { // view is on the stack
      if (ui_viewmgr_top_view_get(view_mgr) == view) // already on top
         return EINA_TRUE;
      // remove  the view from the stack.
      view_mgr->view_stack = eina_list_remove(view_mgr->view_stack, view);

      return ui_viewmgr_view_push(view_mgr, view);
   }

   return EINA_FALSE;
}

EAPI Eina_Bool
ui_viewmgr_view_insert_before(ui_viewmgr *view_mgr, ui_view *before, ui_view *view)
{
   VIEW_MGR_CHECK(view_mgr) EINA_FALSE;

   if(!view) // check for invalid view
      return EINA_FALSE;
   if(!before)
      return EINA_FALSE;

   if(eina_list_data_find(view_mgr->view_stack, view)) { // view is already on stack
      if(ui_viewmgr_top_view_get(view_mgr) == view) // if its the top view do nothing
         return EINA_FALSE;
      eina_list_remove(view_mgr->view_stack, view);

   } else {
      _ui_view_state_set(view, VIEW_ABOUT_TO_SHOW);
   }
   view_mgr->view_stack = eina_list_prepend_relative(view_mgr->view_stack, view, before);
   return EINA_TRUE;

}

EAPI Eina_Bool
ui_viewmgr_view_insert_after(ui_viewmgr *view_mgr, ui_view *after, ui_view *view)
{
   VIEW_MGR_CHECK(view_mgr) EINA_FALSE;

   if(!view) // check for invalid view
      return EINA_FALSE;
   if(!after)
      return EINA_FALSE;

   if(eina_list_data_find(view_mgr->view_stack, view)) { // view is already on stack
      if(ui_viewmgr_top_view_get(view_mgr) == view) // if its the top view do nothing
         return EINA_FALSE;
      eina_list_remove(view_mgr->view_stack, view);

   } else {
      _ui_view_state_set(view, VIEW_ABOUT_TO_SHOW);
   }

   if (ui_viewmgr_top_view_get(view_mgr) == after)
      return ui_viewmgr_view_push(view_mgr, view);

   view_mgr->view_stack = eina_list_append_relative(view_mgr->view_stack, view, after);
   return EINA_TRUE;

}

EAPI Eina_Bool
ui_viewmgr_view_pop(ui_viewmgr *view_mgr)
{
   ui_view *top_view;

   VIEW_MGR_CHECK(view_mgr) EINA_FALSE;

   // get the current view that is on top of the stack.
   top_view = ui_viewmgr_top_view_get(view_mgr);

   if(!top_view || (eina_list_count(view_mgr->view_stack) == 1))
      return EINA_FALSE;

   _ui_view_state_set(top_view, VIEW_ABOUT_TO_HIDE);

   if(!view_mgr->animation_job)
      view_mgr->animation_job = ecore_job_add(_animation_cb, view_mgr);

   return EINA_TRUE;

}

EAPI Eina_Bool
ui_viewmgr_view_pop_to(ui_viewmgr *view_mgr, ui_view *to_view)
{
   ui_view *top_view, *view = NULL;
   Eina_List *sublist, *l, *l_next;

   VIEW_MGR_CHECK(view_mgr) EINA_FALSE;
   if(!view_mgr->view_stack) return EINA_FALSE;

   top_view = ui_viewmgr_top_view_get(view_mgr);
   if(!top_view) return EINA_FALSE;

   if(top_view == to_view) return EINA_FALSE;

   // check if the view is present in the stack
   sublist = eina_list_data_find_list(view_mgr->view_stack, to_view);
   if(!sublist) return EINA_FALSE;
   sublist = eina_list_next(sublist);
   if(!sublist) return EINA_FALSE;

   EINA_LIST_FOREACH_SAFE(sublist,l,l_next,view) {
      if(view != top_view) {
         _ui_view_event_callback_call(view_mgr->anim.view_this, SIG_VIEW_UNLOAD,"");
         ui_view_del(view);
         sublist = eina_list_remove_list(sublist, l);
      }
   }

   _ui_view_state_set(top_view,VIEW_ABOUT_TO_HIDE);

   if(!view_mgr->animation_job)
      view_mgr->animation_job = ecore_job_add(_animation_cb, view_mgr);

   return EINA_TRUE;
}

EAPI ui_view *
ui_viewmgr_top_view_get(const ui_viewmgr *view_mgr)
{
   VIEW_MGR_CHECK(view_mgr) NULL;
   if (!view_mgr->view_stack) return NULL;

   return eina_list_data_get(eina_list_last(view_mgr->view_stack));
}

EAPI Evas_Object *
ui_viewmgr_conformant_get(const ui_viewmgr *view_mgr)
{
   VIEW_MGR_CHECK(view_mgr) NULL;
   return view_mgr->conformant;
}
