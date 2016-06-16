#ifndef _UI_VIEW_CAPI_H_
#define _UI_VIEW_CAPI_H_

#ifdef __cplusplus
extern "C" {
#endif

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
 *  @see ui_view_destroy()
 */
ui_view *ui_view_create(const char *name);

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
bool ui_view_content_set(ui_view *view, Evas_Object *content);

/**
 *  @brief Set callback functions for handling view's lifecycle events.
 *
 *  @param view An ui_view instance.
 *  @param lifecycle_callback The set of callback functions to handle application lifecycle events.
 *  @param data The user data to be passed to the given @p lifecycle_callback functions.
 *
 *  @return @c true if it succeeds, @c false otherwise.
 */
bool ui_view_lifecycle_callbacks_set(ui_view *view, ui_view_lifecycle_callback_s *lifecycle_callback, void *data);

/**
 *  @brief Set callback functions for handling view events.
 *
 *  @param view An ui_view instance.
 *  @param event_callback The set of callback functions to handle view events.
 *  @param data The user data to be passed to the given @p event_callback functions.
 *
 *  @return @c true if it succeeds, @c false otherwise.
 */
bool ui_view_event_callbacks_set(ui_view *view, ui_view_event_callback_s *event_callback, void *data);

/**
 *  @brief Get a base object of ui_view.
 *
 *  @param view An ui_view instance.
 *
 *  @note Normally, this base object can be used for a parent of a view content.
 *
 *  @return The base object of ui_view.
 */
Evas_Object* ui_view_base_get(ui_view *view);

/**
 *  @brief Unset a ui_view content.
 *
 *  @param view An ui_view instance.
 *
 *  @return A previous content. If it wasn't, return @c NULL.
 *
 *  @see ui_view_content_set()
 */
Evas_Object *ui_view_content_unset(ui_view *view);

/**
 *  @brief Set the indicator mode of a ui_view.
 *
 *  @param view An ui_view instance.
 *  @param indicator The mode to set, one of #ui_view_indicator
 *
 *  @see ui_view_indicator_get()
 */
void ui_view_indicator_set(ui_view *view, ui_view_indicator indicator);

/**
 *  @brief Return the indicator mode of this view.
 *
 *  @param view An ui_view instance.
 *
 *  @return indicator state of the given @p view.
 *
 *  @see ui_view_indicator_set()
 */
ui_view_indicator ui_view_indicator_get(ui_view *view);

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
void ui_view_removable_content_set(ui_view *view, bool remove);

/**
 *  @brief Return a state of removable content.
 *
 *  @param view An ui_view instance.
 *
 *  @return @c true if the view's content is removable, otherwise @c false.
 *
 *  @see ui_view_removable_content_get()
 */
bool ui_view_removable_content_get(ui_view *view);

/**
 *  @brief Get the current view's degree.
 *
 *  @param view An ui_view instance.
 *
 *  @return Current rotation degree, -1 if it fails to get degree information.
 */
int ui_view_degree_get(ui_view *view);

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
bool ui_view_transition_style_set(ui_view *view, const char *style);

/**
 *  @brief Return a style name of this view.
 *
 *  @param view An ui_view instance.
 *
 *  @return style name of view.
 *
 *  @see ui_view_transition_style_set()
 */
const char *ui_view_transition_style_get(ui_view *view);

/**
 *  @brief Get a ui_menu instance.
 *
 *  @param view An ui_view instance.
 *
 *  @return The ui_memnu that connected with given @p view.
 */
const ui_menu *ui_view_menu_get(ui_view *view);

/**
 *  @brief Set name of ui_view.
 *
 *  @note A ui_view can have a unique name. Default value of the name is NULL.
 *
 *  @param view An ui_view instance.
 *  @param name A new name of given @p view.
 *
 *  @return @c true if the given @p name is available, otherwise @c false.
 *
 *  @see ui_view_name_get()
 */
bool ui_view_name_set(ui_view *view, const char *name);

/**
 *  @brief Return a name of this view.
 *
 *  @param view An ui_view instance.
 *
 *  @return name of @p view.
 *
 *  @see ui_view_name_set()
 */
const char *ui_view_name_get(ui_view *view);

/**
 *  @brief Return a state of this view.
 *
 *  @param view An ui_view instance.
 *
 *  @return current state of @p view.
 */
ui_view_state ui_view_state_get(ui_view *view);

/**
 *  @brief Return a content of this view.
 *
 *  @param view An ui_view instance.
 *
 *  @return content of @p view. If no contents set yet, @c NULL.
 *
 *  @see ui_view_content_set()
 */
Evas_Object *ui_view_content_get(ui_view *view);

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
bool ui_view_destroy(ui_view *view);


//================================ ui_standard_view APIs =====================================

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

#endif /* _UI_VIEW_CAPI_H_ */
