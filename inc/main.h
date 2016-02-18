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
#include <system_settings.h>
#include <dlog.h>
#include <efl_extension.h>
#include "../src/efl/mobile/efl_viewmgr.h"

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

using namespace efl;

typedef struct appdata {
	ui_viewmgr *viewmgr;
} appdata_s;

Evas_Object *create_content(Evas_Object *parent, const char *text, Evas_Smart_Cb prev_btn_clicked_cb, Evas_Smart_Cb next_btn_clicked_cb, appdata_s *ad);
