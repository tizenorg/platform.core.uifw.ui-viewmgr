
/**
* @defgroup ViewManager ViewManager
* @brief ViewManager manages the view stack
* for applications.
* Viewmanager takes the explicit wonership of the view it manages.
* It is responsible for the View state management and triggers the state change for the view.
* It manages the view transition and presentation by using edc layout file. see @View more details.
* It internally creates the conformant , if user needs to customise the conformant either it can
* add a configuration file to do so , or by getting the conformant and updating its property.
*/

#ifndef _UI_VIEWMGR_H
#define _UI_VIEWMGR_H

#include <Elementary.h>
#include <ui_view.h>

typedef struct _ui_viewmgr ui_viewmgr;

/**
* @brief Add a new view manager to window
* @param window , window object
* @return New ui_viewmgr object on success or @c NULL on failure.
*/

EAPI ui_viewmgr *ui_viewmgr_add(Evas_Object *window);

/**
* @brief Delete the view manager
* ViewManager deletes itself when the associated window gets deleted.
*/
EAPI void ui_viewmgr_del(ui_viewmgr *view_mgr);

/**
* @brief Push  a view into view manager's view stack
* View Push operation can be customised by setting the style on View.
* @param view_mgr , view maanger object
* @param view , view object to be pushed
* @return EINA_TRUE on sucsess else EINA_FALSE.
*/
EAPI Eina_Bool ui_viewmgr_view_push(ui_viewmgr *view_mgr, ui_view *view);

/**
* @brief Insert  a view into view manager's view stack with relative to a view
* @param view_mgr , view maanger object
* @param view , view object to be pushed
* @param before , the view before which the new view will be placed in view stack.
* @return EINA_TRUE on sucsess else EINA_FALSE.
*/
EAPI Eina_Bool ui_viewmgr_view_insert_before(ui_viewmgr *view_mgr, ui_view *before, ui_view *view);

/**
* @brief Insert  a view into view manager's view stack with relative to a view
* @param view_mgr , view maanger object
* @param view , view object to be pushed
* @param after , the relative view after which the new view will be placed in view stack.
* @return EINA_TRUE on sucsess else EINA_FALSE.
*/
EAPI Eina_Bool ui_viewmgr_view_insert_after(ui_viewmgr *view_mgr, ui_view *after, ui_view *view);

/**
* @brief Remove the top view from the stack.
* If there is more view on the stack it makes the below view as the top view of the stack
* @ret returns EINA_TRUE if the operation is a success , else EINA_FALSE
*/

EAPI Eina_Bool ui_viewmgr_view_pop(ui_viewmgr *view_mgr);

/**
* @brief Pop to a view on the stack.
* On the process it removes all the view in beteen the top view and the view it pops to.
* It will only do the view transition effect between top view and the view it pops to.
* @param view , view object on the stack to be poped to
* @ret returns EINA_TRUE if the operation is a success , else EINA_FALSE
*/
EAPI Eina_Bool ui_viewmgr_view_pop_to(ui_viewmgr *view_mgr, ui_view *to_view);


/**
* @brief Promote a view to the top of the stack.
* @param view , view object that needs to be brought on th top of the stack
* This operation will happen if the view is present on the stack and not on the top.
* @ret returns EINA_TRUE if the operation is a success , else EINA_FALSE
*/
EAPI Eina_Bool ui_viewmgr_view_promote(ui_viewmgr *view_mgr, ui_view *view);

/**
* @brief Get the top view from the view manager
* @ret returns the top view of the view stack , else returns NULL
*/
EAPI ui_view *ui_viewmgr_top_view_get(const ui_viewmgr *view_mgr);

/**
* @brief Get the conformant created by view manager
* @ret returns the conformant that internally created by view manager.
*/
EAPI Evas_Object *ui_viewmgr_conformant_get(const ui_viewmgr *view_mgr);

#endif //_UI_VIEWMGR_H
