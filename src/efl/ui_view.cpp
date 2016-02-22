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
#include "ui_viewmanager.h"

using namespace efl_viewmgr;
using namespace viewmgr;

ui_view::ui_view(ui_controller *controller, const char *name, const char *style)
		: ui_view_interface(controller, name, style)
{
}

ui_view::~ui_view()
{
}

Evas_Object *ui_view::set_content(Evas_Object *content)
{
	T pcontent = ui_view_interface::set_content(CONVERT_TO_T(content));
	return static_cast<Evas_Object *>(pcontent);
}

Evas_Object *ui_view::get_base()
{
	ui_viewmgr *viewmgr = dynamic_cast<ui_viewmgr *>(ui_view_interface::get_viewmgr());
	if (!viewmgr)
	{
		return NULL;
	}
	return viewmgr->get_base();
}

void ui_view::unload_content()
{
	Evas_Object *pcontent = this->set_content(NULL);
	if (pcontent) evas_object_del(pcontent);
}

Evas_Object *ui_view ::get_parent()
{
	ui_viewmgr *viewmgr = dynamic_cast<ui_viewmgr *>(this->get_viewmgr());
	return viewmgr->get_base();
}

void ui_view::set_indicator(ui_view_indicator indicator)
{
	if (this->get_indicator() == indicator) return;

	ui_view_interface::set_indicator(indicator);

	ui_viewmgr *viewmgr = dynamic_cast<ui_viewmgr *>(this->get_viewmgr());

	if (!viewmgr->is_activated()) return;

	if (dynamic_cast<ui_view *>(viewmgr->get_last_view()) != this) return;

	viewmgr->set_indicator(indicator);
}
