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

class UiIfaceViewmgr;

/**
 *  @class UiIfaceView
 *
 *  @ingroup ui_viewmanager
 *
 *  @brief This is a base class of view. A view must have one actual view content instance which represents a view for a current screen.
 *         The content type could be any types with regards to UI systems (ie, Eo*, Layer, Window...) A derived class must implement the view body based on the
 *         actual content in its UI system. This view will be belongs to a UiIfaceViewmgr instance and dominated its state by UiIfaceViewmgr. Basically,
 *         a view communicates with UiIfaceViewmgr to active cooperatively. This class is inherited to UiIfaceRotatable class to handle view's rotation
 *         state. Also, user can handle a view's life-cycle events with these -load, unload, activate, deactivate, pause, resume, destroy-. A view may have
 *         it's own show/hide transition styles. That means, it's available that views have different show/hide effects on demands. It's not mandatory but view
 *         should describe the transitions in this class. Please be full aware of view life-cycle to understand view's behavior.
 *
 *  @warning When the transitions are finished, the view must to call UiIfaceViewmgr :: _push_finished(), UiIfaceViewmgr :: _pop_finished() in order that
 *           The UiIfaceViewmgr keeps the view states exactly.
 */
class UiIfaceView : public UiIfaceRotatable
{
public:
	/**
	 *  @brief This is a constructor for initializing this view resources.
	 *
	 *  @param name view name.
	 *
	 *  @warning if you don't set a view name, you could not look up the view with its name. @see ui_viewmgr_view_get_by_name()
	 */
	explicit UiIfaceView(const char *name = NULL);

	///Destructor.
	virtual ~UiIfaceView();

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
	bool setTransitionStyle(const char *style);

	/**
	 *  @brief Set content removable.
	 *
	 *  @param removable if @p removable is @c true, content of this view will be removed on unload state. @c false otherwise.
 	 *
	 *  @warning You should not remove a view content manually on unload status if removable content is set.
	 */
	void setRemovableContent(bool removable);

	/**
	 *  @brief Set the indicator mode of the view.
	 *
	 *  @param indicator The mode to set, one of #UiViewIndicator.
	 */
	virtual void setIndicator(UiViewIndicator indicator);

	/**
	 *  @brief Return a style name of this view.
	 *
	 *  @return style name of view.
	 */
	const char *getTransitionStyle();

	/**
	 *  @brief Return a name of this view.
	 *
	 *  @return name of view.
	 */
	const char *getName();

	/**
	 *  @brief Return a content instance of this view.
	 *
	 *  @return content of view. If no contents set yet, @c NULL.
	 */
	T getContent();

	/**
	 *  @brief Replace or set a content of the view.
	 *
	 *  @note @p content is a logical object that represents a view in your framework. The actual type of the content could be translated to any certain types.
	 *        For instance, the type could be Evas_Object * in EFL and Layer * in Dali.
	 *
	 *  @param content a new content. It allows @c NULL for canceling the previous content.
	 *
	 *  @return @c true if it succeeds, @c false otherwise.
	 */
	virtual bool setContent(T content);

	/**
	 *  @brief Unset the view content.
	 *
	 *  @return A previous content. If it wasn't, return @c NULL.
	 */
	virtual T unsetContent();

	/**
	 *  @brief Return a state of this view.
	 *
	 *  @return current state of view.
	 */
	UiViewState getState();

	/**
	 *  @brief Return a state of removable content.
	 *
	 *  @return true if the view's content is removable, otherwise false.
	 */
	bool getRemovableContent();

	/**
	 *  @brief Return the indicator mode of this view.
	 *
	 *  @return indicator state of view.
	 */
	UiViewIndicator getIndicator();

	/**
	 *  @brief The H/W back key event occurs on view.
	 *
	 *  @note User can override this function to define application specific action when H/W back key
	 *        event occurs. otherwise current view will be popped.
	 */
	virtual void onBack();

protected:
	/**
	 *  @brief Toggle event block.
	 *
	 *  @note This interface is designed for toggling touch event on view transition.
	 *        UiIfaceViewmgr will call this interface for notifying event blocking toggling on transition time.
	 *
	 *  @param block @c true, when blocking is enabled, otherwise @c false.
	 *
	 *  @see getEventBlock()
	 */
	virtual void setEventBlock(bool block);

	/**
	 *  @brief Return the state of event block.
	 *
	 *  @return true if the event block enabled, otherwise false.
	 *
	 *  @see setEventBlock()
	 */
	bool getEventBlock();

	/**
	 *  @brief View load state.
	 *
	 *  @note A view of this state is moving onto the screen. Get ready for this view. Generally, you could prepare this view's content here and set them to
	 *        this view. In the most cases, this onLoad() will be triggered with this step. load -> deactivated -> activated. Tihs onLoad() will be triggered
	 *        only when view has not any content yet.
	 */
	virtual void onLoad();

	/**
	 *  @brief View unload state.
	 *
	 *  @note Remove resources (contents) with regards to this view for saving memory. Otherwise, you could keep those resources (contents) for later access.
	 *        Removing resources might be better in point of performance view. It's up to your scenario. onUnload() will be triggered just right before
	 *        the view is going to be deleted by popping or by somehow. Also, onUnload() will be triggered when this view is pushed behind other views.
	 */
	virtual void onUnload();

	/**
	 *  @brief View activate state.
 	 *
 	 *  @note Generally, a view will be activated when show-transition is finished. From whatever its state, when the view comes on the screen,
 	 *        onActivate() will be triggered. In the most cases, onActivate() will be triggered with this step. load -> deactivate -> activate
	 */
	virtual void onActivate();

	/**
	 *  @brief View deactivate state.
	 *
	 *  @note Get ready for unload. Hide transition may be triggered at this point. If the system blocks application running in some cases such as phone call,
	 *        system notification, application switching ..., Deactivate state will be triggered. Also, when a view is going to be popped or destroyed,
	 *        onDeactivate() will be triggered. Lastly, when a new view is pushed, so if it becomes invisible state by other views, onDeactivate() will be
	 *        triggered also.
	 */
	virtual void onDeactivate();

	/**
	 *  @brief View pause state.
	 *
	 *  @note Some UI controls such as Popup or a Menu popup usually blocks views. For those scenarios, this blocked view would be paused and shouldn't be
	 *        interactive with users. However, still it would be visible in some way (ie, half transparency). For this, this Pause will be triggered.
	 *        If the view is already deactivated or under the unload state, the pause won't be called.
	 */
	virtual void onPause();

	/**
	 *  @brief View resume state.
	 *
	 *  @note When a view is returns to the activate state from pause state, this onResume() will be triggered. For instance, a Popup is dismissed.
	 */
	virtual void onResume();

	/**
	 *  @brief View destroy state.
	 *
	 *  @note When this view is on destroyed by popping or by somehow, destroy will be triggered. Most of the cases, you can free your personal resources for
	 *        the view because this view instance will be totally freed at the end of destroy. Be aware that you must not request any view functions on this
	 *        state.
	 */
	virtual void onDestroy();

	/**
	 *  @brief Low Memory Event
	 *
	 *  @note This event function is responsible for saving data in the main memory to a persistent memory or storage to avoid data loss in case the Tizen
	 *        platform Low Memory Killer kills your application to get more free memory. This event function must also release any cached data in the main
	 *        memory to secure more free memory.
	 */
	virtual void onLowMemory();

	/**
	 *  @brief Low Battery Event
	 *
	 *  @note This event function is responsible for saving data in the main memory to a persistent memory or storage to avoid data loss in case the power goes
	 *        off completely. This event function must also stop heavy CPU consumption or power consumption activities to save the remaining power.
	 */
	virtual void onLowBattery();

	/**
	 *  @brief Region Changed Event
	 *
	 *  @note This event function is responsible for refreshing the display into the new time zone.
	 */
	virtual void onRegionChanged(const char *region);

	/**
	 *  @brief Language Changed Event
	 *
	 *  @note This event function is responsible for refreshing the display into the new language.
	 */
	virtual void onLanguageChanged(const char *language);

private:
	/**
	 *  @brief Connect with given viewmgr.
	 *
	 *  @param viewmgr The instance of viewmgr.
	 *
	 *  @return @c true if it succeeds, @c false otherwise.
	 *
	 *  @see _getViewmgr()
	 */
	bool _setViewmgr(UiIfaceViewmgr *viewmgr);

	/**
	 *  @brief Return the viewmgr instance.
	 *
	 *  @return UiIfaceViewmgr instance.
	 *
	 *  @see _setViewmgr()
	 */
	UiIfaceViewmgr *_getViewmgr();

	_UI_DECLARE_PRIVATE_IMPL(UiIfaceView);
	_UI_DISABLE_COPY_AND_ASSIGN(UiIfaceView);
	_UI_DECLARE_FRIENDS(UiIfaceViewmgr);
	_UI_DECLARE_FRIENDS(UiIfaceApp);
};

}

#endif /* _UI_IFACE_VIEW_H_ */
