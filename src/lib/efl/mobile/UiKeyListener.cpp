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
#include "../../../include/efl/mobile/UiMobileViewManager.h"

static const char *KEY_MENU = "XF86Menu";
static const char *KEY_MENU2 = "XF86Send";

UiKeyListener::UiKeyListener(UiViewmgr *viewmgr)
		: UiBaseKeyListener(viewmgr)
{
}

void UiKeyListener::extendEventProc(UiBaseView *view, Evas_Event_Key_Down *ev)
{
	if (strcmp(ev->keyname, KEY_MENU) && strcmp(ev->keyname, KEY_MENU2)) return;
	UiView *v = dynamic_cast<UiView *>(view);
	UiMenu *menu = v->onMenuPre();
	if (!menu) return;
	v->onMenu(menu);
	v->onMenuPost();
}

bool UiKeyListener::init()
{
	if (!UiBaseKeyListener::init()) return false;
	if (!evas_object_key_grab(this->getKeygrabObj(), KEY_MENU, 0, 0, EINA_FALSE))
	{
		LOGE("Failed to grab MENU KEY(%s)\n", KEY_MENU);
		return false;
	}

	if (!evas_object_key_grab(this->getKeygrabObj(), KEY_MENU2, 0, 0, EINA_FALSE))
	{
		LOGE("Failed to grab MENU KEY(%s)\n", KEY_MENU2);
		return false;
	}
	return true;
}
