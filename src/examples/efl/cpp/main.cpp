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
#include "main.h"

#include "page16.h"
#include "page15.h"
#include "page14.h"
#include "page13.h"
#include "page12.h"
#include "page11.h"
#include "page10.h"
#include "page9.h"
#include "page8.h"
#include "page7.h"
#include "page6.h"
#include "page5.h"
#include "page4.h"
#include "page3.h"
#include "page2.h"
#include "page1.h"

class SampleApp: public UiApp
{
public:
	SampleApp()
			: UiApp(PACKAGE, LOCALE_DIR)
	{
	}
	~SampleApp()
	{
	}

protected:
	bool onCreate()
	{
		if (!UiApp::onCreate())
		{
			return false;
		}

		//Push first view in viewmgr.
		UI_VIEWMGR->pushView(new page1());

		return true;
	}
};

int main(int argc, char *argv[])
{
	SampleApp app;
	return app.run(argc, argv);
}
