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

static void
view5_prev_btn_clicked_cb(void *data, Evas_Object *obj, void *event_info)
{
	UI_VIEWMGR_VIEW_POP();
}

static void
view5_next_btn_clicked_cb(void *data, Evas_Object *obj, void *event_info)
{
	create_page6();
}

static void
view5_load_cb(void *data, ui_view *view)
{
	ui_view_on_load();

	Evas_Object *base_layout = ui_view_base_layout_get(view);

	Evas_Object *content = create_content(base_layout, "ViewMgr Demo<br>Full View",
			view5_prev_btn_clicked_cb, view5_next_btn_clicked_cb, data);

	ui_view_content_set(view, content);
	ui_view_title_badge_set("999+");
}

static void
create_page5()
{
	ui_view_lifecycle_callback_s event_callback = {0, };
	event_callback.load = view5_load_cb;

	//Is it proper way to set style of view?
	ui_view *view = ui_view_create(NULL, "page5", "ui_view", &event_callback);

	// Does it change to like below?
	//ui_view *view = ui_view_create(NULL, "page1", &event_callback, &data);

	UI_VIEWMGR_VIEW_PUSH(view);
}


static void
view4_prev_btn_clicked_cb(void *data, Evas_Object *obj, void *event_info)
{
	UI_VIEWMGR_VIEW_POP();
}

static void
view4_next_btn_clicked_cb(void *data, Evas_Object *obj, void *event_info)
{
	create_page5();
}

static void
view4_load_cb(void *data, ui_view *view)
{
	ui_view_on_load();

	Evas_Object *base_layout = ui_view_base_layout_get(view);

	Evas_Object *content = create_content(base_layout, "ViewMgr Demo<br>Title Badge",
			view4_prev_btn_clicked_cb, view4_next_btn_clicked_cb, data);

	ui_view_content_set(view, content, "Page4 We put a long title here intentionally");
	ui_view_title_badge_set("999+");
}

static void
create_page4()
{
	ui_view_lifecycle_callback_s event_callback = {0, };
	event_callback.load = view4_load_cb;

	ui_view *view = ui_view_create(NULL, "page4", NULL, &event_callback);
	// Does it change to like below?
	//ui_view *view = ui_view_create(NULL, "page1", &event_callback, &data);

	UI_VIEWMGR_VIEW_PUSH(view);
}

static void
view3_prev_btn_clicked_cb(void *data, Evas_Object *obj, void *event_info)
{
	UI_VIEWMGR_VIEW_POP();
}

static void
view3_next_btn_clicked_cb(void *data, Evas_Object *obj, void *event_info)
{
	create_page4();
}

static void
view3_load_cb(void *data, ui_view *view)
{
	ui_view_on_load();

	Evas_Object *base_layout = ui_view_base_layout_get(view);

	Evas_Object *content = create_content(base_layout, "ViewMgr Demo<br>Subtitle",
			view3_prev_btn_clicked_cb, view3_next_btn_clicked_cb, data);

	ui_view_content_set(view, content, "Page3", "Subtitle", NULL, NULL);
}

static void
create_page3()
{
	ui_view_lifecycle_callback_s event_callback = {0, };
	event_callback.load = view3_load_cb;

	ui_view *view = ui_view_create(NULL, "page3", NULL, &event_callback);
	// Does it change to like below?
	//ui_view *view = ui_view_create(NULL, "page1", &event_callback, &data);

	UI_VIEWMGR_VIEW_PUSH(view);
}

static void
view2_prev_btn_clicked_cb(void *data, Evas_Object *obj, void *event_info)
{
	UI_VIEWMGR_VIEW_POP();
}

static void
view2_next_btn_clicked_cb(void *data, Evas_Object *obj, void *event_info)
{
	create_page3();
}

static void
view2_load_cb(void *data, ui_view *view)
{
	ui_view_on_load();

	Evas_Object *base_layout = ui_view_base_layout_get(view);

	Evas_Object *content = create_content(base_layout, "ViewMgr Demo<br>Title Buttons",
			view2_prev_btn_clicked_cb, view2_next_btn_clicked_cb, data);

	//Title left button
	Elm_Button *left_title_btn = elm_button_add(this->get_base());
	elm_object_text_set(left_title_btn, "Cancel");

	//Title right button
	Elm_Button *right_title_btn = elm_button_add(this->get_base());
	elm_object_text_set(right_title_btn, "Done");

	ui_view_content_set(view, content, "Page2", NULL, left_title_btn, right_title_btn);
}

static void
create_page2()
{
	ui_view_lifecycle_callback_s event_callback = {0, };
	event_callback.load = view2_load_cb;

	ui_view *view = ui_view_create(NULL, "page2", NULL, &event_callback);
	// Does it change to like below?
	//ui_view *view = ui_view_create(NULL, "page1", &event_callback, &data);

	UI_VIEWMGR_VIEW_PUSH(view);
}

static void
view1_prev_btn_clicked_cb(void *data, Evas_Object *obj, void *event_info)
{
	UI_VIEWMGR_DEACTIVATE();
}

static void
view1_next_btn_clicked_cb(void *data, Evas_Object *obj, void *event_info)
{
	create_page2();
}

static void
view1_load_cb(void *data, ui_view *view)
{
	ui_view_on_load(view);

	Evas_Object *base_layout = ui_view_base_layout_get(view);

	Evas_Object *content = create_content(base_layout, "ViewMgr Demo<br>Page 1",
			view1_prev_btn_clicked_cb, view1_next_btn_clicked_cb, data);

	ui_view_content_set(view, content, "Page1", NULL, NULL, NULL);
}

static void
create_page1()
{
	ui_view_lifecycle_callback_s event_callback = {0, };
	event_callback.load = view1_load_cb;

	ui_view *view = ui_view_create(NULL, "page1", &event_callback);
	// Does it change to like below?
	//ui_view *view = ui_view_create(NULL, "page1", &event_callback, &data);

	UI_VIEWMGR_VIEW_PUSH(view);
}

static bool
app_create(void *data)
{
	if (!ui_app_on_create()) return false;

	create_page1();

	return true;
}

int
main(int argc, char *argv[])
{
	appdata_s *ad = {0,};

	// Should ad send to ui_app to allocation?
	// Like this ui_app_add(PACKAGE, LOCALE_DIR, ad);
	ad = calloc(1, sizeof(appdata_s));

	//We need to define ui_app class for CAPIs.
	ui_app_lifecycle_callback_s event_callback = {0,};

	event_callback.create = app_create;
	event_callback.terminate = app_terminate;
	event_callback.pause = app_pause;
	event_callback.resume = app_resume;
	event_callback.app_control = app_control;

	//does ret value need?
	int ret = ui_app_init(PACKAGE, LOCALE_DIR);

	app_event_handler_h handlers[5] = {NULL, };

	ui_app_add_event_handler(&handlers[APP_EVENT_LOW_BATTERY], APP_EVENT_LOW_BATTERY, ui_app_low_battery, &ad);
	ui_app_add_event_handler(&handlers[APP_EVENT_LOW_MEMORY], APP_EVENT_LOW_MEMORY, ui_app_low_memory, &ad);
	ui_app_add_event_handler(&handlers[APP_EVENT_DEVICE_ORIENTATION_CHANGED], APP_EVENT_DEVICE_ORIENTATION_CHANGED, ui_app_orient_changed, &ad);
	ui_app_add_event_handler(&handlers[APP_EVENT_LANGUAGE_CHANGED], APP_EVENT_LANGUAGE_CHANGED, ui_app_lang_changed, &ad);
	ui_app_add_event_handler(&handlers[APP_EVENT_REGION_FORMAT_CHANGED], APP_EVENT_REGION_FORMAT_CHANGED, ui_app_region_changed, &ad)


	return ui_app_run(argc, argv, &event_callback, &ad);
}
