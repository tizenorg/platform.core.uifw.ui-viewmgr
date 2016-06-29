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
#ifndef _UI_IFACE_APP_H_
#define _UI_IFACE_APP_H_

namespace ui_viewmanager {

class UiIfaceViewmgr;

/**
 *  @class UiIfaceApp
 *
 *  @ingroup ui_viewmanager
 *
 *  @brief UiIfaceApp is designed for wrapping the application instance. This class hides unnecessary application settings but expose only basic functions
 *         such as initialization and run. Basically, it works on the application life-cycle. It has application life-cycle event interfaces such as create(),
 *         pause(), resume(), terminate(), etc so that users can handle those events for the their application concept. Also, It provides system event
 *         interfaces such as low_baterry(), low_meomory(), lang_changed(), region_changed() and so on. UiIfaceApp create an unique ui_viewmgr instance
 *         internally, and manage its life.
 */
class UiIfaceApp
{
public:
	/**
	 *  @brief This is a constructor for initializing UiIfaceApp.
	 *
	 *  @param pkg The name of package.
	 *  @param loale_dir The path of locale directory.
	 *  @param viewmgr instance of ui_viewmgr.
	 */
	UiIfaceApp(const char *pkg, const char *locale_dir, UiIfaceViewmgr *viewmgr);

	///Destructor.
	virtual ~UiIfaceApp();

	/**
	 *  @brief Return the viewmgr instance.
	 *
	 *  @return UiIfaceViewmgr instance.
	 */
	UiIfaceViewmgr *getViewmgr();

	/**
	 *  @brief Return UiIfaceApp instance.
	 *
	 *  @return The instance of UiIfaceApp.
	 */
	static UiIfaceApp *getInstance();

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
	virtual bool onCreate();

	/**
	 *  @brief Calling before the main event loop finish.
	 *
	 *  @note Release all resources here.
	 */
	virtual void onTerminate();

	/**
	 *  @brief Calling when application becomes invisible.
	 */
	virtual void onPause();

	/**
	 *  @brief Calling when application becomes visible.
	 */
	virtual void onResume();

	/**
	 *  @brief Calling when gets a launch request event.
	 *
	 *  @param app_control_h The instance of app_control_h.
	 */
	virtual void onControl(app_control_h app_control);

	/**
	 *  @brief Calling when device low battery.
	 *
	 *  @param app_event_info_h The instance of app_event_info_h.
	 */
	virtual void onLowBattery(app_event_info_h event_info);

	/**
	 *  @brief Calling when device low memory.
	 *
	 *  @param app_event_info_h The instance of app_event_info_h.
	 */
	virtual void onLowMemory(app_event_info_h event_info);

	/**
	 *  @brief Calling when device region changed.
	 *
	 *  @param app_event_info_h The instance of app_event_info_h.
	 */
	virtual void onRegionChanged(app_event_info_h event_info);

	/**
	 *  @brief Calling when device orient changed.
	 *
	 *  @param app_event_info_h The instance of app_event_info_h.
	 */
	virtual void onOrientChanged(app_event_info_h event_info);

	/**
	 *  @brief Calling when language changed.
	 *
	 *  @param app_event_info_h The instance of app_event_info_h.
	 */
	virtual void onLangChanged(app_event_info_h event_info);

private:
	_UI_DECLARE_PRIVATE_IMPL(UiIfaceApp);
	_UI_DISABLE_COPY_AND_ASSIGN(UiIfaceApp);
	_UI_DECLARE_FRIENDS(UiIfaceView);
};

}

#endif /* _UI_IFACE_APP_H_ */
