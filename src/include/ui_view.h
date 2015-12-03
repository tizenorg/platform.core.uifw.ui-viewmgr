/**
* @brief, A view is responsible for showing the content on the screen
* How it will be shown on the screen will be decided by the style set on the view.
* Its the view manager's resposibility to show
* the view on screen and to manage the owenership of the view.
* View manager emit the signals corresponding to the state change of the view.
* View takes the explicit ownersip of the content .
* If user wants to take the ownership back it has to do that with content_unset api.
* list of signal emmmited from view
* @li @c "view,load" - When View is about to be shown and the content is null
*
* @li @c "view,unload" - When View is about to destroy.
*
* @li @c "view,appear,start" - When View is about to show on screen, before show transition start.
*
* @li @c "view,appear,finish" - When View is fully shown on screen, after show transition finished.
*
* @li @c "view,disappear,start" - When View is about to disappear from screen, before hide transition start.
*
* @li @c "view,disappear,finish" - When View is fully hidden from screen, after hide transition finish.
*
* @li @c "key,back" - When back key is pressed .
* @li @c "key,more" - When more key is pressed.
*
* List of styel provided in the view , the behaviour will be decided by the ui-viewmgr layout file.
* @li @c "default" - The default transition for the system , and this will be applied if nothing is set.
* @li @c "noanimation" - If the user don't want any transition while showing a view.
* @li @c "slidein" - If the new view need to slidein to the screen when shown.
* @li @c "popup" - If the new view need to shown as a popup on the screen.
*/

#ifndef _UI_VIEW_H
#define _UI_VIEW_H

#include <Elementary.h>

typedef struct _ui_view     ui_view;

/** <View event callback function signature */
typedef Eina_Bool (*ui_view_event_cb)(void *data, ui_view *obj, void *event_info);

/**
* @brief Create a view using content. 
* @param content , any Evas_Object that needs to be shown as a view on screen.
* @return New view object on success else @c NULL.
*/

EAPI ui_view *ui_view_add(Evas_Object *content);

/**
* @brief Deletes a view object. 
* It also deletes the associated content with it.
* User can take the content ownership by calling content_unset api.
*/
EAPI void ui_view_del(ui_view* view);

/**
* @brief To set the content of a view 
* Deletes the previous content object if any and 
* adds the new object as the content object of the view .
*/
EAPI Eina_Bool ui_view_content_set(ui_view *view, Evas_Object *content);

/**
* @brief To unset the content of a view 
* It returns the content object it holds and sets the content object to NULL. 
* @return The content Object else @c NULL
*/
EAPI Evas_Object *ui_view_content_unset(ui_view *view);

/**
* @brief To get the content object from the view 
* @return returns the Content object if set , else NULL.
*/
EAPI Evas_Object *ui_view_content_get(ui_view *view);

/** 
* @brief Set the style that will be used by view manager 
* while showing and hiding the view. The style includes the 
* presentation as well as transition property. These styles are
* defined in the ui-viewmgr.edc file and can be customised.
* If no style is set view manger will use a default style for this view.
*
* @param style, the style to be used by view manager while showing this view.
*/
EAPI void ui_view_style_set(ui_view* view, const char *style);

/**
* @brief To get the current style applied to this view. 
* @return returns the style name set on this view else return the defult style.
*/
EAPI const char *ui_view_style_get(ui_view* view);

/**
* @brief Add a callback function to the event specified by
* @p event on the view @p view
*
* @param obj view 
* @param event the event's name string
* @param func the callback function
* @param data user data to be passed to the callback function
*/
EAPI void ui_view_event_callback_add(ui_view *view, const char *event, ui_view_event_cb func, const void *data);

/**
 * Delete (unregister) a callback function from the event
 * specified by @p event on the view @p view.
 *
 * @param view a view object
 * @param event the event's name string
 * @param func the callback function
 * @return the data pointer
 */
EAPI void *ui_view_event_callback_del(ui_view *view, const char *event, ui_view_event_cb func);


#endif //_UI_VIEW_H
