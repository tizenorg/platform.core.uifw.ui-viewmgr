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
#include <dlog.h>
#include <UiViewManager.h>

//uncomment if you want debug
#ifndef TIZEN_ENGINEER_MODE
#define TIZEN_ENGINEER_MODE
#endif

#ifdef  LOG_TAG
#undef  LOG_TAG
#endif
#define LOG_TAG "UI_VIEWMGR"

#if !defined(PACKAGE)
#define PACKAGE "ui-viewmgr"
#endif

Evas_Object *create_landscape_content(Evas_Object *parent, const char *text, Evas_Smart_Cb prev_btn_clicked_cb, Evas_Smart_Cb next_btn_clicked_cb);
Evas_Object *create_content(Evas_Object *parent, const char *text, Evas_Smart_Cb prev_btn_clicked_cb, Evas_Smart_Cb next_btn_clicked_cb);
Evas_Object *create_scrolling_content(Evas_Object *parent);
Evas_Object* create_title_handle_content(Evas_Object *parent, Evas_Smart_Cb prev_btn_clicked_cb, Evas_Smart_Cb next_btn_clicked_cb,
					Evas_Smart_Cb title_show_btn_clicked_cb, Evas_Smart_Cb title_hide_btn_clicked_cb,
					Evas_Smart_Cb title_show_anim_btn_clicked_cb, Evas_Smart_Cb title_hide_anim_btn_clicked_cb, UiView *view);
Elm_Toolbar *create_toolbar(Evas_Object *parent, const char *style);
