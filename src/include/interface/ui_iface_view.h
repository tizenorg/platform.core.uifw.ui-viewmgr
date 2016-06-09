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
 *  @ingroup ui_viewmanager
 *
 *  @brief This is a base class of view. A view must have one actual view content instance which represents a view for a current screen.
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
	/**
	 *  @brief This is a constructor for initializing this view resources.
	 *
	 *  @param name view name.
	 */
	ui_iface_view(const char *name = NULL);

	///Destructor.
	virtual ~ui_iface_view();

	/**
	 *  @brief Set transition style of a view.
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

	/**
	 *  @brief Set name of the view.
	 *
	 *  @note A view can get a specific name. default value of the name is NULL.
	 *
	 *  @param name a new name of view.
	 *
	 *  @return true if the given @c name is available, otherwise false.
	 *
	 *  @warning When you override this member function, you should check the name duplicate with other view or not.
	 */
	bool set_name(const char *name);

	/**
	 *  @brief Set content removable.
	 *
	 *  @param removable if @p removable is @c true, content of this view will be removed on unload state. @c false otherwise.
 	 *
	 *  @warning You should not remove a view content manually on unload status if removable content is set.
	 */
	void set_removable_content(bool removable);

	/**
	 *  @brief Set the indicator of the view with mode.
	 *
	 *  @param indicator The mode to set, one of #ui_view_indicator.
	 */
	void set_indicator(ui_view_indicator indicator);

	/**
	 *  @brief Return a style name of this view.
	 *
	 *  @return style name of view.
	 */
	const char *get_transition_style();

	/**
	 *  @brief Return a name of this view.
	 *
	 *  @return name of view.
	 */
	const char *get_name();

	/**
	 *  @brief Return a content instance of this view.
	 *
	 *  @return content of view.
	 */
	T get_content();

	/**
	 *  @brief This is for replacing or setting a content of the view.
	 *
	 *  @note @p content is a logical object that represents a view in your framework. The actual type of the content could be translated to any certain types.
	 *        For instance, the type could be Evas_Object * in EFL and Layer * in Dali.
	 *
	 *  @param content a new content. It allows @c NULL for canceling the previous content.
	 *
	 *  @return true if it succeed, false otherwise.
	 */
	virtual bool set_content(T content);

	/**
	 *  @brief This is for unsetting a content of the view.
	 *
	 *  @return A previous content. If it wasn't, return value will be @c NULL.
	 */
	virtual T unset_content();

	/**
	 *  @brief Return a state of this view.
	 *
	 *  @return current state of view.
	 */
	ui_view_state get_state();

	/**
	 *  @brief Return a state of removable content.
	 *
	 *  @return true if the view's content is removable, otherwise false.
	 */
	bool get_removable_content();

	/**
	 *  @brief Return the indicator mode of this view.
	 *
	 *  @return indicator state of view.
	 */
	ui_view_indicator get_indicator();

	/**
	 *  @brief The H/W back key event occurs on view.
	 *
	 *  @note User can override this function to define application specific action when H/W back key
	 *        event occurs. otherwise current view will be popped.
	 */
	virtual void on_back();

protected:
	/**
	 *  @brief Toggle event block.
	 *
	 *  @note This interface is designed for toggling touch event on view transition.
	 *        ui_iface_viewmgr will call this interface for notifying event blocking toggling on transition time.
	 *
	 *  @param block @c true, when blocking is enabled, otherwise @c false.
	 *
	 *  @see get_event_block()
	 */
	virtual void set_event_block(bool block);

	/**
	 *  @brief Return the state of event block.
	 *
	 *  @return true if the event block enabled, otherwise false.
	 *
	 *  @see set_event_block()
	 */
	bool get_event_block();

	/**
	 *  @brief View load state.
	 *
	 *  @note A view of this state is moving onto the screen. Get ready for this view. Generally, you could prepare this view's content here and set them to
	 *        this view. In the most cases, this on_load() will be triggered with this step. load -> deactivated -> activated. Tihs on_load() will be triggered
	 *        only when view has not any content yet.
	 */
	virtual void on_load();

	/**
	 *  @brief View unload state.
	 *
	 *  @note Remove resources (contents) with regards to this view for saving memory. Otherwise, you could keep those resources (contents) for later access.
	 *        Removing resources might be better in point of performance view. It's up to your scenario. on_unload() will be triggered just right before
	 *        the view is going to be deleted by popping or by somehow. Also, on_unload() will be triggered when this view is pushed behind other views.
	 */
	virtual void on_unload();

	/**
	 *  @brief View activate state.
 	 *
 	 *  @note Generally, a view will be activated when show-transition is finished. From whatever its state, when the view comes on the screen,
 	 *        on_activate() will be triggered. In the most cases, on_activate() will be triggered with this step. load -> deactivate -> activate
	 */
	virtual void on_activate();

	/**
	 *  @brief View deactivate state.
	 *
	 *  @note Get ready for unload. Hide transition may be triggered at this point. If the system blocks application running in some cases such as phone call,
	 *        system notification, application switching ..., Deactivate state will be triggered. Also, when a view is going to be popped or destroyed,
	 *        on_deactivate() will be triggered. Lastly, when a new view is pushed, so if it becomes invisible state by other views, on_deactivate() will be
	 *        triggered also.
	 */
	virtual void on_deactivate();

	/**
	 *  @brief View pause state.
	 *
	 *  @note Some UI controls such as Popup or a Menu popup usually blocks views. For those scenarios, this blocked view would be paused and shouldn't be
	 *        interactive with users. However, still it would be visible in some way (ie, half transparency). For this, this Pause will be triggered.
	 *        If the view is already deactivated or under the unload state, the pause won't be called.
	 */
	virtual void on_pause();

	/**
	 *  @brief View resume state.
	 *
	 *  @note When a view is returns to the activate state from pause state, this on_resume() will be triggered. For instance, a Popup is dismissed.
	 */
	virtual void on_resume();

	/**
	 *  @brief View destroy state.
	 *
	 *  @note When this view is on destroyed by popping or by somehow, destroy will be triggered. Most of the cases, you can free your personal resources for
	 *        the view because this view instance will be totally freed at the end of destroy. Be aware that you must not request any view functions on this
	 *        state.
	 */
	virtual void on_destroy();

	/**
	 *  @brief Low Memory Event
	 *
	 *  @note This event function is responsible for saving data in the main memory to a persistent memory or storage to avoid data loss in case the Tizen
	 *        platform Low Memory Killer kills your application to get more free memory. This event function must also release any cached data in the main
	 *        memory to secure more free memory.
	 */
	virtual void on_low_memory();

	/**
	 *  @brief Low Battery Event
	 *
	 *  @note This event function is responsible for saving data in the main memory to a persistent memory or storage to avoid data loss in case the power goes
	 *        off completely. This event function must also stop heavy CPU consumption or power consumption activities to save the remaining power.
	 */
	virtual void on_low_battery();

	/**
	 *  @brief Region Changed Event
	 *
	 *  @note This event function is responsible for refreshing the display into the new time zone.
	 */
	virtual void on_region_changed(const char *region);

	/**
	 *  @brief Language Changed Event
	 *
	 *  @note This event function is responsible for refreshing the display into the new language.
	 */
	virtual void on_language_changed(const char *language);

private:
	/**
	 *  @brief Connect with given viewmgr.
	 *
	 *  @param viewmgr The instance of viewmgr.
	 *
	 *  @return true if it succeed, false otherwise.
	 *
	 *  @see get_viewmgr()
	 */
	bool set_viewmgr(ui_iface_viewmgr *viewmgr);

	/**
	 *  @brief Return the viewmgr instance.
	 *
	 *  @return ui_iface_viewmgr instance.
	 *
	 *  @see set_viewmgr()
	 */
	ui_iface_viewmgr *get_viewmgr();

	_UI_DECLARE_PRIVATE_IMPL(ui_iface_view);
	_UI_DISABLE_COPY_AND_ASSIGN(ui_iface_view);
	_UI_DECLARE_FRIENDS(ui_iface_viewmgr);
	_UI_DECLARE_FRIENDS(ui_iface_app);
};

}

#endif /* _UI_IFACE_VIEW_H_ */
