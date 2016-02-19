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
#ifndef UI_VIEWMGR
#define UI_VIEWMGR

#include <Elementary.h>
#include "../interface/ui_viewmgr.h"
#include "ui_key_handler.h"

namespace efl
{

class ui_view;

class ui_viewmgr: public ui_viewmgr_base
{
	friend class ui_view;

private:
	Evas_Object *win;
	Evas_Object *conform;
	Evas_Object *layout;
	ui_key_handler *key_handler;   //HW Key Handler such as "BACK" key...
	ui_view_indicator indicator;

	bool create_conformant(Evas_Object *win);
	bool create_base_layout(Evas_Object *conform);
	bool set_indicator(ui_view_indicator indicator);
	virtual void set_key_handler();

protected:
	Evas_Object *get_base()
	{
		return this->layout;
	}

public:
	ui_viewmgr(const char *pkg);
	virtual ~ui_viewmgr();

	virtual bool activate();
	virtual bool deactivate();
	virtual ui_view *push_view(ui_view *view);
	virtual bool pop_view();

	Evas_Object *get_window()
	{
		return this->win;
	}

	Evas_Object *get_conformant()
	{
		return this->conform;
	}
};
}

#endif /* UI_VIEWMGR */
