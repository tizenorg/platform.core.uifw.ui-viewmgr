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
#ifndef _UI_MOBILE_VIEWMANAGER_CAPI_H_
#define _UI_MOBILE_VIEWMANAGER_CAPI_H_

/**
 * @internal
 * @defgroup CAPI_UI_VIEWMGR ui-viewmgr
 * @brief This module provides functionalities to manage view of application's.
 * @section UI_VIEWMGR_GROUP_HEADER Required Header
 *   \#include <ui_viewmanager.h>
 *
 * @section CAPI_UI_VIEWMGR_MODULE_OVERVIEW Overview
 * ui-viewmgr provides functionalities to manage view of application's.
 * It includes below features.
 * 1. View Life-cycle events.
 * 2. Support view managing methods.
 * 3. H/W key event support by each view.
 * 4. Considered overlay controls as view.(ex.Popup, ctxpoup)
 * 5. Support profile specific UX.
 */

#include <Elementary.h>
#include <app.h>
#include <dlog.h>

//FIXME?
#ifndef Elm_Conformant
#define Elm_Conformant Evas_Object
#endif

#ifndef Elm_Ctxpopup
#define Elm_Ctxpopup Evas_Object
#endif

typedef struct ui_viewmgr_s ui_viewmgr;
typedef struct ui_view_s ui_view;
typedef struct ui_menu_s ui_menu;
typedef struct ui_popup_s ui_popup;

//FIXME: better way?
#include "../../../interface/ui_iface_types.h"

#include "ui_application.h"
#include "ui_menu.h"
#include "ui_popup.h"
#include "ui_viewmgr.h"
#include "ui_view.h"
#include "ui_standard_view.h"

#endif /* UI_MOBILE_VIEWMANAGER_CAPI_H */
