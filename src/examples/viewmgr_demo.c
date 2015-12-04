/*
 * Copyright (c) 2013 Samsung Electronics Co., Ltd All Rights Reserved
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 *
 */


#include <Elementary.h>
#include <dlog.h>
#include <ui_view.h>
#include <ui_viewmgr.h>

static Evas_Object *window;
static ui_viewmgr *view_mgr;
static ui_view *promote_view;

Evas_Object*
create_btn(const char *title, Eina_Bool left, Eina_Bool popup_btn)
{
   Evas_Object *button = elm_button_add(window);

   if (popup_btn)
     elm_object_style_set(button, "bottom");
   else
     {
        if (left)
          elm_object_style_set(button, "naviframe/title_left");
        else
          elm_object_style_set(button, "naviframe/title_right");
     }

   elm_object_text_set(button, title);
   return button;
}

Evas_Object*
create_content(const char *text)
{
   Evas_Object  *nocontents;

   /* Create elm_layout and set its style as nocontents/text */
   nocontents = elm_layout_add(window);
   elm_layout_theme_set(nocontents, "layout", "nocontents", "default");
   evas_object_size_hint_weight_set(nocontents, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
   evas_object_size_hint_align_set(nocontents, EVAS_HINT_FILL, EVAS_HINT_FILL);
   elm_object_part_text_set(nocontents, "elm.text", text);
   elm_layout_signal_emit(nocontents, "align.center", "elm");

   return nocontents;
}

// Create Content using layout and elm_widgets
Evas_Object*
create_view(const char *title_label,Evas_Object *prev_btn,Evas_Object *next_btn,Evas_Object *content)
{
   Evas_Object *layout;
   layout = elm_layout_add(window);
   elm_layout_theme_set(layout, "layout", "application", "view");

   // add next button if any
   if(next_btn) {
      elm_object_part_content_set(layout, "title_right_btn", next_btn);
   }
   // add prev_button if any
   if(prev_btn) {
      elm_object_part_content_set(layout, "title_left_btn", prev_btn);
   }
   if(content) {
      elm_object_part_content_set(layout, "elm.swallow.content", content);
   }
   if(title_label) {
      elm_object_part_text_set(layout, "elm.text.title", title_label);
   }
   return layout;
}

// pop the top view from the view manager stack
void
_pop_view(void *data EINA_UNUSED, Evas_Object *obj EINA_UNUSED, void *event_info EINA_UNUSED)
{
   ui_viewmgr_view_pop(view_mgr);
}

// promote a view to top of the stack
void
_promote_view2(void *data EINA_UNUSED, Evas_Object *obj EINA_UNUSED, void *event_info EINA_UNUSED)
{
   ui_viewmgr_view_promote(view_mgr, promote_view);
}

// this is the callback handler for view_event 
Eina_Bool
_view6(void *data EINA_UNUSED, ui_view *viewobj EINA_UNUSED, void *event_info EINA_UNUSED)
{
   Evas_Object *prev, *content, *next;
   prev = create_btn("view 5", EINA_TRUE, EINA_FALSE);
   next = create_btn("Promote View 2", EINA_FALSE, EINA_FALSE);
   content = create_view("View 6",prev,next,create_content("View 6 Content"));
   ui_view *view = ui_view_add(content);
   ui_view_style_set(view, "slidein");
   ui_viewmgr_view_push(view_mgr, view);
   evas_object_smart_callback_add(prev, "clicked", _pop_view, view_mgr);
   evas_object_smart_callback_add(next, "clicked", _promote_view2, view_mgr);
}

void
_popup_cb(void *data, Evas_Object *obj EINA_UNUSED, void *event_info EINA_UNUSED)
{
   ui_view *view = data;
   // add a callback when the view pop transition is finished.
   ui_view_event_callback_add(view,"view,disappear,finish",_view6,data);
   ui_viewmgr_view_pop(view_mgr);
}

// A popup view which will overlay on top of the previous view
void
_view5(void *data EINA_UNUSED, Evas_Object *obj EINA_UNUSED, void *event_info EINA_UNUSED)
{
   Evas_Object *content, *next, *cancel, *popup;

   popup = elm_popup_add(window);
   elm_popup_align_set(popup, ELM_NOTIFY_ALIGN_FILL, 1.0);
   evas_object_size_hint_weight_set(popup, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
   elm_object_text_set(popup, "This popup has content area and action area, action area has two buttons Next and Cancel.");

   ui_view *view = ui_view_add(popup);

   next = create_btn("Next", EINA_FALSE, EINA_TRUE);
   cancel = create_btn("Cancel", EINA_FALSE, EINA_TRUE);

   elm_object_part_content_set(popup, "button1", next);
   evas_object_smart_callback_add(next, "clicked", _popup_cb, view);
   elm_object_part_content_set(popup, "button2", cancel);
   evas_object_smart_callback_add(cancel, "clicked", _pop_view, view_mgr);

   ui_view_style_set(view, "popup");
   ui_viewmgr_view_push(view_mgr, view);

   evas_object_smart_callback_add(prev, "clicked", _pop_view, view_mgr);
   evas_object_smart_callback_add(next, "clicked", _popup_cb, view);
}

void
_view4(void *data EINA_UNUSED, Evas_Object *obj EINA_UNUSED, void *event_info EINA_UNUSED)
{
   Evas_Object *prev, *next, *content;
   prev = create_btn("view3", EINA_TRUE, EINA_FALSE);
   next = create_btn("Next", EINA_FALSE, EINA_FALSE);
   content = create_view("View 4",prev,next,create_content("View 4 Content"));
   ui_view *view = ui_view_add(content);

   // set a different style for the view transition
   ui_view_style_set(view, "slidein");

   ui_viewmgr_view_push(view_mgr, view);
   evas_object_smart_callback_add(prev, "clicked", _pop_view, view_mgr);
   evas_object_smart_callback_add(next, "clicked", _view5, view_mgr);

}

void
_view3(void *data EINA_UNUSED, Evas_Object *obj EINA_UNUSED, void *event_info EINA_UNUSED)
{
   Evas_Object *prev, *next, *content;
   prev = create_btn("view2", EINA_TRUE, EINA_FALSE);
   next = create_btn("Next", EINA_FALSE, EINA_FALSE);
   content = create_view("View 3",prev,next,create_content("View 3 Content"));
   ui_view *view = ui_view_add(content);
   ui_view_style_set(view, "default");
   ui_viewmgr_view_push(view_mgr, view);
   evas_object_smart_callback_add(prev, "clicked", _pop_view, view_mgr);
   evas_object_smart_callback_add(next, "clicked", _view4, view_mgr);

}

// A callback handler to set the content of view2
Eina_Bool _load_view2_cb(void *data EINA_UNUSED, ui_view *view , void *event_info EINA_UNUSED)
{
   Evas_Object *prev, *next, *content;
   prev = create_btn("view1", EINA_TRUE, EINA_FALSE);
   next = create_btn("Next", EINA_FALSE, EINA_FALSE);
   content = create_view("View 2",prev,next,create_content("View 2 Content"));
   evas_object_smart_callback_add(prev, "clicked", _pop_view, view_mgr);
   evas_object_smart_callback_add(next, "clicked", _view3, view_mgr);
   ui_view_content_set(view,content);
}

// Lazy initialization of the content in a view
// if no style is set then default style will be used for view transition
void
_view2(void *data EINA_UNUSED, Evas_Object *obj EINA_UNUSED, void *event_info EINA_UNUSED)
{
   ui_view *view = ui_view_add(NULL);
   ui_viewmgr_view_push(view_mgr, view);

   // add a callback for the view,load notification
   ui_view_event_callback_add(view,"view,load",_load_view2_cb,data);
   promote_view = view;
}

Eina_Bool _key_back_cb(void *data EINA_UNUSED, ui_view *obj EINA_UNUSED, void *event_info EINA_UNUSED)
{
   // delete the window
   // The view manager assosiated with this wind will get deleted automatically.
   evas_object_del(window);
   return EINA_TRUE;
}

// The first view on the application
// if user don't want any view animation while app is lunching 
// user can set the view style as "noanimation"
void
_view1(void *data, Evas_Object *obj EINA_UNUSED, void *event_info EINA_UNUSED)
{
   Evas_Object  *next, *content;
   next = create_btn("Next", EINA_FALSE, EINA_FALSE);
   content = create_view("View 1",NULL, next, create_content("View 1 Content"));
   ui_view *view = ui_view_add(content);
   ui_viewmgr_view_push(view_mgr, view);

   // if we don't want view swithcing animation
   ui_view_style_set(view, "noanimation");

   evas_object_smart_callback_add(next, "clicked", _view2, data);

   // Add a "key,back" callback to handle application close
   ui_view_event_callback_add(view, "key,back",_key_back_cb,data);
}

int
elm_main(int argc, char **argv)
{
   // create a window with background
   //window = elm_win_util_standard_add("viewmanager", "ViewMannager");
   window = elm_win_add(NULL, "viewmanager", ELM_WIN_BASIC);
   elm_win_autodel_set(window, EINA_TRUE);

   // Create View manager using window as a parent
   view_mgr = ui_viewmgr_add(window);

   // add a view to vew manager.
   _view1(view_mgr,NULL,NULL);

   evas_object_resize(window, 720, 1280);
   elm_win_autodel_set(window, EINA_TRUE);
   elm_policy_set(ELM_POLICY_QUIT, ELM_POLICY_QUIT_LAST_WINDOW_CLOSED);
   evas_object_show(window);

   elm_run();
   elm_shutdown();
   return 0;
}
ELM_MAIN()
