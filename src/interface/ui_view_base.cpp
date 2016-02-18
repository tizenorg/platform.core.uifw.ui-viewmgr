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
#include "ui_viewmgr.h"

void ui_view_base::set_event_block(bool block)
{
	this->event_block = block;
}

void ui_view_base::load()
{
	this->state = UI_VIEW_STATE_LOAD;
	if (this->content) return;
	if (!this->controller) return;
	this->controller->load();
}

void ui_view_base::unload()
{
	this->state = UI_VIEW_STATE_UNLOAD;
	if (this->get_removable_content())
	{
		this->unload_content();
		return;
	}
	if (!this->content) return;
	if (!this->controller) return;
	this->controller->unload();
}

void ui_view_base::active()
{
	this->state = UI_VIEW_STATE_ACTIVE;
	if (!this->controller) return;
	this->controller->active();
}

void ui_view_base::inactive()
{
	this->state = UI_VIEW_STATE_INACTIVE;
	if (!this->controller) return;
	this->controller->inactive();
}

void ui_view_base::pause()
{
	this->state = UI_VIEW_STATE_PAUSE;
	if (!this->content) return;
	if (state != UI_VIEW_STATE_ACTIVE) return;
	if (!this->controller) return;
	this->controller->pause();
}

void ui_view_base::resume()
{
	this->state = UI_VIEW_STATE_ACTIVE;
	if (state != UI_VIEW_STATE_PAUSE) return;
	if (!this->content) return;
	if (!this->controller) return;
	this->controller->resume();
}

void ui_view_base::destroy()
{
	if (!this->controller) return;
	this->controller->destroy();
}

ui_view_base::ui_view_base(T content, ui_controller_base *controller, const char *name)
		: content(content), controller(controller), name(string(name ? name : "")), style(string("")), viewmgr(NULL), state(UI_VIEW_STATE_LOAD),
		  indicator(UI_VIEW_INDICATOR_DEFAULT), event_block(false), removable_content(true)
{
	if (!content) this->state = UI_VIEW_STATE_UNLOAD;
	else this->state = UI_VIEW_STATE_LOAD;
	controller->set_view(this);
}

ui_view_base::ui_view_base(ui_controller_base *controller, const char *name)
		: ui_view_base(NULL, controller, name)
{
	this->state = UI_VIEW_STATE_UNLOAD;
}

ui_view_base::ui_view_base(const char *name)
		: ui_view_base(NULL, name)
{

}

ui_view_base::~ui_view_base()
{
	this->viewmgr->remove_view(this);
	if (this->controller) delete (this->controller);
}

ui_controller_base* ui_view_base::set_controller(ui_controller_base *controller)
{
	ui_controller_base *prev_controller = this->controller;
	this->controller = controller;
	if (controller) controller->set_view(this);
	if (prev_controller) prev_controller->set_view(NULL);
	return prev_controller;
}

T ui_view_base::set_content(T content)
{
	T prev = this->content;
	this->content = content;
	return prev;
}

bool ui_view_base::set_style(const char *style)
{
	this->style.assign(style);
	return true;
}

void ui_view_base::set_removable_content(bool removable)
{
	this->removable_content = removable;

	//FIXME: If this api is called on unload state? should we remove content right now?
}

void ui_view_base::set_indicator(ui_view_indicator indicator)
{
	this->indicator = indicator;
}
