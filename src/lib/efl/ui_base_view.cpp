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
#include "../../include/efl/ui_base_viewmanager.h"

using namespace efl_viewmgr;
using namespace viewmgr;

typedef list<ui_base_popup*>::reverse_iterator popup_ritr;

static void content_del_cb(void *data, Evas *e, Evas_Object *obj, void *event_info)
{
	ui_base_view *view = static_cast<ui_base_view *>(data);
	view->unset_content();
}

void ui_base_view::connect_popup(ui_base_popup *popup)
{
	this->popup_list.push_back(popup);
}

void ui_base_view::disconnect_popup(ui_base_popup *popup)
{
	this->popup_list.remove(popup);
}

ui_base_view::ui_base_view(const char *name)
		: ui_iface_view(name)
{
}

ui_base_view::~ui_base_view()
{
}

bool ui_base_view::set_content(Evas_Object *content)
{
	Evas_Object *pcontent = this->unset_content();
	if (pcontent)
	{
		evas_object_del(pcontent);
	}
	if (content)
	{
		evas_object_event_callback_add(content, EVAS_CALLBACK_DEL, content_del_cb, this);
		ui_iface_view::set_content(CONVERT_TO_T(content));
	}
	return true;
}

Evas_Object *ui_base_view::unset_content()
{
	T pcontent = ui_iface_view::unset_content();
	if (pcontent)
	{
		Evas_Object *obj = CONVERT_TO_EO(pcontent);
		evas_object_event_callback_del(obj, EVAS_CALLBACK_DEL, content_del_cb);
		evas_object_hide(obj);
		return obj;
	}
	return NULL;
}

Evas_Object *ui_base_view::get_base()
{
	ui_base_viewmgr *viewmgr = UI_BASE_VIEWMGR;
	if (!viewmgr)
	{
		return NULL;
	}
	return viewmgr->get_base();
}

//FIXME: seems it could be replaced with set_content(NULL);
void ui_base_view::unload_content()
{
	T pcontent = this->get_content();
	if (pcontent) evas_object_del(CONVERT_TO_EO(pcontent));
	this->set_content(NULL);
}

Evas_Object *ui_base_view ::get_parent()
{
	ui_base_viewmgr *viewmgr = UI_BASE_VIEWMGR;
	if (!viewmgr)
	{
		LOGE("Failed to get a viewmgr");
		return NULL;
	}
	return viewmgr->get_base();
}

void ui_base_view::set_indicator(ui_view_indicator indicator)
{
	if (this->get_indicator() == indicator) return;

	ui_iface_view::set_indicator(indicator);

	ui_base_viewmgr *viewmgr = UI_BASE_VIEWMGR;
	if (!viewmgr)
	{
		LOGE("Failed to get a viewmgr");
		return;
	}

	if (!viewmgr->is_activated()) return;

	if (dynamic_cast<ui_base_view *>(viewmgr->get_last_view()) != this) return;

	viewmgr->set_indicator(indicator);
}

bool ui_base_view::deactivate_popup(bool top_one)
{
	for (popup_ritr it = this->popup_list.rbegin(); it != this->popup_list.rend(); it++)
	{
		ui_base_popup *popup = *it;
		if (!popup->is_activated()) continue;
		popup->on_back();
		//deactivate only one top one? or all popups?
		if (top_one) return true;
	}
	return false;
}

void ui_base_view::on_deactivate()
{
	deactivate_popup(false);
	ui_iface_view::on_deactivate();
}

void ui_base_view::on_back()
{
	//If any popup is activated, deactivate the popup first.
	if (this->deactivate_popup(true)) return;

	ui_base_viewmgr *viewmgr = UI_BASE_VIEWMGR;
	if (!viewmgr)
	{
		LOGE("Failed to get a viewmgr");
		return;
	}
	viewmgr->pop_view();
}

void ui_base_view::on_rotate(int degree)
{
}

void ui_base_view::on_portrait()
{
}

void ui_base_view::on_landscape()
{
}

void ui_base_view::set_event_block(bool block)
{
	ui_iface_view::set_event_block(block);
	evas_object_freeze_events_set(CONVERT_TO_EO(this->get_content()), block);
}

int ui_base_view::get_degree()
{
	ui_base_viewmgr *viewmgr = UI_BASE_VIEWMGR;
	if (!viewmgr)
	{
		LOGE("Failed to get a viewmgr");
		return -1;
	}
	return elm_win_rotation_get(viewmgr->get_window());
}
