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
class ui_base_view;

class ui_base_key_listener
{
protected:
	ui_base_viewmgr *viewmgr;
	Evas_Object *key_grabber;

public:
	ui_base_key_listener(ui_base_viewmgr *viewmgr);
	virtual ~ui_base_key_listener() {}

	virtual bool init();
	virtual bool term();
	virtual void extend_event_proc(ui_base_view *view, Evas_Event_Key_Down *ev) {}

	ui_base_viewmgr *get_viewmgr() { return this->viewmgr; }
};

}

#endif /* _UI_BASE_KEY_LISTENER_H_ */
