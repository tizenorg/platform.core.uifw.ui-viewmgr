#include "../../../../include/efl/mobile/c/ui_mobile_viewmanager.h"
#include "../../../../include/efl/mobile/c/ui_viewmgr.h"

using namespace efl_viewmanager;

extern "C" {
	ui_view *ui_viewmgr_view_push(ui_viewmgr *viewmgr, ui_view *view)
	{
		return static_cast<ui_view *>(viewmgr->push_view(view));
	}

	bool ui_viewmgr_view_pop(ui_viewmgr *viewmgr)
	{
		return viewmgr->pop_view();
	}

	bool ui_viewmgr_deactivate(ui_viewmgr *viewmgr)
	{
		return viewmgr->deactivate();
	}
}
