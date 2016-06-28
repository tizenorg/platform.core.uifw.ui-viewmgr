#include "../../../../include/efl/mobile/c/_ui_private.h"
#include "../../../../include/efl/mobile/c/ui_application.h"

using namespace efl_viewmanager;

class ui_app_capi : public UiApp
{
public:
	ui_app_lifecycle_callback_s capi_lifecycle_callback;
	void *data;

	bool on_create()
	{
		if (!UiApp::on_create()) return false;

		if (!this->capi_lifecycle_callback.create) return false;
		return this->capi_lifecycle_callback.create(this->data);
	}

	void on_terminate()
	{
		UiApp::on_terminate();

		if (!this->capi_lifecycle_callback.terminate) return;
		this->capi_lifecycle_callback.terminate(this->data);
	}

	void on_pause()
	{
		UiApp::on_pause();

		if (!this->capi_lifecycle_callback.pause) return;
		this->capi_lifecycle_callback.pause(this->data);
	}

	void on_resume()
	{
		UiApp::on_resume();

		if (!this->capi_lifecycle_callback.resume) return;
		this->capi_lifecycle_callback.resume(this->data);
	}

	void on_control(app_control_h app_control)
	{
		UiApp::on_control(app_control);

		if (!this->capi_lifecycle_callback.app_control) return;
		this->capi_lifecycle_callback.app_control(app_control, this->data);
	}

	ui_app_capi(const char *pkg, const char *locale_dir)
			: UiApp(pkg, locale_dir), data(NULL)
	{
	}

	~ui_app_capi()
	{
	}

	int run(int argc, char **argv, ui_app_lifecycle_callback_s *lifecycle_callback, void *user_data)
	{
		if (lifecycle_callback)
		{
			this->capi_lifecycle_callback = *lifecycle_callback;
		}

		this->data = user_data;

		return UiApp::run(argc, argv);
	}
};

static ui_app_capi *g_app = NULL;

EAPI bool ui_application_init(const char *pkg, const char *locale_dir)
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

EAPI int ui_application_run(int argc, char **argv, ui_app_lifecycle_callback_s *lifecycle_callback, void *user_data)
{
	ui_app_capi *app = g_app;
	if (!app) return -1;

	return app->run(argc, argv, lifecycle_callback, user_data);
}

EAPI bool ui_application_term(void)
{
	ui_app_capi *app = g_app;
	if (app) delete (app);
	else return false;

	g_app = NULL;

	return true;
}
