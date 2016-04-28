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
#ifndef _UI_BASE_VIEWMANAGER_H_
#define _UI_BASE_VIEWMANAGER_H_

#include <Elementary.h>
#include "../interface/ui_iface_viewmanager.h"
#include "ui_base_overlay.h"
#include "ui_base_key_listener.h"
#include "ui_base_viewmgr.h"
#include "ui_base_view.h"

#define UI_BASE_VIEWMGR dynamic_cast<ui_base_viewmgr *>(ui_iface_viewmgr<Evas_Object *>::get_instance())

using namespace efl_viewmanager;

#endif /* UI_BASE_VIEWMANAGER_H */
