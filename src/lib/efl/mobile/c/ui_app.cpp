#include "../../../../include/efl/mobile/c/ui_mobile_viewmanager.h"
#include "../../../../include/efl/mobile/c/ui_app.h"

using namespace efl_viewmanager;

class ui_app_capi : public ui_app
{
private:
	ui_app_lifecycle_callback_s capi_event_callback;
	void *data;

protected:
	bool on_create()
	{
		if (!ui_app::on_create())
		{
			return false;
		}

		if (this->capi_event_callback.create)
			this->capi_event_callback.create(this->data);

		return true;
	}

	void on_terminate()
	{
		if (this->capi_event_callback.terminate)
			this->capi_event_callback.terminate(this->data);
	}

	void on_pause()
	{
		if (this->capi_event_callback.pause)
			this->capi_event_callback.pause(this->data);
	}

	void on_resume()
	{
		if (this->capi_event_callback.resume)
			this->capi_event_callback.resume(this->data);
	}

	void on_control(app_control_h app_control)
	{
		ui_app::on_control(app_control);

		if (this->capi_event_callback.app_control)
			this->capi_event_callback.app_control(app_control, this->data);
	}

public:
	ui_app_capi(const char *pkg, const char *locale_dir)
		: ui_app(pkg, locale_dir)
	{
	}

	~ui_app_capi()
	{
	}

	int run(int argc, char **argv, ui_app_lifecycle_callback_s *event_callback, void *data)
	{
		this->capi_event_callback = *event_callback;
		this->data = data;

		return ui_app::run(argc, argv);
	}

	ui_app_lifecycle_callback_s get_app_lifecycle_callback()
	{
		return this->capi_event_callback;
	}

	void* get_data()
	{
		return this->data;
	}
};

extern "C" {
	static ui_app_capi *app = NULL;

	bool ui_app_init(const char *pkg, const char *locale_dir)
	{
		app = new ui_app_capi(pkg, locale_dir);

		if (app) return true;
		else return false;
	}

	int ui_app_run(int argc, char **argv, ui_app_lifecycle_callback_s *event_callback, void *data)
	{
		return app->run(argc, argv, event_callback, data);
	}

	ui_viewmgr *ui_app_viewmgr_get()
	{
		return app->get_viewmgr();
	}
}
