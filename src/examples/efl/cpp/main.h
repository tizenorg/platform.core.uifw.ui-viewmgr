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

using namespace efl_viewmanager;

Evas_Object *createLandscapeContent(Evas_Object *parent, const char *text, Evas_Smart_Cb _prevBtnClickedCb, Evas_Smart_Cb _nextBtnClickedCb);
Evas_Object *createContent(Evas_Object *parent, const char *text, Evas_Smart_Cb _prevBtnClickedCb, Evas_Smart_Cb _nexBtnClickedCb);
Evas_Object *createScrollingContent(Evas_Object *parent);
Evas_Object* createTitleHandleContent(Evas_Object *parent, Evas_Smart_Cb _prevBtnClickedCb, Evas_Smart_Cb _nextBtnClickedCb,
					Evas_Smart_Cb _titleShowBtnClickedCb, Evas_Smart_Cb _titleHideBtnClickedCb,
					Evas_Smart_Cb _titleShowAnimBtnClickedCb, Evas_Smart_Cb _titleHideAnimBtnClickedCb, UiView *view);
Elm_Toolbar *createToolbar(Evas_Object *parent, const char *style);
