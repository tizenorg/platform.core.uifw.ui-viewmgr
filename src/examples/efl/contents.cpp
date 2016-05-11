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
	Elm_Image *image;

	/* Image */
	image = elm_image_add(parent);
	snprintf(buf, sizeof(buf), "%s/data/images/bg.png", BINDIR);
	elm_image_file_set(image, buf, NULL);
	elm_image_resizable_set(image, EINA_FALSE, EINA_FALSE);
	evas_object_show(image);

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
create_title_handle_content(Evas_Object *parent, Evas_Smart_Cb prev_btn_clicked_cb, Evas_Smart_Cb next_btn_clicked_cb,
				Evas_Smart_Cb title_show_btn_clicked_cb, Evas_Smart_Cb title_hide_btn_clicked_cb,
				Evas_Smart_Cb title_show_anim_btn_clicked_cb, Evas_Smart_Cb title_hide_anim_btn_clicked_cb, ui_view *view)
{
	Elm_Grid *grid;
	Elm_Box *box;
	Elm_Layout *layout;
	Elm_Button *btn;

	/* Grid */
	grid = elm_grid_add(parent);
	evas_object_size_hint_weight_set(grid, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_size_hint_align_set(grid, EVAS_HINT_FILL, EVAS_HINT_FILL);
	evas_object_show(grid);

	/* NoContent Layout */
	layout = elm_layout_add(grid);
	elm_layout_theme_set(layout, "layout", "nocontents", "default");
	elm_object_part_text_set(layout, "elm.text", NULL);
	evas_object_show(layout);
	elm_grid_pack(grid, layout, 0, 0, 100, 100);

	/* Box */
	box = elm_box_add(grid);
	//elm_box_horizontal_set(box, EINA_TRUE);
	evas_object_size_hint_weight_set(box, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_size_hint_align_set(box, EVAS_HINT_FILL, EVAS_HINT_FILL);
	//elm_box_padding_set(box, ELM_SCALE_SIZE(50), 0);
	evas_object_show(box);
	elm_grid_pack(grid, box, 25, 15, 50, 50);

	/* Title Show Button */
	btn = elm_button_add(grid);
	evas_object_size_hint_weight_set(btn, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_size_hint_align_set(btn, EVAS_HINT_FILL, 1.0);
	elm_object_text_set(btn, "Title Show");
	evas_object_smart_callback_add(btn, "clicked", title_show_btn_clicked_cb, view);
	evas_object_show(btn);
	elm_box_pack_end(box, btn);

	/* Title Hide Button */
	btn = elm_button_add(grid);
	evas_object_size_hint_weight_set(btn, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_size_hint_align_set(btn, EVAS_HINT_FILL, 1.0);
	elm_object_text_set(btn, "Title Hide");
	evas_object_smart_callback_add(btn, "clicked", title_hide_btn_clicked_cb, view);
	evas_object_show(btn);
	elm_box_pack_end(box, btn);

	/* Title Show Anim Button */
	btn = elm_button_add(grid);
	evas_object_size_hint_weight_set(btn, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_size_hint_align_set(btn, EVAS_HINT_FILL, 1.0);
	elm_object_text_set(btn, "Title Show Anim");
	evas_object_smart_callback_add(btn, "clicked", title_show_anim_btn_clicked_cb, view);
	evas_object_show(btn);
	elm_box_pack_end(box, btn);

	/* Title Hide Anim Button */
	btn = elm_button_add(grid);
	evas_object_size_hint_weight_set(btn, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_size_hint_align_set(btn, EVAS_HINT_FILL, 1.0);
	elm_object_text_set(btn, "Title Hide Anim");
	evas_object_smart_callback_add(btn, "clicked", title_hide_anim_btn_clicked_cb, view);
	evas_object_show(btn);
	elm_box_pack_end(box, btn);

	/* Box */
	box = elm_box_add(grid);
	elm_box_horizontal_set(box, EINA_TRUE);
	evas_object_size_hint_weight_set(box, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_size_hint_align_set(box, EVAS_HINT_FILL, 1.0);
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

	return grid;
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
