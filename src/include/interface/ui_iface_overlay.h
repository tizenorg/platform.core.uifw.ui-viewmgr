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
#ifndef _UI_IFACE_OVERLAY_H_
#define _UI_IFACE_OVERLAY_H_

namespace ui_viewmanager
{

class ui_iface_view;

/**
 *  @class ui_iface_overlay
 *
 *  @ingroup ui_viewmanager
 *
 *  @brief This is a base class to support overlay view which could be active on other ui_iface_view. An overlay is designed to be one subordinate of one
 *         ui_iface_view. The specific behaviors of this class are totally depended on the derived class but it must be communicated with ui_iface_view to work
 *         successfully. Fundamentally, overlay view provides simpler interfaces than ui_iface_view since most of the overlay views will be active temporarily.
 *         This class is inherited to ui_iface_rotatable class to handle view's rotation state.
 */
class ui_iface_overlay: public ui_iface_rotatable
{
public:
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
	 *  @brief The H/W back key event occurs on view.
	 *
	 *  @note User can override this function to define application specific action when H/W back key
	 *        event occurs. otherwise current view will be popped.
	 */
	virtual void on_back();

	/**
	 *  @brief Overlay activate.
	 *
	 *  @note It makes overlay state as show.
	 *
	 *  @return @c true on success or @c false otherwise.
	 *
	 *  @see deactivate()
	 */
	virtual bool activate();

	/**
	 *  @brief Overlay deactivate.
	 *
	 *  @note It makes overlay state as hide.
	 *
	 *  @return @c true on success or @c false otherwise.
	 *
	 *  @see activate()
	 */
	virtual bool deactivate();

	/**
	 *  @brief Return the active status of overlay.
	 *
	 *  @return @c true if overlay is activated, @c false otherwise.
	 *
	 *  @see activate()
	 *  @see deactivate()
	 */
	virtual bool is_activated();

	/**
	 *  @brief Return a view which is matched with the overlay.
	 *
	 *  @return The view which is matched with overlay.
	 */
	ui_iface_view *get_view();

	/**
	 *  @brief Return a content instance of this overlay.
	 *
	 *  @return content of overlay.
	 */
	virtual T get_content();

protected:
	/**
	 *  @brief This is a constructor for initializing overlay.
	 *
	 *  @param view The instance of ui_iface_view.
	 */
	ui_iface_overlay(ui_iface_view *view);

	///Destructor.
	virtual ~ui_iface_overlay();

private:
	_UI_DECLARE_PRIVATE_IMPL(ui_iface_overlay);
	_UI_DISABLE_COPY_AND_ASSIGN(ui_iface_overlay);
};

}

#endif /* _UI_IFACE_OVERLAY_H_ */
