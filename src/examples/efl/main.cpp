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
#include "page7.h"
#include "page6.h"
#include "page5.h"
#include "page4.h"
#include "page3.h"
#include "page2.h"
#include "page1.h"

Evas_Object*
create_toolbar(Evas_Object *parent, const char *style)
{
	Evas_Object *toolbar;

	toolbar = elm_toolbar_add(parent);

	//FIXME: :( UI_View can set this style instead.
	elm_object_style_set(toolbar, style);
	elm_toolbar_shrink_mode_set(toolbar, ELM_TOOLBAR_SHRINK_EXPAND);
	elm_toolbar_transverse_expanded_set(toolbar, EINA_TRUE);

	elm_toolbar_item_append(toolbar, NULL, "Tab1", NULL, NULL);
	elm_toolbar_item_append(toolbar, NULL, "Tab2", NULL, NULL);

	if (!strcmp(style, "navigationbar"))
	{
		elm_toolbar_shrink_mode_set(toolbar, ELM_TOOLBAR_SHRINK_SCROLL);
		elm_toolbar_align_set(toolbar, 0.0);
		elm_toolbar_item_append(toolbar, NULL, "Tab3", NULL, NULL);
		elm_toolbar_item_append(toolbar, NULL, "Tab4", NULL, NULL);
	}

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
	evas_object_smart_callback_add(btn, "clicked", prev_btn_clicked_cb, ad);
	evas_object_show(btn);
	elm_box_pack_end(box, btn);

	/* Next Page Button */
	btn = elm_button_add(grid);
	evas_object_size_hint_weight_set(btn, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_size_hint_align_set(btn, EVAS_HINT_FILL, 1.0);
	elm_object_text_set(btn, "Next");
	evas_object_smart_callback_add(btn, "clicked", next_btn_clicked_cb, ad);
	evas_object_show(btn);
	elm_box_pack_end(box, btn);

	elm_object_content_set(scroller, grid);

	return scroller;
}

static void create_base_gui(appdata_s *ad)
{
	//FIXME: Hide this creation.
	ad->viewmgr = new ui_basic_viewmgr(PACKAGE);

	create_page1(ad);

	ad->viewmgr->activate();
}

int
elm_main(int argc, char **argv)
{
	appdata_s *ad = {0,};

	ad = static_cast<appdata_s *>(calloc(1, sizeof(appdata_s)));
	create_base_gui(ad);

	elm_run();
	elm_shutdown();
	return 0;
}
ELM_MAIN()

