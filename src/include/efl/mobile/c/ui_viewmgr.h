#ifndef _UI_VIEWMGR_CAPI_H_
#define _UI_VIEWMGR_CAPI_H_

#ifdef __cplusplus
extern "C" {
#endif

ui_view *ui_viewmgr_view_push(ui_viewmgr *viewmgr, ui_view *view);
bool ui_viewmgr_view_push_insert_before(ui_viewmgr *viewmgr, ui_view *view, ui_view *before);
bool ui_viewmgr_view_push_insert_after(ui_viewmgr *viewmgr, ui_view *view, ui_view *after);
bool ui_viewmgr_view_pop(ui_viewmgr *viewmgr);
bool ui_viewmgr_activate(ui_viewmgr *viewmgr);
bool ui_viewmgr_deactivate(ui_viewmgr *viewmgr);
Elm_Win *ui_viewmgr_window_get(ui_viewmgr *viewmgr);
ui_view *ui_viewmgr_last_view_get(ui_viewmgr *viewmgr);
ui_view *ui_viewmgr_view_get(ui_viewmgr *viewmgr, int idx);
//ui_view *ui_viewmgr_view_get_by_id(ui_viewmgr *viewmgr, const char *id);
Evas_Object *ui_viewmgr_base_get(ui_viewmgr *viewmgr);
int ui_viewmgr_view_count_get(ui_viewmgr *viewmgr);
bool ui_viewmgr_soft_key_need_get(ui_viewmgr *viewmgr);
ui_viewmgr *ui_viewmgr_viewmgr_get();

#define UI_VIEWMGR_DEACTIVATE() (ui_viewmgr_deactivate(ui_viewmgr_viewmgr_get()))
#define UI_VIEWMGR_VIEW_PUSH(X) (ui_viewmgr_view_push(ui_viewmgr_viewmgr_get(), (X)))
#define UI_VIEWMGR_VIEW_POP() (ui_viewmgr_view_pop(ui_viewmgr_viewmgr_get()))

#ifdef __cplusplus
}
#endif

#endif /* _UI_VIEWMGR_CAPI_H_ */
