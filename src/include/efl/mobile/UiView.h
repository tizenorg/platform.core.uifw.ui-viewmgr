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

class UiMenu;
class UiPopup;
class UiKeyListener;

/**
 *  @class UiView
 *
 *  @ingroup efl_viewmanager
 *
 *  @brief This is a mobile view. Typically, this view extends UiBaseView and implements mobile specific behaviors for EFL view in mobile profile.
 *         Basically, UiView implements basics for running together with overlays such as UiMenu and UiPopup. You can use this UiView as an empty ui form
 *         view.
 */
class UiView: public UiBaseView
{
public:
	/**
	 *  @brief This is a constructor for initializing this view resources.
	 *
	 *  @param name view name.
	 *
	 *  @warning if you don't set a view name, you could not look up the view with its name. @see ui_viewmgr_view_get_by_name()
	 */
	UiView(const char *name = NULL);

	///Destructor.
	virtual ~UiView();

	/**
	 *  @brief Get menu object.
	 *
	 *  @return The menu object that connected with this view.
	 */
	const UiMenu *get_menu();

protected:
	/**
	 *  @brief This is making UiMenu instance.
	 *
	 *  @note It creates UiMenu instance, if there is no connected UiMenu instance of this view.
	 *        It hides menu if there is already menu activated.
	 *
	 *  @return The menu instance of this view. NULL If the menu already activated.
	 */
	virtual UiMenu *on_menu_pre();

	/**
	 *  @brief Activate menu.
	 *
	 *  @note It calls activate() for posting menu. If there is a menu instance.
	 */
	virtual void on_menu_post();

	/**
	 *  @brief The H/W menu key event occurs on view.
	 *
	 *  @param menu menu instance, This is made by key listener when menu key occured.
	 */
	virtual void on_menu(UiMenu *menu);

	/**
	 *  @brief The H/W back key event occurs on view.
	 *
	 *  @note User can override this function to define application specific action when H/W back key
	 *        event occurs. otherwise current view will be popped.
	 */
	virtual void on_back();

	/**
	 *  @brief View rotate changed.
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
	 *  @brief View portrait state.
	 *
	 *  @note This state will be called when view rotation changed to portrait.
	 *
	 *  @see on_landscpae()
	 *  @see on_rotate()
	 */
	virtual void on_portrait();

	/**
	 *  @brief View landscape state.
	 *
	 *  @note This state will be called when view rotation changed to landscape.
	 *
	 *  @see on_portrait()
	 *  @see on_rotate()
	 */
	virtual void on_landscape();

	/** @brief View deactivate state.
	 *
	 *  @note this state will be triggered by UiIfaceViewmgr.
	 *
	 */
	virtual void on_deactivate();

private:
	/**
	 *  @brief Push given popup instance in the internal popup stack.
	 *
	 *  @param popup UiPopup instance
	 */
	void connect_popup(UiPopup *popup);

	/**
	 *  @brief pop given popup instance in the internal popup stack.
	 *
	 *  @param popup UiPopup instance
	 */
	void disconnect_popup(UiPopup *popup);

	_UI_DECLARE_PRIVATE_IMPL(UiView);
	_UI_DISABLE_COPY_AND_ASSIGN(UiView);
	_UI_DECLARE_FRIENDS(UiMenu);
	_UI_DECLARE_FRIENDS(UiPopup);
	_UI_DECLARE_FRIENDS(UiKeyListener);
};

}

#endif /* _UI_VIEW_H_ */
