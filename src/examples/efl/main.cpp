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
#include "page15.h"
#include "page14.h"
#include "page13.h"
#include "page12.h"
#include "page11.h"
#include "page10.h"
#include "page9.h"
#include "page8.h"
#include "page7.h"
#include "page6.h"
#include "page5.h"
#include "page4.h"
#include "page3.h"
#include "page2.h"
#include "page1.h"

Elm_Toolbar*
create_toolbar(Evas_Object *parent, const char *style)
{
	Elm_Toolbar *toolbar;

	toolbar = elm_toolbar_add(parent);

	//FIXME: :( UI_View can set this style instead.
	elm_object_style_set(toolbar, style);

	//FIXME: If not call below API, toolbar items create with min size.
	//       It looks toolbar bug.
	elm_toolbar_shrink_mode_set(toolbar, ELM_TOOLBAR_SHRINK_EXPAND);

	elm_toolbar_item_append(toolbar, NULL, "Tab1", NULL, NULL);
	elm_toolbar_item_append(toolbar, NULL, "Tab2", NULL, NULL);
	elm_toolbar_item_append(toolbar, NULL, "Tab3", NULL, NULL);
	elm_toolbar_item_append(toolbar, NULL, "Tab4", NULL, NULL);

	return toolbar;
}

Evas_Object*
create_scrolling_content(Evas_Object *parent)
{
	char buf[PATH_MAX];
	Elm_Grid *grid;
	Elm_Box *box;
	Elm_Layout *layout;
	Elm_Scroller *scroller;
	Elm_Button *btn;
	Elm_Image *image;


	/* Image */
	image = elm_image_add(parent);
	snprintf(buf, sizeof(buf), "%s/data/images/bg.png", BINDIR);
	elm_image_file_set(image, buf, NULL);
	evas_object_show(image);
	elm_image_resizable_set(image, EINA_FALSE, EINA_FALSE);

	return image;
}

Evas_Object*
create_landscape_content(Evas_Object *parent, const char *text, Evas_Smart_Cb prev_btn_clicked_cb, Evas_Smart_Cb next_btn_clicked_cb)
{
	char buf[PATH_MAX];
	Elm_Grid *grid;
	Elm_Box *box;
	Elm_Layout *layout;
	Elm_Scroller *scroller;
	Elm_Button *btn;
	Elm_Image *image;

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
	elm_grid_pack(grid, layout, 0, 0, 50, 100);

	/* Image */
	image = elm_image_add(grid);
	snprintf(buf, sizeof(buf), "%s/data/images/tizen.png", BINDIR);
	elm_image_file_set(image, buf, NULL);
	evas_object_show(image);
	elm_grid_pack(grid, image, 50, 0, 50, 85);

	/* Box */
	box = elm_box_add(grid);
	elm_box_horizontal_set(box, EINA_TRUE);
	evas_object_size_hint_weight_set(box, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_size_hint_align_set(box, EVAS_HINT_FILL, EVAS_HINT_FILL);
	elm_box_padding_set(box, ELM_SCALE_SIZE(50), 0);
	evas_object_show(box);
	elm_grid_pack(grid, box, 0, 0, 100, 100);

	/* Previous Page Button */
	btn = elm_button_add(grid);
	evas_object_size_hint_weight_set(btn, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_size_hint_align_set(btn, EVAS_HINT_FILL, 1.0);
	elm_object_text_set(btn, "Prev");
	evas_object_smart_callback_add(btn, "clicked", prev_btn_clicked_cb, NULL);
	evas_object_show(btn);
	elm_box_pack_end(box, btn);

	/* Next Page Button */
	btn = elm_button_add(grid);
	evas_object_size_hint_weight_set(btn, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_size_hint_align_set(btn, EVAS_HINT_FILL, 1.0);
	elm_object_text_set(btn, "Next");
	evas_object_smart_callback_add(btn, "clicked", next_btn_clicked_cb, NULL);
	evas_object_show(btn);
	elm_box_pack_end(box, btn);

	elm_object_content_set(scroller, grid);

	return scroller;
}

Evas_Object*
create_content(Evas_Object *parent, const char *text, Evas_Smart_Cb prev_btn_clicked_cb, Evas_Smart_Cb next_btn_clicked_cb)
{
	Elm_Grid *grid;
	Elm_Box *box;
	Elm_Layout *layout;
	Elm_Scroller *scroller;
	Elm_Button *btn;

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

	/* Box */
	box = elm_box_add(grid);
	elm_box_horizontal_set(box, EINA_TRUE);
	evas_object_size_hint_weight_set(box, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_size_hint_align_set(box, EVAS_HINT_FILL, EVAS_HINT_FILL);
	elm_box_padding_set(box, ELM_SCALE_SIZE(50), 0);
	evas_object_show(box);
	elm_grid_pack(grid, box, 0, 0, 100, 100);

	/* Previous Page Button */
	btn = elm_button_add(grid);
	evas_object_size_hint_weight_set(btn, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_size_hint_align_set(btn, EVAS_HINT_FILL, 1.0);
	elm_object_text_set(btn, "Prev");
	evas_object_smart_callback_add(btn, "clicked", prev_btn_clicked_cb, NULL);
	evas_object_show(btn);
	elm_box_pack_end(box, btn);

	/* Next Page Button */
	btn = elm_button_add(grid);
	evas_object_size_hint_weight_set(btn, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_size_hint_align_set(btn, EVAS_HINT_FILL, 1.0);
	elm_object_text_set(btn, "Next");
	evas_object_smart_callback_add(btn, "clicked", next_btn_clicked_cb, NULL);
	evas_object_show(btn);
	elm_box_pack_end(box, btn);

	elm_object_content_set(scroller, grid);

	return scroller;
}

static void create_base_gui(void)
{
	create_page1();
	UI_VIEWMGR->activate();
}

static bool app_create(void *data)
{
	/* Hook to take necessary actions before main event loop starts
	 Initialize UI resources and application's data
	 If this function returns true, the main loop of application starts
	 If this function returns false, the application is terminated */

	elm_app_base_scale_set(2.6);

	/* Bind package locale file */
	bindtextdomain(PACKAGE, LOCALE_DIR);
	textdomain(PACKAGE);

	//FIXME: Hide this creation.
	ui_viewmgr *viewmgr = new ui_viewmgr(PACKAGE);

	create_base_gui();

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
	UI_VIEWMGR->activate();
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
	appdata_s ad;
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
