#include "ui_view.h"
#include "ui_controller.h"
#include "ui_viewmgr.h"

using namespace efl;

ui_view::ui_view(ui_controller *controller) :
		ui_view_base(controller)
{
}

ui_view::~ui_view()
{
}

Evas_Object *
ui_view::set_content(Evas_Object *content)
{
	T pcontent = ui_view_base::set_content(CONVERT_TO_T(content));
	return static_cast<Evas_Object *>(pcontent);
}

Evas_Object *
ui_view::get_parent()
{
	ui_viewmgr *viewmgr = dynamic_cast<ui_viewmgr *>(ui_view_base::get_viewmgr());
	if (!viewmgr)
		return NULL;
	return viewmgr->get_base_layout();
}

void ui_view::load()
{
	ui_view_base::load();
}
