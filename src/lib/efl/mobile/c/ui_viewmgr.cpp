#include "../../../../include/efl/mobile/c/ui_mobile_viewmanager.h"
#include "../../../../include/efl/mobile/c/ui_viewmgr.h"

using namespace efl_viewmanager;

extern "C" {
	ui_view *ui_viewmgr_view_push(ui_viewmgr *viewmgr, ui_view *view)
	{
		if (!viewmgr || !view)
		{
			LOGE("Invalid Parameter viewmgr = %p, view = %p", viewmgr, view);
			return NULL;
		}

		return static_cast<ui_view *>(viewmgr->push_view(view));
	}

	bool ui_viewmgr_view_push_insert_before(ui_viewmgr *viewmgr, ui_view *view, ui_view *before)
	{
		if (!viewmgr || !view || !before)
		{
			LOGE("Invalid Parameter viewmgr = %p, view = %p, before = %p", viewmgr, view, before);
			return -1;
		}

		return viewmgr->insert_view_before(view, before);
	}

	bool ui_viewmgr_view_push_insert_after(ui_viewmgr *viewmgr, ui_view *view, ui_view *after)
	{
		if (!viewmgr || !view || !after)
		{
			LOGE("Invalid Parameter viewmgr = %p, view = %p, after = %p", viewmgr, view, after);
			return -1;
		}

		return viewmgr->insert_view_after(view, after);
	}

	bool ui_viewmgr_view_pop(ui_viewmgr *viewmgr)
	{
		if (!viewmgr)
		{
			LOGE("Invalid Viewmgr");
			return -1;
		}

		return viewmgr->pop_view();
	}

	bool ui_viewmgr_activate(ui_viewmgr *viewmgr)
	{
		if (!viewmgr)
		{
			LOGE("Invalid Viewmgr");
			return -1;
		}

		return viewmgr->activate();
	}

	bool ui_viewmgr_deactivate(ui_viewmgr *viewmgr)
	{
		if (!viewmgr)
		{
			LOGE("Invalid Viewmgr");
			return -1;
		}

		return viewmgr->deactivate();
	}

	Elm_Win *ui_viewmgr_window_get(ui_viewmgr *viewmgr)
	{
		if (!viewmgr)
		{
			LOGE("Invalid Viewmgr");
			return NULL;
		}

		return viewmgr->get_window();
	}

	Elm_Conformant *ui_viewmgr_conformant_get(ui_viewmgr *viewmgr)
	{
		if (!viewmgr)
		{
			LOGE("Invalid Viewmgr");
			return NULL;
		}

		return viewmgr->get_conformant();
	}

	ui_view *ui_viewmgr_last_view_get(ui_viewmgr *viewmgr)
	{
		if (!viewmgr)
		{
			LOGE("Invalid Viewmgr");
			return NULL;
		}

		return static_cast<ui_view *>(viewmgr->get_last_view());
	}

	ui_view *ui_viewmgr_view_get(ui_viewmgr *viewmgr, int idx)
	{
		if (!viewmgr)
		{
			LOGE("Invalid Viewmgr");
			return NULL;
		}

		return static_cast<ui_view *>(viewmgr->get_view(idx));
	}

	Evas_Object *ui_viewmgr_base_get(ui_viewmgr *viewmgr)
	{
		if (!viewmgr)
		{
			LOGE("Invalid Viewmgr");
			return NULL;
		}

		return viewmgr->get_base();
	}

	int ui_viewmgr_view_count_get(ui_viewmgr *viewmgr)
	{
		if (!viewmgr)
		{
			LOGE("Invalid Viewmgr");
			return -1;
		}

		return viewmgr->get_view_count();
	}

	bool ui_viewmgr_soft_key_need_get(ui_viewmgr *viewmgr)
	{
		if (!viewmgr)
		{
			LOGE("Invalid Viewmgr");
			return false;
		}

		return viewmgr->need_soft_key();
	}

	ui_viewmgr *ui_viewmgr_viewmgr_get()
	{
		return UI_VIEWMGR;
	}
}
