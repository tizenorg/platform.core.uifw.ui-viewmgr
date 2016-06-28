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

/***********************************************************************************************/
/* Internal class Implementation                                                               */
/***********************************************************************************************/
namespace ui_viewmanager
{

class UiIfaceAppImpl
{
public:
	friend class UiIfaceApp;

	UiIfaceApp *app;
	UiIfaceViewmgr *viewmgr;
	Eina_Stringshare *pkg;
	Eina_Stringshare *locale_dir;

	UiIfaceAppImpl(UiIfaceApp *app, const char *pkg, const char *locale_dir, UiIfaceViewmgr* viewmgr);
	~UiIfaceAppImpl();

	int run(int argc, char **argv);

	bool init();
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

static bool app_create(void *data)
{
	UiIfaceAppImpl *app = static_cast<UiIfaceAppImpl *>(data);
	return app->on_create();
}

static void app_terminate(void *data)
{
	UiIfaceAppImpl *app = static_cast<UiIfaceAppImpl *>(data);
	app->on_terminate();
}

static void app_pause(void *data)
{
	UiIfaceAppImpl *app = static_cast<UiIfaceAppImpl *>(data);
	app->on_pause();
}

static void app_resume(void *data)
{
	UiIfaceAppImpl *app = static_cast<UiIfaceAppImpl *>(data);
	app->on_resume();
}

static void app_control(app_control_s *app_control, void *data)
{
	UiIfaceAppImpl *app = static_cast<UiIfaceAppImpl *>(data);
	app->on_control(app_control);
}

static void ui_app_lang_changed(app_event_info_h event_info, void *data)
{
	UiIfaceAppImpl *app = static_cast<UiIfaceAppImpl *>(data);
	app->on_lang_changed(event_info);
}

static void ui_app_orient_changed(app_event_info_h event_info, void *data)
{
	UiIfaceAppImpl *app = static_cast<UiIfaceAppImpl *>(data);
	app->on_orient_changed(event_info);
}

static void ui_app_region_changed(app_event_info_h event_info, void *data)
{
	UiIfaceAppImpl *app = static_cast<UiIfaceAppImpl *>(data);
	app->on_region_changed(event_info);
}

static void ui_app_low_battery(app_event_info_h event_info, void *data)
{
	UiIfaceAppImpl *app = static_cast<UiIfaceAppImpl *>(data);
	app->on_low_battery(event_info);
}

static void ui_app_low_memory(app_event_info_h event_info, void *data)
{
	UiIfaceAppImpl *app = static_cast<UiIfaceAppImpl *>(data);
	app->on_low_memory(event_info);
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

	event_callback.create = app_create;
	event_callback.terminate = app_terminate;
	event_callback.pause = app_pause;
	event_callback.resume = app_resume;
	event_callback.app_control = app_control;

	ui_app_add_event_handler(&handlers[APP_EVENT_LOW_BATTERY], APP_EVENT_LOW_BATTERY, ui_app_low_battery, this);
	ui_app_add_event_handler(&handlers[APP_EVENT_LOW_MEMORY], APP_EVENT_LOW_MEMORY, ui_app_low_memory, this);
	ui_app_add_event_handler(&handlers[APP_EVENT_DEVICE_ORIENTATION_CHANGED], APP_EVENT_DEVICE_ORIENTATION_CHANGED, ui_app_orient_changed, this);
	ui_app_add_event_handler(&handlers[APP_EVENT_LANGUAGE_CHANGED], APP_EVENT_LANGUAGE_CHANGED, ui_app_lang_changed, this);
	ui_app_add_event_handler(&handlers[APP_EVENT_REGION_FORMAT_CHANGED], APP_EVENT_REGION_FORMAT_CHANGED, ui_app_region_changed, this);

	int ret = ui_app_main(argc, argv, &event_callback, this);

	if (ret != APP_ERROR_NONE)
	{
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

void UiIfaceAppImpl::on_lang_changed(app_event_info_h event_info)
{
	this->app->on_lang_changed(event_info);
}

void UiIfaceAppImpl::on_low_memory(app_event_info_h event_info)
{
	this->app->on_low_memory(event_info);
}

void UiIfaceAppImpl::on_low_battery(app_event_info_h event_info)
{
	this->app->on_low_battery(event_info);
}

void UiIfaceAppImpl::on_region_changed(app_event_info_h event_info)
{
	this->app->on_region_changed(event_info);
}

void UiIfaceAppImpl::on_orient_changed(app_event_info_h event_info)
{
	this->app->on_orient_changed(event_info);
}

bool UiIfaceAppImpl::on_create()
{
	return this->app->on_create();
}

void UiIfaceAppImpl::on_pause()
{
	this->app->on_pause();
}

void UiIfaceAppImpl::on_resume()
{
	this->app->on_resume();
}

void UiIfaceAppImpl::on_control(app_control_h app_control)
{
	this->app->on_control(app_control);
}

void UiIfaceAppImpl::on_terminate()
{
	this->app->on_terminate();
}

/***********************************************************************************************/
/* External class Implementation                                                               */
/***********************************************************************************************/

static UiIfaceApp *inst = NULL;

void UiIfaceApp::on_lang_changed(app_event_info_h event_info)
{
	char *language = NULL;
	int ret = app_event_get_language(event_info, &language);
	if (ret != APP_ERROR_NONE) {
		dlog_print(DLOG_ERROR, LOG_TAG, "app_event_get_language() failed. Err = %d.", ret);
		return;
	}

	if (language != NULL) {
		elm_language_set(language);
		UiIfaceView *view = this->impl->viewmgr->get_last_view();
		view->on_language_changed(language);
		free(language);
	}
}

void UiIfaceApp::on_low_memory(app_event_info_h event_info)
{
	UiIfaceView *view = this->impl->viewmgr->get_last_view();
	view->on_low_memory();
}

void UiIfaceApp::on_low_battery(app_event_info_h event_info)
{
	UiIfaceView *view = this->impl->viewmgr->get_last_view();
	view->on_low_battery();
}

void UiIfaceApp::on_region_changed(app_event_info_h event_info)
{
	char *region = NULL;
	int ret = app_event_get_region_format(event_info, &region);
	if (ret != APP_ERROR_NONE) {
		dlog_print(DLOG_ERROR, LOG_TAG, "model_app_event_get_region_format() failed. Err = %d", ret);
		return;
	}

	UiIfaceView *view = this->impl->viewmgr->get_last_view();
	view->on_region_changed(region);
}

void UiIfaceApp::on_orient_changed(app_event_info_h event_info)
{
}

bool UiIfaceApp::on_create()
{
	return this->impl->init();
}

void UiIfaceApp::on_pause()
{
	this->impl->viewmgr->deactivate();
}

void UiIfaceApp::on_resume()
{
//	this->impl->viewmgr->activate();
}

void UiIfaceApp::on_control(app_control_h app_control)
{
	/* Handle the launch request. */
	this->impl->viewmgr->activate();
}

void UiIfaceApp::on_terminate()
{
	delete(this);
}

UiIfaceApp::UiIfaceApp(const char *pkg, const char *locale_dir, UiIfaceViewmgr *viewmgr)
{
	if (inst)
	{
		LOGE("You created UiIfaceApp multiple times!!");
	}
	inst = this;

	this->impl = new UiIfaceAppImpl(this, pkg, locale_dir, viewmgr);
}

int UiIfaceApp::run(int argc, char **argv)
{
	return this->impl->run(argc, argv);
}

UiIfaceApp::~UiIfaceApp()
{
	delete (this->impl);
	inst = NULL;
}

UiIfaceViewmgr *UiIfaceApp::get_viewmgr()
{
	return this->impl->viewmgr;
}

UiIfaceApp *UiIfaceApp::get_instance()
{
	return inst;
}
