#ifndef _UI_POPUP_C_H_
#define _UI_POPUP_C_H_

using namespace efl_viewmananger;

#ifdef __cplusplus
extern "C" {
#endif
	bool ui_popup_content_set(ui_popup *popup, Elm_Popup *popup);
	bool ui_popup_activate(ui_popup *popup);
	void ui_popup_del(ui_popup *popup);
#ifdef __cplusplus
}
#endif

#endif /* _UI_POPUP_C_H_ */
