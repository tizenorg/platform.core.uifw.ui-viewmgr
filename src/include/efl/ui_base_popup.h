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
#ifndef UI_BASE_POPUP_H
#define UI_BASE_POPUP_H

#include "../interface/ui_iface_viewmanager.h"

namespace efl_viewmgr
{
class ui_base_view;

class ui_base_popup : public viewmgr::ui_iface_rotatable
{
	friend class ui_base_view;
private:
	ui_base_view *view;
	Elm_Popup *popup;

	Elm_Win *get_window();

public:
	ui_base_popup(ui_base_view *view);
	virtual ~ui_base_popup();

	virtual bool activate();
	virtual bool deactivate();
	virtual bool set_content(Elm_Ctxpopup* ctxpopup);
	virtual Elm_Popup *unset_content();
	virtual void on_back();
	virtual bool is_activated();

	virtual Evas_Object *get_base();
	virtual int get_degree();
	virtual Elm_Popup *get_content()
	{
		return this->popup;
	}
};

}

#endif /* UI_BASE_POPUP_H */
