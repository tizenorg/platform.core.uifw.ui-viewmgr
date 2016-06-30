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
	create_page9();
}

void
create_page8()
{
	ui_standard_view *view = NULL;
	Evas_Object *base = NULL;
	Evas_Object *content = NULL;

	//Create a view.
	view = ui_standard_view_create("page8");
	if (!view)
	{
		dlog_print(DLOG_ERROR, LOG_TAG, "failed to create a view");
		return;
	}

	//Get a base object from view.
	base = ui_view_get_base(view);
	if (!base)
	{
		dlog_print(DLOG_ERROR, LOG_TAG, "failed to get a view base object");
		ui_view_destroy(view);
		return;
	}

	//Create and set a main content in advance.
	content = create_content(base, "ViewMgr Demo<br>Content Preload", prev_btn_clicked_cb, next_btn_clicked_cb);
	if (!content)
	{
		ui_view_destroy(view);
		return;
	}

	if (!ui_standard_view_set_content(view, content, "Page8", NULL, NULL, NULL))
	{
		dlog_print(DLOG_ERROR, LOG_TAG, "failed to set view content");
		ui_view_destroy(view);
		return;
	}

	//Don't delete view's content when this view popped.
	//This is a show case for saving this content for reuse later.
	ui_view_set_removable_content(view, false);


	UI_VIEWMGR_PUSH_VIEW(view);
}
