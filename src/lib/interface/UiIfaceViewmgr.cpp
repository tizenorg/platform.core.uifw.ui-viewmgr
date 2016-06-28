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
	static UiIfaceViewmgr *inst;
	static bool soft_key;                      //If system doesn't support HW back key, then this value is @c true.
	static bool event_block;                   //Event block on view transition. This value should be configurable by system.
	list<UiIfaceView *> view_list;           //View list.
	bool activated;                            //Activated status of this viewmgr.
	bool destroying;                           //True, if viewmgr is on destroying.

public:
	bool connect_view(UiIfaceView *view);
	bool disconnect_view(UiIfaceView *view);
	void set_event_block(UiIfaceView *view, bool block);

	bool push_view_finished(UiIfaceView *view);
	bool pop_view_finished(UiIfaceView *view);
	UiIfaceView *push_view(UiIfaceView *view);
	bool pop_view();
	bool insert_view_before(UiIfaceView *view, UiIfaceView *before);
	bool insert_view_after(UiIfaceView *view, UiIfaceView *after);
	bool remove_view(UiIfaceView *view);
	UiIfaceView* get_view(unsigned int idx);
	UiIfaceView *get_view(const char *name);
	UiIfaceView *get_last_view();
	int get_view_index(const UiIfaceView *view);

	UiIfaceViewmgrImpl(UiIfaceViewmgr *viewmgr);
	~UiIfaceViewmgrImpl();

	bool activate();
	bool deactivate();
	bool is_activated();
	unsigned int get_view_count();
	static bool need_soft_key();
	static UiIfaceViewmgr* get_instance();
};

}

UiIfaceViewmgr* UiIfaceViewmgrImpl::inst = NULL;
//FIXME: Read system profile to decide whether support software key or not.
bool UiIfaceViewmgrImpl::soft_key = true;
//FIXME: Read system profile to decide whether support event block or not.
bool UiIfaceViewmgrImpl::event_block = true;

#define VIEW_ITR list<UiIfaceView *>::iterator
#define VIEW_RITR list<UiIfaceView *>::reverse_iterator

bool UiIfaceViewmgrImpl::insert_view_after(UiIfaceView *view, UiIfaceView *after)
{
	VIEW_ITR it;

	if (!view)
	{
		LOGE("invalid view argument. view(NULL)");
		return false;
	}

	if (!this->connect_view(view))
	{
		LOGE("connect view failed");
		return false;
	}

	if (this->view_list.size() > 0)
	{
		for (it = this->view_list.begin(); it != this->view_list.end(); it++)
		{
			if (after == *it)
			{
				//If the after is a last item of list.
				//view has to push now.
				if (it == this->view_list.end())
					this->push_view(view);
				else
					this->view_list.insert(++it, view);

				return true;
			}
		}
	}

	//If there is no matching after view with current list.
	//also in case of after is NULL.
	this->push_view(view);

	return true;
}

bool UiIfaceViewmgrImpl::need_soft_key()
{
	return UiIfaceViewmgrImpl::soft_key;
}

bool UiIfaceViewmgrImpl::connect_view(UiIfaceView *view)
{
	//TODO: Perform this only in debug mode?
	//Check whether the same name of this view is already existed in this viewmgr?
	int name_len = strlen(view->get_name());
	const char *name = view->get_name();

	for (VIEW_ITR it = this->view_list.begin(); it != this->view_list.end(); it++)
	{
		UiIfaceView *view = *it;
		const char *view_name = view->get_name();
		if (!view_name) continue;
		int view_name_len = strlen(view_name);

		//Got you!
		if ((view_name_len == name_len) && !strcmp(name, view_name))
		{
			LOGE("the same name of UiIfaceView(%p) is already in this UiIfaceViewmgr(%p)", view, this);
			return false;
		}
	}

	return view->set_viewmgr(this->get_instance());
}

bool UiIfaceViewmgrImpl::disconnect_view(UiIfaceView *view)
{
	if (!view->get_viewmgr()) return false;
	view->set_viewmgr(NULL);
	return true;
}

void UiIfaceViewmgrImpl::set_event_block(UiIfaceView *view, bool block)
{
	if (!UiIfaceViewmgrImpl::event_block) return;
	view->set_event_block(block);
}

bool UiIfaceViewmgrImpl::push_view_finished(UiIfaceView *view)
{
	UiIfaceView *last = this->view_list.back();

	//The previous view has been pushed. This should be unload.
	if (last != view)
	{
		view->on_unload();
		return true;
	}

	//A new view has been pushed. This should be activate.
	view->on_activate();
	this->set_event_block(view, false);

	return true;
}

bool UiIfaceViewmgrImpl::pop_view_finished(UiIfaceView *view)
{
	UiIfaceView *last = this->view_list.back();

	//This view has been popped. It should be destroyed.
	if (last == view)
	{
		view->on_unload();
		view->on_destroy();
		delete (view);
		return true;
	}

	//The previous view has been popped. It should become activate.
	view->on_activate();
	this->set_event_block(view, false);

	return true;
}

UiIfaceViewmgrImpl::UiIfaceViewmgrImpl(UiIfaceViewmgr* viewmgr)
		: activated(false), destroying(false)
{
	UiIfaceViewmgrImpl::inst = viewmgr;
}

UiIfaceViewmgrImpl::~UiIfaceViewmgrImpl()
{
	//Terminate views
	this->destroying = EINA_TRUE;
	for (VIEW_RITR ritr = this->view_list.rbegin(); ritr != this->view_list.rend(); ritr++)
	{
		UiIfaceView *view = *ritr;
		if ((view->get_state() != UI_VIEW_STATE_DEACTIVATE) &&
			(view->get_state() != UI_VIEW_STATE_UNLOAD))
		{
			view->on_deactivate();
		}
		if (view->get_state() != UI_VIEW_STATE_UNLOAD)
		{
			view->on_unload();
		}
		view->on_destroy();
		delete (view);
	}
	this->destroying = EINA_FALSE;

	ui_app_exit();

	UiIfaceViewmgrImpl::inst = NULL;
}

UiIfaceView *UiIfaceViewmgrImpl::push_view(UiIfaceView *view)
{
	if (!view)
	{
		LOGE("invalid view argument. view(NULL)");
		return NULL;
	}

	if (!this->connect_view(view))
	{
		LOGE("connect view failed");
		return NULL;
	}

	UiIfaceView *pview;

	//Previous view
	if (this->view_list.size() > 0)
	{
		pview = this->view_list.back();
		pview->on_deactivate();
		this->set_event_block(pview, true);
	}

	this->view_list.push_back(view);

	//If view manager is not activated yet, don't load view.
	if (!this->is_activated()) return view;

	view->on_load();
	view->on_deactivate();

	if (this->view_list.size() != 1)
	{
		this->set_event_block(view, true);
	}

	return view;
}

bool UiIfaceViewmgrImpl::pop_view()
{
	//last page to be popped.
	UiIfaceView*view = this->view_list.back();

	if (view->get_event_block())
	{
		return false;
	}

	//FIXME: No more view?
	if (this->get_view_count() == 0)
	{
		LOGE("No Views. Can't pop anymore!");
		return false;
	}

	//This is the last page.
	if (this->get_view_count() == 1)
	{
		//destroy viewmgr?
		UiIfaceView*view = this->view_list.back();
		view->on_deactivate();
		view->on_unload();
		view->on_destroy();
		delete(view);

		return true;
	}

	view->on_deactivate();
	this->set_event_block(view, true);

	//Below object has to be used in child class...
	//Make this getter method? or define instance?
	//previous page is to be an active page.
	auto nx = prev(this->view_list.end(), 2);
	UiIfaceView*pview = *nx;
	pview->on_load();
	pview->on_deactivate();
	this->set_event_block(pview, true);

	return true;
}

bool UiIfaceViewmgrImpl::insert_view_before(UiIfaceView *view, UiIfaceView *before)
{
	VIEW_ITR it;

	if (!view)
	{
		LOGE("invalid view argument. view(NULL)");
		return false;
	}

	if (!this->connect_view(view))
	{
		LOGE("connect view failed");
		return false;
	}

	if (this->view_list.size() > 0)
	{
		for (it = this->view_list.begin(); it != this->view_list.end(); it++)
		{
			if (before == *it)
			{
				this->view_list.insert(it, view);

				return true;
			}
		}
	}

	//If there is no matching before view with current list.
	//also in case of before is NULL.
	this->push_view(view);

	return true;
}

bool UiIfaceViewmgrImpl::remove_view(UiIfaceView *view)
{
	if (this->destroying) return false;

	this->view_list.remove(view);
	this->disconnect_view(view);

	//TODO: If this view is the top on the stack ?
	return true;
}

UiIfaceView *UiIfaceViewmgrImpl::get_view(unsigned int idx)
{
	if (idx < 0 || idx >= this->view_list.size())
	{
		LOGE("Invalid idx(%d)! =? (idx range: %d ~ %d)", idx, 0, this->view_list.size() - 1);
		return NULL;
	}
	VIEW_ITR it = this->view_list.begin();
	advance(it, idx);
	return *it;
}

int UiIfaceViewmgrImpl::get_view_index(const UiIfaceView *view)
{
	int idx = 0;

	for (VIEW_ITR it = this->view_list.begin(); it != this->view_list.end(); it++)
	{
		if (view == *it) return idx;
		++idx;
	}

	return -1;
}

UiIfaceView *UiIfaceViewmgrImpl::get_last_view()
{
	int cnt = this->get_view_count();
	return this->get_view(cnt - 1);
}

bool UiIfaceViewmgrImpl::activate()
{
	if (this->activated) return false;
	if (this->get_view_count() == 0) return false;
	this->activated = true;
	UiIfaceView *view = this->get_last_view();
	view->on_load();
	view->on_deactivate();
	view->on_activate();
	return true;
}

bool UiIfaceViewmgrImpl::deactivate()
{
	if (!this->activated) return false;
	this->activated = false;
	UiIfaceView *view = this->get_last_view();

	if ((view->get_state() != UI_VIEW_STATE_DEACTIVATE) &&
		(view->get_state() != UI_VIEW_STATE_UNLOAD))
	{
		view->on_deactivate();
	}
	if (view->get_state() != UI_VIEW_STATE_UNLOAD)
	{
		view->on_unload();
	}

	return true;
}

UiIfaceView *UiIfaceViewmgrImpl::get_view(const char *name)
{
	if (!name) return NULL;
	int name_len = strlen(name);

	for (VIEW_ITR it = this->view_list.begin(); it != this->view_list.end(); it++)
	{
		UiIfaceView *view = *it;
		const char *view_name = view->get_name();
		if (!view_name) continue;
		int view_name_len = strlen(view_name);

		//Got you!
		if ((view_name_len == name_len) && !strcmp(name, view_name))
		{
			return view;
		}
	}

	return NULL;
}

bool UiIfaceViewmgrImpl::is_activated()
{
	return this->activated;
}

unsigned int UiIfaceViewmgrImpl::get_view_count()
{
	return this->view_list.size();
}

UiIfaceViewmgr* UiIfaceViewmgrImpl::get_instance()
{
	return UiIfaceViewmgrImpl::inst;
}

/***********************************************************************************************/
/* External class Implementation                                                               */
/***********************************************************************************************/
bool UiIfaceViewmgr::insert_view_after(UiIfaceView *view, UiIfaceView *after)
{
	return this->impl->insert_view_after(view, after);
}

bool UiIfaceViewmgr::need_soft_key()
{
	return UiIfaceViewmgrImpl::need_soft_key();
}

bool UiIfaceViewmgr::push_view_finished(UiIfaceView *view)
{
	return this->impl->push_view_finished(view);
}

bool UiIfaceViewmgr::pop_view_finished(UiIfaceView *view)
{
	return this->impl->pop_view_finished(view);
}

UiIfaceViewmgr::UiIfaceViewmgr()
{
	this->impl = new UiIfaceViewmgrImpl(this);
}

UiIfaceViewmgr::~UiIfaceViewmgr()
{
	delete(this->impl);
}

UiIfaceView *UiIfaceViewmgr::push_view(UiIfaceView *view)
{
	return this->impl->push_view(view);
}

bool UiIfaceViewmgr::pop_view()
{
	return this->impl->pop_view();
}

bool UiIfaceViewmgr::insert_view_before(UiIfaceView *view, UiIfaceView *before)
{
	return this->impl->insert_view_before(view, before);
}

bool UiIfaceViewmgr::remove_view(UiIfaceView *view)
{
	return this->impl->remove_view(view);
}

UiIfaceView *UiIfaceViewmgr::get_view(unsigned int idx)
{
	return this->impl->get_view(idx);
}

int UiIfaceViewmgr::get_view_index(const UiIfaceView *view)
{
	return this->get_view_index(view);
}

UiIfaceView *UiIfaceViewmgr::get_last_view()
{
	return this->impl->get_last_view();
}

bool UiIfaceViewmgr::activate()
{
	return this->impl->activate();
}

bool UiIfaceViewmgr::deactivate()
{
	return this->impl->deactivate();
}

UiIfaceView *UiIfaceViewmgr::get_view(const char *name)
{
	return this->impl->get_view(name);
}

bool UiIfaceViewmgr::is_activated()
{
	return this->impl->is_activated();
}

unsigned int UiIfaceViewmgr::get_view_count()
{
	return this->impl->get_view_count();
}

UiIfaceViewmgr* UiIfaceViewmgr::get_instance()
{
	return UiIfaceViewmgrImpl::get_instance();
}
