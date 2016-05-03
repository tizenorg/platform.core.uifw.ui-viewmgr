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
#ifndef _UI_APP_H_
#define _UI_APP_H_

namespace efl_viewmanager
{

class ui_viewmgr;

class ui_app
{
public:
	ui_app(const char *pkg, const char *locale_dir);
	virtual ~ui_app();

	ui_viewmgr *get_viewmgr();
	static ui_app *get_instance();

	virtual int run(int argc, char **argv);

protected:
	virtual bool on_create();
	virtual void on_terminate();
	virtual void on_pause();
	virtual void on_resume();
	virtual void on_control(app_control_h app_control);

	virtual void on_low_battery(app_event_info_h event_info);
	virtual void on_low_memory(app_event_info_h event_info);
	virtual void on_region_changed(app_event_info_h event_info);
	virtual void on_orient_changed(app_event_info_h event_info);
	virtual void on_lang_changed(app_event_info_h event_info);

private:
	_UI_DECLARE_PRIVATE_IMPL(ui_app);
	_UI_DISABLE_COPY_AND_ASSIGN(ui_app);
};

}

#endif /* _UI_APP_H_ */
