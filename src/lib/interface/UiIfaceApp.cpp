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
#include <system_settings.h>
#include "../../include/interface/UiIfaceViewManager.h"

using namespace ui_viewmanager;

/***********************************************************************************************/
/* Internal class Implementation                                                               */
/***********************************************************************************************/
namespace ui_viewmanager
{

class UiIfaceAppImpl
{
public:
	friend class UiIfaceApp;

	UiIfaceApp *app = NULL;
	UiIfaceViewmgr *viewmgr = NULL;
	Eina_Stringshare *pkg = NULL;
	Eina_Stringshare *locale_dir = NULL;

	UiIfaceAppImpl(UiIfaceApp *app, const char *pkg, const char *locale_dir, UiIfaceViewmgr* viewmgr);
	~UiIfaceAppImpl();

	int run(int argc, char **argv);

	bool init();
	bool onCreate();
	void onTerminate();
	void onPause();
	void onResume();
	void onControl(app_control_h app_control);

	void onLowBattery(app_event_info_h event_info);
	void onLowMemory(app_event_info_h event_info);
	void onRegionChanged(app_event_info_h event_info);
	void onOrientChanged(app_event_info_h event_info);
	void onLangChanged(app_event_info_h event_info);
};

}

static bool appCreate(void *data)
{
	UiIfaceAppImpl *app = static_cast<UiIfaceAppImpl *>(data);
	return app->onCreate();
}

static void appTerminate(void *data)
{
	UiIfaceAppImpl *app = static_cast<UiIfaceAppImpl *>(data);
	app->onTerminate();
}

static void appPause(void *data)
{
	UiIfaceAppImpl *app = static_cast<UiIfaceAppImpl *>(data);
	app->onPause();
}

static void appResume(void *data)
{
	UiIfaceAppImpl *app = static_cast<UiIfaceAppImpl *>(data);
	app->onResume();
}

static void appControl(app_control_s *app_control, void *data)
{
	UiIfaceAppImpl *app = static_cast<UiIfaceAppImpl *>(data);
	app->onControl(app_control);
}

static void uiAppLangChanged(app_event_info_h event_info, void *data)
{
	UiIfaceAppImpl *app = static_cast<UiIfaceAppImpl *>(data);
	app->onLangChanged(event_info);
}

static void uiAppOrientChanged(app_event_info_h event_info, void *data)
{
	UiIfaceAppImpl *app = static_cast<UiIfaceAppImpl *>(data);
	app->onOrientChanged(event_info);
}

static void uiAppRegionChanged(app_event_info_h event_info, void *data)
{
	UiIfaceAppImpl *app = static_cast<UiIfaceAppImpl *>(data);
	app->onRegionChanged(event_info);
}

static void uiAppLowBattery(app_event_info_h event_info, void *data)
{
	UiIfaceAppImpl *app = static_cast<UiIfaceAppImpl *>(data);
	app->onLowBattery(event_info);
}

static void uiAppLowMemory(app_event_info_h event_info, void *data)
{
	UiIfaceAppImpl *app = static_cast<UiIfaceAppImpl *>(data);
	app->onLowMemory(event_info);
}

bool UiIfaceAppImpl::init()
{
	/* Bind package locale file */
	bindtextdomain(this->pkg, this->locale_dir);
	textdomain(this->pkg);

	return true;
}

UiIfaceAppImpl::UiIfaceAppImpl(UiIfaceApp *app, const char *pkg, const char *locale_dir, UiIfaceViewmgr *viewmgr)
		: app(app), viewmgr(viewmgr)
{
	this->pkg = eina_stringshare_add(pkg);
	this->locale_dir = eina_stringshare_add(locale_dir);
}

int UiIfaceAppImpl::run(int argc, char **argv)
{
	ui_app_lifecycle_callback_s event_callback = { 0, };
	app_event_handler_h handlers[5] = { NULL, };

	event_callback.create = appCreate;
	event_callback.terminate = appTerminate;
	event_callback.pause = appPause;
	event_callback.resume = appResume;
	event_callback.app_control = appControl;

	ui_app_add_event_handler(&handlers[APP_EVENT_LOW_BATTERY], APP_EVENT_LOW_BATTERY, uiAppLowBattery, this);
	ui_app_add_event_handler(&handlers[APP_EVENT_LOW_MEMORY], APP_EVENT_LOW_MEMORY, uiAppLowMemory, this);
	ui_app_add_event_handler(&handlers[APP_EVENT_DEVICE_ORIENTATION_CHANGED], APP_EVENT_DEVICE_ORIENTATION_CHANGED, uiAppOrientChanged, this);
	ui_app_add_event_handler(&handlers[APP_EVENT_LANGUAGE_CHANGED], APP_EVENT_LANGUAGE_CHANGED, uiAppLangChanged, this);
	ui_app_add_event_handler(&handlers[APP_EVENT_REGION_FORMAT_CHANGED], APP_EVENT_REGION_FORMAT_CHANGED, uiAppRegionChanged, this);

	int ret = ui_app_main(argc, argv, &event_callback, this);

	if (ret != APP_ERROR_NONE) {
		LOGE("ui_app_main() is failed. err = %d", ret);
	}

	return ret;
}

UiIfaceAppImpl::~UiIfaceAppImpl()
{
	delete (this->viewmgr);
	eina_stringshare_del(this->pkg);
	eina_stringshare_del(this->locale_dir);
}

void UiIfaceAppImpl::onLangChanged(app_event_info_h event_info)
{
	this->app->onLangChanged(event_info);
}

void UiIfaceAppImpl::onLowMemory(app_event_info_h event_info)
{
	this->app->onLowMemory(event_info);
}

void UiIfaceAppImpl::onLowBattery(app_event_info_h event_info)
{
	this->app->onLowBattery(event_info);
}

void UiIfaceAppImpl::onRegionChanged(app_event_info_h event_info)
{
	this->app->onRegionChanged(event_info);
}

void UiIfaceAppImpl::onOrientChanged(app_event_info_h event_info)
{
	this->app->onOrientChanged(event_info);
}

bool UiIfaceAppImpl::onCreate()
{
	return this->app->onCreate();
}

void UiIfaceAppImpl::onPause()
{
	this->app->onPause();
}

void UiIfaceAppImpl::onResume()
{
	this->app->onResume();
}

void UiIfaceAppImpl::onControl(app_control_h app_control)
{
	this->app->onControl(app_control);
}

void UiIfaceAppImpl::onTerminate()
{
	this->app->onTerminate();
}

/***********************************************************************************************/
/* External class Implementation                                                               */
/***********************************************************************************************/

static UiIfaceApp *_inst = NULL;

void UiIfaceApp::onLangChanged(app_event_info_h event_info)
{
	char *language = NULL;
	int ret = app_event_get_language(event_info, &language);
	if (ret != APP_ERROR_NONE) {
		dlog_print(DLOG_ERROR, LOG_TAG, "app_event_get_language() failed. Err = %d.", ret);
		return;
	}

	if (language != NULL) {
		elm_language_set(language);
		UiIfaceView *view = this->_impl->viewmgr->getLastView();
		view->onLanguageChanged(language);
		free(language);
	}
}

void UiIfaceApp::onLowMemory(app_event_info_h event_info)
{
	UiIfaceView *view = this->_impl->viewmgr->getLastView();
	view->onLowMemory();
}

void UiIfaceApp::onLowBattery(app_event_info_h event_info)
{
	UiIfaceView *view = this->_impl->viewmgr->getLastView();
	view->onLowBattery();
}

void UiIfaceApp::onRegionChanged(app_event_info_h event_info)
{
	char *region = NULL;
	int ret = app_event_get_region_format(event_info, &region);
	if (ret != APP_ERROR_NONE) {
		dlog_print(DLOG_ERROR, LOG_TAG, "model_app_event_get_region_format() failed. Err = %d", ret);
		return;
	}

	UiIfaceView *view = this->_impl->viewmgr->getLastView();
	view->onRegionChanged(region);
}

void UiIfaceApp::onOrientChanged(app_event_info_h event_info)
{
}

bool UiIfaceApp::onCreate()
{
	return this->_impl->init();
}

void UiIfaceApp::onPause()
{
	this->_impl->viewmgr->deactivate();
}

void UiIfaceApp::onResume()
{
//	this->_impl->viewmgr->activate();
}

void UiIfaceApp::onControl(app_control_h app_control)
{
	/* Handle the launch request. */
	this->_impl->viewmgr->activate();
}

void UiIfaceApp::onTerminate()
{
#ifndef TARGET_LANG_CPLUS
	delete(this);
#endif
}

UiIfaceApp::UiIfaceApp(const char *pkg, const char *locale_dir, UiIfaceViewmgr *viewmgr)
{
	if (_inst) {
		LOGE("You created UiIfaceApp multiple times!!");
	}
	_inst = this;

	this->_impl = new UiIfaceAppImpl(this, pkg, locale_dir, viewmgr);
}

int UiIfaceApp::run(int argc, char **argv)
{
	return this->_impl->run(argc, argv);
}

UiIfaceApp::~UiIfaceApp()
{
	delete (this->_impl);
	_inst = NULL;
}

UiIfaceViewmgr *UiIfaceApp::getViewmgr()
{
	return this->_impl->viewmgr;
}

UiIfaceApp *UiIfaceApp::getInstance()
{
	return _inst;
}
