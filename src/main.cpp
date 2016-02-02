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
#include "app_controller.h"

/*
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

   Evas_Object *view = _create_view(ad, 3, EINA_TRUE, _pop_view, EINA_FALSE, NULL);

   view3->set_content(view);
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
*/



static void
create_base_gui(appdata_s *ad)
{
   ad->viewmgr = new ui_viewmgr(PACKAGE);

   //View 1
   {
	   app_controller1 *controller = new app_controller1();
	   ad->viewmgr->push_view(new ui_basic_view(controller));
   }

   //View 2
   {
	   app_controller2 *controller = new app_controller2(ad);
	   ad->viewmgr->push_view(new ui_basic_view(controller));
   }

#if 0
   //View 3
   app_controller1 *controller = new app_controller1();
   ui_basic_view *view = ad->viewmgr->push_view(new ui_basic_view(controller));

   //View 3
   app_controller1 *controller = new app_controller1();
   ui_basic_view *view = ad->viewmgr->push_view(new ui_basic_view(controller));
#endif

   ad->viewmgr->activate();
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
//   elm_config_accel_preference_set("3d");

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
