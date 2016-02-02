#include <dlog.h>
#include "ui_basic_view.h"
#include "ui_viewmgr.h"

using namespace efl;

bool ui_basic_view::destroy_layout()
{
	if (!this->layout) return false;
	if (this->get_content())
	{
		elm_object_part_content_unset(this->layout, "elm.swallow.content");
	}
	evas_object_del(this->layout);

	return true;
}

bool ui_basic_view::create_layout()
{
	ui_viewmgr *viewmgr = dynamic_cast<ui_viewmgr *>(ui_view_base::get_viewmgr());
	Evas_Object *parent = viewmgr->get_window();

	Evas_Object *layout = elm_layout_add(parent);
	if (!layout)
	{
		LOGE("Failed to create a layout = ui_basic_view(%p)", this);
		return false;
	}

	if (!elm_layout_theme_set(layout, "layout", "tizen_view", "default"))
	{
		LOGE("Failed to set theme = ui_basic_view(%p)", this);
		evas_object_del(layout);
		return false;
	}
	evas_object_size_hint_weight_set(layout, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_size_hint_align_set(layout, EVAS_HINT_FILL, EVAS_HINT_FILL);

	if (this->get_content())
	{
		elm_object_part_content_set(layout, "elm.swallow.content", CONVERT_TO_EO(this->get_content()));
	}

	this->layout = layout;

	return true;
}

ui_basic_view::ui_basic_view(ui_controller *controller) :
		ui_view(controller), layout(NULL)
{
}

ui_basic_view::~ui_basic_view()
{
	destroy_layout();
}

void ui_basic_view::load()
{
	this->create_layout();
	ui_view::load();
}

void ui_basic_view ::unload()
{
	this->destroy_layout();
	ui_view::unload();
}

Evas_Object *
ui_basic_view::set_content(Evas_Object *content)
{
	Evas_Object *pcontent = ui_view::set_content(content);

	if (this->layout)
	{
		elm_object_part_content_unset(this->layout, "elm.swallow.content");
		elm_object_part_content_set(this->layout, "elm.swallow.content", content);
	}
	else
	{
		LOGE("Layout is not exist!");
	}

	return pcontent;
}


Evas_Object *
ui_basic_view::set_content(Evas_Object *content, const char *title, const char *subtitle, Evas_Object *title_left_btn, Evas_Object *title_right_btn)
{

	Evas_Object *pcontent = this->set_content(content);

	if (this->layout)
	{
		if (title) elm_object_part_text_set(this->layout, "elm.text.title", title);
		if (subtitle) elm_object_part_text_set(this->layout, "elm.text.subtitle", subtitle);
		if (title_left_btn)
		{
			elm_object_style_set(title_left_btn, "naviframe/title_left");
			//FIXME:
			//elm_object_style_set(title_left_btn, "tizen_view/title_left");
			elm_object_part_content_set(this->layout, "title_left_btn", title_left_btn);
		}
		if (title_right_btn)
		{
			LOGE("AHHHHHHHHHHHHH");
			elm_object_style_set(title_right_btn, "naviframe/title_right");
			//FIXME:
			//elm_object_style_set(title_left_btn, "tizen_view/title_right");
			elm_object_part_content_set(this->layout, "title_right_btn", title_right_btn);
		}
	}
	else
	{
		LOGE("Layout is not exist!");
	}

	return pcontent;
}


