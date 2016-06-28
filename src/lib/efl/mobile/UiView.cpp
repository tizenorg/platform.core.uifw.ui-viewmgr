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
#include "../../../include/efl/mobile/UiMobileViewManager.h"

/***********************************************************************************************/
/* Internal class Implementation                                                               */
/***********************************************************************************************/

using namespace std;

namespace efl_viewmanager
{

class UiViewImpl
{
	friend class UiView;

private:
	UiView *view;
	UiMenu *menu;
	list<UiPopup *> popup_list;

	void connect_popup(UiPopup *popup);
	void disconnect_popup(UiPopup *popup);
	bool deactivate_popup(bool top_one);

protected:
	UiMenu *on_menu_pre();
	void on_menu_post();
	void on_rotate(int degree);
	void on_portrait();
	void on_landscape();
	bool on_back();

public:
	UiViewImpl(UiView *view);
	~UiViewImpl();

	const UiMenu *get_menu()
	{
		return this->menu;
	}
};

}

typedef list<UiPopup*>::reverse_iterator popup_ritr;

void UiViewImpl::connect_popup(UiPopup *popup)
{
	this->popup_list.push_back(popup);
}

void UiViewImpl::disconnect_popup(UiPopup *popup)
{
	this->popup_list.remove(popup);
}

bool UiViewImpl::deactivate_popup(bool top_one)
{
	for (popup_ritr it = this->popup_list.rbegin(); it != this->popup_list.rend(); it++)
	{
		UiPopup *popup = *it;
		if (!popup->is_activated()) continue;
		popup->on_back();
		//deactivate only one top one? or all popups?
		if (top_one) return true;
	}
	return false;
}

bool UiViewImpl::on_back()
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

UiViewImpl::UiViewImpl(UiView *view)
		: view(view), menu(NULL)
{
}

UiViewImpl::~UiViewImpl()
{
	if (menu) delete (this->menu);
}

UiMenu *UiViewImpl::on_menu_pre()
{
	if (!this->menu)
	{
		this->menu = new UiMenu(this->view);
	}

	if (this->menu->is_activated())
	{
		this->menu->deactivate();
		return NULL;
	}

	return this->menu;
}

void UiViewImpl::on_menu_post()
{
	if (!this->menu) return;
	this->menu->activate();
}

void UiViewImpl::on_rotate(int degree)
{
	if (!this->menu) return;
	if (!this->menu->is_activated()) return;
	this->menu->on_rotate(degree);
}

void UiViewImpl::on_portrait()
{
	if (!this->menu) return;
	if (!this->menu->is_activated()) return;
	this->menu->on_portrait();
}

void UiViewImpl::on_landscape()
{
	if (!this->menu) return;
	if (!this->menu->is_activated()) return;
	this->menu->on_landscape();
}

/***********************************************************************************************/
/* External class Implementation                                                               */
/***********************************************************************************************/

void UiView::connect_popup(UiPopup *popup)
{
	this->impl->connect_popup(popup);
}

void UiView::disconnect_popup(UiPopup *popup)
{
	this->impl->disconnect_popup(popup);
}

void UiView::on_deactivate()
{
	this->impl->deactivate_popup(false);
	UiBaseView::on_deactivate();
}

void UiView::on_back()
{
	if (!this->impl->on_back()) return;
	UiBaseView::on_back();
}

UiView::UiView(const char *name)
		: UiBaseView(name)
{
	this->impl = new UiViewImpl(this);
}

UiView::~UiView()
{
	delete(this->impl);
}

UiMenu *UiView::on_menu_pre()
{
	return this->impl->on_menu_pre();
}

void UiView::on_menu(UiMenu *menu)
{
}

void UiView::on_menu_post()
{
	this->impl->on_menu_post();
}

void UiView::on_rotate(int degree)
{
	//FIXME: see how to handle on_menu()
	UiBaseView::on_rotate(degree);
	this->impl->on_rotate(degree);
}

void UiView::on_portrait()
{
	//FIXME: see how to handle on_menu()
	UiBaseView::on_portrait();
	this->impl->on_portrait();
}

void UiView::on_landscape()
{
	//FIXME: see how to handle on_menu()
	UiBaseView::on_landscape();
	this->impl->on_landscape();
}

const UiMenu *UiView::get_menu()
{
	return this->impl->get_menu();
}
