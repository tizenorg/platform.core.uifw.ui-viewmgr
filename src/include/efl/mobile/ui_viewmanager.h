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

#if 0
#include "ui_view.h"
#include "ui_key_listener.h"
#include "ui_viewmgr.h"
#include "ui_menu.h"
#include "ui_popup.h"
#endif

#define _UI_DECLARE_PRIVATE_IMPL(A) \
		class A##_impl* impl; \
		friend class A##_impl

#define _UI_DISABLE_COPY_AND_ASSIGN(A) \
		A(const A&) = delete; \
		const A& operator=(const A&) = delete

#include "ui_app.h"
