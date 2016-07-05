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

using namespace ui_viewmanager;
using namespace efl_viewmanager;

/***********************************************************************************************/
/* Internal class Implementation                                                               */
/***********************************************************************************************/
namespace efl_viewmanager
{
class UiBaseKeyListenerImpl
{
protected:
	UiBaseKeyListener *keyListener;
	UiBaseViewmgr *viewmgr;
	Evas_Object *keyGrabber;

public:
	UiBaseKeyListenerImpl(UiBaseKeyListener *key_listener, UiBaseViewmgr *viewmgr);
	~UiBaseKeyListenerImpl() {}

	bool init();
	bool term();
	void eventProc(Evas_Event_Key_Down *ev);
	UiBaseViewmgr *getViewmgr() { return this->viewmgr; }
	Evas_Object *getKeygrabObj() { return this->keyGrabber; }
};
}

static const char *KEY_BACK = "XF86Back";
static const char *KEY_BACK2 = "XF86Stop";

static void _keyGrabRectKeyUpCb(UiBaseKeyListenerImpl *keyListener, Evas_Event_Key_Down *ev)
{
	keyListener->eventProc(ev);
}

UiBaseKeyListenerImpl::UiBaseKeyListenerImpl(UiBaseKeyListener *keyListener, UiBaseViewmgr *viewmgr)
		: keyListener(keyListener), viewmgr(viewmgr), keyGrabber(NULL)
{
}

void UiBaseKeyListenerImpl::eventProc(Evas_Event_Key_Down *ev)
{
	//Only if view manager is activated
	UiBaseViewmgr *viewmgr = this->keyListener->getViewmgr();
	if (!viewmgr->isActivated()) return;

	//Get Top View
	UiBaseView *view = viewmgr->getLastView();
	if (!view) return;

	this->keyListener->extendEventProc(view, ev);

	if (strcmp(ev->keyname, KEY_BACK) && strcmp(ev->keyname, KEY_BACK2)) return;

	view->onBack();
}

bool UiBaseKeyListenerImpl::term()
{
	evas_object_del(this->keyGrabber);

	return true;
}

bool UiBaseKeyListenerImpl::init()
{
	if (!this->viewmgr) {
		LOGE("No view manager??");
		return false;
	}

	Evas *e = evas_object_evas_get(this->viewmgr->getWindow());
	if (!e) {
		LOGE("Failed to get Evas from window");
		return false;
	}

	Evas_Object *keyGrabRect = evas_object_rectangle_add(e);
	if (!keyGrabRect) {
		LOGE("Failed to create a key grabber rectangle");
		return false;
	}

	evas_object_event_callback_add(keyGrabRect, EVAS_CALLBACK_KEY_UP, [](void *data, Evas *e, Evas_Object *obj, void *event_info) -> void
	{
		Evas_Event_Key_Down *ev = static_cast<Evas_Event_Key_Down *>(event_info);
		UiBaseKeyListenerImpl *keyListener = static_cast<UiBaseKeyListenerImpl *>(data);
		_keyGrabRectKeyUpCb(keyListener, ev);
	}, this);

	if (!evas_object_key_grab(keyGrabRect, KEY_BACK, 0, 0, EINA_FALSE)) {
		LOGE("Failed to grab BACK KEY(%s)\n", KEY_BACK);
		evas_object_del(keyGrabRect);
		return false;
	}

	if (!evas_object_key_grab(keyGrabRect, KEY_BACK2, 0, 0, EINA_FALSE)) {
		LOGE("Failed to grab BACK KEY(%s)\n", KEY_BACK2);
		evas_object_del(keyGrabRect);
		return false;
	}

	this->keyGrabber = keyGrabRect;

	return true;
}


/***********************************************************************************************/
/* External class Implementation                                                               */
/***********************************************************************************************/

UiBaseKeyListener::UiBaseKeyListener(UiBaseViewmgr *viewmgr)
{
	this->_impl = new UiBaseKeyListenerImpl(this, viewmgr);
}

UiBaseKeyListener::~UiBaseKeyListener()
{
	delete(this->_impl);
}

bool UiBaseKeyListener::term()
{
	return this->_impl->term();
}

bool UiBaseKeyListener::init()
{
	return this->_impl->init();
}

Evas_Object *UiBaseKeyListener::getKeygrabObj()
{
	return this->_impl->getKeygrabObj();
}


UiBaseViewmgr *UiBaseKeyListener::getViewmgr()
{
	return this->_impl->getViewmgr();
}
