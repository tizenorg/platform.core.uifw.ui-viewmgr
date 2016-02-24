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
#ifndef UI_VIEW_INTERFACE_H_
#define UI_VIEW_INTERFACE_H_

#include <string>

using namespace std;

typedef void* T;

namespace viewmgr {

class ui_viewmgr_interface;
class ui_controller_interface;

/**
 *  @class ui_view_interface
 *
 *  @ingroup viewmgr
 *
 *  @brief UI View Base Class. This is the base class of view. A view must have one content instance which represents a view for a current screen.
 *         UI View may have it's own show/hide transition styles. That means, it's available that views have different show/hide effects on demands.
 *         It's not mandatory but view should describe the transitions in this class.
 *
 *  @warning When the transitions are finished, the view must to call ui_viewmgr_interface :: _push_finished(), ui_viewmgr_interface :: _pop_finished() in order that
 *           The ui_viewmgr_interface keeps the view states exactly.
 */
class ui_view_interface
{
	friend class ui_viewmgr_interface;
	friend class ui_controller_interface;

private:
	/// View state definition
	enum ui_view_state
	{
		UI_VIEW_STATE_LOAD = 0,        ///< Load state
		UI_VIEW_STATE_UNLOAD,          ///< Unload state
		UI_VIEW_STATE_ACTIVE,          ///< Active state
		UI_VIEW_STATE_INACTIVE,        ///< Inactive state
		UI_VIEW_STATE_PAUSE,           ///< Pause state
		UI_VIEW_STATE_LAST
	};

	T content;                              ///< A content instance for a screen as a view.
	ui_controller_interface *controller;    ///< View life-cycle controller interface.
	string name;                            ///< View name.
	string style;                           ///< View style name.
	ui_viewmgr_interface *viewmgr;          ///< Viewmgr which this view belongs to.
	ui_view_state state;                    ///< View state.
	ui_view_indicator indicator;            ///< View indicator mode.
	bool event_block;                       ///< State of event block.
	bool removable_content;                 ///< When this value is true, view removes it's content internally on unload state.

protected:

	/** @brief toggle event block.
	 *
	 *  @note This interface is designed for toggling touch event on view transition.
	 *        ui_viewmgr_interface will call this interface for notifying event blocking toggling on transition time.
	 *
	 *  @param block @c true, when blocking is enabled, otherwise @c false.
	 */
	virtual void set_event_block(bool block);

	/** @brief view load state.
	 *
	 *  @note this state will be triggered by ui_viewmgr_interface.
	 *
	 *  @see ui_controller_interface for this state in detail.
	 */
	virtual void load();

	/** @brief view unload state.
	 *
	 *  @note this state will be triggered by ui_viewmgr_interface.
	 *
	 *  @see ui_controller_interface for this state in detail.
	 */
	virtual void unload();

	/** @brief view active state.
	 *
	 *  @note this state will be triggered by ui_viewmgr_interface.
	 *
	 *  @see ui_controller_interface for this state in detail.
	 */
	virtual void active();

	/** @brief view inactive state.
	 *
	 *  @note this state will be triggered by ui_viewmgr_interface.
	 *
	 *  @see ui_controller_interface for this state in detail.
	 */
	virtual void inactive();

	/** @brief view pause state.
	 *
	 *  @note this state will be triggered by ui_viewmgr_interface.
	 *
	 *  @see ui_controller_interface for this state in detail.
	 */
	virtual void pause();

	/** @brief view resume state.
	 *
	 *  @note this state will be triggered by ui_viewmgr_interface.
	 *
	 *  @see ui_controller_interface for this state in detail.
	 */
	virtual void resume();

	/** @brief view destroy state.
	 *
	 *  @note this state will be triggered by ui_viewmgr_interface.
	 *
	 *  @see ui_controller_interface for this state in detail.
	 */
	virtual void destroy();

	//Make this view's content as NULL, then destroy content.
	virtual void unload_content() = 0;

	/** @brief Return the state of event block.
	 *
	 *  @see set_event_block()
	 */
	bool get_event_block()
	{
		return this->event_block;
	}

	/** @brief Return a viewmgr which this view is belonging to.
	 */
	ui_viewmgr_interface *get_viewmgr()
	{
		return this->viewmgr;
	}

	/** @brief This is for replacing or setting a controller of the view.
	 *
	 *  @return A previous controller. If it wasn't, the return value will be @c NULL.
	 *  @note this state will be triggered by ui_viewmgr_interface.
	 *  @param controller a new controller. It allows @c NULL for canceling the previous controller.
	 *
	 *  @warning Be aware deletion of controller passed here will be taken cover by ui_view_interface.
	 *           If you want to keep the controller for any reasons, please unset it using set_controller() before ui_view_interface is deleted.
	 */
	ui_controller_interface* set_controller(ui_controller_interface *controller);

	/** @brief Return a controller of this view.
	 *
	 *  @see set_controller()
	 */
	const ui_controller_interface* get_controller()
	{
		return this->controller;
	}

public:
	/** @brief This is a constructor for initializing this view resources.
	 *
	 *  @param content A content instance for a screen as a view.
	 *  @param controller view life-cycle controller interface.
	 *  @param name view name.
	 *
	 *  @warning Be aware the deletion of controller passed here will be covered by ui_view_interface.
	 *           If you want to keep it for any reasons, please unset it using set_controller() before ui_view_interface is deleted.
	 */
	ui_view_interface(T content, ui_controller_interface *controller, const char *name, const char *style = NULL);
	///Constructor for initializing with controller.
	ui_view_interface(ui_controller_interface *controller, const char *name = NULL, const char *style = NULL);
	///Constructor for initializing with name.
	ui_view_interface(const char *name = NULL);

	///Destructor for terminating view.
	virtual ~ui_view_interface();

	/** @brief This is for replacing or setting a content of the view.
	 *
	 *  @note @p content is a logical object that represents a view in your framework. The actual type of the content could be translated to any certain types.
	 *        For instance, the type could be Evas_Object * in EFL and Layer * in Dali.
	 *
	 *  @param content a new content. It allows @c NULL for canceling the previous content.
	 *
	 *  @return A previous content. If it wasn't, return value will be @c NULL.
	 */
	T set_content(T content);

	/** @brief set style of the view.
	 *
	 *  @note style is reserved for supporting various kinds of view as well as it's transition effects.
	 *        The actual behaviors with this style is up to your frameworks. Default value of the style is NULL.
	 *
	 *  @param style a new style name.
	 *
	 *  @return true if the given @c style is available, otherwise false.
	 *
	 *  @warning When you override this member function, you should implement the logic to check the given style name is available or not.
	 *           If your framework doesn't support any styles then just allow a @c NULL argument and return true. Otherwise return false.
	 */
	bool set_style(const char *style);

	/** @brief set name of the view.
	 *
	 *  @note A view can gets a specific name. default value of the name is NULL.
	 *
	 *  @param name a new name of view.
	 *
	 *  @return true if the given @c name is available, otherwise false.
	 *
	 *  @warning When you override this member function, you should check the name duplicate with other view or not.
	 */
	bool set_name(const char *name);

	/** @brief set content removable.
	 *
	 *  @param removable if @p removable is @c true, content of this view will be removed on unload state. @c false otherwise.
 	 *
	 *  @warning You should not remove a view content manually on unload status if removable content is set.
	 */
	void set_removable_content(bool removable);

	/** @brief set the indicator of the view with mode.
	 *
	 *  @param indicator The mode to set, one of #ui_view_indicator.
	 */
	void set_indicator(ui_view_indicator indicator);

	/** @brief Return a style name of this view.
	 *
	 *  @return style name of view.
	 */
	const char *get_style()
	{
		return this->style.c_str();
	}

	/** @brief Return a name of this view.
	 *
	 *  @return name of view.
	 */
	const char *get_name()
	{
		return this->name.c_str();
	}

	/** @brief Return a content instance of this view.
	 *
	 *  @return content of view.
	 */
	T get_content()
	{
		return this->content;
	}

	/** @brief Return a state of this view.
	 *
	 *  #return current state of view.
	 */
	ui_view_state get_state()
	{
		return this->state;
	}


	/** @brief Return a state of removeable content.
	 *
	 *  @return true if the view's content is removable, otherwise false.
	 */
	bool get_removable_content()
	{
		return this->removable_content;
	}

	/** @brief Return the indicator mode of this view.
	 *
	 *  @return indicator state of view.
	 */
	ui_view_indicator get_indicator()
	{
		return this->indicator;
	}
};

}

#endif /* UI_VIEW_INTERFACE_H_ */
