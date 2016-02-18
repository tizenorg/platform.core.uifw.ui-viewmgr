#include "efl_viewmgr.h"

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

	if (!elm_layout_file_set(layout, EDJ_PATH, GROUP))
	{
		LOGE("Failed to set file = ui_basic_view(%p), path(%s), group(%s)", this, EDJ_PATH, GROUP);
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

ui_basic_view::ui_basic_view(ui_controller *controller, const char *name)
		: ui_view(controller, name), layout(NULL)
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

void ui_basic_view::unload()
{
	this->destroy_layout();
	ui_view::unload();
}

Evas_Object *
ui_basic_view::set_content(Evas_Object *content, const char *title)
{
	Evas_Object *pcontent = ui_view::set_content(content);

	if (this->layout)
	{
		elm_object_part_content_unset(this->layout, "elm.swallow.content");
		elm_object_part_content_set(this->layout, "elm.swallow.content", content);
		elm_object_part_text_set(this->layout, "elm.text.title", title);
	}
	else
	{
		LOGE("Layout is not exist!");
	}

	return pcontent;
}

bool ui_basic_view::set_subtitle(const char *text)
{
	if (this->layout)
	{
		elm_object_part_text_set(this->layout, "elm.text.subtitle", text);
		if (text) elm_object_signal_emit(this->layout, "elm,state,subtitle,show", "elm");
		else elm_object_signal_emit(this->layout, "elm,state,subtitle,hide", "elm");
		return true;
	}
	LOGE("Layout is not exist!");
	return false;
}

bool ui_basic_view::set_icon(Evas_Object *icon)
{
	if (this->layout)
	{
		elm_object_part_content_set(this->layout, "elm.swallow.icon", icon);
		if (icon) elm_object_signal_emit(this->layout, "elm,state,icon,show", "elm");
		else elm_object_signal_emit(this->layout, "elm,state,icon,hide", "elm");
		return true;
	}
	LOGE("Layout is not exist!");
	return false;
}

bool ui_basic_view::set_title_left_btn(Evas_Object *title_left_btn)
{
	if (this->layout)
	{
		if (title_left_btn)
		{
			elm_object_style_set(title_left_btn, "naviframe/title_left");
			//FIXME: naviframe/title_left -> tizen_view/title_left
			//elm_object_style_set(title_left_btn, "tizen_view/title_left");
		}
		elm_object_part_content_set(this->layout, "title_left_btn", title_left_btn);
		if (title_left_btn) elm_object_signal_emit(this->layout, "elm,state,title_left_btn,show", "elm");
		else elm_object_signal_emit(this->layout, "elm,state,title_left_btn,hide", "elm");
		return true;
	}
	LOGE("Layout is not exist!");
	return false;
}

bool ui_basic_view::set_title_right_btn(Evas_Object *title_right_btn)
{
	if (this->layout)
	{
		if (title_right_btn)
		{
			elm_object_style_set(title_right_btn, "naviframe/title_right");
			//FIXME: naviframe/title_right -> tizen_view/title_right
			//elm_object_style_set(title_left_btn, "tizen_view/title_right");
		}
		elm_object_part_content_set(this->layout, "title_right_btn", title_right_btn);
		if (title_right_btn) elm_object_signal_emit(this->layout, "elm,state,title_right_btn,show", "elm");
		else elm_object_signal_emit(this->layout, "elm,state,title_right_btn,hide", "elm");
		return true;
	}
	LOGE("Layout is not exist!");
	return false;
}

bool ui_basic_view::set_title_badge(const char *text)
{
	if (this->layout)
	{
		elm_object_part_text_set(this->layout, "title_badge", text);
		if (text) elm_object_signal_emit(this->layout, "elm,state,title_badge,show", "elm");
		else elm_object_signal_emit(this->layout, "elm,state,title_badge,hide", "elm");
		return true;
	}
	LOGE("Layout is not exist!");
	return false;
}

bool ui_basic_view::set_title(const char *text)
{
	if (this->layout)
	{
		elm_object_part_text_set(this->layout, "elm.text.title", text);
		if (text) elm_object_signal_emit(this->layout, "elm,state,title,show", "elm");
		else elm_object_signal_emit(this->layout, "elm,state,title,hide", "elm");
		return true;
	}
	LOGE("Layout is not exist!");
	return false;
}

Evas_Object *ui_basic_view::set_content(Evas_Object *content, const char *title, const char *subtitle, Evas_Object *icon, Evas_Object *title_left_btn,
        Evas_Object *title_right_btn)
{
	Evas_Object *pcontent = this->set_content(content);

	if (this->layout)
	{
		this->set_title(title);
		this->set_subtitle(subtitle);
		this->set_icon(icon);
		this->set_title_left_btn(title_left_btn);
		this->set_title_right_btn(title_right_btn);
	}
	else
	{
		LOGE("Layout is not exist!");
	}

	return pcontent;
}

