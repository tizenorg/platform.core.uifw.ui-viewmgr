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
view8_prev_btn_clicked_cb(void *data, Evas_Object *obj, void *event_info)
{
	UI_VIEWMGR_VIEW_POP();
}

static void
view8_next_btn_clicked_cb(void *data, Evas_Object *obj, void *event_info)
{
	create_page9();
}

void
create_page8()
{
	ui_view *view = ui_standard_view_create("page8");

	Evas_Object *base_layout = ui_view_base_get(view);

	Evas_Object *content = create_content(base_layout, "ViewMgr Demo<br>Content Preload",
			view8_prev_btn_clicked_cb, view8_next_btn_clicked_cb);

	ui_view_removable_content_set(view, false);
	ui_standard_view_content_set(view, content, "Page8", NULL, NULL, NULL);

	UI_VIEWMGR_VIEW_PUSH(view);
}
