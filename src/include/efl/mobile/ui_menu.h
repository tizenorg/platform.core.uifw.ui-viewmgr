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
class ui_view;

class ui_menu: public ui_base_overlay
{
public:
	/** @brief menu activate.
	 *
	 *  @note It makes menu state as show.
	 *
	 *  @return true if it succeed, false otherwise.
	 *
	 *  @see deactivate()
	 */
	virtual bool activate();

	/** @brief menu deactivate.
	 *
	 *  @note It makes menu state as hide.
	 *
	 *  @return true if it succeed, false otherwise.
	 *
	 *  @see activate()
	 */
	virtual bool deactivate();

	/** @brief This is for replacing or setting a content of the menu.
	 *
	 *  @param ctxpopup ctxpopup object. It allows @c NULL for canceling the previous content.
	 *
	 *  @return true if it succeed, false otherwise.
	 */
	virtual bool set_content(Elm_Ctxpopup* ctxpopup);

	/** @brief This is for unsetting a content of the menu.
	 *
	 *  @return A previous content. If it wasn't, return value will be @c NULL.
	 */
	virtual Elm_Ctxpopup *unset_content();

	/**
	 *  @brief Return the active status of menu.
	 *
	 *  @return @c true if overlay is activated, @c false otherwise.
	 *
	 *  @see activate()
	 *  @see deactivate()
	 */
	virtual bool is_activated();

	/**
	 *  @brief Get a base window of viewmgr.
	 *
	 *  @return viewmgr's window object.
	 */
	virtual Evas_Object *get_base();

	/**
	 *  @brief Get current menu's degree.
	 *
	 *  @return Current rotation degree, -1 if it fails to get degree information.
	 */
	virtual int get_degree();

protected:
	///Constructor.
	ui_menu(ui_view *view);

	///Destructor.
	virtual ~ui_menu();

	/**
	 *  @brief Get a base window of viewmgr.
	 *
	 *  @return viewmgr's window object.
	 */
	Elm_Win *get_window();

private:
	_UI_DECLARE_PRIVATE_IMPL(ui_menu);
	_UI_DISABLE_COPY_AND_ASSIGN(ui_menu);
	_UI_DECLARE_FRIENDS(ui_view);
};

}

#endif /* _UI_MENU_H_ */
