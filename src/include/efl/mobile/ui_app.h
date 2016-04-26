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
#ifndef UI_APP_H
#define UI_APP_H

#include "../ui_base_viewmanager.h"

namespace efl_viewmgr
{

class ui_viewmgr;

class ui_app
{
private:
	ui_viewmgr *viewmgr;
	Eina_Stringshare *pkg;
	Eina_Stringshare *locale_dir;

public:
	ui_app(const char *pkg, const char *locale_dir);
	virtual ~ui_app();

	virtual int start(int argc, char **argv);
	virtual bool on_create();
	virtual void on_terminate();
	virtual void on_pause();
	virtual void on_resume();
	virtual void on_control(app_control_h app_control);
};

}

#endif /* UI_APP_H */
