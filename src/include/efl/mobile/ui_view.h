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
	///Constructor.
	ui_view(const char *name = NULL);

	///Destructor.
	virtual ~ui_view();

	/**
	 *  @brief Get menu object.
	 *
	 *  @return menu object if any.
	 */
	const ui_menu *get_menu();

protected:
	/**
	 *  @brief This is making ui_menu instance.
	 *
	 *  @note It creates ui_menu instance, if there is no ui_menu instance of this view.
	 *        It hides menu if there is already menu activated.
	 *
	 *  @return menu instance of this view. NULL If the menu already activated.
	 */
	virtual ui_menu *on_menu_pre();

	/**
	 *  @brief Activate menu.
	 *
	 *  @note It calls activate() for posting menu. If there is a menu instance.
	 */
	virtual void on_menu_post();

	/**
	 *  @brief H/W back key event occurs on view.
	 *
	 *  @param menu menu instance, This is made by key listener when menu key occured.
	 */
	virtual void on_menu(ui_menu *menu);

	/**
	 *  @brief H/W back key event occurs on view.
	 *
	 *  @note User can override this function to define application specific action when H/W back key
	 *        event occurs. otherwise current view will be popped.
	 */
	virtual void on_back();

	/**
	 *  @brief view rotate changed.
	 *
	 *  @note This state will be called when view rotation changed.
	 *
	 *  @param degree Current view's degree.
	 *
	 *  @see on_portrait()
	 *  @see on_landscpae()
	 */
	virtual void on_rotate(int degree);

	/**
	 *  @brief view portrait state.
	 *
	 *  @note This state will be called when view rotation changed to portrait.
	 *
	 *  @see on_landscpae()
	 *  @see on_rotate()
	 */
	virtual void on_portrait();

	/**
	 *  @brief view landscape state.
	 *
	 *  @note This state will be called when view rotation changed to landscape.
	 *
	 *  @see on_portrait()
	 *  @see on_rotate()
	 */
	virtual void on_landscape();

	/** @brief view deactivate state.
	 *
	 *  @note this state will be triggered by ui_iface_viewmgr.
	 *
	 */
	virtual void on_deactivate();

private:
	/**
	 *  @brief Push given popup instance in the internal popup stack.
	 *
	 *  @param popup ui_popup instance
	 */
	void connect_popup(ui_popup *popup);

	/**
	 *  @brief pop given popup instance in the internal popup stack.
	 *
	 *  @param popup ui_popup instance
	 */
	void disconnect_popup(ui_popup *popup);

	_UI_DECLARE_PRIVATE_IMPL(ui_view);
	_UI_DISABLE_COPY_AND_ASSIGN(ui_view);
	_UI_DECLARE_FRIENDS(ui_menu);
	_UI_DECLARE_FRIENDS(ui_popup);
	_UI_DECLARE_FRIENDS(ui_key_listener);
};

}

#endif /* _UI_VIEW_H_ */
