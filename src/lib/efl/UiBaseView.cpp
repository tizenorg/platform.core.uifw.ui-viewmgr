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
class UiBaseViewImpl;
}

/***********************************************************************************************/
/* External class Implementation                                                               */
/***********************************************************************************************/

static void content_del_cb(void *data, Evas *e, Evas_Object *obj, void *event_info)
{
	UiBaseView *view = static_cast<UiBaseView *>(data);
	view->unset_content();
}

UiBaseView::UiBaseView(const char *name)
		: UiIfaceView(name)
{
}

UiBaseView::~UiBaseView()
{
}

bool UiBaseView::set_content(Evas_Object *content)
{
	Evas_Object *pcontent = this->unset_content();
	if (pcontent)
	{
		evas_object_del(pcontent);
	}
	if (content)
	{
		evas_object_event_callback_add(content, EVAS_CALLBACK_DEL, content_del_cb, this);
		UiIfaceView::set_content(content);
	}
	return true;
}

Evas_Object *UiBaseView::unset_content()
{
	Evas_Object *obj = UiIfaceView::unset_content();
	if (obj)
	{
		evas_object_event_callback_del(obj, EVAS_CALLBACK_DEL, content_del_cb);
		evas_object_hide(obj);
	}
	return obj;
}

Evas_Object *UiBaseView::get_base()
{
	UiBaseViewmgr *viewmgr = UI_BASE_VIEWMGR;
	if (!viewmgr)
	{
		return NULL;
	}
	return viewmgr->get_base();
}

Evas_Object *UiBaseView ::get_parent()
{
	UiBaseViewmgr *viewmgr = UI_BASE_VIEWMGR;
	if (!viewmgr)
	{
		LOGE("Failed to get a viewmgr");
		return NULL;
	}
	return viewmgr->get_base();
}

void UiBaseView::set_indicator(UiViewIndicator indicator)
{
	if (this->get_indicator() == indicator) return;

	UiIfaceView::set_indicator(indicator);

	UiBaseViewmgr *viewmgr = UI_BASE_VIEWMGR;
	if (!viewmgr)
	{
		LOGE("Failed to get a viewmgr");
		return;
	}

	if (!viewmgr->is_activated()) return;

	if (viewmgr->get_last_view() != this) return;

	viewmgr->set_indicator(indicator);
}

void UiBaseView::on_rotate(int degree)
{
}

void UiBaseView::on_portrait()
{
}

void UiBaseView::on_landscape()
{
}

void UiBaseView::set_event_block(bool block)
{
	UiIfaceView::set_event_block(block);
	evas_object_freeze_events_set(this->get_content(), block);
}

int UiBaseView::get_degree()
{
	UiBaseViewmgr *viewmgr = UI_BASE_VIEWMGR;
	if (!viewmgr)
	{
		LOGE("Failed to get a viewmgr");
		return -1;
	}
	return elm_win_rotation_get(viewmgr->get_window());
}

