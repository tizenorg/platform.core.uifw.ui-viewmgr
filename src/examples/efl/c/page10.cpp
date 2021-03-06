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
prev_btn_clicked_cb(void *data, Evas_Object *obj, void *event_info)
{
	UI_VIEWMGR_POP_VIEW();
}

static void
next_btn_clicked_cb(void *data, Evas_Object *obj, void *event_info)
{
	create_page11();
}

static bool
view10_rotate_cb(ui_standard_view *view, int degree, void *data)
{
	Evas_Object *content = NULL;
	Evas_Object *base = NULL;

	//Get a base object from view.
	base = ui_view_get_base(view);
	if (!base)
	{
		dlog_print(DLOG_ERROR, LOG_TAG, "failed to get a view base object");
		return false;
	}

	//Check orientation manually to create a content.
	if (ui_view_get_orientation_mode(view) == UI_VIEW_ORIENTATION_MODE_PORTRAIT)
	{
		//Portrait
		content = create_content(base, "ViewMgr Demo<br>Rotation", prev_btn_clicked_cb, next_btn_clicked_cb);
		if (!content) return false;
		ui_view_set_indicator(view, UI_VIEW_INDICATOR_DEFAULT);
	} else {
		//Landscape
		content = create_landscape_content(base, "ViewMgr Demo<br>Rotation", prev_btn_clicked_cb, next_btn_clicked_cb);
		if (!content) return false;
		ui_view_set_indicator(view, UI_VIEW_INDICATOR_OPTIMAL);
	}

	if (!ui_view_set_content(view, content) ||
	    !ui_standard_view_set_title(view, "Page10"))
	{
		dlog_print(DLOG_ERROR, LOG_TAG, "failed to set view property");
		return false;
	}

	return true;
}

static bool
view10_load_cb(ui_standard_view *view, void *data)
{
	return view10_rotate_cb(view, ui_view_get_degree(view), data);
}

void
create_page10()
{
	int ret = 0;
	ui_standard_view *view = NULL;
	ui_view_lifecycle_callback_s lifecycle_callback = {0, };
	ui_view_event_callback_s event_callback = {0, };

	//Create a view.
	view = ui_standard_view_create("page10");
	if (!view)
	{
		dlog_print(DLOG_ERROR, LOG_TAG, "failed to create a view");
		return;
	}

	//Set View Life-Cycle callbacks.
	lifecycle_callback.load = view10_load_cb;
	if (!(ret = ui_view_set_lifecycle_callbacks(view, &lifecycle_callback, NULL)))
	{
		dlog_print(DLOG_ERROR, LOG_TAG, "ui_view_lifecycle_callback_set is failed. err = %d", ret);
		ui_view_destroy(view);
		return;
	}

	//Set Rotation Event callbacks.
	event_callback.rotate = view10_rotate_cb;
	if (!(ret = ui_view_set_event_callbacks(view, &event_callback, NULL)))
	{
		dlog_print(DLOG_ERROR, LOG_TAG, "ui_view_event_callback_set is failed. err = %d", ret);
	}

	UI_VIEWMGR_PUSH_VIEW(view);
}
