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
#ifndef UI_BASE_OVERLAY_H
#define UI_BASE_OVERLAY_H

#include <Elementary.h>
#include "../interface/ui_iface_viewmanager.h"

namespace efl_viewmgr
{

class ui_base_viewmgr;
class ui_base_view;

class ui_base_overlay: public viewmgr::ui_iface_overlay<Evas_Object *, ui_base_viewmgr>
{
protected:
	ui_base_overlay(ui_base_view *view);
	virtual ~ui_base_overlay();
};

}

#endif /* UI_BASE_OVERLAY_H */