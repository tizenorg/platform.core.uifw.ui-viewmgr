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
#include <list>
#include "../../../include/efl/mobile/UiMobileViewManager.h"

/***********************************************************************************************/
/* Internal class Implementation                                                               */
/***********************************************************************************************/

using namespace std;

namespace efl_viewmanager
{

class UiViewImpl
{
	friend class UiView;

private:
	UiView *_view;
	UiMenu *_menu;
	list<UiPopup *> _popupList;

	void _connectPopup(UiPopup *popup);
	void _disconnectPopup(UiPopup *popup);
	bool _deactivatePopup(bool topOne);

protected:
	UiMenu *onMenuPre();
	void onMenuPost();
	void onRotate(int degree);
	void onPortrait();
	void onLandscape();
	bool onBack();

public:
	UiViewImpl(UiView *view);
	~UiViewImpl();

	const UiMenu *getMenu()
	{
		return this->_menu;
	}

	UiViewOrientationMode getOrientationMode();
};

}

typedef list<UiPopup*>::reverse_iterator popupRitr;

void UiViewImpl::_connectPopup(UiPopup *popup)
{
	this->_popupList.push_back(popup);
}

void UiViewImpl::_disconnectPopup(UiPopup *popup)
{
	this->_popupList.remove(popup);
}

bool UiViewImpl::_deactivatePopup(bool topOne)
{
	for (popupRitr it = this->_popupList.rbegin(); it != this->_popupList.rend(); it++) {
		UiPopup *popup = *it;
		if (!popup->isActivated()) continue;
		popup->onBack();
		//deactivate only one top one? or all popups?
		if (topOne) return true;
	}

	return false;
}

bool UiViewImpl::onBack()
{
	//If any popup is activated, deactivate the popup first.
	if (this->_deactivatePopup(true)) {
		return false;
	}

	if (this->_menu) {
		if (this->_menu->isActivated()) {
			this->_menu->onBack();
			return false;
		}
	}

	return true;
}

UiViewImpl::UiViewImpl(UiView *view)
		: _view(view), _menu(NULL)
{
}

UiViewImpl::~UiViewImpl()
{
	if (_menu) delete (this->_menu);
}

UiMenu *UiViewImpl::onMenuPre()
{
	if (!this->_menu) {
		this->_menu = new UiMenu(this->_view);
	}

	if (this->_menu->isActivated()) {
		this->_menu->deactivate();

		return NULL;
	}

	return this->_menu;
}

void UiViewImpl::onMenuPost()
{
	if (!this->_menu) return;

	this->_menu->activate();
}

void UiViewImpl::onRotate(int degree)
{
	if (!this->_menu) return;
	if (!this->_menu->isActivated()) return;

	this->_menu->onRotate(degree);
}

void UiViewImpl::onPortrait()
{
	if (!this->_menu) return;
	if (!this->_menu->isActivated()) return;

	this->_menu->onPortrait();
}

void UiViewImpl::onLandscape()
{
	if (!this->_menu) return;
	if (!this->_menu->isActivated()) return;

	this->_menu->onLandscape();
}

UiViewOrientationMode UiViewImpl::getOrientationMode()
{
	switch (this->_view->getDegree()) {
		case 0:
		case 180:
			return UI_VIEW_ORIENTATION_MODE_PORTRAIT;
			break;
		case 90:
		case 270:
			return UI_VIEW_ORIENTATION_MODE_LANDSCAPE;
			break;
		}

	return UI_VIEW_ORIENTATION_MODE_UNKOWN;
}


/***********************************************************************************************/
/* External class Implementation                                                               */
/***********************************************************************************************/

void UiView::_connectPopup(UiPopup *popup)
{
	this->_impl->_connectPopup(popup);
}

void UiView::_disconnectPopup(UiPopup *popup)
{
	this->_impl->_disconnectPopup(popup);
}

void UiView::onDeactivate()
{
	this->_impl->_deactivatePopup(false);

	UiBaseView::onDeactivate();
}

void UiView::onBack()
{
	if (!this->_impl->onBack()) return;

	UiBaseView::onBack();
}

UiView::UiView(const char *name)
		: UiBaseView(name)
{
	this->_impl = new UiViewImpl(this);
}

UiView::~UiView()
{
	delete(this->_impl);
}

UiMenu *UiView::onMenuPre()
{
	return this->_impl->onMenuPre();
}

void UiView::onMenu(UiMenu *menu)
{
}

void UiView::onMenuPost()
{
	this->_impl->onMenuPost();
}

void UiView::onRotate(int degree)
{
	//FIXME: see how to handle on_menu()
	UiBaseView::onRotate(degree);

	this->_impl->onRotate(degree);
}

void UiView::onPortrait()
{
	//FIXME: see how to handle on_menu()
	UiBaseView::onPortrait();

	this->_impl->onPortrait();
}

void UiView::onLandscape()
{
	//FIXME: see how to handle on_menu()
	UiBaseView::onLandscape();

	this->_impl->onLandscape();
}

UiViewOrientationMode UiView::getOrientationMode()
{
	return this->_impl->getOrientationMode();
}

const UiMenu *UiView::getMenu()
{
	return this->_impl->getMenu();
}
