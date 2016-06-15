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
view15_btn_clicked_cb(void *data, Evas_Object *obj, void *event_info)
{
	create_page16();
}

static bool
view15_load_cb(ui_view *view, void *data)
{
	Evas_Object *content = NULL;
	Evas_Object *base = NULL;

	//Get a base object from view.
	base = ui_view_base_get(view);
	if (!base)
	{
		dlog_print(DLOG_ERROR, LOG_TAG, "failed to get a view base object");
		return false;
	}

	//Create and set a main content.
	content = create_scrolling_content(base);
	if (!content) return false;

	ui_standard_view_content_set(view, content, "Page 15 Scroller In Viewmgr", NULL, NULL, NULL);

	//Title Right button
	Elm_Button *right_btn = elm_button_add(base);
	elm_object_text_set(right_btn, "Next");
	evas_object_smart_callback_add(right_btn, "clicked", view15_btn_clicked_cb, NULL);

	ui_standard_view_title_right_btn_set(view, right_btn);

	return true;
}

void
create_page15()
{
	int ret = 0;
	ui_view *view = NULL;
	ui_view_lifecycle_callback_s lifecycle_callback = {0, };

	view = ui_standard_view_create("page15");
	if (!view)
	{
		dlog_print(DLOG_ERROR, LOG_TAG, "failed to create a view");
		return;
	}

	//Set View Life-Cycle callbacks.
	lifecycle_callback.load = view15_load_cb;
	if (!(ret = ui_view_lifecycle_callbacks_set(view, &lifecycle_callback, NULL)))
	{
		dlog_print(DLOG_ERROR, LOG_TAG, "ui_view_lifecycle_callback_set is failed. err = %d", ret);
		ui_view_destroy(view);
		return;
	}

	UI_VIEWMGR_VIEW_PUSH(view);
}

