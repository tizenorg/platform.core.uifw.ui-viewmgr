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
#include "../../../include/efl/mobile/UiMobileViewManager.h"

/***********************************************************************************************/
/* Internal class Implementation                                                               */
/***********************************************************************************************/

namespace efl_viewmanager
{

class UiStandardViewImpl
{
	friend class UiStandardView;

private:
	UiStandardView *view;
	Elm_Layout *layout;                //Base layout for view
	Elm_Toolbar *toolbar;              //Toolbar
	Elm_Button *title_left_btn;        //Title left button
	Elm_Button *title_right_btn;       //Title right button

	bool create_layout();
	bool destroy_layout();

public:
	UiStandardViewImpl(UiStandardView *view);
	~UiStandardViewImpl();

	bool set_content(Evas_Object *content, const char *title = NULL);
	bool set_content(Evas_Object *content, const char *title, const char *subtitle, Elm_Button *title_left_btn, Elm_Button *title_right_btn);
	bool set_title_badge(const char *text);
	bool set_subtitle(const char *text);
	bool set_title_left_btn(Elm_Button *title_left_btn);
	bool set_title_right_btn(Elm_Button *title_right_btn);
	bool set_title(const char *text);
	bool set_toolbar(Elm_Toolbar *toolbar);
	bool set_title_visible(bool visible, bool anim);
	void unset_content();
	Elm_Button *unset_title_left_btn();
	Elm_Button *unset_title_right_btn();
	Elm_Toolbar *unset_toolbar();
	Evas_Object *get_base();

	Elm_Button *get_title_left_btn()
	{
		return this->title_left_btn;
	}

	Elm_Button *get_title_right_btn()
	{
		return this->title_right_btn;
	}

	Elm_Toolbar *get_toolbar()
	{
		return this->toolbar;
	}
};

}

#define DEFAULT_GROUP "tizen_view/default"

#define LAYOUT_VALIDATE() if (!layout) \
							{ \
								LOGE("Layout is invalid! UiStandardView(%p)", this); \
								return false; \
							}

static void title_left_btn_del_cb(void *data, Evas *e, Evas_Object *obj, void *event_info)
{
	UiStandardView *view = static_cast<UiStandardView *>(data);
	view->unset_title_left_btn();
}

static void title_right_btn_del_cb(void *data, Evas *e, Evas_Object *obj, void *event_info)
{
	UiStandardView *view = static_cast<UiStandardView *>(data);
	view->unset_title_right_btn();
}

static void toolbar_del_cb(void *data, Evas *e, Evas_Object *obj, void *event_info)
{
	UiStandardView *view = static_cast<UiStandardView *>(data);
	view->unset_toolbar();
}

bool UiStandardViewImpl::destroy_layout()
{
	if (!this->layout) return false;
	evas_object_del(this->layout);
	this->layout = NULL;

	return true;
}

bool UiStandardViewImpl::create_layout()
{
	if (this->layout) return false;

	Elm_Layout *layout = elm_layout_add(this->view->get_parent());
	LAYOUT_VALIDATE();

	char buf[PATH_MAX];
	snprintf(buf, sizeof(buf), "%s/ui-viewmgr.edj", EDJ_PATH);

	if (!elm_layout_file_set(layout, buf, DEFAULT_GROUP))
	{
		LOGE("Failed to set file = UiStandardView(%p), path(%s), group(%s)", this, buf, DEFAULT_GROUP);
		evas_object_del(layout);
		return false;
	}
	evas_object_size_hint_weight_set(layout, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_size_hint_align_set(layout, EVAS_HINT_FILL, EVAS_HINT_FILL);

	if (this->view->get_content())
	{
		elm_object_part_content_set(layout, "elm.swallow.content", this->view->get_content());
	}

	//Set software back key, if it's needed
	UiViewmgr *viewmgr = UI_VIEWMGR;
	if (viewmgr && viewmgr->need_soft_key())
	{
		Elm_Button *prev_btn = elm_button_add(layout);

		if (!prev_btn)
		{
			LOGE("Failed to create a button = UiStandardView(%p)", this);
		} else {
			evas_object_smart_callback_add(prev_btn, "clicked", [](void *data, Evas_Object *obj, void *event_info) -> void
			{
				UiViewmgr *viewmgr = static_cast<UiViewmgr *>(data);
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

UiStandardViewImpl::UiStandardViewImpl(UiStandardView *view)
		: view(view), layout(NULL), toolbar(NULL), title_left_btn(NULL), title_right_btn(NULL)
{
}

UiStandardViewImpl::~UiStandardViewImpl()
{
	destroy_layout();
}

bool UiStandardViewImpl::set_content(Evas_Object *content, const char *title)
{
	Elm_Layout *layout = this->get_base();
	LAYOUT_VALIDATE();

	elm_object_part_content_set(layout, "elm.swallow.content", content);
	if (content)
	{
		elm_object_signal_emit(layout, "elm.state,elm.swallow.content,show", "viewmgr");
	} else {
		elm_object_signal_emit(layout, "elm.state,elm.swallow.content,hide", "viewmgr");
	}

	this->set_title(title);

	return true;
}

bool UiStandardViewImpl::set_subtitle(const char *text)
{
	Elm_Layout *layout = this->get_base();
	LAYOUT_VALIDATE();

	elm_object_part_text_set(layout, "elm.text.subtitle", text);
	if (text) elm_object_signal_emit(layout, "elm,state,subtitle,show", "viewmgr");
	else elm_object_signal_emit(layout, "elm,state,subtitle,hide", "viewmgr");

	return true;
}

bool UiStandardViewImpl::set_title_left_btn(Elm_Button *title_left_btn)
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
	evas_object_event_callback_add(title_left_btn, EVAS_CALLBACK_DEL, title_left_btn_del_cb, this->view);

	return true;
}

bool UiStandardViewImpl::set_title_right_btn(Elm_Button *title_right_btn)
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
	evas_object_event_callback_add(title_right_btn, EVAS_CALLBACK_DEL, title_right_btn_del_cb, this->view);

	return true;
}

bool UiStandardViewImpl::set_title_badge(const char *text)
{
	Elm_Layout *layout = this->get_base();
	LAYOUT_VALIDATE();

	elm_object_part_text_set(layout, "title_badge", text);
	if (text) elm_object_signal_emit(layout, "elm,state,title_badge,show", "viewmgr");
	else elm_object_signal_emit(layout, "elm,state,title_badge,hide", "viewmgr");

	return true;
}

bool UiStandardViewImpl::set_title(const char *text)
{
	Elm_Layout *layout = this->get_base();
	LAYOUT_VALIDATE();

	elm_object_part_text_set(layout, "elm.text.title", text);
	if (text) elm_object_signal_emit(layout, "elm,state,title,show", "viewmgr");
	else elm_object_signal_emit(layout, "elm,state,title,hide", "viewmgr");

	return true;
}

bool UiStandardViewImpl::set_toolbar(Elm_Toolbar *toolbar)
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
	} else {
		elm_toolbar_shrink_mode_set(toolbar, ELM_TOOLBAR_SHRINK_EXPAND);
	}
	elm_toolbar_transverse_expanded_set(toolbar, EINA_TRUE);

	//FIXME: It can be deleted when the application want to handle this property.
	//       Some of application may want to select one of toolbar item when view activated.
	elm_toolbar_select_mode_set(toolbar, ELM_OBJECT_SELECT_MODE_ALWAYS);

	elm_object_part_content_set(layout, "toolbar", toolbar);
	elm_object_signal_emit(layout, "elm,state,toolbar,show", "viewmgr");
	evas_object_event_callback_add(toolbar, EVAS_CALLBACK_DEL, toolbar_del_cb, this->view);

	return true;
}

void UiStandardViewImpl::unset_content()
{
	Elm_Layout *layout = this->get_base();
	if (!layout)
	{
		LOGE("Layout is invalid! UiStandardView(%p)", this);
		return;
	}
	elm_object_part_content_unset(layout, "elm.swallow.content");
	elm_object_signal_emit(layout, "elm.state,elm.swallow.content,hide", "viewmgr");
}

Elm_Button *UiStandardViewImpl::unset_title_left_btn()
{
	Elm_Button *btn = this->title_left_btn;
	if (!btn) return NULL;

	Elm_Layout *layout = this->get_base();
	if (!layout)
	{
		LOGE("Layout is invalid! UiStandardView(%p)", this);
		return btn;
	}

	elm_object_part_content_unset(layout, "title_left_btn");
	elm_object_signal_emit(layout, "elm,state,title_left_btn,hide", "viewmgr");
	evas_object_event_callback_del(btn, EVAS_CALLBACK_DEL, title_left_btn_del_cb);
	evas_object_hide(btn);
	this->title_left_btn = NULL;

	return btn;
}

Elm_Button *UiStandardViewImpl::unset_title_right_btn()
{
	Elm_Button *btn = this->title_right_btn;
	if (!btn) return NULL;

	Elm_Layout *layout = this->get_base();
	if (!layout)
	{
		LOGE("Layout is invalid! UiStandardView(%p)", this);
		return btn;
	}

	elm_object_part_content_unset(layout, "title_right_btn");
	elm_object_signal_emit(layout, "elm,state,title_right_btn,hide", "viewmgr");
	evas_object_event_callback_del(btn, EVAS_CALLBACK_DEL, title_right_btn_del_cb);
	evas_object_hide(btn);
	this->title_right_btn = NULL;

	return btn;
}

Elm_Toolbar *UiStandardViewImpl::unset_toolbar()
{
	Elm_Toolbar *toolbar = this->toolbar;
	if (!toolbar) return NULL;

	Elm_Layout *layout = this->get_base();
	if (!layout)
	{
		LOGE("Layout is invalid! UiStandardView(%p)", this);
		return toolbar;
	}

	elm_object_part_content_unset(layout, "toolbar");
	elm_object_signal_emit(layout, "elm,state,toolbar,hide", "viewmgr");
	evas_object_event_callback_del(toolbar, EVAS_CALLBACK_DEL, toolbar_del_cb);
	evas_object_hide(toolbar);
	this->toolbar = NULL;

	return toolbar;
}

Evas_Object *UiStandardViewImpl::get_base()
{
	if (!this->layout)
	{
		this->create_layout();
	}
	return this->layout;
}

bool UiStandardViewImpl::set_title_visible(bool visible, bool anim)
{
	//FIXME: save visible, anim value. they can be used in layout created time.
	Elm_Layout *layout = this->get_base();
	if (!layout)
	{
		LOGE("Layout is invalid! UiStandardView(%p)", this);
		return false;
	}

	if (visible)
	{
		if (anim) elm_object_signal_emit(layout, "elm,state,title,show,anim", "viewmgr");
		else elm_object_signal_emit(layout, "elm,state,title,show", "viewmgr");
	} else {
		if (anim) elm_object_signal_emit(layout, "elm,state,title,hide,anim", "viewmgr");
		else elm_object_signal_emit(layout, "elm,state,title,hide", "viewmgr");
	}

	return true;
}

/***********************************************************************************************/
/* External class Implementation                                                               */
/***********************************************************************************************/

UiStandardView::UiStandardView(const char *name)
		: UiView(name)
{
	this->impl = new UiStandardViewImpl(this);
}

UiStandardView::~UiStandardView()
{
	delete(this->impl);
}

void UiStandardView::on_load()
{
	UiView::on_load();

	Elm_Layout *layout = this->get_base();
	evas_object_show(layout);
}

void UiStandardView::on_unload()
{
	UiView::on_unload();

	Elm_Layout *layout = this->get_base();
	evas_object_hide(layout);
}

bool UiStandardView::set_content(Evas_Object *content, const char *title)
{
	UiView::set_content(content);
	return this->impl->set_content(content, title);
}

bool UiStandardView::set_subtitle(const char *text)
{
	return this->impl->set_subtitle(text);
}

bool UiStandardView::set_title_left_btn(Elm_Button *title_left_btn)
{
	return this->impl->set_title_left_btn(title_left_btn);
}

bool UiStandardView::set_title_right_btn(Elm_Button *title_right_btn)
{
	return this->impl->set_title_right_btn(title_right_btn);
}

bool UiStandardView::set_title_badge(const char *text)
{
	return this->impl->set_title_badge(text);
}

bool UiStandardView::set_title(const char *text)
{
	return this->impl->set_title(text);
}

bool UiStandardView::set_content(Evas_Object *content, const char *title, const char *subtitle, Elm_Button *title_left_btn, Elm_Button *title_right_btn)
{
	if (!this->set_content(content, title)) return false;
	if (!this->set_subtitle(subtitle)) return false;
	if (!this->set_title_left_btn(title_left_btn)) return false;
	if (!this->set_title_right_btn(title_right_btn)) return false;

	return true;
}

bool UiStandardView::set_toolbar(Elm_Toolbar *toolbar)
{
	return this->impl->set_toolbar(toolbar);
}

void UiStandardView::set_event_block(bool block)
{
	UiView::set_event_block(block);
	evas_object_freeze_events_set(this->get_base(), block);
}

Evas_Object *UiStandardView::unset_content()
{
	Evas_Object *pcontent = UiView::unset_content();
	if (!pcontent) return NULL;

	this->impl->unset_content();

	return pcontent;
}

Elm_Button *UiStandardView::unset_title_left_btn()
{
	return this->impl->unset_title_left_btn();
}

Elm_Button *UiStandardView::unset_title_right_btn()
{
	return this->impl->unset_title_right_btn();
}

Elm_Toolbar *UiStandardView::unset_toolbar()
{
	return this->impl->unset_toolbar();
}

Evas_Object *UiStandardView::get_base()
{
	return this->impl->get_base();
}

bool UiStandardView::set_title_visible(bool visible, bool anim)
{
	return this->impl->set_title_visible(visible, anim);
}

Elm_Button *UiStandardView::get_title_left_btn()
{
	return this->impl->get_title_left_btn();
}

Elm_Button *UiStandardView::get_title_right_btn()
{
	return this->impl->get_title_right_btn();
}

Elm_Toolbar *UiStandardView::get_toolbar()
{
	return this->impl->get_toolbar();
}
