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
#ifndef UI_IFACE_VIEWMGR_H_
#define UI_IFACE_VIEWMGR_H_

#include <list>

using namespace std;

namespace viewmgr {

template<typename T, typename T2>
class ui_iface_view;

/**
 *  @class ui_iface_viewmgr
 *
 *  @internal
 *  @ingroup viewmgr
 *
 *  @brief This is a interface class of viewmgr. One viewmgr represents a window which contains multiple views.
 *         A viewmgr manages not only views life-cycle but constructs basic infrastructures such as key events handling, transition effects, transient views.
 *         This interface guide you a basic policy of a view manager.
 *
 *  @warning viewmgr will remove all containing views when it's destroyed.
 */
template<typename T, typename T2>
class ui_iface_viewmgr: public singleton<T2>
{
	friend class ui_iface_view<T, T2>;

private:
	static bool soft_key;                  //If system doesn't support HW back key, then this value is @c true.
	static bool event_block;               //Event block on view transition. This value should be configurable by system.
	list<ui_iface_view<T, T2> *> view_list;    //View list.
	bool activated;                        //Activated status of this viewmgr.

	/**
	 *  @brief Connect a given view to this viewmgr.
	 *
	 *  @param view A view to connect to this viewmgr which means the @p view is to belong to this viewmgr.
	 *
	 *  @return @c true success or @c false not.
	 *
	 *  @warning If the given view is already connected to a viewmgr, this call will be failed.
	 *  @see disconnect_view()
	 */
	bool connect_view(ui_iface_view<T, T2> *view);

	/**
	 *  @brief Disconnect a given view from this viewmgr.
	 *
	 *  @param view A view to disconnect from this viewmgr.
	 *
	 *  @return @c true on success or @c false otherwise.
	 *
	 *  @see connect_view()
	 */
	bool disconnect_view(ui_iface_view<T, T2> *view);

	/**
	 *  @brief Toggle event blocking to the given view.
	 *
	 *  @note If the event is blocked, product users won't be able to enter any inputs to this @p view. These inputs are mouse clicks, key press,
	 *        screen touches, etc. Event if this function is called, @p view will be event-blocked only when system requires event blocking.
	 *        Most of the times, This function should be used on transition. @see also push_view(), push_view_finished(), pop_view(), pop_view_finished().
	 *
	 *  @param view A view to toggle event blocking.
	 *  @param block @c true is blocking event, otherwise @c false.
	 */
	void set_event_block(ui_iface_view<T, T2> *view, bool block);

protected:
	/**
	 *  @brief This function is designed for finishing process of push transition.
	 *
	 *  @param view A view which is finished pushing.
	 *
	 *  @return @c true on success or @c false otherwise.
	 *
	 *  @warning This function must be called when push transition is finished.
	 */
	bool push_view_finished(ui_iface_view<T, T2> *view);

	/**
	 *  @brief This function is designed for finishing process for pop transition.
	 *
	 *  @note If a new view is pushed.
	 *
	 *  @param view A view which is finished popping.
	 *
	 *  @return @c true on success or @c false otherwise.
	 *
	 *  @warning This function must be called when push transition is finished.
	 */
	bool pop_view_finished(ui_iface_view<T, T2> *view);

//FIXME: Necessary?
#if 0
	/**
	 *  @brief Return a list of views which this viewmgr has.
	 *
	 *  @return a pointer of list of views.
	 *
	 *  @warning Don't modify this view list.
	 */
	const list<ui_iface_view<T, T2>*>* const get_view_list()
	{
		return &this->view_list;
	}
#endif

	/**
	 *  @brief Push a new view into this viewmgr. This function is used for when application switches a current view to a new one.
	 *
	 *  @note Normally, the current view will be hidden by a new view. In default, when user calls this API, view will be switched to @p view instantly,
	 *        only when viewmgr state is activated. Otherwise, the @p view will be shown later when viewmgr is activated. push_view() is designed for providing
	 *        view transition effect. If you want push view instantly without any transition, you could use insert_view_before() or insert_view_after().
	 *        If you want to pop the current view, the please use pop_view().
	 *
	 *  @param view A view to insert at the end of viewmgr view list.
	 *
	 *  @return @p view, @c NULL when it fails to push a @p view.
	 *
	 *  @see activated()
	 *  @see insert_view_before()
	 *  @see insert_view_after()
	 *  @see pop_view()
	 */
	ui_iface_view<T, T2> *push_view(ui_iface_view<T, T2> *view);

	/**
	 *  @brief Pop the top(last) view from this viewmgr view list.
	 *         This function is used for application switches the current view back to the previous view.
	 *         The top view will be removed from the view stack and then it will be deleted by the viewmgr.
	 *
	 *  @note If the view is just one left, then viewmgr would be deactivated since the ui application might be invalid anymore. Otherwise, the application will
	 *        be terminated. It's up to system configuration.
	 *
	 *  @return @c true on success or @c false otherwise.
	 *
	 *  @see deactivate()
	 *  @see push_view()
	 */
	virtual bool pop_view();

	/**
	 *  @brief Insert a view in this viewmgr view list. Specifically, insert a given @p view right before of the given view, @before.
	 *
	 *  @param view A view to insert in the viewmgr view list.
	 *  @param before A view that will be just inserted after @p view. If you pass @c NULL, @p view will be inserted at the front of the view list.
	 *
	 *  @return @c true on success or @c false otherwise.
	 */
	bool insert_view_before(ui_iface_view<T, T2> *view, ui_iface_view<T, T2> *before);

	/**
	 *  @brief Insert a view in this viewmgr view list. Specifically, insert a given @p view right after of the given view, @after.
	 *
	 *  @param view A view to insert in the viewmgr view list.
	 *  @param after A view that will be just inserted before the @p view. If you pass @c NULL, @p view will be inserted at the end of the view list.
	 *
	 *  @return @c true on success or @c false otherwise.
	 */
	bool insert_view_after(ui_iface_view<T, T2> *view, ui_iface_view<T, T2> *after);

	/**
	 *  @brief Remove the given view from this viewmgr view list.
	 *
	 *  @param view A view to remove from the viewmgr view list.
	 *
	 *  @return @c true on success or @c false otherwise.
	 *
	 *  @see insert_view_before()
	 *  @see insert_view_after()
	 *  @see push_view()
	 */
	bool remove_view(ui_iface_view<T, T2> *view);

	/**
	 *  @brief Return a view which is matched with the index @p idx.
	 *
	 *  @param idx A index of the view which you are looking for.
	 *
	 *  @return The view which index is matched with @p idx.
	 *          If there were no views with index @p idx, @c NULL will be returned.
	 *
	 *  @note You could use the index as the page numbers of the views.
	 *  @warning the index number of views are variable since the view list is variable.
	 *
	 *  @see get_view_index()
	 *  @see get_view_count()
	 */
	ui_iface_view<T, T2>* get_view(unsigned int idx);

	/**
	 *  @brief Return a view which is matched with the @p name.
	 *
	 *  @note Every view have their names as their own identifiers.
	 *
	 *  @param name The name of the view which you are looking for.
	 *
	 *  @return The view which name is matched with @p name.
	 *          If there were no views name matched, @c NULL will be returned.
	 *
	 *  @see ui_iface_view::set_name()
	 */
	ui_iface_view<T, T2> *get_view(const char *name);

	/**
	 *  @brief Return a last(top) view.
	 *
	 *  @return The view which is last view of the viewmgr view list.
	 */
	ui_iface_view<T, T2> *get_last_view();

	/**
	 *  @brief Return a view index(page) number of the given view.
	 *         You could use this function to query the given @p view list order.
	 *
	 *  @param view A view to query the index.
	 *
	 *  @return An index of the give @p view on success, otherwise, -1.
	 *
	 *  @warning The index number of views are variable since the view list is variable.
	 */
	int get_view_index(const ui_iface_view<T, T2> *view);

	///Constructor.
	ui_iface_viewmgr();
	ui_iface_viewmgr(const ui_iface_viewmgr& viewmgr);

	///Destructor.
	virtual ~ui_iface_viewmgr();

public:
	/**
	 *  @brief Activate this view manager.
	 *
	 *  @note viewmgr window and views will be shown once activate() is called. Usually this activate() should be called after applications set their all views
	 *        on initialization time.
	 *
	 *  @return @c true on success or @c false otherwise.
	 *
	 *  @see deactivate()
	 */
	bool activate();

	/**
	 *  @brief Deactivate this view manager.
	 *
	 *  @note viewmgr window and views will be hidden once deactivate() is called. deactivate() behavior is up ui system, but usually it hides(unmap)
	 *        current window in order that application go background.
	 *
	 *  @return @c true success or @c false not.
	 *
	 *  @see activate()
	 */
	bool deactivate();

	/**
	 *  @brief Return the active status of viewmgr.
	 *
	 *  @return @c true if viewmgr is activated, @c false otherwise.
	 *
	 *  @see activate()
	 *  @see deactivate()
	 */
	bool is_activated();

	/**
	 *  @brief Return the number of views which this viewmgr has.
	 *
	 *  @return the number of view
	 */
	unsigned int get_view_count();

	/**
	 *  @brief Return whether soft key is required or not.
	 *
	 *  @note Soft key is kind of like the software back button. It's used for product users to change current view to a previous view (pop).
	 *        If a device doesn't have any hardware back buttons, Soft back key is necessary which means this function will return @c true.
	 *        Some devices may needs software back key as well as hardware back key at the same time. That decision is up to product design.
	 *        And soft_key initial value should read from the system configuration.
	 *
	 *  @return @c true if soft key is required, @c false otherwise.
	 */
	static bool need_soft_key();
};


#define VIEW_ITR typename list<ui_iface_view<T, T2> *>::iterator
#define VIEW_RITR typename list<ui_iface_view<T, T2> *>::reverse_iterator

//FIXME: Read system profile to decide whether support software key or not.
template<typename T, typename T2> bool ui_iface_viewmgr<T, T2>::soft_key = true;
//FIXME: Read system profile to decide whether support event block or not.
template<typename T, typename T2> bool ui_iface_viewmgr<T, T2>::event_block = true;


template<typename T, typename T2>
bool ui_iface_viewmgr<T, T2>::insert_view_after(ui_iface_view<T, T2> *view, ui_iface_view<T, T2> *after)
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

template<typename T, typename T2>
bool ui_iface_viewmgr<T, T2>::need_soft_key()
{
	return ui_iface_viewmgr<T, T2>::soft_key;
}

template<typename T, typename T2>
bool ui_iface_viewmgr<T, T2>::connect_view(ui_iface_view<T, T2> *view)
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

template<typename T, typename T2>
bool ui_iface_viewmgr<T, T2>::disconnect_view(ui_iface_view<T, T2> *view)
{
	if (!view->viewmgr) return false;
	view->viewmgr = NULL;
	return true;
}

template<typename T, typename T2>
void ui_iface_viewmgr<T, T2>::set_event_block(ui_iface_view<T, T2> *view, bool block)
{
	if (!ui_iface_viewmgr::event_block) return;
	view->set_event_block(block);
}

template<typename T, typename T2>
bool ui_iface_viewmgr<T, T2>::push_view_finished(ui_iface_view<T, T2> *view)
{
	ui_iface_view<T, T2> *last = this->view_list.back();

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

template<typename T, typename T2>
bool ui_iface_viewmgr<T, T2>::pop_view_finished(ui_iface_view<T, T2> *view)
{
	ui_iface_view<T, T2> *last = this->view_list.back();

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

template<typename T, typename T2>
ui_iface_viewmgr<T, T2>::ui_iface_viewmgr(const ui_iface_viewmgr<T, T2>& viewmgr)
{

}

template<typename T, typename T2>
ui_iface_viewmgr<T, T2>::ui_iface_viewmgr()
		: singleton<T2>(), activated(false)
{
}

template<typename T, typename T2>
ui_iface_viewmgr<T, T2>::~ui_iface_viewmgr()
{
	//Terminate views
	for (VIEW_RITR it = this->view_list.rbegin(); it != this->view_list.rend(); it++)
	{
		ui_iface_view<T, T2> *view = *it;
		view->on_deactivate();
		view->on_unload();
		view->on_destroy();
		delete (view);
	}

	//FIXME: Window is destroyed. Terminate Application!
	ui_app_exit();
}

template<typename T, typename T2>
ui_iface_view<T, T2> *ui_iface_viewmgr<T, T2>::push_view(ui_iface_view<T, T2> *view)
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

	ui_iface_view<T, T2> *pview;

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

template<typename T, typename T2>
bool ui_iface_viewmgr<T, T2>::pop_view()
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
		ui_iface_view<T, T2>*view = this->view_list.back();
		view->on_deactivate();
		view->on_unload();
		view->on_destroy();
		delete(view);

		return true;
	}

	//last page to be popped.
	ui_iface_view<T, T2>*view = this->view_list.back();
	view->on_deactivate();
	this->set_event_block(view, true);

	//Below object has to be used in child class...
	//Make this getter method? or define instance?
	//previous page is to be an active page.
	auto nx = prev(this->view_list.end(), 2);
	ui_iface_view<T, T2>*pview = *nx;
	pview->on_load();
	pview->on_deactivate();
	this->set_event_block(pview, true);

	return true;
}

template<typename T, typename T2>
bool ui_iface_viewmgr<T, T2>::insert_view_before(ui_iface_view<T, T2> *view, ui_iface_view<T, T2> *before)
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

template<typename T, typename T2>
bool ui_iface_viewmgr<T, T2>::remove_view(ui_iface_view<T, T2> *view)
{
	this->view_list.remove(view);
	this->disconnect_view(view);

	//TODO: If this view is the top on the stack ?
	return true;
}

template<typename T, typename T2>
ui_iface_view<T, T2> *ui_iface_viewmgr<T, T2>::get_view(unsigned int idx)
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

template<typename T, typename T2>
int ui_iface_viewmgr<T, T2>::get_view_index(const ui_iface_view<T, T2> *view)
{
	int idx = 0;

	for (VIEW_ITR it = this->view_list.begin(); it != this->view_list.end(); it++)
	{
		if (view == *it) return idx;
		++idx;
	}

	return -1;
}

template<typename T, typename T2>
ui_iface_view<T, T2> *ui_iface_viewmgr<T, T2>::get_last_view()
{
	int cnt = this->get_view_count();
	return this->get_view(cnt - 1);
}

template<typename T, typename T2>
bool ui_iface_viewmgr<T, T2>::activate()
{
	if (this->activated) return false;
	if (this->get_view_count() == 0) return false;
	this->activated = true;
	return true;
}

template<typename T, typename T2>
bool ui_iface_viewmgr<T, T2>::deactivate()
{
	if (!this->activated) return false;
	this->activated = false;
	return true;
}

template<typename T, typename T2>
ui_iface_view<T, T2> *ui_iface_viewmgr<T, T2>::get_view(const char *name)
{
	//FIXME: ...
	return NULL;
}

template<typename T, typename T2>
bool ui_iface_viewmgr<T, T2>::is_activated()
{
	return this->activated;
}

template<typename T, typename T2>
unsigned int ui_iface_viewmgr<T, T2>::get_view_count()
{
	return this->view_list.size();
}

}

#endif /* UI_IFACE_VIEWMGR_H_ */
