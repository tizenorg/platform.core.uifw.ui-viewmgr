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
#include "../../include/efl/ui_viewmanager_base.h"

using namespace efl_viewmgr;
using namespace viewmgr;

ui_base_view * ui_base_controller::get_view()
{
	ui_iface_view *view = ui_iface_controller::get_view();
	if (!view) return NULL;
	return dynamic_cast<ui_base_view *>(view);
}

ui_base_controller::~ui_base_controller()
{

}
