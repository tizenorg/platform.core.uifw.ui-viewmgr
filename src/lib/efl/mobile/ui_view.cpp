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

#define DEFAULT_GROUP "tizen_view/default"

using namespace efl_viewmgr;
using namespace viewmgr;

typedef list<ui_popup*>::reverse_iterator popup_ritr;

#define LAYOUT_VALIDATE() if (!layout) \
							{ \
								LOGE("Layout is invalid! ui_view(%p)", this); \
								return false; \
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

void ui_view::connect_popup(ui_popup *popup)
{
	this->popup_list.push_back(popup);
}

void ui_view::disconnect_popup(ui_popup *popup)
{
	this->popup_list.remove(popup);
}

bool ui_view::deactivate_popup(bool top_one)
{
	for (popup_ritr it = this->popup_list.rbegin(); it != this->popup_list.rend(); it++)
	{
		ui_popup *popup = *it;
		if (!popup->is_activated()) continue;
		popup->on_back();
		//deactivate only one top one? or all popups?
		if (top_one) return true;
	}
	return false;
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
	LAYOUT_VALIDATE();

	char buf[PATH_MAX];
	snprintf(buf, sizeof(buf), "%s/ui-viewmgr.edj", EDJ_PATH);

	if (!elm_layout_file_set(layout, buf, DEFAULT_GROUP))
	{
		LOGE("Failed to set file = ui_view(%p), path(%s), group(%s)", this, buf, DEFAULT_GROUP);
		evas_object_del(layout);
		return false;
	}
	evas_object_size_hint_weight_set(layout, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_size_hint_align_set(layout, EVAS_HINT_FILL, EVAS_HINT_FILL);

	if (this->get_content())
	{
		elm_object_part_content_set(layout, "elm.swallow.content", this->get_content());
	}

	//Set software back key, if it's needed
	ui_viewmgr *viewmgr = UI_VIEWMGR;
	if (viewmgr && viewmgr->need_soft_key())
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
			elm_object_signal_emit(layout, "elm,state,prev_btn,show", "viewmgr");
		}
	}

	this->layout = layout;

	return true;
}

void ui_view::on_deactivate()
{
	deactivate_popup(false);
	ui_base_view::on_deactivate();
}

void ui_view::on_back()
{
	//If any popup is activated, deactivate the popup first.
	if (this->deactivate_popup(true)) return;

	if (this->menu)
	{
		if (this->menu->is_activated())
		{
			this->menu->on_back();
			return;
		}
	}
	ui_base_view::on_back();
}

ui_view::ui_view(const char *name)
		: ui_base_view(name), layout(NULL), toolbar(NULL), title_left_btn(NULL), title_right_btn(NULL), menu(NULL)
{
}

ui_view::~ui_view()
{
	if (menu) delete (this->menu);
	destroy_layout();
}

void ui_view::on_load()
{
	ui_base_view::on_load();

	Elm_Layout *layout = this->get_base();
	evas_object_show(layout);
}

void ui_view::on_unload()
{
	ui_base_view::on_unload();

	Elm_Layout *layout = this->get_base();
	evas_object_hide(layout);
}

bool ui_view::set_content(Evas_Object *content, const char *title)
{
	ui_base_view::set_content(content);

	Elm_Layout *layout = this->get_base();
	LAYOUT_VALIDATE();

	elm_object_part_content_set(layout, "elm.swallow.content", content);
	if (content)
	{
		elm_object_signal_emit(layout, "elm.state,elm.swallow.content,show", "viewmgr");
	}
	else
	{
		elm_object_signal_emit(layout, "elm.state,elm.swallow.content,hide", "viewmgr");
	}

	this->set_title(title);

	return true;
}

bool ui_view::set_subtitle(const char *text)
{
	Elm_Layout *layout = this->get_base();
	LAYOUT_VALIDATE();

	elm_object_part_text_set(layout, "elm.text.subtitle", text);
	if (text) elm_object_signal_emit(layout, "elm,state,subtitle,show", "viewmgr");
	else elm_object_signal_emit(layout, "elm,state,subtitle,hide", "viewmgr");

	return true;
}

bool ui_view::set_title_left_btn(Elm_Button *title_left_btn)
{
	Elm_Layout *layout = this->get_base();
	LAYOUT_VALIDATE();

	//FIXME: inside of the unset_title_left_btn, it will send a title_left_btn,hide signal.
	//But right after it needs to send a show signal again if new title_left_btn is valid.
	//We don't need to send a hide signal in this case.
	Elm_Button *pbtn = this->unset_title_left_btn();
	evas_object_del(pbtn);

	this->title_left_btn = title_left_btn;
	if (!title_left_btn) return true;

	elm_object_style_set(title_left_btn, "tizen_view/title_left");
	elm_object_part_content_set(layout, "title_left_btn", title_left_btn);
	elm_object_signal_emit(layout, "elm,state,title_left_btn,show", "viewmgr");
	evas_object_event_callback_add(title_left_btn, EVAS_CALLBACK_DEL, title_left_btn_del_cb, this);

	return true;
}

bool ui_view::set_title_right_btn(Elm_Button *title_right_btn)
{
	Elm_Layout *layout = this->get_base();
	LAYOUT_VALIDATE();

	//FIXME: inside of the unset_title_right_btn, it will send a title_right_btn,hide signal.
	//But right after it needs to send a show signal again if new title_right_btn is valid.
	//We don't need to send a hide signal in this case.
	Elm_Button *pbtn = this->unset_title_right_btn();
	evas_object_del(pbtn);

	this->title_right_btn = title_right_btn;
	if (!title_right_btn) return true;

	elm_object_style_set(title_right_btn, "tizen_view/title_right");
	elm_object_part_content_set(layout, "title_right_btn", title_right_btn);
	elm_object_signal_emit(layout, "elm,state,title_right_btn,show", "viewmgr");
	evas_object_event_callback_add(title_right_btn, EVAS_CALLBACK_DEL, title_right_btn_del_cb, this);

	return true;
}

bool ui_view::set_title_badge(const char *text)
{
	Elm_Layout *layout = this->get_base();
	LAYOUT_VALIDATE();

	elm_object_part_text_set(layout, "title_badge", text);
	if (text) elm_object_signal_emit(layout, "elm,state,title_badge,show", "viewmgr");
	else elm_object_signal_emit(layout, "elm,state,title_badge,hide", "viewmgr");

	return true;
}

bool ui_view::set_title(const char *text)
{
	Elm_Layout *layout = this->get_base();
	LAYOUT_VALIDATE();

	elm_object_part_text_set(layout, "elm.text.title", text);
	if (text) elm_object_signal_emit(layout, "elm,state,title,show", "viewmgr");
	else elm_object_signal_emit(layout, "elm,state,title,hide", "viewmgr");

	return true;
}

bool ui_view::set_content(Evas_Object *content, const char *title, const char *subtitle, Elm_Button *title_left_btn, Elm_Button *title_right_btn)
{
	if (!this->set_content(content, title)) return false;
	if (!this->set_subtitle(subtitle)) return false;
	if (!this->set_title_left_btn(title_left_btn)) return false;
	if (!this->set_title_right_btn(title_right_btn)) return false;

	return true;
}

bool ui_view::set_toolbar(Elm_Toolbar *toolbar)
{
	Elm_Layout *layout = this->get_base();
	LAYOUT_VALIDATE();

	//FIXME: inside of the unset_toolbar, it will send a toolbar,hide signal.
	//But right after it needs to send a show signal again if new toolbar is valid.
	//We don't need to send a hide signal in this case.
	Elm_Toolbar *ptoolbar = this->unset_toolbar();
	evas_object_del(ptoolbar);

	this->toolbar = toolbar;
	if (!toolbar) return true;

	//FIXME: eeeek. check style?? :(
	if (!strcmp(elm_object_style_get(toolbar), "navigationbar"))
	{
		elm_toolbar_shrink_mode_set(toolbar, ELM_TOOLBAR_SHRINK_SCROLL);
		elm_toolbar_align_set(toolbar, 0);
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
	elm_object_signal_emit(layout, "elm,state,toolbar,show", "viewmgr");
	evas_object_event_callback_add(toolbar, EVAS_CALLBACK_DEL, toolbar_del_cb, this);

	return true;
}

ui_menu *ui_view::on_menu_pre()
{
	if (!this->menu)
	{
		this->menu = new ui_menu(this);
	}

	if (this->menu->is_activated())
	{
		this->menu->deactivate();
		return NULL;
	}

	return this->menu;
}

void ui_view::on_menu(ui_menu *menu)
{
}

void ui_view::on_menu_post()
{
	if (!this->menu) return;
	this->menu->activate();
}

void ui_view::set_event_block(bool block)
{
	ui_base_view::set_event_block(block);
	evas_object_freeze_events_set(this->get_base(), block);
}

Evas_Object *ui_view::unset_content()
{
	Evas_Object *pcontent = ui_base_view::unset_content();
	if (!pcontent) return NULL;

	Elm_Layout *layout = this->get_base();
	if (!layout)
	{
		LOGE("Layout is invalid! ui_view(%p)", this);
		return pcontent;
	}
	elm_object_part_content_unset(layout, "elm.swallow.content");
	elm_object_signal_emit(layout, "elm.state,elm.swallow.content,hide", "viewmgr");

	return pcontent;
}

Elm_Button *ui_view::unset_title_left_btn()
{
	Elm_Button *btn = this->title_left_btn;
	if (!btn) return NULL;

	Elm_Layout *layout = this->get_base();
	if (!layout)
	{
		LOGE("Layout is invalid! ui_view(%p)", this);
		return btn;
	}

	elm_object_part_content_unset(layout, "title_left_btn");
	elm_object_signal_emit(layout, "elm,state,title_left_btn,hide", "viewmgr");
	evas_object_event_callback_del(btn, EVAS_CALLBACK_DEL, title_left_btn_del_cb);
	evas_object_hide(btn);
	this->title_left_btn = NULL;

	return btn;
}

Elm_Button *ui_view::unset_title_right_btn()
{
	Elm_Button *btn = this->title_right_btn;
	if (!btn) return NULL;

	Elm_Layout *layout = this->get_base();
	if (!layout)
	{
		LOGE("Layout is invalid! ui_view(%p)", this);
		return btn;
	}

	elm_object_part_content_unset(layout, "title_right_btn");
	elm_object_signal_emit(layout, "elm,state,title_right_btn,hide", "viewmgr");
	evas_object_event_callback_del(btn, EVAS_CALLBACK_DEL, title_right_btn_del_cb);
	evas_object_hide(btn);
	this->title_right_btn = NULL;

	return btn;
}

Elm_Toolbar *ui_view::unset_toolbar()
{
	Elm_Toolbar *toolbar = this->toolbar;
	if (!toolbar) return NULL;

	Elm_Layout *layout = this->get_base();
	if (!layout)
	{
		LOGE("Layout is invalid! ui_view(%p)", this);
		return toolbar;
	}

	elm_object_part_content_unset(layout, "toolbar");
	elm_object_signal_emit(layout, "elm,state,toolbar,hide", "viewmgr");
	evas_object_event_callback_del(toolbar, EVAS_CALLBACK_DEL, toolbar_del_cb);
	evas_object_hide(toolbar);
	this->toolbar = NULL;

	return toolbar;
}

void ui_view::on_rotate(int degree)
{
	//FIXME: see how to handle on_menu()
	ui_base_view::on_rotate(degree);
	if (!this->menu) return;
	if (!this->menu->is_activated()) return;
	this->menu->on_rotate(degree);
}

void ui_view::on_portrait()
{
	//FIXME: see how to handle on_menu()
	ui_base_view::on_portrait();
	if (!this->menu) return;
	if (!this->menu->is_activated()) return;
	this->menu->on_portrait();
}

void ui_view::on_landscape()
{
	//FIXME: see how to handle on_menu()
	ui_base_view::on_landscape();
	if (!this->menu) return;
	if (!this->menu->is_activated()) return;
	this->menu->on_landscape();
}

Evas_Object *ui_view::get_base()
{
	if (!this->layout)
	{
		this->create_layout();
	}
	return this->layout;
}

bool ui_view::set_title_visible(bool visible, bool anim)
{
	//FIXME: save visible, anim value. they can be used in layout created time.
	Elm_Layout *layout = this->get_base();
	if (!layout)
	{
		LOGE("Layout is invalid! ui_view(%p)", this);
		return false;
	}

	if (visible)
	{
		if (anim) elm_object_signal_emit(layout, "elm,state,title,show,anim", "viewmgr");
		else elm_object_signal_emit(layout, "elm,state,title,show", "viewmgr");
	}
	else
	{
		if (anim) elm_object_signal_emit(layout, "elm,state,title,hide,anim", "viewmgr");
		else elm_object_signal_emit(layout, "elm,state,title,hide", "viewmgr");
	}

	return true;
}
