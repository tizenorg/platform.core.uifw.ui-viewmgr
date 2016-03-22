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
#include "../../include/interface/ui_viewmanager_interface.h"

using namespace viewmgr;

void ui_iface_view::set_event_block(bool block)
{
	this->event_block = block;
}

void ui_iface_view::on_load()
{
	this->state = UI_VIEW_STATE_LOAD;
	if (this->content) return;
	if (!this->controller) return;
	this->controller->on_load();
}

void ui_iface_view::on_unload()
{
	this->state = UI_VIEW_STATE_UNLOAD;
	if (this->get_removable_content())
	{
		this->unload_content();
		return;
	}
	if (!this->content) return;
	if (!this->controller) return;
	this->controller->on_unload();
}

void ui_iface_view::on_active()
{
	this->state = UI_VIEW_STATE_ACTIVE;
	if (!this->controller) return;
	this->controller->on_active();
}

void ui_iface_view::on_inactive()
{
	this->state = UI_VIEW_STATE_INACTIVE;
	if (!this->controller) return;
	this->controller->on_inactive();
}

void ui_iface_view::on_pause()
{
	this->state = UI_VIEW_STATE_PAUSE;
	if (!this->content) return;
	if (state != UI_VIEW_STATE_ACTIVE) return;
	if (!this->controller) return;
	this->controller->on_pause();
}

void ui_iface_view::on_resume()
{
	this->state = UI_VIEW_STATE_ACTIVE;
	if (state != UI_VIEW_STATE_PAUSE) return;
	if (!this->content) return;
	if (!this->controller) return;
	this->controller->on_resume();
}

void ui_iface_view::on_destroy()
{
	if (!this->controller) return;
	this->controller->on_destroy();
}

ui_iface_view::ui_iface_view(ui_iface_controller *controller, const char *name)
		: content(NULL), controller(controller), name(string(name ? name : "")), transition_style(string("default")), viewmgr(NULL), state(UI_VIEW_STATE_LOAD),
		  indicator(UI_VIEW_INDICATOR_DEFAULT), event_block(false), removable_content(true)
{
	this->state = UI_VIEW_STATE_UNLOAD;

	if (controller)
		controller->set_view(this);
}

ui_iface_view::ui_iface_view(const char *name)
		: ui_iface_view(NULL, name)
{

}

ui_iface_view::~ui_iface_view()
{
	this->viewmgr->remove_view(this);
	if (this->controller) delete (this->controller);
}

ui_iface_controller* ui_iface_view::set_controller(ui_iface_controller *controller)
{
	ui_iface_controller *prev_controller = this->controller;
	this->controller = controller;
	if (controller) controller->set_view(this);
	if (prev_controller) prev_controller->set_view(NULL);
	return prev_controller;
}

T ui_iface_view::set_content(T content)
{
	T prev = this->content;
	this->content = content;
	return prev;
}

bool ui_iface_view::set_transition_style(const char *style)
{
	this->transition_style.assign(style);
	return true;
}

bool ui_iface_view::set_name(const char *name)
{
	this->name.assign(name);
	return true;
}

void ui_iface_view::set_removable_content(bool removable)
{
	this->removable_content = removable;

	//FIXME: If this api is called on unload state? should we remove content right now?
}

void ui_iface_view::set_indicator(ui_view_indicator indicator)
{
	this->indicator = indicator;
}
