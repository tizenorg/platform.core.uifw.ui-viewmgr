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
#ifndef _UI_IFACE_VIEW_H_
#define _UI_IFACE_VIEW_H_

namespace ui_viewmanager {

class ui_iface_viewmgr;

/**
 *  @class ui_iface_view
 *
 *  @internal
 *  @ingroup ui_viewmanager
 *
 *  @brief This is the base class of view. A view must have one actual view content instance which represents a view for a current screen.
 *         The content type could be any types with regards to UI systems (ie, Eo*, Layer, Window...) A derived class must implement the view body based on the
 *         actual content in its UI system. This view will be belongs to a ui_iface_viewmgr instance and dominated its state by ui_iface_viewmgr. Basically,
 *         a view communicates with ui_iface_viewmgr to active cooperatively. This class is inherited to ui_iface_rotatable class to handle view's rotation
 *         state. Also, user can handle a view's life-cycle events with these -load, unload, activate, deactivate, pause, resume, destroy-. A view may have
 *         it's own show/hide transition styles. That means, it's available that views have different show/hide effects on demands. It's not mandatory but view
 *         should describe the transitions in this class. Please be full aware of view life-cycle to understand view's behavior.
 *
 *  @warning When the transitions are finished, the view must to call ui_iface_viewmgr :: _push_finished(), ui_iface_viewmgr :: _pop_finished() in order that
 *           The ui_iface_viewmgr keeps the view states exactly.
 */
class ui_iface_view : public ui_iface_rotatable
{
public:
	/** @brief This is a constructor for initializing this view resources.
	 *
	 *  @param name view name.
	 */
	ui_iface_view(const char *name = NULL);

	///Destructor for terminating view.
	virtual ~ui_iface_view();

	/** @brief set transition style of a view.
	 *
	 *  @note @p style is reserved for supporting various kinds of view transition effects.
	 *        The actual behaviors with this transition style is up to your frameworks. Default value of the style is NULL.
	 *        and "none" represents none transition. If you don't like give any transition effects to this view, you can pass "none" as @p style.
	 *
	 *  @param style a transition style name.
	 *
	 *  @return true if the given @c style is available, otherwise false.
	 *
	 *  @warning When you override this member function, you should implement the logic to check the given style name is available or not.
	 *           If your framework doesn't support any styles then just allow a @c NULL argument and return true. Otherwise return false.
	 */
	bool set_transition_style(const char *style);

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
	const char *get_transition_style();

	/** @brief Return a name of this view.
	 *
	 *  @return name of view.
	 */
	const char *get_name();

	/** @brief Return a content instance of this view.
	 *
	 *  @return content of view.
	 */
	T get_content();

	/** @brief This is for replacing or setting a content of the view.
	 *
	 *  @note @p content is a logical object that represents a view in your framework. The actual type of the content could be translated to any certain types.
	 *        For instance, the type could be Evas_Object * in EFL and Layer * in Dali.
	 *
	 *  @param content a new content. It allows @c NULL for canceling the previous content.
	 *
	 *  @return true if it succeed, false otherwise.
	 */
	virtual bool set_content(T content);

	/** @brief This is for unsetting a content of the view.
	 *
	 *  @return A previous content. If it wasn't, return value will be @c NULL.
	 */
	virtual T unset_content();

	/** @brief Return a state of this view.
	 *
	 *  #return current state of view.
	 */
	ui_view_state get_state();

	/** @brief Return a state of removable content.
	 *
	 *  @return true if the view's content is removable, otherwise false.
	 */
	bool get_removable_content();

	/** @brief Return the indicator mode of this view.
	 *
	 *  @return indicator state of view.
	 */
	ui_view_indicator get_indicator();

	/** @brief H/W back key event occurs on view.
	 *
	 *  @note User can override this function to define application specific action when H/W back key
	 *        event occurs. otherwise current view will be popped.
	 */
	virtual void on_back();

protected:

	/** @brief toggle event block.
	 *
	 *  @note This interface is designed for toggling touch event on view transition.
	 *        ui_iface_viewmgr will call this interface for notifying event blocking toggling on transition time.
	 *
	 *  @param block @c true, when blocking is enabled, otherwise @c false.
	 */
	virtual void set_event_block(bool block);

	/** @brief view load state.
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

	/** @brief view activate state.
	 *
	 *  @note this state will be triggered by ui_iface_viewmgr.
	 *
	 */
	virtual void on_activate();

	/** @brief view deactivate state.
	 *
	 *  @note this state will be triggered by ui_iface_viewmgr.
	 *
	 */
	virtual void on_deactivate();

	/** @brief view pause state.
	 *
	 *  @note this state will be triggered by ui_iface_viewmgr.
	 *
	 */
	virtual void on_pause();

	/** @brief view resume state.
	 *
	 *  @note this state will be triggered by ui_iface_viewmgr.
	 *
	 */
	virtual void on_resume();

	/** @brief view destroy state.
	 *
	 *  @note this state will be triggered by ui_iface_viewmgr.
	 *
	 */
	virtual void on_destroy();

	/** @brief Return the state of event block.
	 *
	 *  @see set_event_block()
	 */
	bool get_event_block();

private:

	/** @brief Connect with given viewmgr.
	 *
	 *  @return true if it succeed, false otherwise.
	 *
	 *  @see get_viewmgr()
	 */
	bool set_viewmgr(ui_iface_viewmgr *viewmgr);

	/** @brief Return the viewmgr instance.
	 *
	 *  @return ui_iface_viewmgr instance.
	 *
	 *  @see set_viewmgr()
	 */
	ui_iface_viewmgr *get_viewmgr();

	_UI_DECLARE_PRIVATE_IMPL(ui_iface_view);
	_UI_DISABLE_COPY_AND_ASSIGN(ui_iface_view);
	_UI_DECLARE_FRIENDS(ui_iface_viewmgr);
};

}

#endif /* _UI_IFACE_VIEW_H_ */
