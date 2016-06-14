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

#define ui_viewmgr void
#define ui_view void
#define ui_menu void
#define ui_popup void

//FIXME: better way?
#include "../../../interface/ui_iface_types.h"

#include "ui_app.h"
#include "ui_menu.h"
#include "ui_popup.h"
#include "ui_viewmgr.h"
#include "ui_view.h"

#endif /* UI_MOBILE_VIEWMANAGER_CAPI_H */
