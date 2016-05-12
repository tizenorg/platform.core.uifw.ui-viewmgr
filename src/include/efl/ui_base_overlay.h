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
#ifndef _UI_BASE_OVERLAY_H_
#define _UI_BASE_OVERLAY_H_

namespace efl_viewmanager
{

class ui_base_view;

/**
 *  @class ui_base_overlay
 *
 *  @internal
 *  @ingroup efl_viewmanager
 *
 *  @brief This is a base class to support EFL overlay view which could be active on other ui_base_view. An overlay is designed to be one subordinate of one
 *         ui_base_view. ui_base_overlay is nothing more than ui_iface_overlay in behavior perspective. It just comes out with renaming class for adapting with
 *         other EFL base classes.
 */
class ui_base_overlay: public ui_iface_overlay
{
protected:
	ui_base_overlay(ui_base_view *view);
	virtual ~ui_base_overlay();
};

}

#endif /* _UI_BASE_OVERLAY_H_ */
