#ifndef _UI_STANDARD_VIEW_CAPI_H_
#define _UI_STANDARD_VIEW_CAPI_H_

#ifdef __cplusplus
extern "C" {
#endif

/**
 *  @brief A constructor for an ui_standard_view.
 *
 *  @param name view name
 *
 *  @param view An ui_view instance.
 *
 *  @see ui_view_destroy()
 */
ui_view *ui_standard_view_create(const char *name);

/**
 *  @brief Replace or set a content of the view.
 *
 *  @param view An ui_view instance.
 *  @param content A new content. It allows @c NULL for canceling the previous content.
 *  @param title The label in the title area. The name of the title label part is "elm.text.title".
 *  @param subtitle The label in the subtitle area. The name of the subtitle label part is "elm.text.subtitle".
 *  @param title_left_btn The button in the left part of title area.
 *  @param title_right_btn The button in the right part of title area.
 *
 *  @return @c true if it succeeds, @c false otherwise.
 *
 *  @see ui_view_content_get()
 */
bool ui_standard_view_content_set(ui_view *view, Evas_Object *content, const char *title, const char *subtitle, Evas_Object *title_left_btn, Evas_Object *title_right_btn);

/**
 *  @brief Set a title text.
 *
 *  @param view An ui_view instance.
 *  @param text The label in the title area
 *
 *  @return @c true if it succeeds, @c false otherwise.
 *
 *  @ui_standard_view_title_get()
 */
bool ui_standard_view_title_set(ui_view *view, const char *text);

/**
 *  @brief Set a subtitle text.
 *
 *  @param view An ui_view instance.
 *  @param text The label in the subtitle area.
 *
 *  @return @c true if it succeeds, @c false otherwise.
 *
 *  @see ui_standard_view_sub_title_get()
 */
bool ui_standard_view_sub_title_set(ui_view *view, const char *text);

/**
 *  @brief Set a title badge text.
 *
 *  @param view An ui_view instance.
 *  @param text The label in the title badge area.
 *
 *  @return @c true if it succeeds, @c false otherwise.
 *
 *  @see ui_standard_view_title_badge_get()
 */
bool ui_standard_view_title_badge_set(ui_view *view, const char *badge_text);

/**
 *  @brief Set a title_right_btn.
 *
 *  @param view An ui_view instance.
 *  @param title_right_btn The button in the right part of title area.
 *
 *  @return @c true if it succeeds, @c false otherwise.
 *
 *  @see ui_standard_view_title_right_btn_get()
 */
bool ui_standard_view_title_right_btn_set(ui_view *view, Evas_Object *title_right_btn);

/**
 *  @brief Return a title right button of the view.
 *
 *  @param view An ui_view instance.
 *
 *  @return title right button of the view.
 *
 *  @see ui_standard_view_title_right_btn_set()
 */
Elm_Button *ui_standard_view_title_right_btn_get(ui_view *view);

/**
 *  @brief Unset a title right button of title area.
 *
 *  @param view An ui_view instance.
 *  @return A previous content. If it wasn't, return @c NULL
 */
Elm_Button *ui_standard_view_title_right_btn_unset(ui_view *view);

/**
 *  @brief Set a title_left_btn.
 *
 *  @param view An ui_view instance.
 *  @param title_left_btn The button in the left part of title area.
 *
 *  @return @c true if it succeeds, @c false otherwise.
 *
 *  @see ui_standard_view_title_left_btn_get()
 */
bool ui_standard_view_title_left_btn_set(ui_view *view, Evas_Object *title_left_btn);

/**
 *  @brief Return a title left button of the view.
 *
 *  @param view An ui_view instance.
 *
 *  @return title left button of the view
 *
 *  @see ui_standard_view_title_left_btn_set()
 */
Elm_Button *ui_standard_view_title_left_btn_get(ui_view *view);

/**
 *  @brief Unset a title right button of title area.
 *
 *  @param view An ui_view instance.
 *
 *  @return A previous content. If it wasn't, return @c NULL.
 */
Elm_Button *ui_standard_view_title_left_btn_unset(ui_view *view);

/**
 *  @brief Set a toolbar below title.
 *
 *  @param view An ui_view instance.
 *  @param toolbar Toolbar object
 *
 *  @return @c true if it succeeds, @c false otherwise.
 *
 *  @see ui_standard_view_toolbar_get()
 */
bool ui_standard_view_toolbar_set(ui_view *view, Elm_Toolbar *toolbar);

/**
 *  @brief Return a toolbar of the view.
 *
 *  @param view An ui_view instance.
 *  @return The toolbar of the given @p view.
 *
 *  @see ui_standard_view_toolbar_set()
 */
Elm_Toolbar *ui_standard_view_toolbar_get(ui_view *view);

/**
 *  @brief Unset a toolbar.
 *
 *  @param view An ui_view instance.
 *
 *  @return A previous content. If it wasn't, return @c NULL.
 */
Elm_Toolbar *ui_standard_view_toolbar_unset(ui_view *view);

/**
 *  @brief Control the title visible state.
 *
 *  @param view An ui_view instance.
 *  @param visible title state set as visible if the given param is @c true, otherwise title area set as invisible
 *  @param anim title area will be shown with animation if the given param is @c true, otherwise title area will be shown without animation
 *
 *  @return @c true if it succeeds, @c false otherwise.
 */
bool ui_standard_view_title_visible_set(ui_view *view, bool visible, bool anim);

#ifdef __cplusplus
}
#endif

#endif /* _UI_STANDARD_VIEW_CAPI_H_ */
