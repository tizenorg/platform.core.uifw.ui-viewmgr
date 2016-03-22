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
#include "../../include/efl/ui_viewmanager_efl.h"

using namespace efl_viewmgr;
using namespace viewmgr;

ui_view::ui_view(ui_controller *controller, const char *name)
		: ui_iface_view(controller, name)
{
}

ui_view::ui_view(const char *name)
		: ui_view(NULL, name)
{
}

ui_view::~ui_view()
{
}

Evas_Object *ui_view::set_content(Evas_Object *content)
{
	T pcontent = ui_iface_view::set_content(CONVERT_TO_T(content));
	return static_cast<Evas_Object *>(pcontent);
}

Evas_Object *ui_view::get_base()
{
	ui_viewmgr *viewmgr = dynamic_cast<ui_viewmgr *>(ui_iface_view::get_viewmgr());
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
	if (!viewmgr)
	{
		LOGE("Failed to get a viewmgr");
		return NULL;
	}
	return viewmgr->get_base();
}

void ui_view::set_indicator(ui_view_indicator indicator)
{
	if (this->get_indicator() == indicator) return;

	ui_iface_view::set_indicator(indicator);

	ui_viewmgr *viewmgr = dynamic_cast<ui_viewmgr *>(this->get_viewmgr());

	if (!viewmgr->is_activated()) return;

	if (dynamic_cast<ui_view *>(viewmgr->get_last_view()) != this) return;

	viewmgr->set_indicator(indicator);
}

void ui_view::on_back()
{
	if (this->get_controller())
	{
		if (!dynamic_cast<ui_controller *>(this->get_controller())->on_back())
		{
			return;
		}
	}
	dynamic_cast<ui_viewmgr *>(this->get_viewmgr())->pop_view();
}

void ui_view::on_rotate(int degree)
{
	if (this->get_controller())
	{
		dynamic_cast<ui_controller *>(this->get_controller())->on_rotate(degree);
	}
}

void ui_view::on_portrait()
{
	if (this->get_controller())
	{
		dynamic_cast<ui_controller *>(this->get_controller())->on_portrait();
	}
}

void ui_view::on_landscape()
{
	if (this->get_controller())
	{
		dynamic_cast<ui_controller *>(this->get_controller())->on_landscape();
	}
}
void ui_view::set_event_block(bool block)
{
	ui_iface_view::set_event_block(block);
	evas_object_freeze_events_set(CONVERT_TO_EO(this->get_content()), block);
}

int ui_view::get_degree()
{
	ui_viewmgr *viewmgr = dynamic_cast<ui_viewmgr *>(ui_iface_view::get_viewmgr());
	if (!viewmgr)
	{
		LOGE("Failed to get a viewmgr");
		return -1;
	}
	return elm_win_rotation_get(viewmgr->get_window());
}
