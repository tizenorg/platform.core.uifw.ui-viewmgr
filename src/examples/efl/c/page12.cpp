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
	UI_VIEWMGR_VIEW_POP();
}

static void
next_btn_clicked_cb(void *data, Evas_Object *obj, void *event_info)
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
	evas_object_smart_callback_del(obj, "dismissed", popup_dismissed_cb);

	//Destroy ui_popup
	ui_popup *popup = (ui_popup *) data;
	ui_popup_destroy(popup);
}

static void
view12_btn_clicked(void *data, Evas_Object *obj, void *event_info)
{
	ui_standard_view *view = NULL;
	ui_popup *popup = NULL;
	Evas_Object *base = NULL;
	Elm_Popup *content = NULL;

	view = (ui_standard_view *) data;

	//Create a popup.
	if (!(popup = ui_popup_create(view)))
	{
		dlog_print(DLOG_ERROR, LOG_TAG, "failed to create a ui_popup");
		return;
	}

	//Get a base object from popup.
	base = ui_popup_base_get(popup);
	if (!base)
	{
		dlog_print(DLOG_ERROR, LOG_TAG, "failed to get a view base object");
		return;
	}

	//Create a popup object.
	if (!(content = elm_popup_add(base)))
	{
		dlog_print(DLOG_ERROR, LOG_TAG, "failed to create a popup object");
		return;
	}
	elm_object_text_set(content, "This popup has only text which is set via desc set function, (This popup gets hidden when user clicks outside) here timeout of 3 sec is set.");
	elm_popup_timeout_set(content, 3.0);
	evas_object_smart_callback_add(content, "dismissed", popup_dismissed_cb, popup);
	evas_object_smart_callback_add(content, "block,clicked", popup_block_clicked_cb, NULL);
	evas_object_smart_callback_add(content, "timeout", popup_timeout_cb, NULL);

	//Set elm popup as a ui_popup content.
	ui_popup_content_set(popup, content);
	ui_popup_activate(popup);
}

static bool
view12_load_cb(ui_standard_view *view, void *data)
{
	Evas_Object *content = NULL;
	Evas_Object *base = NULL;
	Elm_Button *right_btn = NULL;

	//Get a base object from view.
	base = ui_view_base_get(view);
	if (!base)
	{
		dlog_print(DLOG_ERROR, LOG_TAG, "failed to get a view base object");
		return false;
	}

	//Create and set a main content.
	content = create_content(base, "ViewMgr Demo<br>Popup", prev_btn_clicked_cb, next_btn_clicked_cb);
	if (!content) return false;

	ui_standard_view_content_set(view, content, "Page12", NULL, NULL, NULL);

	//Title Right button
	right_btn = elm_button_add(base);
	elm_object_text_set(right_btn, "popup");
	evas_object_smart_callback_add(right_btn, "clicked", view12_btn_clicked, view);

	ui_standard_view_title_right_btn_set(view, right_btn);

	return true;
}

void
create_page12()
{
	int ret = 0;
	ui_standard_view *view = NULL;
	ui_view_lifecycle_callback_s lifecycle_callback = {0, };

	//Create a view
	view = ui_standard_view_create("page12");
	if (!view)
	{
		dlog_print(DLOG_ERROR, LOG_TAG, "failed to create a view");
		return;
	}

	//Set View Life-Cycle callbacks.
	lifecycle_callback.load = view12_load_cb;
	if (!(ret = ui_view_lifecycle_callbacks_set(view, &lifecycle_callback, NULL)))
	{
		dlog_print(DLOG_ERROR, LOG_TAG, "ui_view_lifecycle_callback_set is failed. err = %d", ret);
		ui_view_destroy(view);
		return;
	}

	UI_VIEWMGR_VIEW_PUSH(view);
}
