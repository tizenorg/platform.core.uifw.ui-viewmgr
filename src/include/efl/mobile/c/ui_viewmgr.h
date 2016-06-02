#ifndef _UI_VIEWMGR_C_H_
#define _UI_VIEWMGR_C_H_

using namespace efl_viewmananger;

#ifdef __cplusplus
extern "C" {
#endif
	ui_view *ui_viewmgr_view_push(ui_viewmgr *viewmgr, ui_view *view);
	bool ui_viewmgr_view_push_insert_before(ui_viewmgr *viewmgr, ui_view *view, ui_view *before);
	bool ui_viewmgr_view_push_insert_after(ui_viewmgr *viewmgr, ui_view *view, ui_view *after);
	bool ui_viewmgr_view_pop(ui_viewmgr *viewmgr);

	bool ui_viewmgr_activate(ui_viewmgr *viewmgr);
	bool ui_viewmgr_deactivate(ui_viewmgr *viewmgr);

	Elm_Win ui_viewmgr_window_get(ui_viewmgr *viewmgr);

	Elm_Conformant ui_viewmgr_conformant_get(ui_viewmgr *viewmgr);

	ui_view *ui_viewmgr_last_view_get(ui_viewmgr *viewmgr);

	ui_view *ui_viewmgr_view_get(ui_viewmgr *viewmgr, int idx);

	Evas_Object *ui_viewmgr_base_get(ui_viewmgr *viewmgr);

	int ui_viewmgr_view_count_get(ui_viewmgr *viewmgr);

	bool ui_viewmgr_soft_key_need_get(ui_viewmgr *viewmgr);

	ui_viewmgr *ui_viewmgr_viewmgr_get();

	#define UI_VIEWMGR_DEACTIVATE() (ui_viewmgr_deactivate(ui_app_viewmgr_get()))
	#define UI_VIEWMGR_VIEW_PUSH(x) (ui_viewmgr_view_push(ui_app_viewmgr_get(), x))
	#define UI_VIEWMGR_VIEW_POP()   (ui_viewmgr_view_pop(ui_app_viewmgr_get()))
#ifdef __cplusplus
}
#endif

#endif /* _UI_VIEWMGR_C_H_ */
