#include "../../../../include/efl/mobile/ui_mobile_viewmanager.h"
#include "../../../../include/efl/mobile/c/ui_app.h"

using namespace efl_viewmanager;

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
}
