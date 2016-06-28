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
#include "../../include/efl/UiBaseViewManager.h"

/***********************************************************************************************/
/* Internal class Implementation                                                               */
/***********************************************************************************************/
namespace efl_viewmanager
{
class UiBaseKeyListenerImpl
{
protected:
	UiBaseKeyListener *key_listener;
	UiBaseViewmgr *viewmgr;
	Evas_Object *key_grabber;

public:
	UiBaseKeyListenerImpl(UiBaseKeyListener *key_listener, UiBaseViewmgr *viewmgr);
	~UiBaseKeyListenerImpl() {}

	bool init();
	bool term();
	void event_proc(Evas_Event_Key_Down *ev);
	UiBaseViewmgr *get_viewmgr() { return this->viewmgr; }
	Evas_Object *get_keygrab_obj() { return this->key_grabber; }
};
}

static const char *KEY_BACK = "XF86Back";
static const char *KEY_BACK2 = "XF86Stop";

static void key_grab_rect_key_up_cb(UiBaseKeyListenerImpl *key_listener, Evas_Event_Key_Down *ev)
{
	key_listener->event_proc(ev);
}

UiBaseKeyListenerImpl::UiBaseKeyListenerImpl(UiBaseKeyListener *key_listener, UiBaseViewmgr *viewmgr)
		: key_listener(key_listener), viewmgr(viewmgr), key_grabber(NULL)
{
}

void UiBaseKeyListenerImpl::event_proc(Evas_Event_Key_Down *ev)
{
	//Only if view manager is activated
	UiBaseViewmgr *viewmgr = this->key_listener->get_viewmgr();
	if (!viewmgr->is_activated()) return;

	//Get Top View
	UiBaseView *view = viewmgr->get_last_view();
	if (!view) return;

	this->key_listener->extend_event_proc(view, ev);

	if (strcmp(ev->keyname, KEY_BACK) && strcmp(ev->keyname, KEY_BACK2)) return;

	view->on_back();
}

bool UiBaseKeyListenerImpl::term()
{
	evas_object_del(this->key_grabber);
	return true;
}

bool UiBaseKeyListenerImpl::init()
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
		UiBaseKeyListenerImpl *key_listener = static_cast<UiBaseKeyListenerImpl *>(data);
		key_grab_rect_key_up_cb(key_listener, ev);
	}, this);

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

UiBaseKeyListener::UiBaseKeyListener(UiBaseViewmgr *viewmgr)
{
	this->impl = new UiBaseKeyListenerImpl(this, viewmgr);
}

UiBaseKeyListener::~UiBaseKeyListener()
{
	delete(this->impl);
}

bool UiBaseKeyListener::term()
{
	return this->impl->term();
}

bool UiBaseKeyListener::init()
{
	return this->impl->init();
}

Evas_Object *UiBaseKeyListener::get_keygrab_obj()
{
	return this->impl->get_keygrab_obj();
}


UiBaseViewmgr *UiBaseKeyListener::get_viewmgr()
{
	return this->impl->get_viewmgr();
}
