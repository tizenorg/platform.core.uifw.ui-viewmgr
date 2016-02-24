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
#ifndef UI_TAB_VIEW
#define UI_TAB_VIEW

#include "../ui_viewmanager.h"

namespace efl_viewmgr
{

class ui_tab_view: public ui_basic_view
{
public:
	ui_tab_view(ui_controller *controller, const char *name = NULL);
	virtual ~ui_tab_view();

	bool set_tabbar(Evas_Object *toolbar);
};

}

#endif /* UI_BASIC_VIEW */
