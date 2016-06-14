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
	//FIXME: deactivate??? or ui_app deactivate??? or ui_viewmgr pop???
	UI_VIEWMGR_DEACTIVATE();
}

static void
next_btn_clicked_cb(void *data, Evas_Object *obj, void *event_info)
{
	create_page2();
}

static bool
load_cb(ui_view *view, void *data)
{
	Evas_Object *content;
	Evas_Object *base;

	base = ui_view_base_get(view);
	if (!base) return false;

	content = create_content(base, "ViewMgr Demo<br>Basic View", prev_btn_clicked_cb, next_btn_clicked_cb);
	ui_standard_view_content_set(view, content, "Page1", NULL, NULL, NULL);

	return true;
}

void
create_page1()
{
	int ret;
	ui_view *view;
	ui_view_lifecycle_callback_s lifecycle_callback = {0, };

	view = ui_standard_view_create("page1");
	if (!view)
	{
		dlog_print(DLOG_ERROR, LOG_TAG, "failed to create a view");
		return;
	}

	lifecycle_callback.load = view1_load_cb;

	if (!ui_view_lifecycle_callbacks_set(view, &lifecycle_callback, NULL))
	{
		dlog_print(DLOG_ERROR, LOG_TAG, "ui_view_lifecycle_callback_set is failed. err = %d", ret);
		ui_view_destroy(view);
		return;
	}

	UI_VIEWMGR_VIEW_PUSH(view);
}
