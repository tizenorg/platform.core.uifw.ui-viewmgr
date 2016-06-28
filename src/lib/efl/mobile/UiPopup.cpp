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

static bool update_popup(UiPopup *popup)
{
	Elm_Win *win = popup->get_base();
	if (!win) return false;

	Elm_Popup *_popup = popup->get_content();
	if (!_popup) return false;

	evas_object_show(_popup);

	return true;
}

static void popup_dismissed_cb(void *data, Evas_Object *obj, void *event_info)
{
	evas_object_hide(obj);
}

static void popup_del_cb(void *data, Evas *e, Evas_Object *obj, void *event_info)
{
	UiPopup *popup = static_cast<UiPopup *>(data);
	popup->unset_content();
}

UiPopup::UiPopup(UiView *view)
		: UiBaseOverlay(view)
{
	view->connect_popup(this);
}

UiPopup::~UiPopup()
{
	dynamic_cast<UiView *>(this->get_view())->disconnect_popup(this);
	Elm_Popup *popup = this->unset_content();
	evas_object_del(popup);
}

Elm_Win *UiPopup::get_window()
{
	UiViewmgr *viewmgr = UI_VIEWMGR;
	if (!viewmgr)
	{
		LOGE("Viewmgr is null?? menu(%p)", this);
		return NULL;
	}
	return viewmgr->get_window();
}

bool UiPopup::deactivate()
{
	Elm_Popup *popup = this->get_content();
	if (!popup)
	{
		LOGE("Content is not set! = UiPopup(%p)", this);
		return false;
	}

	elm_popup_dismiss(popup);
	dynamic_cast<UiView*>(this->get_view())->on_resume();

	return true;
}

bool UiPopup::activate()
{
	bool ret = update_popup(this);
	if (ret) dynamic_cast<UiView*>(this->get_view())->on_pause();
	return ret;
}

bool UiPopup::set_content(Elm_Popup *popup)
{
	Elm_Popup *prev = this->unset_content();
	evas_object_del(prev);

	if (!popup) return true;

	if (strcmp(evas_object_type_get(popup), "elm_popup"))
	{
		LOGE("Menu widget is not a popup!");
		return false;
	}

	elm_popup_align_set(popup, ELM_NOTIFY_ALIGN_FILL, 1.0);
	evas_object_event_callback_add(popup, EVAS_CALLBACK_DEL, popup_del_cb, this);
	evas_object_smart_callback_add(popup, "dismissed", popup_dismissed_cb, this);

	UiBaseOverlay::set_content(popup);

	return true;
}

bool UiPopup::is_activated()
{
	Elm_Popup *popup = this->get_content();
	if (!popup) return false;
	return evas_object_visible_get(popup);
}

Elm_Popup *UiPopup::unset_content()
{
	Elm_Popup *popup = UiBaseOverlay::unset_content();
	if (!popup) return NULL;

	evas_object_event_callback_del(popup, EVAS_CALLBACK_DEL, popup_del_cb);
	evas_object_smart_callback_del(popup, "dismissed", popup_dismissed_cb);

	return popup;
}

Evas_Object *UiPopup::get_base()
{
	return this->get_window();
}

int UiPopup::get_degree()
{
	return this->get_view()->get_degree();
}
