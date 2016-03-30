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
#include "../../include/efl/ui_base_viewmanager.h"

using namespace efl_viewmgr;
using namespace viewmgr;

//FIXME: is it correct to define here?
#define EDJ_PATH "/usr/share/edje/ui-viewmgr/ui-viewmgr.edj"

bool ui_base_viewmgr::create_base_layout(Elm_Conformant *conform, const char *style)
{
	char buf[128];
	Elm_Layout *layout = elm_layout_add(conform);
	if (!layout) return false;

	//FIXME: Is it C programming style? need to change?
	snprintf(buf, sizeof(buf), "transition/%s", style);
	//default transition layout
	elm_layout_file_set(layout, EDJ_PATH, buf);
	elm_object_content_set(conform, layout);

	//Push Finished Event
	elm_layout_signal_callback_add(layout, "push,finished", "viewmgr",
			[](void *data, Evas_Object *obj, const char *emission, const char *source) -> void
			{
				ui_base_viewmgr *viewmgr = static_cast<ui_base_viewmgr *>(data);
				ui_base_view *pview = viewmgr->get_view(viewmgr->get_view_count() - 2);
				ui_base_view *view = viewmgr->get_last_view();
				if (pview) viewmgr->push_view_finished(pview);
				if (view) viewmgr->push_view_finished(view);
			},
			this);

	//Pop Finished Event
	elm_layout_signal_callback_add(layout, "pop,finished", "viewmgr",
			[](void *data, Evas_Object *obj, const char *emission, const char *source) -> void
			{
				ui_base_viewmgr *viewmgr = static_cast<ui_base_viewmgr *>(data);
				ui_base_view *pview = viewmgr->get_view(viewmgr->get_view_count() - 2);
				ui_base_view *view = viewmgr->get_last_view();
				if (pview) viewmgr->pop_view_finished(pview);
				if (view) viewmgr->pop_view_finished(view);
			},
			this);

	this->layout = layout;

	return true;
}

Elm_Layout *ui_base_viewmgr::set_transition_layout(string transition_style)
{
	Elm_Layout *effect_layout = NULL;

	elm_object_part_content_unset(this->get_base(), "pcontent");
	elm_object_part_content_unset(this->get_base(), "content");

	if (transition_style.compare(this->transition_style) == 0) return this->layout;

	if (effect_map.size()) effect_layout = effect_map.find(transition_style)->second;

	//Conformant content change to current effect layout and change to hide prev layout.
	Elm_Layout *playout = elm_object_part_content_unset(this->conform, "elm.swallow.content");
	evas_object_hide(playout);

	if (!effect_layout)
	{
		//Create and add effect_layouts in map here.
		//FIXME: If we have to support many effects, this logic should be changed.
		effect_map.insert(pair<string, Elm_Layout *>("default", this->layout));
		this->create_base_layout(this->get_conformant(), transition_style.c_str());
		effect_map.insert(pair<string, Elm_Layout *>(transition_style, this->layout));
	}
	else
	{
		elm_object_part_content_set(this->conform, "elm.swallow.content", effect_layout);

		this->layout = effect_layout;
	}

	this->transition_style = transition_style;

	return this->layout;
}

void ui_base_viewmgr::activate_top_view()
{
	elm_object_part_content_unset(this->get_base(), "content");

	ui_base_view *view = this->get_last_view();

	//In case of ui_base_view, it doesn't have any base form. It uses viewmgr base instead.
	Evas_Object *content;
	if (view->get_base() == this->get_base())
	{
		content = CONVERT_TO_EO(view->get_content());
	}
	else
	{
		content = CONVERT_TO_EO(view->get_base());
	}

	elm_object_part_content_set(this->get_base(), "content", content);

	this->set_indicator(view->get_indicator());
}

//FIXME: How to deal with indicator in other UI framework? Dali? Volt?
//Is it possible make this interface common?
bool ui_base_viewmgr::set_indicator(ui_view_indicator indicator)
{
	if (this->indicator == indicator) return false;
	this->indicator = indicator;

	Elm_Win *window = this->get_window();
	Elm_Conformant *conform = this->get_conformant();

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

bool ui_base_viewmgr::create_conformant(Elm_Win *win)
{
	Elm_Conformant *conform = elm_conformant_add(win);
	if (!conform) return false;

	evas_object_size_hint_weight_set(conform, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	elm_win_resize_object_add(win, conform);
	elm_win_conformant_set(win, EINA_TRUE);
	evas_object_show(conform);

	this->conform = conform;

	return true;
}

ui_base_viewmgr::ui_base_viewmgr(const char *pkg, ui_base_key_listener *key_listener)
		: singleton(), ui_iface_viewmgr(), key_listener(key_listener), transition_style("default")
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

	//FIXME: Make a method? to set available rotation degree.
	//Set window rotation
	if (elm_win_wm_rotation_supported_get(this->win))
	{
		int rots[4] =
		{ 0, 90, 180, 270 };
		elm_win_wm_rotation_available_rotations_set(this->win, (const int *) (&rots), 4);
	}
	evas_object_smart_callback_add(this->win, "wm,rotation,changed",
			[](void *data, Evas_Object *obj, void *event_info) -> void
			{
				int rot = elm_win_rotation_get(obj);

				ui_base_viewmgr *viewmgr = static_cast<ui_base_viewmgr *>(data);
				ui_base_view *view = viewmgr->get_last_view();
				view->on_rotate(rot);

				//FIXME: Change this configurable?
				if (rot == 0 || rot == 180) view->on_portrait();
				else view->on_landscape();
			}
			, this);

	//Window is requested to delete.
	evas_object_smart_callback_add(this->win, "delete,request",
			[](void *data, Evas_Object *obj, void *event_info) -> void
			{
				ui_base_viewmgr *viewmgr = static_cast<ui_base_viewmgr*>(data);
				delete(viewmgr);
				//FIXME: Window is destroyed. Terminate Application!
				//ui_app_exit();
			},
			this);

	//FIXME: Make conformant configurable?
	if (!this->create_conformant(this->win))
	{
		LOGE("Failed to create a conformant (%s)", pkg);
		return;
	}

	if (!this->create_base_layout(this->conform, "default"))
	{
		LOGE("Failed to create a base layout (%s)", pkg);
		return;
	}

	//Set Indicator properties
	elm_win_indicator_mode_set(this->win, ELM_WIN_INDICATOR_SHOW);
	elm_win_indicator_opacity_set(this->win, ELM_WIN_INDICATOR_OPAQUE);

	elm_win_autodel_set(this->win, EINA_TRUE);

	key_listener->init();
}

ui_base_viewmgr::ui_base_viewmgr(const char *pkg)
		: ui_base_viewmgr(pkg, new ui_base_key_listener(this))
{
}

ui_base_viewmgr::~ui_base_viewmgr()
{
	this->key_listener->term();
	delete(this->key_listener);
}

bool ui_base_viewmgr::activate()
{
	if (!ui_iface_viewmgr::activate()) return false;

	this->activate_top_view();

	//FIXME: Necessary??
	ui_base_view *view = this->get_last_view();
	view->on_activate();

	evas_object_show(this->win);

	return true;
}

bool ui_base_viewmgr::deactivate()
{
	if (!ui_iface_viewmgr::deactivate()) return false;

	//FIXME: based on the profile, we should app to go behind or terminate.
	if (true)
	{
		ui_base_view *view = this->get_last_view();
		if (view) view->on_deactivate();
		evas_object_lower(this->win);
	}
	else
	{
		//FIXME: exit app
		//ui_app_exit();
	}

	return true;
}

bool ui_base_viewmgr::pop_view()
{
	if (this->get_view_count() == 1)
	{
		this->deactivate();
		return true;
	}

	if(!ui_iface_viewmgr::pop_view())
	{
		return false;
	}

	ui_base_view *pview = this->get_view(this->get_view_count() - 2);
	ui_base_view *view = this->get_last_view();

	//In case, if view doesn't have transition effect
	if (!strcmp(view->get_transition_style(), "none"))
	{
		this->pop_view_finished(pview);
		this->pop_view_finished(view);
		this->activate_top_view();
		return true;
	}

	//Choose an effect layout.
	Elm_Layout *effect = this->set_transition_layout(view->get_transition_style());
	if (!effect) {
		LOGE("invalid effect transition style?! = %s", view->get_transition_style());
		this->pop_view_finished(pview);
		this->pop_view_finished(view);
		this->activate_top_view();
		return true;
	}

	//Trigger Effects.
	Evas_Object *prv = CONVERT_TO_EO(this->get_base() == pview->get_base() ? pview->get_content() : pview->get_base());
	elm_layout_content_set(effect, "content", prv);

	Evas_Object *cur = CONVERT_TO_EO(this->get_base() == view->get_base() ? view->get_content() : view->get_base());
	elm_layout_content_set(effect, "pcontent", cur);

	elm_layout_signal_emit(effect, "view,pop", "viewmgr");

	this->set_indicator(pview->get_indicator());

	return true;
}

ui_base_view * ui_base_viewmgr::push_view(ui_base_view *view)
{
	ui_iface_viewmgr::push_view(view);

	if (!this->is_activated()) return view;

	//In case, if viewmgr has one view, we skip effect.
	if (this->get_view_count() == 1) {
		this->activate_top_view();
		this->push_view_finished(view);
		return view;
	}

	ui_base_view *pview = this->get_view(this->get_view_count() - 2);

	//In case, if view doesn't have transition effect
	if (!strcmp(view->get_transition_style(), "none")) {
		this->activate_top_view();
		this->push_view_finished(pview);
		this->push_view_finished(view);
		return view;
	}

	//Choose an effect layout.
	Elm_Layout *effect = this->set_transition_layout(view->get_transition_style());
	if (!effect) {
		LOGE("invalid effect transition style?! = %s", view->get_transition_style());
		this->activate_top_view();
		this->push_view_finished(pview);
		this->push_view_finished(view);
		return view;
	}

	//Trigger Effects.
	Evas_Object *prv = CONVERT_TO_EO(this->get_base() == pview->get_base() ? pview->get_content() : pview->get_base());
	elm_layout_content_set(effect, "pcontent", prv);

	Evas_Object *cur = CONVERT_TO_EO(this->get_base() == view->get_base() ? view->get_content() : view->get_base());
	elm_layout_content_set(effect, "content", cur);

	elm_layout_signal_emit(effect, "view,push", "viewmgr");

	this->set_indicator(view->get_indicator());

	return view;
}

bool ui_base_viewmgr::insert_view_before(ui_base_view *view, ui_base_view *before)
{
	ui_iface_viewmgr::insert_view_before(view, before);

	return true;
}

bool ui_base_viewmgr::insert_view_after(ui_base_view *view, ui_base_view *after)
{
	ui_iface_viewmgr::insert_view_after(view, after);

	return true;
}

ui_base_view *ui_base_viewmgr::get_view(unsigned int idx)
{
	return dynamic_cast<ui_base_view *>(ui_iface_viewmgr::get_view(idx));
}

ui_base_view *ui_base_viewmgr::get_last_view()
{
	return dynamic_cast<ui_base_view *>(ui_iface_viewmgr::get_last_view());
}
