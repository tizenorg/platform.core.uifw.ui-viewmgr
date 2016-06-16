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
 *  @class ui_view
 *
 *  @ingroup efl_viewmanager
 *
  *  @brief This is a mobile standard view. This view extends ui_view and implements mobile specific behaviors for EFL view in mobile profile.
 *          Basically, ui_standard_view implements standard UI form for mobile application view. It internally constructs a layout which builds a basic form
 *          view that is consisted of title, tool and content parts. The title part locally has a left, right button parts as well as title and sub title text
 *          parts. The tool part is designed for an additional tools feature in a view. Elm_Toolbar widget could be used for this part and ui_standard_view will
 *          set up all Elm_Toolbar decorating options for users convenient. Lastly, the content part is used for main content for ui_standard_view. According
 *          to the system profile, when this view is pushed into a ui_viewmgr, it will internally create a software back key that triggers popping the view.
 *
 */
class ui_standard_view: public ui_view
{
public:
	/**
	 *  @brief A constructor for an ui_standard_view.
	 *
	 *  @param name view name.
	 */
	ui_standard_view(const char *name = NULL);

	///Destructor.
	virtual ~ui_standard_view();

	/**
	 *  @brief Replace or set a content of the view.
	 *
	 *  @param content a new content. It allows @c NULL for canceling the previous content.
	 *  @param title  title_label The label in the title area. The name of the title label part is "elm.text.title"
	 *
	 *  @return @c true if it succeeds, @c false otherwise.
	 */
	bool set_content(Evas_Object *content, const char *title = NULL);

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
	bool set_content(Evas_Object *content, const char *title, const char *subtitle, Elm_Button *title_left_btn, Elm_Button *title_right_btn);

	/**
	 *  @brief Set a title badge text.
	 *
	 *  @param text The label in the title badge area.
	 *
	 *  @return @c true if it succeeds, @c false otherwise.
	 */
	bool set_title_badge(const char *text);

	/**
	 *  @brief Set a subtitle text.
	 *
	 *  @param text The label in the subtitle area.
	 *
	 *  @return @c true if it succeeds, @c false otherwise.
	 */
	bool set_subtitle(const char *text);

	/**
	 *  @brief Set a title_left_btn.
	 *
	 *  @param title_left_btn The button in the left part of title area.
	 *
	 *  @return @c true if it succeeds, @c false otherwise.
	 */
	bool set_title_left_btn(Elm_Button *title_left_btn);

	/**
	 *  @brief Set a title_right_btn.
	 *
	 *  @param title_right_btn The button in the right part of title area.
	 *
	 *  @return @c true if it succeeds, @c false otherwise.
	 */
	bool set_title_right_btn(Elm_Button *title_right_btn);

	/**
	 *  @brief Set a title text.
	 *
	 *  @param text The label in the title area.
	 *
	 *  @return @c true if it succeeds, @c false otherwise.
	 */
	bool set_title(const char *text);

	/**
	 *  @brief Set a toolbar below title.
	 *
	 *  @param toolbar Toolbar object.
	 *
	 *  @return @c true if it succeeds, @c false otherwise.
	 */
	bool set_toolbar(Elm_Toolbar *toolbar);

	/**
	 *  @brief Control the title visible state.
	 *
	 *  @param visible title state set as visible if the given param is @c true, otherwise title area set as invisible.
	 *  @param anim title area will be shown with animation if the given param is @c true, otherwise title area will be shown without animation.
	 *
	 *  @return @c true if it succeeds, @c false otherwise.
	 */
	bool set_title_visible(bool visible, bool anim);

	/**
	 *  @brief Unset a content of the view.
	 *
	 *  @return A previous content. If it wasn't, return @c NULL.
	 */
	Evas_Object *unset_content();

	/**
	 *  @brief Unset a title left button of title area.
	 *
	 *  @return A previous content. If it wasn't, return @c NULL.
	 */
	Elm_Button *unset_title_left_btn();

	/**
	 *  @brief Unset a title right button of title area.
	 *
	 *  @return A previous content. If it wasn't, return @c NULL.
	 */
	Elm_Button *unset_title_right_btn();

	/**
	 *  @brief Unset a toolbar.
	 *
	 *  @return A previous content. If it wasn't, return @c NULL.
	 */
	Elm_Toolbar *unset_toolbar();

	/**
	 *  @brief Return a title left button of the view.
	 *
	 *  @return title left button of the view.
	 */
	Elm_Button *get_title_left_btn();

	/**
	 *  @brief Return a title right button of the view.
	 *
	 *  @return title right button of the view.
	 */
	Elm_Button *get_title_right_btn();

	/**
	 *  @brief Return a toolbar of the view.
	 *
	 *  @return toolbar of the view.
	 */
	Elm_Toolbar *get_toolbar();

	/**
	 *  @brief Get a base layout of viewmgr.
	 *
	 *  @return viewmgr's base layout object.
	 */
	virtual Evas_Object *get_base();

protected:
	/**
	 *  @brief view load state.
	 *
	 *  @note this state will be triggered by ui_iface_viewmgr.
	 *
	 */
	virtual void on_load();

	/** @brief view unload state.
	 *
	 *  @note this state will be triggered by ui_iface_viewmgr.
	 *
	 */
	virtual void on_unload();

	/** @brief toggle event block.
	 *
	 *  @note This interface is designed for toggling touch event on view transition.
	 *        ui_iface_viewmgr will call this interface for notifying event blocking toggling on transition time.
	 *
	 *  @param block @c true, blocking enable, otherwise @c false.
	 */
	virtual void set_event_block(bool block);

private:
	_UI_DECLARE_PRIVATE_IMPL(ui_standard_view);
	_UI_DISABLE_COPY_AND_ASSIGN(ui_standard_view);
};

}

#endif /* _UI_STANDARD_VIEW_H_ */
