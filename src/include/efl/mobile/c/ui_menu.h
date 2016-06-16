#ifndef _UI_MENU_CAPI_H_
#define _UI_MENU_CAPI_H_

#ifdef __cplusplus
extern "C" {
#endif

/**
 *  @brief This is for replacing or setting a content of the ui_menu.
 *
 *  @param menu The ui_menu object
 *  @param ctxpopup ctxpopup object. It allows @c NULL for canceling the previous content
 *
 *  @return true if it succeed, false otherwise
 *
 *  @see ui_menu_content_get()
 */
bool ui_menu_content_set(ui_menu *menu, Elm_Ctxpopup *ctxpopup);

/**
 *  @brief Return a content object of ui_menu.
 *
 *  @param menu The ui_menu object
 *
 *  @return content of ui_memu object
 *
 *  @see ui_menu_content_set()
 */
Elm_Ctxpopup *ui_menu_content_get(ui_menu *menu);

/**
 *  @brief This is for unsetting a content of the ui_menu.
 *
 *  @param menu The ui_menu object
 *
 *  @return A previous content. If it wasn't, return value will be @c NULL.
 */
Elm_Ctxpopup *ui_menu_content_unset(ui_menu *menu);

/**
 *  @brief This is activating the ui_menu.
 *
 *  @note It makes ui_menu state as show.
 *
 *  @param menu The ui_menu object
 *
 *  @return true if it succeed, false otherwise
 *
 *  @see ui_menu_deactivate()
 */
bool ui_menu_activate(ui_menu *menu);

/**
 *  @brief This is deactivating the ui_menu.
 *
 *  @note It makes ui_menu state as hide.
 *
 *  @param menu The ui_menu object
 *
 *  @return true if it succeed, false otherwise
 *
 *  @see ui_menu_activate()
 */
bool ui_menu_deactivate(ui_menu *menu);

/**
 *  @brief Return the active status of ui_menu.
 *
 *  @param menu The ui_menu object
 *
 *  @return @c true if ui_menu is activated, @c false otherwise
 *
 *  @see ui_menu_activate()
 *  @see ui_menu_deactivate()
 */
bool ui_menu_activated_get(ui_menu *menu);

//FIXME: is it really need?
/**
 *  @brief Get a base window of viewmgr.
 *
 *  @param menu The ui_menu object
 *
 *  @return viewmgr's window object
 */
Evas_Object *ui_menu_base_get(ui_menu *menu);

/**
 *  @brief Get current ui_menu's degree.
 *
 *  @param menu The ui_menu object
 *
 *  @return Current rotation degree, -1 if it fails to get degree information
 */
int ui_menu_degree_get(ui_menu *menu);

/**
 *  @brief Return a view which is matched with the ui_menu.
 *
 *  @param menu The ui_menu object
 *
 *  @return The view which is matched with ui_menu
 */
ui_view *ui_menu_view_get(ui_menu *menu);

#ifdef __cplusplus
}
#endif

#endif /* _UI_MENU_CAPI_H_ */
