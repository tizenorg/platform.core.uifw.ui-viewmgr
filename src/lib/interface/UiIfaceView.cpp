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

#include <string>

using namespace std;

/***********************************************************************************************/
/* Internal class Implementation                                                               */
/***********************************************************************************************/
namespace ui_viewmanager
{

class UiIfaceViewImpl
{
	friend class UiIfaceViewmgrImpl;
	friend class UiIfaceView;

private:
	UiIfaceView *_view;
	T _content;                              ///< A content instance for a screen as a view.
	string _name;                            ///< View name.
	string _transition_style;                ///< View transition style name.
	UiIfaceViewmgr *_viewmgr;              ///< Viewmgr which this view belongs to.
	UiViewState _state;                    ///< View state.
	UiViewIndicator _indicator;            ///< View indicator mode.
	bool _event_block;                       ///< State of event block.
	bool _removable_content;                 ///< When this value is true, view removes it's content internally on unload state.

public:
	void setEventBlock(bool block);
	void onLoad();
	void onUnload();
	void onActivate();
	void onDeactivate();
	void onPause();
	void onResume();
	void onDestroy();
	bool getEventBlock();
	bool setContent(T content);
	T unsetContent();

	UiIfaceViewImpl(UiIfaceView *view, const char *name);
	~UiIfaceViewImpl();

	bool setTransitionStyle(const char *style);
	void setRemovableContent(bool removable);
	void setIndicator(UiViewIndicator indicator);
	const char *getTransitionStyle();
	const char *getName();
	T getContent();
	UiViewState getState();
	bool getRemovableContent();
	UiViewIndicator getIndicator();
	void onBack();
};

}

bool UiIfaceViewImpl::getEventBlock()
{
	return this->_event_block;
}

void UiIfaceViewImpl::setEventBlock(bool block)
{
	this->_event_block = block;
}

void UiIfaceViewImpl::onLoad()
{
	this->_state = UI_VIEW_STATE_LOAD;
}

void UiIfaceViewImpl::onUnload()
{
	this->_state = UI_VIEW_STATE_UNLOAD;
	if (this->getRemovableContent())
	{
		this->setContent(NULL);
		return;
	}
}

void UiIfaceViewImpl::onActivate()
{
	this->_state = UI_VIEW_STATE_ACTIVATE;
}

void UiIfaceViewImpl::onDeactivate()
{
	this->_state = UI_VIEW_STATE_DEACTIVATE;
}

void UiIfaceViewImpl::onPause()
{
	this->_state = UI_VIEW_STATE_PAUSE;
}

void UiIfaceViewImpl::onResume()
{
	this->_state = UI_VIEW_STATE_ACTIVATE;
}

void UiIfaceViewImpl::onDestroy()
{
}

UiIfaceViewImpl::UiIfaceViewImpl(UiIfaceView *view, const char *name)
		: _view(view), _content(NULL), _name(string(name ? name : "")), _transition_style(string("default")), _viewmgr(NULL), _state(UI_VIEW_STATE_LOAD),
		  _indicator(UI_VIEW_INDICATOR_DEFAULT), _event_block(false), _removable_content(true)
{
	this->_state = UI_VIEW_STATE_UNLOAD;
}

UiIfaceViewImpl::~UiIfaceViewImpl()
{
	this->_viewmgr->removeView(this->_view);
}

bool UiIfaceViewImpl::setContent(T content)
{
	this->_content = content;
	return true;
}

T UiIfaceViewImpl::unsetContent()
{
	T prev = this->_content;
	this->_content = NULL;
	return prev;
}

bool UiIfaceViewImpl::setTransitionStyle(const char *style)
{
	this->_transition_style.assign(style);
	return true;
}

void UiIfaceViewImpl::setRemovableContent(bool removable)
{
	this->_removable_content = removable;

	//FIXME: If this api is called on unload state? should we remove content right now?
}

void UiIfaceViewImpl::setIndicator(UiViewIndicator indicator)
{
	this->_indicator = indicator;
}

const char *UiIfaceViewImpl::getTransitionStyle()
{
	return this->_transition_style.c_str();
}

const char *UiIfaceViewImpl::getName()
{
	return this->_name.c_str();
}

T UiIfaceViewImpl::getContent()
{
	return this->_content;
}

UiViewState UiIfaceViewImpl::getState()
{
	return this->_state;
}

bool UiIfaceViewImpl::getRemovableContent()
{
	return this->_removable_content;
}

UiViewIndicator UiIfaceViewImpl::getIndicator()
{
	return this->_indicator;
}

void UiIfaceViewImpl::onBack()
{
	UiIfaceViewmgr *viewmgr = this->_viewmgr;
	if (!viewmgr)
	{
		LOGE("Failed to get a viewmgr, view =%p", this);
		return;
	}
	viewmgr->popView();
}

/***********************************************************************************************/
/* External class Implementation                                                               */
/***********************************************************************************************/

bool UiIfaceView::getEventBlock()
{
	return this->_impl->getEventBlock();
}

void UiIfaceView::setEventBlock(bool block)
{
	this->_impl->setEventBlock(block);
}

void UiIfaceView::onLoad()
{
	this->_impl->onLoad();
}

void UiIfaceView::onUnload()
{
	this->_impl->onUnload();
}

void UiIfaceView::onActivate()
{
	this->_impl->onActivate();
}

void UiIfaceView::onDeactivate()
{
	this->_impl->onDeactivate();
}

void UiIfaceView::onPause()
{
	this->_impl->onPause();
}

void UiIfaceView::onResume()
{
	this->_impl->onResume();
}

void UiIfaceView::onDestroy()
{
	this->_impl->onDestroy();
}

UiIfaceView::UiIfaceView(const char *name)
{
	this->_impl = new UiIfaceViewImpl(this, name);
}

UiIfaceView::~UiIfaceView()
{
	delete(this->_impl);
}

bool UiIfaceView::setContent(T content)
{
	return this->_impl->setContent(content);
}

T UiIfaceView::unsetContent()
{
	return this->_impl->unsetContent();
}

bool UiIfaceView::setTransitionStyle(const char *style)
{
	return this->_impl->setTransitionStyle(style);
}

void UiIfaceView::setRemovableContent(bool removable)
{
	this->_impl->setRemovableContent(removable);
}

void UiIfaceView::setIndicator(UiViewIndicator indicator)
{
	this->_impl->setIndicator(indicator);
}

const char *UiIfaceView::getTransitionStyle()
{
	return this->_impl->getTransitionStyle();
}

const char *UiIfaceView::getName()
{
	return this->_impl->getName();
}

T UiIfaceView::getContent()
{
	return this->_impl->getContent();
}

UiViewState UiIfaceView::getState()
{
	return this->_impl->getState();
}

bool UiIfaceView::getRemovableContent()
{
	return this->_impl->getRemovableContent();
}

UiViewIndicator UiIfaceView::getIndicator()
{
	return this->_impl->getIndicator();
}

void UiIfaceView::onBack()
{
	this->_impl->onBack();
}

bool UiIfaceView::_setViewmgr(UiIfaceViewmgr *viewmgr)
{
	this->_impl->_viewmgr = viewmgr;
	return true;
}

UiIfaceViewmgr *UiIfaceView::_getViewmgr()
{
	return this->_impl->_viewmgr;
}

void UiIfaceView::onLowMemory()
{
}

void UiIfaceView::onLowBattery()
{
}

void UiIfaceView::onRegionChanged(const char *region)
{
}

void UiIfaceView::onLanguageChanged(const char *language)
{
}
