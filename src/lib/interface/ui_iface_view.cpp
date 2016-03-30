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
#include "../../include/interface/ui_iface_viewmanager.h"

using namespace viewmgr;

void ui_iface_view::set_event_block(bool block)
{
	this->event_block = block;
}

void ui_iface_view::on_load()
{
	this->state = UI_VIEW_STATE_LOAD;
}

void ui_iface_view::on_unload()
{
	this->state = UI_VIEW_STATE_UNLOAD;
	if (this->get_removable_content())
	{
		this->unload_content();
		return;
	}
}

void ui_iface_view::on_activate()
{
	this->state = UI_VIEW_STATE_ACTIVATE;
}

void ui_iface_view::on_deactivate()
{
	this->state = UI_VIEW_STATE_DEACTIVATE;
}

void ui_iface_view::on_pause()
{
	this->state = UI_VIEW_STATE_PAUSE;
}

void ui_iface_view::on_resume()
{
	this->state = UI_VIEW_STATE_ACTIVATE;
}

void ui_iface_view::on_destroy()
{
}

ui_iface_view::ui_iface_view(const char *name)
		: content(NULL), name(string(name ? name : "")), transition_style(string("default")), viewmgr(NULL), state(UI_VIEW_STATE_LOAD),
		  indicator(UI_VIEW_INDICATOR_DEFAULT), event_block(false), removable_content(true)
{
	this->state = UI_VIEW_STATE_UNLOAD;
}

ui_iface_view::~ui_iface_view()
{
	this->viewmgr->remove_view(this);
}

T ui_iface_view::set_content(T content)
{
	T prev = this->content;
	this->content = content;
	return prev;
}

T ui_iface_view::unset_content()
{
	T prev = this->content;
	this->content = NULL;
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
