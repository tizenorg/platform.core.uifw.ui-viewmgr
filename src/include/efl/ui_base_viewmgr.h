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
#ifndef _UI_BASE_VIEWMGR_H_
#define _UI_BASE_VIEWMGR_H_

namespace efl_viewmanager
{

class ui_base_view;

/**
 *  @class ui_base_viewmgr
 *
 *  @ingroup efl_viewmanager
 *
 *  @brief This is a base class of EFL view manager. Typically, this view manager extends ui_iface_viewmgr and implement basic behaviors for
 *         EFL view manager in all profiles. Basically, this view manager has one default window to display several logic views as well as this has
 *         a conformant and default application layout to display indicator, application layout and virtual keypad properly. This base view manager implements
 *         view transition effects. Of course, those could be customized for each profile. Also, it implements events blocking for views during views going
 *         back and forth. But the behavior will be turned on/off based on the system profile.
 *
 *  @warning viewmgr will remove its window, conformant and default layout when it's destroyed.
 */
class ui_base_viewmgr: public ui_iface_viewmgr
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
	virtual bool activate();

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
	virtual bool deactivate();

	/**
	 *  @brief Push a new view into this viewmgr. This function is used for when application switches a current view to a new one.
	 *
	 *  @note Normally, the current view will be hidden by a new view. In default, when user calls this API, view will be switched to @p view instantly,
	 *        only when viewmgr state is activated. Otherwise, the @p view will be shown later when viewmgr is activated. push_view() is designed for providing
	 *        view transition effect. If you want push view instantly without any transition, you could use insert_view_before() or insert_view_after().
	 *        If you want to pop the current view, the please use pop_view().
	 *
	 *  @param view A view to insert in the viewmgr view list.
	 *
	 *  @return @p view, @c NULL when it fails to push a @p view.
	 *
	 *  @see activated()
	 *  @see insert_view_before()
	 *  @see insert_view_after()
	 *  @see pop_view()
	 */
	virtual ui_base_view *push_view(ui_base_view *view);

	/**
	 *  @brief Push a new view into this viewmgr. This function is used for when application switches a current view to a new one.
	 *
	 *  @note Normally, the current view will be hidden by a new view. In default, when user calls this API, view will be switched to @p view instantly,
	 *        only when viewmgr state is activated. Otherwise, the @p view will be shown later when viewmgr is activated. push_view() is designed for providing
	 *        view transition effect. If you want push view instantly without any transition, you could use insert_view_before() or insert_view_after().
	 *        If you want to pop the current view, the please use pop_view().
	 *
	 *  @param view A view to insert in the viewmgr view list.
	 *
	 *  @return @p view, @c NULL when it fails to push a @p view.
	 *
	 *  @see activated()
	 *  @see insert_view_before()
	 *  @see insert_view_after()
	 *  @see pop_view()
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
	virtual bool insert_view_before(ui_base_view *view, ui_base_view *before);

	/**
	 *  @brief Insert a view in this viewmgr view list. Specifically, insert a given @p view right after of the given view, @after.
	 *
	 *  @param view A view to insert in the viewmgr view list.
	 *  @param after A view that will be just inserted before the @p view. If you pass @c NULL, @p view will be inserted at the end of the view list.
	 *
	 *  @return @c true on success or @c false otherwise.
	 */
	virtual bool insert_view_after(ui_base_view *view, ui_base_view *after);

	/** @brief Get a window object of viewmgr.
	 */
	Elm_Win *get_window();

	/** @brief Get a conformant object of viewmgr.
	 */
	Elm_Conformant *get_conformant();

	/** @brief Get a last view of current view stack.
	 */
	ui_base_view *get_last_view();

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
	ui_base_view *get_view(unsigned int idx);

	/** @brief Get a base layout of viewmgr.
	 */
	Evas_Object *get_base();

protected:
	/**
	 *  @brief Set indicator of the view.
	 *
	 *  @param indicator The mode to set, one of #ui_view_indicator
	 */
	bool set_indicator(ui_view_indicator indicator);

	///Constructor
	ui_base_viewmgr(const char *pkg, ui_base_key_listener *key_listener);
	ui_base_viewmgr(const char *pkg);

	///Destructor.
	virtual ~ui_base_viewmgr();

private:
	_UI_DECLARE_PRIVATE_IMPL(ui_base_viewmgr);
	_UI_DISABLE_COPY_AND_ASSIGN(ui_base_viewmgr);
	_UI_DECLARE_FRIENDS(ui_base_view);
};

}

#endif /* _UI_BASE_VIEWMGR_H_ */
