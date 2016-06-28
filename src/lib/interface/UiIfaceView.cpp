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
	UiIfaceView *view;
	T content;                              ///< A content instance for a screen as a view.
	string name;                            ///< View name.
	string transition_style;                ///< View transition style name.
	UiIfaceViewmgr *viewmgr;              ///< Viewmgr which this view belongs to.
	UiViewState state;                    ///< View state.
	UiViewIndicator indicator;            ///< View indicator mode.
	bool event_block;                       ///< State of event block.
	bool removable_content;                 ///< When this value is true, view removes it's content internally on unload state.

public:
	void set_event_block(bool block);
	void on_load();
	void on_unload();
	void on_activate();
	void on_deactivate();
	void on_pause();
	void on_resume();
	void on_destroy();
	bool get_event_block();
	bool set_content(T content);
	T unset_content();

	UiIfaceViewImpl(UiIfaceView *view, const char *name);
	~UiIfaceViewImpl();

	bool set_transition_style(const char *style);
	void set_removable_content(bool removable);
	void set_indicator(UiViewIndicator indicator);
	const char *get_transition_style();
	const char *get_name();
	T get_content();
	UiViewState get_state();
	bool get_removable_content();
	UiViewIndicator get_indicator();
	void on_back();
};

}

bool UiIfaceViewImpl::get_event_block()
{
	return this->event_block;
}

void UiIfaceViewImpl::set_event_block(bool block)
{
	this->event_block = block;
}

void UiIfaceViewImpl::on_load()
{
	this->state = UI_VIEW_STATE_LOAD;
}

void UiIfaceViewImpl::on_unload()
{
	this->state = UI_VIEW_STATE_UNLOAD;
	if (this->get_removable_content())
	{
		this->set_content(NULL);
		return;
	}
}

void UiIfaceViewImpl::on_activate()
{
	this->state = UI_VIEW_STATE_ACTIVATE;
}

void UiIfaceViewImpl::on_deactivate()
{
	this->state = UI_VIEW_STATE_DEACTIVATE;
}

void UiIfaceViewImpl::on_pause()
{
	this->state = UI_VIEW_STATE_PAUSE;
}

void UiIfaceViewImpl::on_resume()
{
	this->state = UI_VIEW_STATE_ACTIVATE;
}

void UiIfaceViewImpl::on_destroy()
{
}

UiIfaceViewImpl::UiIfaceViewImpl(UiIfaceView *view, const char *name)
		: view(view), content(NULL), name(string(name ? name : "")), transition_style(string("default")), viewmgr(NULL), state(UI_VIEW_STATE_LOAD),
		  indicator(UI_VIEW_INDICATOR_DEFAULT), event_block(false), removable_content(true)
{
	this->state = UI_VIEW_STATE_UNLOAD;
}

UiIfaceViewImpl::~UiIfaceViewImpl()
{
	this->viewmgr->remove_view(this->view);
}

bool UiIfaceViewImpl::set_content(T content)
{
	this->content = content;
	return true;
}

T UiIfaceViewImpl::unset_content()
{
	T prev = this->content;
	this->content = NULL;
	return prev;
}

bool UiIfaceViewImpl::set_transition_style(const char *style)
{
	this->transition_style.assign(style);
	return true;
}

void UiIfaceViewImpl::set_removable_content(bool removable)
{
	this->removable_content = removable;

	//FIXME: If this api is called on unload state? should we remove content right now?
}

void UiIfaceViewImpl::set_indicator(UiViewIndicator indicator)
{
	this->indicator = indicator;
}

const char *UiIfaceViewImpl::get_transition_style()
{
	return this->transition_style.c_str();
}

const char *UiIfaceViewImpl::get_name()
{
	return this->name.c_str();
}

T UiIfaceViewImpl::get_content()
{
	return this->content;
}

UiViewState UiIfaceViewImpl::get_state()
{
	return this->state;
}

bool UiIfaceViewImpl::get_removable_content()
{
	return this->removable_content;
}

UiViewIndicator UiIfaceViewImpl::get_indicator()
{
	return this->indicator;
}

void UiIfaceViewImpl::on_back()
{
	UiIfaceViewmgr *viewmgr = this->viewmgr;
	if (!viewmgr)
	{
		LOGE("Failed to get a viewmgr, view =%p", this);
		return;
	}
	viewmgr->pop_view();
}

/***********************************************************************************************/
/* External class Implementation                                                               */
/***********************************************************************************************/

bool UiIfaceView::get_event_block()
{
	return this->impl->get_event_block();
}

void UiIfaceView::set_event_block(bool block)
{
	this->impl->set_event_block(block);
}

void UiIfaceView::on_load()
{
	this->impl->on_load();
}

void UiIfaceView::on_unload()
{
	this->impl->on_unload();
}

void UiIfaceView::on_activate()
{
	this->impl->on_activate();
}

void UiIfaceView::on_deactivate()
{
	this->impl->on_deactivate();
}

void UiIfaceView::on_pause()
{
	this->impl->on_pause();
}

void UiIfaceView::on_resume()
{
	this->impl->on_resume();
}

void UiIfaceView::on_destroy()
{
	this->impl->on_destroy();
}

UiIfaceView::UiIfaceView(const char *name)
{
	this->impl = new UiIfaceViewImpl(this, name);
}

UiIfaceView::~UiIfaceView()
{
	delete(this->impl);
}

bool UiIfaceView::set_content(T content)
{
	return this->impl->set_content(content);
}

T UiIfaceView::unset_content()
{
	return this->impl->unset_content();
}

bool UiIfaceView::set_transition_style(const char *style)
{
	return this->impl->set_transition_style(style);
}

void UiIfaceView::set_removable_content(bool removable)
{
	this->impl->set_removable_content(removable);
}

void UiIfaceView::set_indicator(UiViewIndicator indicator)
{
	this->impl->set_indicator(indicator);
}

const char *UiIfaceView::get_transition_style()
{
	return this->impl->get_transition_style();
}

const char *UiIfaceView::get_name()
{
	return this->impl->get_name();
}

T UiIfaceView::get_content()
{
	return this->impl->get_content();
}

UiViewState UiIfaceView::get_state()
{
	return this->impl->get_state();
}

bool UiIfaceView::get_removable_content()
{
	return this->impl->get_removable_content();
}

UiViewIndicator UiIfaceView::get_indicator()
{
	return this->impl->get_indicator();
}

void UiIfaceView::on_back()
{
	this->impl->on_back();
}

bool UiIfaceView::set_viewmgr(UiIfaceViewmgr *viewmgr)
{
	this->impl->viewmgr = viewmgr;
	return true;
}

UiIfaceViewmgr *UiIfaceView::get_viewmgr()
{
	return this->impl->viewmgr;
}

void UiIfaceView::on_low_memory()
{
}

void UiIfaceView::on_low_battery()
{
}

void UiIfaceView::on_region_changed(const char *region)
{
}

void UiIfaceView::on_language_changed(const char *language)
{
}
