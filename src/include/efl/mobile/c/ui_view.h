#ifndef _UI_VIEW_CAPI_H_
#define _UI_VIEW_CAPI_H_

#ifdef __cplusplus
extern "C" {
#endif

/**
 *  @brief ui_view's 'lifecycle callback' function signature.
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

//================================== view common APIs ========================================

/**
 *  @brief Set callback functions for handling view's lifecycle events.
 *
 *  @param view The ui_view object
 *  @param lifecycle_callback The set of callback functions to handle application lifecycle events
 *  @param data The user data to be passed to the callback functions
 *
 *  @return true if it succeed, false otherwise
 */
bool ui_view_lifecycle_callbacks_set(ui_view *view, ui_view_lifecycle_callback_s *lifecycle_callback, void *data);

/**
 *  @brief Set callback functions for handling view events.
 *
 *  @param view The ui_view object
 *  @param event_callback The set of callback functions to handle view events
 *  @param data The user data to be passed to the callback functions
 *
 *  @return true if it succeed, false otherwise
 */
bool ui_view_event_callbacks_set(ui_view *view, ui_view_event_callback_s *event_callback, void *data);

/**
 *  @brief Get a base layout of viewmgr.
 *
 *  @param view The ui_view object
 *
 *  @return viewmgr's base layout object
 */
Evas_Object* ui_view_base_get(ui_view *view);

/**
 *  @brief This is for unsetting a content of the view.
 *
 *  @param view The ui_view object
 *
 *  @return A previous content. If it wasn't, return value will be @c NULL
 *
 *  @see ui_view_content_set()
 */
Evas_Object *ui_view_content_unset(ui_view *view);

/**
 *  @brief Set indicator of the view.
 *
 *  @param view The ui_view object
 *  @param indicator The mode to set, one of #ui_view_indicator
 *
 *  @return @c false if current indicator is same with new one, @c true otherwise
 *
 *  @see ui_view_indicator_get()
 */
void ui_view_indicator_set(ui_view *view, ui_view_indicator indicator);

/**
 *  @brief Return the indicator mode of this view.
 *
 *  @param view The ui_view object
 *
 *  @return indicator state of view
 *
 *  @see ui_view_indicator_set()
 */
ui_view_indicator ui_view_indicator_get(ui_view *view);

/**
 *  @brief Set content removable.
 *
 *  @param view The ui_view object
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
 *  @param view The ui_view object
 *
 *  @return true if the view's content is removable, otherwise false
 *
 *  @see ui_view_removable_content_get()
 */
bool ui_view_removable_content_get(ui_view *view);

/**
 *  @brief Get current view's degree.
 *
 *  @param view The ui_view object
 *
 *  @return Current rotation degree, -1 if it fails to get degree information
 */
int ui_view_degree_get(ui_view *view);

/**
 *  @brief Set transition style of a view.
 *
 *  @note @p style is reserved for supporting various kinds of view transition effects.
 *        The actual behaviors with this transition style is up to your frameworks. Default value of the style is NULL.
 *        and "none" represents none transition. If you don't like give any transition effects to this view, you can pass "none" as @p style.
 *
 *  @param view The ui_view object
 *  @param style a transition style name
 *
 *  @return true if the given @c style is available, otherwise false
 *
 *  @see ui_view_transition_style_get()
 */
bool ui_view_transition_style_set(ui_view *view, const char *style);

/**
 *  @brief Return a style name of this view.
 *
 *  @param view The ui_view object
 *
 *  @return style name of view
 *
 *  @see ui_view_transition_style_set()
 */
const char *ui_view_transition_style_get(ui_view *view);

/**
 *  @brief Get menu object.
 *
 *  @param view The ui_view object
 *
 *  @return The menu object of connected with view
 */
const ui_menu *ui_view_menu_get(ui_view *view);

/**
 *  @brief Set name of the view.
 *
 *  @note A view can get a specific name. default value of the name is NULL.
 *
 *  @param view The ui_view object
 *  @param name A new name of view
 *
 *  @return true if the given @c name is available, otherwise false
 *
 *  @warning When you override this member function, you should check the name duplicate with other view or not.
 *
 *  @see ui_view_name_get()
 */
bool ui_view_name_set(ui_view *view, const char *name);

/**
 *  @brief Return a name of this view.
 *
 *  @param view The ui_view object
 *
 *  @return name of view
 *
 *  @see ui_view_name_set()
 */
const char *ui_view_name_get(ui_view *view);

/**
 *  @brief Return a state of this view.
 *
 *  @param view The ui_view object
 *
 *  @return current state of view
 */
ui_view_state ui_view_state_get(ui_view *view);

/**
 *  @brief Return a content of this view.
 *
 *  @param view The ui_view object
 *
 *  @return content of view
 *
 *  @see ui_view_content_set()
 */
Evas_Object *ui_view_content_get(ui_view *view);

/**
 *  @brief This is a view destructor.
 *
 *  @param view The ui_view object
 *
 *  @return true if it succeed, false otherwise
 */
bool ui_view_destroy(ui_view *view);

//================================ ui_standard view APIs =====================================

/**
 *  @brief This is a constructor for initializing ui_standard_view.
 *
 *  @param name view name
 *
 *  @return The ui_view object
 *
 *  @see ui_view_destroy()
 */
ui_view *ui_standard_view_create(const char *name);

/**
 *  @brief This is for replacing or setting a content of the view.
 *
 *  @param view The ui_view object
 *  @param content A new content. It allows @c NULL for canceling the previous content
 *  @param title  The label in the title area. The name of the title label part is "elm.text.title"
 *  @param subtitle  The label in the subtitle area. The name of the subtitle label part is "elm.text.subtitle"
 *  @param title_left_btn The button in the left part of title area
 *  @param title_right_btn The button in the right part of title area
 *
 *  @return true if it succeed, false otherwise
 *
 *  @see ui_view_content_get()
 */
bool ui_standard_view_content_set(ui_view *view, Evas_Object *content, const char *title, const char *subtitle, Evas_Object *title_left_btn,
        Evas_Object *title_right_btn);

/**
 *  @brief This is for setting title text.
 *
 *  @param view The ui_view object
 *  @param text The label in the title area
 *
 *  @return true if it succeed, false otherwise
 *
 *  @ui_standard_view_title_get()
 */
bool ui_standard_view_title_set(ui_view *view, const char *text);

/**
 *  @brief This is for setting subtitle text.
 *
 *  @param view The ui_view object
 *  @param text The label in the subtitle area
 *
 *  @return true if it succeed, false otherwise
 *
 *  @see ui_standard_view_sub_title_get()
 */
bool ui_standard_view_sub_title_set(ui_view *view, const char *text);

/**
 *  @brief This is for setting title badge text.
 *
 *  @param view The ui_view object
 *  @param text The label in the title badge area
 *
 *  @return true if it succeed, false otherwise
 *
 *  @see ui_standard_view_title_badge_get()
 */
bool ui_standard_view_title_badge_set(ui_view *view, const char *badge_text);

/**
 *  @brief This is for setting title_right_btn.
 *
 *  @param view The ui_view object
 *  @param title_right_btn The button in the right part of title area
 *
 *  @return true if it succeed, false otherwise
 *
 *  @see ui_standard_view_title_right_btn_get()
 */
bool ui_standard_view_title_right_btn_set(ui_view *view, Evas_Object *title_right_btn);

/**
 *  @brief Return a title right button of the view.
 *
 *  @param view The ui_view object
 *
 *  @return title right button of the view
 *
 *  @see ui_standard_view_title_right_btn_set()
 */
Elm_Button *ui_standard_view_title_right_btn_get(ui_view *view);

/**
 *  @brief This is for unsetting a title right button of title area.
 *
 *  @param view The ui_view object
 *  @return A previous content. If it wasn't, return value will be @c NULL
 */
Elm_Button *ui_standard_view_title_right_btn_unset(ui_view *view);

/**
 *  @brief This is for setting title_left_btn.
 *
 *  @param view The ui_view object
 *  @param title_left_btn The button in the left part of title area
 *
 *  @return true if it succeed, false otherwise
 *
 *  @see ui_standard_view_title_left_btn_get()
 */
bool ui_standard_view_title_left_btn_set(ui_view *view, Evas_Object *title_left_btn);

/**
 *  @brief Return a title left button of the view.
 *
 *  @param view The ui_view object
 *
 *  @return title left button of the view
 *
 *  @see ui_standard_view_title_left_btn_set()
 */
Elm_Button *ui_standard_view_title_left_btn_get(ui_view *view);

/**
 *  @brief This is for unsetting a title right button of title area.
 *
 *  @param view The ui_view object
 *
 *  @return A previous content. If it wasn't, return value will be @c NULL
 */
Elm_Button *ui_standard_view_title_left_btn_unset(ui_view *view);

/**
 *  @brief This is for setting toolbar below title.
 *
 *  @param view The ui_view obejct
 *  @param toolbar Toolbar object
 *
 *  @return true if it succeed, false otherwise
 *
 *  @see ui_standard_view_toolbar_get()
 */
bool ui_standard_view_toolbar_set(ui_view *view, Elm_Toolbar *toolbar);

/**
 *  @brief Return a toolbar of the view.
 *
 *  @param view The ui_view obejct
 *  @return toolbar of the view
 *
 *  @see ui_standard_view_toolbar_set()
 */
Elm_Toolbar *ui_standard_view_toolbar_get(ui_view *view);

/**
 *  @brief This is for unsetting a toolbar.
 *
 *  @param view The ui_view object
 *
 *  @return A previous content. If it wasn't, return value will be @c NULL
 */
Elm_Toolbar *ui_standard_view_toolbar_unset(ui_view *view);

/**
 *  @brief This is handling title visible state.
 *
 *  @param view The ui_view object
 *  @param visible title state set as visible if the given param is true, otherwise title area set as invisible
 *  @param anim title area will be shown with animation if the given param is true, otherwise title area will be shown without animation
 *
 *  @return true if it succeed, false otherwise
 */
bool ui_standard_view_title_visible_set(ui_view *view, bool visible, bool anim);

//==================================== ui_view APIs ==========================================

/**
 *  @brief This is a constructor for initializing ui_view.
 *
 *  @param name view name
 *
 *  @return The ui_view object
 *
 *  @see ui_view_destory()
 */
ui_view *ui_view_create(const char *name);

/**
 *  @brief This is for replacing or setting a content of the view.
 *
 *  @param view The ui_view object
 *  @param content A new content. It allows @c NULL for canceling the previous content
 *
 *  @return true if it succeed, false otherwise
 *
 *  @see ui_view_content_get()
 */
bool ui_view_content_set(ui_view *view, Evas_Object *content);


#ifdef __cplusplus
}
#endif

#endif /* _UI_VIEW_CAPI_H_ */
