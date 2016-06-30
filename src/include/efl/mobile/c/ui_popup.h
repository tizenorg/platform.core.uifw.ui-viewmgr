#ifndef _UI_POPUP_CAPI_H_
#define _UI_POPUP_CAPI_H_

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @defgroup CAPI_UI_VIEWMGR_POPUP ui_popup
 * @ingroup CAPI_UI_VIEWMGR
 * @brief This module provides functionalities about ui_popup.
 * @{
 */

/**
 *  @brief A constructor for an ui_popup.
 *
 *  @param view An instance of ui_view.
 *
 *  @note The instance of ui_popup is subordinated to the given @p ui_view. If the given @p ui_view is hidden or deactivated, this ui_popup will be also do
 *        same followed to its ui_view behaviors.
 *
 *  @return An ui_popup instance.
 *
 *  @warning The instance of ui_popup will be destroyed automatically when the ui_view is destroyed.
 *
 *  @see ui_popup_destroy()
 */
EAPI ui_popup *ui_popup_create(ui_view *view);

/**
 *  @brief A destructor for an ui_popup.
 *
 *  @note destroy an @p given ui_popup instance.
 *
 *  @param popup An ui_popup instance.
 *
 *  @see ui_popup_create()
 */
EAPI void ui_popup_destroy(ui_popup *popup);

/**
 *  @brief Replace or set a content of an ui_popup.
 *
 *  @param popup An ui_popup instance.
 *  @param content popup object. It allows @c NULL for canceling the previous content.
 *
 *  @return @c true if it succeeds, @c false otherwise.
 *
 *  @see ui_popup_content_get()
 */
EAPI bool ui_popup_set_content(ui_popup *popup, Elm_Popup *content);

/**
 *  @brief Return a content object of ui_popup.
 *
 *  @param popup An ui_popup instance.
 *
 *  @return A content of ui_popup.
 *
 *  @see ui_popup_content_set()
 */
EAPI Elm_Popup *ui_popup_get_content(ui_popup *popup);

/**
 *  @brief Unset an ui_popup content.
 *
 *  @param popup An ui_popup instance.
 *
 *  @return A previous content. If it wasn't, return @c NULL.
 *
 *  @see ui_popup_content_set()
 */
EAPI Elm_Popup *ui_popup_unset_content(ui_popup *popup);

/**
 *  @brief Activate an ui_popup.
 *
 *  @note It makes ui_popup state as show.
 *
 *  @param popup An ui_popup instance.
 *
 *  @return @c true if it succeeds, @c false otherwise.
 *
 *  @see ui_popup_deactivate()
 */
EAPI bool ui_popup_activate(ui_popup *popup);

/**
 *  @brief Deactivate an ui_popup.
 *
 *  @note It makes ui_popup state as hide.
 *
 *  @param popup An ui_popup instance.
 *
 *  @return @c true if it succeeds, @c false otherwise.
 *
 *  @see ui_popup_activate()
 */
EAPI bool ui_popup_deactivate(ui_popup *popup);

/**
 *  @brief Return the active status of ui_popup.
 *
 *  @param popup An ui_popup instance.
 *
 *  @return @c true if ui_popup is activated, @c false otherwise
 *
 *  @see ui_popup_activate()
 *  @see ui_popup_deactivate()
 */
EAPI bool ui_popup_get_activated(ui_popup *popup);

/**
 *  @brief Get a base object of an ui_popup.
 *
 *  @note Normally, A base object can be used for a parent of ui_popup content.
 *
 *  @param menu An ui_popup instance.
 *
 *  @return base object of ui_popup.
 */
EAPI Evas_Object *ui_popup_get_base(ui_popup *popup);

/**
 *  @brief Get current ui_popup's degree.
 *
 *  @param popup An ui_popup instance.
 *
 *  @return Current rotation degree, -1 if it fails to get degree information.
 */
EAPI int ui_popup_get_degree(ui_popup *popup);

/**
 *  @brief Return a view which is matched with the ui_popup.
 *
 *  @param popup An ui_popup instance.
 *
 *  @return The view which is matched with ui_popup.
 */
EAPI ui_view *ui_popup_get_view(ui_popup *popup);

#ifdef __cplusplus
}
#endif

/**
 * @}
 */

#endif /* _UI_POPUP_CAPI_H_ */
