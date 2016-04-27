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
#ifndef _UI_IMPL_VIEW_H_
#define _UI_IMPL_VIEW_H_


//FIXME: remove this.
#include "../ui_base_viewmanager.h"

namespace efl_viewmgr
{

class ui_view;
class ui_menu;
class ui_popup;
class ui_key_listener;

class ui_impl_view: public ui_base_view
{
	friend class ui_menu;
	friend class ui_popup;
	friend class ui_key_listener;

private:
	ui_view *view;
	Elm_Layout *layout;                //Base layout for view
	Elm_Toolbar *toolbar;              //Toolbar
	Elm_Button *title_left_btn;        //Title left button
	Elm_Button *title_right_btn;       //Title right button
	ui_menu *menu;                     //Menu
	list<ui_popup *> popup_list;

	void connect_popup(ui_popup *popup);
	void disconnect_popup(ui_popup *popup);
	bool deactivate_popup(bool top_one);

	bool create_layout();
	bool destroy_layout();

protected:
	virtual void on_load();
	virtual void on_unload();
	ui_menu *on_menu_pre();
	void on_menu_post();
	virtual void on_menu(ui_menu *menu);
	virtual void set_event_block(bool block);
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
	ui_impl_view(ui_view *view, const char *name);
	virtual ~ui_impl_view();

	bool set_content(Evas_Object *content, const char *title = NULL);
	bool set_content(Evas_Object *content, const char *title, const char *subtitle, Elm_Button *title_left_btn, Elm_Button *title_right_btn);
	bool set_title_badge(const char *text);
	bool set_subtitle(const char *text);
	bool set_title_left_btn(Elm_Button *title_left_btn);
	bool set_title_right_btn(Elm_Button *title_right_btn);
	bool set_title(const char *text);
	bool set_toolbar(Elm_Toolbar *toolbar);
	bool set_title_visible(bool visible, bool anim);
	Evas_Object *unset_content();
	Elm_Button *unset_title_left_btn();
	Elm_Button *unset_title_right_btn();
	Elm_Toolbar *unset_toolbar();

	virtual Evas_Object *get_base();

	Elm_Button *get_title_left_btn()
	{
		return this->title_left_btn;
	}

	Elm_Button *get_title_right_btn()
	{
		return this->title_right_btn;
	}

	Elm_Toolbar *get_toolbar()
	{
		return this->toolbar;
	}

	const ui_menu *get_menu()
	{
		return this->menu;
	}

	//just for delegating.
	void on_load_internal();
	void on_unload_internal();
	ui_menu *on_menu_pre_internal();
	void on_menu_post_internal();
	void on_menu_internal(ui_menu *menu);
	void set_event_block_internal(bool block);
	void on_back_internal();
	void on_rotate_internal(int degree);
	void on_portrait_internal();
	void on_landscape_internal();
	void on_deactivate_internal();
};

}

#endif /* _UI_IMPL_VIEW_H_ */
