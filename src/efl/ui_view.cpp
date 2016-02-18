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
#include "efl_viewmgr.h"

using namespace efl;

ui_view::ui_view(ui_controller *controller, const char *name)
		: ui_view_base(controller, name)
{
}

ui_view::~ui_view()
{
}

Evas_Object *ui_view::set_content(Evas_Object *content)
{
	T pcontent = ui_view_base::set_content(CONVERT_TO_T(content));
	return static_cast<Evas_Object *>(pcontent);
}

Evas_Object *ui_view::get_base()
{
	ui_viewmgr *viewmgr = dynamic_cast<ui_viewmgr *>(ui_view_base::get_viewmgr());
	if (!viewmgr)
	{
		return NULL;
	}
	return viewmgr->get_base();
}

void ui_view::load()
{
	ui_view_base::load();
}

void ui_view::unload()
{
	ui_view_base::unload();
}

void ui_view::unload_content()
{
	Evas_Object *pcontent = this->set_content(NULL);
	if (pcontent) evas_object_del(pcontent);
}
