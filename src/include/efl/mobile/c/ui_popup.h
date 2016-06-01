#ifndef _UI_POPUP_C_H_
#define _UI_POPUP_C_H_

namespace efl_viewmananger
{

#ifdef __cplusplus
extern "C" {
#endif
	ui_popup *ui_popup_create(ui_view *view);
	bool ui_popup_content_set(ui_popup *popup, Elm_Popup *elm_popup);
	Elm_Popup *ui_popup_content_unset(ui_popup *popup);
	bool ui_popup_activate(ui_popup *popup);
	bool ui_popup_deactivate(ui_popup *popup);
	void ui_popup_del(ui_popup *popup);
	bool ui_popup_activate_get(ui_popup *popup);
	//Is it needed?
	Evas_Object *ui_popup_base_get(ui_popup *popup);
	int ui_popup_degree_get(ui_popup *popup);
	Elm_Popup ui_popup_content_get(ui_popup *popup);
	ui_view *ui_popup_view_get(ui_popup *popup);
#ifdef __cplusplus
}
#endif

}
#endif /* _UI_POPUP_C_H_ */
