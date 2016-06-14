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
view11_prev_btn_clicked_cb(void *data, Evas_Object *obj, void *event_info)
{
	UI_VIEWMGR_VIEW_POP();
}

static void
view11_next_btn_clicked_cb(void *data, Evas_Object *obj, void *event_info)
{
	create_page12();
}

static bool
view11_load_cb(ui_view *view, void *data)
{
	Evas_Object *base_layout = ui_view_base_get(view);

	Evas_Object *content = create_content(base_layout, "ViewMgr Demo<br>Menu Popup",
			view11_prev_btn_clicked_cb, view11_next_btn_clicked_cb);

	ui_standard_view_content_set(view, content, "Page11", NULL, NULL, NULL);

	return true;
}

static void ctxpopup_item_select_cb(void *data, Evas_Object *obj, void *event_info)
{
	Elm_Object_Item *it = static_cast<Elm_Object_Item *>(event_info);
	elm_ctxpopup_dismiss(obj);
	LOGE("Item (%s) is selected", elm_object_item_text_get(it));
}

static bool
view11_menu_cb(ui_menu *menu, void *data)
{
	Elm_Ctxpopup *ctxpopup = elm_ctxpopup_add(menu->get_base());
	elm_ctxpopup_item_append(ctxpopup, "Phone calls", NULL, ctxpopup_item_select_cb, NULL);
	elm_ctxpopup_item_append(ctxpopup, "Favorites", NULL, ctxpopup_item_select_cb, NULL);
	elm_ctxpopup_item_append(ctxpopup, "Search", NULL, ctxpopup_item_select_cb, NULL);
	elm_ctxpopup_item_append(ctxpopup, "Dialer", NULL, ctxpopup_item_select_cb, NULL);
	elm_ctxpopup_item_append(ctxpopup, "Add contact", NULL, ctxpopup_item_select_cb, NULL);
	elm_ctxpopup_item_append(ctxpopup, "Phone calls", NULL, ctxpopup_item_select_cb, NULL);
	elm_ctxpopup_item_append(ctxpopup, "Favorites", NULL, ctxpopup_item_select_cb, NULL);
	elm_ctxpopup_item_append(ctxpopup, "Search", NULL, ctxpopup_item_select_cb, NULL);
	elm_ctxpopup_item_append(ctxpopup, "Dialer", NULL, ctxpopup_item_select_cb, NULL);

	ui_menu_content_set(menu, ctxpopup);

	return true;
}

void
create_page11()
{
	ui_view_lifecycle_callback_s lifecycle_callback = {0, };
	ui_view_event_callback_s event_callback = {0, };

	lifecycle_callback.load = view11_load_cb;
	event_callback.menu = view11_menu_cb;

	ui_view *view = ui_standard_view_create("page11");

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
