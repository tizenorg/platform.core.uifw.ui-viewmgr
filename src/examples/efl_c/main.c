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

static void
view11_prev_btn_clicked_cb(void *data, Evas_Object *obj, void *event_info)
{
	UI_VIEWMGR_VIEW_POP();
}

static void
view11_next_btn_clicked_cb(void *data, Evas_Object *obj, void *event_info)
{
	create_page12();
}

static void
view11_load_cb(ui_view *view, void *data)
{
	Evas_Object *base_layout = ui_view_base_get(view);

	Evas_Object *content = create_content(base_layout, "ViewMgr Demo<br>Menu Popup",
			view11_prev_btn_clicked_cb, view11_next_btn_clicked_cb);

	ui_standard_view_content_set(view, content, "Page11");
}

static void ctxpopup_item_select_cb(void *data, Evas_Object *obj, void *event_info)
{
	Elm_Object_Item *it = event_info;
	elm_ctxpopup_dismiss(obj);
	LOGE("Item (%s) is selected", elm_object_item_text_get(it));
}

//Basically the menu cb has ui_menu instance for param.
static void
view11_menu_cb(ui_view *view, void *data)
{
	Elm_Ctxpopup *ctxpopup = elm_ctxpopup_add(menu->get_base());
	elm_ctxpopup_item_append(ctxpopup, "Phone calls", NULL, ctxpopup_item_select_cb, this);
	elm_ctxpopup_item_append(ctxpopup, "Favorites", NULL, ctxpopup_item_select_cb, this);
	elm_ctxpopup_item_append(ctxpopup, "Search", NULL, ctxpopup_item_select_cb, this);
	elm_ctxpopup_item_append(ctxpopup, "Dialer", NULL, ctxpopup_item_select_cb, this);
	elm_ctxpopup_item_append(ctxpopup, "Add contact", NULL, ctxpopup_item_select_cb, this);
	elm_ctxpopup_item_append(ctxpopup, "Phone calls", NULL, ctxpopup_item_select_cb, this);
	elm_ctxpopup_item_append(ctxpopup, "Favorites", NULL, ctxpopup_item_select_cb, this);
	elm_ctxpopup_item_append(ctxpopup, "Search", NULL, ctxpopup_item_select_cb, this);
	elm_ctxpopup_item_append(ctxpopup, "Dialer", NULL, ctxpopup_item_select_cb, this);

	ui_menu_content_set(menu, ctxpopup);
}

static void
create_page11()
{
	ui_view_lifecycle_callback_s lifecycle_callback = {0, };
	//ui_view_event_callback_s event_callback = {0, };

	//Does it menu can belong to lifecycle callback?
	lifecycle_callback.load = view11_load_cb;
	lifecycle_callback.menu = view11_menu_cb;

	ui_view *view = ui_standard_view_create(NULL, "page11");

	int ret = ui_view_lifecycle_callbacks_set(view, &lifecycle_callback, NULL);
	if (ret != 0)
	{
		//TODO
	}

	UI_VIEWMGR_VIEW_PUSH(view);
}

//================================================================================
//================================== View 10 ======================================
//================================================================================

static void
view10_prev_btn_clicked_cb(void *data, Evas_Object *obj, void *event_info)
{
	UI_VIEWMGR_VIEW_POP();
}

static void
view10_next_btn_clicked_cb(void *data, Evas_Object *obj, void *event_info)
{
	create_page11();
}

//Basically the rotate cb has degree value for param.
static void
view10_rotate_cb(ui_view *view, void *data)
{
	Evas_Object *base_layout = ui_view_base_get(view);

	if (ui_view_degree_get(view) == 0 || ui_view_degree_get(view) == 180)
	{
		Evas_Object *content = create_content(base_layout, "ViewMgr Demo<br>Rotation",
				view10_prev_btn_clicked_cb, view10_next_btn_clicked_cb);

		ui_standard_view_content_set(view, content, "Page10");
		ui_view_indicator_set(view, UI_VIEW_INDICATOR_DEFAULT);
	}
	else
	{
		Evas_Object *content = create_content(base_layout, "ViewMgr Demo<br>Rotation",
				view10_prev_btn_clicked_cb, view10_next_btn_clicked_cb);

		ui_standard_view_content_set(view, content, "Page10");
		ui_view_indicator_set(view, UI_VIEW_INDICATOR_OPTIMAL);
	}
}

static void
view10_load_cb(ui_view *view, void *data)
{
	view10_rotate_cb(view, data);
}

static void
create_page10()
{
	ui_view_lifecycle_callback_s lifecycle_callback = {0, };
	//ui_view_event_callback_s event_callback = {0, };

	lifecycle_callback.load = view10_load_cb;
	//Does it rotate can belong to lifecycle callback?
	lifecycle_callback.rotate = view10_rotate_cb;

	ui_view *view = ui_standard_view_create(NULL, "page10");

	int ret = ui_view_lifecycle_callbacks_set(view, &lifecycle_callback, NULL);
	if (ret != 0)
	{
		//TODO
	}

	UI_VIEWMGR_VIEW_PUSH(view);
}

//================================================================================
//================================== View 9 ======================================
//================================================================================

static void
view9_prev_btn_clicked_cb(void *data, Evas_Object *obj, void *event_info)
{
	UI_VIEWMGR_VIEW_POP();
}

static void
view9_next_btn_clicked_cb(void *data, Evas_Object *obj, void *event_info)
{
	create_page10();
}

static void
view9_portrait_cb(ui_view *view, void *data)
{
	Evas_Object *base_layout = ui_view_base_get(view);

	Evas_Object *content = create_content(base_layout, "ViewMgr Demo<br>Portrait/Landscape",
			view9_prev_btn_clicked_cb, view9_next_btn_clicked_cb);

	ui_standard_view_content_set(view, content, "Page9");
	ui_view_indicator_set(view, UI_VIEW_INDICATOR_DEFAULT);
}

static void
view9_landscape_cb(ui_view *view, void *data)
{
	Evas_Object *base_layout = ui_view_base_get(view);

	Evas_Object *content = create_content(base_layout, "ViewMgr Demo<br>Portrait/Landscape",
			view9_prev_btn_clicked_cb, view9_next_btn_clicked_cb);

	ui_standard_view_content_set(view, content, "Page9");
	ui_view_indicator_set(view, UI_VIEW_INDICATOR_OPTIMAL);
}

static void
view9_load_cb(ui_view *view, void *data)
{
	if (ui_view_degree_get(view) == 90 || ui_view_degree_get(view) == 270)
		view9_landscape_cb(view, data);
	else
		view9_portrait_cb(view, data);
}

static void
create_page9()
{
	ui_view_lifecycle_callback_s lifecycle_callback = {0, };
	//ui_view_event_callback_s event_callback = {0, };

	lifecycle_callback.load = view9_load_cb;
	//Does it portrait can belong to lifecycle callback?
	lifecycle_callback.portrait = view9_portrait_cb;
	lifecycle_callback.landscape = view9_landscape_cb;

	ui_view *view = ui_standard_view_create(NULL, "page9");

	int ret = ui_view_lifecycle_callbacks_set(view, &lifecycle_callback, NULL);
	if (ret != 0)
	{
		//TODO
	}

	UI_VIEWMGR_VIEW_PUSH(view);
}

//================================================================================
//================================== View 8 ======================================
//================================================================================

static void
view8_prev_btn_clicked_cb(void *data, Evas_Object *obj, void *event_info)
{
	UI_VIEWMGR_VIEW_POP();
}

static void
view8_next_btn_clicked_cb(void *data, Evas_Object *obj, void *event_info)
{
	create_page9();
}

static void
create_page8()
{
	ui_view_lifecycle_callback_s lifecycle_callback = {0, };
	//ui_view_event_callback_s event_callback = {0, };

	//Content is not need when view create...
	ui_view *view = ui_standard_view_create("page7");

	Evas_Object *base_layout = ui_view_base_get(view);

	Evas_Object *content = create_content(base_layout, "ViewMgr Demo<br>Content Preload",
			view8_prev_btn_clicked_cb, view8_next_btn_clicked_cb);

	ui_view_removable_content(view, false);
	ui_standard_view_content_set(view, content, "Page7");

	UI_VIEWMGR_VIEW_PUSH(view);
}

//================================================================================
//================================== View 7 ======================================
//================================================================================

static void
view7_prev_btn_clicked_cb(void *data, Evas_Object *obj, void *event_info)
{
	UI_VIEWMGR_VIEW_POP();
}

static void
view7_next_btn_clicked_cb(void *data, Evas_Object *obj, void *event_info)
{
	create_page8();
}

static void
view7_load_cb(ui_view *view, void *data)
{
	Evas_Object *base_layout = ui_view_base_get(view);

	Evas_Object *content = create_content(base_layout, "ViewMgr Demo<br>Navigationbarr",
			view7_prev_btn_clicked_cb, view7_next_btn_clicked_cb);

	ui_standard_view_content_set(view, content, "Page7");
	Elm_Toolbar *toolbar = create_toolbar(base_layout, "navigarionbar");
	ui_standard_view_toolbar_set(view, toolbar);
}

static void
create_page7()
{
	ui_view_lifecycle_callback_s lifecycle_callback = {0, };
	//ui_view_event_callback_s event_callback = {0, };

	lifecycle_callback.load = view7_load_cb;

	ui_view *view = ui_standard_view_create(NULL, "page7");

	int ret = ui_view_lifecycle_callbacks_set(view, &lifecycle_callback, NULL);
	if (ret != 0)
	{
		//TODO
	}

	UI_VIEWMGR_VIEW_PUSH(view);
}

//================================================================================
//================================== View 6 ======================================
//================================================================================

static void
view6_prev_btn_clicked_cb(void *data, Evas_Object *obj, void *event_info)
{
	UI_VIEWMGR_VIEW_POP();
}

static void
view6_next_btn_clicked_cb(void *data, Evas_Object *obj, void *event_info)
{
	create_page7();
}

static void
view6_load_cb(ui_view *view, void *data)
{
	Evas_Object *base_layout = ui_view_base_get(view);

	Evas_Object *content = create_content(base_layout, "ViewMgr Demo<br>Toolbar",
			view6_prev_btn_clicked_cb, view6_next_btn_clicked_cb);

	ui_standard_view_content_set(view, content, "Page6");
	Elm_Toolbar *toolbar = create_toolbar(base_layout, "toolbar_with_title");
	ui_standard_view_toolbar_set(view, toolbar);
}

static void
create_page6()
{
	ui_view_lifecycle_callback_s lifecycle_callback = {0, };
	//ui_view_event_callback_s event_callback = {0, };

	lifecycle_callback.load = view6_load_cb;

	ui_view *view = ui_standard_view_create(NULL, "page6");

	int ret = ui_view_lifecycle_callbacks_set(view, &lifecycle_callback, NULL);
	if (ret != 0)
	{
		//TODO
	}

	UI_VIEWMGR_VIEW_PUSH(view);
}

//================================================================================
//================================== View 5 ======================================
//================================================================================

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
view5_load_cb(ui_view *view, void *data)
{
	ui_view_on_load();

	Evas_Object *base_layout = ui_view_base_layout_get(view);

	Evas_Object *content = create_content(base_layout, "ViewMgr Demo<br>Full View",
			view5_prev_btn_clicked_cb, view5_next_btn_clicked_cb);

	ui_view_content_set(view, content);
	ui_view_indicator_set(view, UI_VIEW_INDICATOR_HIDE);
}

static void
create_page5()
{
	ui_view_lifecycle_callback_s lifecycle_callback = {0, };
	//ui_view_event_callback_s event_callback = {0, };

	lifecycle_callback.load = view5_load_cb;

	ui_view *view = ui_view_create(NULL, "page5");

	int ret = ui_view_lifecycle_callbacks_set(view, &lifecycle_callback, NULL);
	if (ret != 0)
	{
		//TODO
	}

	UI_VIEWMGR_VIEW_PUSH(view);
}

//================================================================================
//================================== View 4 ======================================
//================================================================================

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
view4_load_cb(ui_view *view, void *data)
{
	Evas_Object *base_layout = ui_view_base_get(view);

	Evas_Object *content = create_content(base_layout, "ViewMgr Demo<br>Title Badge",
			view4_prev_btn_clicked_cb, view4_next_btn_clicked_cb);

	ui_standard_view_content_set(view, content, "Page4 We put a long title here intentionally");
	ui_standard_view_title_badge_set(view, "999+");
}

static void
create_page4()
{
	ui_view_lifecycle_callback_s lifecycle_callback = {0, };
	//ui_view_event_callback_s event_callback = {0, };

	lifecycle_callback.load = view4_load_cb;

	ui_view *view = ui_standard_view_create(NULL, "page4");

	int ret = ui_view_lifecycle_callbacks_set(view, &lifecycle_callback, NULL);
	if (ret != 0)
	{
		//TODO
	}

	UI_VIEWMGR_VIEW_PUSH(view);
}

//================================================================================
//================================== View 3 ======================================
//================================================================================

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
view3_load_cb(ui_view *view, void *data)
{
	Evas_Object *base_layout = ui_view_base_get(view);

	Evas_Object *content = create_content(base_layout, "ViewMgr Demo<br>Subtitle",
			view3_prev_btn_clicked_cb, view3_next_btn_clicked_cb);

	ui_standard_view_content_set(view, content, "Page3", "Subtitle", NULL, NULL);
}

static void
create_page3()
{
	ui_view_lifecycle_callback_s lifecycle_callback = {0, };
	//ui_view_event_callback_s event_callback = {0, };

	lifecycle_callback.load = view3_load_cb;

	ui_view *view = ui_standard_view_create(NULL, "page3");

	int ret = ui_view_lifecycle_callbacks_set(view, &lifecycle_callback, NULL);
	if (ret != 0)
	{
		//TODO
	}

	UI_VIEWMGR_VIEW_PUSH(view);
}

//================================================================================
//================================== View 2 ======================================
//================================================================================

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
view2_load_cb(ui_view *view, void *data)
{
	Evas_Object *base_layout = ui_view_base_get(view);

	Evas_Object *content = create_content(base_layout, "ViewMgr Demo<br>Title Buttons",
			view2_prev_btn_clicked_cb, view2_next_btn_clicked_cb);

	//Title left button
	Elm_Button *left_title_btn = elm_button_add(this->get_base());
	elm_object_text_set(left_title_btn, "Cancel");

	//Title right button
	Elm_Button *right_title_btn = elm_button_add(this->get_base());
	elm_object_text_set(right_title_btn, "Done");

	ui_standard_view_content_set(view, content, "Page2", NULL, left_title_btn, right_title_btn);
}

static void
create_page2()
{
	ui_view_lifecycle_callback_s lifecycle_callback = {0, };
	//ui_view_event_callback_s event_callback = {0, };

	lifecycle_callback.load = view2_load_cb;

	ui_view *view = ui_standard_view_create(NULL, "page2");

	int ret = ui_view_lifecycle_callbacks_set(view, &lifecycle_callback, NULL);
	if (ret != 0)
	{
		//TODO
	}

	UI_VIEWMGR_VIEW_PUSH(view);
}

//================================================================================
//================================== View 1 ======================================
//================================================================================

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
view1_load_cb(ui_view *view, void *data)
{
	Evas_Object *base_layout = ui_view_base_get(view);

	Evas_Object *content = create_content(base_layout, "ViewMgr Demo<br>Page 1",
			view1_prev_btn_clicked_cb, view1_next_btn_clicked_cb);

	ui_standard_view_content_set(view, content, "Page1", NULL, NULL, NULL);
}

static void
create_page1()
{
	ui_view_lifecycle_callback_s lifecycle_callback = {0, };
	//ui_view_event_callback_s event_callback = {0, };

	lifecycle_callback.load = view1_load_cb;

	ui_view *view = ui_standard_view_create(NULL, "page1");

	int ret = ui_view_lifecycle_callbacks_set(view, &lifecycle_callback, NULL);
	if (ret != 0)
	{
		//TODO
	}

	UI_VIEWMGR_VIEW_PUSH(view);
}

static bool
app_create(void *data)
{
	create_page1();

	return true;
}

int
main(int argc, char *argv[])
{
	appdata_s ad = {0,};
	int ret;

	ui_app_lifecycle_callback_s event_callback = {0,};

	event_callback.create = app_create;
	event_callback.terminate = app_terminate;
	event_callback.pause = app_pause;
	event_callback.resume = app_resume;
	event_callback.app_control = app_control;

	int ret = ui_app_init(PACKAGE, LOCALE_DIR);
	if (ret != 0)
	{
		//TODO
		return ret;
	}

	app_event_handler_h handlers[5] = {NULL, };

	ui_app_add_event_handler(&handlers[APP_EVENT_LOW_BATTERY], APP_EVENT_LOW_BATTERY, ui_app_low_battery, &ad);
	ui_app_add_event_handler(&handlers[APP_EVENT_LOW_MEMORY], APP_EVENT_LOW_MEMORY, ui_app_low_memory, &ad);
	ui_app_add_event_handler(&handlers[APP_EVENT_DEVICE_ORIENTATION_CHANGED], APP_EVENT_DEVICE_ORIENTATION_CHANGED, ui_app_orient_changed, &ad);
	ui_app_add_event_handler(&handlers[APP_EVENT_LANGUAGE_CHANGED], APP_EVENT_LANGUAGE_CHANGED, ui_app_lang_changed, &ad);
	ui_app_add_event_handler(&handlers[APP_EVENT_REGION_FORMAT_CHANGED], APP_EVENT_REGION_FORMAT_CHANGED, ui_app_region_changed, &ad)


	return ui_app_run(argc, argv, &event_callback, &ad);
}
