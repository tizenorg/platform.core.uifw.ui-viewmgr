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
#include "../../include/efl/ui_base_viewmanager.h"

/***********************************************************************************************/
/* Internal class Implementation                                                               */
/***********************************************************************************************/
namespace efl_viewmanager
{
class ui_base_key_listener_impl
{
protected:
	ui_base_key_listener *key_listener;
	ui_base_viewmgr *viewmgr;
	Evas_Object *key_grabber;

public:
	ui_base_key_listener_impl(ui_base_key_listener *key_listener, ui_base_viewmgr *viewmgr);
	~ui_base_key_listener_impl() {}

	bool init();
	bool term();
	ui_base_viewmgr *get_viewmgr() { return this->viewmgr; }
	Evas_Object *get_keygrab_obj() { return this->key_grabber; }
};
}

static const char *KEY_BACK = "XF86Back";
static const char *KEY_BACK2 = "XF86Stop";

static void event_proc(ui_base_key_listener *key_listener, Evas_Event_Key_Down *ev)
{
	//Only if view manager is activated
	ui_base_viewmgr *viewmgr = key_listener->get_viewmgr();
	if (!viewmgr->is_activated()) return;

	//Get Top View
	ui_base_view *view = viewmgr->get_last_view();
	if (!view) return;

	key_listener->extend_event_proc(view, ev);

	if (strcmp(ev->keyname, KEY_BACK) && strcmp(ev->keyname, KEY_BACK2)) return;

	view->on_back();
}

ui_base_key_listener_impl::ui_base_key_listener_impl(ui_base_key_listener *key_listener, ui_base_viewmgr *viewmgr)
		: key_listener(key_listener), viewmgr(viewmgr), key_grabber(NULL)
{

}

bool ui_base_key_listener_impl::term()
{
	evas_object_del(this->key_grabber);
	return true;
}

bool ui_base_key_listener_impl::init()
{
	if (!this->viewmgr)
	{
		LOGE("No view manager??");
		return false;
	}

	Evas *e = evas_object_evas_get(this->viewmgr->get_window());
	if (!e)
	{
		LOGE("Failed to get Evas from window");
		return false;
	}

	Evas_Object *key_grab_rect = evas_object_rectangle_add(e);
	if (!key_grab_rect)
	{
		LOGE("Failed to create a key grabber rectangle");
		return false;
	}

	evas_object_event_callback_add(key_grab_rect, EVAS_CALLBACK_KEY_UP, [](void *data, Evas *e, Evas_Object *obj, void *event_info) -> void
	{
		Evas_Event_Key_Down *ev = static_cast<Evas_Event_Key_Down *>(event_info);
		ui_base_key_listener *key_listener = static_cast<ui_base_key_listener *>(data);
		event_proc(key_listener, ev);
	}, this->key_listener);

	if (!evas_object_key_grab(key_grab_rect, KEY_BACK, 0, 0, EINA_FALSE))
	{
		LOGE("Failed to grab BACK KEY(%s)\n", KEY_BACK);
		evas_object_del(key_grab_rect);
		return false;
	}

	if (!evas_object_key_grab(key_grab_rect, KEY_BACK2, 0, 0, EINA_FALSE))
	{
		LOGE("Failed to grab BACK KEY(%s)\n", KEY_BACK2);
		evas_object_del(key_grab_rect);
		return false;
	}

	this->key_grabber = key_grab_rect;

	return true;
}


/***********************************************************************************************/
/* External class Implementation                                                               */
/***********************************************************************************************/

ui_base_key_listener::ui_base_key_listener(ui_base_viewmgr *viewmgr)
{
	this->impl = new ui_base_key_listener_impl(this, viewmgr);
}

ui_base_key_listener::~ui_base_key_listener()
{
	delete(this->impl);
}

bool ui_base_key_listener::term()
{
	return this->impl->term();
}

bool ui_base_key_listener::init()
{
	return this->impl->init();
}

Evas_Object *ui_base_key_listener::get_keygrab_obj()
{
	return this->impl->get_keygrab_obj();
}


ui_base_viewmgr *ui_base_key_listener::get_viewmgr()
{
	return this->impl->get_viewmgr();
}
