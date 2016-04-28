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
#ifndef _UI_POPUP_H_
#define _UI_POPUP_H_

namespace efl_viewmanager
{
class ui_popup : public ui_base_overlay
{
private:
	Elm_Win *get_window();

public:
	ui_popup(ui_view *view);
	virtual ~ui_popup();

	virtual bool activate();
	virtual bool deactivate();
	virtual bool set_content(Elm_Popup* popup);
	virtual Elm_Popup *unset_content();
	virtual bool is_activated();

	virtual Evas_Object *get_base();
	virtual int get_degree();
};

}

#endif /* _UI_POPUP_H_ */
