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
#include "../../../include/efl/mobile/ui_mobile_viewmanager.h"

/***********************************************************************************************/
/* Internal class Implementation                                                               */
/***********************************************************************************************/
namespace efl_viewmanager
{

class ui_app_capi_impl
{
	friend class ui_app_capi;

private:
	ui_app_capi *app;
	ui_viewmgr *viewmgr;
	Eina_Stringshare *pkg;
	Eina_Stringshare *locale_dir;
	void *data;

	ui_app_lifecycle_callback_s capi_event_callback;

public:
	ui_app_capi_impl(ui_app_capi *ui_app_capi, const char *pkg, const char *locale_dir);
	~ui_app_capi_impl();

	bool init();

	int run(int argc, char **argv, ui_app_lifecycle_callback_s *event_callback, void *data);
	ui_viewmgr *get_viewmgr();

	ui_app_lifecycle_callback_s get_app_lifecycle_callback();
	void* get_data();
};

}

ui_app_lifecycle_callback_s ui_app_capi_impl::get_app_lifecycle_callback()
{
	return this->capi_event_callback;
}

void* ui_app_capi_impl::get_data()
{
	return this->data;
}

ui_app_capi_impl::ui_app_capi_impl(ui_app_capi *ui_app_capi, const char *pkg, const char *locale_dir)
		: app(ui_app_capi), viewmgr(NULL)
{
	this->pkg = eina_stringshare_add(pkg);
	this->locale_dir = eina_stringshare_add(locale_dir);
	this->capi_event_callback = {0,};
}

ui_app_capi_impl::~ui_app_capi_impl()
{
	delete (this->viewmgr);
	eina_stringshare_del(this->pkg);
	eina_stringshare_del(this->locale_dir);
}

bool ui_app_capi_impl::init()
{
	//FIXME: this scale value should be configurable.
	elm_app_base_scale_set(2.6);

	/* Bind package locale file */
	bindtextdomain(this->pkg, this->locale_dir);
	textdomain(this->pkg);

	/* Default View Manager */
	this->viewmgr = new ui_viewmgr(this->pkg);

	if (!this->viewmgr)
	{
		LOGE("Failed to create a viewmgr(%s)", this->pkg);
		return false;
	}
	return true;
}

static bool app_create(void *data)
{
	ui_app_capi_impl *app = static_cast<ui_app_capi_impl *>(data);

	int ret = app->init();

	if (!ret) return false;
	else
	{
		if (app->get_app_lifecycle_callback().create)
			app->get_app_lifecycle_callback().create(NULL);
	}

	return true;
}


static void app_control(app_control_s *app_control, void *data)
{
	ui_app_capi_impl *app = static_cast<ui_app_capi_impl *>(data);

	app->get_viewmgr()->activate();

	if (app->get_app_lifecycle_callback().app_control)
		app->get_app_lifecycle_callback().app_control(app_control, NULL);

}

int ui_app_capi_impl::run(int argc, char **argv, ui_app_lifecycle_callback_s *event_callback, void *data)
{
	int ret;

	this->data = data;

	if (event_callback->create)
	{
		this->capi_event_callback.create = event_callback->create;
		event_callback->create = app_create;
	}
	else
		event_callback->create = app_create;

	if (event_callback->app_control)
	{
		this->capi_event_callback.app_control = event_callback->app_control;
		event_callback->app_control = app_control;
	}
	else
		event_callback->app_control = app_control;

	ret = ui_app_main(argc, argv, event_callback, this);

	if (ret != APP_ERROR_NONE)
	{
		LOGE("ui_app_main() is failed. err = %d", ret);
	}

	return ret;
}

ui_viewmgr *ui_app_capi_impl::get_viewmgr()
{
	return this->viewmgr;
}


/***********************************************************************************************/
/* External class Implementation                                                               */
/***********************************************************************************************/

static ui_app_capi *inst = NULL;


ui_app_capi::ui_app_capi(const char *pkg, const char *locale_dir)
{
	if (inst)
	{
		LOGE("You created ui_app_capi multiple times!!");
	}
	inst = this;
	this->impl = new ui_app_capi_impl(this, pkg, locale_dir);

}

ui_app_capi::~ui_app_capi()
{
	delete (this->impl);
	inst = NULL;
}

int ui_app_capi::run(int argc, char **argv, ui_app_lifecycle_callback_s *event_callback, void *data)
{
	return this->impl->run(argc, argv, event_callback, data);
}

ui_viewmgr *ui_app_capi::get_viewmgr()
{
	return this->impl->get_viewmgr();
}

ui_app_capi *ui_app_capi::get_instance()
{
	return inst;
}
