#include <dlog.h>
#include "ui_basic_view.h"
#include "ui_viewmgr.h"

using namespace efl;

bool
ui_basic_view :: destroy_layout()
{
	if (this->layout) evas_object_del(this->layout);

	return true;
}

bool
ui_basic_view :: create_layout()
{
    ui_viewmgr *viewmgr = dynamic_cast<ui_viewmgr *>(ui_view_base ::get_viewmgr());
    Evas_Object *parent = viewmgr->get_window();

	Evas_Object *layout = elm_layout_add(parent);
	if (!layout) {
		LOGE("Failed to create a layout = ui_basic_view(%p)", this);
		return false;
	}

	if (!elm_layout_theme_set(layout, "layout", "tizen_view", "default")) {
		LOGE("Failed to set theme = ui_basic_view(%p)", this);
		evas_object_del(layout);
		return false;
	}
	evas_object_size_hint_weight_set(layout, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_size_hint_align_set(layout, EVAS_HINT_FILL, EVAS_HINT_FILL);

	if (this->get_content()) {
		elm_object_part_content_set(layout, "elm.swallow.content", CONVERT_TO_EO(this->get_content()));
	}

	this->layout = layout;

	return true;
}


ui_basic_view :: ui_basic_view(ui_controller *controller) : ui_view(controller), layout(NULL)
{
}

ui_basic_view :: ~ui_basic_view()
{
	destroy_layout();
}


void
ui_basic_view ::load()
{
	this->create_layout();
	ui_view :: load();
}

Evas_Object *
ui_basic_view :: set_content(Evas_Object *content)
{
   Evas_Object *pcontent = ui_view :: set_content(content);

   if (this->layout) {
	   LOGI("layout content set called content = %p", content);
	  elm_object_part_content_unset(this->layout, "elm.swallow.content");
      elm_object_part_content_set(this->layout, "elm.swallow.content", content);
   }
   return pcontent;
}
