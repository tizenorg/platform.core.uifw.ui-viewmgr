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
#include <app.h>

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
	friend class A##Impl; \
	friend class A

#define _UI_DECLARE_PRIVATE_IMPL(A) \
	class A##Impl *_impl; \
	friend class A##Impl

#define _UI_DISABLE_COPY_AND_ASSIGN(A) \
	A(const A&) = delete; \
	const A& operator=(const A&) = delete

#ifdef __GNUC__
	#if __GNUC__ >= 4
		#ifndef EAPI
			#define EAPI __attribute__ ((visibility("default")))
		#endif
	#endif
#endif

#include "UiIfaceTypes.h"
#include "UiIfaceRotatable.h"
#include "UiIfaceOverlay.h"
#include "UiIfaceView.h"
#include "UiIfaceViewmgr.h"
#include "UiIfaceApp.h"

#endif /* UI_IFACE_VIEWMANAGER_H */
