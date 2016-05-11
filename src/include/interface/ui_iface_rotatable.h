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
#ifndef _UI_IFACE_ROTATABLE_H_
#define _UI_IFACE_ROTATABLE_H_

namespace ui_viewmanager
{

/**
 *  @class ui_iface_rotatable
 *
 *  @internal
 *  @ingroup ui_viewmanager
 *
 *  @brief This is an interface class to support rotation behavior of views (or overlay). This class just defines status such as rotate, portrait, landscape
 *         so the derived class must implement the behavior body in its concept.
 */
class ui_iface_rotatable
{
protected:
	/**
	 *  @brief view portrait state.
	 *
	 *  @note This state will be called when view rotation changed to portrait.
	 *
	 *  @see on_landscpae()
	 *  @see on_rotate()
	 */
	virtual void on_portrait() {}

	/**
	 *  @brief view landscape state.
	 *
	 *  @note This state will be called when view rotation changed to landscape.
	 *
	 *  @see on_portrait()
	 *  @see on_rotate()
	 */
	virtual void on_landscape() {}

	/**
	 *  @brief view rotate changed.
	 *
	 *  @note This state will be called when view rotation changed.
	 *
	 *  @param degree Current view's degree.
	 *
	 *  @see on_portrait()
	 *  @see on_landscpae()
	 */
	virtual void on_rotate(int degree) {}

public:
	/** @brief Get current view's degree.
	 *
	 *  @return Current rotation degree, -1 if it fails to get degree information.
	 */
	virtual int get_degree() { return 0; }
};

}

#endif /* _UI_IFACE_ROTATABLE_H_ */
