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
#include <list>
#include "../../../include/efl/mobile/ui_mobile_viewmanager.h"

/***********************************************************************************************/
/* Internal class Implementation                                                               */
/***********************************************************************************************/

using namespace std;

namespace efl_viewmanager
{

class ui_view_impl
{
	friend class ui_view;

private:
	ui_view *view;
	ui_menu *menu;
	list<ui_popup *> popup_list;

	void connect_popup(ui_popup *popup);
	void disconnect_popup(ui_popup *popup);
	bool deactivate_popup(bool top_one);

protected:
	ui_menu *on_menu_pre();
	void on_menu_post();
	void on_rotate(int degree);
	void on_portrait();
	void on_landscape();
	bool on_back();

public:
	ui_view_impl(ui_view *view);
	~ui_view_impl();

	const ui_menu *get_menu()
	{
		return this->menu;
	}
};

}

typedef list<ui_popup*>::reverse_iterator popup_ritr;

void ui_view_impl::connect_popup(ui_popup *popup)
{
	this->popup_list.push_back(popup);
}

void ui_view_impl::disconnect_popup(ui_popup *popup)
{
	this->popup_list.remove(popup);
}

bool ui_view_impl::deactivate_popup(bool top_one)
{
	for (popup_ritr it = this->popup_list.rbegin(); it != this->popup_list.rend(); it++)
	{
		ui_popup *popup = *it;
		if (!popup->is_activated()) continue;
		popup->on_back();
		//deactivate only one top one? or all popups?
		if (top_one) return true;
	}
	return false;
}

bool ui_view_impl::on_back()
{
	//If any popup is activated, deactivate the popup first.
	if (this->deactivate_popup(true))
	{
		return false;
	}

	if (this->menu)
	{
		if (this->menu->is_activated())
		{
			this->menu->on_back();
			return false;
		}
	}
	return true;
}

ui_view_impl::ui_view_impl(ui_view *view)
		: view(view), menu(NULL)
{
}

ui_view_impl::~ui_view_impl()
{
	if (menu) delete (this->menu);
}

ui_menu *ui_view_impl::on_menu_pre()
{
	if (!this->menu)
	{
		this->menu = new ui_menu(this->view);
	}

	if (this->menu->is_activated())
	{
		this->menu->deactivate();
		return NULL;
	}

	return this->menu;
}

void ui_view_impl::on_menu_post()
{
	if (!this->menu) return;
	this->menu->activate();
}

void ui_view_impl::on_rotate(int degree)
{
	if (!this->menu) return;
	if (!this->menu->is_activated()) return;
	//FIXME: is it needed?
	this->menu->on_rotate(degree);
}

void ui_view_impl::on_portrait()
{
	if (!this->menu) return;
	if (!this->menu->is_activated()) return;
	//FIXME: is it needed?
	this->menu->on_portrait();
}

void ui_view_impl::on_landscape()
{
	if (!this->menu) return;
	if (!this->menu->is_activated()) return;
	//FIXME: is it needed?
	this->menu->on_landscape();
}

/***********************************************************************************************/
/* External class Implementation                                                               */
/***********************************************************************************************/

void ui_view::connect_popup(ui_popup *popup)
{
	this->impl->connect_popup(popup);
}

void ui_view::disconnect_popup(ui_popup *popup)
{
	this->impl->disconnect_popup(popup);
}

void ui_view::on_deactivate()
{
	this->impl->deactivate_popup(false);
	ui_base_view::on_deactivate();
}

void ui_view::on_back()
{
	if (!this->impl->on_back()) return;
	ui_base_view::on_back();
}

ui_view::ui_view(const char *name)
		: ui_base_view(name)
{
	this->impl = new ui_view_impl(this);
}

ui_view::~ui_view()
{
	delete(this->impl);
}

ui_menu *ui_view::on_menu_pre()
{
	return this->impl->on_menu_pre();
}

void ui_view::on_menu(ui_menu *menu)
{
}

void ui_view::on_menu_post()
{
	this->impl->on_menu_post();
}

void ui_view::on_rotate(int degree)
{
	//FIXME: see how to handle on_menu()
	ui_base_view::on_rotate(degree);
	this->impl->on_rotate(degree);
}

void ui_view::on_portrait()
{
	//FIXME: see how to handle on_menu()
	ui_base_view::on_portrait();
	this->impl->on_portrait();
}

void ui_view::on_landscape()
{
	//FIXME: see how to handle on_menu()
	ui_base_view::on_landscape();
	this->impl->on_landscape();
}

const ui_menu *ui_view::get_menu()
{
	return this->impl->get_menu();
}
