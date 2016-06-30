#ifndef _UI_MENU_CAPI_H_
#define _UI_MENU_CAPI_H_

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @defgroup CAPI_UI_VIEWMGR_MENU ui_menu
 * @ingroup CAPI_UI_VIEWMGR
 * @brief This module provides functionalities about ui_menu.
 * @{
 */

/**
 *  @brief Replace or set a content of an ui_menu.
 *
 *  @param menu An ui_menu object
 *  @param ctxpopup ctxpopup object. It allows @c NULL for canceling the previous content.
 *
 *  @return @c true if it succeeds, @c false otherwise.
 *
 *  @see ui_menu_content_get()
 */
EAPI bool ui_menu_set_content(ui_menu *menu, Elm_Ctxpopup *ctxpopup);

/**
 *  @brief Return an ui_menu content.
 *
 *  @param menu An ui_menu instance.
 *
 *  @return A content of ui_menu.
 *
 *  @see ui_menu_content_set()
 */
EAPI Elm_Ctxpopup *ui_menu_get_content(ui_menu *menu);

/**
 *  @brief Unset an ui_menu content.
 *
 *  @param menu An ui_menu instance.
 *
 *  @return A previous content. If it wasn't, return @c NULL.
 *
 *  @see ui_menu_content_set()
 */
EAPI Elm_Ctxpopup *ui_menu_unset_content(ui_menu *menu);

/**
 *  @brief Activate an ui_menu.
 *
 *  @note It makes ui_menu state as show.
 *
 *  @param menu An ui_menu instance.
 *
 *  @return @c true if it succeeds, @c false otherwise.
 *
 *  @see ui_menu_deactivate()
 */
EAPI bool ui_menu_activate(ui_menu *menu);

/**
 *  @brief Deactivate an ui_menu.
 *
 *  @note It makes ui_menu state as hide.
 *
 *  @param menu An ui_menu instance.
 *
 *  @return @c true if it succeeds, @c false otherwise.
 *
 *  @see ui_menu_activate()
 */
EAPI bool ui_menu_deactivate(ui_menu *menu);

/**
 *  @brief Return the active status of ui_menu.
 *
 *  @param menu An ui_menu instance.
 *
 *  @return @c true if it succeeds, @c false otherwise.
 *
 *  @see ui_menu_activate()
 *  @see ui_menu_deactivate()
 */
EAPI bool ui_menu_get_activated(ui_menu *menu);

/**
 *  @brief Get a base object of an ui_menu.
 *
 *  @note Normally, A base object can be used for a parent of ui_menu content.
 *
 *  @param menu An ui_menu instance.
 *
 *  @return base object of ui_menu.
 */
EAPI Evas_Object *ui_menu_get_base(ui_menu *menu);

/**
 *  @brief Get a current ui_menu's degree.
 *
 *  @param menu An ui_menu instance.
 *
 *  @return Current rotation degree, -1 if it fails to get degree information.
 */
EAPI int ui_menu_get_degree(ui_menu *menu);

/**
 *  @brief Return a view which is matched with this ui_menu.
 *
 *  @param menu An ui_menu instance.
 *
 *  @return The view which is matched with ui_menu
 */
EAPI ui_view *ui_menu_get_view(ui_menu *menu);

#ifdef __cplusplus
}
#endif

/**
 * @}
 */

#endif /* _UI_MENU_CAPI_H_ */
