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

static bool
view10_rotate_cb(ui_view *view, int degree, void *data)
{
	Evas_Object *base_layout = ui_view_base_get(view);

	if (degree == 0 || degree == 180)
	{
		Evas_Object *content = create_content(base_layout, "ViewMgr Demo<br>Rotation",
				view10_prev_btn_clicked_cb, view10_next_btn_clicked_cb);

		ui_standard_view_content_set(view, content, "Page10", NULL, NULL, NULL);
		ui_view_indicator_set(view, UI_VIEW_INDICATOR_DEFAULT);
	}
	else
	{
		Evas_Object *content = create_landscape_content(base_layout, "ViewMgr Demo<br>Rotation",
				view10_prev_btn_clicked_cb, view10_next_btn_clicked_cb);

		ui_standard_view_content_set(view, content, "Page10", NULL, NULL, NULL);
		ui_view_indicator_set(view, UI_VIEW_INDICATOR_OPTIMAL);
	}

	return true;
}

static bool
view10_load_cb(ui_view *view, void *data)
{
	view10_rotate_cb(view, ui_view_degree_get(view), data);

	return true;
}

void
create_page10()
{
	ui_view_lifecycle_callback_s lifecycle_callback = {0, };
	ui_view_event_callback_s event_callback = {0, };

	lifecycle_callback.load = view10_load_cb;
	event_callback.rotate = view10_rotate_cb;

	ui_view *view = ui_standard_view_create("page10");

	int ret = ui_view_lifecycle_callbacks_set(view, &lifecycle_callback, NULL);
	if (ret != 0)
	{
		//TODO
	}

	ret = ui_view_event_callbacks_set(view, &event_callback, NULL);
	if (ret != 0)
	{
		//TODO
	}

	UI_VIEWMGR_VIEW_PUSH(view);
}
