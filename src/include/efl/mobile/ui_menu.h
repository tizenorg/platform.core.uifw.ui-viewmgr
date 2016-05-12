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

/**
 *  @class ui_menu
 *
 *  @ingroup efl_viewmanager
 *
 *  @brief ui_menu is to support EFL menu UI which could be active on one ui_view. A menu is used for traditional contextual popup to give an option in its
 *         view context. Elm_Ctxpopup widget could be set as this ui_menu content for mobile profile. ui_menu will set up all Elm_Ctxpopup decorating
 *         options instead of users for their convenient. A ui_menu is designed to be one subordinate of one ui_view in order to share events and contexts
 *         each other to work nicely. Only one menu could be active on a ui_view. That means the previous menu will be removed by ui_view when a new menu comes.
 *
 *  @warning ui_menu and its content, Elm_Ctxpopup will be deleted by its owned ui_view on the proper time. So you can just leave its instance to it.
 */
class ui_menu: public ui_base_overlay
{
public:
	virtual bool activate();
	virtual bool deactivate();
	virtual bool set_content(Elm_Ctxpopup* ctxpopup);
	virtual Elm_Ctxpopup *unset_content();
	virtual bool is_activated();

	virtual Evas_Object *get_base();
	virtual int get_degree();

protected:
	ui_menu(ui_view *view);
	virtual ~ui_menu();
	Elm_Win *get_window();

private:
	_UI_DECLARE_PRIVATE_IMPL(ui_menu);
	_UI_DISABLE_COPY_AND_ASSIGN(ui_menu);
	_UI_DECLARE_FRIENDS(ui_view);
};

}

#endif /* _UI_MENU_H_ */
