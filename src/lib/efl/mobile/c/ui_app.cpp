#include "../../../../include/efl/mobile/ui_mobile_viewmanager.h"
#include "../../../../include/efl/mobile/c/ui_mobile_viewmanager.h"

using namespace efl_viewmanager;

class ui_app_capi : public ui_app
{
private:
	ui_app_lifecycle_callback_s capi_lifecycle_callback;
	ui_app_event_callback_s capi_event_callback;
	void *data;

protected:
	bool on_create()
	{
		if (!ui_app::on_create())
		{
			return false;
		}

		if (this->capi_lifecycle_callback.create)
			this->capi_lifecycle_callback.create(this->data);

		return true;
	}

	void on_terminate()
	{
		if (this->capi_lifecycle_callback.terminate)
			this->capi_lifecycle_callback.terminate(this->data);
	}

	void on_pause()
	{
		if (this->capi_lifecycle_callback.pause)
			this->capi_lifecycle_callback.pause(this->data);
	}

	void on_resume()
	{
		if (this->capi_lifecycle_callback.resume)
			this->capi_lifecycle_callback.resume(this->data);
	}

	void on_control(app_control_h app_control)
	{
		ui_app::on_control(app_control);

		if (this->capi_lifecycle_callback.app_control)
			this->capi_lifecycle_callback.app_control(app_control, this->data);
	}

	void on_low_battery(app_event_info_h event_info)
	{
		if (this->capi_event_callback.low_battery)
			this->capi_event_callback.low_battery(event_info, this->data);
	}

	void on_low_memory(app_event_info_h event_info)
	{
		if (this->capi_event_callback.low_memory)
			this->capi_event_callback.low_memory(event_info, this->data);
	}

	void on_orient_changed(app_event_info_h event_info)
	{
		if (this->capi_event_callback.orient_changed)
			this->capi_event_callback.orient_changed(event_info, this->data);
	}

	void on_lang_changed(app_event_info_h event_info)
	{
		if (this->capi_event_callback.lang_changed)
			this->capi_event_callback.lang_changed(event_info, this->data);
	}

	void on_region_changed(app_event_info_h event_info)
	{
		if (this->capi_event_callback.region_changed)
			this->capi_event_callback.region_changed(event_info, this->data);
	}

public:
	ui_app_capi(const char *pkg, const char *locale_dir)
		: ui_app(pkg, locale_dir)
	{
	}

	~ui_app_capi()
	{
	}

	int run(int argc, char **argv, ui_app_lifecycle_callback_s *lifecycle_callback,
		  ui_app_event_callback_s *event_callback, void *data)
	{
		if (lifecycle_callback)
			this->capi_lifecycle_callback = *lifecycle_callback;
		if (event_callback)
			this->capi_event_callback = *event_callback;
		this->data = data;

		return ui_app::run(argc, argv);
	}

	ui_app_lifecycle_callback_s get_app_lifecycle_callback()
	{
		return this->capi_lifecycle_callback;
	}

	ui_app_event_callback_s get_app_event_callback()
	{
		return this->capi_event_callback;
	}

	void* get_data()
	{
		return this->data;
	}
};


static ui_app_capi *g_app = NULL;

bool ui_app_init(const char *pkg, const char *locale_dir)
{
	ui_app_capi *app = g_app;
	if (app) return true;

	app = new ui_app_capi(pkg, locale_dir);
	if (!app)
	{
		LOGE("Failed to create new ui_app_capi()!");
		return false;
	}

	g_app = app;

	return true;
}

int ui_app_run(int argc, char **argv, ui_app_lifecycle_callback_s *lifecycle_callback, ui_app_event_callback_s *event_callback, void *data)
{
	ui_app_capi *app = g_app;
	if (!app) return -1;

	return app->run(argc, argv, lifecycle_callback, event_callback, data);
}

ui_viewmgr *ui_app_viewmgr_get()
{
	ui_app_capi *app = g_app;
	if (!app) return NULL;

	return app->get_viewmgr();
}

bool ui_app_term(void)
{
	ui_app_capi *app = g_app;
	if (app) delete (app);

	return true;
}
