#include "efl_viewmgr.h"

using namespace efl;

void
win_delete_request_cb(void *data, Evas_Object *obj EINA_UNUSED, void *event_info EINA_UNUSED)
{
	ui_viewmgr *viewmgr = static_cast<ui_viewmgr*>(data);
	delete(viewmgr);
}

bool
ui_viewmgr::create_conformant(Evas_Object *win)
{
	Evas_Object *conform = elm_conformant_add(win);
	if (!conform) return false;

	evas_object_size_hint_weight_set(conform, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	elm_win_resize_object_add(win, conform);
	elm_win_conformant_set(win, EINA_TRUE);
	evas_object_show(conform);

	this->conform = conform;

	return true;
}

bool
ui_viewmgr::create_base_layout(Evas_Object *conform)
{
	Evas_Object *layout = elm_layout_add(conform);
	if (!layout) return false;

	elm_layout_theme_set(layout, "layout", "application", "default");
	elm_object_content_set(conform, layout);

	this->layout = layout;

	return true;
}

ui_viewmgr::ui_viewmgr(const char *pkg)
		: ui_viewmgr_base()
{
	if (!pkg)
	{
		LOGE("Invalid package name");
		return;
	}
	//Window
	this->win = elm_win_util_standard_add(pkg, pkg);

	if (!this->win)
	{
		LOGE("Failed to create a window (%s)", pkg);
		return;
	}

	//Set window rotation
	if (elm_win_wm_rotation_supported_get(this->win))
	{
		int rots[4] =
		{ 0, 90, 180, 270 };
		elm_win_wm_rotation_available_rotations_set(this->win, (const int *) (&rots), 4);
	}

	//Window is requested to delete.
	evas_object_smart_callback_add(this->win, "delete,request",
			[](void *data, Evas_Object *obj, void *event_info) -> void
			{
				ui_viewmgr *viewmgr = static_cast<ui_viewmgr*>(data);
				delete(viewmgr);

				//FIXME: Window is destroyed. Terminate Application!
				//ui_app_exit();
			},
			this);

	//Conformant: Make this configurable.
	if (!this->create_conformant(this->win))
	{
		LOGE("Failed to create a conformant (%s)", pkg);
		return;
	}

	if (!this->create_base_layout(this->conform))
	{
		LOGE("Failed to create a base layout (%s)", pkg);
		return;
	}

	//Set Indicator properties
	elm_win_indicator_mode_set(this->win, ELM_WIN_INDICATOR_SHOW);
	elm_win_indicator_opacity_set(this->win, ELM_WIN_INDICATOR_TRANSPARENT);
	elm_win_autodel_set(this->win, EINA_TRUE);
}

ui_viewmgr::~ui_viewmgr()
{
}

bool ui_viewmgr::activate()
{
	ui_viewmgr_base :: activate();

	elm_object_part_content_unset(this->get_base(), "elm.swallow.content");

	ui_view *view = dynamic_cast<ui_view *>(this->get_last_view());

	//TODO: get parent?
	Evas_Object *content = view->get_base();
	if (content == this->get_base())
	{
		elm_object_part_content_set(this->get_base(), "elm.swallow.content", CONVERT_TO_EO(view->get_content()));
	}
	else
	{
		elm_object_part_content_set(this->get_base(), "elm.swallow.content", CONVERT_TO_EO(view->get_base()));
	}

	evas_object_show(this->win);

	return true;
}

bool ui_viewmgr::deactivate()
{
	ui_viewmgr_base ::deactivate();

	//FIXME: based on the profile, we should app to go behind or terminate.
	if (true)
	{
		evas_object_lower(this->win);
	}
	else
	{
		//FIXME: exit app
		//ui_app_exit();
	}

	return true;
}

bool ui_viewmgr::pop_view()
{
	if (!ui_viewmgr_base::pop_view())
	{
		return false;
	}

	ui_view *view = dynamic_cast<ui_view *>(this->get_last_view());

	//TODO: get parent?
	Evas_Object *content = view->get_base();
	if (content == this->get_base())
	{
		elm_object_part_content_set(this->get_base(), "elm.swallow.content", CONVERT_TO_EO(view->get_content()));
	}
	else
	{
		elm_object_part_content_set(this->get_base(), "elm.swallow.content", CONVERT_TO_EO(view->get_base()));
	}

	return true;
}

ui_view *
ui_viewmgr::push_view(ui_view *view)
{
	ui_viewmgr_base::push_view(view);

	//Don't prepare yet if viewmgr is not activated.
	if (!this->is_activated()) return view;

	elm_object_part_content_unset(this->get_base(), "elm.swallow.content");

	Evas_Object *content = view->get_base();

	if (content == this->get_base())
	{
		elm_object_part_content_set(this->get_base(), "elm.swallow.content", CONVERT_TO_EO(view->get_content()));
	}
	else
	{
		LOGE("view->base = %p", view->get_base());
		elm_object_part_content_set(this->get_base(), "elm.swallow.content", CONVERT_TO_EO(view->get_base()));
	}

	return view;
}
