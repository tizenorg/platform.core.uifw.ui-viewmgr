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
#ifndef UI_VIEW_H
#define UI_VIEW_H

#include <Elementary.h>
#include "../interface/ui_viewmanager_interface.h"

#define CONVERT_TO_EO(T) static_cast<Evas_Object *>((T))
#define CONVERT_TO_T(EO) static_cast<T>((EO))

namespace efl_viewmgr
{
class ui_controller;

/**
 *  @class ui_view
 *
 *  @ingroup viewmgr
 *
 *  @brief UI View Class. This is the class of view. A view must have one content instance which represents a view for a current screen.
 *         UI View may have it's own show/hide transition styles. That means, it's available that views have different show/hide effects on demands.
 *         It's not mandatory but view should describe the transitions in this class.
 *
 *  @warning When the transitions are finished, the view must to call ui_iface_viewmgr :: _push_finished(), ui_iface_viewmgr :: _pop_finished() in order that
 *           The ui_iface_viewmgr keeps the view states exactly.
 */
class ui_view: public viewmgr::ui_iface_view
{
	friend class ui_viewmgr;

protected:
	/** @brief Unload current view's content
	 *
	 *  @note Make this view's content as NULL, then destroy content.
	 */
	virtual void unload_content();

	/** @brief Get a parent object of view.
	 *
	 *  @note This is calling viewmgr get_base() method internally.
	 *
	 *  @return base layout of viewmgr.
	 */
	Evas_Object *get_parent();

	/** @brief toggle event block.
	 *
	 *  @note It makes internal conformant event freeze during effect showing.
	 *
	 *  @param block @c true, when blocking is enabled, otherwise @c false.
	 */
	virtual void set_event_block(bool block) {}

public:
	///Constructor.
	ui_view(ui_controller *controller, const char *name = NULL);
	///Constructor.
	ui_view(const char *name = NULL);

	///Destructor.
	virtual ~ui_view();

	/** @brief This is for replacing or setting a content of the view.
	 *
	 *  @param content a new content. It allows @c NULL for canceling the previous content.
	 *
	 *  @return A previous content. If it wasn't, return value will be @c NULL.
	 */
	virtual Evas_Object *set_content(Evas_Object *content);

	/**  @brief Get a base layout of viewmgr.
	 */
	virtual Evas_Object *get_base();

	/** @brief This is for calling controller's back method.
	 */
	virtual void back();

	/** @brief This is for calling controller's rotated method.
	 */
	virtual void rotated();

	/** @brief Set the indicator mode.
	 *
	 *  @param indicator The mode to set, one of #ui_view_indicator.
	 */
	void set_indicator(ui_view_indicator indicator);

};

}

#endif /* UI_VIEW_H */
