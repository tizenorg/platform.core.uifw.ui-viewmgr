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
#include "../../include/efl/UiBaseViewManager.h"

using namespace ui_viewmanager;
using namespace efl_viewmanager;
using namespace std;

/***********************************************************************************************/
/* Internal class Implementation                                                               */
/***********************************************************************************************/
namespace efl_viewmanager
{

class UiBaseViewmgrImpl
{
	friend class UiBaseViewmgr;

private:
	UiBaseViewmgr *_viewmgr = NULL;
	Elm_Win *_win = NULL;                                      //This is acting like a base object of viewmgr.
	Elm_Conformant *_conform = NULL;                           //Conformant for viewmgr.
	Elm_Scroller *_scroller = NULL;                            //Scroller for viewmgr.
	Elm_Layout *_layout = NULL;                                //Viewmgr's base layout.
	UiBaseKeyListener *_keyListener = NULL;                    //HW Key Handler such as "BACK" key...
	UiViewIndicator _indicator = UI_VIEW_INDICATOR_DEFAULT;    //Mode of indicator.
	string _transitionStyle = "default";                       //Current transition effect style name
	map<string, Elm_Layout *> _effectMap;                      //Map for effect layouts.

	Elm_Layout *_setTransitionLayout(string transitionStyle);

	bool _createConformant(Elm_Win *win);
	bool _createScroller(Elm_Conformant *conform);
	bool _createBaseLayout(Elm_Scroller *scroller, const char *style);
	bool _setIndicator(UiViewIndicator indicator);
	void _activateTopView();
	bool _init();
	bool _term();

public:
	UiBaseViewmgrImpl(UiBaseViewmgr *viewmgr, const char *pkg, UiBaseKeyListener *keyListener);
	~UiBaseViewmgrImpl();

	bool activate();
	bool deactivate();
	UiBaseView *pushView(UiBaseView *view);
	bool popView();
	bool insertViewBefore(UiBaseView *view, UiBaseView *before);
	bool insertViewAfter(UiBaseView *view, UiBaseView *after);

	Evas_Object *getBase() {
		return this->_layout;
	}

	Elm_Win *getWindow() {
		return this->_win;
	}

	Elm_Conformant *getConformant() {
		return this->_conform;
	}
};

}

bool UiBaseViewmgrImpl::_createBaseLayout(Elm_Scroller *scroller, const char *style)
{
	char edjPath[PATH_MAX];
	char groupName[128];

	Elm_Layout *layout = elm_layout_add(scroller);
	if (!layout) return false;

	snprintf(groupName, sizeof(groupName), "transition/%s", style);
	snprintf(edjPath, sizeof(edjPath), "%s/ui-viewmgr.edj", EDJ_PATH);
	elm_layout_file_set(layout, edjPath, groupName);
	evas_object_size_hint_weight_set(layout, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_size_hint_align_set(layout, EVAS_HINT_FILL, EVAS_HINT_FILL);
	elm_object_content_set(scroller, layout);

	//Push Finished Event
	elm_layout_signal_callback_add(layout, "push,finished", "viewmgr",
			[](void *data, Evas_Object *obj, const char *emission, const char *source) -> void
			{
				UiBaseViewmgr *viewmgr = static_cast<UiBaseViewmgr *>(data);
				UiBaseView *pview = viewmgr->getView(viewmgr->getViewCount() - 2);
				UiBaseView *view = viewmgr->getLastView();
				if (pview) viewmgr->pushViewFinished(pview);
				if (view) viewmgr->pushViewFinished(view);
			},
			this->_viewmgr);

	//Pop Finished Event
	elm_layout_signal_callback_add(layout, "pop,finished", "viewmgr",
			[](void *data, Evas_Object *obj, const char *emission, const char *source) -> void
			{
				UiBaseViewmgr *viewmgr = static_cast<UiBaseViewmgr *>(data);
				UiBaseView *pview = viewmgr->getView(viewmgr->getViewCount() - 2);
				UiBaseView *view = viewmgr->getLastView();
				if (pview) viewmgr->popViewFinished(pview);
				if (view) viewmgr->popViewFinished(view);
			},
			this->_viewmgr);

	this->_layout = layout;

	return true;
}

Elm_Layout *UiBaseViewmgrImpl::_setTransitionLayout(string transitionStyle)
{
	Elm_Layout *effectLayout = NULL;
	Elm_Layout *pcontent;

	pcontent = elm_object_part_content_unset(this->getBase(), "pcontent");
	if (pcontent) evas_object_hide(pcontent);
	elm_object_part_content_unset(this->getBase(), "content");

	if (transitionStyle.compare(this->_transitionStyle) == 0) return this->_layout;

	if (_effectMap.size()) effectLayout = _effectMap.find(transitionStyle)->second;

	//Scroller content change to current effect layout and change to hide prev layout.
	Elm_Layout *playout = elm_object_part_content_unset(this->_scroller, NULL);
	evas_object_hide(playout);

	if (!effectLayout) {
		//Create and add effect_layouts in map here.
		//FIXME: If we have to support many effects, this logic should be changed.
		_effectMap.insert(pair<string, Elm_Layout *>("default", this->_layout));
		this->_createBaseLayout(this->_scroller, transitionStyle.c_str());
		_effectMap.insert(pair<string, Elm_Layout *>(transitionStyle, this->_layout));
	} else {
		elm_object_content_set(this->_scroller, effectLayout);

		this->_layout = effectLayout;
	}

	this->_transitionStyle = transitionStyle;

	return this->_layout;
}

void UiBaseViewmgrImpl::_activateTopView()
{
	Evas_Object *pcontent = elm_object_part_content_unset(this->getBase(), "content");
	if (pcontent) evas_object_hide(pcontent);

	UiBaseView *view = this->_viewmgr->getLastView();

	//In case of UiBaseView, it doesn't have any base form. It uses viewmgr base instead.
	Evas_Object *content;
	if (view->getBase() == this->getBase()) {
		content = view->getContent();
	} else {
		content = view->getBase();
	}

	elm_object_part_content_set(this->getBase(), "content", content);

	this->_setIndicator(view->getIndicator());
}

//FIXME: How to deal with indicator in other UI framework? Dali? Volt?
//Is it possible make this interface common?
bool UiBaseViewmgrImpl::_setIndicator(UiViewIndicator indicator)
{
	if (this->_indicator == indicator) return false;
	this->_indicator = indicator;

	Elm_Win *window = this->getWindow();
	Elm_Conformant *conform = this->getConformant();

	switch (indicator) {
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

bool UiBaseViewmgrImpl::_createConformant(Elm_Win *win)
{
	Elm_Conformant *conform = elm_conformant_add(win);
	if (!conform) return false;

	evas_object_size_hint_weight_set(conform, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	elm_win_resize_object_add(win, conform);
	elm_win_conformant_set(win, EINA_TRUE);
	evas_object_show(conform);

	this->_conform = conform;

	return true;
}

bool UiBaseViewmgrImpl::_createScroller(Elm_Conformant *conform)
{
	Elm_Scroller *scroller = elm_scroller_add(conform);
	if (!scroller) return false;

	elm_scroller_policy_set(scroller, ELM_SCROLLER_POLICY_AUTO, ELM_SCROLLER_POLICY_AUTO);
	evas_object_size_hint_weight_set(scroller, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_size_hint_align_set(scroller, EVAS_HINT_FILL, EVAS_HINT_FILL);

	elm_object_content_set(conform, scroller);

	this->_scroller = scroller;

	return true;
}

UiBaseViewmgrImpl::UiBaseViewmgrImpl(UiBaseViewmgr *viewmgr, const char *pkg, UiBaseKeyListener *keyListener)
		: _viewmgr(viewmgr), _keyListener(keyListener)
{
	if (!pkg) {
		LOGE("Invalid package name");
		return;
	}

	//Window
	this->_win = elm_win_util_standard_add(pkg, pkg);

	if (!this->_win) {
		LOGE("Failed to create a window (%s)", pkg);
		return;
	}

	//FIXME: Make a method? to set available rotation degree.
	//Set window rotation
	if (elm_win_wm_rotation_supported_get(this->_win)) {
		int rots[4] =
		{ 0, 90, 180, 270 };
		elm_win_wm_rotation_available_rotations_set(this->_win, (const int *) (&rots), 4);
	}
	evas_object_smart_callback_add(this->_win, "wm,rotation,changed",
			[](void *data, Evas_Object *obj, void *event_info) -> void
			{
				int rot = elm_win_rotation_get(obj);

				UiBaseViewmgr *viewmgr = static_cast<UiBaseViewmgr *>(data);
				UiBaseView *view = viewmgr->getLastView();
				view->onRotate(rot);

				//FIXME: Change this configurable?
				if (rot == 0 || rot == 180) view->onPortrait();
				else view->onLandscape();
			}
			, this->_viewmgr);
	//Window is requested to delete.
	evas_object_smart_callback_add(this->_win, "delete,request",
			[](void *data, Evas_Object *obj, void *event_info) -> void
			{
				UiBaseViewmgr *viewmgr = static_cast<UiBaseViewmgr*>(data);
				delete(viewmgr);
			},
			this->_viewmgr);

	//FIXME: Make conformant configurable?
	if (!this->_createConformant(this->_win)) {
		LOGE("Failed to create a conformant (%s)", pkg);
		return;
	}

	if (!this->_createScroller(this->_conform)) {
		LOGE("Failed to create a scroller (%s)", pkg);
		return;
	}

	if (!this->_createBaseLayout(this->_scroller, "default")) {
		LOGE("Failed to create a base layout (%s)", pkg);
		return;
	}

	//Set Indicator properties
	elm_win_indicator_mode_set(this->_win, ELM_WIN_INDICATOR_SHOW);
	elm_win_indicator_opacity_set(this->_win, ELM_WIN_INDICATOR_OPAQUE);

	elm_win_autodel_set(this->_win, EINA_TRUE);
}

UiBaseViewmgrImpl::~UiBaseViewmgrImpl()
{
	delete(this->_keyListener);
}

bool UiBaseViewmgrImpl::_init()
{
	return this->_keyListener->init();
}

bool UiBaseViewmgrImpl::_term()
{
	return this->_keyListener->term();
}

bool UiBaseViewmgrImpl::activate()
{
	this->_activateTopView();
	evas_object_show(this->_win);

	return true;
}

bool UiBaseViewmgrImpl::deactivate()
{
	//FIXME: based on the profile, we should app to go behind or terminate.
	if (true) {
		evas_object_lower(this->_win);
	} else {
		delete(this->_viewmgr);
	}

	return true;
}

bool UiBaseViewmgrImpl::popView()
{
	UiBaseView *pview = this->_viewmgr->getView(this->_viewmgr->getViewCount() - 2);
	UiBaseView *view = this->_viewmgr->getLastView();

	//In case, if view doesn't have any transition effects.
	if (!strcmp(view->getTransitionStyle(), "none")) {
		this->_viewmgr->popViewFinished(pview);
		this->_viewmgr->popViewFinished(view);
		this->_activateTopView();
		return true;
	}

	//Choose an effect layout.
	Elm_Layout *effect = this->_setTransitionLayout(view->getTransitionStyle());
	if (!effect) {
		LOGE("invalid effect transition style?! = %s", view->getTransitionStyle());
		this->_viewmgr->popViewFinished(pview);
		this->_viewmgr->popViewFinished(view);
		this->_activateTopView();
		return true;
	}

	//Trigger Effects.
	Evas_Object *prv = this->getBase() == pview->getBase() ? pview->getContent() : pview->getBase();
	elm_layout_content_set(effect, "content", prv);

	Evas_Object *cur = this->getBase() == view->getBase() ? view->getContent() : view->getBase();
	elm_layout_content_set(effect, "pcontent", cur);

	elm_layout_signal_emit(effect, "view,pop", "viewmgr");

	this->_setIndicator(pview->getIndicator());

	return true;
}

UiBaseView * UiBaseViewmgrImpl::pushView(UiBaseView *view)
{
	if (!this->_viewmgr->isActivated()) return view;

	//In case, if viewmgr has one view, we skip effect.
	if (this->_viewmgr->getViewCount() == 1) {
		this->_activateTopView();
		this->_viewmgr->pushViewFinished(view);
		return view;
	}

	UiBaseView *pview = this->_viewmgr->getView(this->_viewmgr->getViewCount() - 2);

	//In case, if view doesn't have transition effect
	if (!strcmp(view->getTransitionStyle(), "none")) {
		this->_activateTopView();
		this->_viewmgr->pushViewFinished(pview);
		this->_viewmgr->pushViewFinished(view);
		return view;
	}

	//Choose an effect layout.
	Elm_Layout *effect = this->_setTransitionLayout(view->getTransitionStyle());
	if (!effect) {
		LOGE("invalid effect transition style?! = %s", view->getTransitionStyle());
		this->_activateTopView();
		this->_viewmgr->pushViewFinished(pview);
		this->_viewmgr->pushViewFinished(view);
		return view;
	}

	//Trigger Effects.
	Evas_Object *prv = this->getBase() == pview->getBase() ? pview->getContent() : pview->getBase();
	elm_layout_content_set(effect, "pcontent", prv);

	Evas_Object *cur = this->getBase() == view->getBase() ? view->getContent() : view->getBase();
	elm_layout_content_set(effect, "content", cur);

	elm_layout_signal_emit(effect, "view,push", "viewmgr");

	this->_setIndicator(view->getIndicator());

	return view;
}

/***********************************************************************************************/
/* External class Implementation                                                               */
/***********************************************************************************************/

UiBaseViewmgr::UiBaseViewmgr(const char *pkg, UiBaseKeyListener *key_listener)
		: UiIfaceViewmgr()
{
	this->_impl = new UiBaseViewmgrImpl(this, pkg, key_listener);
	this->_impl->_init();
}

UiBaseViewmgr::UiBaseViewmgr(const char *pkg)
		: UiBaseViewmgr(pkg, new UiBaseKeyListener(this))
{
}

UiBaseViewmgr::~UiBaseViewmgr()
{
	this->_impl->_term();
	delete(this->_impl);
	ui_app_exit();
}

bool UiBaseViewmgr::activate()
{
	if (!UiIfaceViewmgr::activate()) return false;
	this->_impl->activate();

	return true;
}

bool UiBaseViewmgr::deactivate()
{
	if (!UiIfaceViewmgr::deactivate()) return false;
	this->_impl->deactivate();

	return true;
}

bool UiBaseViewmgr::popView()
{
	if (this->getViewCount() == 1) {
		this->deactivate();
		return true;
	}

	if(!UiIfaceViewmgr::popView()) {
		return false;
	}

	return this->_impl->popView();
}

UiBaseView * UiBaseViewmgr::pushView(UiBaseView *view)
{
	UiIfaceViewmgr::pushView(view);

	return this->_impl->pushView(view);
}

bool UiBaseViewmgr::insertViewBefore(UiBaseView *view, UiBaseView *before)
{
	return UiIfaceViewmgr::insertViewBefore(view, before);
}

bool UiBaseViewmgr::insertViewAfter(UiBaseView *view, UiBaseView *after)
{
	return UiIfaceViewmgr::insertViewAfter(view, after);
}

UiBaseView *UiBaseViewmgr::getView(unsigned int idx)
{
	return dynamic_cast<UiBaseView *>(UiIfaceViewmgr::getView(idx));
}

UiBaseView *UiBaseViewmgr::getView(const char *name)
{
	return dynamic_cast<UiBaseView *>(UiIfaceViewmgr::getView(name));
}

UiBaseView *UiBaseViewmgr::getLastView()
{
	return dynamic_cast<UiBaseView *>(UiIfaceViewmgr::getLastView());
}

Evas_Object *UiBaseViewmgr::getBase()
{
	return this->_impl->getBase();
}
Elm_Win *UiBaseViewmgr::getWindow()
{
	return this->_impl->getWindow();
}
Elm_Conformant *UiBaseViewmgr::getConformant()
{
	return this->_impl->getConformant();
}

bool UiBaseViewmgr::setIndicator(UiViewIndicator indicator)
{
	return this->_impl->_setIndicator(indicator);
}
