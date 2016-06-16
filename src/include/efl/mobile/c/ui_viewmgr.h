#ifndef _UI_VIEWMGR_CAPI_H_
#define _UI_VIEWMGR_CAPI_H_

#ifdef __cplusplus
extern "C" {
#endif

/**
 *  @brief Push a new view into this viewmgr. This function is used for when application switches a current view to a new one.
 *
 *  @note Normally, the current view will be hidden by a new view. In default, when user calls this API, view will be switched to @p view instantly,
 *        only when viewmgr state is activated. Otherwise, the @p view will be shown later when viewmgr is activated. ui_viewmgr_view_push() is designed for providing
 *        view transition effect. If you want push view instantly without any transition, you could use ui_viewmgr_view_push_insert_before() or ui_viewmgr_view_push_insert_after().
 *        If you want to pop the current view, the please use ui_viewmgr_view_pop().
 *
 *  @param viewmgr The viewmgr object
 *  @param view A view to insert in the viewmgr view list
 *
 *  @return @p view, @c NULL when it fails to push a @p view
 *
 *  @see ui_viewmgr_activate()
 *  @see ui_viewmgr_view_push_insert_before()
 *  @see ui_viewmgr_view_push_insert_after()
 *  @see ui_viewmgr_view_pop()
 */
ui_view *ui_viewmgr_view_push(ui_viewmgr *viewmgr, ui_view *view);

/**
 *  @brief Insert a view in this viewmgr view list. Specifically, insert a given @p view right before of the given view, @before.
 *
 *  @param viewmgr The viewmgr object
 *  @param view A view to insert in the viewmgr view list
 *  @param before A view that will be just inserted after @p view. If you pass @c NULL, @p view will be inserted at the front of the view list
 *
 *  @return @c true on success or @c false otherwise
 *
 *  @see ui_viewmgr_view_push_insert_after()
 */
bool ui_viewmgr_view_push_insert_before(ui_viewmgr *viewmgr, ui_view *view, ui_view *before);

/**
 *  @brief Insert a view in this viewmgr view list. Specifically, insert a given @p view right after of the given view, @after.
 *
 *  @oaran viewmgr The viewmgr object
 *  @param view A view to insert in the viewmgr view list
 *  @param after A view that will be just inserted before the @p view. If you pass @c NULL, @p view will be inserted at the end of the view list
 *
 *  @return @c true on success or @c false otherwise
 *
 *  @see ui_viewmgr_view_push_insert_before()
 */
bool ui_viewmgr_view_push_insert_after(ui_viewmgr *viewmgr, ui_view *view, ui_view *after);

/**
 *  @brief Pop the top(last) view from this viewmgr view list.
 *         This function is used when application switches the current view back to the previous view.
 *         The top view will be removed from the view stack and then it will be deleted by the viewmgr.
 *
 *  @note If the view is just one left, then viewmgr would be deactivated automatically since the ui application might be invalid anymore. Otherwise,
 *        the application will be terminated. It's up to system configuration.
 *
 *  @param viewmgr The viewmgr object
 *
 *  @return @c true on success or @c false otherwise
 *
 *  @see ui_viewmgr_deactivate()
 *  @see ui_viewmgr_view_push()
 */
bool ui_viewmgr_view_pop(ui_viewmgr *viewmgr);

/**
 *  @brief Activate this view manager.
 *
 *  @note viewmgr window and views will be shown once this function is called. Usually this should be called after applications set their all views
 *        on initialization time.
 *
 *  @param viewmgr The viewmgr object
 *
 *  @return @c true on success or @c false otherwise
 *
 *  @see ui_viewmgr_deactivate()
 */
bool ui_viewmgr_activate(ui_viewmgr *viewmgr);

/**
 *  @brief Deactivate this view manager.
 *
 *  @note viewmgr window and views will be hidden once this function is called. this behavior is up ui system, but usually it hides(unmap)
 *        current window in order that application go background.
 *
 *  @param viewmgr The viewmgr object
 *
 *  @return @c true success or @c false not
 *
 *  @see ui_viewmgr_activate()
 */
bool ui_viewmgr_deactivate(ui_viewmgr *viewmgr);

/**
 *  @brief Get a window object of viewmgr.
 *
 *  @param viewmgr The viewmgr object
 *
 *  @return The window object of viewmgr
 */
Elm_Win *ui_viewmgr_window_get(ui_viewmgr *viewmgr);

/**
 *  @brief Return a last(top) view.
 *
 *  @param viewmgr The viewmgr object
 *
 *  @return The view which is last view of the viewmgr view list
 */
ui_view *ui_viewmgr_last_view_get(ui_viewmgr *viewmgr);

/**
 *  @brief Return a view which is matched with the index @p idx.
 *
 *  @param viewmgr The viewmgr object
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
ui_view *ui_viewmgr_view_get(ui_viewmgr *viewmgr, int idx);

//ui_view *ui_viewmgr_view_get_by_id(ui_viewmgr *viewmgr, const char *id);

/**
 *  @brief Get a base layout of viewmgr.
 *
 *  @param viewmgr The viewmgr object
 *
 *  @return The base layout object of viewmgr
 */
Evas_Object *ui_viewmgr_base_get(ui_viewmgr *viewmgr);

/**
 *  @brief Return a view index(page) number of the given view.
 *         You could use this function to query the given @p view list order.
 *
 *  @param viewmgr The viewmgr object
 *  @param view A view to query the index
 *
 *  @return An index of the given @p view on success, otherwise, -1
 *
 *  @warning The index number of views are variable since the view list is variable
 */
int ui_viewmgr_view_index_get(ui_viewmgr *viewmgr, const ui_view *view);

/**
 *  @brief Return the number of views which this viewmgr has.
 *
 *  @param viewgmr The viewmgr object
 *
 *  @return the count of views
 */
int ui_viewmgr_view_count_get(ui_viewmgr *viewmgr);

/**
 *  @brief Return whether soft back key is required or not.
 *
 *  @param viewmgr The viewmgr object
 *
 *  @return @c true if soft key is required, @c false otherwise
 */
bool ui_viewmgr_soft_key_need_get(ui_viewmgr *viewmgr);

/**
 *  @brief Return viewmgr object.
 *
 *  @return The viewmgr object
 */
ui_viewmgr *ui_viewmgr_viewmgr_get();

/**
 *  @brief Macro for calling ui_viewmgr_deactivate()
 */
#define UI_VIEWMGR_DEACTIVATE() (ui_viewmgr_deactivate(ui_viewmgr_viewmgr_get()))

/**
 *  @brief Macro for calling ui_viewmgr_view_push()
 */
#define UI_VIEWMGR_VIEW_PUSH(X) (ui_viewmgr_view_push(ui_viewmgr_viewmgr_get(), (X)))

/**
 *  @brief Macro for calling ui_viewmgr_view_pop()
 */
#define UI_VIEWMGR_VIEW_POP() (ui_viewmgr_view_pop(ui_viewmgr_viewmgr_get()))

#ifdef __cplusplus
}
#endif

#endif /* _UI_VIEWMGR_CAPI_H_ */
