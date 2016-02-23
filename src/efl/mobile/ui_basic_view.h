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

#include "../ui_viewmanager.h"

namespace efl_viewmgr
{

class ui_basic_view: public ui_view
{
private:
	Evas_Object *layout; //Base layout for view

	bool create_layout();
	bool destroy_layout();

protected:
	virtual void load();
	virtual void unload();
	virtual void unload_content();

public:
	ui_basic_view(ui_controller *controller, const char *name = NULL, const char *style = NULL);
	virtual ~ui_basic_view();

	Evas_Object *set_content(Evas_Object *content, const char *title = NULL);
	Evas_Object *set_content(Evas_Object *content, const char *title, const char *subtitle, Evas_Object *title_left_btn, Evas_Object *title_right_btn);
	bool set_title_badge(const char *text);
	bool set_subtitle(const char *text);
	bool set_title_left_btn(Evas_Object *title_left_btn);
	bool set_title_right_btn(Evas_Object *title_right_btn);
	bool set_title(const char *text);
	bool set_tabbar(Evas_Object *toolbar);

	virtual void menu();

	virtual Evas_Object *get_base()
	{
		return this->layout;
	}
};

}

#endif /* UI_BASIC_VIEW */
