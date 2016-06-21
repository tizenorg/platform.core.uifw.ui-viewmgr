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
#include "../../include/interface/ui_iface_viewmanager.h"

using namespace std;

/***********************************************************************************************/
/* Internal class Implementation                                                               */
/***********************************************************************************************/
namespace ui_viewmanager
{

class ui_iface_viewmgr_impl
{
	friend class ui_iface_view_impl;
	friend class ui_iface_viewmgr;

private:
	static ui_iface_viewmgr *inst;
	static bool soft_key;                      //If system doesn't support HW back key, then this value is @c true.
	static bool event_block;                   //Event block on view transition. This value should be configurable by system.
	list<ui_iface_view *> view_list;           //View list.
	bool activated;                            //Activated status of this viewmgr.
	bool destroying;                           //True, if viewmgr is on destroying.

public:
	bool connect_view(ui_iface_view *view);
	bool disconnect_view(ui_iface_view *view);
	void set_event_block(ui_iface_view *view, bool block);

	bool push_view_finished(ui_iface_view *view);
	bool pop_view_finished(ui_iface_view *view);
	ui_iface_view *push_view(ui_iface_view *view);
	bool pop_view();
	bool insert_view_before(ui_iface_view *view, ui_iface_view *before);
	bool insert_view_after(ui_iface_view *view, ui_iface_view *after);
	bool remove_view(ui_iface_view *view);
	ui_iface_view* get_view(unsigned int idx);
	ui_iface_view *get_view(const char *name);
	ui_iface_view *get_last_view();
	int get_view_index(const ui_iface_view *view);

	ui_iface_viewmgr_impl(ui_iface_viewmgr *viewmgr);
	~ui_iface_viewmgr_impl();

	bool activate();
	bool deactivate();
	bool is_activated();
	unsigned int get_view_count();
	static bool need_soft_key();
	static ui_iface_viewmgr* get_instance();
};

}

ui_iface_viewmgr* ui_iface_viewmgr_impl::inst = NULL;
//FIXME: Read system profile to decide whether support software key or not.
bool ui_iface_viewmgr_impl::soft_key = true;
//FIXME: Read system profile to decide whether support event block or not.
bool ui_iface_viewmgr_impl::event_block = true;

#define VIEW_ITR list<ui_iface_view *>::iterator
#define VIEW_RITR list<ui_iface_view *>::reverse_iterator

bool ui_iface_viewmgr_impl::insert_view_after(ui_iface_view *view, ui_iface_view *after)
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

bool ui_iface_viewmgr_impl::need_soft_key()
{
	return ui_iface_viewmgr_impl::soft_key;
}

bool ui_iface_viewmgr_impl::connect_view(ui_iface_view *view)
{
	//TODO: Perform this only in debug mode?
	//Check whether the same name of this view is already existed in this viewmgr?
	int name_len = strlen(view->get_name());
	const char *name = view->get_name();

	for (VIEW_ITR it = this->view_list.begin(); it != this->view_list.end(); it++)
	{
		ui_iface_view *view = *it;
		const char *view_name = view->get_name();
		if (!view_name) continue;
		int view_name_len = strlen(view_name);

		//Got you!
		if ((view_name_len == name_len) && !strcmp(name, view_name))
		{
			LOGE("the same name of ui_iface_view(%p) is already in this ui_iface_viewmgr(%p)", view, this);
			return false;
		}
	}

	return view->set_viewmgr(this->get_instance());
}

bool ui_iface_viewmgr_impl::disconnect_view(ui_iface_view *view)
{
	if (!view->get_viewmgr()) return false;
	view->set_viewmgr(NULL);
	return true;
}

void ui_iface_viewmgr_impl::set_event_block(ui_iface_view *view, bool block)
{
	if (!ui_iface_viewmgr_impl::event_block) return;
	view->set_event_block(block);
}

bool ui_iface_viewmgr_impl::push_view_finished(ui_iface_view *view)
{
	ui_iface_view *last = this->view_list.back();

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

bool ui_iface_viewmgr_impl::pop_view_finished(ui_iface_view *view)
{
	ui_iface_view *last = this->view_list.back();

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

ui_iface_viewmgr_impl::ui_iface_viewmgr_impl(ui_iface_viewmgr* viewmgr)
		: activated(false), destroying(false)
{
	ui_iface_viewmgr_impl::inst = viewmgr;
}

ui_iface_viewmgr_impl::~ui_iface_viewmgr_impl()
{
	//Terminate views
	this->destroying = EINA_TRUE;
	for (VIEW_RITR ritr = this->view_list.rbegin(); ritr != this->view_list.rend(); ritr++)
	{
		ui_iface_view *view = *ritr;
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

	ui_iface_viewmgr_impl::inst = NULL;
}

ui_iface_view *ui_iface_viewmgr_impl::push_view(ui_iface_view *view)
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

	ui_iface_view *pview;

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

bool ui_iface_viewmgr_impl::pop_view()
{
	//last page to be popped.
	ui_iface_view*view = this->view_list.back();

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
		ui_iface_view*view = this->view_list.back();
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
	ui_iface_view*pview = *nx;
	pview->on_load();
	pview->on_deactivate();
	this->set_event_block(pview, true);

	return true;
}

bool ui_iface_viewmgr_impl::insert_view_before(ui_iface_view *view, ui_iface_view *before)
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

bool ui_iface_viewmgr_impl::remove_view(ui_iface_view *view)
{
	if (this->destroying) return false;

	this->view_list.remove(view);
	this->disconnect_view(view);

	//TODO: If this view is the top on the stack ?
	return true;
}

ui_iface_view *ui_iface_viewmgr_impl::get_view(unsigned int idx)
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

int ui_iface_viewmgr_impl::get_view_index(const ui_iface_view *view)
{
	int idx = 0;

	for (VIEW_ITR it = this->view_list.begin(); it != this->view_list.end(); it++)
	{
		if (view == *it) return idx;
		++idx;
	}

	return -1;
}

ui_iface_view *ui_iface_viewmgr_impl::get_last_view()
{
	int cnt = this->get_view_count();
	return this->get_view(cnt - 1);
}

bool ui_iface_viewmgr_impl::activate()
{
	if (this->activated) return false;
	if (this->get_view_count() == 0) return false;
	this->activated = true;
	ui_iface_view *view = this->get_last_view();
	view->on_load();
	view->on_deactivate();
	view->on_activate();
	return true;
}

bool ui_iface_viewmgr_impl::deactivate()
{
	if (!this->activated) return false;
	this->activated = false;
	ui_iface_view *view = this->get_last_view();

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

ui_iface_view *ui_iface_viewmgr_impl::get_view(const char *name)
{
	if (!name) return NULL;
	int name_len = strlen(name);

	for (VIEW_ITR it = this->view_list.begin(); it != this->view_list.end(); it++)
	{
		ui_iface_view *view = *it;
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

bool ui_iface_viewmgr_impl::is_activated()
{
	return this->activated;
}

unsigned int ui_iface_viewmgr_impl::get_view_count()
{
	return this->view_list.size();
}

ui_iface_viewmgr* ui_iface_viewmgr_impl::get_instance()
{
	return ui_iface_viewmgr_impl::inst;
}

/***********************************************************************************************/
/* External class Implementation                                                               */
/***********************************************************************************************/
bool ui_iface_viewmgr::insert_view_after(ui_iface_view *view, ui_iface_view *after)
{
	return this->impl->insert_view_after(view, after);
}

bool ui_iface_viewmgr::need_soft_key()
{
	return ui_iface_viewmgr_impl::need_soft_key();
}

bool ui_iface_viewmgr::push_view_finished(ui_iface_view *view)
{
	return this->impl->push_view_finished(view);
}

bool ui_iface_viewmgr::pop_view_finished(ui_iface_view *view)
{
	return this->impl->pop_view_finished(view);
}

ui_iface_viewmgr::ui_iface_viewmgr()
{
	this->impl = new ui_iface_viewmgr_impl(this);
}

ui_iface_viewmgr::~ui_iface_viewmgr()
{
	delete(this->impl);
}

ui_iface_view *ui_iface_viewmgr::push_view(ui_iface_view *view)
{
	return this->impl->push_view(view);
}

bool ui_iface_viewmgr::pop_view()
{
	return this->impl->pop_view();
}

bool ui_iface_viewmgr::insert_view_before(ui_iface_view *view, ui_iface_view *before)
{
	return this->impl->insert_view_before(view, before);
}

bool ui_iface_viewmgr::remove_view(ui_iface_view *view)
{
	return this->impl->remove_view(view);
}

ui_iface_view *ui_iface_viewmgr::get_view(unsigned int idx)
{
	return this->impl->get_view(idx);
}

int ui_iface_viewmgr::get_view_index(const ui_iface_view *view)
{
	return this->get_view_index(view);
}

ui_iface_view *ui_iface_viewmgr::get_last_view()
{
	return this->impl->get_last_view();
}

bool ui_iface_viewmgr::activate()
{
	return this->impl->activate();
}

bool ui_iface_viewmgr::deactivate()
{
	return this->impl->deactivate();
}

ui_iface_view *ui_iface_viewmgr::get_view(const char *name)
{
	return this->impl->get_view(name);
}

bool ui_iface_viewmgr::is_activated()
{
	return this->impl->is_activated();
}

unsigned int ui_iface_viewmgr::get_view_count()
{
	return this->impl->get_view_count();
}

ui_iface_viewmgr* ui_iface_viewmgr::get_instance()
{
	return ui_iface_viewmgr_impl::get_instance();
}
