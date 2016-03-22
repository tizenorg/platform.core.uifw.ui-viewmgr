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
#ifndef UI_BASIC_VIEW
#define UI_BASIC_VIEW

#include "../ui_viewmanager_efl.h"

namespace efl_viewmgr
{

class ui_basic_view: public ui_view
{
private:
	Evas_Object *layout; 	  		 //Base layout for view
	Evas_Object *ctxpopup; 	  		 //Menu Widget

	bool create_layout();
	bool destroy_layout();

protected:
	virtual void on_load();
	virtual void on_unload();
	virtual void unload_content();
	virtual void set_event_block(bool block);

public:
	ui_basic_view(ui_controller *controller, const char *name = NULL);
	ui_basic_view(const char *name = NULL);
	virtual ~ui_basic_view();

	Evas_Object *set_content(Evas_Object *content, const char *title = NULL);
	Evas_Object *set_content(Evas_Object *content, const char *title, const char *subtitle, Evas_Object *title_left_btn, Evas_Object *title_right_btn);
	bool set_title_badge(const char *text);
	bool set_subtitle(const char *text);
	bool set_title_left_btn(Evas_Object *title_left_btn);
	bool set_title_right_btn(Evas_Object *title_right_btn);
	bool set_title(const char *text);
	bool set_toolbar(Elm_Toolbar *toolbar);
	bool set_menu(Elm_Ctxpopup *menu);
	Elm_Ctxpopup * unset_menu();

	virtual void on_menu();

	virtual Evas_Object *get_base()
	{
		if (!this->layout)this->create_layout();
		return this->layout;
	}

	Evas_Object *get_menu()
	{
		return this->ctxpopup;
	}

};

}

#endif /* UI_BASIC_VIEW */
