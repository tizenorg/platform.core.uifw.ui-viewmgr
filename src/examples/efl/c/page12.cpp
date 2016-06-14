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
view12_prev_btn_clicked_cb(void *data, Evas_Object *obj, void *event_info)
{
	UI_VIEWMGR_VIEW_POP();
}

static void
view12_next_btn_clicked_cb(void *data, Evas_Object *obj, void *event_info)
{
	create_page13();
}

static void
popup_block_clicked_cb(void *data, Evas_Object *obj, void *event_info)
{
	elm_popup_dismiss(obj);
}

static void
popup_timeout_cb(void *data, Evas_Object *obj, void *event_info)
{
	elm_popup_dismiss(obj);
}

static void
popup_dismissed_cb(void *data, Evas_Object *obj, void *event_info)
{
	//FIXME: remove dismissed callback because this callback is called twice.
	//It seems this is an efl or popup error, not this ui_popup nor example.
	evas_object_smart_callback_del(obj, "dismissed", popup_dismissed_cb);
	ui_popup *popup = static_cast<ui_popup *>(data);

	//Is It right?
	ui_popup_del(popup);
}

static void
view12_btn_clicked(void *data, Evas_Object *obj, void *event_info)
{
	ui_view *view = static_cast<ui_view *>(data);

	//Create popup.
	//FIXME: is overlay a proper name?
	ui_popup *popup = ui_popup_create(view);

	Elm_Popup *elm_popup = elm_popup_add(ui_view_base_get(view));
	elm_object_text_set(elm_popup, "This popup has only text which is set via desc set function, (This popup gets hidden when user clicks outside) here timeout of 3 sec is set.");
	elm_popup_timeout_set(elm_popup, 3.0);
	evas_object_smart_callback_add(elm_popup, "dismissed", popup_dismissed_cb, popup);
	evas_object_smart_callback_add(elm_popup, "block,clicked", popup_block_clicked_cb, NULL);
	evas_object_smart_callback_add(elm_popup, "timeout", popup_timeout_cb, NULL);

	ui_popup_content_set(popup, elm_popup);
	ui_popup_activate(popup);
}

static bool
view12_load_cb(ui_view *view, void *data)
{
	Evas_Object *base_layout = ui_view_base_get(view);

	Evas_Object *content = create_content(base_layout, "ViewMgr Demo<br>Popup",
			view12_prev_btn_clicked_cb, view12_next_btn_clicked_cb);

	ui_standard_view_content_set(view, content, "Page12", NULL, NULL, NULL);

	//Title Right button
	Elm_Button *right_btn = elm_button_add(base_layout);
	elm_object_text_set(right_btn, "popup");
	evas_object_smart_callback_add(right_btn, "clicked", view12_btn_clicked, view);

	ui_standard_view_title_right_btn_set(view, right_btn);

	return true;
}

void
create_page12()
{
	ui_view_lifecycle_callback_s lifecycle_callback = {0, };
	lifecycle_callback.load = view12_load_cb;

	ui_view *view = ui_standard_view_create("page12");

	int ret = ui_view_lifecycle_callbacks_set(view, &lifecycle_callback, NULL);
	if (ret != 0)
	{
		//TODO
	}

	UI_VIEWMGR_VIEW_PUSH(view);
}
