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
	create_page3();
}

static bool
view2_load_cb(ui_standard_view *view, void *data)
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

	//Create and set a main content.
	content = create_content(base, "ViewMgr Demo<br>Title Buttons", prev_btn_clicked_cb, next_btn_clicked_cb);
	if (!content) return false;

	//Title left button
	Elm_Button *left_title_btn = elm_button_add(base);
	elm_object_text_set(left_title_btn, "Cancel");

	//Title right button
	Elm_Button *right_title_btn = elm_button_add(base);
	elm_object_text_set(right_title_btn, "Done");

	//Set available rotation only "0, 90" of this view
	const int rots[2] = { 0, 90 };
	ui_view_set_available_rotations(view, rots, 2);

	if (!ui_standard_view_set_content(view, content) ||
	    !ui_standard_view_set_title(view, "Page2") ||
	    !ui_standard_view_set_title_left_btn(view, left_title_btn) ||
	    !ui_standard_view_set_title_right_btn(view, right_title_btn))
	{
		dlog_print(DLOG_ERROR, LOG_TAG, "failed to set view property");
		return false;
	}

	return true;
}

void
create_page2()
{
	int ret = 0;
	ui_standard_view *view = NULL;
	ui_view_lifecycle_callback_s lifecycle_callback = {0, };

	//Create a view.
	view = ui_standard_view_create("page2");
	if (!view)
	{
		dlog_print(DLOG_ERROR, LOG_TAG, "failed to create a view");
		return;
	}

	//Set View Life-Cycle callbacks.
	lifecycle_callback.load = view2_load_cb;
	if (!(ret = ui_view_set_lifecycle_callbacks(view, &lifecycle_callback, NULL)))
	{
		dlog_print(DLOG_ERROR, LOG_TAG, "ui_view_lifecycle_callback_set() is failed. err = %d", ret);
		ui_view_destroy(view);
		return;
	}

	UI_VIEWMGR_PUSH_VIEW(view);
}
