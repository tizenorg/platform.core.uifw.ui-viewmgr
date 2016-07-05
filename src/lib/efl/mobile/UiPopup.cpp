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

static bool _updatePopup(UiPopup *popup)
{
	Elm_Win *win = popup->getBase();
	if (!win) return false;

	Elm_Popup *_popup = popup->getContent();
	if (!_popup) return false;

	evas_object_show(_popup);

	return true;
}

static void _popupDismissedCb(void *data, Evas_Object *obj, void *event_info)
{
	evas_object_hide(obj);
}

static void _popupDelCb(void *data, Evas *e, Evas_Object *obj, void *event_info)
{
	UiPopup *popup = static_cast<UiPopup *>(data);
	popup->unsetContent();
}

UiPopup::UiPopup(UiView *view)
		: UiBaseOverlay(view)
{
	view->_connectPopup(this);
}

UiPopup::~UiPopup()
{
	dynamic_cast<UiView *>(this->getView())->_disconnectPopup(this);
	Elm_Popup *popup = this->unsetContent();
	evas_object_del(popup);
}

Elm_Win *UiPopup::getWindow()
{
	UiViewmgr *viewmgr = UI_VIEWMGR;
	if (!viewmgr) {
		LOGE("Viewmgr is null?? menu(%p)", this);
		return NULL;
	}

	return viewmgr->getWindow();
}

bool UiPopup::deactivate()
{
	Elm_Popup *popup = this->getContent();
	if (!popup) {
		LOGE("Content is not set! = UiPopup(%p)", this);
		return false;
	}

	elm_popup_dismiss(popup);
	dynamic_cast<UiView*>(this->getView())->onResume();

	return true;
}

bool UiPopup::activate()
{
	bool ret = _updatePopup(this);
	if (ret) dynamic_cast<UiView*>(this->getView())->onPause();
	return ret;
}

bool UiPopup::setContent(Elm_Popup *popup)
{
	Elm_Popup *prev = this->unsetContent();
	evas_object_del(prev);

	if (!popup) return true;

	if (strcmp(evas_object_type_get(popup), "elm_popup")) {
		LOGE("Menu widget is not a popup!");
		return false;
	}

	elm_popup_align_set(popup, ELM_NOTIFY_ALIGN_FILL, 1.0);
	evas_object_event_callback_add(popup, EVAS_CALLBACK_DEL, _popupDelCb, this);
	evas_object_smart_callback_add(popup, "dismissed", _popupDismissedCb, this);

	UiBaseOverlay::setContent(popup);

	return true;
}

bool UiPopup::isActivated()
{
	Elm_Popup *popup = this->getContent();
	if (!popup) return false;
	return evas_object_visible_get(popup);
}

Elm_Popup *UiPopup::unsetContent()
{
	Elm_Popup *popup = UiBaseOverlay::unsetContent();
	if (!popup) return NULL;

	evas_object_event_callback_del(popup, EVAS_CALLBACK_DEL, _popupDelCb);
	evas_object_smart_callback_del(popup, "dismissed", _popupDismissedCb);

	return popup;
}

Evas_Object *UiPopup::getBase()
{
	return this->getWindow();
}

int UiPopup::getDegree()
{
	return this->getView()->getDegree();
}
