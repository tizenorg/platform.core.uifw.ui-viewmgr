/*
 * Copyright (c) 2015 Samsung Electronics Co., Ltd All Rights Reserved
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *               http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 *
 */

#include "main.h"
#include <iostream>
#include "ui_viewmgr.h"
#include "app_controller.h"

using namespace std;
using namespace efl;

ui_viewmgr *viewmgr;
app_controller *controller;
ui_view *view1;
ui_view *view2;
ui_view *view3;

static void
win_delete_request_cb(void *data, Evas_Object *obj, void *event_info)
{
   /* To make your application go to background,
      Call the elm_win_lower() instead
      Evas_Object *win = (Evas_Object *) data;
      elm_win_lower(win); */
   ui_app_exit();
}

static Evas_Object*
create_bg(Evas_Object *parent, int num)
{
   Evas_Object *bg;

   bg = elm_bg_add(parent);
   evas_object_size_hint_weight_set(bg, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
   evas_object_size_hint_align_set(bg, EVAS_HINT_FILL, EVAS_HINT_FILL);

   if (num == 1)
     elm_bg_color_set(bg, 0, 0, 100);
   else if (num == 2)
     elm_bg_color_set(bg, 100, 0, 0);
   else
     elm_bg_color_set(bg, 0, 100, 0);


   evas_object_show(bg);

   return bg;
}


static Evas_Object *
_create_view(appdata_s *ad, int num, Eina_Bool left_btn, Evas_Smart_Cb priv_func,
             Eina_Bool right_btn, Evas_Smart_Cb next_func)
{
   Evas_Object *grid = elm_grid_add(ad->win);
   evas_object_size_hint_weight_set(grid, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
   evas_object_size_hint_align_set(grid, EVAS_HINT_FILL, EVAS_HINT_FILL);
   evas_object_show(grid);

   Evas_Object *bg = create_bg(grid, num);
   elm_grid_pack(grid, bg, 0, 0, 100, 100);

   if (left_btn)
     {
        Evas_Object *btn = elm_button_add(ad->win);
        evas_object_size_hint_weight_set(btn, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
        evas_object_size_hint_align_set(btn, EVAS_HINT_FILL, EVAS_HINT_FILL);
        elm_object_text_set(btn, "priv");
        evas_object_smart_callback_add(btn, "clicked", priv_func, ad);
        evas_object_show(btn);
        elm_grid_pack(grid, btn, 10, 5, 20, 10);
     }

   if (right_btn)
     {
        Evas_Object *btn = elm_button_add(ad->win);
        evas_object_size_hint_weight_set(btn, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
        evas_object_size_hint_align_set(btn, EVAS_HINT_FILL, EVAS_HINT_FILL);
        elm_object_text_set(btn, "next");
        evas_object_smart_callback_add(btn, "clicked", next_func, ad);
        evas_object_show(btn);
        elm_grid_pack(grid, btn, 70, 5, 20, 10);
     }

   return grid;
}

void
_pop_view(void *data, Evas_Object *obj, void *event_info)
{
   viewmgr->pop_view();
}

static void
_view_3_clicked(void *data, Evas_Object *obj, void *event_info)
{
   appdata_s *ad = (appdata_s *)data;
   view3 = new ui_view();
   view3->set_controller(controller);

   Evas_Object *content = elm_button_add(ad->win);
   evas_object_size_hint_weight_set(content, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
   evas_object_size_hint_align_set(content, EVAS_HINT_FILL, EVAS_HINT_FILL);
   elm_object_text_set(content, "view 3");
   evas_object_show(content);

   view3->set_content(content);
   viewmgr->push_view(view3);

}

static void
_view_2_clicked(void *data, Evas_Object *obj, void *event_info)
{
   appdata_s *ad = (appdata_s *)data;
   view2 = new ui_view();
   view2->set_controller(controller);

   Evas_Object *view = _create_view(ad, 2, EINA_TRUE, _pop_view, EINA_TRUE, _view_3_clicked);

   view2->set_content(view);
   viewmgr->push_view(view2);
}

void
_view1(appdata_s *ad)
{
   view1 = new ui_view();
   view1->set_controller(controller);

   Evas_Object *view = _create_view(ad, 1, EINA_FALSE, NULL, EINA_TRUE, _view_2_clicked);

   view1->set_content(view);
   viewmgr->push_view(view1);
}

static void
create_base_gui(appdata_s *ad)
{
   /* Window */
   ad->win = elm_win_util_standard_add(PACKAGE, PACKAGE);
   elm_win_conformant_set(ad->win, EINA_TRUE);
   elm_win_autodel_set(ad->win, EINA_TRUE);

   if (elm_win_wm_rotation_supported_get(ad->win)) {
        int rots[4] = { 0, 90, 180, 270 };
        elm_win_wm_rotation_available_rotations_set(ad->win, (const int *)(&rots), 4);
   }

   evas_object_smart_callback_add(ad->win, "delete,request", win_delete_request_cb, NULL);

   /* Indicator */
   elm_win_indicator_mode_set(ad->win, ELM_WIN_INDICATOR_SHOW);
   elm_win_indicator_opacity_set(ad->win, ELM_WIN_INDICATOR_TRANSPARENT);

   viewmgr = new ui_viewmgr(ad->win);
   controller = new app_controller();

   _view1(ad);

   /* Show window after base gui is set up */
   evas_object_show(ad->win);
}

static bool
app_create(void *data)
{
   /* Hook to take necessary actions before main event loop starts
      Initialize UI resources and application's data
      If this function returns true, the main loop of application starts
      If this function returns false, the application is terminated */
   appdata_s *ad = (appdata_s *)data;

   elm_app_base_scale_set(2.6);

   /* Enable HW acceleration */
   elm_config_accel_preference_set("3d");

   /* Bind package locale file */
   bindtextdomain (PACKAGE, LOCALE_DIR);
   textdomain (PACKAGE);

   create_base_gui(ad);

   return true;
}

static void
app_control(app_control_h app_control, void *data)
{
   /* Handle the launch request. */
}

static void
app_pause(void *data)
{
}

static void
app_resume(void *data)
{
}

static void
app_terminate(void *data)
{
}

static void
ui_app_lang_changed(app_event_info_h event_info, void *user_data)
{
   /*APP_EVENT_LANGUAGE_CHANGED*/
   char *locale = NULL;
   system_settings_get_value_string(SYSTEM_SETTINGS_KEY_LOCALE_LANGUAGE, &locale);
   elm_language_set(locale);
   free(locale);
   return;
}

static void
ui_app_orient_changed(app_event_info_h event_info, void *user_data)
{
   /*APP_EVENT_DEVICE_ORIENTATION_CHANGED*/
   return;
}

static void
ui_app_region_changed(app_event_info_h event_info, void *user_data)
{
   /*APP_EVENT_REGION_FORMAT_CHANGED*/
}

static void
ui_app_low_battery(app_event_info_h event_info, void *user_data)
{
   /*APP_EVENT_LOW_BATTERY*/
}

static void
ui_app_low_memory(app_event_info_h event_info, void *user_data)
{
   /*APP_EVENT_LOW_MEMORY*/
}

int
main(int argc, char *argv[])
{
   appdata_s ad = {0,};
   int ret = 0;

   ui_app_lifecycle_callback_s event_callback = {0,};
   app_event_handler_h handlers[5] = {NULL, };

   event_callback.create = app_create;
   event_callback.terminate = app_terminate;
   event_callback.pause = app_pause;
   event_callback.resume = app_resume;
   event_callback.app_control = app_control;

   ui_app_add_event_handler(&handlers[APP_EVENT_LOW_BATTERY], APP_EVENT_LOW_BATTERY, ui_app_low_battery, &ad);
   ui_app_add_event_handler(&handlers[APP_EVENT_LOW_MEMORY], APP_EVENT_LOW_MEMORY, ui_app_low_memory, &ad);
   ui_app_add_event_handler(&handlers[APP_EVENT_DEVICE_ORIENTATION_CHANGED], APP_EVENT_DEVICE_ORIENTATION_CHANGED, ui_app_orient_changed, &ad);
   ui_app_add_event_handler(&handlers[APP_EVENT_LANGUAGE_CHANGED], APP_EVENT_LANGUAGE_CHANGED, ui_app_lang_changed, &ad);
   ui_app_add_event_handler(&handlers[APP_EVENT_REGION_FORMAT_CHANGED], APP_EVENT_REGION_FORMAT_CHANGED, ui_app_region_changed, &ad);
   ui_app_remove_event_handler(handlers[APP_EVENT_LOW_MEMORY]);

   ret = ui_app_main(argc, argv, &event_callback, &ad);
   if (ret != APP_ERROR_NONE) {
        dlog_print(DLOG_ERROR, LOG_TAG, "app_main() is failed. err = %d", ret);
   }

   return ret;
}
