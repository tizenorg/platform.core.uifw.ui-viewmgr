/*
 * ui_viewmgr_base.h
 *
 *  Created on: Jan 15, 2016
 *      Author: hermet
 */

#ifndef UI_WINDOW_BASE_H_
#define UI_WINDOW_BASE_H_

#include <list>

template <typename T>
class ui_view_base;

#define UI_VIEW_BASE ui_view_base<T>

/**
 *  @class ui_viewmgr_base
 *
 *  @ingroup ui_viewmgr
 *
 *  @brief This is a base class of viewmgr. One viewmgr represents a window which contains multiple views.
 *         A viewmgr manages not only views life-cycle but constructs some basic infrastructure. It's up to derived classes.
 *
 *  @warning viewmgr will remove all containing views when it's destroyed.
 *  @date 2016/01/29
 *  @author Hermet Park <chuneon.park@samsung.com>
 */
template <typename T>
class ui_viewmgr_base
{
 private:
    //TODO: change name to view_stack
    //std::list<UI_VIEW_BASE*> view_list;     //view list.
    bool                     event_block;   //event block on view transition. This value should be configurable by system.

    /**
     *	@brief link a given view to this viewmgr.
     *
     *  @param view a view to connect to this viewmgr.
     *  @return success or not.
     *
     *	@note This is s a friend function of ui_view_base
     */
    bool _connect_view(UI_VIEW_BASE *view)
    {
       if (view->viewmgr) return false;
       view->viewmgr = this;
       return true;
    }

    /**
     *	@brief unlink a given view from this viewmgr.
     *
     *  @param view a view to disconnect from this viewmgr.
     *  @return @c true success or @c false not.
     *
     *	@note This is s a friend function of ui_view_base
     */
    bool _disconnect_view(UI_VIEW_BASE *view)
    {
       if (!view->viewmgr) return false;
       view->viewmgr = NULL;
       return true;
    }

    /**
     *	@brief toggle event blocking to the given view.
     *
     *  @param view a view to toggle event blocking
     *  @param block @c true is block event, otherwise @c false.
     *
     *	@note This is s a friend function of ui_view_base
     */
    void _set_event_block(UI_VIEW_BASE *view, bool block)
    {
       LOGI("CALLED");
       if (!this->event_block) return;
       view->set_event_block(block);
    }

 protected:
    //check the inherit range.
    std::list<UI_VIEW_BASE*> view_list;     //view list.
    struct {
         UI_VIEW_BASE* view_this;
         UI_VIEW_BASE* view_other;
    } anim;
    /**
     *	@brief This function is designed for end of push transition.
     *
     *  @param view view which is finished pushing.
     *  @return @c true success or @c false not.
     *
     *  @warning This function must be called definitely when push transition is finished.
     *	@note This is s a friend function of ui_view_base
     */
    virtual bool _push_view_finished(UI_VIEW_BASE *view)
    {
       UI_VIEW_BASE *last = this->view_list.back();

       //The previous view has been pushed. This should be unload.
       if (last != view) {
          view->unload();
          return true;
       }

       //A new view has been pushed. This should be active.
       view->active();
       this->_set_event_block(view, true);

       return true;
    }

    /**
     *	@brief This function is designed for end of pop transition.
     *
     *	@param view view which is finished popping.
     *  @return @c true success or @c false not.
     *
     *  @warning This function must be called definitely when push transition is finished.
     *	@note This is s a friend function of ui_view_base
     */
    virtual bool _pop_view_finished(UI_VIEW_BASE *view)
    {
       UI_VIEW_BASE *last = this->view_list.back();

       //This view has been popped. It should be destroyed.
       if (last == view) {
          view->unload();
          view->destroy();
          delete(view);
          return true;
       }

       //The previous view has been popped. It should become active.
       view->active();
       this->_set_event_block(view, true);

       return true;
    }

  public:
    ///Constructor.
    ui_viewmgr_base() : event_block(true)
    {
       LOGI("CALLED");
	   this->anim.view_this = NULL;
	   this->anim.view_other = NULL;
       //TODO: Initialize ?
    }

    ///Destructor. Delete all contained views.
    virtual ~ui_viewmgr_base()
    {
       LOGI("CALLED");
       //Terminate views
       for (typename std ::list<UI_VIEW_BASE*> ::reverse_iterator it = this->view_list.rbegin();
            it != this->view_list.rend(); it++)
       {
          UI_VIEW_BASE *view = *it;
          view->inactive();
          view->unload();
          view->destroy();
          delete(view);
       }
    }

    //Activate a viewmgr. Implement this body to activate a viewmgr.
    virtual bool activate() = 0;

    //Deactivate a viewmgr. Implement this body to deactivate a viewmgr.
    virtual bool deactivate() = 0;

    /**
     *	@brief Push a new view into the viewmgr stack.
     *	       This function is used for application switches the current view to a new one.
     *
     *  @note Normally, the current view will be hidden by a new view.
     *  @return @c true on success, @c false otherwise.
     */
    virtual bool push_view(UI_VIEW_BASE *view)
    {
       LOGI("CALLED");
       if (!view) {
         LOGE("view in NULL"); return false;
       }
       if (!this->_connect_view(view)) {
         LOGE("connect view failed"); return false;
       }

       UI_VIEW_BASE *pview;

       //Previous view
       if (this->view_list.size())
       {
         pview = this->view_list.back();
         pview->inactive();
         this->_set_event_block(pview, false);
       }

       view_list.push_back(view);

       //TODO: Implement below method.
       //this->push_intermediate();

       if (!view->content)
       {
          //Current view
          view->load();
       }

       view->inactive();
       this->_set_event_block(view, false);

       return true;
    }

    /**
     *	@brief Pop the top view from the viewmgr stack.
     *	       This function is used for application switches the current view back to the previous view.
     *	       The top view will be removed from the view stack and then it will be deleted by the viewmgr.
     *
     *	@note If the view is just one left, then viewmgr would be destroyed since the application might be terminated.
     *	      But this behavior is optional.
     *
     *  @return A view pointer which was popped. If it's failed to pop, @c null will be returned.
     */
    virtual UI_VIEW_BASE* pop_view()
    {
       //No more view? destroy viewmgr?
       if (this->get_view_count() == 0) {
            return NULL;
       }

       //This is the last page. destroy viewmgr?
       if (this->get_view_count() == 1) {
            //destroy viewmgr?
            UI_VIEW_BASE *view = this->view_list.back();
            view->inactive();
            view->unload();
            view->destroy();
            return NULL;
       }

       //last page to be popped.
       UI_VIEW_BASE *view = this->view_list.back();
       view->inactive();
       this->_set_event_block(view, true);

       //Below object has to be used in child class...
       //Make this getter method? or define instance?
       //previous page to be current active.
       auto nx = std::prev(this->view_list.end(), 2);
       UI_VIEW_BASE *pview = *nx;
       pview->load();
       pview->inactive();
       this->_set_event_block(pview, true);

       return view;
    }

    /**
     *	@brief Insert a view into this viewmgr stack. Specially, right before of the given view, @before
     *
     *  @param view a view to push into the viewmgr stack
     *  @param before a view that will be just after the @c view.
     *         If you pass @c null, @c view will be inserted at the front of the view stack.
     *  @return @c true success or @c false not.
     */
    virtual bool insert_view_before(UI_VIEW_BASE *view, UI_VIEW_BASE *before)
    {
       //TODO: ...

       return true;
    }

    /**
     *	@brief Insert a view into this viewmgr stack. Specially, right after of the given view, @after
     *
     *  @param view a view to push into the viewmgr stack
     *  @param after a view that will be just before the @c view.
     *         If you pass @c null, @c view will be inserted at the end of the view stack.
     *  @return @c true success or @c false not.
     */
    virtual bool insert_view_after(UI_VIEW_BASE *view, UI_VIEW_BASE *after)
    {
       //TODO: ...

       return true;
    }

    /**
     *	@brief Remove the given view from this viewmgr stack.
     *
     *  @return @c true on success or @c false if not.
     *
     */
    virtual bool remove_view(UI_VIEW_BASE *view)
    {
       this->view_list.remove(view);
       this->_disconnect_view(view);

       //TODO: If this view is the top on the stack ?

       return true;
    }

    /**
     *	@brief Return a stack index number of the given view.
     *	       You could use this function to query the given view stack order.
     *
     *  @param idx a view to query the index.
     *  @return an index of the give view.
     *          If there were no views on the idx, @c null will be returned.
     *
     *  @warning the index number is variable since the view stack size is also variable.
     */
    UI_VIEW_BASE* get_view(unsigned int idx)
    {
       typename std ::list<UI_VIEW_BASE*> :: iterator it = this->view_list.begin();
       std ::advance(it, idx);
       return *it;
    }

    /**
     *	@brief Return a view which is matched with the @c name.
     *
     *  @param name the name of the view which you find.
     *  @return the view which name is matched with @c name.
     *          If there were no views name matched, @c null will be returned.
     *
     */
    UI_VIEW_BASE *get_view(const char *name)
    {
       //TODO: ...
    }

    /**
     *	@brief Return a stack index number of the given view.
     *	       You could use this function to query the given view stack order.
     *
     *  @param a view to query the index.
     *  @return an index of the give view on success, otherwise, -1.
     *
     *  @warning the index number is variable since the view stack size is also variable.
     */
    int get_view_index(const UI_VIEW_BASE *view)
    {
       int idx = 0;

       for (typename std ::list<UI_VIEW_BASE*> :: iterator it = this->view_list.begin(); it != this->view_list.end(); it++) {
          if (view == *it) return idx;
          ++idx;
       }

       return -1;
    }

    /**
     *	@brief Return the number of views which this viewmgr has.
     *
     *  @return the number of view
     *
     */
    unsigned int get_view_count()
    {
       return this->view_list.size();
    }

    /**
     *	@brief Return a list of views which this viewmgr has.
     *
     *  @return a pointer of list of views.
     *
     */
    const std ::list<UI_VIEW_BASE*>* const get_view_list()
    {
       return &this->view_list;
    }
};

#endif /* UI_WINDOW_BASE_H_ */
