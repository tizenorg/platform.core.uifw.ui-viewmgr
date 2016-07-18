#ifndef _UI_STANDARD_VIEW_CAPI_H_
#define _UI_STANDARD_VIEW_CAPI_H_

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @defgroup CAPI_UI_VIEWMGR_STANDARD_VIEW ui_standard_view
 * @ingroup CAPI_UI_VIEWMGR
 * @brief This module provides functionalities about ui_standard_view.
 * @{
 */

/**
 *  @brief A constructor for an ui_standard_view.
 *
 *  @param name view name
 *  @param view An ui_standard_view instance.
 *
 *  @warning if you don't set a view name, you could not look up the view with its name. @see ui_viewmgr_view_get_by_name().
 *
 *  @see ui_view_destroy()
 */
EAPI ui_standard_view *ui_standard_view_create(const char *name);

/**
 *  @brief Replace or set a content of the view.
 *
 *  @param view An ui_standard_view instance.
 *  @param content A new content. It allows @c NULL for canceling the previous content.
 *
 *  @return @c true if it succeeds, @c false otherwise.
 *
 *  @see ui_view_content_get()
 */
EAPI bool ui_standard_view_set_content(ui_standard_view *view, Evas_Object *content);

/**
 *  @brief Set a title text.
 *
 *  @param view An ui_standard_view instance.
 *  @param text The label in the title area
 *
 *  @return @c true if it succeeds, @c false otherwise.
 *
 *  @ui_standard_view_title_get()
 */
EAPI bool ui_standard_view_set_title(ui_standard_view *view, const char *text);

/**
 *  @brief Set a subtitle text.
 *
 *  @param view An ui_standard_view instance.
 *  @param text The label in the subtitle area.
 *
 *  @return @c true if it succeeds, @c false otherwise.
 *
 *  @see ui_standard_view_sub_title_get()
 */
EAPI bool ui_standard_view_set_sub_title(ui_standard_view *view, const char *text);

/**
 *  @brief Set a title badge text.
 *
 *  @param view An ui_standard_view instance.
 *  @param text The label in the title badge area.
 *
 *  @return @c true if it succeeds, @c false otherwise.
 *
 *  @see ui_standard_view_title_badge_get()
 */
EAPI bool ui_standard_view_set_title_badge(ui_standard_view *view, const char *badge_text);

/**
 *  @brief Set a title_right_btn.
 *
 *  @param view An ui_standard_view instance.
 *  @param title_right_btn The button in the right part of title area.
 *
 *  @return @c true if it succeeds, @c false otherwise.
 *
 *  @see ui_standard_view_title_right_btn_get()
 */
EAPI bool ui_standard_view_set_title_right_btn(ui_standard_view *view, Evas_Object *title_right_btn);

/**
 *  @brief Return a title right button of the view.
 *
 *  @param view An ui_standard_view instance.
 *
 *  @return title right button of the view.
 *
 *  @see ui_standard_view_title_right_btn_set()
 */
EAPI Elm_Button *ui_standard_view_get_title_right_btn(ui_standard_view *view);

/**
 *  @brief Unset a title right button of title area.
 *
 *  @param view An ui_standard_view instance.
 *  @return A previous content. If it wasn't, return @c NULL
 */
EAPI Elm_Button *ui_standard_view_unset_title_right_btn(ui_standard_view *view);

/**
 *  @brief Set a title_left_btn.
 *
 *  @param view An ui_standard_view instance.
 *  @param title_left_btn The button in the left part of title area.
 *
 *  @return @c true if it succeeds, @c false otherwise.
 *
 *  @see ui_standard_view_title_left_btn_get()
 */
EAPI bool ui_standard_view_set_title_left_btn(ui_standard_view *view, Evas_Object *title_left_btn);

/**
 *  @brief Return a title left button of the view.
 *
 *  @param view An ui_standard_view instance.
 *
 *  @return title left button of the view
 *
 *  @see ui_standard_view_title_left_btn_set()
 */
EAPI Elm_Button *ui_standard_view_get_title_left_btn(ui_standard_view *view);

/**
 *  @brief Unset a title right button of title area.
 *
 *  @param view An ui_standard_view instance.
 *
 *  @return A previous content. If it wasn't, return @c NULL.
 */
EAPI Elm_Button *ui_standard_view_unset_title_left_btn(ui_standard_view *view);

/**
 *  @brief Set a toolbar below title.
 *
 *  @param view An ui_standard_view instance.
 *  @param toolbar Toolbar object
 *
 *  @return @c true if it succeeds, @c false otherwise.
 *
 *  @see ui_standard_view_toolbar_get()
 */
EAPI bool ui_standard_view_set_toolbar(ui_standard_view *view, Elm_Toolbar *toolbar);

/**
 *  @brief Return a toolbar of the view.
 *
 *  @param view An ui_standard_view instance.
 *  @return The toolbar of the given @p view.
 *
 *  @see ui_standard_view_toolbar_set()
 */
EAPI Elm_Toolbar *ui_standard_view_get_toolbar(ui_standard_view *view);

/**
 *  @brief Unset a toolbar.
 *
 *  @param view An ui_standard_view instance.
 *
 *  @return A previous content. If it wasn't, return @c NULL.
 */
EAPI Elm_Toolbar *ui_standard_view_unset_toolbar(ui_standard_view *view);

/**
 *  @brief Control the title visible state.
 *
 *  @param view An ui_standard_view instance.
 *  @param visible title state set as visible if the given param is @c true, otherwise title area set as invisible
 *  @param anim title area will be shown with animation if the given param is @c true, otherwise title area will be shown without animation
 *
 *  @return @c true if it succeeds, @c false otherwise.
 */
EAPI bool ui_standard_view_set_title_visible(ui_standard_view *view, bool visible, bool anim);

#ifdef __cplusplus
}
#endif

/**
 * @}
 */

#endif /* _UI_STANDARD_VIEW_CAPI_H_ */
