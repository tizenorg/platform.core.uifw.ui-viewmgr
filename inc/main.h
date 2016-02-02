/*
 * Copyright (c) 2015 Samsung Electronics Co., Ltd All Rights Reserved
 *
 * Licensed under the Apache License, Version 2.0 (the License);
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an AS IS BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <app.h>
#include <Elementary.h>
#include <system_settings.h>
#include <dlog.h>
#include <efl_extension.h>

//uncomment if you want debug
#ifndef TIZEN_ENGINEER_MODE
#define TIZEN_ENGINEER_MODE
#endif

#ifdef  LOG_TAG
#undef  LOG_TAG
#endif
#define LOG_TAG "VIEWMGR"

#if !defined(PACKAGE)
#define PACKAGE "org.tizen.ui-viewmgr"
#endif

#define ELM_DEMO_EDJ "/opt/usr/apps/org.tizen.ui-viewmgr/res/ui-viewmgr.edj"

typedef struct appdata {
	Evas_Object *win;
} appdata_s;

void view_cb(void *data, Evas_Object *obj, void *event_info);
