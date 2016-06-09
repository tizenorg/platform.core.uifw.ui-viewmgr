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
#ifndef _UI_IFACE_VIEWMANAGER_H_
#define _UI_IFACE_VIEWMANAGER_H_

#include <dlog.h>

/**
 * Possible values for indicator state.
 */
enum ui_view_indicator
{
	UI_VIEW_INDICATOR_DEFAULT = 0, ///< Opaque indicator
	UI_VIEW_INDICATOR_OPTIMAL,     ///< Transparent indicator
	UI_VIEW_INDICATOR_OVERLAP,     ///< Overlap indicator
	UI_VIEW_INDICATOR_HIDE,        ///< Indicator hide
	UI_VIEW_INDICATOR_SHOW,        ///< Indicator show
	UI_VIEW_INDICATOR_LAST
};

/**
 * Possible values for view state.
 */
enum ui_view_state
{
	UI_VIEW_STATE_LOAD = 0,        ///< Load state
	UI_VIEW_STATE_UNLOAD,          ///< Unload state
	UI_VIEW_STATE_ACTIVATE,        ///< Activate state
	UI_VIEW_STATE_DEACTIVATE,      ///< Deactivate state
	UI_VIEW_STATE_PAUSE,           ///< Pause state
	UI_VIEW_STATE_LAST
};

#define UI_EFL 1

#if UI_EFL
	#include <Elementary.h>
	typedef Evas_Object* T;
#elif UI_DALI
#endif

#ifdef  LOG_TAG
#undef  LOG_TAG
#endif
#define LOG_TAG "UI_VIEWMGR"

#define _UI_DECLARE_FRIENDS(A) \
	friend class A##_impl; \
	friend class A

#define _UI_DECLARE_PRIVATE_IMPL(A) \
	class A##_impl *impl; \
	friend class A##_impl

#define _UI_DISABLE_COPY_AND_ASSIGN(A) \
	A(const A&) = delete; \
	const A& operator=(const A&) = delete

#include <app.h>
#include "ui_iface_rotatable.h"
#include "ui_iface_overlay.h"
#include "ui_iface_view.h"
#include "ui_iface_viewmgr.h"
#include "ui_iface_app.h"

using namespace ui_viewmanager;


#endif /* UI_IFACE_VIEWMANAGER_H */
