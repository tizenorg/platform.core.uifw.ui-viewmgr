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


/***********************************************************************************************/
/* Internal class Implementation                                                               */
/***********************************************************************************************/
namespace ui_viewmanager
{

class ui_iface_overlay_impl
{
	friend class ui_iface_overlay;

private:
	ui_iface_overlay *overlay;
	ui_iface_view *view;
	T content;

public:
	bool set_content(T content);
	T unset_content();
	ui_iface_view *get_view();
	T get_content();

	ui_iface_overlay_impl(ui_iface_overlay *overlay, ui_iface_view *view);
	~ui_iface_overlay_impl();
};

}

ui_iface_overlay_impl::ui_iface_overlay_impl(ui_iface_overlay *overlay, ui_iface_view *view)
		: overlay(overlay), view(view), content(NULL)
{
}

ui_iface_overlay_impl::~ui_iface_overlay_impl()
{
}

bool ui_iface_overlay_impl::set_content(T content)
{
	this->content = content;
	return true;
}

T ui_iface_overlay_impl::unset_content()
{
	T prev = this->content;
	this->content = NULL;
	return prev;
}

T ui_iface_overlay_impl::get_content()
{
	return this->content;
}

ui_iface_view *ui_iface_overlay_impl::get_view()
{
	return this->view;
}


/***********************************************************************************************/
/* External class Implementation                                                               */
/***********************************************************************************************/
ui_iface_overlay::ui_iface_overlay(ui_iface_view *view)
{
	this->impl = new ui_iface_overlay_impl(this, view);
}

ui_iface_overlay::~ui_iface_overlay()
{
	delete(this->impl);
}

bool ui_iface_overlay::set_content(T content)
{
	return this->impl->set_content(content);
}

T ui_iface_overlay::unset_content()
{
	return this->impl->unset_content();
}

T ui_iface_overlay::get_content()
{
	return this->impl->get_content();
}

ui_iface_view *ui_iface_overlay::get_view()
{
	return this->impl->get_view();
}

void ui_iface_overlay::on_back()
{
	this->deactivate();
}

bool ui_iface_overlay::activate()
{
	return true;
}

bool ui_iface_overlay::deactivate()
{
	return true;
}

bool ui_iface_overlay::is_activated()
{
	return true;
}
