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
using namespace viewmgr;

#define MY_CONTROLLER dynamic_cast<ui_base_controller *>(this->get_controller())
#define MY_VIEWMGR dynamic_cast<ui_base_viewmgr *>(this->get_viewmgr())
typedef list<ui_base_popup*>::reverse_iterator popup_ritr;

void ui_base_view::connect_popup(ui_base_popup *popup)
{
	this->popup_list.push_back(popup);
}

void ui_base_view::disconnect_popup(ui_base_popup *popup)
{
	this->popup_list.remove(popup);
}

ui_base_view::ui_base_view(ui_base_controller *controller, const char *name)
		: ui_iface_view(controller, name)
{
}

ui_base_view::ui_base_view(const char *name)
		: ui_base_view(NULL, name)
{
}

ui_base_view::~ui_base_view()
{
}

bool ui_base_view::set_content(Evas_Object *content)
{
	T pcontent = this->get_content();
	if (pcontent) evas_object_del(CONVERT_TO_EO(pcontent));
	if (content) ui_iface_view::set_content(CONVERT_TO_T(content));
	else ui_iface_view::set_content(NULL);
	return true;
}

Evas_Object *ui_base_view::unset_content()
{
	T pcontent = ui_iface_view::unset_content();
	return CONVERT_TO_EO(pcontent);
}

Evas_Object *ui_base_view::get_base()
{
	ui_base_viewmgr *viewmgr = MY_VIEWMGR;
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
	ui_base_viewmgr *viewmgr = MY_VIEWMGR;
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

	ui_base_viewmgr *viewmgr = MY_VIEWMGR;

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

	if (this->get_controller())
	{
		if (!MY_CONTROLLER->on_back())
		{
			return;
		}
	}
	MY_VIEWMGR->pop_view();
}

void ui_base_view::on_rotate(int degree)
{
	if (!this->get_controller()) return;
	MY_CONTROLLER->on_rotate(degree);
}

void ui_base_view::on_portrait()
{
	if (!this->get_controller()) return;
	MY_CONTROLLER->on_portrait();
}

void ui_base_view::on_landscape()
{
	if (!this->get_controller()) return;
	MY_CONTROLLER->on_landscape();
}
void ui_base_view::set_event_block(bool block)
{
	ui_iface_view::set_event_block(block);
	evas_object_freeze_events_set(CONVERT_TO_EO(this->get_content()), block);
}

int ui_base_view::get_degree()
{
	ui_base_viewmgr *viewmgr = MY_VIEWMGR;
	if (!viewmgr)
	{
		LOGE("Failed to get a viewmgr");
		return -1;
	}
	return elm_win_rotation_get(viewmgr->get_window());
}
