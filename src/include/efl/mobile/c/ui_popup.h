#ifndef _UI_POPUP_C_H_
#define _UI_POPUP_C_H_

namespace efl_viewmananger
{

#ifdef __cplusplus
extern "C" {
#endif
	ui_popup *ui_popup_create(ui_view *view);
	bool ui_popup_content_set(ui_popup *popup, Elm_Popup *elm_popup);
	bool ui_popup_activate(ui_popup *popup);
	void ui_popup_del(ui_popup *popup);
#ifdef __cplusplus
}
#endif

}
#endif /* _UI_POPUP_C_H_ */
