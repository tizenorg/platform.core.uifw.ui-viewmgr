#include "ui_viewmanager_private.h"
#include "ui_controller_capi.h"

using namespace efl_viewmgr;

extern "C" {
	ui_viewmgr* ui_viewmgr_add(const char *pkg)
	{
		return new ui_basic_viewmgr(pkg);
	}

	bool ui_viewmgr_activate(ui_viewmgr *viewmgr)
	{
		return viewmgr->activate();
	}

	bool ui_viewmgr_deactivate(ui_viewmgr *viewmgr)
	{
		return viewmgr->deactivate();
	}

	ui_basic_view* ui_view_add(ui_controller *controller, const char *name)
	{
		ui_capi_controller *controller_dummy = new ui_capi_controller();
		return new ui_basic_view(controller_dummy, name);
	}

	Evas_Object* ui_view_base_layout_get(ui_view *view)
	{
		return view->get_base();
	}

	Evas_Object* ui_view_content_set(ui_view *view, Evas_Object *content,
			                         const char *title, const char *subtitle,
									 Evas_Object *title_left_btn, Evas_Object *title_right_btn)
	{
		return dynamic_cast<ui_basic_view *>(view)->set_content(content, title, subtitle, title_left_btn, title_right_btn);
	}

	ui_view* ui_viewmgr_view_push(ui_viewmgr *viewmgr, ui_view *view)
	{
		return viewmgr->push_view(view);
	}

	bool ui_viewmgr_view_pop(ui_viewmgr *viewmgr)
	{
		return viewmgr->pop_view();
	}

	void ui_view_event_callback_add(ui_view *view, const char *event, ui_view_event_cb func, const void *data)
	{
		ui_view_event_callback *cb;
		if (!event) return;
		if (!func) return;

		cb = static_cast<ui_view_event_callback *>(calloc(1,sizeof(ui_view_event_callback)));
		cb->view = view;
		cb->event = eina_stringshare_add(event);
		cb->func = func;
		cb->func_data = (void *)data;
		callback_list.push_back(cb);
	}
}
