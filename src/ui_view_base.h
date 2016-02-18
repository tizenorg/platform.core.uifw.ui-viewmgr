/*
 * ui_view_base.h
 *
 *  Created on: Jan 15, 2016
 *      Author: hermet
 */

#ifndef UI_VIEW_BASE_H_
#define UI_VIEW_BASE_H_

#include <string>

#ifdef  LOG_TAG
#undef  LOG_TAG
#endif
#define LOG_TAG "VIEWMGR"

typedef void* T;

class ui_viewmgr_base;
class ui_controller_base;

/**
 *  @class ui_view_base
 *
 *  @ingroup ui_viewmgr
 *
 *	@brief UI View Base Class. This is the base class of view. A view must have one content instance which represents a view for a current screen.
 *	       UI View may have it's own show/hide transition styles. That means, it's available that views have different show/hide effects on demands.
 *	       It's not mandatory but view should describe the transitions in this class.
 *
 *	@warning When the transitions are finished, the view must to call ui_viewmgr_base :: _push_finished(), ui_viewmgr_base :: _pop_finished() in order that
 *	         The ui_viewmgr_base keeps the view states exactly.
 *
 *	@date 2016/01/15
 *	@author Hermet Park <chuneon.park@samsung.com>
 */
class ui_view_base
{
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
	ui_controller_base *controller;         ///< view life-cycle controller interface.
	std::string name;                       ///< view name
	std::string style;                      ///< view style name.
	ui_viewmgr_base *viewmgr;               ///< viewmgr which this view belongs to.
	ui_view_state state;                    ///< view state
	bool event_block;                       ///< state of event block.

	//Need to check.
	friend class ui_viewmgr_base;
	//friend bool ui_viewmgr_base ::_connect_view(ui_view_base *view);
	//friend bool ui_viewmgr_base ::_disconnect_view(ui_view_base<T> *view);
	//friend void ui_viewmgr_base ::_set_event_block(ui_view_base<T> *view);
	//friend bool ui_viewmgr_base ::_push_view_finished(ui_view_base<T> *view);
	//friend bool ui_viewmgr_base ::_pop_view_finished(ui_view_base<T> *view);

protected:

	/** @brief toggle event block
	 *
	 *  @note This interface is designed for toggling touch event on view transition.
	 *        ui_viewmgr_base will call this interface for notifying event blocking toggling on transition time.
	 *
	 *  @param block @c true, when blocking is enabled, otherwise @c false.
	 *
	 */
	virtual void set_event_block(bool block);

	/** @brief view load state
	 *
	 *  @note this state will be triggered by ui_viewmgr_base
	 *
	 *  @see ui_controller_base for this state in detail.
	 */
	virtual void load();

	/** @brief view unload state
	 *
	 *  @note this state will be triggered by ui_viewmgr_base
	 *
	 *  @see ui_controller_base for this state in detail.
	 */
	virtual void unload();

	/** @brief view active state
	 *
	 *  @note this state will be triggered by ui_viewmgr_base
	 *
	 *  @see ui_controller_base for this state in detail.
	 */
	virtual void active();

	/** @brief view inactive state
	 *
	 *  @note this state will be triggered by ui_viewmgr_base
	 *
	 *  @see ui_controller_base for this state in detail.
	 */
	virtual void inactive();

	/** @brief view pause state
	 *
	 *  @note this state will be triggered by ui_viewmgr_base
	 *
	 *  @see ui_controller_base for this state in detail.
	 */
	virtual void pause();

	/** @brief view resume state
	 *
	 *  @note this state will be triggered by ui_viewmgr_base
	 *
	 *  @see ui_controller_base for this state in detail.
	 */
	virtual void resume();

	/** @brief view destroy state
	 *
	 *  @note this state will be triggered by ui_viewmgr_base
	 *
	 *  @see ui_controller_base for this state in detail.
	 */
	virtual void destroy();

	/// Return the state of event block.
	bool get_event_block()
	{
		return this->event_block;
	}

public:
	/** @brief This is a constructor for initializing this view resources.
	 *
	 *  @param content A content instance for a screen as a view.
	 *  @param controller view life-cycle controller interface.
	 *  @param name view name.
	 *
	 *  @warning Be aware the deletion of controller passed here will be covered by ui_view_base.
	 *           If you want to keep it for any reasons, please unset it using set_controller() before ui_view_base is deleted.
	 */

	//Constructor
	ui_view_base(T content, ui_controller_base *controller, const char *name);
	///Constructor for initializing with controller.
	ui_view_base(ui_controller_base *controller, const char *name = NULL);
	///Constructor for initializing with name.
	ui_view_base(const char *name = NULL);

	///Destructor for terminating view.
	virtual ~ui_view_base();

	/** @brief This is for replacing or setting a controller of the view.
	 *
	 *  @param controller a new controller. It allows @c NULL for canceling the previous controller.
	 *  @return A previous controller. If it wasn't, the return value will be @c NULL
	 *
	 *  @warning Be aware deletion of controller passed here will be taken cover by ui_view_base.
	 *           If you want to keep the controller for any reasons, please unset it using set_controller() before ui_view_base is deleted.
	 */
	ui_controller_base* set_controller(ui_controller_base *controller);

	/** @brief This is for replacing or setting a content of the view.
	 *
	 *  @note @c content is a logical object that represents a view in your framework. The actual type of the content could be translated to any certain types.
	 *        For instance, the type could be Evas_Object * in EFL and Layer * in Dali.
	 *
	 *  @param content a new content. It allows @c NULL for canceling the previous content.
	 *  @return A previous content. If it wasn't, return value will be @c NULL
	 */
	virtual T set_content(T content);

	/** @brief set style of the view.
	 *
	 *  @note style is reserved for supporting various kinds of view as well as it's transition effects.
	 *  	  The actual behaviors with this style is up to your frameworks. Default value of the style is NULL.
	 *
	 *  @param style a new style name.
	 *  @return true if the given @c style is available, otherwise false.
	 *
	 *  @warning When you override this member function, you should implement the logic to check the given style name is available or not.
	 *           If your framework doesn't support any styles then just allow a @c NULL argument and return true. Otherwise return false.
	 *
	 */
	virtual bool set_style(const char *style);

	/// Return a controller of this view.
	const ui_controller_base* get_controller()
	{
		return this->controller;
	}
	/// Return a style name of this view.
	const char *get_style()
	{
		return this->style.c_str();
	}
	/// Return a content instance of this view.
	T get_content()
	{
		return this->content;
	}
	/// Return a viewmgr which this view is belonging to
	ui_viewmgr_base *get_viewmgr()
	{
		return this->viewmgr;
	}
	/// Return a state of this view.
	ui_view_state get_state()
	{
		return this->state;
	}
};

#endif /* UI_VIEW_BASE_H_ */
