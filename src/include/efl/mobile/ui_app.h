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
	///Constructor.
	ui_app(const char *pkg, const char *locale_dir);

	///Destructor.
	virtual ~ui_app();

	/**
	 *  @brief Return the viewmgr instance.
	 *
	 *  @return ui_viewmgr instance.
	 */
	ui_viewmgr *get_viewmgr();

	/**
	 *  @brief Return ui_app instance.
	 */
	static ui_app *get_instance();

	/**
	 *  @brief Application life-cycle start and add application event callback functions add.
	 *
	 *  @note This is calling ui_app_main function to start application life-cycle start.
	 *        and adding all of the functions for application events handling such as
	 *        create, terminate, pause, resume, app_control, APP_EVENT_LOW_BATTERY, APP_EVENT_LOW_MEMORY
	 *        APP_EVENT_DEVICE_ORIENTATION_CHANGED, APP_EVENT_LANGUAGE_CHANGED, APP_EVENT_REGION_FORMAT_CHANGED.
	 *        Application can add those events using wrapping functions by viewmgr supported.
	 */
	virtual int run(int argc, char **argv);

protected:
	/**
	 *  @brief Calling before the main event loop start.
	 *
	 *  @note Take necessary actions like a Initialize UI resources and application data.
	 *
	 *  @return If this function returns true, the application main loop starts.
	 *          If this function returns false, the application terminates.
	 */
	virtual bool on_create();

	/**
	 *  @brief Calling before the main event loop finish.
	 *
	 *  @note Release all resources here.
	 */
	virtual void on_terminate();

	/**
	 *  @brief Calling when application becomes invisible.
	 */
	virtual void on_pause();

	/**
	 *  @brief Calling when application becomes visible.
	 */
	virtual void on_resume();

	/**
	 *  @brief Calling when gets a launch request event.
	 */
	virtual void on_control(app_control_h app_control);

	/**
	 *  @brief Calling when device low battery.
	 */
	virtual void on_low_battery(app_event_info_h event_info);

	/**
	 *  @brief Calling when device low memory.
	 */
	virtual void on_low_memory(app_event_info_h event_info);

	/**
	 *  @brief Calling when device region changed.
	 */
	virtual void on_region_changed(app_event_info_h event_info);

	/**
	 *  @brief Calling when device orient changed.
	 */
	virtual void on_orient_changed(app_event_info_h event_info);

	/**
	 *  @brief Calling when language changed.
	 */
	virtual void on_lang_changed(app_event_info_h event_info);

private:
	_UI_DECLARE_PRIVATE_IMPL(ui_app);
	_UI_DISABLE_COPY_AND_ASSIGN(ui_app);
};

}

#endif /* _UI_APP_H_ */