#include "../../../../include/efl/mobile/c/ui_mobile_viewmanager.h"
#include "../../../../include/efl/mobile/c/ui_viewmgr.h"

using namespace efl_viewmanager;

extern "C" {
	ui_view *ui_viewmgr_view_push_insert_before(ui_viewmgr *viewmgr, ui_view *view, ui_view *before)
	{
		//TODO
		return NULL;
	}

	ui_view *ui_viewmgr_view_push_insert_after(ui_viewmgr *viewmgr, ui_view *view, ui_view *after)
	{
		//TODO
		return NULL;
	}

	ui_view *ui_viewmgr_view_push(ui_viewmgr *viewmgr, ui_view *view)
	{
		return static_cast<ui_view *>(viewmgr->push_view(view));
	}

	bool ui_viewmgr_view_pop(ui_viewmgr *viewmgr)
	{
		return viewmgr->pop_view();
	}

	bool ui_viewmgr_activate(ui_viewmgr *viewmgr)
	{
		//TODO
		return 1;
	}

	bool ui_viewmgr_deactivate(ui_viewmgr *viewmgr)
	{
		return viewmgr->deactivate();
	}

	Elm_Win ui_viewmgr_window_get(ui_viewmgr *viewmgr)
	{
		//TODO
		return NULL;
	}

	Elm_Conformant ui_viewmgr_conformant_get(ui_viewmgr *viewmgr)
	{
		//TODO
		return NULL;
	}

	ui_view *ui_viewmgr_last_view_get(ui_viewmgr *viewmgr)
	{
		//TODO
		return NULL;
	}

	ui_view *ui_viewmgr_view_get(ui_viewmgr *viewmgr, int idx)
	{
		//TODO
		return NULL;
	}

	Evas_Object *ui_viewmgr_base_get(ui_viewmgr *viewmgr)
	{
		//TODO
		return NULL;
	}

	unsigned int ui_viewmgr_view_count_get(ui_viewmgr *viewmgr)
	{
		//TODO
		return 1;
	}

	bool ui_viewmgr_soft_key_need_get(ui_viewmgr *viewmgr)
	{
		//TODO
		return 1;
	}

	ui_viewmgr *ui_viewmgr_viewmgr_get()
	{
		//TODO
		return NULL;
	}
}
