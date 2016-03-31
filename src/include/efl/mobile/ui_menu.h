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
#ifndef UI_MENU_H
#define UI_MENU_H

#include "../../interface/ui_iface_viewmanager.h"
#include "../ui_base_viewmanager.h"

namespace efl_viewmgr
{
class ui_view;

class ui_menu: public viewmgr::ui_iface_overlay<Elm_Ctxpopup *>
{
	friend class ui_view;
private:
	ui_menu(ui_view *view);
	virtual ~ui_menu();

	Elm_Win *get_window();

public:
	virtual bool activate();
	virtual bool deactivate();
	virtual bool set_content(Elm_Ctxpopup* ctxpopup);
	virtual Elm_Ctxpopup *unset_content();
	virtual bool is_activated();

	virtual Evas_Object *get_base();
	virtual int get_degree();
};

}

#endif /* UI_MENU_H */
