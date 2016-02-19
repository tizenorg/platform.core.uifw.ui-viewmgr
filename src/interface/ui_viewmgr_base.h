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
#ifndef UI_WINDOW_BASE_H_
#define UI_WINDOW_BASE_H_

#include <list>

using namespace std;

class ui_view_base;

/**
 *  @class ui_viewmgr_base
 *
 *  @ingroup ui_viewmgr
 *
 *  @brief This is a base class of viewmgr. One viewmgr represents a window which contains multiple views.
 *         A viewmgr manages not only views life-cycle but constructs some basic infrastructure. It's up to derived classes.
 *
 *  @warning viewmgr will remove all containing views when it's destroyed.
 *  @date 2016/01/29
 *  @author Hermet Park <chuneon.park@samsung.com>
 */
class ui_viewmgr_base
{
	friend class ui_view_base;

private:
	list<ui_view_base*> view_list;      //view list.
	bool event_block;   //event block on view transition. This value should be configurable by system.
	bool activated;     //activated status of this viewmgr.
	bool soft_back_key;  //If system doesn't support HW back key, then this value is true.

	/**
	 *  @brief link a given view to this viewmgr.
	 *
	 *  @param view a view to connect to this viewmgr.
	 *  @return success or not.
	 *
	 *  @note This is s a friend function of ui_view_base
	 */
	bool connect_view(ui_view_base *view);

	/**
	 *  @brief unlink a given view from this viewmgr.
	 *
	 *  @param view a view to disconnect from this viewmgr.
	 *  @return @c true success or @c false not.
	 *
	 *  @note This is s a friend function of ui_view_base
	 */
	bool disconnect_view(ui_view_base *view);

	/**
	 *  @brief toggle event blocking to the given view.
	 *
	 *  @param view a view to toggle event blocking
	 *  @param block @c true is block event, otherwise @c false.
	 *
	 *  @note This is s a friend function of ui_view_base
	 */
	void set_event_block(ui_view_base *view, bool block);

protected:
	/**
	 *  @brief This function is designed for end of push transition.
	 *
	 *  @param view view which is finished pushing.
	 *  @return @c true success or @c false not.
	 *
	 *  @warning This function must be called definitely when push transition is finished.
	 *  @note This is s a friend function of ui_view_base
	 */
	bool push_view_finished(ui_view_base *view);

	/**
	 *  @brief This function is designed for end of pop transition.
	 *
	 *  @param view view which is finished popping.
	 *  @return @c true success or @c false not.
	 *
	 *  @warning This function must be called definitely when push transition is finished.
	 *  @note This is s a friend function of ui_view_base
	 */
	bool pop_view_finished(ui_view_base *view);

	/**
	 *  @brief Return a list of views which this viewmgr has.
	 *
	 *  @return a pointer of list of views.
	 */
	const list<ui_view_base*>* const get_view_list()
	{
		return &this->view_list;
	}

	/**
	 *  @brief Push a new view into the viewmgr stack.
	 *         This function is used for application switches the current view to a new one.
	 *
	 *  @note Normally, the current view will be hidden by a new view.
	 *  @return @c true on success, @c false otherwise.
	 */
	ui_view_base *push_view(ui_view_base *view);

	/**
	 *  @brief Pop the top view from the viewmgr stack.
	 *         This function is used for application switches the current view back to the previous view.
	 *         The top view will be removed from the view stack and then it will be deleted by the viewmgr.
	 *
	 *  @note If the view is just one left, then viewmgr would be destroyed since the application might be terminated.
	 *        But this behavior is optional.
	 *
	 *  @return A view pointer which was popped. If it's failed to pop, @c NULL will be returned.
	 */
	bool pop_view();

	/**
	 *  @brief Insert a view into this viewmgr stack. Specially, right before of the given view, @before
	 *
	 *  @param view a view to push into the viewmgr stack
	 *  @param before a view that will be just after the @c view.
	 *         If you pass @c NULL, @c view will be inserted at the front of the view stack.
	 *  @return @c true success or @c false not.
	 */
	bool insert_view_before(ui_view_base *view, ui_view_base *before);

	/**
	 *  @brief Insert a view into this viewmgr stack. Specially, right after of the given view, @after
	 *
	 *  @param view a view to push into the viewmgr stack
	 *  @param after a view that will be just before the @c view.
	 *         If you pass @c NULL, @c view will be inserted at the end of the view stack.
	 *  @return @c true success or @c false not.
	 */
	bool insert_view_after(ui_view_base *view, ui_view_base *after);

	/**
	 *  @brief Remove the given view from this viewmgr stack.
	 *
	 *  @return @c true on success or @c false if not.
	 *
	 */
	bool remove_view(ui_view_base *view);

	/**
	 *  @brief Return a stack index number of the given view.
	 *         You could use this function to query the given view stack order.
	 *
	 *  @param idx a view to query the index.
	 *  @return an index of the give view.
	 *          If there were no views on the idx, @c NULL will be returned.
	 *
	 *  @warning the index number is variable since the view stack size is also variable.
	 */
	ui_view_base* get_view(unsigned int idx);

	/**
	 *  @brief Return a view which is matched with the @c name.
	 *
	 *  @param name the name of the view which you find.
	 *  @return the view which name is matched with @c name.
	 *          If there were no views name matched, @c NULL will be returned.
	 *
	 */
	ui_view_base *get_view(const char *name)
	{
		//FIXME: ...
		return NULL;
	}

	/**
	 *  @brief Return a stack index number of the given view.
	 *         You could use this function to query the given view stack order.
	 *
	 *  @param a view to query the index.
	 *  @return an index of the give view on success, otherwise, -1.
	 *
	 *  @warning the index number is variable since the view stack size is also variable.
	 */
	int get_view_index(const ui_view_base *view);

	//Activate a viewmgr.
	bool activate();

	//Deactivate a viewmgr.
	bool deactivate();

public:
	///Constructor.
	ui_viewmgr_base();

	///Destructor. Delete all contained views.
	virtual ~ui_viewmgr_base();

	//FIXME: Doc.
	ui_view_base *get_last_view();

	/**
	 *  @brief Return the number of views which this viewmgr has.
	 *
	 *  @return the number of view
	 *
	 */
	unsigned int get_view_count()
	{
		return this->view_list.size();
	}

	/**
	 *  @brief Return the active status of viewmgr.
	 *
	 *  @return active status
	 *
	 */
	bool is_activated()
	{
		return this->activated;
	}

	/**
	 *  @brief Return the whether software back key need or not.
	 *
	 *  @return whether need software back key.
	 *
	 */
	bool get_soft_back_key()
	{
		return this->soft_back_key;
	}

};

#endif /* UI_WINDOW_BASE_H_ */
