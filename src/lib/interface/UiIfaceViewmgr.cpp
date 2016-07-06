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

#include <app.h>
#include <list>

#include "../../include/interface/UiIfaceViewManager.h"

using namespace ui_viewmanager;
using namespace std;

/***********************************************************************************************/
/* Internal class Implementation                                                               */
/***********************************************************************************************/
namespace ui_viewmanager
{

class UiIfaceViewmgrImpl
{
	friend class UiIfaceViewImpl;
	friend class UiIfaceViewmgr;

private:
	static UiIfaceViewmgr *_inst;
	static bool _softKey;                      //If system doesn't support HW back key, then this value is @c true.
	static bool _eventBlock;                   //Event block on view transition. This value should be configurable by system.
	list<UiIfaceView *> _viewList;           //View list.
	bool _activated;                            //Activated status of this viewmgr.
	bool _destroying;                           //True, if viewmgr is on destroying.

public:
	bool connectView(UiIfaceView *view);
	bool disconnectView(UiIfaceView *view);
	void setEventBlock(UiIfaceView *view, bool block);

	bool pushViewFinished(UiIfaceView *view);
	bool popViewFinished(UiIfaceView *view);
	UiIfaceView *pushView(UiIfaceView *view);
	bool popView();
	bool insertViewBefore(UiIfaceView *view, UiIfaceView *before);
	bool insertViewAfter(UiIfaceView *view, UiIfaceView *after);
	bool removeView(UiIfaceView *view);
	UiIfaceView *getView(unsigned int idx);
	UiIfaceView *getView(const char *name);
	UiIfaceView *getLastView();
	int getViewIndex(const UiIfaceView *view);

	explicit UiIfaceViewmgrImpl(UiIfaceViewmgr *viewmgr);
	~UiIfaceViewmgrImpl();

	bool activate();
	bool deactivate();
	bool isActivated();
	unsigned int getViewCount();
	static bool needSoftKey();
	static UiIfaceViewmgr* getInstance();
};

}

UiIfaceViewmgr* UiIfaceViewmgrImpl::_inst = NULL;
//FIXME: Read system profile to decide whether support software key or not.
bool UiIfaceViewmgrImpl::_softKey = true;
//FIXME: Read system profile to decide whether support event block or not.
bool UiIfaceViewmgrImpl::_eventBlock = true;

#define VIEW_ITR list<UiIfaceView *>::iterator
#define VIEW_RITR list<UiIfaceView *>::reverse_iterator

bool UiIfaceViewmgrImpl::insertViewAfter(UiIfaceView *view, UiIfaceView *after)
{
	VIEW_ITR it;

	if (!view) {
		LOGE("invalid view argument. view(NULL)");
		return false;
	}

	if (!this->connectView(view)) {
		LOGE("connect view failed");
		return false;
	}

	if (this->_viewList.size() > 0) {
		for (it = this->_viewList.begin(); it != this->_viewList.end(); it++) {
			if (after == *it) {
				//If the after is a last item of list.
				//view has to push now.
				if (it == this->_viewList.end())
					this->pushView(view);
				else
					this->_viewList.insert(++it, view);

				return true;
			}
		}
	}

	//If there is no matching after view with current list.
	//also in case of after is NULL.
	this->pushView(view);

	return true;
}

bool UiIfaceViewmgrImpl::needSoftKey()
{
	return UiIfaceViewmgrImpl::_softKey;
}

bool UiIfaceViewmgrImpl::connectView(UiIfaceView *view)
{
	//TODO: Perform this only in debug mode?
	//Check whether the same name of this view is already existed in this viewmgr?
	int nameLen = strlen(view->getName());
	const char *name = view->getName();

	for (UiIfaceView *v : this->_viewList) {
		const char *viewName = v->getName();
		if (!viewName) continue;
		int viewNameLen = strlen(viewName);

		//Got you!
		if ((viewNameLen == nameLen) && !strcmp(name, viewName)) {
			LOGE("the same name of UiIfaceView(%p) is already in this UiIfaceViewmgr(%p)", v, this);
			return false;
		}
	}

	return view->_setViewmgr(this->getInstance());
}

bool UiIfaceViewmgrImpl::disconnectView(UiIfaceView *view)
{
	if (!view->_getViewmgr()) return false;
	view->_setViewmgr(NULL);
	return true;
}

void UiIfaceViewmgrImpl::setEventBlock(UiIfaceView *view, bool block)
{
	if (!UiIfaceViewmgrImpl::_eventBlock) return;
	view->setEventBlock(block);
}

bool UiIfaceViewmgrImpl::pushViewFinished(UiIfaceView *view)
{
	UiIfaceView *last = this->_viewList.back();

	//The previous view has been pushed. This should be unload.
	if (last != view) {
		view->onUnload();
		return true;
	}

	//A new view has been pushed. This should be activate.
	view->onActivate();
	this->setEventBlock(view, false);

	return true;
}

bool UiIfaceViewmgrImpl::popViewFinished(UiIfaceView *view)
{
	UiIfaceView *last = this->_viewList.back();

	//This view has been popped. It should be destroyed.
	if (last == view) {
		view->onUnload();
		view->onDestroy();
		delete (view);
		return true;
	}

	//The previous view has been popped. It should become activate.
	view->onActivate();
	this->setEventBlock(view, false);

	return true;
}

UiIfaceViewmgrImpl::UiIfaceViewmgrImpl(UiIfaceViewmgr* viewmgr)
		: _activated(false), _destroying(false)
{
	UiIfaceViewmgrImpl::_inst = viewmgr;
}

UiIfaceViewmgrImpl::~UiIfaceViewmgrImpl()
{
	//Terminate views
	this->_destroying = EINA_TRUE;
	for (VIEW_RITR ritr = this->_viewList.rbegin(); ritr != this->_viewList.rend(); ritr++) {
		UiIfaceView *view = *ritr;
		if ((view->getState() != UI_VIEW_STATE_DEACTIVATE) &&
			(view->getState() != UI_VIEW_STATE_UNLOAD)) {
			view->onDeactivate();
		}
		if (view->getState() != UI_VIEW_STATE_UNLOAD) {
			view->onUnload();
		}

		view->onDestroy();
		delete (view);
	}
	this->_destroying = EINA_FALSE;

	ui_app_exit();

	UiIfaceViewmgrImpl::_inst = NULL;
}

UiIfaceView *UiIfaceViewmgrImpl::pushView(UiIfaceView *view)
{
	if (!view) {
		LOGE("invalid view argument. view(NULL)");
		return NULL;
	}

	if (!this->connectView(view)) {
		LOGE("connect view failed");
		return NULL;
	}

	UiIfaceView *pview;

	//Previous view
	if (this->_viewList.size() > 0) {
		pview = this->_viewList.back();
		pview->onDeactivate();
		this->setEventBlock(pview, true);
	}

	this->_viewList.push_back(view);

	//If view manager is not activated yet, don't load view.
	if (!this->isActivated()) return view;

	view->onLoad();
	view->onDeactivate();

	if (this->_viewList.size() != 1) {
		this->setEventBlock(view, true);
	}

	return view;
}

bool UiIfaceViewmgrImpl::popView()
{
	//last page to be popped.
	UiIfaceView*view = this->_viewList.back();

	if (view->getEventBlock()) {
		return false;
	}

	//FIXME: No more view?
	if (this->getViewCount() == 0) {
		LOGE("No Views. Can't pop anymore!");
		return false;
	}

	//This is the last page.
	if (this->getViewCount() == 1) {
		//destroy viewmgr?
		UiIfaceView*view = this->_viewList.back();
		view->onDeactivate();
		view->onUnload();
		view->onDestroy();
		delete(view);

		return true;
	}

	view->onDeactivate();
	this->setEventBlock(view, true);

	//Below object has to be used in child class...
	//Make this getter method? or define instance?
	//previous page is to be an active page.
	auto nx = prev(this->_viewList.end(), 2);
	UiIfaceView*pview = *nx;
	pview->onLoad();
	pview->onDeactivate();
	this->setEventBlock(pview, true);

	return true;
}

bool UiIfaceViewmgrImpl::insertViewBefore(UiIfaceView *view, UiIfaceView *before)
{
	VIEW_ITR it;

	if (!view) {
		LOGE("invalid view argument. view(NULL)");
		return false;
	}

	if (!this->connectView(view)) {
		LOGE("connect view failed");
		return false;
	}

	if (this->_viewList.size() > 0) {
		for (it = this->_viewList.begin(); it != this->_viewList.end(); it++) {
			if (before == *it) {
				this->_viewList.insert(it, view);

				return true;
			}
		}
	}

	//If there is no matching before view with current list.
	//also in case of before is NULL.
	this->pushView(view);

	return true;
}

bool UiIfaceViewmgrImpl::removeView(UiIfaceView *view)
{
	if (this->_destroying) return false;

	this->_viewList.remove(view);
	this->disconnectView(view);

	//TODO: If this view is the top on the stack ?
	return true;
}

UiIfaceView *UiIfaceViewmgrImpl::getView(unsigned int idx)
{
	if (idx < 0 || idx >= this->_viewList.size()) {
		LOGE("Invalid idx(%d)! =? (idx range: %d ~ %d)", idx, 0, this->_viewList.size() - 1);
		return NULL;
	}

	VIEW_ITR it = this->_viewList.begin();
	advance(it, idx);
	return *it;
}

int UiIfaceViewmgrImpl::getViewIndex(const UiIfaceView *view)
{
	int idx = 0;

	for (UiIfaceView *v : this->_viewList) {
		if (view == v) return idx;
		++idx;
	}

	return -1;
}

UiIfaceView *UiIfaceViewmgrImpl::getLastView()
{
	int cnt = this->getViewCount();

	return this->getView(cnt - 1);
}

bool UiIfaceViewmgrImpl::activate()
{
	if (this->_activated) return false;
	if (this->getViewCount() == 0) return false;
	this->_activated = true;

	UiIfaceView *view = this->getLastView();

	view->onLoad();
	view->onDeactivate();
	view->onActivate();

	return true;
}

bool UiIfaceViewmgrImpl::deactivate()
{
	if (!this->_activated) return false;
	this->_activated = false;

	UiIfaceView *view = this->getLastView();

	if ((view->getState() != UI_VIEW_STATE_DEACTIVATE) &&
		(view->getState() != UI_VIEW_STATE_UNLOAD)) {
		view->onDeactivate();
	}
	if (view->getState() != UI_VIEW_STATE_UNLOAD) {
		view->onUnload();
	}

	return true;
}

UiIfaceView *UiIfaceViewmgrImpl::getView(const char *name)
{
	if (!name) return NULL;
	int nameLen = strlen(name);

	for (UiIfaceView *v : this->_viewList) {
		const char *viewName = v->getName();
		if (!viewName) continue;
		int viewNameLen = strlen(viewName);

		//Got you!
		if ((viewNameLen == nameLen) && !strcmp(name, viewName)) {
			return v;
		}
	}

	return NULL;
}

bool UiIfaceViewmgrImpl::isActivated()
{
	return this->_activated;
}

unsigned int UiIfaceViewmgrImpl::getViewCount()
{
	return this->_viewList.size();
}

UiIfaceViewmgr* UiIfaceViewmgrImpl::getInstance()
{
	return UiIfaceViewmgrImpl::_inst;
}

/***********************************************************************************************/
/* External class Implementation                                                               */
/***********************************************************************************************/
bool UiIfaceViewmgr::insertViewAfter(UiIfaceView *view, UiIfaceView *after)
{
	return this->_impl->insertViewAfter(view, after);
}

bool UiIfaceViewmgr::needSoftKey()
{
	return UiIfaceViewmgrImpl::needSoftKey();
}

bool UiIfaceViewmgr::pushViewFinished(UiIfaceView *view)
{
	return this->_impl->pushViewFinished(view);
}

bool UiIfaceViewmgr::popViewFinished(UiIfaceView *view)
{
	return this->_impl->popViewFinished(view);
}

UiIfaceViewmgr::UiIfaceViewmgr()
{
	this->_impl = new UiIfaceViewmgrImpl(this);
}

UiIfaceViewmgr::~UiIfaceViewmgr()
{
	delete(this->_impl);
}

UiIfaceView *UiIfaceViewmgr::pushView(UiIfaceView *view)
{
	return this->_impl->pushView(view);
}

bool UiIfaceViewmgr::popView()
{
	return this->_impl->popView();
}

bool UiIfaceViewmgr::insertViewBefore(UiIfaceView *view, UiIfaceView *before)
{
	return this->_impl->insertViewBefore(view, before);
}

bool UiIfaceViewmgr::removeView(UiIfaceView *view)
{
	return this->_impl->removeView(view);
}

UiIfaceView *UiIfaceViewmgr::getView(unsigned int idx)
{
	return this->_impl->getView(idx);
}

int UiIfaceViewmgr::getViewIndex(const UiIfaceView *view)
{
	return this->getViewIndex(view);
}

UiIfaceView *UiIfaceViewmgr::getLastView()
{
	return this->_impl->getLastView();
}

bool UiIfaceViewmgr::activate()
{
	return this->_impl->activate();
}

bool UiIfaceViewmgr::deactivate()
{
	return this->_impl->deactivate();
}

UiIfaceView *UiIfaceViewmgr::getView(const char *name)
{
	return this->_impl->getView(name);
}

bool UiIfaceViewmgr::isActivated()
{
	return this->_impl->isActivated();
}

unsigned int UiIfaceViewmgr::getViewCount()
{
	return this->_impl->getViewCount();
}

UiIfaceViewmgr* UiIfaceViewmgr::getInstance()
{
	return UiIfaceViewmgrImpl::getInstance();
}
