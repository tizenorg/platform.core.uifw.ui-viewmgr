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

static void ctxpopup_dismissed_cb(void *data, Evas_Object *obj, void *event_info)
{
	evas_object_hide(obj);
}

static void ctxpopup_del_cb(void *data, Evas *e, Evas_Object *obj, void *event_info)
{
	UiMenu *menu = static_cast<UiMenu *>(data);
	menu->unset_content();
}

static bool update_menu(UiMenu *menu)
{
	Elm_Win *win = menu->get_base();
	if (!win) return false;

	Elm_Ctxpopup *ctxpopup = menu->get_content();
	if (!ctxpopup) return false;

	/* We convince the top widget is a window */
	Evas_Coord w, h;
	elm_win_screen_size_get(win, NULL, NULL, &w, &h);
	int rot = elm_win_rotation_get(win);

	switch (rot)
	{
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

static void win_resize_cb(void *data, Evas *e, Evas_Object *obj, void *event_info)
{
	UiMenu *menu = static_cast<UiMenu *>(data);
	if (!menu->is_activated()) return;
	update_menu(menu);
}

UiMenu::UiMenu(UiView *view)
		: UiBaseOverlay(view)
{
	Elm_Win *win = this->get_window();
	evas_object_event_callback_add(win, EVAS_CALLBACK_RESIZE, win_resize_cb, this);
}

UiMenu::~UiMenu()
{
	Elm_Win *win = this->get_window();
	if (win) evas_object_event_callback_del(win, EVAS_CALLBACK_RESIZE, win_resize_cb);
	Elm_Ctxpopup *ctxpopup = this->unset_content();
	evas_object_del(ctxpopup);
}

Elm_Win *UiMenu::get_window()
{
	UiViewmgr *viewmgr = UI_VIEWMGR;
	if (!viewmgr)
	{
		LOGE("Viewmgr is null?? menu(%p)", this);
		return NULL;
	}

	return viewmgr->get_window();
}

bool UiMenu::deactivate()
{
	Elm_Ctxpopup *ctxpopup = this->get_content();
	if (!ctxpopup)
	{
		LOGE("Content is not set! = UiMenu(%p)", this);
		return false;
	}

	elm_ctxpopup_dismiss(ctxpopup);
	dynamic_cast<UiView *>(this->get_view())->on_resume();

	return true;
}

bool UiMenu::activate()
{
	bool ret = update_menu(this);
	if (ret) dynamic_cast<UiView *>(this->get_view())->on_pause();
	return ret;
}

bool UiMenu::set_content(Elm_Ctxpopup *ctxpopup)
{
	Elm_Ctxpopup *prev = this->unset_content();
	evas_object_del(prev);

	if (!ctxpopup) return true;

	if (strcmp(evas_object_type_get(ctxpopup), "elm_ctxpopup"))
	{
		LOGE("Menu widget is not a ctxpopup!");
		return false;
	}

	elm_object_style_set(ctxpopup, "more/default");
	elm_ctxpopup_auto_hide_disabled_set(ctxpopup, EINA_TRUE);
	evas_object_smart_callback_add(ctxpopup, "dismissed", ctxpopup_dismissed_cb, NULL);
	evas_object_event_callback_add(ctxpopup, EVAS_CALLBACK_DEL, ctxpopup_del_cb, this);

	UiBaseOverlay::set_content(ctxpopup);

	return true;
}

bool UiMenu::is_activated()
{
	Elm_Ctxpopup *ctxpopup = this->get_content();
	if (!ctxpopup) return false;
	return evas_object_visible_get(ctxpopup);
}

Elm_Ctxpopup *UiMenu::unset_content()
{
	Elm_Ctxpopup *ctxpopup = UiBaseOverlay::unset_content();
	if (!ctxpopup) return NULL;

	evas_object_smart_callback_del(ctxpopup, "dismissed", ctxpopup_dismissed_cb);
	evas_object_event_callback_del(ctxpopup, EVAS_CALLBACK_DEL, ctxpopup_del_cb);

	return ctxpopup;
}

Evas_Object *UiMenu::get_base()
{
	return this->get_window();
}

int UiMenu::get_degree()
{
	return this->get_view()->get_degree();
}
