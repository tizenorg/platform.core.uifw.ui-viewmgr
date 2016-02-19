/*
 * Copyright (c) 2016 Samsung Electronics Co., Ltd All Rights Reserved
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *               http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 *
 */
#include "efl_viewmgr.h"

using namespace efl;

bool ui_viewmgr::set_indicator(ui_view_indicator indicator)
{
	if (this->indicator == indicator) return false;
	this->indicator = indicator;

	Evas_Object *window = this->get_window();
	Evas_Object *conform = this->get_conformant();

	switch (indicator)
	{
	case UI_VIEW_INDICATOR_DEFAULT:
		elm_win_indicator_opacity_set(window, ELM_WIN_INDICATOR_OPAQUE);
		elm_win_indicator_mode_set(window, ELM_WIN_INDICATOR_SHOW);
		/* Unset if you set the Indicator BG */
		evas_object_del(elm_object_part_content_get(conform, "elm.swallow.indicator_bg"));
		elm_object_signal_emit(conform, "elm,state,indicator,nooverlap", "elm");
		break;
	case UI_VIEW_INDICATOR_OPTIMAL:
		elm_win_indicator_mode_set(window, ELM_WIN_INDICATOR_SHOW);
		elm_win_indicator_opacity_set(window, ELM_WIN_INDICATOR_TRANSPARENT);
		break;
	case UI_VIEW_INDICATOR_OVERLAP:
		elm_win_indicator_mode_set(window, ELM_WIN_INDICATOR_SHOW);
		elm_object_signal_emit(conform, "elm,state,indicator,overlap", "elm");
		break;
	default:
		elm_win_indicator_mode_set(window, ELM_WIN_INDICATOR_HIDE);
		break;
	}
	return true;
}

bool ui_viewmgr::create_conformant(Evas_Object *win)
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

bool ui_viewmgr::create_base_layout(Evas_Object *conform)
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
	elm_win_indicator_opacity_set(this->win, ELM_WIN_INDICATOR_OPAQUE);

	elm_win_autodel_set(this->win, EINA_TRUE);
}

ui_viewmgr::~ui_viewmgr()
{
}

bool ui_viewmgr::activate()
{
	ui_viewmgr_base::activate();

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

	this->set_indicator(view->get_indicator());
	view->activate();

	evas_object_show(this->win);

	return true;
}

bool ui_viewmgr::deactivate()
{
	ui_viewmgr_base::deactivate();

	//FIXME: based on the profile, we should app to go behind or terminate.
	if (true)
	{
		ui_view *view = this->get_last_view();
		if (view) view->inactive();
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
	if (this->get_view_count() == 1) this->deactivate();
	else if(!ui_viewmgr_base::pop_view()) return false;

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

	this->set_indicator(view->get_indicator());

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
		elm_object_part_content_set(this->get_base(), "elm.swallow.content", CONVERT_TO_EO(view->get_base()));
	}

	this->set_indicator(view->get_indicator());

	return view;
}
