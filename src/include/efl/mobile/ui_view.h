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

namespace efl_viewmanager
{

class ui_menu;
class ui_popup;
class ui_key_listener;

/**
 *  @class ui_view
 *
 *  @ingroup efl_viewmanager
 *
 *  @brief This is a mobile view. Typically, this view extends ui_base_view and implements mobile specific behaviors for EFL view in mobile profile.
 *         Basically, ui_view implements basics for running together with overlays such as ui_menu and ui_popup. You can use this ui_view as an empty ui form
 *         view.
 */
class ui_view: public ui_base_view
{
public:
	ui_view(const char *name = NULL);
	virtual ~ui_view();

	const ui_menu *get_menu();

protected:
	virtual ui_menu *on_menu_pre();
	virtual void on_menu_post();
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

private:
	void connect_popup(ui_popup *popup);
	void disconnect_popup(ui_popup *popup);

	_UI_DECLARE_PRIVATE_IMPL(ui_view);
	_UI_DISABLE_COPY_AND_ASSIGN(ui_view);
	_UI_DECLARE_FRIENDS(ui_menu);
	_UI_DECLARE_FRIENDS(ui_popup);
	_UI_DECLARE_FRIENDS(ui_key_listener);
};

}

#endif /* _UI_VIEW_H_ */
