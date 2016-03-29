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
#include "../../../include/efl/mobile/ui_viewmanager.h"

using namespace efl_viewmgr;
using namespace viewmgr;

static const char *KEY_MENU = "XF86Menu";
static const char *KEY_MENU2 = "XF86Send";

ui_key_listener::ui_key_listener(ui_viewmgr *viewmgr)
		: ui_base_key_listener(viewmgr)
{
}

void ui_key_listener::extend_event_proc(ui_base_view *view, Evas_Event_Key_Down *ev)
{
	if (strcmp(ev->keyname, KEY_MENU) && strcmp(ev->keyname, KEY_MENU2)) return;
	ui_view *v = dynamic_cast<ui_view *>(view);
	if (!v->on_menu_pre()) return;
	v->on_menu((ui_menu*)(v->get_menu()));
	v->on_menu_post();
}

bool ui_key_listener::init()
{
	if (!ui_base_key_listener::init()) return false;
	if (!evas_object_key_grab(this->key_grabber, KEY_MENU, 0, 0, EINA_FALSE))
	{
		LOGE("Failed to grab MENU KEY(%s)\n", KEY_MENU);
		return false;
	}

	if (!evas_object_key_grab(this->key_grabber, KEY_MENU2, 0, 0, EINA_FALSE))
	{
		LOGE("Failed to grab MENU KEY(%s)\n", KEY_MENU2);
		return false;
	}
	return true;
}
