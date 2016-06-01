#ifndef _UI_MENU_C_H_
#define _UI_MENU_C_H_

namespace efl_viewmananger
{

#ifdef __cplusplus
extern "C" {
#endif
	bool ui_menu_content_set(ui_menu *menu, Elm_Ctxpopup *ctxpopup);
	Elm_Ctxpopup *ui_menu_content_unset(ui_menu *menu);
	bool ui_menu_activate(ui_menu *menu);
	bool ui_menu_deactivate(ui_menu *menu);
	bool ui_menu_activate_get(ui_menu *menu);
	//Is it needed?
	Evas_Object *ui_menu_base_get(ui_menu *menu);
	int ui_menu_degree_get(ui_menu *menu);
	Elm_Ctxpopup ui_menu_content_get(ui_menu *menu);
	ui_view *ui_menu_view_get(ui_menu *menu);
#ifdef __cplusplus
}
#endif
}

#endif /* _UI_MENU_C_H_ */
