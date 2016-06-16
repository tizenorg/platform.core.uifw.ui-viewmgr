#ifndef _UI_MENU_CAPI_H_
#define _UI_MENU_CAPI_H_

#ifdef __cplusplus
extern "C" {
#endif

/**
 *  @brief Replace or set a content of an ui_menu.
 *
 *  @param menu An ui_menu object
 *  @param ctxpopup ctxpopup object. It allows @c NULL to cancel the previous content.
 *
 *  @return @c true if it succeeds, @c false otherwise.
 *
 *  @see ui_menu_content_get()
 */
bool ui_menu_content_set(ui_menu *menu, Elm_Ctxpopup *ctxpopup);

/**
 *  @brief Return an ui_menu content.
 *
 *  @param menu An ui_menu instance.
 *
 *  @return A content of ui_menu.
 *
 *  @see ui_menu_content_set()
 */
Elm_Ctxpopup *ui_menu_content_get(ui_menu *menu);

/**
 *  @brief Unset an ui_menu content.
 *
 *  @param menu An ui_menu instance.
 *
 *  @return A previous content. If it wasn't, return @c NULL.
 *
 *  @see ui_menu_content_set()
 */
Elm_Ctxpopup *ui_menu_content_unset(ui_menu *menu);

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
bool ui_menu_activate(ui_menu *menu);

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
bool ui_menu_deactivate(ui_menu *menu);

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
bool ui_menu_activated_get(ui_menu *menu);

/**
 *  @brief Get a base object of an ui_menu.
 *
 *  @note Normally, A base object can be used for a parent of ui_menu content.
 *
 *  @param menu An ui_menu instance.
 *
 *  @return base object of ui_menu.
 */
Evas_Object *ui_menu_base_get(ui_menu *menu);

/**
 *  @brief Get a current ui_menu's degree.
 *
 *  @param menu An ui_menu instance.
 *
 *  @return Current rotation degree, -1 if it fails to get degree information.
 */
int ui_menu_degree_get(ui_menu *menu);

/**
 *  @brief Return a view which is matched with this ui_menu.
 *
 *  @param menu An ui_menu instance.
 *
 *  @return The view which is matched with ui_menu
 */
ui_view *ui_menu_view_get(ui_menu *menu);

#ifdef __cplusplus
}
#endif

#endif /* _UI_MENU_CAPI_H_ */
