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
#ifndef _UI_KEY_LISTENER_H_
#define _UI_KEY_LISTENER_H_

namespace efl_viewmanager
{
class ui_viewmgr;

/**
 *  @class ui_key_listener
 *
 *  @ingroup efl_viewmanager
 *
 *  @brief This class extends to ui_base_key_listener to support an additional HW Menu key for mobile profile. Basically, HW Menu key will be propagated to
 *         the top view and ui_view::on_menu() will be triggered.
  */
class ui_key_listener : public ui_base_key_listener
{
public:
	ui_key_listener(ui_viewmgr *viewmgr);

	virtual bool init();
	virtual void extend_event_proc(ui_base_view *view, Evas_Event_Key_Down *ev);
};

}

#endif /* _UI_KEY_LISTENER_H_ */
