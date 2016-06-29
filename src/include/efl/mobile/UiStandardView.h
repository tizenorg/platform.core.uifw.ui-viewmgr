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
#ifndef _UI_STANDARD_VIEW_H_
#define _UI_STANDARD_VIEW_H_

namespace efl_viewmanager
{

/**
 *  @class UiView
 *
 *  @ingroup efl_viewmanager
 *
  *  @brief This is a mobile standard view. This view extends UiView and implements mobile specific behaviors for EFL view in mobile profile.
 *          Basically, UiStandardView implements standard UI form for mobile application view. It internally constructs a layout which builds a basic form
 *          view that is consisted of title, tool and content parts. The title part locally has a left, right button parts as well as title and sub title text
 *          parts. The tool part is designed for an additional tools feature in a view. Elm_Toolbar widget could be used for this part and UiStandardView will
 *          set up all Elm_Toolbar decorating options for users convenient. Lastly, the content part is used for main content for UiStandardView. According
 *          to the system profile, when this view is pushed into a UiViewmgr, it will internally create a software back key that triggers popping the view.
 *
 */
class UiStandardView: public UiView
{
public:
	/**
	 *  @brief A constructor for an UiStandardView.
	 *
	 *  @param name view name.
	 */
	UiStandardView(const char *name = NULL);

	///Destructor.
	virtual ~UiStandardView();

	/**
	 *  @brief Replace or set a content of the view.
	 *
	 *  @param content a new content. It allows @c NULL for canceling the previous content.
	 *  @param title  title_label The label in the title area. The name of the title label part is "elm.text.title"
	 *
	 *  @return @c true if it succeeds, @c false otherwise.
	 */
	bool setContent(Evas_Object *content, const char *title = NULL);

	/**
	 *  @brief Replace or set a content of the view.
	 *
	 *  @param content A new content. It allows @c NULL for canceling the previous content.
	 *  @param title  The label in the title area. The name of the title label part is "elm.text.title".
	 *  @param subtitle  The label in the subtitle area. The name of the subtitle label part is "elm.text.subtitle".
	 *  @param title_left_btn The button in the left part of title area.
	 *  @param title_right_btn The button in the right part of title area.
	 *
	 *  @return @c true if it succeeds, @c false otherwise.
	 */
	bool setContent(Evas_Object *content, const char *title, const char *subtitle, Elm_Button *titleLeftBtn, Elm_Button *titleRightBtn);

	/**
	 *  @brief Set a title badge text.
	 *
	 *  @param text The label in the title badge area.
	 *
	 *  @return @c true if it succeeds, @c false otherwise.
	 */
	bool setTitleBadge(const char *text);

	/**
	 *  @brief Set a subtitle text.
	 *
	 *  @param text The label in the subtitle area.
	 *
	 *  @return @c true if it succeeds, @c false otherwise.
	 */
	bool setSubtitle(const char *text);

	/**
	 *  @brief Set a title_left_btn.
	 *
	 *  @param title_left_btn The button in the left part of title area.
	 *
	 *  @return @c true if it succeeds, @c false otherwise.
	 */
	bool setTitleLeftBtn(Elm_Button *titleLeftBtn);

	/**
	 *  @brief Set a title_right_btn.
	 *
	 *  @param title_right_btn The button in the right part of title area.
	 *
	 *  @return @c true if it succeeds, @c false otherwise.
	 */
	bool setTitleRightBtn(Elm_Button *titleRightBtn);

	/**
	 *  @brief Set a title text.
	 *
	 *  @param text The label in the title area.
	 *
	 *  @return @c true if it succeeds, @c false otherwise.
	 */
	bool setTitle(const char *text);

	/**
	 *  @brief Set a toolbar below title.
	 *
	 *  @param toolbar Toolbar object.
	 *
	 *  @return @c true if it succeeds, @c false otherwise.
	 */
	bool setToolbar(Elm_Toolbar *toolbar);

	/**
	 *  @brief Control the title visible state.
	 *
	 *  @param visible title state set as visible if the given param is @c true, otherwise title area set as invisible.
	 *  @param anim title area will be shown with animation if the given param is @c true, otherwise title area will be shown without animation.
	 *
	 *  @return @c true if it succeeds, @c false otherwise.
	 */
	bool setTitleVisible(bool visible, bool anim);

	/**
	 *  @brief Unset a content of the view.
	 *
	 *  @return A previous content. If it wasn't, return @c NULL.
	 */
	Evas_Object *unSetContent();

	/**
	 *  @brief Unset a title left button of title area.
	 *
	 *  @return A previous content. If it wasn't, return @c NULL.
	 */
	Elm_Button *unSetTitleLeftBtn();

	/**
	 *  @brief Unset a title right button of title area.
	 *
	 *  @return A previous content. If it wasn't, return @c NULL.
	 */
	Elm_Button *unSetTitleRightBtn();

	/**
	 *  @brief Unset a toolbar.
	 *
	 *  @return A previous content. If it wasn't, return @c NULL.
	 */
	Elm_Toolbar *unSetToolbar();

	/**
	 *  @brief Return a title left button of the view.
	 *
	 *  @return title left button of the view.
	 */
	Elm_Button *getTitleLeftBtn();

	/**
	 *  @brief Return a title right button of the view.
	 *
	 *  @return title right button of the view.
	 */
	Elm_Button *getTitleRightBtn();

	/**
	 *  @brief Return a toolbar of the view.
	 *
	 *  @return toolbar of the view.
	 */
	Elm_Toolbar *getToolbar();

	/**
	 *  @brief Get a base layout of viewmgr.
	 *
	 *  @return viewmgr's base layout object.
	 */
	virtual Evas_Object *getBase();

protected:
	/**
	 *  @brief view load state.
	 *
	 *  @note this state will be triggered by UiIfaceViewmgr.
	 *
	 */
	virtual void onLoad();

	/** @brief view unload state.
	 *
	 *  @note this state will be triggered by UiIfaceViewmgr.
	 *
	 */
	virtual void onUnload();

	/** @brief toggle event block.
	 *
	 *  @note This interface is designed for toggling touch event on view transition.
	 *        UiIfaceViewmgr will call this interface for notifying event blocking toggling on transition time.
	 *
	 *  @param block @c true, blocking enable, otherwise @c false.
	 */
	virtual void setEventBlock(bool block);

private:
	_UI_DECLARE_PRIVATE_IMPL(UiStandardView);
	_UI_DISABLE_COPY_AND_ASSIGN(UiStandardView);
};

}

#endif /* _UI_STANDARD_VIEW_H_ */
