#include "../../../../include/efl/mobile/c/_ui_private.h"
#include "../../../../include/efl/mobile/c/ui_viewmgr.h"

using namespace efl_viewmanager;

struct ui_viewmgr_s
{
	ui_viewmgr *p;
};

static bool validate_viewmgr(ui_viewmgr *viewmgr)
{
	if (!viewmgr)
	{
		LOGE("Invalid ui_viewmgr = NULL");
		return false;
	}
	return true;
}


EAPI ui_view *ui_viewmgr_view_push(ui_viewmgr *viewmgr, ui_view *view)
{
	if (!viewmgr || !view)
	{
		LOGE("Invalid Parameter viewmgr = %p, view = %p", viewmgr, view);
		return NULL;
	}

	return dynamic_cast<ui_view *>(viewmgr->push_view(view));
}

EAPI bool ui_viewmgr_view_insert_before(ui_viewmgr *viewmgr, ui_view *view, ui_view *before)
{
	if (!viewmgr || !view)
	{
		LOGE("Invalid Parameter viewmgr = %p, view = %p, before = %p", viewmgr, view, before);
		return false;
	}

	return viewmgr->insert_view_before(view, before);
}

EAPI bool ui_viewmgr_view_insert_after(ui_viewmgr *viewmgr, ui_view *view, ui_view *after)
{
	if (!viewmgr || !view)
	{
		LOGE("Invalid Parameter viewmgr = %p, view = %p, after = %p", viewmgr, view, after);
		return false;
	}

	return viewmgr->insert_view_after(view, after);
}

EAPI bool ui_viewmgr_view_pop(ui_viewmgr *viewmgr)
{
	if (!validate_viewmgr(viewmgr)) return false;
	return viewmgr->pop_view();
}

EAPI bool ui_viewmgr_activate(ui_viewmgr *viewmgr)
{
	if (!validate_viewmgr(viewmgr)) return false;
	return viewmgr->activate();
}

EAPI bool ui_viewmgr_deactivate(ui_viewmgr *viewmgr)
{
	if (!validate_viewmgr(viewmgr)) return false;
	return viewmgr->deactivate();
}

EAPI Elm_Win *ui_viewmgr_window_get(ui_viewmgr *viewmgr)
{
	if (!validate_viewmgr(viewmgr)) return NULL;
	return viewmgr->get_window();
}

EAPI ui_view *ui_viewmgr_last_view_get(ui_viewmgr *viewmgr)
{
	if (!validate_viewmgr(viewmgr)) return NULL;
	return dynamic_cast<ui_view *>(viewmgr->get_last_view());
}

EAPI ui_view *ui_viewmgr_view_get(ui_viewmgr *viewmgr, int idx)
{
	if (!validate_viewmgr(viewmgr)) return NULL;
	return dynamic_cast<ui_view *>(viewmgr->get_view(idx));
}

EAPI Evas_Object *ui_viewmgr_base_get(ui_viewmgr *viewmgr)
{
	if (!validate_viewmgr(viewmgr)) return NULL;
	return viewmgr->get_base();
}

EAPI int ui_viewmgr_view_index_get(ui_viewmgr *viewmgr, const ui_view *view)
{
	if (!viewmgr || !view)
	{
		LOGE("Invalid Parameter viewmgr = %p, view = %p", viewmgr, view);
		return -1;
	}

	return viewmgr->get_view_index(view);
}


EAPI int ui_viewmgr_view_count_get(ui_viewmgr *viewmgr)
{
	if (!validate_viewmgr(viewmgr)) return -1;

	return viewmgr->get_view_count();
}

EAPI bool ui_viewmgr_soft_key_need_get(ui_viewmgr *viewmgr)
{
	if (!validate_viewmgr(viewmgr)) return false;
	return viewmgr->need_soft_key();
}

EAPI ui_viewmgr *ui_viewmgr_viewmgr_get()
{
	return UI_VIEWMGR;
}
