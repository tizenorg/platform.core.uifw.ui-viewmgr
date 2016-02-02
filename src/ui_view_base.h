/*
 * ui_view_base.h
 *
 *  Created on: Jan 15, 2016
 *      Author: hermet
 */

#ifndef UI_VIEW_BASE_H_
#define UI_VIEW_BASE_H_

#include <string>

template <typename T>
class ui_controller_base;

template <typename T>
class ui_viewmgr_base;

#define UI_VIEWMGR_BASE ui_viewmgr_base<T>
#define UI_CONTROLLER_BASE ui_controller_base<T>

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
template <typename T>
class ui_view_base
{
 private:
    /// View state definition
    enum ui_view_state {
         UI_VIEW_STATE_LOAD = 0,        ///< Load state
         UI_VIEW_STATE_UNLOAD,          ///< Unload state
         UI_VIEW_STATE_ACTIVE,          ///< Active state
         UI_VIEW_STATE_INACTIVE,        ///< Inactive state
         UI_VIEW_STATE_PAUSE,           ///< Pause state
         UI_VIEW_STATE_LAST
    };

    T content;                              ///< A content instance for a screen as a view.
    UI_CONTROLLER_BASE *controller;         ///< view life-cycle controller interface.
    //std::string name;                       ///< view name
    std::string style;                      ///< view style name.
    UI_VIEWMGR_BASE *viewmgr;               ///< viewmgr which this view belongs to.
    ui_view_state state;                    ///< view state
    bool event_block;                       ///< state of event block.

    //Need to check.
    friend class UI_VIEWMGR_BASE;
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
    virtual void set_event_block(bool block)
      {
         this->event_block = block;
      }

    /** @brief view load state
     *
     *  @note this state will be triggered by ui_viewmgr_base
     *
     *  @see ui_controller_base for this state in detail.
     */
    virtual void load()
      {
         this->state = UI_VIEW_STATE_LOAD;
         if (this->content) return;
         if (!this->controller) return;
         printf("controller load func called\n");
         this->controller->load(this);
      }

    /** @brief view unload state
     *
     *  @note this state will be triggered by ui_viewmgr_base
     *
     *  @see ui_controller_base for this state in detail.
     */
    virtual void unload()
      {
         this->state = UI_VIEW_STATE_UNLOAD;
         if (!this->content) return;
         if (!this->controller) return;
         this->controller->unload(this);
      }

    /** @brief view active state
     *
     *  @note this state will be triggered by ui_viewmgr_base
     *
     *  @see ui_controller_base for this state in detail.
     */
    virtual void active()
      {
         this->state = UI_VIEW_STATE_ACTIVE;
         if (!this->controller) return;
         this->controller->active(this);
      }

    /** @brief view inactive state
     *
     *  @note this state will be triggered by ui_viewmgr_base
     *
     *  @see ui_controller_base for this state in detail.
     */
    virtual void inactive()
      {
         this->state = UI_VIEW_STATE_INACTIVE;
         if (!this->controller) return;
         this->controller->inactive(this);
      }

    /** @brief view pause state
     *
     *  @note this state will be triggered by ui_viewmgr_base
     *
     *  @see ui_controller_base for this state in detail.
     */
    virtual void pause()
      {
         this->state = UI_VIEW_STATE_PAUSE;
         if (!this->content) return;
         if (state != UI_VIEW_STATE_ACTIVE) return;
         if (!this->controller) return;
         this->controller->pause(this);
      }

    /** @brief view resume state
     *
     *  @note this state will be triggered by ui_viewmgr_base
     *
     *  @see ui_controller_base for this state in detail.
     */
    virtual void resume()
      {
         this->state = UI_VIEW_STATE_ACTIVE;
         if (state != UI_VIEW_STATE_PAUSE) return;
         if (!this->content) return;
         if (!this->controller) return;
         this->controller->resume(this);
      }

    /** @brief view destroy state
     *
     *  @note this state will be triggered by ui_viewmgr_base
     *
     *  @see ui_controller_base for this state in detail.
     */
    virtual void destroy()
      {
         if (!this->controller) return;
         this->controller->destroy(this);
      }

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
	//ui_view_base(T content, const char *name, UI_CONTROLLER_BASE *controller)
    ui_view_base(T content, UI_CONTROLLER_BASE *controller) : content(content),
                                                              controller(controller),
                                                              style(NULL),
                                                              viewmgr(NULL),
															  state(UI_VIEW_STATE_LOAD),
                                                              event_block(false)
    {
      if (!content) this->state = UI_VIEW_STATE_UNLOAD;
      else this->state = UI_VIEW_STATE_LOAD;
    }

    ///Constructor for initializing with empty resources.
    //ui_view_bas() : ui_view_base(NULL, NULL)
	ui_view_base()
    {
		this->state = UI_VIEW_STATE_UNLOAD;
    }

    ///Destructor for terminating view.
    virtual ~ui_view_base()
    {
       this->viewmgr->remove_view(this);
       delete(this->controller);
    }

    /// Return a controller of this view.
    const UI_CONTROLLER_BASE* get_controller() { return this->controller; }
    /// Return a style name of this view.
    const char *get_style() { return this->style.c_str(); }
    /// Return a content instance of this view.
    T get_content() { return this->content; }
    /// Return a viewmgr which this view is belonging to
    UI_VIEWMGR_BASE *get_viewmgr() { return this->viewmgr; }


    /** @brief This is for replacing or setting a controller of the view.
     *
     *  @param controller a new controller. It allows @c null for canceling the previous controller.
     *  @return A previous controller. If it wasn't, the return value will be @c null
     *
     *  @warning Be aware deletion of controller passed here will be taken cover by ui_view_base.
     *           If you want to keep the controller for any reasons, please unset it using set_controller() before ui_view_base is deleted.
     */
    UI_CONTROLLER_BASE* set_controller(UI_CONTROLLER_BASE *controller)
      {
         UI_CONTROLLER_BASE *prev_controller = this->controller;
         this->controller = controller;
         printf("controller set \n");
         return prev_controller;
      }

    /** @brief This is for replacing or setting a content of the view.
     *
     *  @note @c content is a logical object that represents a view in your framework. The actual type of the content could be translated to any certain types.
     *        For instance, the type could be Evas_Object * in EFL and Layer * in Dali.
     *
     *  @param content a new content. It allows @c null for canceling the previous content.
     *  @return A previous content. If it wasn't, return value will be @c null
     */
    T set_content(T content)
      {
         T prev = this->content;
         this->content = content;
         return prev;
      }

    /** @brief set style of the view.
     *
     *  @note style is reserved for supporting various kinds of view as well as it's transition effects.
     *  	  The actual behaviors with this style is up to your frameworks. Default value of the style is null.
     *
     *  @param style a new style name.
     *  @return true if the given @c style is available, otherwise false.
     *
     *  @warning When you override this member function, you should implement the logic to check the given style name is available or not.
     *           If your framework doesn't support any styles then just allow a @c null argument and return true. Otherwise return false.
     *
     */
    virtual bool set_style(const char *style)
      {
         this->style.assign(style);
         return true;
      }
};


#endif /* UI_VIEW_BASE_H_ */
