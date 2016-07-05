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

#include "../../include/interface/UiIfaceViewManager.h"

using namespace ui_viewmanager;

/***********************************************************************************************/
/* Internal class Implementation                                                               */
/***********************************************************************************************/
namespace ui_viewmanager
{

class UiIfaceOverlayImpl
{
	friend class UiIfaceOverlay;

private:
	UiIfaceOverlay *_overlay;
	UiIfaceView *_view;
	T _content;

public:
	bool setContent(T content);
	T unsetContent();
	UiIfaceView *getView();
	T getContent();

	UiIfaceOverlayImpl(UiIfaceOverlay *overlay, UiIfaceView *view);
	~UiIfaceOverlayImpl();
};

}

UiIfaceOverlayImpl::UiIfaceOverlayImpl(UiIfaceOverlay *overlay, UiIfaceView *view)
		: _overlay(overlay), _view(view), _content(NULL)
{
}

UiIfaceOverlayImpl::~UiIfaceOverlayImpl()
{
}

bool UiIfaceOverlayImpl::setContent(T content)
{
	this->_content = content;
	return true;
}

T UiIfaceOverlayImpl::unsetContent()
{
	T prev = this->_content;
	this->_content = NULL;
	return prev;
}

T UiIfaceOverlayImpl::getContent()
{
	return this->_content;
}

UiIfaceView *UiIfaceOverlayImpl::getView()
{
	return this->_view;
}


/***********************************************************************************************/
/* External class Implementation                                                               */
/***********************************************************************************************/
UiIfaceOverlay::UiIfaceOverlay(UiIfaceView *view)
{
	this->_impl = new UiIfaceOverlayImpl(this, view);
}

UiIfaceOverlay::~UiIfaceOverlay()
{
	delete(this->_impl);
}

bool UiIfaceOverlay::setContent(T content)
{
	return this->_impl->setContent(content);
}

T UiIfaceOverlay::unsetContent()
{
	return this->_impl->unsetContent();
}

T UiIfaceOverlay::getContent()
{
	return this->_impl->getContent();
}

UiIfaceView *UiIfaceOverlay::getView()
{
	return this->_impl->getView();
}

void UiIfaceOverlay::onBack()
{
	this->deactivate();
}

bool UiIfaceOverlay::activate()
{
	return true;
}

bool UiIfaceOverlay::deactivate()
{
	return true;
}

bool UiIfaceOverlay::isActivated()
{
	return true;
}
