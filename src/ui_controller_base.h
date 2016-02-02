/*
 * ui_controller_base.h
 *
 *  Created on: Jan 15, 2016
 *  Author: Hermet Park <chuneon.park@samsung.com>
 */

#ifndef UI_CONTROLLER_BASE_H_
#define UI_CONTROLLER_BASE_H_

#ifdef  LOG_TAG
#undef  LOG_TAG
#endif
#define LOG_TAG "VIEWMGR"


class ui_view_base;


/**
 *  @class ui_controller_base
 *
 *  @ingroup ui_viewmgr
 *
 *  @brief UI Controller Interface. This interface is designed for handling of life-cycle events from user side.
 *
 *  @date 2016/01/15
 *  @author Hermet Park <chuneon.park@samsung.com>
 *
 */
class ui_controller_base
{
 private:
	ui_view_base *view;

 public:
    ui_controller_base() : view(NULL) {}

    /** @brief load callback
     *
     *  @note Now, this view is moving onto the screen. Get ready for this view. If this view content is alive, load callback won't be called.
     *        In the most cases, this callback will be triggered with this step load -> inactive -> active.
     */
    virtual void load() = 0;

    /** @brief unload callback
     *
     *  @note Remove resources with regards to this view for saving memory or keep the content for performance. It's up to your scenario.
     *        Unload will be called just right before when the view is going to be deleted by popping or it's piled under the more than one view.
     *        If the view content is not alive, the unload won't be called.
     *        In the most cases, this callback will be triggered with this step. inactive -> unload -> destroy
     */
    virtual void unload() = 0;

    /** @brief active callback
     *
     *  @note View is on active state after show transition is finished.
     *        From whatever the state, if the view is on the screen, the active callback will be called.
     *        In the most cases, this callback will be triggered with this step. load -> inactive -> active
     */
    virtual void active() = 0;

    /** @brief inactive callback
     *
     *  @note View is on inactive state. Get ready for unload. Hide transition may be triggered at this point.
     *        Inactive state is triggered on this scenario that the view is still visible but it's not interactive with users.
     *        In the most cases, when view is going to be popped or destroyed or pushed one more depth, the inactive state will be triggered.
     *        Some UI controls such as a center popup or a menu popup blocks the view, this view may be inactive but still visible in someway (with transparency)
     */
    virtual void inactive() = 0;

    /** @brief pause callback
     *
     *  @note When the system blocks the application running in cases such as phone call, system notification, switching applications ...
     *        When Window turns to deactivate. (@see ui_viewmgr_base :: deactivate())
     *        If the view were inactive or unload state, the pause won't be called.
     */
    virtual void pause() = 0;

    /** @brief resume callback
     *
     *  @note View is turning back to the active state again from pause.
     *        When the system allows the application turns to activate.
     *        When the Window turns to activate. (@see ui_viewmgr_base :: activate())
     */
    virtual void resume() = 0;

    /** @brief destroy callback
     *
     *  @note When this view is on destroying by popping or deleting.
     */
    virtual void destroy() = 0;

	void set_view(ui_view_base *view);

	ui_view_base *get_view() { return this->view; }
};

#endif /* UI_CONTROLLER_BASE_H_ */
