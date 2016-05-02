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
#ifndef _UI_VIEW_H_
#define _UI_VIEW_H_

#include <list>

using namespace std;

namespace efl_viewmanager
{

class ui_menu;
class ui_popup;
class ui_key_listener;

class ui_view: public ui_base_view
{
	friend class ui_menu;
	friend class ui_popup;
	friend class ui_key_listener;

private:
	ui_menu *menu;                     //Menu
	list<ui_popup *> popup_list;

	void connect_popup(ui_popup *popup);
	void disconnect_popup(ui_popup *popup);
	bool deactivate_popup(bool top_one);

protected:
	ui_menu *on_menu_pre();
	void on_menu_post();
	virtual void on_menu(ui_menu *menu);
	virtual void on_back();
	virtual void on_rotate(int degree);
	virtual void on_portrait();
	virtual void on_landscape();

	/** @brief view deactivate state.
	 *
	 *  @note this state will be triggered by ui_iface_viewmgr.
	 *
	 */
	virtual void on_deactivate();

public:
	ui_view(const char *name = NULL);
	virtual ~ui_view();

	const ui_menu *get_menu()
	{
		return this->menu;
	}
};

}

#endif /* _UI_VIEW_H_ */
