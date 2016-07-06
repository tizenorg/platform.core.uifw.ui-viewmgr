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
class UiBaseViewImpl;
}

/***********************************************************************************************/
/* External class Implementation                                                               */
/***********************************************************************************************/

static void _contentDelCb(void *data, Evas *e, Evas_Object *obj, void *event_info)
{
	UiBaseView *view = static_cast<UiBaseView *>(data);
	view->unsetContent();
}

UiBaseView::UiBaseView(const char *name)
		: UiIfaceView(name)
{
}

UiBaseView::~UiBaseView()
{
}

bool UiBaseView::setContent(Evas_Object *content)
{
	Evas_Object *pcontent = this->unsetContent();

	if (pcontent) {
		evas_object_del(pcontent);
	}

	if (content) {
		evas_object_event_callback_add(content, EVAS_CALLBACK_DEL, _contentDelCb, this);
		UiIfaceView::setContent(content);
	}

	return true;
}

Evas_Object *UiBaseView::unsetContent()
{
	Evas_Object *obj = UiIfaceView::unsetContent();

	if (obj) {
		evas_object_event_callback_del(obj, EVAS_CALLBACK_DEL, _contentDelCb);
		evas_object_hide(obj);
	}

	return obj;
}

Evas_Object *UiBaseView::getBase()
{
	UiBaseViewmgr *viewmgr = UI_BASE_VIEWMGR;

	if (!viewmgr) {
		return NULL;
	}

	return viewmgr->getBase();
}

Evas_Object *UiBaseView ::getParent()
{
	UiBaseViewmgr *viewmgr = UI_BASE_VIEWMGR;

	if (!viewmgr) {
		LOGE("Failed to get a viewmgr");
		return NULL;
	}

	return viewmgr->getBase();
}

void UiBaseView::setIndicator(UiViewIndicator indicator)
{
	if (this->getIndicator() == indicator) return;

	UiIfaceView::setIndicator(indicator);

	UiBaseViewmgr *viewmgr = UI_BASE_VIEWMGR;

	if (!viewmgr) {
		LOGE("Failed to get a viewmgr");
		return;
	}

	if (!viewmgr->isActivated()) return;

	if (viewmgr->getLastView() != this) return;

	viewmgr->setIndicator(indicator);
}

void UiBaseView::setAvailableRotations(int *rotations, int count)
{
	UiIfaceView::setAvailableRotations(rotations, count);

	UiBaseViewmgr *viewmgr = UI_BASE_VIEWMGR;

	if (!viewmgr) {
		LOGE("Failed to get a viewmgr");
		return;
	}

	elm_win_wm_rotation_available_rotations_set(viewmgr->getWindow(), rotations, count);
}

void UiBaseView::onRotate(int degree)
{
}

void UiBaseView::onPortrait()
{
}

void UiBaseView::onLandscape()
{
}

void UiBaseView::setEventBlock(bool block)
{
	UiIfaceView::setEventBlock(block);

	evas_object_freeze_events_set(this->getContent(), block);
}

int UiBaseView::getDegree()
{
	UiBaseViewmgr *viewmgr = UI_BASE_VIEWMGR;

	if (!viewmgr) {
		LOGE("Failed to get a viewmgr");
		return -1;
	}

	return elm_win_rotation_get(viewmgr->getWindow());
}

