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
#include "../../../include/efl/mobile/ui_viewmanager.h"

using namespace efl_viewmgr;
using namespace viewmgr;

static bool app_create(void *data)
{
	ui_app *app = static_cast<ui_app *>(data);
	return app->on_create();
}

static void app_terminate(void *data)
{
	ui_app *app = static_cast<ui_app *>(data);
	app->on_terminate();
}

static void app_pause(void *data)
{
	ui_app *app = static_cast<ui_app *>(data);
	app->on_pause();
}

static void app_resume(void *data)
{
	ui_app *app = static_cast<ui_app *>(data);
	app->on_resume();
}

static void app_control(app_control_s *app_control, void *data)
{
	ui_app *app = static_cast<ui_app *>(data);
	app->on_control(app_control);
}

bool ui_app::on_create()
{
	LOGE("create!!");

	/* Hook to take necessary actions before main event loop starts
	 Initialize UI resources and application's data
	 If this function returns true, the main loop of application starts
	 If this function returns false, the application is terminated */

	//FIXME: this scale value should be configurable.
	elm_app_base_scale_set(2.6);

	/* Bind package locale file */
	bindtextdomain(this->pkg, this->locale_dir);
	textdomain (this->pkg);

	this->viewmgr = new ui_viewmgr(this->pkg);

	if (!this->viewmgr)
	{
		LOGE("Failed to create a viewmgr(%s)", this->pkg);
		return false;
	}

	return true;
}

void ui_app::on_pause()
{
	this->viewmgr->deactivate();
}

void ui_app::on_resume()
{
}

void ui_app::on_control(app_control_h app_control)
{
	this->viewmgr->activate();
	/* Handle the launch request. */
}

void ui_app::on_terminate()
{
}

ui_app::ui_app(const char *pkg, const char *locale_dir)
		: viewmgr(NULL)
{
	pkg = eina_stringshare_add(pkg);
	locale_dir = eina_stringshare_add(locale_dir);
}

int ui_app::start(int argc, char **argv)
{
	ui_app_lifecycle_callback_s event_callback = { 0, };

	event_callback.create = app_create;
	event_callback.terminate = app_terminate;
	event_callback.pause = app_pause;
	event_callback.resume = app_resume;
	event_callback.app_control = app_control;

	int ret = ui_app_main(argc, argv, &event_callback, this);

	if (ret != APP_ERROR_NONE)
	{
		LOGE("ui_app_main() is failed. err = %d", ret);
	}

	return ret;
}

ui_app::~ui_app()
{
	eina_stringshare_del(this->pkg);
	delete (this->viewmgr);
}
