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

using namespace ui_viewmanager;
using namespace efl_viewmanager;

/***********************************************************************************************/
/* Internal class Implementation                                                               */
/***********************************************************************************************/

namespace efl_viewmanager
{

class UiStandardViewImpl
{
	friend class UiStandardView;

private:
	UiStandardView *_view = NULL;
	Elm_Layout *_layout = NULL;              //Base layout for view
	Elm_Toolbar *_toolbar = NULL;            //Toolbar
	Elm_Button *_titleLeftBtn = NULL;        //Title left button
	Elm_Button *_titleRightBtn = NULL;       //Title right button
	bool _titleVisible = true;

	bool _createLayout();
	bool _destroyLayout();

public:
	explicit UiStandardViewImpl(UiStandardView *view);
	~UiStandardViewImpl();

	bool setContent(Evas_Object *content, const char *title = NULL);
	bool setContent(Evas_Object *content, const char *title, const char *subtitle, Elm_Button *titleLeftBtn, Elm_Button *titleRightBtn);
	bool setTitleBadge(const char *text);
	bool setSubtitle(const char *text);
	bool setTitleLeftBtn(Elm_Button *titleLeftBtn);
	bool setTitleRightBtn(Elm_Button *titleRightBtn);
	bool setTitle(const char *text);
	bool setToolbar(Elm_Toolbar *toolbar);
	bool setTitleVisible(bool visible, bool anim);
	void unsetContent();
	Elm_Button *unsetTitleLeftBtn();
	Elm_Button *unsetTitleRightBtn();
	Elm_Toolbar *unsetToolbar();
	Evas_Object *getBase();

	Elm_Button *getTitleLeftBtn() {
		return this->_titleLeftBtn;
	}

	Elm_Button *getTitleRightBtn() {
		return this->_titleRightBtn;
	}

	Elm_Toolbar *getToolbar() {
		return this->_toolbar;
	}
};

}

#define DEFAULT_GROUP "tizen_view/default"

#define LAYOUT_VALIDATE() if (!layout) { \
					LOGE("Layout is invalid! UiStandardView(%p)", this); \
					return false; \
				}

static void _titleLeftBtnDelCb(void *data, Evas *e, Evas_Object *obj, void *event_info)
{
	UiStandardView *view = static_cast<UiStandardView *>(data);

	view->unsetTitleLeftBtn();
}

static void _titleRightBtnDelCb(void *data, Evas *e, Evas_Object *obj, void *event_info)
{
	UiStandardView *view = static_cast<UiStandardView *>(data);

	view->unsetTitleRightBtn();
}

static void _toolbarDelCb(void *data, Evas *e, Evas_Object *obj, void *event_info)
{
	UiStandardView *view = static_cast<UiStandardView *>(data);

	view->unsetToolbar();
}

bool UiStandardViewImpl::_destroyLayout()
{
	if (!this->_layout) return false;

	evas_object_del(this->_layout);
	this->_layout = NULL;

	return true;
}

bool UiStandardViewImpl::_createLayout()
{
	if (this->_layout) return false;

	Elm_Layout *layout = elm_layout_add(this->_view->getParent());
	LAYOUT_VALIDATE();

	char buf[PATH_MAX];
	snprintf(buf, sizeof(buf), "%s/ui-viewmgr.edj", EDJ_PATH);

	if (!elm_layout_file_set(layout, buf, DEFAULT_GROUP))	{
		LOGE("Failed to set file = UiStandardView(%p), path(%s), group(%s)", this, buf, DEFAULT_GROUP);
		evas_object_del(layout);
		return false;
	}

	evas_object_size_hint_weight_set(layout, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_size_hint_align_set(layout, EVAS_HINT_FILL, EVAS_HINT_FILL);

	if (this->_view->getContent()) {
		elm_object_part_content_set(layout, "elm.swallow.content", this->_view->getContent());
	}

	//Set software back key, if it's needed
	UiViewmgr *viewmgr = UI_VIEWMGR;
	if (viewmgr && viewmgr->needSoftKey()) {
		Elm_Button *prevBtn = elm_button_add(layout);

		if (!prevBtn) {
			LOGE("Failed to create a button = UiStandardView(%p)", this);
		} else {
			evas_object_smart_callback_add(prevBtn, "clicked", [](void *data, Evas_Object *obj, void *event_info) -> void
			{
				UiViewmgr *viewmgr = static_cast<UiViewmgr *>(data);
				viewmgr->popView();
			}, viewmgr);

			elm_object_style_set(prevBtn, "tizen_view/prev_btn");
			elm_object_part_content_set(layout, "elm.swallow.prev_btn", prevBtn);
			elm_object_signal_emit(layout, "elm,state,prev_btn,show", "viewmgr");
		}
	}

	this->_layout = layout;

	return true;
}

UiStandardViewImpl::UiStandardViewImpl(UiStandardView *view)
		: _view(view)
{
}

UiStandardViewImpl::~UiStandardViewImpl()
{
	_destroyLayout();
}

bool UiStandardViewImpl::setContent(Evas_Object *content, const char *title)
{
	Elm_Layout *layout = this->getBase();
	LAYOUT_VALIDATE();

	elm_object_part_content_set(layout, "elm.swallow.content", content);

	if (content)
	{
		elm_object_signal_emit(layout, "elm.state,elm.swallow.content,show", "viewmgr");
	} else {
		elm_object_signal_emit(layout, "elm.state,elm.swallow.content,hide", "viewmgr");
	}

	this->setTitle(title);

	return true;
}

bool UiStandardViewImpl::setSubtitle(const char *text)
{
	Elm_Layout *layout = this->getBase();
	LAYOUT_VALIDATE();

	elm_object_part_text_set(layout, "elm.text.subtitle", text);

	if (text) elm_object_signal_emit(layout, "elm,state,subtitle,show", "viewmgr");
	else elm_object_signal_emit(layout, "elm,state,subtitle,hide", "viewmgr");

	return true;
}

bool UiStandardViewImpl::setTitleLeftBtn(Elm_Button *titleLeftBtn)
{
	Elm_Layout *layout = this->getBase();
	LAYOUT_VALIDATE();
	Elm_Button *pbtn;

	if (!titleLeftBtn)
	{
		pbtn = this->unsetTitleLeftBtn();
		evas_object_del(pbtn);

		return true;
	}

	pbtn = this->getTitleLeftBtn();
	evas_object_del(pbtn);

	this->_titleLeftBtn = titleLeftBtn;

	elm_object_style_set(titleLeftBtn, "tizen_view/title_left");
	elm_object_part_content_set(layout, "title_left_btn", titleLeftBtn);
	elm_object_signal_emit(layout, "elm,state,title_left_btn,show", "viewmgr");
	evas_object_event_callback_add(titleLeftBtn, EVAS_CALLBACK_DEL, _titleLeftBtnDelCb, this->_view);

	return true;
}

bool UiStandardViewImpl::setTitleRightBtn(Elm_Button *titleRightBtn)
{
	Elm_Layout *layout = this->getBase();
	Elm_Button *pbtn;

	if (!titleRightBtn)
	{
		pbtn = this->unsetTitleRightBtn();
		evas_object_del(pbtn);

		return true;
	}

	pbtn = this->getTitleRightBtn();
	evas_object_del(pbtn);

	this->_titleRightBtn = titleRightBtn;

	elm_object_style_set(titleRightBtn, "tizen_view/title_right");
	elm_object_part_content_set(layout, "title_right_btn", titleRightBtn);
	elm_object_signal_emit(layout, "elm,state,title_right_btn,show", "viewmgr");
	evas_object_event_callback_add(titleRightBtn, EVAS_CALLBACK_DEL, _titleRightBtnDelCb, this->_view);

	return true;
}

bool UiStandardViewImpl::setTitleBadge(const char *text)
{
	Elm_Layout *layout = this->getBase();
	LAYOUT_VALIDATE();

	elm_object_part_text_set(layout, "title_badge", text);

	if (text) elm_object_signal_emit(layout, "elm,state,title_badge,show", "viewmgr");
	else elm_object_signal_emit(layout, "elm,state,title_badge,hide", "viewmgr");

	return true;
}

bool UiStandardViewImpl::setTitle(const char *text)
{
	Elm_Layout *layout = this->getBase();
	LAYOUT_VALIDATE();

	elm_object_part_text_set(layout, "elm.text.title", text);

	if (text && this->_titleVisible) elm_object_signal_emit(layout, "elm,state,title,show", "viewmgr");
	else elm_object_signal_emit(layout, "elm,state,title,hide", "viewmgr");

	return true;
}

bool UiStandardViewImpl::setToolbar(Elm_Toolbar *toolbar)
{
	Elm_Layout *layout = this->getBase();
	LAYOUT_VALIDATE();

	//FIXME: inside of the unset_toolbar, it will send a toolbar,hide signal.
	//But right after it needs to send a show signal again if new toolbar is valid.
	//We don't need to send a hide signal in this case.
	Elm_Toolbar *ptoolbar = this->unsetToolbar();
	evas_object_del(ptoolbar);

	this->_toolbar = toolbar;
	if (!toolbar) return true;

	//FIXME: eeeek. check style?? :(
	if (!strcmp(elm_object_style_get(toolbar), "navigationbar")) {
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
	evas_object_event_callback_add(toolbar, EVAS_CALLBACK_DEL, _toolbarDelCb, this->_view);

	return true;
}

void UiStandardViewImpl::unsetContent()
{
	Elm_Layout *layout = this->getBase();
	if (!layout) {
		LOGE("Layout is invalid! UiStandardView(%p)", this);
		return;
	}

	elm_object_part_content_unset(layout, "elm.swallow.content");
	elm_object_signal_emit(layout, "elm.state,elm.swallow.content,hide", "viewmgr");
}

Elm_Button *UiStandardViewImpl::unsetTitleLeftBtn()
{
	Elm_Button *btn = this->_titleLeftBtn;
	if (!btn) return NULL;

	Elm_Layout *layout = this->getBase();
	if (!layout) {
		LOGE("Layout is invalid! UiStandardView(%p)", this);
		return btn;
	}

	elm_object_part_content_unset(layout, "title_left_btn");
	elm_object_signal_emit(layout, "elm,state,title_left_btn,hide", "viewmgr");
	evas_object_event_callback_del(btn, EVAS_CALLBACK_DEL, _titleLeftBtnDelCb);
	evas_object_hide(btn);
	this->_titleLeftBtn = NULL;

	return btn;
}

Elm_Button *UiStandardViewImpl::unsetTitleRightBtn()
{
	Elm_Button *btn = this->_titleRightBtn;
	if (!btn) return NULL;

	Elm_Layout *layout = this->getBase();
	if (!layout) {
		LOGE("Layout is invalid! UiStandardView(%p)", this);
		return btn;
	}

	elm_object_part_content_unset(layout, "title_right_btn");
	elm_object_signal_emit(layout, "elm,state,title_right_btn,hide", "viewmgr");
	evas_object_event_callback_del(btn, EVAS_CALLBACK_DEL, _titleRightBtnDelCb);
	evas_object_hide(btn);
	this->_titleRightBtn = NULL;

	return btn;
}

Elm_Toolbar *UiStandardViewImpl::unsetToolbar()
{
	Elm_Toolbar *toolbar = this->_toolbar;
	if (!toolbar) return NULL;

	Elm_Layout *layout = this->getBase();
	if (!layout) {
		LOGE("Layout is invalid! UiStandardView(%p)", this);
		return toolbar;
	}

	elm_object_part_content_unset(layout, "toolbar");
	elm_object_signal_emit(layout, "elm,state,toolbar,hide", "viewmgr");
	evas_object_event_callback_del(toolbar, EVAS_CALLBACK_DEL, _toolbarDelCb);
	evas_object_hide(toolbar);
	this->_toolbar = NULL;

	return toolbar;
}

Evas_Object *UiStandardViewImpl::getBase()
{
	if (!this->_layout) {
		this->_createLayout();
	}

	return this->_layout;
}

bool UiStandardViewImpl::setTitleVisible(bool visible, bool anim)
{
	this->_titleVisible = visible;

	//FIXME: save visible, anim value. they can be used in layout created time.
	Elm_Layout *layout = this->getBase();
	if (!layout) {
		LOGE("Layout is invalid! UiStandardView(%p)", this);
		return false;
	}

	if (visible) {
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
	this->_impl = new UiStandardViewImpl(this);
}

UiStandardView::~UiStandardView()
{
	delete(this->_impl);
}

void UiStandardView::onLoad()
{
	UiView::onLoad();

	Elm_Layout *layout = this->getBase();
	evas_object_show(layout);
}

void UiStandardView::onUnload()
{
	UiView::onUnload();

	Elm_Layout *layout = this->getBase();
	evas_object_hide(layout);
}

bool UiStandardView::setContent(Evas_Object *content, const char *title)
{
	UiView::setContent(content);

	return this->_impl->setContent(content, title);
}

bool UiStandardView::setSubtitle(const char *text)
{
	return this->_impl->setSubtitle(text);
}

bool UiStandardView::setTitleLeftBtn(Elm_Button *titleLeftBtn)
{
	return this->_impl->setTitleLeftBtn(titleLeftBtn);
}

bool UiStandardView::setTitleRightBtn(Elm_Button *titleRightBtn)
{
	return this->_impl->setTitleRightBtn(titleRightBtn);
}

bool UiStandardView::setTitleBadge(const char *text)
{
	return this->_impl->setTitleBadge(text);
}

bool UiStandardView::setTitle(const char *text)
{
	return this->_impl->setTitle(text);
}

bool UiStandardView::setContent(Evas_Object *content, const char *title, const char *subtitle, Elm_Button *titleLeftBtn, Elm_Button *titleRightBtn)
{
	if (!this->setContent(content, title)) return false;
	if (!this->setSubtitle(subtitle)) return false;
	if (!this->setTitleLeftBtn(titleLeftBtn)) return false;
	if (!this->setTitleRightBtn(titleRightBtn)) return false;

	return true;
}

bool UiStandardView::setToolbar(Elm_Toolbar *toolbar)
{
	return this->_impl->setToolbar(toolbar);
}

void UiStandardView::setEventBlock(bool block)
{
	UiView::setEventBlock(block);

	evas_object_freeze_events_set(this->getBase(), block);
}

Evas_Object *UiStandardView::unsetContent()
{
	Evas_Object *pcontent = UiView::unsetContent();
	if (!pcontent) return NULL;

	this->_impl->unsetContent();

	return pcontent;
}

Elm_Button *UiStandardView::unsetTitleLeftBtn()
{
	return this->_impl->unsetTitleLeftBtn();
}

Elm_Button *UiStandardView::unsetTitleRightBtn()
{
	return this->_impl->unsetTitleRightBtn();
}

Elm_Toolbar *UiStandardView::unsetToolbar()
{
	return this->_impl->unsetToolbar();
}

Evas_Object *UiStandardView::getBase()
{
	return this->_impl->getBase();
}

bool UiStandardView::setTitleVisible(bool visible, bool anim)
{
	return this->_impl->setTitleVisible(visible, anim);
}

Elm_Button *UiStandardView::getTitleLeftBtn()
{
	return this->_impl->getTitleLeftBtn();
}

Elm_Button *UiStandardView::getTitleRightBtn()
{
	return this->_impl->getTitleRightBtn();
}

Elm_Toolbar *UiStandardView::getToolbar()
{
	return this->_impl->getToolbar();
}
