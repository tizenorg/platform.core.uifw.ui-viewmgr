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
#include "../../../include/efl/mobile/UiMobileViewManager.h"

using namespace ui_viewmanager;
using namespace efl_viewmanager;

/***********************************************************************************************/
/* Internal class Implementation                                                               */
/***********************************************************************************************/

/***********************************************************************************************/
/* External class Implementation                                                               */
/***********************************************************************************************/

UiApp::UiApp(const char *pkg, const char *locale_dir)
		: UiIfaceApp(pkg, locale_dir, new UiViewmgr(pkg))
{
}

UiApp::~UiApp()
{
}

UiViewmgr *UiApp::getViewmgr()
{
	return dynamic_cast<UiViewmgr*>(UiIfaceApp::getViewmgr());
}

UiApp *UiApp::getInstance()
{
	return dynamic_cast<UiApp*>(UiIfaceApp::getInstance());
}
