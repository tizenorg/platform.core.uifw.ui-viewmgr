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

using namespace ui_viewmanager;
using namespace efl_viewmanager;

static void _ctxpopupDismissedCb(void *data, Evas_Object *obj, void *event_info)
{
	evas_object_hide(obj);
}

static void _ctxpopupDelCb(void *data, Evas *e, Evas_Object *obj, void *event_info)
{
	UiMenu *menu = static_cast<UiMenu *>(data);
	menu->unsetContent();
}

static bool _updateMenu(UiMenu *menu)
{
	Elm_Win *win = menu->getBase();
	if (!win) return false;

	Elm_Ctxpopup *ctxpopup = menu->getContent();
	if (!ctxpopup) return false;

	/* We convince the top widget is a window */
	Evas_Coord w, h;
	elm_win_screen_size_get(win, NULL, NULL, &w, &h);
	int rot = elm_win_rotation_get(win);

	switch (rot) {
	case 0:
	case 180:
		evas_object_move(ctxpopup, (w / 2), h);
		break;
	case 90:
	case 270:
		evas_object_move(ctxpopup, (h / 2), w);
		break;
	}

	evas_object_show(ctxpopup);

	return true;
}

static void _winResizeCb(void *data, Evas *e, Evas_Object *obj, void *event_info)
{
	UiMenu *menu = static_cast<UiMenu *>(data);
	if (!menu->isActivated()) return;

	_updateMenu(menu);
}

UiMenu::UiMenu(UiView *view)
		: UiBaseOverlay(view)
{
	Elm_Win *win = this->getWindow();
	evas_object_event_callback_add(win, EVAS_CALLBACK_RESIZE, _winResizeCb, this);
}

UiMenu::~UiMenu()
{
	Elm_Win *win = this->getWindow();
	if (win) evas_object_event_callback_del(win, EVAS_CALLBACK_RESIZE, _winResizeCb);

	Elm_Ctxpopup *ctxpopup = this->unsetContent();
	evas_object_del(ctxpopup);
}

Elm_Win *UiMenu::getWindow()
{
	UiViewmgr *viewmgr = UI_VIEWMGR;
	if (!viewmgr) {
		LOGE("Viewmgr is null?? menu(%p)", this);
		return NULL;
	}

	return viewmgr->getWindow();
}

bool UiMenu::deactivate()
{
	Elm_Ctxpopup *ctxpopup = this->getContent();
	if (!ctxpopup)
	{
		LOGE("Content is not set! = UiMenu(%p)", this);
		return false;
	}

	elm_ctxpopup_dismiss(ctxpopup);
	dynamic_cast<UiView *>(this->getView())->onResume();

	return true;
}

bool UiMenu::activate()
{
	bool ret = _updateMenu(this);
	if (ret) dynamic_cast<UiView *>(this->getView())->onPause();

	return ret;
}

bool UiMenu::setContent(Elm_Ctxpopup *ctxpopup)
{
	Elm_Ctxpopup *prev = this->unsetContent();
	evas_object_del(prev);

	if (!ctxpopup) return true;

	if (strcmp(evas_object_type_get(ctxpopup), "elm_ctxpopup")) {
		LOGE("Menu widget is not a ctxpopup!");
		return false;
	}

	elm_object_style_set(ctxpopup, "more/default");
	elm_ctxpopup_auto_hide_disabled_set(ctxpopup, EINA_TRUE);
	evas_object_smart_callback_add(ctxpopup, "dismissed", _ctxpopupDismissedCb, NULL);
	evas_object_event_callback_add(ctxpopup, EVAS_CALLBACK_DEL, _ctxpopupDelCb, this);

	UiBaseOverlay::setContent(ctxpopup);

	return true;
}

bool UiMenu::isActivated()
{
	Elm_Ctxpopup *ctxpopup = this->getContent();
	if (!ctxpopup) return false;

	return evas_object_visible_get(ctxpopup);
}

Elm_Ctxpopup *UiMenu::unsetContent()
{
	Elm_Ctxpopup *ctxpopup = UiBaseOverlay::unsetContent();
	if (!ctxpopup) return NULL;

	evas_object_smart_callback_del(ctxpopup, "dismissed", _ctxpopupDismissedCb);
	evas_object_event_callback_del(ctxpopup, EVAS_CALLBACK_DEL, _ctxpopupDelCb);

	return ctxpopup;
}

Evas_Object *UiMenu::getBase()
{
	return this->getWindow();
}

int UiMenu::getDegree()
{
	return this->getView()->getDegree();
}
