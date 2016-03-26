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

static void popup_del_cb(void *data, Evas *e, Evas_Object *obj, void *event_info)
{
	ui_popup *popup = static_cast<ui_popup *>(data);
	popup->unset_content();
}

ui_popup::ui_popup(ui_view *view)
		: view(view), popup(NULL)
{
}

ui_popup::~ui_popup()
{
	Elm_Win *win = this->get_window();
	evas_object_del(this->popup);
}

Elm_Win *ui_popup::get_window()
{
	ui_viewmgr *viewmgr = dynamic_cast<ui_viewmgr *>(this->view->get_viewmgr());
	if (!viewmgr)
	{
		LOGE("Viewmgr is null?? menu(%p)", this);
		return NULL;
	}
	return viewmgr->get_window();
}

bool ui_popup::deactivate()
{
	if (this->popup)
	{
		evas_object_hide(this->popup);
	}
	else
	{
		LOGE("Content is not set! = ui_popup(%p)", this);
		return false;
	}

	this->view->on_resume();

	return true;
}

bool ui_popup::activate()
{
	bool ret = update_popup(this);
	if (ret) this->view->on_pause();
	return ret;
}

bool ui_popup::set_content(Elm_Popup *popup)
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

	this->popup = popup;

	return true;
}

bool ui_popup::is_activated()
{
	if (!this->popup) return false;
	return evas_object_visible_get(this->popup);
}

Elm_Popup *ui_popup::unset_content()
{
	if (!this->popup) return NULL;

	Elm_Popup *prev = this->popup;
	this->popup = NULL;
	evas_object_event_callback_del(prev, EVAS_CALLBACK_DEL, popup_del_cb);
	return prev;
}

Evas_Object *ui_popup::get_base()
{
	if (!this->view)
	{
		LOGE("View is null?? menu(%p)", this);
		return NULL;
	}

	return this->get_window();
}

void ui_popup::on_back()
{
	this->deactivate();
}

int ui_popup::get_degree()
{
	return this->view->get_degree();
}
