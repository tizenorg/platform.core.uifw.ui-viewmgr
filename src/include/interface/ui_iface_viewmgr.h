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
#ifndef _UI_IFACE_VIEWMGR_H_
#define _UI_IFACE_VIEWMGR_H_

namespace ui_viewmanager {

class ui_iface_view;

/**
 *  @class ui_iface_viewmgr
 *
 *  @ingroup ui_viewmanager
 *
 *  @brief This is a base class of viewmgr. One viewmgr represents a class which contains multiple views.
 *         A viewmgr manages not only views life-cycle but constructs basic infrastructures such as key events handling, transition effects, transient views,
 *         etc. This interface guides you a basic policy and behaviors of a view manager. Basically, View manager must have a default window internally.
 *
 *  @warning viewmgr will remove all containing views when it's destroyed.
 */
class ui_iface_viewmgr
{
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
	 *  @return the count of views
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

	/**
	 *  @brief Return viewmgr instance.
	 *
	 *  @return viewmgr instance.
	 */
	static ui_iface_viewmgr* get_instance();

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
	bool push_view_finished(ui_iface_view *view);

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
	bool pop_view_finished(ui_iface_view *view);

	/**
	 *  @brief Push a new view into this viewmgr. This function is used for when application switches a current view to a new one.
	 *
	 *  @note Normally, the current view will be hidden by a new view. In default, when user calls this API, view will be switched to @p view instantly,
	 *        only when viewmgr state is activated. Otherwise, the @p view will be shown later when viewmgr is activated. push_view() is designed for providing
	 *        view transition effect. If you want push view instantly without any transition, you could use insert_view_before() or insert_view_after().
	 *        or use the view transition style function.
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
	 *  @see ui_iface_view::set_transition_style()
	 */
	virtual ui_iface_view *push_view(ui_iface_view *view);

	/**
	 *  @brief Pop the top(last) view from this viewmgr view list.
	 *         This function is used when application switches the current view back to the previous view.
	 *         The top view will be removed from the view stack and then it will be deleted by the viewmgr.
	 *
	 *  @note If the view is just one left, then viewmgr would be deactivated automatically since the ui application might be invalid anymore. Otherwise,
	 *        the application will be terminated. It's up to system configuration.
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
	bool insert_view_before(ui_iface_view *view, ui_iface_view *before);

	/**
	 *  @brief Insert a view in this viewmgr view list. Specifically, insert a given @p view right after of the given view, @after.
	 *
	 *  @param view A view to insert in the viewmgr view list.
	 *  @param after A view that will be just inserted before the @p view. If you pass @c NULL, @p view will be inserted at the end of the view list.
	 *
	 *  @return @c true on success or @c false otherwise.
	 */
	bool insert_view_after(ui_iface_view *view, ui_iface_view *after);

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
	bool remove_view(ui_iface_view *view);

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
	ui_iface_view* get_view(unsigned int idx);

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
	ui_iface_view *get_view(const char *name);

	/**
	 *  @brief Return a last(top) view.
	 *
	 *  @return The view which is last view of the viewmgr view list.
	 */
	ui_iface_view *get_last_view();

	/**
	 *  @brief Return a view index(page) number of the given view.
	 *         You could use this function to query the given @p view list order.
	 *
	 *  @param view A view to query the index.
	 *
	 *  @return An index of the given @p view on success, otherwise, -1.
	 *
	 *  @warning The index number of views are variable since the view list is variable.
	 */
	int get_view_index(const ui_iface_view *view);

	///Constructor.
	ui_iface_viewmgr();

	///Destructor.
	virtual ~ui_iface_viewmgr();

private:
	_UI_DECLARE_PRIVATE_IMPL(ui_iface_viewmgr);
	_UI_DISABLE_COPY_AND_ASSIGN(ui_iface_viewmgr);
	_UI_DECLARE_FRIENDS(ui_iface_view);
	_UI_DECLARE_FRIENDS(ui_iface_app);
};

}

#endif /* _UI_IFACE_VIEWMGR_H_ */
