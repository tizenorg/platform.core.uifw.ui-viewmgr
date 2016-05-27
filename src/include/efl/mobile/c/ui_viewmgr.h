#ifndef _UI_VIEWMGR_C_H_
#define _UI_VIEWMGR_C_H_

using namespace efl_viewmananger;

#ifdef __cplusplus
extern "C" {
#endif
	ui_view *ui_viewmgr_view_push(ui_viewmgr *viewmgr, ui_view *view);
	bool ui_viewmgr_view_pop(ui_viewmgr *viewmgr);
	bool ui_viewmgr_deactivate(ui_viewmgr *viewmgr);

	//TODO
	#define UI_VIEWMGR_DEACTIVATE() (ui_viewmgr_deactivate(ui_app_viewmgr_get()))
	#define UI_VIEWMGR_VIEW_PUSH(x) (ui_viewmgr_view_push(ui_app_viewmgr_get(), x))
	#define UI_VIEWMGR_VIEW_POP()   (ui_viewmgr_view_pop(ui_app_viewmgr_get()))
#ifdef __cplusplus
}
#endif

#endif /* _UI_VIEWMGR_C_H_ */
