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
#include "page8_controller.h"

class page8: public ui_basic_view
{
private:
	appdata_s *ad;

public:
	page8(ui_controller *controller, const char *name, appdata_s *ad)
		: ui_basic_view(controller, name), ad(ad)
	{
		ad->viewmgr->push_view(this);
	}

	~page8()
	{
	}
};

void create_page8(appdata_s *ad)
{
	/* This page is case for inherit view instead of controller in application.
	   You can add controller for view create, otherwise create content in view
	   constructor.*/
	new page8(new page8_controller(ad), "page8", ad);
}
