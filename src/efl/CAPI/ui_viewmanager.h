#ifndef UI_VIEWMGR_CAPI_H
#define UI_VIEWMGR_CAPI_H

#include "../mobile/ui_viewmanager.h"

using namespace efl_viewmgr;

typedef Eina_Bool (*ui_view_event_cb)(void *data, ui_view *obj, void *event_info);

#ifdef __cplusplus
extern "C" {
#endif
	ui_viewmgr* ui_viewmgr_add(const char *pkg);
	bool ui_viewmgr_activate(ui_viewmgr *viewmgr);
	bool ui_viewmgr_deactivate(ui_viewmgr *viewmgr);
	ui_basic_view* ui_view_add(ui_controller *controller, const char *name);
	Evas_Object* ui_view_base_layout_get(ui_view *view);
	Evas_Object* ui_view_content_set(ui_view *view, Evas_Object *content,
			                         const char *title, const char *subtitle,
									 Evas_Object *title_left_btn, Evas_Object *title_right_btn);
	ui_view* ui_viewmgr_view_push(ui_viewmgr *viewmgr, ui_view *view);
	bool ui_viewmgr_view_pop(ui_viewmgr *viewmgr);
	void ui_view_event_callback_add(ui_view *view, const char *event, ui_view_event_cb func, const void *data);
#ifdef __cplusplus
}
#endif

#endif /* UI_VIEWMGR_CAPI_H */
