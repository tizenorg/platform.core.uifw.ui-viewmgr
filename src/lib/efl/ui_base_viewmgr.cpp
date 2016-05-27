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

#include <map>
#include <string>
#include "../../include/efl/ui_base_viewmanager.h"

using namespace std;

/***********************************************************************************************/
/* Internal class Implementation                                                               */
/***********************************************************************************************/
namespace efl_viewmanager
{

class ui_base_viewmgr_impl
{
	friend class ui_base_viewmgr;

private:
	ui_base_viewmgr *viewmgr;
	Elm_Win *win;             		           //This is acting like a base object of viewmgr.
	Elm_Conformant *conform;                   //Conformant for viewmgr.
	Elm_Scroller *scroller;                    //Scroller for viewmgr.
	Elm_Layout *layout;                        //Viewmgr's base layout.
	ui_base_key_listener *key_listener;        //HW Key Handler such as "BACK" key...
	ui_view_indicator indicator;               //Mode of indicator.
	string transition_style;                   //Current transition effect style name
	map<string, Elm_Layout *> effect_map;      //Map for effect layouts.

	Elm_Layout *set_transition_layout(string transition_style);

	bool create_conformant(Elm_Win *win);
	bool create_scroller(Elm_Conformant *conform);
	bool create_base_layout(Elm_Scroller *scroller, const char *style);
	bool set_indicator(ui_view_indicator indicator);
	void activate_top_view();
	bool init();
	bool term();

public:
	ui_base_viewmgr_impl(ui_base_viewmgr *viewmgr, const char *pkg, ui_base_key_listener *key_listener);
	~ui_base_viewmgr_impl();

	bool activate();
	bool deactivate();
	ui_base_view *push_view(ui_base_view *view);
	bool pop_view();
	bool insert_view_before(ui_base_view *view, ui_base_view *before);
	bool insert_view_after(ui_base_view *view, ui_base_view *after);

	Evas_Object *get_base()
	{
		return this->layout;
	}
	Elm_Win *get_window()
	{
		return this->win;
	}
	Elm_Conformant *get_conformant()
	{
		return this->conform;
	}
};

}

bool ui_base_viewmgr_impl::create_base_layout(Elm_Scroller *scroller, const char *style)
{
	char edj_path[PATH_MAX];
	char group_name[128];

	Elm_Layout *layout = elm_layout_add(scroller);
	if (!layout) return false;

	snprintf(group_name, sizeof(group_name), "transition/%s", style);
	snprintf(edj_path, sizeof(edj_path), "%s/ui-viewmgr.edj", EDJ_PATH);
	elm_layout_file_set(layout, edj_path, group_name);
	evas_object_size_hint_weight_set(layout, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_size_hint_align_set(layout, EVAS_HINT_FILL, EVAS_HINT_FILL);
	elm_object_content_set(scroller, layout);

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
			this->viewmgr);

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
			this->viewmgr);

	this->layout = layout;

	return true;
}

Elm_Layout *ui_base_viewmgr_impl::set_transition_layout(string transition_style)
{
	Elm_Layout *effect_layout = NULL;
	Elm_Layout *pcontent;

	pcontent = elm_object_part_content_unset(this->get_base(), "pcontent");
	if (pcontent) evas_object_hide(pcontent);
	elm_object_part_content_unset(this->get_base(), "content");

	if (transition_style.compare(this->transition_style) == 0) return this->layout;

	if (effect_map.size()) effect_layout = effect_map.find(transition_style)->second;

	//Scroller content change to current effect layout and change to hide prev layout.
	Elm_Layout *playout = elm_object_part_content_unset(this->scroller, NULL);
	evas_object_hide(playout);

	if (!effect_layout)
	{
		//Create and add effect_layouts in map here.
		//FIXME: If we have to support many effects, this logic should be changed.
		effect_map.insert(pair<string, Elm_Layout *>("default", this->layout));
		this->create_base_layout(this->scroller, transition_style.c_str());
		effect_map.insert(pair<string, Elm_Layout *>(transition_style, this->layout));
	}
	else
	{
		elm_object_content_set(this->scroller, effect_layout);

		this->layout = effect_layout;
	}

	this->transition_style = transition_style;

	return this->layout;
}

void ui_base_viewmgr_impl::activate_top_view()
{
	Evas_Object *pcontent = elm_object_part_content_unset(this->get_base(), "content");
	if (pcontent) evas_object_hide(pcontent);

	ui_base_view *view = this->viewmgr->get_last_view();

	//In case of ui_base_view, it doesn't have any base form. It uses viewmgr base instead.
	Evas_Object *content;
	if (view->get_base() == this->get_base())
	{
		content = view->get_content();
	}
	else
	{
		content = view->get_base();
	}

	elm_object_part_content_set(this->get_base(), "content", content);

	this->set_indicator(view->get_indicator());
}

//FIXME: How to deal with indicator in other UI framework? Dali? Volt?
//Is it possible make this interface common?
bool ui_base_viewmgr_impl::set_indicator(ui_view_indicator indicator)
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

bool ui_base_viewmgr_impl::create_conformant(Elm_Win *win)
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

bool ui_base_viewmgr_impl::create_scroller(Elm_Conformant *conform)
{
	Elm_Scroller *scroller = elm_scroller_add(conform);
	if (!scroller) return false;

	elm_scroller_policy_set(scroller, ELM_SCROLLER_POLICY_AUTO, ELM_SCROLLER_POLICY_AUTO);
	evas_object_size_hint_weight_set(scroller, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_size_hint_align_set(scroller, EVAS_HINT_FILL, EVAS_HINT_FILL);

	elm_object_content_set(conform, scroller);

	this->scroller = scroller;

	return true;
}

ui_base_viewmgr_impl::ui_base_viewmgr_impl(ui_base_viewmgr *viewmgr, const char *pkg, ui_base_key_listener *key_listener)
		: viewmgr(viewmgr), key_listener(key_listener), transition_style("default")
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
			, this->viewmgr);
	//Window is requested to delete.
	evas_object_smart_callback_add(this->win, "delete,request",
			[](void *data, Evas_Object *obj, void *event_info) -> void
			{
				ui_base_viewmgr *viewmgr = static_cast<ui_base_viewmgr*>(data);
				delete(viewmgr);
			},
			this->viewmgr);

	//FIXME: Make conformant configurable?
	if (!this->create_conformant(this->win))
	{
		LOGE("Failed to create a conformant (%s)", pkg);
		return;
	}

	if (!this->create_scroller(this->conform))
	{
		LOGE("Failed to create a scroller (%s)", pkg);
		return;
	}

	if (!this->create_base_layout(this->scroller, "default"))
	{
		LOGE("Failed to create a base layout (%s)", pkg);
		return;
	}

	//Set Indicator properties
	elm_win_indicator_mode_set(this->win, ELM_WIN_INDICATOR_SHOW);
	elm_win_indicator_opacity_set(this->win, ELM_WIN_INDICATOR_OPAQUE);

	elm_win_autodel_set(this->win, EINA_TRUE);
}

ui_base_viewmgr_impl::~ui_base_viewmgr_impl()
{
	delete(this->key_listener);
}

bool ui_base_viewmgr_impl::init()
{
	return this->key_listener->init();
}

bool ui_base_viewmgr_impl::term()
{
	return this->key_listener->term();
}

bool ui_base_viewmgr_impl::activate()
{
	this->activate_top_view();
	evas_object_show(this->win);

	return true;
}

bool ui_base_viewmgr_impl::deactivate()
{
	//FIXME: based on the profile, we should app to go behind or terminate.
	if (true)
	{
		evas_object_lower(this->win);
	}
	else
	{
		delete(this->viewmgr);
	}

	return true;
}

bool ui_base_viewmgr_impl::pop_view()
{
	ui_base_view *pview = this->viewmgr->get_view(this->viewmgr->get_view_count() - 2);
	ui_base_view *view = this->viewmgr->get_last_view();

	//In case, if view doesn't have any transition effects.
	if (!strcmp(view->get_transition_style(), "none"))
	{
		this->viewmgr->pop_view_finished(pview);
		this->viewmgr->pop_view_finished(view);
		this->activate_top_view();
		return true;
	}

	//Choose an effect layout.
	Elm_Layout *effect = this->set_transition_layout(view->get_transition_style());
	if (!effect) {
		LOGE("invalid effect transition style?! = %s", view->get_transition_style());
		this->viewmgr->pop_view_finished(pview);
		this->viewmgr->pop_view_finished(view);
		this->activate_top_view();
		return true;
	}

	//Trigger Effects.
	Evas_Object *prv = this->get_base() == pview->get_base() ? pview->get_content() : pview->get_base();
	elm_layout_content_set(effect, "content", prv);

	Evas_Object *cur = this->get_base() == view->get_base() ? view->get_content() : view->get_base();
	elm_layout_content_set(effect, "pcontent", cur);

	elm_layout_signal_emit(effect, "view,pop", "viewmgr");

	this->set_indicator(pview->get_indicator());

	return true;
}

ui_base_view * ui_base_viewmgr_impl::push_view(ui_base_view *view)
{
	if (!this->viewmgr->is_activated()) return view;

	//In case, if viewmgr has one view, we skip effect.
	if (this->viewmgr->get_view_count() == 1) {
		this->activate_top_view();
		this->viewmgr->push_view_finished(view);
		return view;
	}

	ui_base_view *pview = this->viewmgr->get_view(this->viewmgr->get_view_count() - 2);

	//In case, if view doesn't have transition effect
	if (!strcmp(view->get_transition_style(), "none")) {
		this->activate_top_view();
		this->viewmgr->push_view_finished(pview);
		this->viewmgr->push_view_finished(view);
		return view;
	}

	//Choose an effect layout.
	Elm_Layout *effect = this->set_transition_layout(view->get_transition_style());
	if (!effect) {
		LOGE("invalid effect transition style?! = %s", view->get_transition_style());
		this->activate_top_view();
		this->viewmgr->push_view_finished(pview);
		this->viewmgr->push_view_finished(view);
		return view;
	}

	LOGE("content set!!!");
	//Trigger Effects.
	Evas_Object *prv = this->get_base() == pview->get_base() ? pview->get_content() : pview->get_base();
	elm_layout_content_set(effect, "pcontent", prv);

	Evas_Object *cur = this->get_base() == view->get_base() ? view->get_content() : view->get_base();
	elm_layout_content_set(effect, "content", cur);

	elm_layout_signal_emit(effect, "view,push", "viewmgr");

	this->set_indicator(view->get_indicator());

	return view;
}

/***********************************************************************************************/
/* External class Implementation                                                               */
/***********************************************************************************************/

ui_base_viewmgr::ui_base_viewmgr(const char *pkg, ui_base_key_listener *key_listener)
		: ui_iface_viewmgr()
{
	this->impl = new ui_base_viewmgr_impl(this, pkg, key_listener);
	this->impl->init();
}

ui_base_viewmgr::ui_base_viewmgr(const char *pkg)
		: ui_base_viewmgr(pkg, new ui_base_key_listener(this))
{
}

ui_base_viewmgr::~ui_base_viewmgr()
{
	this->impl->term();
	delete(this->impl);
	ui_app_exit();
}

bool ui_base_viewmgr::activate()
{
	if (!ui_iface_viewmgr::activate()) return false;
	this->impl->activate();

	return true;
}

bool ui_base_viewmgr::deactivate()
{
	if (!ui_iface_viewmgr::deactivate()) return false;
	this->impl->deactivate();

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

	return this->impl->pop_view();
}

ui_base_view * ui_base_viewmgr::push_view(ui_base_view *view)
{
	ui_iface_viewmgr::push_view(view);

	return this->impl->push_view(view);
}

bool ui_base_viewmgr::insert_view_before(ui_base_view *view, ui_base_view *before)
{
	return ui_iface_viewmgr::insert_view_before(view, before);
}

bool ui_base_viewmgr::insert_view_after(ui_base_view *view, ui_base_view *after)
{
	return ui_iface_viewmgr::insert_view_after(view, after);
}

ui_base_view *ui_base_viewmgr::get_view(unsigned int idx)
{
	return dynamic_cast<ui_base_view *>(ui_iface_viewmgr::get_view(idx));
}

ui_base_view *ui_base_viewmgr::get_last_view()
{
	return dynamic_cast<ui_base_view *>(ui_iface_viewmgr::get_last_view());
}

Evas_Object *ui_base_viewmgr::get_base()
{
	return this->impl->get_base();
}
Elm_Win *ui_base_viewmgr::get_window()
{
	return this->impl->get_window();
}
Elm_Conformant *ui_base_viewmgr::get_conformant()
{
	return this->impl->get_conformant();
}

bool ui_base_viewmgr::set_indicator(ui_view_indicator indicator)
{
	return this->impl->set_indicator(indicator);
}
