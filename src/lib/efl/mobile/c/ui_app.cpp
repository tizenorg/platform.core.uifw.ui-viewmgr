#include "../../../../include/efl/mobile/ui_mobile_viewmanager.h"
#include "../../../../include/efl/mobile/c/ui_mobile_viewmanager.h"

using namespace efl_viewmanager;

static ui_app_capi *g_app = NULL;

class ui_app_capi : public ui_app
{
public:
	ui_app_lifecycle_callback_s capi_lifecycle_callback;
	ui_app_event_callback_s capi_event_callback;
	void *data;

	bool on_create()
	{
		if (!ui_app::on_create()) return false;

		if (!this->capi_lifecycle_callback.create) return false;
		return this->capi_lifecycle_callback.create(this->data);
	}

	void on_terminate()
	{
		ui_app::on_terminate();

		if (!this->capi_lifecycle_callback.terminate) return;
		this->capi_lifecycle_callback.terminate(this->data);
	}

	void on_pause()
	{
		ui_app:on_pause();

		if (!this->capi_lifecycle_callback.pause) return;
		this->capi_lifecycle_callback.pause(this->data);
	}

	void on_resume()
	{
		ui_app::on_resume();

		if (!this->capi_lifecycle_callback.resume) return;
		this->capi_lifecycle_callback.resume(this->data);
	}

	void on_control(app_control_h app_control)
	{
		ui_app::on_control(app_control);

		if (!this->capi_lifecycle_callback.app_control) return;
		this->capi_lifecycle_callback.app_control(app_control, this->data);
	}

	void on_low_battery(app_event_info_h event_info)
	{
		if (!this->capi_event_callback.low_battery) return;
		this->capi_event_callback.low_battery(event_info, this->data);
	}

	void on_low_memory(app_event_info_h event_info)
	{
		if (!this->capi_event_callback.low_memory) return;
		this->capi_event_callback.low_memory(event_info, this->data);
	}

	void on_orient_changed(app_event_info_h event_info)
	{
		if (!this->capi_event_callback.orient_changed) return;
		this->capi_event_callback.orient_changed(event_info, this->data);
	}

	void on_lang_changed(app_event_info_h event_info)
	{
		if (!this->capi_event_callback.lang_changed) return;
		this->capi_event_callback.lang_changed(event_info, this->data);
	}

	void on_region_changed(app_event_info_h event_info)
	{
		if (!this->capi_event_callback.region_changed) return;
		this->capi_event_callback.region_changed(event_info, this->data);
	}

	ui_app_capi(const char *pkg, const char *locale_dir)
			: ui_app(pkg, locale_dir), data(NULL)
	{
	}

	~ui_app_capi()
	{
	}

	int run(int argc, char **argv, ui_app_lifecycle_callback_s *lifecycle_callback, void *data)
	{
		if (lifecycle_callback)
		{
			this->capi_lifecycle_callback = *lifecycle_callback;
		}

		this->data = data;

		return ui_app::run(argc, argv);
	}
};

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

int ui_app_run(int argc, char **argv, ui_app_lifecycle_callback_s *lifecycle_callback, void *data)
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
	g_app = NULL;

	return true;
}
