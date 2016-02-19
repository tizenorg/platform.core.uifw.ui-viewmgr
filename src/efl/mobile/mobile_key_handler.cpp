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
#include "../efl_viewmgr.h"
#include "mobile_key_handler.h"

using namespace efl;

static const char *KEY_BACK = "XF86Back";
static const char *KEY_MENU = "XF86Menu";

enum mobile_key_event_type
{
	UI_KEY_EVENT_BACK = 0,
	UI_KEY_EVENT_MENU
};

mobile_key_handler::mobile_key_handler(ui_viewmgr *viewmgr)
		: ui_key_handler(viewmgr)
{
}

static void event_proc(mobile_key_handler *key_handler, Evas_Event_Key_Down *ev)
{
   mobile_key_event_type type;

   if (!strcmp(ev->keyname, KEY_BACK))
     type = UI_KEY_EVENT_BACK;
   else if (!strcmp(ev->keyname, KEY_MENU))
     type = UI_KEY_EVENT_MENU;
   else return;

   ui_viewmgr *viewmgr = key_handler->get_viewmgr();
   if (!viewmgr->is_activated()) return;

   //Get Top View
   ui_view *view = reinterpret_cast<ui_view *>(viewmgr->get_last_view());
   if (!view) return;

   //call events
   switch (type)
   {
   case UI_KEY_EVENT_BACK:
	   //view->back();
	   LOGE("BACK!");
	   break;
   case UI_KEY_EVENT_MENU:
	   //view->menu();
	   LOGE("MENU!");
	   break;
   }
}

bool mobile_key_handler::term()
{
	evas_object_del(this->key_grabber);
	return true;
}

bool mobile_key_handler::init()
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

	evas_object_event_callback_add(key_grab_rect, EVAS_CALLBACK_KEY_UP,
			[](void *data, Evas *e, Evas_Object *obj, void *event_info) -> void
			{
				Evas_Event_Key_Down *ev = static_cast<Evas_Event_Key_Down *>(event_info);
				mobile_key_handler *key_handler = static_cast<mobile_key_handler *>(data);
				event_proc(key_handler, ev);
			},
			this);

	if (!evas_object_key_grab(key_grab_rect, KEY_BACK, 0, 0, EINA_FALSE))
	{
	     LOGE("Failed to grab BACK KEY(%s)\n", KEY_BACK);
	     evas_object_del(key_grab_rect);
	     return false;
	}

	if (!evas_object_key_grab(key_grab_rect, KEY_MENU, 0, 0, EINA_FALSE))
	{
	     LOGE("Failed to grab MENU KEY(%s)\n", KEY_MENU);
	     evas_object_del(key_grab_rect);
	     return false;
	}

	this->key_grabber = key_grab_rect;

	return true;
}
