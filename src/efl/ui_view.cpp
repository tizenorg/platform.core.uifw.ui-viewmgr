#include "efl_viewmgr.h"

using namespace efl;

ui_view::ui_view(ui_controller *controller, const char *name)
		: ui_view_base(controller, name)
{
}

ui_view::~ui_view()
{
}

Evas_Object *ui_view::set_content(Evas_Object *content)
{
	T pcontent = ui_view_base::set_content(CONVERT_TO_T(content));
	return static_cast<Evas_Object *>(pcontent);
}

Evas_Object *ui_view::get_base()
{
	ui_viewmgr *viewmgr = dynamic_cast<ui_viewmgr *>(ui_view_base::get_viewmgr());
	if (!viewmgr)
	{
		return NULL;
	}
	return viewmgr->get_base();
}

void ui_view::load()
{
	ui_view_base::load();
}

void ui_view::unload()
{
	ui_view_base::unload();
}

void ui_view::unload_content()
{
	Evas_Object *pcontent = this->set_content(NULL);
	if (pcontent) evas_object_del(pcontent);
}
