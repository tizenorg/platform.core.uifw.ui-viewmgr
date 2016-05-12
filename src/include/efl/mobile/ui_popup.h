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
#ifndef _UI_POPUP_H_
#define _UI_POPUP_H_

namespace efl_viewmanager
{

class ui_view;

/**
 *  @class ui_popup
 *
 *  @ingroup efl_viewmanager
 *
 *  @brief ui_popup is to support EFL popup UI which could be active on one ui_view. A popup is used for traditional popping context information to give
 *         an option or information in its view context. Elm_Popup widget could be set as this ui_popup content for mobile profile. ui_popup will set up all
 *         Elm_Popup decorating options instead of users for their convenient. A ui_popup is designed to be one subordinate of one ui_view in order to share
 *         events and contexts each other to work nicely. One of differ points of ui_popup with ui_menu is, multiple popup could be active at the same time.
 *         That means, a new ui_popup will be overlaid on the previous ui_popup on the demands. It's up to user's scenario.
 *
 *  @warning ui_popup and its content, Elm_Popup will be deleted by its owned ui_view on the proper time. So you can just leave its instance to it.
 */
class ui_popup : public ui_base_overlay
{
public:
	ui_popup(ui_view *view);
	virtual ~ui_popup();

	virtual bool activate();
	virtual bool deactivate();
	virtual bool set_content(Elm_Popup* popup);
	virtual Elm_Popup *unset_content();
	virtual bool is_activated();

	virtual Evas_Object *get_base();
	virtual int get_degree();

protected:
	virtual Elm_Win *get_window();

private:
	_UI_DECLARE_PRIVATE_IMPL(ui_popup);
	_UI_DISABLE_COPY_AND_ASSIGN(ui_popup);
};

}

#endif /* _UI_POPUP_H_ */
