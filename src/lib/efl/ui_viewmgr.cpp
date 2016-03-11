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
#include "../../include/efl/ui_viewmanager_efl.h"

using namespace efl_viewmgr;
using namespace viewmgr;

//FIXME: is it correct to define here?
#define EDJ_PATH "/usr/share/edje/ui-viewmgr/ui-viewmgr.edj"

Evas_Object *ui_viewmgr::set_transition_layout(string transition_style)
{
	elm_object_part_content_unset(this->get_base(), "pcontent");
	elm_object_part_content_unset(this->get_base(), "content");

	if (transition_style == this->transition_style) return this->layout;

	//FIXME: 1. Find current style effect layout
	Evas_Object *effect = this->get_base();

	//2. Switch effect layout to base layout
	elm_object_part_content_unset(this->get_conformant(), "elm.swallow.content");
	elm_object_part_content_set(this->get_conformant(), "elm.swallow.content", effect);

	this->layout = effect;
	this->transition_style = transition_style;

	return this->layout;
}

void ui_viewmgr::active_top_view()
{
	elm_object_part_content_unset(this->get_base(), "content");

	ui_view *view = this->get_last_view();

	//In case of ui_view, it doesn't have any base form. It uses viewmgr base instead.
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

	//default transition layout
	elm_layout_file_set(layout, EDJ_PATH, "transition/default");
	elm_object_content_set(conform, layout);

	//Push Finished Event
	elm_layout_signal_callback_add(layout, "push,finished", "viewmgr",
			[](void *data, Evas_Object *obj, const char *emission, const char *source) -> void
			{
				ui_viewmgr *viewmgr = static_cast<ui_viewmgr *>(data);
				ui_view *pview = viewmgr->get_view(viewmgr->get_view_count() - 2);
				ui_view *view = viewmgr->get_last_view();
				if (pview) viewmgr->push_view_finished(pview);
				if (view) viewmgr->push_view_finished(view);
			},
			this);

	//Pop Finished Event
	elm_layout_signal_callback_add(layout, "pop,finished", "viewmgr",
			[](void *data, Evas_Object *obj, const char *emission, const char *source) -> void
			{
				ui_viewmgr *viewmgr = static_cast<ui_viewmgr *>(data);
				ui_view *pview = viewmgr->get_view(viewmgr->get_view_count() - 2);
				ui_view *view = viewmgr->get_last_view();
				if (pview) viewmgr->pop_view_finished(pview);
				if (view) viewmgr->pop_view_finished(view);
			},
			this);

	this->layout = layout;

	return true;
}

ui_viewmgr::ui_viewmgr(const char *pkg, ui_key_listener *key_listener)
		: ui_iface_viewmgr(), key_listener(key_listener), transition_style("")
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

	key_listener->init();
}

ui_viewmgr::ui_viewmgr(const char *pkg)
		: ui_viewmgr(pkg, new ui_key_listener(this))
{
}

ui_viewmgr::~ui_viewmgr()
{
	this->key_listener->term();
	delete(this->key_listener);
}

bool ui_viewmgr::activate()
{
	if (!ui_iface_viewmgr::activate()) return false;

	this->active_top_view();

	//FIXME: Necessary??
	ui_view *view = this->get_last_view();
	view->active();

	evas_object_show(this->win);

	return true;
}

bool ui_viewmgr::deactivate()
{
	if (!ui_iface_viewmgr::deactivate()) return false;

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
	if (this->get_view_count() == 1)
	{
		this->deactivate();
		return true;
	}

	if(!ui_iface_viewmgr::pop_view())
	{
		return false;
	}

	ui_view *pview = this->get_view(this->get_view_count() - 2);
	ui_view *view = this->get_last_view();

	//In case, if view doesn't have transition effect
	if (!strcmp(view->get_transition_style(), "none"))
	{
		this->pop_view_finished(pview);
		this->pop_view_finished(view);
		this->active_top_view();
		return true;
	}

	//Choose an effect layout.
	Evas_Object *effect = this->set_transition_layout(view->get_transition_style());
	if (!effect) {
		LOGE("invalid effect transition style?! = %s", view->get_transition_style());
		this->pop_view_finished(pview);
		this->pop_view_finished(view);
		this->active_top_view();
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

ui_view * ui_viewmgr::push_view(ui_view *view)
{
	ui_iface_viewmgr::push_view(view);

	if (!this->is_activated()) return view;

	//In case, if viewmgr has one view, we skip effect.
	if (this->get_view_count() == 1) {
		this->active_top_view();
		this->push_view_finished(view);
		return view;
	}

	ui_view *pview = this->get_view(this->get_view_count() - 2);

	//In case, if view doesn't have transition effect
	if (!strcmp(view->get_transition_style(), "none")) {
		this->active_top_view();
		this->push_view_finished(pview);
		this->push_view_finished(view);
		return view;
	}

	//Choose an effect layout.
	Evas_Object *effect = this->set_transition_layout(view->get_transition_style());
	if (!effect) {
		LOGE("invalid effect transition style?! = %s", view->get_transition_style());
		this->active_top_view();
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

ui_view *ui_viewmgr::get_view(unsigned int idx)
{
	return dynamic_cast<ui_view *>(ui_iface_viewmgr::get_view(idx));
}

ui_view *ui_viewmgr::get_last_view()
{
	return dynamic_cast<ui_view *>(ui_iface_viewmgr::get_last_view());
}
