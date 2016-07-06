#include "../../../../include/efl/mobile/c/_ui_private.h"
#include "../../../../include/efl/mobile/c/ui_viewmgr.h"

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

EAPI ui_view *ui_viewmgr_push_view(ui_viewmgr *viewmgr, ui_view *view)
{
	if (!viewmgr || !view)
	{
		LOGE("Invalid Parameter viewmgr = %p, view = %p", viewmgr, view);
		return NULL;
	}

	return dynamic_cast<ui_view *>(viewmgr->pushView(view));
}

EAPI bool ui_viewmgr_push_view_insert_before(ui_viewmgr *viewmgr, ui_view *view, ui_view *before)
{
	if (!viewmgr || !view)
	{
		LOGE("Invalid Parameter viewmgr = %p, view = %p, before = %p", viewmgr, view, before);
		return false;
	}

	return viewmgr->insertViewBefore(view, before);
}

EAPI bool ui_viewmgr_push_view_insert_after(ui_viewmgr *viewmgr, ui_view *view, ui_view *after)
{
	if (!viewmgr || !view)
	{
		LOGE("Invalid Parameter viewmgr = %p, view = %p, after = %p", viewmgr, view, after);
		return false;
	}

	return viewmgr->insertViewAfter(view, after);
}

EAPI bool ui_viewmgr_pop_view(ui_viewmgr *viewmgr)
{
	if (!validate_viewmgr(viewmgr)) return false;
	return viewmgr->popView();
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

EAPI Elm_Win *ui_viewmgr_get_window(ui_viewmgr *viewmgr)
{
	if (!validate_viewmgr(viewmgr)) return NULL;
	return viewmgr->getWindow();
}

EAPI ui_view *ui_viewmgr_get_last_view(ui_viewmgr *viewmgr)
{
	if (!validate_viewmgr(viewmgr)) return NULL;
	return dynamic_cast<ui_view *>(viewmgr->getLastView());
}

EAPI ui_view *ui_viewmgr_get_view_by_idx(ui_viewmgr *viewmgr, int idx)
{
	if (!validate_viewmgr(viewmgr)) return NULL;
	return dynamic_cast<ui_view *>(viewmgr->getView(idx));
}

EAPI ui_view *ui_viewmgr_get_view_by_name(ui_viewmgr *viewmgr, const char *name)
{
	if (!validate_viewmgr(viewmgr)) return NULL;
	return dynamic_cast<ui_view *>(viewmgr->getView(name));
}

EAPI Evas_Object *ui_viewmgr_get_base(ui_viewmgr *viewmgr)
{
	if (!validate_viewmgr(viewmgr)) return NULL;
	return viewmgr->getBase();
}

EAPI int ui_viewmgr_get_view_index(ui_viewmgr *viewmgr, const ui_view *view)
{
	if (!viewmgr || !view)
	{
		LOGE("Invalid Parameter viewmgr = %p, view = %p", viewmgr, view);
		return -1;
	}

	return viewmgr->getViewIndex(view);
}

EAPI int ui_viewmgr_get_view_count(ui_viewmgr *viewmgr)
{
	if (!validate_viewmgr(viewmgr)) return -1;

	return viewmgr->getViewCount();
}

EAPI bool ui_viewmgr_get_soft_key_need(ui_viewmgr *viewmgr)
{
	if (!validate_viewmgr(viewmgr)) return false;
	return viewmgr->needSoftKey();
}

EAPI ui_viewmgr *ui_viewmgr_get_viewmgr()
{
	return UI_VIEWMGR;
}
