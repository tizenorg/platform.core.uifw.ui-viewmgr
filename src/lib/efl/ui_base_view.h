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
#ifndef UI_BASE_VIEW_H
#define UI_BASE_VIEW_H

#include <Elementary.h>
#include "../interface/ui_iface_viewmanager.h"

namespace efl_viewmgr
{

/**
 *  @class ui_base_view
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
class ui_base_view: public viewmgr::ui_iface_view<Evas_Object *, ui_base_viewmgr>
{
	friend class ui_base_viewmgr;

protected:
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
	virtual void set_event_block(bool block);

	virtual void on_rotate(int degree);
	virtual void on_portrait();
	virtual void on_landscape();

public:
	///Constructor.
	ui_base_view(const char *name = NULL);

	///Destructor.
	virtual ~ui_base_view();

	/** @brief This is for replacing or setting a content of the view.
	 *
	 *  @param content a new content. It allows @c NULL for canceling the previous content.
	 *
	 *  @return A previous content. If it wasn't, return value will be @c NULL.
	 */
	virtual bool set_content(Evas_Object *content);

	/** @brief This is for unsetting a content of the view.
	 *
	 *  @return A previous content. If it wasn't, return value will be @c NULL.
	 */
	virtual Evas_Object *unset_content();

	/**  @brief Get a base layout of viewmgr.
	 */
	virtual Evas_Object *get_base();

	/** @brief Set the indicator mode.
	 *
	 *  @param indicator The mode to set, one of #ui_base_view_indicator.
	 */
	virtual void set_indicator(ui_view_indicator indicator);

	/** @brief Get current view's degree.
	 *
	 *  @return Current rotation degree, -1 if it fails to get degree information.
	 */
	virtual int get_degree();
};

}

#endif /* UI_BASE_VIEW_H */