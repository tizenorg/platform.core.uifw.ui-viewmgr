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
#include "../../include/efl/ui_viewmanager_base.h"

using namespace efl_viewmgr;

static bool update_popup(ui_base_popup *popup)
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
	ui_base_popup *popup = static_cast<ui_base_popup *>(data);
	popup->unset_content();
}

ui_base_popup::ui_base_popup(ui_base_view *view)
		: view(view), popup(NULL)
{
	view->connect_popup(this);
}

ui_base_popup::~ui_base_popup()
{
	this->view->disconnect_popup(this);
	evas_object_del(this->popup);
}

Elm_Win *ui_base_popup::get_window()
{
	ui_base_viewmgr *viewmgr = dynamic_cast<ui_base_viewmgr *>(this->view->get_viewmgr());
	if (!viewmgr)
	{
		LOGE("Viewmgr is null?? menu(%p)", this);
		return NULL;
	}
	return viewmgr->get_window();
}

bool ui_base_popup::deactivate()
{
	if (!this->popup)
	{
		LOGE("Content is not set! = ui_base_popup(%p)", this);
		return false;
	}

	elm_popup_dismiss(this->popup);
	this->view->on_resume();

	return true;
}

bool ui_base_popup::activate()
{
	bool ret = update_popup(this);
	if (ret) this->view->on_pause();
	return ret;
}

bool ui_base_popup::set_content(Elm_Popup *popup)
{
	evas_object_del(this->popup);

	//validation!
	//FIXME: isa ?
	if (strcmp(evas_object_type_get(popup), "elm_popup"))
	{
		LOGE("Menu widget is not a popup!");
		return false;
	}

	//FIXME: rename style.
	evas_object_event_callback_add(popup, EVAS_CALLBACK_DEL, popup_del_cb, this);
	evas_object_smart_callback_add(popup, "dismissed", popup_dismissed_cb, this);

	this->popup = popup;

	return true;
}

bool ui_base_popup::is_activated()
{
	if (!this->popup) return false;
	return evas_object_visible_get(this->popup);
}

Elm_Popup *ui_base_popup::unset_content()
{
	if (!this->popup) return NULL;

	Elm_Popup *prev = this->popup;
	this->popup = NULL;
	evas_object_event_callback_del(prev, EVAS_CALLBACK_DEL, popup_del_cb);
	evas_object_smart_callback_del(prev, "dismissed", popup_dismissed_cb);
	return prev;
}

Evas_Object *ui_base_popup::get_base()
{
	if (!this->view)
	{
		LOGE("View is null?? menu(%p)", this);
		return NULL;
	}

	return this->get_window();
}

void ui_base_popup::on_back()
{
	this->deactivate();
}

int ui_base_popup::get_degree()
{
	return this->view->get_degree();
}
