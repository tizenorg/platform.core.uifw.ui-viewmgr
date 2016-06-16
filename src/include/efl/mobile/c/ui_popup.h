#ifndef _UI_POPUP_CAPI_H_
#define _UI_POPUP_CAPI_H_

#ifdef __cplusplus
extern "C" {
#endif

/**
 *  @brief This is a constructor for initializing this ui_popup.
 *
 *  @param view The view object
 *
 *  @return The ui_popup object
 *
 *  @see ui_popup_destroy()
 */
ui_popup *ui_popup_create(ui_view *view);

/**
 *  @brief This is a ui_popup destructor.
 *
 *  @param popup The ui_popup object
 *
 *  @seee ui_popup_create()
 */
void ui_popup_destroy(ui_popup *popup);

/**
 *  @brief This is for replacing or setting a content of the ui_popup.
 *
 *  @popup popup The ui_popup object
 *
 *  @param elm_popup elm_popup object. It allows @c NULL for canceling the previous content.
 *
 *  @return true if it succeed, false otherwise
 *
 *  @see ui_popup_content_get()
 */
bool ui_popup_content_set(ui_popup *popup, Elm_Popup *content);

/**
 *  @brief Return a content object of ui_popup.
 *
 *  @param popup The ui_popup object
 *
 *  @return content of ui_popup object
 *
 *  @see ui_popup_content_set()
 */
Elm_Popup *ui_popup_content_get(ui_popup *popup);

/**
 *  @brief This is for unsetting a content of the ui_popup.
 *
 *  @param popup The ui_popup object
 *
 *  @return A previous content. If it wasn't, return value will be @c NULL
 *
 *  @see ui_popup_content_set()
 *  @see ui_popup_content_get()
 */
Elm_Popup *ui_popup_content_unset(ui_popup *popup);

/**
 *  @brief This is activating the ui_popup.
 *
 *  @param popup The popup object
 *
 *  @return true if it succeed, false otherwise
 *
 *  @see ui_popup_deactivate()
 */
bool ui_popup_activate(ui_popup *popup);

/**
 *  @brief This is deactivating the ui_popup.
 *
 *  @param popup The ui_popup object
 *
 *  @return true if it succeed, false otherwise
 *
 *  @see ui_popup_activate()
 */
bool ui_popup_deactivate(ui_popup *popup);

/**
 *  @brief Return the active status of ui_popup.
 *
 *  @param popup The ui_popup object
 *
 *  @return @c true if ui_popup is activated, @c false otherwise
 *
 *  @see ui_popup_activate()
 *  @see ui_popup_deactivate()
 */
bool ui_popup_activated_get(ui_popup *popup);

//FIXME: is it really need?
/**
 *  @brief Get a base window of viewmgr.
 *
 *  @param popup The ui_popup object
 *
 *  @return viewmgr's window object
 */
Evas_Object *ui_popup_base_get(ui_popup *popup);

/**
 *  @brief Get current ui_popup's degree.
 *
 *  @param popup The ui_popup object
 *
 *  @return Current rotation degree, -1 if it fails to get degree information
 */
int ui_popup_degree_get(ui_popup *popup);

/**
 *  @brief Return a view which is matched with the ui_popup.
 *
 *  @param popup The ui_popup object
 *
 *  @return The view which is matched with ui_popup.
 */
ui_view *ui_popup_view_get(ui_popup *popup);

#ifdef __cplusplus
}
#endif

#endif /* _UI_POPUP_CAPI_H_ */
