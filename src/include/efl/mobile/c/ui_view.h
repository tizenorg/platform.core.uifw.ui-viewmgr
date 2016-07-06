#ifndef _UI_VIEW_CAPI_H_
#define _UI_VIEW_CAPI_H_

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @defgroup CAPI_UI_VIEWMGR_VIEW ui_view
 * @ingroup CAPI_UI_VIEWMGR
 * @brief This module provides functionalities about ui_view.
 * @{
 */

/**
 *  @brief ui_view's lifecycle callback function signature.
 */
typedef bool (*ui_view_lifecycle_cb)(ui_view *view, void *data);

/**
 *  @brief ui_view's rotate event callback function signature.
 */
typedef bool (*ui_view_event_rotate_cb)(ui_view *view, int degree, void *data);
/**
 *  @brief ui_view's portrait event callback function signature.
 */
typedef bool (*ui_view_event_portrait_cb)(ui_view *view, void *data);
/**
 *  @brief ui_view's landscape event callback function signature.
 */
typedef bool (*ui_view_event_landscape_cb)(ui_view *view, void *data);
/**
 *  @brief ui_view's back event callback function signature.
 */
typedef bool (*ui_view_event_back_cb)(ui_view *view, void *data);
/**
 *  @brief ui_view's menu event callback function signature.
 */
typedef bool (*ui_view_event_menu_cb)(ui_menu *menu, void *data);

/**
 *  @brief The structure type containing the set of callback functions for handling view's lifecycle events.
 */
typedef struct
{
	ui_view_lifecycle_cb load;
	ui_view_lifecycle_cb unload;
	ui_view_lifecycle_cb pause;
	ui_view_lifecycle_cb resume;
	ui_view_lifecycle_cb activate;
	ui_view_lifecycle_cb deactivate;
	ui_view_lifecycle_cb destroy;
} ui_view_lifecycle_callback_s;

/**
 *  @brief The structure type containing the set of callback functions for handling view's events.
 */
typedef struct
{
	ui_view_event_rotate_cb rotate;
	ui_view_event_portrait_cb portrait;
	ui_view_event_landscape_cb landscape;
	ui_view_event_back_cb back;
	ui_view_event_menu_cb menu;
} ui_view_event_callback_s;


/**
 *  @brief A constructor for an ui_view.
 *
 *  @param name view name.
 *
 *  @return The ui_view instance.
 *
 *  @warning if you don't set a view name, you could not look up the view with its name. @see ui_viewmgr_view_get_by_name().
 *
 *  @see ui_view_destroy()
 */
EAPI ui_view *ui_view_create(const char *name);

/**
 *  @brief Replace or set a content of ui_view.
 *
 *  @param view An ui_view instance.
 *  @param content A new content. It allows @c NULL for canceling the previous content.
 *
 *  @return @c true if it succeeds, @c false otherwise.
 *
 *  @see ui_view_content_get()
 */
EAPI bool ui_view_set_content(ui_view *view, Evas_Object *content);

/**
 *  @brief Set callback functions for handling view's lifecycle events.
 *
 *  @param view An ui_view instance.
 *  @param lifecycle_callback The set of callback functions to handle application lifecycle events.
 *  @param data The user data to be passed to the given @p lifecycle_callback functions.
 *
 *  @return @c true if it succeeds, @c false otherwise.
 */
EAPI bool ui_view_set_lifecycle_callbacks(ui_view *view, ui_view_lifecycle_callback_s *lifecycle_callback, void *data);

/**
 *  @brief Set callback functions for handling view events.
 *
 *  @param view An ui_view instance.
 *  @param event_callback The set of callback functions to handle view events.
 *  @param data The user data to be passed to the given @p event_callback functions.
 *
 *  @return @c true if it succeeds, @c false otherwise.
 */
EAPI bool ui_view_set_event_callbacks(ui_view *view, ui_view_event_callback_s *event_callback, void *data);

/**
 *  @brief Get a base object of ui_view.
 *
 *  @param view An ui_view instance.
 *
 *  @note Normally, this base object can be used for a parent of a view content.
 *
 *  @return The base object of ui_view.
 */
EAPI Evas_Object* ui_view_get_base(ui_view *view);

/**
 *  @brief Unset a ui_view content.
 *
 *  @param view An ui_view instance.
 *
 *  @return A previous content. If it wasn't, return @c NULL.
 *
 *  @see ui_view_content_set()
 */
EAPI Evas_Object *ui_view_unset_content(ui_view *view);

/**
 *  @brief Set the indicator mode of a ui_view.
 *
 *  @param view An ui_view instance.
 *  @param indicator The mode to set, one of #ui_view_indicator
 *
 *  @see ui_view_indicator_get()
 */
EAPI void ui_view_set_indicator(ui_view *view, ui_view_indicator indicator);

/**
 *  @brief Return the indicator mode of this view.
 *
 *  @param view An ui_view instance.
 *
 *  @return indicator state of the given @p view.
 *
 *  @see ui_view_indicator_set()
 */
EAPI ui_view_indicator ui_view_get_indicator(ui_view *view);

/**
 *  @brief Set content removable.
 *
 *  @param view An ui_view instance.
 *  @param removable if @p removable is @c true, content of this view will be removed on unload state. @c false otherwise
 *
 *  @warning You should not remove a view content manually on unload status if removable content is set.
 *
 *  @see ui_view_removable_content_get()
 */
EAPI void ui_view_set_removable_content(ui_view *view, bool remove);

/**
 *  @brief Return a state of removable content.
 *
 *  @param view An ui_view instance.
 *
 *  @return @c true if the view's content is removable, otherwise @c false.
 *
 *  @see ui_view_removable_content_get()
 */
EAPI bool ui_view_get_removable_content(ui_view *view);

/**
 *  @brief Get the current view's degree.
 *
 *  @param view An ui_view instance.
 *
 *  @return Current rotation degree, -1 if it fails to get degree information.
 */
EAPI int ui_view_get_degree(ui_view *view);

/**
 *  @brief Get current view's orientation mode.
 *
 *  @param view An ui_view instance
 *
 *  @return Current orientation mode, one of #ui_view_orientation_mode.
 */
EAPI ui_view_orientation_mode ui_view_get_orientation_mode(ui_view *view);

/**
 *  @breif Set the array of view's available rotations.
 *
 *  @note Set an array of rotation values.
 *        For instance, {0, 90, 180, 270}. These rotation values depends on the system support.
 *
 *  @param rotations The array of rotation values.
 *  @param count The number of arrays of rotatons.
 */
EAPI bool ui_view_set_available_rotations(ui_view *view, const int *rotations, int count);

/**
 *  @brief Set transition style of a view.
 *
 *  @note @p style is reserved for supporting various kinds of view transition effects.
 *        The actual behaviors with this transition style is up to your frameworks. Default value of the style is NULL.
 *        and "none" represents none transition. If you don't like give any transition effects to this view, you can pass "none" as @p style.
 *
 *  @param view An ui_view instance.
 *  @param style a transition style name
 *
 *  @return @c true if the given @c style is available, otherwise @c false.
 *
 *  @see ui_view_transition_style_get()
 */
EAPI bool ui_view_set_transition_style(ui_view *view, const char *style);

/**
 *  @brief Return a style name of this view.
 *
 *  @param view An ui_view instance.
 *
 *  @return style name of view.
 *
 *  @see ui_view_transition_style_set()
 */
EAPI const char *ui_view_get_transition_style(ui_view *view);

/**
 *  @brief Get a ui_menu instance.
 *
 *  @param view An ui_view instance.
 *
 *  @return The ui_memnu that connected with given @p view.
 */
EAPI const ui_menu *ui_view_get_menu(ui_view *view);

/**
 *  @brief Return a name of this view.
 *
 *  @param view An ui_view instance.
 *
 *  @return name of @p view.
 *
 *  @see ui_view_name_set()
 */
EAPI const char *ui_view_get_name(ui_view *view);

/**
 *  @brief Return a state of this view.
 *
 *  @param view An ui_view instance.
 *
 *  @return current state of @p view.
 */
EAPI ui_view_state ui_view_get_state(ui_view *view);

/**
 *  @brief Return a content of this view.
 *
 *  @param view An ui_view instance.
 *
 *  @return content of @p view. If no contents set yet, @c NULL.
 *
 *  @see ui_view_content_set()
 */
EAPI Evas_Object *ui_view_get_content(ui_view *view);

/**
 *  @brief A destructor for an ui_view.
 *
 *  @param view An ui_view instance.
 *
 *  @return @c true if it succeeds, @c false otherwise.
 *
 *  @see ui_view_create()
 *  @see ui_standard_view_create()
 */
EAPI bool ui_view_destroy(ui_view *view);

#ifdef __cplusplus
}
#endif

/**
 * @}
 */

#endif /* _UI_VIEW_CAPI_H_ */
