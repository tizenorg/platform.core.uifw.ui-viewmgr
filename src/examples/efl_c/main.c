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
_view1_prev_btn_clicked_cb(void *data, Evas_Object *obj, void *event_info)
{
	appdata_s *ad = (appdata_s *)data;

	 ui_viewmgr_deactivate(ad->viewmgr);
}

static void
_view1_next_btn_clicked_cb(void *data, Evas_Object *obj, void *event_info)
{
	appdata_s *ad = (appdata_s *)data;

	 //create_page2(ad);
}

static bool
_view1_load_cb(void *data, ui_view *view, void *event_info)
{
	appdata_s *ad = data;
	Evas_Object *base_layout = ui_view_base_layout_get(ad->view1);

	Evas_Object *content = create_content(base_layout, "ViewMgr Demo<br>Page 1",
			_view1_prev_btn_clicked_cb, _view1_next_btn_clicked_cb, ad);

	ui_view_content_set(ad->view1, content, "title", NULL, NULL, NULL);

	return true;
}

static void
create_page1(appdata_s *ad)
{
	ad->view1 = ui_view_add(NULL, "page1");
	ui_view_event_callback_add(ad->view1, "load", _view1_load_cb, ad);

	ui_viewmgr_view_push(ad->viewmgr, ad->view1);
}

static bool
_on_create(void *data)
{
	appdata_s *ad = data;
	if (!ui_app_on_create(ad->app))
		return false;

	//Push first view in viewmgr.
	ad->viewmgr = ui_app_viewgmr_get(ad->app);
	create_page1(ad);

	return true;
}

int
main(int argc, char *argv[])
{
	appdata_s *ad = {0,};

	// Should ad send to ui_app to allocation?
	// Like this ui_app_add(PACKAGE, LOCALE_DIR, ad);
	ad = calloc(1, sizeof(appdata_s));

	ad->app = ui_app_add(PACKAGE, LOCALE_DIR);

	ui_app_event_callback_add(ad->app, "on_create", _on_create, ad);

	return ui_app_run(ad->app);
}
