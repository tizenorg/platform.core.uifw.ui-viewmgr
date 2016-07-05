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
#ifndef _UI_MENU_H_
#define _UI_MENU_H_

namespace efl_viewmanager
{
class UiView;

/**
 *  @class UiMenu
 *
 *  @ingroup efl_viewmanager
 *
 *  @brief UiMenu is to support EFL menu UI which could be active on one UiView. A menu is used for traditional contextual popup to give an option in its
 *         view context. Elm_Ctxpopup widget could be set as this UiMenu content for mobile profile. UiMenu will set up all Elm_Ctxpopup decorating
 *         options instead of users for their convenient. A UiMenu is designed to be one subordinate of one UiView in order to share events and contexts
 *         each other to work nicely. Only one menu could be active on a UiView. That means the previous menu will be removed by UiView when a new menu comes.
 *
 *  @warning UiMenu and its content, Elm_Ctxpopup will be deleted by its owned UiView on the proper time. So you can just leave its instance to it.
 */
class UiMenu: public efl_viewmanager::UiBaseOverlay
{
public:
	/**
	 *  @brief menu activate.
	 *
	 *  @note It makes menu state as show.
	 *
	 *  @return @c true if it succeeds, @c false otherwise.
	 *
	 *  @see deactivate()
	 */
	virtual bool activate();

	/**
	 *  @brief menu deactivate.
	 *
	 *  @note It makes menu state as hide.
	 *
	 *  @return @c true if it succeeds, @c false otherwise.
	 *
	 *  @see activate()
	 */
	virtual bool deactivate();

	/**
	 *  @brief This is for replacing or setting a content of the menu.
	 *
	 *  @param ctxpopup ctxpopup object. It allows @c NULL for canceling the previous content.
	 *
	 *  @return @c true if it succeeds, @c false otherwise.
	 */
	virtual bool setContent(Elm_Ctxpopup* ctxpopup);

	/**
	 *  @brief This is for unsetting a content of the menu.
	 *
	 *  @return A previous content. If it wasn't, return value will be @c NULL.
	 */
	virtual Elm_Ctxpopup *unsetContent();

	/**
	 *  @brief Return the active status of menu.
	 *
	 *  @return @c true if menu is activated, @c false otherwise.
	 *
	 *  @see activate()
	 *  @see deactivate()
	 */
	virtual bool isActivated();

	/**
	 *  @brief Get a base object of a UiMenu.
	 *
	 *  @note Normally, A base object can be used for a parent of UiMenu content.
	 *  @return base object of UiMenu.
	 */
	virtual Evas_Object *getBase();

	/**
	 *  @brief Get a current menu's degree.
	 *
	 *  @return Current rotation degree, -1 if it fails to get degree information.
	 */
	virtual int getDegree();

protected:
	/**
	 *  @brief This is a constructor for initializing this menu.
	 *
	 *  @param The instance of UiView.
	 */
	UiMenu(UiView *view);

	///Destructor.
	virtual ~UiMenu();

	/**
	 *  @brief Get a base window of viewmgr.
	 *
	 *  @return viewmgr's window object.
	 */
	Elm_Win *getWindow();

private:
	_UI_DECLARE_PRIVATE_IMPL(UiMenu);
	_UI_DISABLE_COPY_AND_ASSIGN(UiMenu);
	_UI_DECLARE_FRIENDS(UiView);
};

}

#endif /* _UI_MENU_H_ */
