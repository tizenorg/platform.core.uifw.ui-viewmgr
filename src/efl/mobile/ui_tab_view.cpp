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

ui_tab_view::ui_tab_view(ui_controller *controller, const char *name)
		: ui_basic_view(controller, name)
{
	this->set_style("tabbar");
}

ui_tab_view::~ui_tab_view()
{
	destroy_layout();
}

bool ui_tab_view::set_tabbar(Evas_Object *toolbar)
{
	Evas_Object *layout = this->get_base();

	if (layout)
	{
		elm_object_part_content_set(layout, "tabbar", toolbar);
		if (toolbar) elm_object_signal_emit(layout, "elm,state,tabbar,show", "elm");
		return true;
	}
	LOGE("Layout is not exist!");
	return false;
}
