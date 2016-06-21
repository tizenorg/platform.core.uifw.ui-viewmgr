#ifndef _UI_VIEWMGR_CAPI_H_
#define _UI_VIEWMGR_CAPI_H_

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @defgroup CAPI_UI_VIEWMGR_VIEWMGR ui_viewmgr
 * @ingroup CAPI_UI_VIEWMGR
 * @brief This module provides functionalities about ui_viewmgr.
 * @{
 */

/**
 *  @brief Push a new view into given @p viewmgr. This function is used for when application switches a current view to a new one.
 *
 *  @note Normally, the current view will be hidden by a new view. In default, when user calls this API, view will be switched to @p view instantly,
 *        only when ui_viewmgr state is activated. Otherwise, the @p view will be shown later when ui_viewmgr is activated. ui_viewmgr_view_push() is designed
 *        for providing view transition effect. If you want push view instantly without any transition, you could use ui_viewmgr_view_push_insert_before() or
 *        ui_viewmgr_view_push_insert_after(). If you want to pop the current view, the please use ui_viewmgr_view_pop().
 *
 *  @param viewmgr The ui_viewmgr instance.
 *  @param view An ui_view to insert in the given @p viewmgr view list
 *
 *  @return @p view, @c NULL when it fails to push a @p view
 *
 *  @see ui_viewmgr_activate()
 *  @see ui_viewmgr_view_push_insert_before()
 *  @see ui_viewmgr_view_push_insert_after()
 *  @see ui_viewmgr_view_pop()
 */
EAPI ui_view *ui_viewmgr_view_push(ui_viewmgr *viewmgr, ui_view *view);

/**
 *  @brief Insert a view in this given @p viewmgr view list. Specifically, insert a given @p view right before of the given view, @before.
 *
 *  @param viewmgr The ui_viewmgr instance.
 *  @param view An ui_view to insert in the @p viewmgr view list
 *  @param before An ui_view that will be just inserted after @p view. If you pass @c NULL, @p view will be inserted at the front of the view list
 *
 *  @return @c true on success or @c false otherwise
 *
 *  @see ui_viewmgr_view_push_insert_after()
 */
EAPI bool ui_viewmgr_view_push_insert_before(ui_viewmgr *viewmgr, ui_view *view, ui_view *before);

/**
 *  @brief Insert a view in this given @p viewmgr view list. Specifically, insert a given @p view right after of the given view, @after.
 *
 *  @param viewmgr The ui_viewmgr instance.
 *  @param view An ui_view to insert in the @p viewmgr view list
 *  @param after An ui_view that will be just inserted before the @p view. If you pass @c NULL, @p view will be inserted at the end of the view list
 *
 *  @return @c true on success or @c false otherwise
 *
 *  @see ui_viewmgr_view_push_insert_before()
 */
EAPI bool ui_viewmgr_view_push_insert_after(ui_viewmgr *viewmgr, ui_view *view, ui_view *after);

/**
 *  @brief Pop the top(last) view from this given @p viewmgr view list.
 *         This function is used when application switches the current view back to the previous view.
 *         The top view will be removed from the view stack and then it will be deleted by the given @p viewmgr.
 *
 *  @note If the view is just one left, then ui_viewmgr would be deactivated automatically since the ui application might be invalid anymore. Otherwise,
 *        the application will be terminated. It's up to system configuration.
 *
 *  @param viewmgr The ui_viewmgr instance.
 *
 *  @return @c true on success or @c false otherwise
 *
 *  @see ui_viewmgr_deactivate()
 *  @see ui_viewmgr_view_push()
 */
EAPI bool ui_viewmgr_view_pop(ui_viewmgr *viewmgr);

/**
 *  @brief Activate this view manager.
 *
 *  @note viewmgr window and views will be shown once this function is called. Usually this should be called after applications set their all views
 *        on initialization time.
 *
 *  @param viewmgr The ui_viewmgr instance.
 *
 *  @return @c true on success or @c false otherwise
 *
 *  @see ui_viewmgr_deactivate()
 */
EAPI bool ui_viewmgr_activate(ui_viewmgr *viewmgr);

/**
 *  @brief Deactivate this view manager.
 *
 *  @note viewmgr window and views will be hidden once this function is called. this behavior is up ui system, but usually it hides(unmap)
 *        current window in order that application go background.
 *
 *  @param viewmgr The ui_viewmgr instance.
 *
 *  @return @c true success or @c false not
 *
 *  @see ui_viewmgr_activate()
 */
EAPI bool ui_viewmgr_deactivate(ui_viewmgr *viewmgr);

/**
 *  @brief Get a window object of viewmgr.
 *
 *  @param viewmgr The ui_viewmgr instance.
 *
 *  @return The window object of viewmgr
 */
EAPI Elm_Win *ui_viewmgr_window_get(ui_viewmgr *viewmgr);

/**
 *  @brief Return a last(top) view.
 *
 *  @param viewmgr The ui_viewmgr instance.
 *
 *  @return The view which is last view of the given @p viewmgr view list
 */
EAPI ui_view *ui_viewmgr_last_view_get(ui_viewmgr *viewmgr);

/**
 *  @brief Return a view which is matched with the index @p idx.
 *
 *  @param viewmgr The ui_viewmgr instance.
 *  @param idx A index of the view which you are looking for.
 *
 *  @note You could use the index as the page numbers of the views.
 *  @warning the index number of views are variable since the view list is variable.
 *
 *  @return The view which index is matched with @p idx
 *          If there were no views with index @p idx, @c NULL will be returned
 *
 *  @see ui_viewmgr_view_index_get()
 *  @see ui_viewmgr_view_count_get()
 */
EAPI ui_view *ui_viewmgr_view_get_by_idx(ui_viewmgr *viewmgr, int idx);

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
EAPI ui_view *ui_viewmgr_view_get_by_name(ui_viewmgr *viewmgr, const char *name);

/**
 *  @brief Get a base object of a ui_viewmgr.
 *
 *	@note Normally, a base object can be used for adding additional objects.
 *
 *  @param viewmgr The ui_viewmgr instance.
 *
 *  @return The base object of ui_viewmgr.
 */
EAPI Evas_Object *ui_viewmgr_base_get(ui_viewmgr *viewmgr);

/**
 *  @brief Return a view index(page) number of the given view.
 *         You could use this function to query the given @p view list order.
 *
 *  @param viewmgr The ui_viewmgr instance.
 *  @param view An ui_view to query the index
 *
 *  @return An index of the given @p view on success, otherwise, -1
 *
 *  @warning The index number of views are variable since the view list is variable
 */
EAPI int ui_viewmgr_view_index_get(ui_viewmgr *viewmgr, const ui_view *view);

/**
 *  @brief Return the number of views which this @p given viewmgr has.
 *
 *  @param viewmgr The ui_viewmgr instance.
 *
 *  @return the count of views
 */
EAPI int ui_viewmgr_view_count_get(ui_viewmgr *viewmgr);

/**
 *  @brief Return whether soft back key is required or not.
 *
 *  @param viewmgr The ui_viewmgr instance.
 *
 *  @return @c true if soft key is required, @c false otherwise
 */
EAPI bool ui_viewmgr_soft_key_need_get(ui_viewmgr *viewmgr);

/**
 *  @brief Return the ui_viewmgr instance.
 *
 *	@note ui_viewmgr has a singleton instance.
 *
 *  @return The ui_viewmgr instance.
 */
EAPI ui_viewmgr *ui_viewmgr_viewmgr_get();

/**
 *  @brief A Convenient Macro to activate the ui_viewmgr.
 */
#define UI_VIEWMGR_ACTIVATE() (ui_viewmgr_activate(ui_viewmgr_viewmgr_get()))

/**
 *  @brief A Convenient Macro function to deactivate the ui_viewmgr.
 */
#define UI_VIEWMGR_DEACTIVATE() (ui_viewmgr_deactivate(ui_viewmgr_viewmgr_get()))

/**
 *  @brief A Convenient Macro function to push a view.
 */
#define UI_VIEWMGR_VIEW_PUSH(X) (ui_viewmgr_view_push(ui_viewmgr_viewmgr_get(), (X)))

/**
 *  @brief A Convenient Macro function to pop a view.
 */
#define UI_VIEWMGR_VIEW_POP() (ui_viewmgr_view_pop(ui_viewmgr_viewmgr_get()))

#ifdef __cplusplus
}
#endif

/**
 * @}
 */

#endif /* _UI_VIEWMGR_CAPI_H_ */
