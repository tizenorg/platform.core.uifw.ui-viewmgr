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

#include <string>

using namespace std;

/***********************************************************************************************/
/* Internal class Implementation                                                               */
/***********************************************************************************************/
namespace ui_viewmanager
{

class ui_iface_view_impl
{
	friend class ui_iface_viewmgr_impl;
	friend class ui_iface_view;

private:
	ui_iface_view *view;
	T content;                              ///< A content instance for a screen as a view.
	string name;                            ///< View name.
	string transition_style;                ///< View transition style name.
	ui_iface_viewmgr *viewmgr;              ///< Viewmgr which this view belongs to.
	ui_view_state state;                    ///< View state.
	ui_view_indicator indicator;            ///< View indicator mode.
	bool event_block;                       ///< State of event block.
	bool removable_content;                 ///< When this value is true, view removes it's content internally on unload state.

public:
	void set_event_block(bool block);
	void on_load();
	void on_unload();
	void on_activate();
	void on_deactivate();
	void on_pause();
	void on_resume();
	void on_destroy();
	bool get_event_block();
	bool set_content(T content);
	T unset_content();

	ui_iface_view_impl(ui_iface_view *view, const char *name);
	~ui_iface_view_impl();

	bool set_transition_style(const char *style);
	bool set_name(const char *name);
	void set_removable_content(bool removable);
	void set_indicator(ui_view_indicator indicator);
	const char *get_transition_style();
	const char *get_name();
	T get_content();
	ui_view_state get_state();
	bool get_removable_content();
	ui_view_indicator get_indicator();
	void on_back();
};

}

bool ui_iface_view_impl::get_event_block()
{
	return this->event_block;
}

void ui_iface_view_impl::set_event_block(bool block)
{
	this->event_block = block;
}

void ui_iface_view_impl::on_load()
{
	this->state = UI_VIEW_STATE_LOAD;
}

void ui_iface_view_impl::on_unload()
{
	this->state = UI_VIEW_STATE_UNLOAD;
	if (this->get_removable_content())
	{
		this->set_content(NULL);
		return;
	}
}

void ui_iface_view_impl::on_activate()
{
	this->state = UI_VIEW_STATE_ACTIVATE;
}

void ui_iface_view_impl::on_deactivate()
{
	this->state = UI_VIEW_STATE_DEACTIVATE;
}

void ui_iface_view_impl::on_pause()
{
	this->state = UI_VIEW_STATE_PAUSE;
}

void ui_iface_view_impl::on_resume()
{
	this->state = UI_VIEW_STATE_ACTIVATE;
}

void ui_iface_view_impl::on_destroy()
{

}

ui_iface_view_impl::ui_iface_view_impl(ui_iface_view *view, const char *name)
		: view(view), content(NULL), name(string(name ? name : "")), transition_style(string("default")), viewmgr(NULL), state(UI_VIEW_STATE_LOAD),
		  indicator(UI_VIEW_INDICATOR_DEFAULT), event_block(false), removable_content(true)
{
	this->state = UI_VIEW_STATE_UNLOAD;
}

ui_iface_view_impl::~ui_iface_view_impl()
{
	this->viewmgr->remove_view(this->view);
}

bool ui_iface_view_impl::set_content(T content)
{
	this->content = content;
	return true;
}

T ui_iface_view_impl::unset_content()
{
	T prev = this->content;
	this->content = NULL;
	return prev;
}

bool ui_iface_view_impl::set_transition_style(const char *style)
{
	this->transition_style.assign(style);
	return true;
}

bool ui_iface_view_impl::set_name(const char *name)
{
	this->name.assign(name);
	return true;
}

void ui_iface_view_impl::set_removable_content(bool removable)
{
	this->removable_content = removable;

	//FIXME: If this api is called on unload state? should we remove content right now?
}

void ui_iface_view_impl::set_indicator(ui_view_indicator indicator)
{
	this->indicator = indicator;
}

const char *ui_iface_view_impl::get_transition_style()
{
	return this->transition_style.c_str();
}

const char *ui_iface_view_impl::get_name()
{
	return this->name.c_str();
}

T ui_iface_view_impl::get_content()
{
	return this->content;
}

ui_view_state ui_iface_view_impl::get_state()
{
	return this->state;
}

bool ui_iface_view_impl::get_removable_content()
{
	return this->removable_content;
}

ui_view_indicator ui_iface_view_impl::get_indicator()
{
	return this->indicator;
}

void ui_iface_view_impl::on_back()
{
	ui_iface_viewmgr *viewmgr = this->viewmgr;
	if (!viewmgr)
	{
		LOGE("Failed to get a viewmgr, view =%p", this);
		return;
	}
	viewmgr->pop_view();
}

/***********************************************************************************************/
/* External class Implementation                                                               */
/***********************************************************************************************/

bool ui_iface_view::get_event_block()
{
	return this->impl->get_event_block();
}

void ui_iface_view::set_event_block(bool block)
{
	this->impl->set_event_block(block);
}

void ui_iface_view::on_load()
{
	this->impl->on_load();
}

void ui_iface_view::on_unload()
{
	this->impl->on_unload();
}

void ui_iface_view::on_activate()
{
	this->impl->on_activate();
}

void ui_iface_view::on_deactivate()
{
	this->impl->on_deactivate();
}

void ui_iface_view::on_pause()
{
	this->impl->on_pause();
}

void ui_iface_view::on_resume()
{
	this->impl->on_resume();
}

void ui_iface_view::on_destroy()
{
	this->impl->on_destroy();
}

ui_iface_view::ui_iface_view(const char *name)
{
	this->impl = new ui_iface_view_impl(this, name);
}

ui_iface_view::~ui_iface_view()
{
	delete(this->impl);
}

bool ui_iface_view::set_content(T content)
{
	return this->impl->set_content(content);
}

T ui_iface_view::unset_content()
{
	return this->impl->unset_content();
}

bool ui_iface_view::set_transition_style(const char *style)
{
	return this->impl->set_transition_style(style);
}

bool ui_iface_view::set_name(const char *name)
{
	return this->impl->set_name(name);
}

void ui_iface_view::set_removable_content(bool removable)
{
	this->impl->set_removable_content(removable);
}

void ui_iface_view::set_indicator(ui_view_indicator indicator)
{
	this->impl->set_indicator(indicator);
}

const char *ui_iface_view::get_transition_style()
{
	return this->impl->get_transition_style();
}

const char *ui_iface_view::get_name()
{
	return this->impl->get_name();
}

T ui_iface_view::get_content()
{
	return this->impl->get_content();
}

ui_view_state ui_iface_view::get_state()
{
	return this->impl->get_state();
}

bool ui_iface_view::get_removable_content()
{
	return this->impl->get_removable_content();
}

ui_view_indicator ui_iface_view::get_indicator()
{
	return this->impl->get_indicator();
}

void ui_iface_view::on_back()
{
	this->impl->on_back();
}

bool ui_iface_view::set_viewmgr(ui_iface_viewmgr *viewmgr)
{
	this->impl->viewmgr = viewmgr;
	return true;
}

ui_iface_viewmgr *ui_iface_view::get_viewmgr()
{
	return this->impl->viewmgr;
}

