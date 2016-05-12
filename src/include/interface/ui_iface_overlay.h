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
	virtual bool set_content(T content);
	virtual T unset_content();
	virtual void on_back();
	virtual bool activate();
	virtual bool deactivate();
	virtual bool is_activated();

	ui_iface_view *get_view();
	virtual T get_content();

protected:
	ui_iface_overlay(ui_iface_view *view);
	virtual ~ui_iface_overlay();

private:
	_UI_DECLARE_PRIVATE_IMPL(ui_iface_overlay);
	_UI_DISABLE_COPY_AND_ASSIGN(ui_iface_overlay);
};

}

#endif /* _UI_IFACE_OVERLAY_H_ */
