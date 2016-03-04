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
#ifndef UI_CONTROLLER_INTERFACE_H_
#define UI_CONTROLLER_INTERFACE_H_

namespace viewmgr {

class ui_iface_view;

/**
 *  @class ui_iface_controller.
 *
 *  @internal
 *  @ingroup viewmgr
 *
 *  @brief UI Controller Interface. This interface is designed for handling of life-cycle events from user side.
 */
class ui_iface_controller
{
	friend class ui_iface_view;

private:
	ui_iface_view *view;

	void set_view(ui_iface_view *view);

protected:
	/**
	 *  @brief Return a view which is matched with controller
	 *
	 *  @return The view which is matched with controller
	 *
	 *  @note User can set a controller 2 ways, 1. send a controller instance when view created,
	 *        2. call set_view() method with controller instance.
	 *
	 *  @see set_view()
	 */
	ui_iface_view *get_view()
	{
		return this->view;
	}

public:
	///Constructor.
	ui_iface_controller() :
			view(NULL)
	{
	}

	///Destructor.
	virtual ~ui_iface_controller()
	{
	}

	/** @brief load callback.
	 *
	 *  @note Now, this view is moving onto the screen. Get ready for this view. If this view content is alive, load callback won't be called.
	 *        In the most cases, this callback will be triggered with this step load -> inactive -> active.
	 */
	virtual void load() = 0;

	/** @brief unload callback.
	 *
	 *  @note Remove resources with regards to this view for saving memory or keep the content for performance. It's up to your scenario.
	 *        Unload will be called just right before when the view is going to be deleted by popping or it's piled under the more than one view.
	 *        If the view content is not alive, the unload won't be called.
	 *        In the most cases, this callback will be triggered with this step. inactive -> unload -> destroy
	 */
	virtual void unload() = 0;

	/** @brief active callback.
	 *
	 *  @note View is on active state after show transition is finished.
	 *        From whatever the state, if the view is on the screen, the active callback will be called.
	 *        In the most cases, this callback will be triggered with this step. load -> inactive -> active
	 */
	virtual void active() = 0;

	/** @brief inactive callback.
	 *
	 *  @note View is on inactive state. Get ready for unload. Hide transition may be triggered at this point.
	 *        Inactive state is triggered on this scenario that the view is still visible but it's not interactive with users.
	 *        In the most cases, when view is going to be popped or destroyed or pushed one more depth, the inactive state will be triggered.
	 *        Some UI controls such as a center popup or a menu popup blocks the view, this view may be inactive but still visible in someway (with transparency)
	 */
	virtual void inactive() = 0;

	/** @brief pause callback.
	 *
	 *  @note When the system blocks the application running in cases such as phone call, system notification, switching applications ...
	 *        When Window turns to deactivate. (@see ui_viewmgr_base :: deactivate()).
	 *        If the view were inactive or unload state, the pause won't be called.
	 */
	virtual void pause() = 0;

	/** @brief resume callback.
	 *
	 *  @note View is turning back to the active state again from pause.
	 *        When the system allows the application turns to activate.
	 *        When the Window turns to activate. (@see ui_viewmgr_base :: activate())
	 */
	virtual void resume() = 0;

	/** @brief destroy callback.
	 *
	 *  @note When this view is on destroying by popping or deleting.
	 */
	virtual void destroy() = 0;
};

}

#endif /* UI_CONTROLLER_INTERFACE_H_ */