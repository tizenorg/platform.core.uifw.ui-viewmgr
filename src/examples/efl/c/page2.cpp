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
view2_prev_btn_clicked_cb(void *data, Evas_Object *obj, void *event_info)
{
	UI_VIEWMGR_VIEW_POP();
}

static void
view2_next_btn_clicked_cb(void *data, Evas_Object *obj, void *event_info)
{
	create_page3();
}

static bool
view2_load_cb(ui_view *view, void *data)
{
	Evas_Object *base_layout = ui_view_base_get(view);

	Evas_Object *content = create_content(base_layout, "ViewMgr Demo<br>Title Buttons",
			view2_prev_btn_clicked_cb, view2_next_btn_clicked_cb);

	//Title left button
	Elm_Button *left_title_btn = elm_button_add(base_layout);
	elm_object_text_set(left_title_btn, "Cancel");

	//Title right button
	Elm_Button *right_title_btn = elm_button_add(base_layout);
	elm_object_text_set(right_title_btn, "Done");

	ui_standard_view_content_set(view, content, "Page2", NULL, left_title_btn, right_title_btn);

	return true;
}

void
create_page2()
{
	ui_view_lifecycle_callback_s lifecycle_callback = {0, };

	lifecycle_callback.load = view2_load_cb;

	ui_view *view = ui_standard_view_create("page2");

	int ret = ui_view_lifecycle_callbacks_set(view, &lifecycle_callback, NULL);
	if (!ret)
	{
		dlog_print(DLOG_ERROR, LOG_TAG, "ui_view_lifecycle_callback_set is failed. err = %d", ret);
	}

	UI_VIEWMGR_VIEW_PUSH(view);
}
