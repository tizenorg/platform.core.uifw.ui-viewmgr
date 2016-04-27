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
#ifndef _UI_IMPL_APP_H_
#define _UI_IMPL_APP_H_

namespace efl_viewmgr
{

class ui_viewmgr;
class ui_app;

class ui_impl_app : public viewmgr::singleton<ui_impl_app>
{
private:
	ui_viewmgr *viewmgr;
	ui_app *app;
	Eina_Stringshare *pkg;
	Eina_Stringshare *locale_dir;

public:
	ui_impl_app(ui_app *app, const char *pkg, const char *locale_dir);
	virtual ~ui_impl_app();

	bool initialize();
	bool run(int agrc, char **argv);
	bool activate();
	bool deactivate();

	ui_viewmgr *get_viewmgr();

	/* appfw events */
	bool on_create();
	void on_terminate();
	void on_pause();
	void on_resume();
	void on_control(app_control_h app_control);

	void on_low_battery(app_event_info_h event_info);
	void on_low_memory(app_event_info_h event_info);
	void on_region_changed(app_event_info_h event_info);
	void on_orient_changed(app_event_info_h event_info);
	void on_lang_changed(app_event_info_h event_info);
};

}

#endif /* _UI_IMPL_APP_H_ */
