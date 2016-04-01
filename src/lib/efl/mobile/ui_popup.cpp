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
#include "../../../include/efl/mobile/ui_viewmanager.h"

using namespace efl_viewmgr;

static bool update_popup(ui_popup *popup)
{
	Elm_Win *win = popup->get_base();
	if (!win) return false;

	Elm_Popup *_popup = popup->get_content();
	if (!_popup) return false;

	evas_object_show(_popup);

	return true;
}

static void popup_dismissed_cb(void *data, Evas_Object *obj, void *event_info)
{
	evas_object_hide(obj);
}

static void popup_del_cb(void *data, Evas *e, Evas_Object *obj, void *event_info)
{
	ui_popup *popup = static_cast<ui_popup *>(data);
	popup->unset_content();
}

ui_popup::ui_popup(ui_view *view)
		: ui_iface_overlay(view)
{
	view->connect_popup(this);
}

ui_popup::~ui_popup()
{
	dynamic_cast<ui_view *>(this->get_view())->disconnect_popup(this);
	Elm_Popup *popup = this->unset_content();
	evas_object_del(popup);
}

Elm_Win *ui_popup::get_window()
{
	ui_viewmgr *viewmgr = UI_VIEWMGR;
	if (!viewmgr)
	{
		LOGE("Viewmgr is null?? menu(%p)", this);
		return NULL;
	}
	return viewmgr->get_window();
}

bool ui_popup::deactivate()
{
	Elm_Popup *popup = this->get_content();
	if (!popup)
	{
		LOGE("Content is not set! = ui_popup(%p)", this);
		return false;
	}

	elm_popup_dismiss(popup);
	dynamic_cast<ui_view*>(this->get_view())->on_resume();

	return true;
}

bool ui_popup::activate()
{
	bool ret = update_popup(this);
	if (ret) dynamic_cast<ui_view*>(this->get_view())->on_pause();
	return ret;
}

bool ui_popup::set_content(Elm_Popup *popup)
{
	Elm_Popup *prev = this->unset_content();
	evas_object_del(prev);

	if (!popup) return true;

	//validation!
	//FIXME: isa ?
	if (strcmp(evas_object_type_get(popup), "elm_popup"))
	{
		LOGE("Menu widget is not a popup!");
		return false;
	}

	elm_popup_align_set(popup, ELM_NOTIFY_ALIGN_FILL, 1.0);

	//FIXME: rename style.
	evas_object_event_callback_add(popup, EVAS_CALLBACK_DEL, popup_del_cb, this);
	evas_object_smart_callback_add(popup, "dismissed", popup_dismissed_cb, this);

	ui_iface_overlay::set_content(popup);

	return true;
}

bool ui_popup::is_activated()
{
	Elm_Popup *popup = this->get_content();
	if (!popup) return false;
	return evas_object_visible_get(popup);
}

Elm_Popup *ui_popup::unset_content()
{
	Elm_Popup *popup = ui_iface_overlay::unset_content();
	if (!popup) return NULL;

	evas_object_event_callback_del(popup, EVAS_CALLBACK_DEL, popup_del_cb);
	evas_object_smart_callback_del(popup, "dismissed", popup_dismissed_cb);

	return popup;
}

Evas_Object *ui_popup::get_base()
{
	return this->get_window();
}

int ui_popup::get_degree()
{
	return this->get_view()->get_degree();
}
