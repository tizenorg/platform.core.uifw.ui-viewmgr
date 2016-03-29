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

static void ctxpopup_dismissed_cb(void *data, Evas_Object *obj, void *event_info)
{
	evas_object_hide(obj);
}

static void ctxpopup_del_cb(void *data, Evas *e, Evas_Object *obj, void *event_info)
{
	ui_menu *menu = static_cast<ui_menu *>(data);
	menu->unset_content();
}

static bool update_menu(ui_menu *menu)
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
	ui_menu *menu = static_cast<ui_menu *>(data);
	Elm_Ctxpopup *ctxpopup = menu->get_content();
	if (!ctxpopup) return;
	if (!evas_object_visible_get(ctxpopup)) return;
	update_menu(menu);
}

ui_menu::ui_menu(ui_view *view)
		: view(view), ctxpopup(NULL)
{
	Elm_Win *win = this->get_window();
	evas_object_event_callback_add(win, EVAS_CALLBACK_RESIZE, win_resize_cb, this);
}

ui_menu::~ui_menu()
{
	Elm_Win *win = this->get_window();
	if (win) evas_object_event_callback_del(win, EVAS_CALLBACK_RESIZE, win_resize_cb);
	evas_object_del(this->ctxpopup);
}

Elm_Win *ui_menu::get_window()
{
	ui_viewmgr *viewmgr = UI_VIEWMGR;
	if (!viewmgr)
	{
		LOGE("Viewmgr is null?? menu(%p)", this);
		return NULL;
	}

	return viewmgr->get_window();
}

bool ui_menu::deactivate()
{
	if (this->ctxpopup)
	{
		elm_ctxpopup_dismiss(this->ctxpopup);
	}
	else
	{
		LOGE("Content is not set! = ui_menu(%p)", this);
		return false;
	}

	this->view->on_resume();

	return true;
}

bool ui_menu::activate()
{
	bool ret = update_menu(this);
	if (ret) this->view->on_pause();
	return ret;
}

bool ui_menu::set_content(Elm_Ctxpopup *ctxpopup)
{
	evas_object_del(this->ctxpopup);

	//validation!
	//FIXME: isa ?
	if (strcmp(evas_object_type_get(ctxpopup), "elm_ctxpopup"))
	{
		LOGE("Menu widget is not a ctxpopup!");
		return false;
	}

	//FIXME: rename style.
	elm_object_style_set(ctxpopup, "more/default");
	elm_ctxpopup_auto_hide_disabled_set(ctxpopup, EINA_TRUE);
	evas_object_smart_callback_add(ctxpopup, "dismissed", ctxpopup_dismissed_cb, NULL);
	evas_object_event_callback_add(ctxpopup, EVAS_CALLBACK_DEL, ctxpopup_del_cb, this);

	this->ctxpopup = ctxpopup;

	return true;
}

bool ui_menu::is_activated()
{
	if (!this->ctxpopup) return false;
	return evas_object_visible_get(this->ctxpopup);
}

Elm_Ctxpopup *ui_menu::unset_content()
{
	if (!this->ctxpopup) return NULL;

	Elm_Ctxpopup *prev = this->ctxpopup;
	this->ctxpopup = NULL;
	evas_object_smart_callback_del(prev, "dismissed", ctxpopup_dismissed_cb);
	evas_object_event_callback_del(prev, EVAS_CALLBACK_DEL, ctxpopup_del_cb);
	return prev;
}

Evas_Object *ui_menu::get_base()
{
	if (!this->view)
	{
		LOGE("View is null?? menu(%p)", this);
		return NULL;
	}

	return this->get_window();
}

void ui_menu::on_back()
{
	this->deactivate();
}

int ui_menu::get_degree()
{
	return this->view->get_degree();
}
