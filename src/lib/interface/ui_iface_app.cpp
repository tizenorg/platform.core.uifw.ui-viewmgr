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
#include "../../include/interface/ui_iface_viewmanager.h"

/***********************************************************************************************/
/* Internal class Implementation                                                               */
/***********************************************************************************************/
namespace ui_viewmanager
{

class ui_iface_app_impl
{
public:
	friend class ui_iface_app;

	ui_iface_app *app;
	ui_iface_viewmgr *viewmgr;
	Eina_Stringshare *pkg;
	Eina_Stringshare *locale_dir;

	ui_iface_app_impl(ui_iface_app *app, const char *pkg, const char *locale_dir, ui_iface_viewmgr* viewmgr);
	~ui_iface_app_impl();

	int run(int argc, char **argv);

	bool init();
	bool on_create();
	void on_terminate();
	void on_pause();
	void on_resume();
	void on_control(app_control_h app_control);

	//
	void on_low_battery(app_event_info_h event_info);
	void on_low_memory(app_event_info_h event_info);
	void on_region_changed(app_event_info_h event_info);
	void on_orient_changed(app_event_info_h event_info);
	void on_lang_changed(app_event_info_h event_info);
};

}

static bool app_create(void *data)
{
	ui_iface_app_impl *app = static_cast<ui_iface_app_impl *>(data);
	return app->on_create();
}

static void app_terminate(void *data)
{
	ui_iface_app_impl *app = static_cast<ui_iface_app_impl *>(data);
	app->on_terminate();
}

static void app_pause(void *data)
{
	ui_iface_app_impl *app = static_cast<ui_iface_app_impl *>(data);
	app->on_pause();
}

static void app_resume(void *data)
{
	ui_iface_app_impl *app = static_cast<ui_iface_app_impl *>(data);
	app->on_resume();
}

static void app_control(app_control_s *app_control, void *data)
{
	ui_iface_app_impl *app = static_cast<ui_iface_app_impl *>(data);
	app->on_control(app_control);
}

static void ui_app_lang_changed(app_event_info_h event_info, void *data)
{
	ui_iface_app_impl *app = static_cast<ui_iface_app_impl *>(data);
	app->on_lang_changed(event_info);
}

static void ui_app_orient_changed(app_event_info_h event_info, void *data)
{
	ui_iface_app_impl *app = static_cast<ui_iface_app_impl *>(data);
	app->on_orient_changed(event_info);
}

static void ui_app_region_changed(app_event_info_h event_info, void *data)
{
	ui_iface_app_impl *app = static_cast<ui_iface_app_impl *>(data);
	app->on_region_changed(event_info);
}

static void ui_app_low_battery(app_event_info_h event_info, void *data)
{
	ui_iface_app_impl *app = static_cast<ui_iface_app_impl *>(data);
	app->on_low_battery(event_info);
}

static void ui_app_low_memory(app_event_info_h event_info, void *data)
{
	ui_iface_app_impl *app = static_cast<ui_iface_app_impl *>(data);
	app->on_low_memory(event_info);
}

bool ui_iface_app_impl::init()
{
	//FIXME: this scale value should be configurable.
	elm_app_base_scale_set(2.6);

	/* Bind package locale file */
	bindtextdomain(this->pkg, this->locale_dir);
	textdomain(this->pkg);

	return true;
}

ui_iface_app_impl::ui_iface_app_impl(ui_iface_app *app, const char *pkg, const char *locale_dir, ui_iface_viewmgr *viewmgr)
		: app(app), viewmgr(viewmgr)
{
	this->pkg = eina_stringshare_add(pkg);
	this->locale_dir = eina_stringshare_add(locale_dir);
}

int ui_iface_app_impl::run(int argc, char **argv)
{
	ui_app_lifecycle_callback_s event_callback =
	{ 0, };
	app_event_handler_h handlers[5] =
	{ NULL, };

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

ui_iface_app_impl::~ui_iface_app_impl()
{
	delete (this->viewmgr);
	eina_stringshare_del(this->pkg);
	eina_stringshare_del(this->locale_dir);
}

void ui_iface_app_impl::on_lang_changed(app_event_info_h event_info)
{
	this->app->on_lang_changed(event_info);
}

void ui_iface_app_impl::on_low_memory(app_event_info_h event_info)
{
	this->app->on_low_memory(event_info);
}

void ui_iface_app_impl::on_low_battery(app_event_info_h event_info)
{
	this->app->on_low_battery(event_info);
}

void ui_iface_app_impl::on_region_changed(app_event_info_h event_info)
{
	this->app->on_region_changed(event_info);
}

void ui_iface_app_impl::on_orient_changed(app_event_info_h event_info)
{
	this->app->on_orient_changed(event_info);
}

bool ui_iface_app_impl::on_create()
{
	return this->app->on_create();
}

void ui_iface_app_impl::on_pause()
{
	this->app->on_pause();
}

void ui_iface_app_impl::on_resume()
{
	this->app->on_resume();
}

void ui_iface_app_impl::on_control(app_control_h app_control)
{
	this->app->on_control(app_control);
}

void ui_iface_app_impl::on_terminate()
{
	this->app->on_terminate();
}

/***********************************************************************************************/
/* External class Implementation                                                               */
/***********************************************************************************************/

static ui_iface_app *inst = NULL;

void ui_iface_app::on_lang_changed(app_event_info_h event_info)
{
	char *locale = NULL;
	system_settings_get_value_string(SYSTEM_SETTINGS_KEY_LOCALE_LANGUAGE, &locale);
	elm_language_set(locale);
	free(locale);
}

void ui_iface_app::on_low_memory(app_event_info_h event_info)
{

}

void ui_iface_app::on_low_battery(app_event_info_h event_info)
{

}

void ui_iface_app::on_region_changed(app_event_info_h event_info)
{

}

void ui_iface_app::on_orient_changed(app_event_info_h event_info)
{

}

bool ui_iface_app::on_create()
{
	return this->impl->init();
}

void ui_iface_app::on_pause()
{
	this->impl->viewmgr->deactivate();
}

void ui_iface_app::on_resume()
{
//	this->impl->viewmgr->activate();
}

void ui_iface_app::on_control(app_control_h app_control)
{
	/* Handle the launch request. */
	this->impl->viewmgr->activate();
}

void ui_iface_app::on_terminate()
{
	delete(this);
}

ui_iface_app::ui_iface_app(const char *pkg, const char *locale_dir, ui_iface_viewmgr *viewmgr)
{
	if (inst)
	{
		LOGE("You created ui_iface_app multiple times!!");
	}
	inst = this;

	this->impl = new ui_iface_app_impl(this, pkg, locale_dir, viewmgr);
}

int ui_iface_app::run(int argc, char **argv)
{
	return this->impl->run(argc, argv);
}

ui_iface_app::~ui_iface_app()
{
	delete (this->impl);
	inst = NULL;
}

ui_iface_viewmgr *ui_iface_app::get_viewmgr()
{
	return this->impl->viewmgr;
}

ui_iface_app *ui_iface_app::get_instance()
{
	return inst;
}
