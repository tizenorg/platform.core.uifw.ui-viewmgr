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
#ifndef UI_VIEWMGR_H_
#define UI_VIEWMGR_H_

#include <app.h>
#include <dlog.h>

#ifdef  LOG_TAG
#undef  LOG_TAG
#endif
#define LOG_TAG "VIEWMGR"

enum ui_view_indicator
{
	UI_VIEW_INDICATOR_DEFAULT = 0,
	UI_VIEW_INDICATOR_OPTIMAL,
	UI_VIEW_INDICATOR_OVERLAP,
	UI_VIEW_INDICATOR_HIDE,
	UI_VIEW_INDICATOR_LAST
};

#include "ui_viewmgr_base.h"
#include "ui_view_base.h"
#include "ui_controller_base.h"


#endif /* UI_VIEWMGR_H */
