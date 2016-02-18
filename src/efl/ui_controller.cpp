#include "efl_viewmgr.h"

using namespace efl;

ui_view *
ui_controller::get_view()
{
	ui_view_base *view = ui_controller_base::get_view();
	if (!view) return NULL;
	return dynamic_cast<ui_view *>(view);
}
