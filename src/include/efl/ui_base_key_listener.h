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
#ifndef _UI_BASE_KEY_LISTENER_H_
#define _UI_BASE_KEY_LISTENER_H_

namespace efl_viewmanager
{

class ui_base_viewmgr;

/**
 *  @class ui_base_key_listener
 *
 *  @ingroup efl_viewmanager
 *
 *  @brief This is a base class of EFL key listener. Typically, this class has a role for delegating event propagation from system to a view.
 *         ui_base_key_listener grabs HW back key event then pass it to the top view from the view manager. You could extend this class for more HW key
 *         events for your profile feature. By overriding ui_base_key_listener::extend_event_proc(), you could get the key event information when that event is
 *         triggered. This class must be requested by ui_base_viewmgr and controlled wholly by it.
 */
class ui_base_key_listener
{
protected:
	ui_base_key_listener(ui_base_viewmgr *viewmgr);
	virtual ~ui_base_key_listener();

	virtual bool init();
	virtual bool term();
	virtual void extend_event_proc(ui_base_view *view, Evas_Event_Key_Down *ev) {}

	ui_base_viewmgr *get_viewmgr();
	Evas_Object *get_keygrab_obj();

private:
	_UI_DECLARE_PRIVATE_IMPL(ui_base_key_listener);
	_UI_DISABLE_COPY_AND_ASSIGN(ui_base_key_listener);
	_UI_DECLARE_FRIENDS(ui_base_viewmgr);
};

}

#endif /* _UI_BASE_KEY_LISTENER_H_ */
