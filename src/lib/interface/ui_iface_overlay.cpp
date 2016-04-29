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

#include "../../include/interface/ui_iface_viewmanager.h"

ui_iface_overlay::ui_iface_overlay(ui_iface_view *view)
		: view(view), content(NULL)
{
}

ui_iface_overlay::~ui_iface_overlay()
{
}

bool ui_iface_overlay::set_content(T content)
{
	this->content = content;
	return true;
}

T ui_iface_overlay::unset_content()
{
	T prev = this->content;
	this->content = NULL;
	return prev;
}

T ui_iface_overlay::get_content()
{
	return this->content;
}

ui_iface_view *ui_iface_overlay::get_view()
{
	return this->view;
}

void ui_iface_overlay::on_back()
{
	this->deactivate();
}
