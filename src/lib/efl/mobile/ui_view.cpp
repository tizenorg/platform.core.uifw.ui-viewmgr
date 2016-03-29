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
#include "../../../include/efl/mobile/ui_viewmanager.h"

//FIXME: is it correct to define here?
#define EDJ_PATH "/usr/share/edje/ui-viewmgr/ui-viewmgr.edj"
#define GROUP "tizen_view/default"

using namespace efl_viewmgr;
using namespace viewmgr;

#define MY_VIEWMGR dynamic_cast<ui_viewmgr *>(this->get_viewmgr())
#define MY_CONTROLLER dynamic_cast<ui_controller *>(this->get_controller())

static void content_del_cb(void *data, Evas *e, Evas_Object *obj, void *event_info)
{
	ui_view *view = static_cast<ui_view *>(data);
	view->unset_content();
}

static void title_left_btn_del_cb(void *data, Evas *e, Evas_Object *obj, void *event_info)
{
	ui_view *view = static_cast<ui_view *>(data);
	view->unset_title_left_btn();
}

static void title_right_btn_del_cb(void *data, Evas *e, Evas_Object *obj, void *event_info)
{
	ui_view *view = static_cast<ui_view *>(data);
	view->unset_title_right_btn();
}

static void toolbar_del_cb(void *data, Evas *e, Evas_Object *obj, void *event_info)
{
	ui_view *view = static_cast<ui_view *>(data);
	view->unset_toolbar();
}

bool ui_view::destroy_layout()
{
	if (!this->layout) return false;
	evas_object_del(this->layout);
	this->layout = NULL;

	return true;
}

bool ui_view::create_layout()
{
	if (this->layout) return false;

	Elm_Layout *layout = elm_layout_add(this->get_parent());

	if (!layout)
	{
		LOGE("Failed to create a layout = ui_view(%p)", this);
		return false;
	}

	if (!elm_layout_file_set(layout, EDJ_PATH, GROUP))
	{
		LOGE("Failed to set file = ui_view(%p), path(%s), group(%s)", this, EDJ_PATH, GROUP);
		evas_object_del(layout);
		return false;
	}
	evas_object_size_hint_weight_set(layout, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_size_hint_align_set(layout, EVAS_HINT_FILL, EVAS_HINT_FILL);

	if (this->get_content())
	{
		elm_object_part_content_set(layout, "elm.swallow.content", CONVERT_TO_EO(this->get_content()));
	}

	//Set software back key, if it's needed
	ui_viewmgr *viewmgr = MY_VIEWMGR;
	if (viewmgr->need_soft_key())
	{
		Elm_Button *prev_btn = elm_button_add(layout);

		if (!prev_btn)
		{
			LOGE("Failed to create a button = ui_view(%p)", this);
		}
		else
		{
			evas_object_smart_callback_add(prev_btn, "clicked", [](void *data, Evas_Object *obj, void *event_info) -> void
			{
				ui_viewmgr *viewmgr = static_cast<ui_viewmgr *>(data);
				viewmgr->pop_view();
			}, viewmgr);

			elm_object_style_set(prev_btn, "tizen_view/prev_btn");
			elm_object_part_content_set(layout, "elm.swallow.prev_btn", prev_btn);
			elm_object_signal_emit(layout, "elm,state,prev_btn,show", "elm");
		}
	}

	this->layout = layout;

	return true;
}

void ui_view::on_back()
{
	if (this->menu)
	{
		if (this->menu->is_activated())
		{
			this->menu->on_back();
			return;
		}
	}
	ui_base_view ::on_back();
}

ui_view::ui_view(ui_controller *controller, const char *name)
		: ui_base_view(controller, name), layout(NULL), menu(NULL)
{
}

ui_view::ui_view(const char *name)
		: ui_view(NULL, name)
{
}

ui_view::~ui_view()
{
	if (menu) delete(this->menu);
	destroy_layout();
}

void ui_view::on_load()
{
	if (!this->layout) this->create_layout();
	ui_base_view::on_load();
}

void ui_view::on_unload()
{
	ui_base_view::on_unload();
}

bool ui_view::set_content(Evas_Object *content, const char *title)
{
	ui_base_view::set_content(content);

	if (this->layout)
	{
		elm_object_part_content_unset(this->layout, "elm.swallow.content");
		elm_object_part_content_set(this->layout, "elm.swallow.content", content);
		elm_object_part_text_set(this->layout, "elm.text.title", title);
	}
	else
	{
		LOGE("Layout is not exist!");
		return false;
	}

	evas_object_event_callback_add(this->layout, EVAS_CALLBACK_DEL, content_del_cb, this);

	return true;
}

bool ui_view::set_subtitle(const char *text)
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

bool ui_view::set_title_left_btn(Elm_Button *title_left_btn)
{
	if (this->layout)
	{
		if (title_left_btn)
		{
			elm_object_style_set(title_left_btn, "tizen_view/title_left");
		}
		elm_object_part_content_set(this->layout, "title_left_btn", title_left_btn);
		if (title_left_btn) elm_object_signal_emit(this->layout, "elm,state,title_left_btn,show", "elm");
		else elm_object_signal_emit(this->layout, "elm,state,title_left_btn,hide", "elm");

		this->title_left_btn = title_left_btn;

		evas_object_event_callback_add(this->title_left_btn, EVAS_CALLBACK_DEL, title_left_btn_del_cb, this);

		return true;
	}
	LOGE("Layout is not exist!");
	return false;
}

bool ui_view::set_title_right_btn(Elm_Button *title_right_btn)
{
	if (this->layout)
	{
		if (title_right_btn)
		{
			elm_object_style_set(title_right_btn, "tizen_view/title_right");
		}
		elm_object_part_content_set(this->layout, "title_right_btn", title_right_btn);
		if (title_right_btn) elm_object_signal_emit(this->layout, "elm,state,title_right_btn,show", "elm");
		else elm_object_signal_emit(this->layout, "elm,state,title_right_btn,hide", "elm");

		this->title_right_btn = title_right_btn;

		evas_object_event_callback_add(this->title_right_btn, EVAS_CALLBACK_DEL, title_right_btn_del_cb, this);

		return true;
	}
	LOGE("Layout is not exist!");
	return false;
}

bool ui_view::set_title_badge(const char *text)
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

bool ui_view::set_title(const char *text)
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

bool ui_view::set_content(Evas_Object *content, const char *title, const char *subtitle, Elm_Button *title_left_btn,
        Elm_Button *title_right_btn)
{
	if (!this->set_content(content)) return false;

	if (this->layout)
	{
		this->set_title(title);
		this->set_subtitle(subtitle);
		this->set_title_left_btn(title_left_btn);
		this->set_title_right_btn(title_right_btn);
	}
	else
	{
		LOGE("Layout is not exist!");
		return false;
	}

	return true;
}

bool ui_view::set_toolbar(Elm_Toolbar *toolbar)
{
	Elm_Layout *layout = this->get_base();

	//FIXME: Keep this toolbar inside of this view then set up when layout is created after.
	if (!layout)
	{
		LOGE("Layout is not exist!");
		return false;
	}

	if (!strcmp(elm_object_style_get(toolbar), "navigationbar"))
	{
		if (elm_toolbar_shrink_mode_get(toolbar) != ELM_TOOLBAR_SHRINK_SCROLL) elm_toolbar_shrink_mode_set(toolbar, ELM_TOOLBAR_SHRINK_SCROLL);
		elm_toolbar_align_set(toolbar, 0.0);
	}
	else
	{
		elm_toolbar_shrink_mode_set(toolbar, ELM_TOOLBAR_SHRINK_EXPAND);
	}
	elm_toolbar_transverse_expanded_set(toolbar, EINA_TRUE);

	//FIXME: It can be deleted when the application want to handle this property.
	//       Some of application may want to select one of toolbar item when view activated.
	elm_toolbar_select_mode_set(toolbar, ELM_OBJECT_SELECT_MODE_ALWAYS);

	elm_object_part_content_set(layout, "toolbar", toolbar);
	if (toolbar) elm_object_signal_emit(layout, "elm,state,toolbar,show", "elm");
	else elm_object_signal_emit(layout, "elm,state,toolbar,hide", "elm");

	this->toolbar= toolbar;

	evas_object_event_callback_add(this->toolbar, EVAS_CALLBACK_DEL, toolbar_del_cb, this);


	return true;
}

void ui_view::unload_content()
{
	ui_base_view::set_content(NULL);
	this->destroy_layout();
}

void ui_view::on_menu()
{
	if (this->menu && this->menu->is_activated())
	{
		this->menu->deactivate();
		return;
	}

	if (this->get_controller())
	{
		if (!this->menu)
		{
			this->menu = new ui_menu(this);
		}
		MY_CONTROLLER->on_menu(this->menu);
	}

	if (this->menu && this->menu->get_content())
	{
		this->menu->activate();
	}
}

void ui_view::set_event_block(bool block)
{
	ui_iface_view::set_event_block(block);
	evas_object_freeze_events_set(this->get_base(), block);
}

Evas_Object *ui_view::unset_content()
{
	Evas_Object *pcontent = ui_base_view::unset_content();

	if (!this->get_base()) return pcontent;

	elm_object_part_content_unset(this->get_base(), "elm.swallow.content");
	evas_object_event_callback_del(pcontent, EVAS_CALLBACK_DEL, content_del_cb);
	evas_object_hide(pcontent);

	return pcontent;
}

Elm_Button *ui_view::unset_title_left_btn()
{
	Elm_Button *title_left_btn;

	if (!this->get_base()) return NULL;

	title_left_btn = elm_object_part_content_unset(this->get_base(), "title_left_btn");
	if (title_left_btn)
		elm_object_signal_emit(this->get_base(), "elm,state,title_left_btn,hide", "elm");
	evas_object_event_callback_del(title_left_btn, EVAS_CALLBACK_DEL, title_left_btn_del_cb);
	evas_object_hide(title_left_btn);

	return title_left_btn;
}

Elm_Button *ui_view::unset_title_right_btn()
{
	Elm_Button *title_right_btn;

	if (!this->get_base()) return NULL;

	title_right_btn = elm_object_part_content_unset(this->get_base(), "title_right_btn");
	if (title_right_btn)
		elm_object_signal_emit(this->get_base(), "elm,state,title_right_btn,hide", "elm");
	evas_object_event_callback_del(title_right_btn, EVAS_CALLBACK_DEL, title_right_btn_del_cb);
	evas_object_hide(title_right_btn);

	return title_right_btn;
}

Elm_Toolbar *ui_view::unset_toolbar()
{
	Elm_Toolbar *toolbar;

	if (!this->get_base()) return NULL;

	toolbar = elm_object_part_content_unset(this->get_base(), "toolbar");
	if (toolbar)
		elm_object_signal_emit(this->get_base(), "elm,state,toolbar,hide", "elm");
	evas_object_event_callback_del(toolbar, EVAS_CALLBACK_DEL, toolbar_del_cb);
	evas_object_hide(toolbar);

	return toolbar;
}

void ui_view::on_rotate(int degree)
{
	ui_base_view::on_rotate(degree);
	if (this->menu && this->menu->is_activated())
	{
		this->menu->on_rotate(degree);
	}
}

void ui_view::on_portrait()
{
	ui_base_view::on_portrait();
	if (this->menu && this->menu->is_activated())
	{
		this->menu->on_portrait();
	}
}

void ui_view::on_landscape()
{
	ui_base_view::on_landscape();
	if (this->menu && this->menu->is_activated())
	{
		this->menu->on_landscape();
	}
}