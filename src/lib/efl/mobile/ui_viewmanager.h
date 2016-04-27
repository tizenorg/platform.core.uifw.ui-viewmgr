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
#include <app.h>
#include <dlog.h>
#include <system_settings.h>
#include <Elementary.h>

#ifdef  LOG_TAG
#undef  LOG_TAG
#endif
#define LOG_TAG "UI_VIEWMGR"

#include "ui_view.h"
#include "ui_key_listener.h"
#include "ui_viewmgr.h"
#include "ui_menu.h"
#include "ui_popup.h"
#include "ui_app.h"

using namespace efl_viewmgr;
using namespace viewmgr;

#define UI_VIEWMGR efl_viewmgr::ui_app_impl::get_instance()->get_viewmgr()
