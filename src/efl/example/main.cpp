/*
 * Copyright (c) 2016 Samsung Electronics Co., Ltd All Rights Reserved
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
#include "page6.h"
#include "page5.h"
#include "page4.h"
#include "page3.h"
#include "page2.h"
#include "page1.h"


Evas_Object*
create_tabbar(Evas_Object *parent)
{
	Evas_Object *toolbar;

	toolbar = elm_toolbar_add(parent);

	elm_object_style_set(toolbar, "tabbar_with_title");
	elm_toolbar_shrink_mode_set(toolbar, ELM_TOOLBAR_SHRINK_EXPAND);
	elm_toolbar_transverse_expanded_set(toolbar, EINA_TRUE);

	elm_toolbar_item_append(toolbar, NULL, "Tab1", NULL, NULL);
	elm_toolbar_item_append(toolbar, NULL, "Tab2", NULL, NULL);

	elm_toolbar_select_mode_set(toolbar, ELM_OBJECT_SELECT_MODE_ALWAYS);

	return toolbar;
}
Evas_Object*
create_content(Evas_Object *parent, const char *text, Evas_Smart_Cb prev_btn_clicked_cb, Evas_Smart_Cb next_btn_clicked_cb, appdata_s *ad)
{
	Evas_Object *grid, *box, *layout, *scroller, *btn, *button_layout;

	/* Scroller */
	scroller = elm_scroller_add(parent);
	elm_scroller_bounce_set(scroller, EINA_FALSE, EINA_TRUE);
	elm_scroller_policy_set(scroller, ELM_SCROLLER_POLICY_OFF, ELM_SCROLLER_POLICY_AUTO);

	/* Grid */
	grid = elm_grid_add(scroller);
	evas_object_size_hint_weight_set(grid, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_size_hint_align_set(grid, EVAS_HINT_FILL, EVAS_HINT_FILL);
	evas_object_show(grid);

	/* NoContent Layout */
	layout = elm_layout_add(grid);
	elm_layout_theme_set(layout, "layout", "nocontents", "default");
	elm_object_part_text_set(layout, "elm.text", text);
	evas_object_show(layout);
	elm_grid_pack(grid, layout, 0, 0, 100, 100);

	/* Previous Page Button */
	btn = elm_button_add(grid);
	elm_object_text_set(btn, "Prev");
	evas_object_smart_callback_add(btn, "clicked", prev_btn_clicked_cb, ad);
	evas_object_show(btn);
	elm_grid_pack(grid, btn, 10, 90, 30, 8);

	/* Next Page Button */
	btn = elm_button_add(grid);
	elm_object_text_set(btn, "Next");
	evas_object_smart_callback_add(btn, "clicked", next_btn_clicked_cb, ad);
	evas_object_show(btn);
	elm_grid_pack(grid, btn, 60, 90, 30, 8);

	elm_object_content_set(scroller, grid);

	return scroller;
}

static void create_base_gui(appdata_s *ad)
{
	//FIXME: Hide this creation.
	ad->viewmgr = new ui_viewmgr(PACKAGE);

	create_page1(ad);

	ad->viewmgr->activate();
}

static bool app_create(void *data)
{
	/* Hook to take necessary actions before main event loop starts
	 Initialize UI resources and application's data
	 If this function returns true, the main loop of application starts
	 If this function returns false, the application is terminated */
	appdata_s *ad = (appdata_s *) data;

	elm_app_base_scale_set(2.6);

	/* Bind package locale file */
	bindtextdomain(PACKAGE, LOCALE_DIR);
	textdomain(PACKAGE);

	create_base_gui(ad);

	return true;
}

static void app_control(app_control_h app_control, void *data)
{
	/* Handle the launch request. */
}

static void app_pause(void *data)
{
}

static void app_resume(void *data)
{
	appdata_s *ad = (appdata_s *) data;
	ad->viewmgr->activate();
}

static void app_terminate(void *data)
{
}

static void ui_app_lang_changed(app_event_info_h event_info, void *user_data)
{
	/*APP_EVENT_LANGUAGE_CHANGED*/
	char *locale = NULL;
	system_settings_get_value_string(SYSTEM_SETTINGS_KEY_LOCALE_LANGUAGE, &locale);
	elm_language_set(locale);
	free(locale);

	return;
}

static void ui_app_orient_changed(app_event_info_h event_info, void *user_data)
{
	/*APP_EVENT_DEVICE_ORIENTATION_CHANGED*/
	return;
}

static void ui_app_region_changed(app_event_info_h event_info, void *user_data)
{
	/*APP_EVENT_REGION_FORMAT_CHANGED*/
}

static void ui_app_low_battery(app_event_info_h event_info, void *user_data)
{
	/*APP_EVENT_LOW_BATTERY*/
}

static void ui_app_low_memory(app_event_info_h event_info, void *user_data)
{
	/*APP_EVENT_LOW_MEMORY*/
}

int main(int argc, char *argv[])
{
	appdata_s ad = { 0, };
	int ret = 0;

	ui_app_lifecycle_callback_s event_callback = { 0, };
	app_event_handler_h handlers[5] = { NULL, };

	event_callback.create = app_create;
	event_callback.terminate = app_terminate;
	event_callback.pause = app_pause;
	event_callback.resume = app_resume;
	event_callback.app_control = app_control;

	ui_app_add_event_handler(&handlers[APP_EVENT_LOW_BATTERY], APP_EVENT_LOW_BATTERY, ui_app_low_battery, &ad);
	ui_app_add_event_handler(&handlers[APP_EVENT_LOW_MEMORY], APP_EVENT_LOW_MEMORY, ui_app_low_memory, &ad);
	ui_app_add_event_handler(&handlers[APP_EVENT_DEVICE_ORIENTATION_CHANGED], APP_EVENT_DEVICE_ORIENTATION_CHANGED,
			ui_app_orient_changed, &ad);
	ui_app_add_event_handler(&handlers[APP_EVENT_LANGUAGE_CHANGED], APP_EVENT_LANGUAGE_CHANGED, ui_app_lang_changed, &ad);
	ui_app_add_event_handler(&handlers[APP_EVENT_REGION_FORMAT_CHANGED], APP_EVENT_REGION_FORMAT_CHANGED, ui_app_region_changed,
			&ad);
	ui_app_remove_event_handler(handlers[APP_EVENT_LOW_MEMORY]);

	ret = ui_app_main(argc, argv, &event_callback, &ad);
	if (ret != APP_ERROR_NONE)
	{
		dlog_print(DLOG_ERROR, LOG_TAG, "app_main() is failed. err = %d", ret);
	}

	return ret;
}
