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

#include "../../include/interface/ui_iface_viewmanager.h"

ui_iface_viewmgr *ui_iface_viewmgr::inst = NULL;

#define VIEW_ITR list<ui_iface_view *>::iterator
#define VIEW_RITR list<ui_iface_view *>::reverse_iterator

//FIXME: Read system profile to decide whether support software key or not.
bool ui_iface_viewmgr::soft_key = true;
//FIXME: Read system profile to decide whether support event block or not.
bool ui_iface_viewmgr::event_block = true;

bool ui_iface_viewmgr::insert_view_after(ui_iface_view *view, ui_iface_view *after)
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

bool ui_iface_viewmgr::need_soft_key()
{
	return ui_iface_viewmgr::soft_key;
}

bool ui_iface_viewmgr::connect_view(ui_iface_view *view)
{
	//FIXME: If user call a set_viewmgr() before, It should not return false.
	/*
	if (view->viewmgr)
	{
		LOGE("view(%p) has already connected to viewmgr(%p)", view, this);
		return false;
	}
	*/

	view->viewmgr = this;
	return true;
}

bool ui_iface_viewmgr::disconnect_view(ui_iface_view *view)
{
	if (!view->viewmgr) return false;
	view->viewmgr = NULL;
	return true;
}

void ui_iface_viewmgr::set_event_block(ui_iface_view *view, bool block)
{
	if (!ui_iface_viewmgr::event_block) return;
	view->set_event_block(block);
}

bool ui_iface_viewmgr::push_view_finished(ui_iface_view *view)
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

bool ui_iface_viewmgr::pop_view_finished(ui_iface_view *view)
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

ui_iface_viewmgr::ui_iface_viewmgr(const ui_iface_viewmgr& viewmgr)
{
}

ui_iface_viewmgr::ui_iface_viewmgr()
		: activated(false)
{
	ui_iface_viewmgr::inst = this;
}

ui_iface_viewmgr::~ui_iface_viewmgr()
{
	//Terminate views
	for (VIEW_RITR it = this->view_list.rbegin(); it != this->view_list.rend(); it++)
	{
		ui_iface_view *view = *it;
		view->on_deactivate();
		view->on_unload();
		view->on_destroy();
		delete (view);
	}

	//FIXME: Window is destroyed. Terminate Application!
	ui_app_exit();

	ui_iface_viewmgr::inst = NULL;
}

ui_iface_view *ui_iface_viewmgr::push_view(ui_iface_view *view)
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

	if (!view->get_content())
	{
		view->on_load();
	}

	view->on_deactivate();

	if (this->view_list.size() != 1)
	{
		this->set_event_block(view, true);
	}

	return view;
}

bool ui_iface_viewmgr::pop_view()
{
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

	//last page to be popped.
	ui_iface_view*view = this->view_list.back();
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

bool ui_iface_viewmgr::insert_view_before(ui_iface_view *view, ui_iface_view *before)
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

bool ui_iface_viewmgr::remove_view(ui_iface_view *view)
{
	this->view_list.remove(view);
	this->disconnect_view(view);

	//TODO: If this view is the top on the stack ?
	return true;
}

ui_iface_view *ui_iface_viewmgr::get_view(unsigned int idx)
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

int ui_iface_viewmgr::get_view_index(const ui_iface_view *view)
{
	int idx = 0;

	for (VIEW_ITR it = this->view_list.begin(); it != this->view_list.end(); it++)
	{
		if (view == *it) return idx;
		++idx;
	}

	return -1;
}

ui_iface_view *ui_iface_viewmgr::get_last_view()
{
	int cnt = this->get_view_count();
	return this->get_view(cnt - 1);
}

bool ui_iface_viewmgr::activate()
{
	if (this->activated) return false;
	if (this->get_view_count() == 0) return false;
	this->activated = true;
	return true;
}

bool ui_iface_viewmgr::deactivate()
{
	if (!this->activated) return false;
	this->activated = false;
	return true;
}

ui_iface_view *ui_iface_viewmgr::get_view(const char *name)
{
	//FIXME: ...
	return NULL;
}

bool ui_iface_viewmgr::is_activated()
{
	return this->activated;
}

unsigned int ui_iface_viewmgr::get_view_count()
{
	return this->view_list.size();
}

ui_iface_viewmgr* ui_iface_viewmgr::get_instance()
{
	return ui_iface_viewmgr::inst;
}
